#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#include "ChipConfig.h"
#include "IO.h"

int main (void){

//Initialisation oscillateur

InitOscillator();

// Configuration des input et output (IO)

InitIO();
LED_BLANCHE_1 = 1;
LED_BLEUE_1 = 1;
LED_ORANGE_1 = 1;
LED_ROUGE_1 = 1;
LED_VERTE_1 = 1;


while(1)
{
}


}