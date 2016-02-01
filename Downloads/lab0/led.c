/* 
 * File:   led.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:15 PM
 */

#include <xc.h>
#include "led.h"

#define ON 1
#define OUTPUT 0

void initLEDs(){
    
    //TODO: Initialize LEDs
    
    LATDbits.LATD0 = ON;
    TRISDbits.TRISD0 = OUTPUT;
    
    LATDbits.LATD1 = ON;
    TRISDbits.TRISD1 = OUTPUT;
    
    LATDbits.LATD2 = ON;
    TRISDbits.TRISD2 = OUTPUT;
    
    
}

void turnOnLED(int led){
    
    //TODO: You may choose to write this function
    // as a matter of convenience
    
}