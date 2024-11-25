using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using ExtendedSerialPort_NS;
using System.IO.Ports;
using System.Windows.Threading;
using System.Collections;


namespace RobotInterface
{
    public partial class MainWindow : Window
    {
        ExtendedSerialPort serialPort1;
        DispatcherTimer timerAffichage;
        Robot robot = new Robot();
        StateReception rcvState = StateReception.Waiting;
        int msgDecodedFunction = 0;
        int msgDecodedPayloadLength = 0;
        byte[] msgDecodedPayload;
        int msgDecodedPayloadIndex = 0;

        public enum StateReception
        {
            Waiting,
            FunctionMSB,
            FunctionLSB,
            PayloadLengthMSB,
            PayloadLengthLSB,
            Payload,
            CheckSum
        }

        public MainWindow()
        {
            InitializeComponent();
            serialPort1 = new ExtendedSerialPort("COM6", 115200, Parity.None, 8, StopBits.One);
            serialPort1.DataReceived += SerialPort1_DataReceived;
            serialPort1.Open();

            timerAffichage = new DispatcherTimer();
            timerAffichage.Interval = new TimeSpan(0, 0, 0, 0, 100);
            timerAffichage.Tick += TimerAffichage_Tick;
            timerAffichage.Start();
        }

        //////////////////////////////////////////////// PROGRAMMATION DES BOUTONS ////////////////////////////////////////////////
        
        private void buttonEnvoyer_Click(object sender, RoutedEventArgs e)
        {
            SendMessage();
        }

        private void textBoxEmission_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
                SendMessage();
        }

        private void buttonClear_Click(object sender, RoutedEventArgs e)
        {
            textBoxReception.Text = "";
        }

        private void buttonTest_Click(object sender, RoutedEventArgs e)
        {
            //byte[] byteList = new byte[20];

            string message = "Bonjour";

            byte[] byteList = Encoding.ASCII.GetBytes(message);

            /*for (int i = 0; i < 20; i++)
            {
                byteList[i] = (byte)(2 * i);
            }*/

            int msgFunction = 0x0080;
            int msgPayloadLength = byteList.Length;

            UartEncodeAndSendMessage(msgFunction, msgPayloadLength, byteList);
        }

        //////////////////////////////////////////////// RECEPTION DES MESSAGES ////////////////////////////////////////////////
        private void TimerAffichage_Tick(object? sender, EventArgs e)
        {
            if (robot.byteListReceived.Count != 0)
            {
                if (robot.byteListReceived.Count != 0)
                {
                    byte receivedByte = robot.byteListReceived.Dequeue();
                    //DecodeMessage(receivedByte);

                    //if(robot.receivedText != "" && robot.receivedText != "\r")
                    //{
                    //    textBoxReception.Text += robot.receivedText;
                    //    robot.receivedText = "";
                    //}
                    //while (robot.byteListReceived.Count > 0)
                    //{
                    //    //var c = robot.byteListReceived.Dequeue();
                    //    // ASCII :
                    //    //    textBoxReception.Text += Convert.ToChar(c);

                    //    // HEXA :
                    //    //    textBoxReception.Text += "0x" + c.ToString("X2") + " ";

                    //}

                    if (robot.byteListReceived.Count >= 1)
                        textBoxReception.Text += receivedByte.ToString("X2") + " ";
                    else
                        textBoxReception.Text += receivedByte.ToString("X2") + "\n";
                }
            }

        }
        private async void SerialPort1_DataReceived(object? sender, DataReceivedArgs e)
        {
            for (int i = 0; i < e.Data.Length; i++)
            {
                robot.byteListReceived.Enqueue(e.Data[i]);
            }
            robot.receivedText += Encoding.UTF8.GetString(e.Data, 0, e.Data.Length);
        }

        private void DecodeMessage(byte c)
        {
            switch (rcvState)
            {
                case StateReception.Waiting:
                    
                if(c != 0x00 && c != 0xFE)
                    rcvState = StateReception.FunctionMSB;

                break;

                case StateReception.FunctionMSB:
                    msgDecodedFunction = c;
                    rcvState = StateReception.FunctionLSB;
                break;

                case StateReception.FunctionLSB:
                    msgDecodedFunction = (msgDecodedFunction << 8) | c;
                    rcvState = StateReception.PayloadLengthMSB;
                    break;

                case StateReception.PayloadLengthMSB:
                    msgDecodedPayloadLength = c;
                    rcvState = StateReception.PayloadLengthLSB;
                    break;

                case StateReception.PayloadLengthLSB:
                    msgDecodedPayloadLength = (msgDecodedPayloadLength << 8) | c;
                    msgDecodedPayload = new byte[msgDecodedPayloadLength];
                    rcvState = StateReception.Payload;
                    break;

                case StateReception.Payload:
                    msgDecodedPayload[msgDecodedPayloadIndex++] = c;
                    if (msgDecodedPayloadIndex == msgDecodedPayloadLength)
                    {
                        rcvState = StateReception.CheckSum;
                    }
                    break;

                case StateReception.CheckSum:
                    byte calculatedChecksum = CalculateChecksum(msgDecodedFunction, msgDecodedPayloadLength, msgDecodedPayload);
                    byte receivedChecksum = c;

                    if (calculatedChecksum == receivedChecksum)
                    {
                        Console.WriteLine("Message valide");
                        rcvState = StateReception.Waiting;
                    }
                    else
                    {
                        Console.WriteLine("Message incorrect");
                        rcvState = StateReception.CheckSum;
                    }

                    break;

                default:
                    rcvState = StateReception.Waiting;
                    break;
            }
        }


        //////////////////////////////////////////////// ENVOIE DES MESSAGES ////////////////////////////////////////////////

        private void SendMessage()
        {
            string value = textBoxEmission.Text;
            textBoxEmission.Text = "";
            if (value.Length > 0)
            {
                serialPort1.WriteLine(value);
            }
        }

        byte CalculateChecksum(int msgFunction, int msgPayloadLength, byte[] msgPayload)
        {
            byte checksum = 0;

            checksum ^= 0xFE;
            checksum ^= 0x00;
            checksum ^= (byte)msgFunction;
            checksum ^= (byte)msgPayloadLength;

            for (int i = 0; i < msgPayloadLength; i++)
            {
                checksum ^= msgPayload[i];
            }
            return checksum;
        }

        void UartEncodeAndSendMessage(int msgFunction, int msgPayloadLength, byte[] msgPayload)
        {
            byte[] trame = new byte[msgPayloadLength + 6];

            trame[0] = 0xFE;
            trame[1] = 0x00;
            trame[2] = (byte)msgFunction;
            trame[3] = (byte)(msgPayloadLength >> 8);
            trame[4] = (byte)(msgPayloadLength & 0xFF);

            for (int i = 0; i < msgPayloadLength; i++)
            {
                trame[i + 5] = msgPayload[i];
            }

            trame[msgPayloadLength + 5] += CalculateChecksum(msgFunction, msgPayloadLength, msgPayload);
            serialPort1.Write(trame, 0, trame.Length);
        }
    }
}

