/*
 * Nom: pb2.cpp
 * Description: Changer l'état (couleur) de la led lors d'appuis du bouton
 * Équipe : 13
 * Auteurs : Kim Desroches et Kimia Foroudian
  
 Identification matérielles (Broches I/O) :
    - La broche A0 est connectée à borne négative de la DEL bicolore
    - La broche A1 est connectée à la borne positive de la DEL bicolore
    - Le bouton est connecté à la broche D2 en entrée.

Table des états:
+---------------+------+-------------+-----------------+
| Current State |  D2  | Next State  | Output ColorLED |
+---------------+------+-------------+-----------------+
| INTIAL_RED    |    0 | INITIAL_RED | RED             |
| INITIAL_RED   |    1 | AMBER       | AMBER           |
| AMBER         |    0 | GREEN       | GREEN           |
| AMBER         |    1 | AMBER       | AMBER           |
| GREEN         |    0 | GREEN       | GREEN           |
| GREEN         |    1 | RED         | RED             |
| RED           |    0 | OFF         | OFF             |
| RED           |    1 | RED         | RED             |
| OFF           |    0 | OFF         | OFF             |
| OFF           |    1 | GREEN2      | GREEN           |
| GREEN2        |    0 | INITIAL_RED | RED             |
| GREEN2        |    1 | GREEN       | GREEN           |
+---------------+------+-------------+-----------------+

 */

#include <avr/io.h>

#define F_CPU 8000000UL
#include <util/delay.h>

const uint8_t MASK_INTERRUPTOR = (1 << PD2); 
const uint8_t DEBOUNCE_DELAY = 10;
const uint8_t RED_DELAY = 1;
const uint8_t GREEN_DELAY = 5;
const uint8_t BUTTON_INPUT_MODE = (1 << PD2);
const uint8_t LED_PIN_GREEN = (1 << PA0);
const uint8_t LED_PIN_RED = (1 << PA1);
const uint8_t LED_OUTPUT_MODE = LED_PIN_GREEN | LED_PIN_RED;

enum class ledColor {INITIAL_RED, AMBER, GREEN, RED, OFF, GREEN2};
ledColor state = ledColor::INITIAL_RED;
bool buttonPressed = false;

bool isButtonPressed(){
  uint8_t reading1 = PIND & MASK_INTERRUPTOR;
  _delay_ms(DEBOUNCE_DELAY); 
  uint8_t reading2 = PIND & MASK_INTERRUPTOR;

  bool signalIsHigh = (reading1 == MASK_INTERRUPTOR);
  bool singalIsStable = (reading1 == reading2);
  return signalIsHigh && singalIsStable;
}

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

bool hasButtonChangedState(bool buttonPressed){
    bool buttonIsPressed = isButtonPressed();
    bool buttonHasChanged = (buttonIsPressed != buttonPressed);
    return buttonHasChanged;
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
    if(hasButtonChangedState(buttonPressed)){
        buttonPressed = !buttonPressed;
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
}

int main(){
    DDRA |= LED_OUTPUT_MODE;
    DDRD &= ~BUTTON_INPUT_MODE;
    while(true){ 
        executeState();
        updateState();
    }
}