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
        public MainWindow()
        {
            InitializeComponent();
            serialPort1 = new ExtendedSerialPort("COM13", 115200, Parity.None, 8, StopBits.One);
            serialPort1.DataReceived += SerialPort1_DataReceived;
            serialPort1.Open();

            timerAffichage = new DispatcherTimer();
            timerAffichage.Interval = new TimeSpan(0, 0, 0, 0, 100);
            timerAffichage.Tick += TimerAffichage_Tick;
            timerAffichage.Start();
        }
        private void TimerAffichage_Tick(object? sender, EventArgs e)
        {
            if (robot.byteListReceived.Count != 0)
            {
                textBoxReception.Text += robot.byteListReceived.Dequeue().ToString("X2") + " ";
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

        private void buttonEnvoyer_Click(object sender, RoutedEventArgs e)
        {
            SendMessage();
        }

        private void textBoxEmission_KeyUp(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
                SendMessage();
        }

        private void SendMessage()
        {
            string value = textBoxEmission.Text;
            textBoxEmission.Text = "";
            if (value.Length > 0)
            {
                serialPort1.WriteLine(value);
            }
        }

        private void buttonClear_Click(object sender, RoutedEventArgs e)
        {
            textBoxReception.Text = "";
        }

        private void buttonTest_Click(object sender, RoutedEventArgs e)
        {
            byte[] byteList = new byte[20];
            for (int i = 0; i < 20; i++)
            {
                byteList[i] = (byte)(2 * i);
            }  
            serialPort1.Write(byteList, 0, byteList.Length);
        }
    }
}

