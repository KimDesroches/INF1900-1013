/*
 * Nom: pb1.cpp
 * Description: Allumer la led en vert après 3 appuis du bouton
 * Équipe : 13
 * Auteurs : Kim Desroches et Kimia Foroudian
 
 Identification matérielles (Broches I/O) :
    - La broche A0 est connectée à borne négative de la DEL bicolore
    - La broche A1 est connectée à la borne positive de la DEL bicolore
    - Le bouton est connecté à la broche D2 en entrée.

Table des états:
+---------------+------+-------------+------------+
| Current State |  D2  | Next State  | Output LED |
+---------------+------+-------------+------------+
| NONE          |    0 | NONE        | OFF        |
| NONE          |    1 | ONCE        | OFF        |
| ONCE          |    0 | ONCE        | OFF        |
| ONCE          |    1 | TWICE       | OFF        |
| TWICE         |    0 | TWICE       | OFF        |
| TWICE         |    1 | THIRD       | OFF        |
| THIRD         |    0 | THIRD       | ON         |
| THIRD         |    1 | FIRST       | OFF        |
+---------------+------+-------------+------------+
*/

#include <avr/io.h>

#define F_CPU 8000000UL
#include <util/delay.h>

const uint8_t MASK_INTERRUPTOR = (1 << PD2); 
const uint8_t DEBOUNCE_DELAY = 10;
const uint16_t LED_DELAY = 2000;
const uint8_t LED_PIN_GREEN = (1 << PA0);
const uint8_t LED_OUTPUT_MODE = (1<<PA0) | (1<<PA1);
const uint8_t BUTTON_INPUT_MODE = (1<<PD2);

enum class ButtonPressed {NONE, ONCE, TWICE, THIRD}; 
ButtonPressed state = ButtonPressed::NONE;

bool isButtonPressed(){
  uint8_t reading1 = PIND & MASK_INTERRUPTOR;
  _delay_ms(DEBOUNCE_DELAY); 
  uint8_t reading2 = PIND & MASK_INTERRUPTOR;

  bool signalIsHigh = (reading1 == MASK_INTERRUPTOR);
  bool singalIsStable = (reading1 == reading2);
  return signalIsHigh && singalIsStable;
}

void turnOnLedGreen() {
    PORTA |= LED_PIN_GREEN;
}

void turnOffLedGreen(){
    PORTA &= ~LED_PIN_GREEN;
}

void waitReleaseButton(){
    while(isButtonPressed()){}
}

void executeState(){
    if(state == ButtonPressed::THIRD){
        turnOnLedGreen();
        _delay_ms(LED_DELAY);
        turnOffLedGreen();
    }
}

void updateState(){
    switch(state){
        case ButtonPressed::NONE:
            state = ButtonPressed::ONCE;
            break;
        case ButtonPressed::ONCE:
            state = ButtonPressed::TWICE;   
            break;
        case ButtonPressed::TWICE:
            state = ButtonPressed::THIRD;
            break;
        case ButtonPressed::THIRD:
            state = ButtonPressed::ONCE;
            break;      
    }
}

int main(){
    DDRA |= LED_OUTPUT_MODE;
    DDRD &= ~BUTTON_INPUT_MODE;

    while(true){
        if(isButtonPressed()){
            updateState(); 
            executeState();
            waitReleaseButton();
        }
        
    }
}