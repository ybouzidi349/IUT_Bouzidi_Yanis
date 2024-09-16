#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "IO.h"
#include "timer.h"
#include "Toolbox.h"
#include "PWM.h"

int main(void) {


    InitOscillator();
    InitTimer1();
    InitTimer23();

    InitIO();
    
    LED_BLANCHE_1= 1;
    LED_ORANGE_1 = 1;
    LED_BLEUE_1 = 1;
    LED_ROUGE_1 = 1;
    LED_VERTE_1 = 1;
    LED_BLANCHE_2 = 1;
    LED_BLEUE_2 = 1;
    LED_ORANGE_2 = 1;
    LED_ROUGE_2 = 1;
    LED_VERTE_2 = 1;

    InitPWM();
    //PWMSetSpeedConsigne(50, MOTEUR_GAUCHE);
    //PWMSetSpeedConsigne(50, MOTEUR_DROIT);


    while (1) {
        
    }
}

