#define F_CPU 8000000UL
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "navigation.h"
#include "led.h"
#include "debug.h"
#include "button.h"
#include "Timer.h"
#define DEBUG
const uint8_t DEBOUNCE_DELAY = 30;
const uint8_t SPEED_ROBOT_75 = 75;
const uint16_t DELAY_STOP = 5000;
const uint8_t DURATION_TIMER = 3;
const uint16_t PRESCALER = 1024;
volatile bool isButtonPressed = false;
volatile bool isTimerExpired = false;

ISR (INT0_vect) 
{    
    _delay_ms(DEBOUNCE_DELAY);
    if(isButtonPressed){        
        isButtonPressed = false;
    }        
    else{
        isButtonPressed = true;
    }             
    EIFR |= (1 << INTF0) ;
}

ISR ( TIMER1_COMPA_vect )
{
    isTimerExpired = true;        
}

int main(){
    //DEBUG
    RS232::initialise();
    DEBUG_TRANSMIT(("button"));    
    
    Button myButton(&DDRD, InteruptSensControl::ANY_EDGE);
    
    //NAVIGATION
    Navigation nav;
    nav.foward(SPEED_ROBOT_75,SPEED_ROBOT_75);
    delayMs(DELAY_STOP);
    nav.stop();
    nav.reverse(SPEED_ROBOT_75,SPEED_ROBOT_75);
    delayMs(DELAY_STOP);
    nav.stop();

    Led myLed(&PORTA, &DDRA, PA0, PA1);
    Timer timer(DURATION_TIMER, PRESCALER, F_CPU);    
    
    timer.startTimer(isTimerExpired);
    while(true){
        if(isTimerExpired){     
            myLed.controlColor(Led::ledColor::GREEN); 
            isTimerExpired = false;                       
        }            
    }
    
    return 0;
}