/*
 * Nom: pb2.cpp
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

const uint8_t BUTTON_INPUT_MODE = (1 << PD2);
const uint8_t LED_PIN_GREEN = (1 << PA0);
const uint8_t LED_PIN_RED = (1 << PA1);
const uint8_t LED_OUTPUT_MODE = LED_PIN_GREEN | LED_PIN_RED;
const uint8_t DEBOUNCE_DELAY = 30;
const uint16_t START_DELAY = 10000; //CHANGE TO 10 seconds

volatile uint8_t timerDone;
volatile uint8_t buttonPressed;


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

void blinkingLed(){
    _delay_ms(START_DELAY);
     const uint16_t DELAY_FLASH = 100;
    for(int dutyCycle = 0; dutyCycle < 2; dutyCycle++){
        turnOnLedRed();
        _delay_ms(DELAY_FLASH);
        turnOffLed();
        _delay_ms(DELAY_FLASH);
   }
   buttonPressed = 0;
}

ISR(INT0_vect){
    _delay_ms(DEBOUNCE_DELAY);
    buttonPressed = 1;
    EIFR |= (1 << INTF0);
}

ISR(TIMER1_COMPA_vect){
    timerDone = 1;
}

void startTimer(uint16_t time){
    timerDone = 0;
    TCNT1 = 0;
    OCR1A = time;
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A);
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
    blinkingLed();
    startTimer(7812.5);
    
    do{  
    } while(timerDone == 0 && buttonPressed == 0);
    
    cli ();

    if(buttonPressed == 1){
        turnOnLedGreen();
    }
    else{
        turnOnLedRed();
    }
}