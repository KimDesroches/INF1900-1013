/*
 * Nom: pb1.cpp
 * Description: À l'aide d'un bouton sur le breadboard, faire clignoter une del.
 * Équipe : 13
 * Auteurs : Kim Desroches et Kimia Foroudian
 
 Identifications matérielles (Broches I/O) :
    - La broche B0 est connectée à borne négative de la DEL bicolore en sortie.
    - La broche B1 est connectée à la borne positive de la DEL bicolore en sortie.
    - Le bouton sur breadboard est connecté à la broche D2 en entrée via le fil de donnée. 
    Ce bouton est en low enable : à 0 (bouton relaché), le courant passe
                                  à 1 (bouton appuyé), aucun courant ne passe
    Le cavalier IntEN est retiré de la carte mère.

Table d'états:
+---------------+------+------------+------------+
| Current State |  D2  | Next State | Output LED |  
+---------------+------+------------+------------+
| INITIAL       | 0    | BLINK      | OFF        |
| INITIAL       | 1    | INITIAL    | OFF        |
| BLINK         | 0    | BLINK      | OFF        |
| BLINK         | 1    | OFF        | ON         |
| OFF           | X    | INITIAL    | OFF        |
+---------------+------+------------+------------+


*/
#define F_CPU 8000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

const uint8_t MASK_BUTTON = (1 << PD2); 
const uint8_t LED_PIN_GREEN = (1 << PB0);
const uint8_t LED_PIN_RED = (1 << PB1);
const uint8_t LED_OUTPUT_MODE = LED_PIN_GREEN | LED_PIN_RED;
const uint8_t BUTTON_INPUT_MODE = (1 << PD2);
const uint8_t DEBOUNCE_DELAY = 30;

const uint64_t FREQUENCE_CPU = 8000000;
const uint16_t PRESCALER = 1024;
const uint8_t N_INCREMENTATIONS  = 10;
const uint16_t N_CYCLES = FREQUENCE_CPU/PRESCALER;
const uint16_t FREQUENCE = (N_CYCLES/N_INCREMENTATIONS);

const uint8_t MAX_COUNTER_VALUE = 120;
const uint16_t RED_LED_DELAY = 2000;
const uint16_t GREEN_LED_DELAY = 1000;
const uint16_t BLINKING_DELAY = 250;
const uint8_t MAX_CYCLE = 2;   

volatile bool timerDone = false;
volatile bool buttonReleased = true;
volatile uint8_t counter = 0;

enum class ledBehaviour {INITIAL, GREEN_BLINK, OFF};
ledBehaviour state = ledBehaviour::INITIAL;
enum class ledColor {GREEN, RED};

void turnOffLed(){
    PORTB &= ~(LED_PIN_GREEN| LED_PIN_RED);
}

void setColor(ledColor color){
    switch(color){
        case ledColor::GREEN:
            turnOffLed();
            PORTB |= LED_PIN_GREEN;
            break;
        case ledColor::RED:
            turnOffLed();
            PORTB |= LED_PIN_RED;
            break;
    }
}

void blinkingLed(ledColor color, uint8_t duration){
    for (uint8_t i = 0; i < duration; i++) {
        setColor(color);
        _delay_ms(BLINKING_DELAY);
        turnOffLed();
        _delay_ms(BLINKING_DELAY);
    }
}

ISR(INT0_vect){
    buttonReleased = (PIND & MASK_BUTTON);
    _delay_ms(DEBOUNCE_DELAY);
    buttonReleased = (PIND & MASK_BUTTON);
    EIFR |= (1 << INTF0);
}

ISR(TIMER1_COMPA_vect){
    timerDone = true;
    counter++;
}

void startTimer(uint16_t time){
    timerDone = false;
    TCNT1 = 0;
    OCR1A = time;
    TCCR1A = 0;
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A);
}

void initialisation(){
    cli();
    DDRB |= LED_OUTPUT_MODE;
    DDRD &= ~BUTTON_INPUT_MODE;
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
    sei();
}

void executeState(){
    switch(state){
        case ledBehaviour::INITIAL:
            counter = 0;
            if(!buttonReleased){
                startTimer(FREQUENCE);
                state = ledBehaviour::GREEN_BLINK;
            }
            break;
        case ledBehaviour::GREEN_BLINK:
            if(buttonReleased || counter == MAX_COUNTER_VALUE){
                cli();
                blinkingLed(ledColor::GREEN, MAX_CYCLE);
                _delay_ms(RED_LED_DELAY);
                setColor(ledColor::RED);
                blinkingLed(ledColor::RED, (counter/2));
                setColor(ledColor::GREEN);
                state = ledBehaviour::OFF;
            }
            break;
        case ledBehaviour::OFF:
            _delay_ms(GREEN_LED_DELAY);
            turnOffLed();
            state = ledBehaviour::INITIAL;
            sei();
            buttonReleased = true;
            break;
    }
}

int main(){
    initialisation();
    while(true){
        executeState();
    }
}