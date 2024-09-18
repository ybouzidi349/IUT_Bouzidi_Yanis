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

    LED_BLANCHE_1 = 1;
    LED_ORANGE_1 = 1;
    LED_BLEUE_1 = 1;
    LED_ROUGE_1 = 1;
    LED_VERTE_1 = 1;
    LED_BLANCHE_2 = 1;
    LED_BLEUE_2 = 1;
    LED_ORANGE_2 = 1;
    LED_ROUGE_2 = 1;
    LED_VERTE_2 = 1;

    //PWMSetSpeedConsigne(20, MOTEUR_GAUCHE);
    //PWMSetSpeedConsigne(20, MOTEUR_DROIT);

    while (1) {
    }
}

unsigned char stateRobot;

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
            PWMSetSpeedConsigne(VITESSE_ROBOT, MOTEUR_DROIT);
            PWMSetSpeedConsigne(VITESSE_ROBOT, MOTEUR_GAUCHE);
            stateRobot = STATE_AVANCE_EN_COURS;
            break;
        case STATE_AVANCE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        case STATE_TOURNE_GAUCHE:
            PWMSetSpeedConsigne(VITESSE_ROBOT, MOTEUR_DROIT);
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_GAUCHE_EN_COURS;
            break;
        case STATE_TOURNE_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        case STATE_TOURNE_DROITE:
            PWMSetSpeedConsigne(0, MOTEUR_DROIT);
            PWMSetSpeedConsigne(VITESSE_ROBOT, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_DROITE_EN_COURS;
            break;
        case STATE_TOURNE_DROITE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        case STATE_TOURNE_SUR_PLACE_GAUCHE:
            PWMSetSpeedConsigne(VITESSE_VIRAGE, MOTEUR_DROIT);
            PWMSetSpeedConsigne(-VITESSE_VIRAGE, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS;
            break;
        case STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        case STATE_TOURNE_SUR_PLACE_DROITE:
            PWMSetSpeedConsigne(-VITESSE_VIRAGE, MOTEUR_DROIT);
            PWMSetSpeedConsigne(VITESSE_VIRAGE, MOTEUR_GAUCHE);
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
unsigned char nextStateRobot = 0;

void SetNextRobotStateInAutomaticMode() {

    unsigned char positionObstacle = PAS_D_OBSTACLE;

    //ÈDtermination de la position des obstacles en fonction des ÈÈËtlmtres

    if (robotState.distanceTelemetreDroit < 30 &&
            robotState.distanceTelemetreCentre > 20 &&
            robotState.distanceTelemetreGauche > 30) //Obstacle ‡droite
        positionObstacle = OBSTACLE_A_DROITE;
    else if (robotState.distanceTelemetreDroit > 30 &&
            robotState.distanceTelemetreCentre > 20 &&
            robotState.distanceTelemetreGauche < 30) //Obstacle ‡gauche
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


