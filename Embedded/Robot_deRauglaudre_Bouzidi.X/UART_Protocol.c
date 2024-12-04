#include <xc.h>
#include "UART_Protocol.h"
#include "CB_TX1.h"
#include "robot.h"

int msgDecodedFunction = 0;
int msgDecodedPayloadLength = 0;
unsigned char msgDecodedPayload[128];
int msgDecodedPayloadIndex = 0;
int rcvState = 0;
unsigned char calculatedChecksum;

unsigned char UartCalculateChecksum(int msgFunction, int msgPayloadLength, unsigned char* msgPayload) {
    unsigned char checksum = 0;

    checksum ^= 0xFE;
    checksum ^= 0x00;
    checksum ^= (unsigned char) msgFunction;
    checksum ^= (unsigned char) msgPayloadLength;

    for (int i = 0; i < msgPayloadLength; i++) {
        checksum ^= msgPayload[i];
    }

    return checksum;
}

void UartEncodeAndSendMessage(int msgFunction, int msgPayloadLength, unsigned char* msgPayload) {
    unsigned char trame[msgPayloadLength + 6];

    trame[0] = 0xFE;
    trame[1] = 0x00;
    trame[2] = (unsigned char) msgFunction;
    trame[3] = (unsigned char) (msgPayloadLength >> 8);
    trame[4] = (unsigned char) (msgPayloadLength & 0xFF);

    for (int i = 0; i < msgPayloadLength; i++) {
        trame[i + 5] = msgPayload[i];
    }

    trame[msgPayloadLength + 5] = UartCalculateChecksum(msgFunction, msgPayloadLength, msgPayload);

    SendMessage(trame, msgPayloadLength + 6);
}

void UartDecodeMessage(unsigned char c) {

    switch (rcvState) {
        case 0:
            rcvState = 1;
            break;

        case 1:
            msgDecodedFunction = c << 8;
            rcvState = 2;
            break;

        case 2:
            msgDecodedFunction |= c;
            rcvState = 3;
            break;

        case 3:
            msgDecodedPayloadLength = c << 8;
            rcvState = 4;
            break;

        case 4:
            msgDecodedPayloadLength |= c;
            msgDecodedPayloadIndex = 0;
            rcvState = 5;
            break;

        case 5:
            msgDecodedPayload[msgDecodedPayloadIndex++] = c;
            if (msgDecodedPayloadIndex == msgDecodedPayloadLength) {
                rcvState = 6;
            }
            break;

        case 6:
            calculatedChecksum = UartCalculateChecksum(msgDecodedFunction, msgDecodedPayloadLength, msgDecodedPayload);

            if (calculatedChecksum == c) {
                UartProcessDecodedMessage(msgDecodedFunction, msgDecodedPayloadLength, msgDecodedPayload);
            }

            rcvState = 0;
            msgDecodedPayloadIndex = 0;
            break;

        default:
            rcvState = 0;
            break;
    }
}

void UartProcessDecodedMessage(int function, int payloadLength, unsigned char* payload) {

    UartEncodeAndSendMessage(function, payloadLength, payload);

    /*switch (function) {
        case SET_ROBOT_STATE:
            //SetRobotState(msgPayload[0]);
            break;

        case SET_ROBOT_MANUAL_CONTROL:
            //SetRobotAutoControlState(msgPayload[0]);
            break;

        case SET_ROBOT_MOTOR:

            
            break;

        default:
            break;
    }*/

}
