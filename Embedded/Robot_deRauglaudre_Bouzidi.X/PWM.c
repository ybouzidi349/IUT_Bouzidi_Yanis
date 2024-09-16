#include <xc.h>
#include "IO.h"
#include "PWM.h"
#include "Toolbox.h"
#include "robot.h"

#define PWMPER 24.0

void InitPWM(void) {
    PTCON2bits.PCLKDIV = 0b000; //Divide by 1
    PTPER = 100 * PWMPER; //ÈPriode en pourcentage
    //ÈRglage PWM moteur 1 sur hacheur 1
    IOCON1bits.PMOD = 0b11; //PWM I/O pin pair is in the True Independent Output mode
    IOCON1bits.PENL = 1;
    IOCON1bits.PENH = 1;
    FCLCON1 = 0x0003; //ÈDsactive la gestion des faults
    IOCON2bits.PMOD = 0b11; //PWM I/O pin pair is in the True Independent Output mode
    IOCON2bits.PENL = 1;
    IOCON2bits.PENH = 1;
    FCLCON2 = 0x0003; //ÈDsactive la gestion des faults
    /* Enable PWM Module */
    PTCONbits.PTEN = 1;
}

void PWMSetSpeedConsigne(float vitesseEnPourcents, int moteur)
{
    if(moteur){
        robotState.vitesseGaucheConsigne = vitesseEnPourcents;
    }else{
        robotState.vitesseDroiteConsigne = vitesseEnPourcents;
    }
}

float acceleration = 5;
double talon = 20;

void PWMUpdateSpeed() {
    // Cette fonction est appelee sur timer et permet de suivre des rampes d acceleration
    if (robotState.vitesseDroiteCommandeCourante < robotState.vitesseDroiteConsigne)
        robotState.vitesseDroiteCommandeCourante = Min(
            robotState.vitesseDroiteCommandeCourante + acceleration,
            robotState.vitesseDroiteConsigne);
    if (robotState.vitesseDroiteCommandeCourante > robotState.vitesseDroiteConsigne)
        robotState.vitesseDroiteCommandeCourante = Max(
            robotState.vitesseDroiteCommandeCourante - acceleration,
            robotState.vitesseDroiteConsigne);
    if (robotState.vitesseDroiteCommandeCourante >= 0) {
        SDC1 = robotState.vitesseDroiteCommandeCourante * PWMPER + talon;
        PDC1 = talon;
    } else {
        SDC1 = talon;
        PDC1 = -robotState.vitesseDroiteCommandeCourante * PWMPER + talon;
    }
    if (robotState.vitesseGaucheCommandeCourante < robotState.vitesseGaucheConsigne)
        robotState.vitesseGaucheCommandeCourante = Min(
            robotState.vitesseGaucheCommandeCourante + acceleration,
            robotState.vitesseGaucheConsigne);
    if (robotState.vitesseGaucheCommandeCourante > robotState.vitesseGaucheConsigne)
        robotState.vitesseGaucheCommandeCourante = Max(
            robotState.vitesseGaucheCommandeCourante - acceleration,
            robotState.vitesseGaucheConsigne);
    if (robotState.vitesseGaucheCommandeCourante > 0) {
        SDC2 = robotState.vitesseGaucheCommandeCourante * PWMPER + talon;
        PDC2 = talon;
    } else {
        SDC2 = talon;
        PDC2 = -robotState.vitesseGaucheCommandeCourante * PWMPER + talon;
    }
}

/*
void PWMSetSpeed(float vitesseEnPourcents, int moteur) {
    if (moteur) {

        if (vitesseEnPourcents < 0) {
            PDC1 = (-vitesseEnPourcents) * PWMPER + talon;
            SDC1 = talon;
        } else {
            SDC1 = vitesseEnPourcents * PWMPER + talon;
            PDC1 = talon;
        }

    } else {

        if (vitesseEnPourcents < 0) {
            PDC2 = (-vitesseEnPourcents) * PWMPER + talon;
            SDC2 = talon;
        } else {
            SDC2 = vitesseEnPourcents * PWMPER + talon;
            PDC2 = talon;
        }
    }
}
*/
