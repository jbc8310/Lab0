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

#define ENABLE 1
#define OFF 0
#define OUTPUT 0
#define INPUT 1
#define LED1 LATDbits.LATD0
#define LED2 LATDbits.LATD1
#define LED3 LATDbits.LATD2
#define PRESSED 0
#define RELEASED 1
#define BUTTON PORTDbits.RD6

//TODO: Define states of the state machine
typedef enum stateTypeEnum{        //creating a variable for leds
    led1, led2, led3, Press, Release
} stateType;

//TODO: Use volatile variables that change within interrupts
volatile stateType state = led1;
volatile stateType prevState = led1;;

int flag1Second = 0;

int main() {
    SYSTEMConfigPerformance(10000000);    //Configures low-level system parameters for 10 MHz clock
    enableInterrupts();                   //This function is necessary to use interrupts.

    //TODO: Write each initialization function
    initLEDs();
    initTimer1();
    initSwitch();
    
    while(1){

        //TODO: Implement a state machine to create the desired functionality
        
                    
                    switch(state){          //then lights up the led depending on current state
                        case led1:
                            LED1 = ENABLE;
                            LED2 = OFF;
                            LED3 = OFF;
                            prevState = led1;
                            break;
                            
                        case led2:
                            LED1 = OFF;
                            LED2 = ENABLE;
                            LED3 = OFF;
                            prevState = led2;
                            break;
                        
                        case led3:
                            LED1 = OFF;
                            LED2 = OFF;
                            LED3 = ENABLE;
                            prevState = led3;
                            break;
                            
                        case Press:
                            T1CONbits.ON = 1;       //turn on timer
                            break;
                        
                        case Release:
                            if(prevState == led1 && flag1Second == 0){
                                state = led2;
                            }
                            else if(prevState == led1 && flag1Second == 1){
                                state = led3;
                            }
                            else if(prevState == led2 && flag1Second == 0){
                                state = led3;
                            }
                            else if(prevState == led2 && flag1Second == 1){
                                state = led1;
                            } 
                            else if(prevState == led3 && flag1Second == 0){
                                state = led1;
                            }
                            else if(prevState == led3 && flag1Second == 1){
                                state = led2;
                            }
                            flag1Second = 0;
                            break;
                            
                        /*default:
                            LED1 = ENABLE;
                            LED2 = ENABLE;
                            LED3 = ENABLE;
                            prevState = led1;
                            state = led1;
                            flag1Second = 0;
                            break;*/
                            
                            
                            
                    } //switch state
                    
                }    
                
               
           //while
    
    return 0;
}

//TODO: Add interrupt service routines that manage the change of states
//for particular events as needed

void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1interrupt(){
    IFS0bits.T1IF = 0;      //pulls down interrupt flag
    
    flag1Second = 1;
    
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNINterrupt(){
    IFS1bits.CNDIF = OFF;   //puts the interrupt flag down
    PORTD;
    //BUTTON = INPUT;      //turns switch into an input
    if(BUTTON == PRESSED){
        state = Press;
    }
    else if(BUTTON == RELEASED){
        state = Release;
    }
    
}