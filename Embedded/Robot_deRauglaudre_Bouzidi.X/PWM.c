#include <xc.h>
#include "IO.h"
#include "PWM.h"

#define PWMPER 24.0

void InitPWM(void) {
PTCON2bits.PCLKDIV = 0b000; //Divide by 1
PTPER = 100 * PWMPER; //�Priode en pourcentage
//�Rglage PWM moteur 1 sur hacheur 1
IOCON1bits.PMOD = 0b11; //PWM I/O pin pair is in the True Independent Output mode
IOCON1bits.PENL = 1;
IOCON1bits.PENH = 1;
FCLCON1 = 0x0003; //�Dsactive la gestion des faults
IOCON2bits.PMOD = 0b11; //PWM I/O pin pair is in the True Independent Output mode
IOCON2bits.PENL = 1;
IOCON2bits.PENH = 1;
FCLCON2 = 0x0003; //�Dsactive la gestion des faults
/* Enable PWM Module */
PTCONbits.PTEN = 1;
}
    double talon = 20;
void PWMSetSpeed(float vitesseEnPourcents)
{
    if(vitesseEnPourcents < 0){
        SDC1 = (-vitesseEnPourcents) * PWMPER + talon;
        PDC1 = talon;
    }else{
        PDC1 = vitesseEnPourcents * PWMPER + talon;
        SDC1 = talon;
    }
     
}
