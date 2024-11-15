#include <xc.h>
#include "UART.h"
#include "ChipConfig.h"

/*
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) {
    IFS0bits.U1RXIF = 0;

    if (U1STAbits.FERR == 1) {
        U1STAbits.FERR = 0;
    }

    if (U1STAbits.OERR == 1) {
        U1STAbits.OERR = 0;
    }

    while (U1STAbits.URXDA == 1) {
        U1TXREG = U1RXREG;
    }
}
*/

void InitUART(void) {
    U1MODEbits.STSEL = 0; // 1-stop bit
    U1MODEbits.PDSEL = 0; // No Parity, 8-data bits
    U1MODEbits.ABAUD = 0; // Auto-Baud Disabled
    U1MODEbits.BRGH = 1; // Low Speed mode
    U1BRG = BRGVAL; // BAUD Rate Setting
    U1STAbits.UTXISEL0 = 0; // Interrupt after one Tx character is transmitted
    U1STAbits.UTXISEL1 = 0;
    IFS0bits.U1TXIF = 0; // clear TX interrupt flag
    IEC0bits.U1TXIE = 1; // UART Tx interrupt
    U1STAbits.URXISEL = 0; // Interrupt after one RX character is received;
    IFS0bits.U1RXIF = 0; // clear RX interrupt flag
    IEC0bits.U1RXIE = 1; // UART Rx interrupt
    U1MODEbits.UARTEN = 1; // Enable UART
    U1STAbits.UTXEN = 1; // Enable UART Tx
}

void SendMessageDirect(unsigned char* message, int length) {
    unsigned char i = 0;
    for (i = 0; i < length; i++) {
        while (U1STAbits.UTXBF); // wait while Tx buffer full
        U1TXREG = *(message)++; // Transmit one character
    }
}

byte CalculateChecksum(int msgFunction, int msgPayloadLength, byte[] msgPayload) {
    
    int checksum = 0;
    checksum += msgFunction & 0xFF;  
    checksum += msgPayloadLength & 0xFF;
    for (int i = 0; i < msgPayloadLength; i++) {
        checksum += msgPayload[i] & 0xFF;
    }
    return (byte)(checksum & 0xFF); 
}

void UartEncodeAndSendMessage(int msgFunction, int msgPayloadLength, byte[] msgPayload) {
    
    
    byte checksum = CalculateChecksum(msgFunction, msgPayloadLength, msgPayload);
    byte[] frame = new byte[msgPayloadLength + 3]; 
    
    
    frame[0] = (byte)(msgFunction & 0xFF); 
    frame[1] = (byte)(msgPayloadLength & 0xFF);
    for (int i = 0; i < msgPayloadLength; i++) {
        frame[i + 2] = msgPayload[i];
    }
    byte[] finalFrame = new byte[frame.Length + 1];
    for (int i = 0; i < frame.Length; i++) {
        finalFrame[i] = frame[i];
    }
    finalFrame[frame.Length] = checksum;
    Serial.write(finalFrame, finalFrame.Length);
}