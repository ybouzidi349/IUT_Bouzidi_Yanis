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

unsigned char stateRobot = STATE_NULL;
unsigned char nextStateRobot = STATE_NULL;

int main(void) {

    InitOscillator();
    InitIO();
    InitTimer1();
    InitTimer4();
    InitTimer23();
    InitPWM();

    InitADC1();

    while (1) {
        
        if (BP1 != 0)
            stateRobot = STATE_ATTENTE;

        if ((robotState.distanceTelemetreExtGauche) < DISTANCE_LIM)
            LED_BLANCHE_1 = 1;
        else
            LED_BLANCHE_1 = 0;
        if ((robotState.distanceTelemetreGauche) < DISTANCE_LIM)
            LED_BLEUE_1 = 1;
        else
            LED_BLEUE_1 = 0;
        if ((robotState.distanceTelemetreCentre) < DISTANCE_LIM)
            LED_ORANGE_1 = 1;
        else
            LED_ORANGE_1 = 0;
        if ((robotState.distanceTelemetreDroit) < DISTANCE_LIM)
            LED_ROUGE_1 = 1;
        else
            LED_ROUGE_1 = 0;
        if ((robotState.distanceTelemetreExtDroit) < DISTANCE_LIM)
            LED_VERTE_1 = 1;
        else
            LED_VERTE_1 = 0;

        if (stateRobot == STATE_AVANCE || stateRobot == STATE_AVANCE_EN_COURS) {
            LED_VERTE_2 = 1;
            LED_ROUGE_2 = 1;
            LED_ORANGE_2 = 1;
            LED_BLEUE_2 = 1;
            LED_BLANCHE_2 = 1;
        } else {
            LED_VERTE_2 = 0;
            LED_ROUGE_2 = 0;
            LED_ORANGE_2 = 0;
            LED_BLEUE_2 = 0;
            LED_BLANCHE_2 = 0;
        }
    }
}

int BinaryCapteur(float capteur, int val) {
    if (capteur < val)
        return (1);
    else
        return (0);
}

int StateBinary(void) {
    return (BinaryCapteur(robotState.distanceTelemetreExtGauche, DISTANCE_LIM_EXT) << 4 |
            BinaryCapteur(robotState.distanceTelemetreGauche, DISTANCE_LIM) << 3 |
            BinaryCapteur(robotState.distanceTelemetreCentre, DISTANCE_LIM_CENTRE) << 2 |
            BinaryCapteur(robotState.distanceTelemetreDroit, DISTANCE_LIM) << 1 |
            BinaryCapteur(robotState.distanceTelemetreExtDroit, DISTANCE_LIM_EXT));
}

void Infrarouge_Conversion() {

    if (ADCIsConversionFinished() == 1) {
        ADCClearConversionFinishedFlag();
        unsigned int *result = ADCGetResult();
        float volts = ((float) result[0]) * 3.3 / 4096;
        robotState.distanceTelemetreExtGauche = 34 / volts - 5;
        volts = ((float) result[1]) * 3.3 / 4096;
        robotState.distanceTelemetreGauche = 34 / volts - 5;
        volts = ((float) result[2]) * 3.3 / 4096;
        robotState.distanceTelemetreCentre = 34 / volts - 5;
        volts = ((float) result[3]) * 3.3 / 4096;
        robotState.distanceTelemetreDroit = 34 / volts - 5;
        volts = ((float) result[4]) * 3.3 / 4096;
        robotState.distanceTelemetreExtDroit = 34 / volts - 5;
    }
}

void OperatingSystemLoop(void) {
    switch (stateRobot) {
        case STATE_NULL:
            PWMSetSpeedConsigne(0, MOTEUR_DROIT);
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
            break;
        case STATE_ATTENTE:
            timestamp = 0;
            PWMSetSpeedConsigne(0, MOTEUR_DROIT);
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
            stateRobot = STATE_ATTENTE_EN_COURS;
            break;
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
            PWMSetSpeedConsigne(VITESSE_VIRAGE, MOTEUR_DROIT);
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_GAUCHE_EN_COURS;
            break;
        case STATE_TOURNE_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        case STATE_TOURNE_DROITE:
            PWMSetSpeedConsigne(0, MOTEUR_DROIT);
            PWMSetSpeedConsigne(VITESSE_VIRAGE, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_DROITE_EN_COURS;
            break;
        case STATE_TOURNE_DROITE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        case STATE_TOURNE_SUR_PLACE_GAUCHE:
            PWMSetSpeedConsigne(VITESSE_T, MOTEUR_DROIT);
            PWMSetSpeedConsigne(-VITESSE_T, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS;
            break;
        case STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;
        case STATE_TOURNE_SUR_PLACE_DROITE:
            PWMSetSpeedConsigne(-VITESSE_T, MOTEUR_DROIT);
            PWMSetSpeedConsigne(VITESSE_T, MOTEUR_GAUCHE);
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
    Operating(StateBinary());

    if (nextStateRobot != stateRobot - 1)
        stateRobot = nextStateRobot;
}

void Operating(int binary) {
    switch (binary) {
        case 0b00000:
            nextStateRobot = STATE_AVANCE;
            break;

        case 0b00001:
            nextStateRobot = STATE_TOURNE_GAUCHE;
            break;

        case 0b00010:
            nextStateRobot = STATE_TOURNE_GAUCHE;
            break;

        case 0b00011:
            nextStateRobot = STATE_TOURNE_GAUCHE;
            break;

        case 0b00100:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;

        case 0b00101:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;

        case 0b00110:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;

        case 0b00111:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;

        case 0b01000:
            nextStateRobot = STATE_TOURNE_DROITE;
            break;

        case 0b01001:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;

        case 0b01010:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;

        case 0b01011:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;

        case 0b01100:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;

        case 0b01101:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;

        case 0b01110:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;

        case 0b01111:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;

        case 0b10000:
            nextStateRobot = STATE_TOURNE_DROITE;
            break;

        case 0b10001:
            nextStateRobot = STATE_AVANCE;
            break;

        case 0b10010:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;

        case 0b10011:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;

        case 0b10100:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;

        case 0b10101:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;

        case 0b10110:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;

        case 0b10111:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;

        case 0b11000:
            nextStateRobot = STATE_TOURNE_DROITE;
            break;

        case 0b11001:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;

        case 0b11010:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;

        case 0b11011:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;

        case 0b11100:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;

        case 0b11101:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;

        case 0b11110:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_DROITE;
            break;

        case 0b11111:
            nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;
            break;

        default:
            nextStateRobot = STATE_ATTENTE;
            break;
    }
}
