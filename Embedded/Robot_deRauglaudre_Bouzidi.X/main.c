#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
//#include "timer.h"
//#include "Toolbox.h"
//#include "PWM.h"

int main(void) {

    //Initialisation oscillateur

    InitOscillator();


    //InitTimer1();
    //InitTimer23();
   // InitPWM();
    //PWMSetSpeed(10, MOTEUR_DROIT);
   // PWMSetSpeed(-10, MOTEUR_GAUCHE);
    
    

    // Configuration des input et output (IO)
    InitIO();

    LED_BLEUE_1 = 1;
    LED_ROUGE_1 = 1;
    LED_VERTE_1 = 1;
    LED_BLANCHE_2 = 1;
    LED_BLEUE_2 = 1;
    LED_ORANGE_2 = 1;
    LED_ROUGE_2 = 1;
    LED_VERTE_2 = 1;


    // Boucle Principale

    while (1) {
        //LED_BLANCHE_1 = !LED_BLANCHE_1;
    } // fin main
}

