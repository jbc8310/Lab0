/* 
 * File:   main.c
 * Author: gvanhoy
 * Description: lab 0.
 * Created on August 27, 2015, 10:14 AM
 */

#include <xc.h>
#include <sys/attribs.h>
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"
#include "switch.h"

#define ON 1
#define OFF 0
#define OUTPUT 0
#define INPUT 1
#define LED1 LATDbits.LATD0
#define LED2 LATDbits.LATD1
#define LED3 LATDbits.LATD2

//TODO: Define states of the state machine
typedef enum stateTypeEnum{        //creating a variable for leds
    led1, led2, led3
} stateType;

//TODO: Use volatile variables that change within interrupts
volatile int state = led1;

int main() {
    SYSTEMConfigPerformance(10000000);    //Configures low-level system parameters for 10 MHz clock
    enableInterrupts();                   //This function is necessary to use interrupts.

    //TODO: Write each initialization function
    initLEDs();
    initTimer1();
    initSwitch();
    
    while(1){

        //TODO: Implement a state machine to create the desired functionality
        switch (state){
            case led1: 
                LED1 = ON;
                LED2 = OFF;
                LED3 = OFF;
                break;
                
            case led2:
                LED1 = OFF;
                LED2 = ON;
                LED3 = OFF;
                break;
                
            case led3:
                LED1 = OFF;
                LED2 = OFF;
                LED3 = ON;
                break;
                
            default:
                LED1 = ON;
                LED2 = ON;
                LED3 = ON;
                break;

        }
    }
    
    return 0;
}

//TODO: Add interrupt service routines that manage the change of states
//for particular events as needed

void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1interrupt(){
    IFS0bits.T1IF = 0;      //pulls down interrupt flag
    if(state == led1) state = led2;
    else if(state == led2) state = led3;
    else if(state == led3) state = led1;
    
    
}