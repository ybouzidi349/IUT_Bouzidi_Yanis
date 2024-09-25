
#ifndef MAIN_H
#define	MAIN_H

void OperatingSystemLoop(void);
void SetNextRobotStateInAutomaticMode(void);
void Infrarouge_Conversion(void);
char Operating(unsigned char binary)
unsigned char BinaryCapteur(float capteur, int val)
unsigned char StateBinary(void)

#define FCY 60000000

 /////////////////////MODIF/////////////////////
 
#define FREQUENCE_TIMER_1 50
#define FREQUENCE_TIMER_4 1000

#define VITESSE_ROBOT 28
#define VITESSE_T 13
#define VITESSE_VIRAGE 13

#define DISTANCE_LIM 33
#define DISTANCE_LIM_CENTRE 38
#define DISTANCE_LIM_EXT 14

 //////////////////////////////////////////

#define STATE_ATTENTE 0
#define STATE_ATTENTE_EN_COURS 1
#define STATE_AVANCE 2
#define STATE_AVANCE_EN_COURS 3
#define STATE_TOURNE_GAUCHE 4
#define STATE_TOURNE_GAUCHE_EN_COURS 5
#define STATE_TOURNE_DROITE 6
#define STATE_TOURNE_DROITE_EN_COURS 7
#define STATE_TOURNE_SUR_PLACE_GAUCHE 8
#define STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS 9
#define STATE_TOURNE_SUR_PLACE_DROITE 10
#define STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS 11
#define STATE_ARRET 12
#define STATE_ARRET_EN_COURS 13
#define STATE_RECULE 14
#define STATE_RECULE_EN_COURS 15
#define STATE_NULL 16

#endif

