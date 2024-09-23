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

void Operating(int test);
int BinaryCapteur(float capteur);
int StateBinary(void);

unsigned char stateRobot;
unsigned char nextStateRobot = 0;

int main(void) {

    InitOscillator();
    InitIO();
    InitTimer1();
    InitTimer4();
    InitTimer23();
    InitPWM();

    InitADC1();

    while (1) {
    }
}

int BinaryCapteur(float capteur) {
    if (capteur < DISTANCE_LIM)
        return (1); // 1 : Presence d'obstacle
    else
        return (0);
}

int StateBinary(void) {
    int n;
    n = BinaryCapteur(robotState.distanceTelemetreExtGauche) * 10000;
    n += BinaryCapteur(robotState.distanceTelemetreGauche) * 1000;
    n += BinaryCapteur(robotState.distanceTelemetreCentre) * 100;
    n += BinaryCapteur(robotState.distanceTelemetreDroit) * 10;
    n += BinaryCapteur(robotState.distanceTelemetreExtDroit);
    return (n);
}

void Infrarouge_Conversion() {

    if (ADCIsConversionFinished() == 1) {
        ADCClearConversionFinishedFlag();
        unsigned int * result = ADCGetResult();
        float volts = ((float) result [0])* 3.3 / 4096;
        robotState.distanceTelemetreExtGauche = 34 / volts - 5;
        volts = ((float) result [1])* 3.3 / 4096;
        robotState.distanceTelemetreGauche = 34 / volts - 5;
        volts = ((float) result [2])* 3.3 / 4096;
        robotState.distanceTelemetreCentre = 34 / volts - 5;
        volts = ((float) result [3])* 3.3 / 4096;
        robotState.distanceTelemetreDroit = 34 / volts - 5;
        volts = ((float) result [4])* 3.3 / 4096;
        robotState.distanceTelemetreExtDroit = 34 / volts - 5;
    }
}

void OperatingSystemLoop(void) {
    switch (stateRobot) {
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


void SetNextRobotStateInAutomaticMode() {
    unsigned char positionObstacle = PAS_D_OBSTACLE;
    
    Operating(StateBinary());

    if (nextStateRobot != stateRobot - 1)
        stateRobot = nextStateRobot;

}

void Operating(int test) {
    switch (test) {
        case 00000:
            nextStateRobot = STATE_AVANCE;
            break;
        case 00001:
            nextStateRobot = STATE_TOURNE_GAUCHE;
            break;
        case 00010:
            nextStateRobot = STATE_TOURNE_GAUCHE;
            break;
        case 00011:
            nextStateRobot = STATE_TOURNE_GAUCHE;
            break;
        case 00100:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 00101:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 00110:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 00111:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;
        case 01000:
            nextStateRobot = STATE_TOURNE_DROITE;
            break;
        case 01001:
            break;
        case 01010:
            break;
        case 01011:
            break;
        case 01100:
            break;
        case 01101:
            break;
        case 01111:
            break;
        case 10000:
            break;
        case 10001:
            break;
        case 10010:
            break;
        case 10011:
            break;
        case 10100:
            break;
        case 10101:
            break;
        case 10111:
            break;
        case 11000:
            break;
        case 11001:
            break;
        case 11010:
            break;
        case 11011:
            break;
        case 11100:
            break;
        case 11101:
            break;
        case 11110:
            break;
        case 11111:
            break;

    }
}
