/*
 * Nom: pb1.cpp
 * Description:
 * Équipe : 13
 * Auteurs : Kim Desroches et Kimia Foroudian
 
 Identification matérielles (Broches I/O) :
    - La broche A0 est connectée à borne négative de la DEL bicolore
    - La broche A1 est connectée à la borne positive de la DEL bicolore

*/
#include <avr/io.h>

#define F_CPU 8000000UL
#include <util/delay.h>

const uint8_t BUTTON_INPUT_MODE = (1 << PD2);
const uint8_t LED_PIN_GREEN = (1 << PA0);
const uint8_t LED_PIN_RED = (1 << PA1);
const uint16_t DELAY_B = 6000;
const uint8_t LED_OUTPUT_MODE = (LED_PIN_GREEN | LED_PIN_RED);

void turnOffLed(){
    PORTA &= ~(LED_PIN_GREEN | LED_PIN_RED);
}

void turnOnLedRed() {
    turnOffLed();
    PORTA |= LED_PIN_RED;
}

void turnOnLedGreen() {
    turnOffLed();
    PORTA |= LED_PIN_GREEN;
}

void delayLedRed(){
    uint16_t DELAY_A = 6000;
    for(int dutyCycle = 0; dutyCycle < 1000; dutyCycle++){
        turnOnLedRed();
        _delay_loop_2(DELAY_A);
        turnOffLed();
        _delay_loop_2(DELAY_B-DELAY_A);
        DELAY_A -= 6; 
   }
}   
    
void delayLedGreen(){
    uint16_t DELAY_A = 6000;
    for(int dutyCycle = 0; dutyCycle < 1000; dutyCycle++){
        turnOnLedGreen();
        _delay_loop_2(DELAY_A);
        turnOffLed();
        _delay_loop_2(DELAY_B-DELAY_A);
        DELAY_A -= 6; 
   }
}   

int main(){
    DDRA |= LED_OUTPUT_MODE;
    
    while(true){
        delayLedRed();
        delayLedGreen();         
    }
    
}