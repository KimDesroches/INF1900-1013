/*
 * Nom: pb2.cpp
 * Description: Changement de couleur d'une del selon la lumière (photorésistance)
 * Équipe : 13
 * Auteurs : Kim Desroches et Kimia Foroudian
 
 Identification matérielles (Broches I/O) :
    - La broche B0 est connectée à borne négative de la DEL bicolore en sortie.
    - La broche B1 est connectée à la borne positive de la DEL bicolore en sortie.
    - La broche A0 est connectée avec le fil de données du câble (breadboard) en entrée (lecture).

*/
#define F_CPU 8000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "can.h"

const uint8_t RED_DELAY = 1;
const uint8_t GREEN_DELAY = 5;
const uint8_t LED_PIN_GREEN = (1 << PB0);
const uint8_t LED_PIN_RED = (1 << PB1);
const uint8_t LED_OUTPUT_MODE = LED_PIN_GREEN | LED_PIN_RED;
const uint8_t CONVERTER_INPUT_MODE = (1 << PA0);
const uint8_t MIN_AMBIANT_LIGHT = 200;
const uint8_t MAX_AMBIANT_LIGHT  = 235;

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

void turnOnLedAmber(){
    setColor(ledColor::RED);
    _delay_ms(RED_DELAY);
    setColor(ledColor::GREEN);
    _delay_ms(GREEN_DELAY);
}

void initialisation(){
    DDRA &= ~CONVERTER_INPUT_MODE;
    DDRB |= LED_OUTPUT_MODE;

}

void adaptLedColor(uint8_t adcVal){
        if(adcVal <= MIN_AMBIANT_LIGHT){
            setColor(ledColor::GREEN);
        }
        else if (adcVal > MIN_AMBIANT_LIGHT && adcVal < MAX_AMBIANT_LIGHT){
            turnOnLedAmber();
        }
        else{
            setColor(ledColor::RED);
        }
}

int main(){
    initialisation();
    can converter;
    uint8_t adcVal;

    while(true){
        adcVal = (converter.lecture(0) >> 2);
        adaptLedColor(adcVal);
    }   
}