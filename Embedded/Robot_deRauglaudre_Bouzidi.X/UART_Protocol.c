#include <xc.h>
#include "UART_Protocol.h"

int msgDecodedFunction = 0;
int msgDecodedPayloadLength = 0;
unsigned char msgDecodedPayload[128];
int msgDecodedPayloadIndex = 0;

unsigned char UartCalculateChecksum(int msgFunction, int msgPayloadLength, unsigned char* msgPayload) {

}

void UartEncodeAndSendMessage(int msgFunction, int msgPayloadLength, unsigned char* msgPayload) {

}

void UartDecodeMessage(unsigned char c) {

}

void UartProcessDecodedMessage(int function,int payloadLength, unsigned char* payload) {

}

