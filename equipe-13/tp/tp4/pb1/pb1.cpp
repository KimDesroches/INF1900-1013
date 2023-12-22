/*
 * Nom: pb1.cpp
 * Description:
 * Équipe : 13
 * Auteurs : Kim Desroches et Kimia Foroudian
 
 Identification matérielles (Broches I/O) :
    - La broche A0 est connectée à borne négative de la DEL bicolore
    - La broche A1 est connectée à la borne positive de la DEL bicolore
    - Le bouton est connecté à la broche D2 en entrée.

*/

#include <avr/interrupt.h>
#include <avr/io.h>

#define F_CPU 8000000UL
#include <util/delay.h>

const uint8_t MASK_INTERRUPTOR = (1 << PD2); 
const uint8_t DEBOUNCE_DELAY = 30;
const uint8_t RED_DELAY = 1;
const uint8_t GREEN_DELAY = 5;
const uint8_t BUTTON_INPUT_MODE = (1 << PD2);
const uint8_t LED_PIN_GREEN = (1 << PA0);
const uint8_t LED_PIN_RED = (1 << PA1);
const uint8_t LED_OUTPUT_MODE = LED_PIN_GREEN | LED_PIN_RED;

enum class ledColor {INITIAL_RED, AMBER, GREEN, RED, OFF, GREEN2};
ledColor state = ledColor::INITIAL_RED;

volatile bool buttonPressed = false;

void turnOffLed(){
    PORTA &= ~(LED_PIN_GREEN| LED_PIN_RED);
}

void turnOnLedRed(){
    turnOffLed();
    PORTA |= LED_PIN_RED;
}

void turnOnLedGreen(){
    turnOffLed();
    PORTA |= LED_PIN_GREEN;
}

void turnOnLedAmber(){
    turnOnLedRed();
    _delay_ms(RED_DELAY);
    turnOnLedGreen();
    _delay_ms(GREEN_DELAY);
}

void executeState(){
    switch(state){
        case ledColor::INITIAL_RED:
            turnOnLedRed();
            break;
        case ledColor::AMBER:
            turnOnLedAmber();
            break;
        case ledColor::GREEN:
            turnOnLedGreen();
            break;
        case ledColor::RED:
            turnOnLedRed();
            break;
        case ledColor::OFF:
            turnOffLed();
            break;
        case ledColor::GREEN2:
            turnOnLedGreen();
            break;
    }
}

void updateState(){
    switch(state){
        case ledColor::INITIAL_RED:
            state = ledColor::AMBER;
            break;
        case ledColor::AMBER:
            state = ledColor::GREEN;   
            break;    
        case ledColor::GREEN:
            state = ledColor::RED;
            break;
        case ledColor::RED:
            state = ledColor::OFF;
            break;
        case ledColor::OFF:
            state = ledColor::GREEN2;
            break;
        case ledColor::GREEN2:
            state = ledColor::INITIAL_RED;
            break;
    }
}

ISR(INT0_vect) {
    _delay_ms(DEBOUNCE_DELAY);
    buttonPressed = true;
    updateState();
    EIFR |= (1 << INTF0);
}

void initialisation(){
    cli();
    DDRA |= LED_OUTPUT_MODE;
    DDRD &= ~BUTTON_INPUT_MODE;
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
    sei();
}

int main(){
    initialisation();
    executeState();
    while(true){ 
        if(buttonPressed){
           executeState(); 
        }
    }
}