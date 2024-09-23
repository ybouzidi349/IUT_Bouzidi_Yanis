#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "ADC.h"
#include "Toolbox.h"
#include "PWM.h"
#include "main.h"
#include "robot.h"

unsigned char stateRobot;
unsigned char nextStateRobot = 0;

int main(void)
{

    InitOscillator();
    InitIO();
    InitTimer1();
    InitTimer4();
    InitTimer23();
    InitPWM();

    InitADC1();

    while (1)
    {
    }
}

int BinaryCapteur(float capteur)
{
    if (capteur < DISTANCE_LIM)
        return (1); // 1 : Presence d'obstacle
    else
        return (0);
}

int StateBinary(void)
{
    return BinaryCapteur(robotState.distanceTelemetreExtGauche) * 10000 +
           BinaryCapteur(robotState.distanceTelemetreGauche) * 1000 +
           BinaryCapteur(robotState.distanceTelemetreCentre) * 100 +
           BinaryCapteur(robotState.distanceTelemetreDroit) * 10 +
           BinaryCapteur(robotState.distanceTelemetreExtDroit);
}

void Infrarouge_Conversion()
{

    if (ADCIsConversionFinished() == 1)
    {
        ADCClearConversionFinishedFlag();
        unsigned int *result = ADCGetResult();
        float volts = ((float)result[0]) * 3.3 / 4096;
        robotState.distanceTelemetreExtGauche = 34 / volts - 5;
        volts = ((float)result[1]) * 3.3 / 4096;
        robotState.distanceTelemetreGauche = 34 / volts - 5;
        volts = ((float)result[2]) * 3.3 / 4096;
        robotState.distanceTelemetreCentre = 34 / volts - 5;
        volts = ((float)result[3]) * 3.3 / 4096;
        robotState.distanceTelemetreDroit = 34 / volts - 5;
        volts = ((float)result[4]) * 3.3 / 4096;
        robotState.distanceTelemetreExtDroit = 34 / volts - 5;
    }
}

void OperatingSystemLoop(void)
{
    switch (stateRobot)
    {
    case STATE_ATTENTE:
        timestamp = 0;
        PWMSetSpeedConsigne(0, MOTEUR_DROIT);
        PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
        stateRobot = STATE_ATTENTE_EN_COURS;
    case STATE_ATTENTE_EN_COURS:
        if (timestamp > 1000)
            stateRobot = STATE_AVANCE;
        break;
    case STATE_AVANCE:
        PWMSetSpeedConsigne(30, MOTEUR_DROIT);
        PWMSetSpeedConsigne(30, MOTEUR_GAUCHE);
        stateRobot = STATE_AVANCE_EN_COURS;
        break;
    case STATE_AVANCE_EN_COURS:
        SetNextRobotStateInAutomaticMode();
        break;
    case STATE_TOURNE_GAUCHE:
        PWMSetSpeedConsigne(30, MOTEUR_DROIT);
        PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
        stateRobot = STATE_TOURNE_GAUCHE_EN_COURS;
        break;
    case STATE_TOURNE_GAUCHE_EN_COURS:
        SetNextRobotStateInAutomaticMode();
        break;
    case STATE_TOURNE_DROITE:
        PWMSetSpeedConsigne(0, MOTEUR_DROIT);
        PWMSetSpeedConsigne(30, MOTEUR_GAUCHE);
        stateRobot = STATE_TOURNE_DROITE_EN_COURS;
        break;
    case STATE_TOURNE_DROITE_EN_COURS:
        SetNextRobotStateInAutomaticMode();
        break;
    case STATE_TOURNE_SUR_PLACE_GAUCHE:
        PWMSetSpeedConsigne(15, MOTEUR_DROIT);
        PWMSetSpeedConsigne(-15, MOTEUR_GAUCHE);
        stateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS;
        break;
    case STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS:
        SetNextRobotStateInAutomaticMode();
        break;
    case STATE_TOURNE_SUR_PLACE_DROITE:
        PWMSetSpeedConsigne(-15, MOTEUR_DROIT);
        PWMSetSpeedConsigne(15, MOTEUR_GAUCHE);
        stateRobot = STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS;
        break;
    case STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS:
        SetNextRobotStateInAutomaticMode();
        break;
    default:
        stateRobot = STATE_ATTENTE;
        break;
    }
}

void SetNextRobotStateInAutomaticMode()
{
    Operating(StateBinary());
    if (nextStateRobot != stateRobot - 1)
        stateRobot = nextStateRobot;
}

void Operating(int bynary)
{
    switch (bynary)
    {
    case 0b00000:
        nextStateRobot = STATE_AVANCE;
        break;
    case 0b00001:
    case 0b00010:
    case 0b00011:
        nextStateRobot = STATE_TOURNE_GAUCHE;
        break;
    case 0b10000:
    case 0b01000:
    case 0b11000:
        nextStateRobot = STATE_TOURNE_DROITE;
        break;
    case 0b00100:
        nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
        break;
    case 0b00101:
    case 0b00110:
    case 0b00111:
        nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
        break;
    case 0b10100:
    case 0b01100:
    case 0b11100:
        nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
        break;
    case 0b01001:
    case 0b01010:
    case 0b10001:
    case 0b10010:
        nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
        break;
    case 0b01110:
    case 0b10110:
    case 0b01111:
    case 0b11110:
        nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
        break;
    case 0b11111:
        nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
        break;
    case 0b10101:
    case 0b11101:
    case 0b10111:
    case 0b11011:
        nextStateRobot = STATE_ARRET; // RECULE ???
        break;
    default:
        nextStateRobot = STATE_ATTENTE;
        break;
    }
}
