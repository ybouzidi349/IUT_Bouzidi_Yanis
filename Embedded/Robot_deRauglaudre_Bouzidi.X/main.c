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

unsigned char stateRobot;

int BinaryCapteur(float capteur) {
    if (capteur < DISTANCE_LIM)
        return (1); // 1 : Presence d'obstacle
    else
        return (0);
}

void StateBinary(void) {
    int n;
    n = BinaryCapteur(robotState.distanceTelemetreExtGauche) * 10000;
    n += BinaryCapteur(robotState.distanceTelemetreGauche) * 1000;
    n += BinaryCapteur(robotState.distanceTelemetreCentre) * 100;
    n += BinaryCapteur(robotState.distanceTelemetreDroit) * 10;
    n += BinaryCapteur(robotState.distanceTelemetreExtDroit);
    return (n);
}

void OperatingSystemLoop(void) {
    switch (stateRobot) {
        case 00000:
            break;
        case 00001:
            break;
        case 00010:
            break;
        case 00011:
            break;
        case 00100:
            break;
        case 00101:
            break;
        case 00110:
            break;
        case 00111:
            break;
            
        case 01000:
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
        case 00000:
            break;
        case 00000:
            break;
        case 00000:
            break;
        case 00000:
            break;


    }
}
unsigned char nextStateRobot = 0;

void SetNextRobotStateInAutomaticMode() {

    unsigned char positionObstacle = PAS_D_OBSTACLE;

    //éDtermination de la position des obstacles en fonction des ééètlmtres

    if (robotState.distanceTelemetreDroit < 30 &&
            robotState.distanceTelemetreCentre > 20 &&
            robotState.distanceTelemetreGauche > 30) //Obstacle àdroite
        positionObstacle = OBSTACLE_A_DROITE;
    else if (robotState.distanceTelemetreDroit > 30 &&
            robotState.distanceTelemetreCentre > 20 &&
            robotState.distanceTelemetreGauche < 30) //Obstacle àgauche
        positionObstacle = OBSTACLE_A_GAUCHE;
    else if (robotState.distanceTelemetreCentre < 20) //Obstacle en face
        positionObstacle = OBSTACLE_EN_FACE;
    else if (robotState.distanceTelemetreDroit > 30 &&
            robotState.distanceTelemetreCentre > 20 &&
            robotState.distanceTelemetreGauche > 30) //pas d?obstacle
        positionObstacle = PAS_D_OBSTACLE;



    if (positionObstacle == PAS_D_OBSTACLE)
        nextStateRobot = STATE_AVANCE;
    else if (positionObstacle == OBSTACLE_A_DROITE)
        nextStateRobot = STATE_TOURNE_GAUCHE;
    else if (positionObstacle == OBSTACLE_A_GAUCHE)
        nextStateRobot = STATE_TOURNE_DROITE;
    else if (positionObstacle == OBSTACLE_EN_FACE)
        nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;

    if (nextStateRobot != stateRobot - 1)
        stateRobot = nextStateRobot;
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


