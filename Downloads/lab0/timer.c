/* 
 * File:   timer.c
 * Author: gvanhoy
 *
 * Created on August 27, 2015, 3:26 PM
 */

#include <xc.h>
#define PRESCALAR_256 3

void initTimer1(){
    //TODO: Initialize Timer 1 to have a period of
    // 1 second. Enable its interrupt
    
    TMR1 = 0;   //incrementer
    T1CONbits.TCKPS = PRESCALAR_256;    //configures ticking rate
    PR1 = 39061;    //period register to compare based off of the calculations
    T1CONbits.ON = 0;       //turn on timer
    IEC0bits.T1IE = 1;      //enable interrupt
    IPC1bits.T1IP = 7;      //default timer priority
    IFS0bits.T1IF = 0;      //puts down flag
    
}