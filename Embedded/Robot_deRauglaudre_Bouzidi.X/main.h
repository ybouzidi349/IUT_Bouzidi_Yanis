
#ifndef MAIN_H
#define	MAIN_H

void OperatingSystemLoop(void);
void SetNextRobotStateInAutomaticMode(void);
void Infrarouge_Conversion(void);
void Operating(int binary);
int BinaryCapteur(float capteur);
int StateBinary(void);

#define FCY 60000000
#define FREQUENCE_TIMER_1 50 //la frequence timer 1 en Hz
#define FREQUENCE_TIMER_4 1000 // la frequence timer 4
#define VITESSE_ROBOT 25
#define VITESSE_T 15

#define DISTANCE_LIM 30



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

#endif

