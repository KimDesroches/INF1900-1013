/*
Auteurs : Ghadi Falouh et ALi Yacoubi
Équipe : 10
Date : 8 septembre 2023
But: Ce programme permet de changer la couleur de la DEL. D'abord, le DEL est allumé en rouge, 
     si on pese sur le bouton poussoir la lumière devient ambrée. En relâchant la lumière 
     devient vert. En pesant de nouveau, la DEL devient rouge et en relâchant, elle s'éteint.
     En suite, lorsqu'on appuie sur la bouton, la DEL s'allume en vert et en relâchant elle
     devient rouge. Cela veut dire qu'on est retourné à l'état initial.    
Cette opération peut être représentée par la table d'états suivante:
+-------------------+-----------------+-------------------+--------+
|   currentState    | isButtonPressed |     nextState     | output |
+-------------------+-----------------+-------------------+--------+
| INITIAL           |               0 | INITIAL           | RED    |
| INITIAL           |               1 | BUTTON_PRESSED_1  | RED    |
| BUTTON_PRESSED_1  |               0 | BUTTON_RELEASED_1 | AMBER  |
| BUTTON_PRESSED_1  |               1 | BUTTON_PRESSED_1  | AMBER  |
| BUTTON_RELEASED_1 |               0 | BUTTON_RELEASED_1 | GREEN  |
| BUTTON_RELEASED_1 |               1 | BUTTON_PRESSED_2  | GREEN  |
| BUTTON_PRESSED_2  |               0 | BUTTON_RELEASED_2 | RED    |
| BUTTON_PRESSED_2  |               1 | BUTTON_PRESSED_2  | RED    |
| BUTTON_RELEASED_2 |               0 | BUTTON_RELEASED_2 | OFF    |
| BUTTON_RELEASED_2 |               1 | BUTTON_PRESSED_3  | OFF    |
| BUTTON_PRESSED_3  |               0 | INITIAL           | GREEN  |
| BUTTON_PRESSED_3  |               1 | BUTTON_PRESSED_3  | GREEN  |
+-------------------+-----------------+-------------------+--------+

Dans ce programme, on a initialiser les broches A0 et A1 comme étants 
    outputs et la broche D2 en input.
Il faut brancher A0 a la broche - de la DEL et A1 a la broche + de la DEL. 
    Alors que, la broche D2 est branchee avec le button poussoir.               
*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


enum class ButtonState{INITIAL, BUTTON_PRESSED_1, BUTTON_RELEASED_1, BUTTON_PRESSED_2, BUTTON_RELEASED_2, BUTTON_PRESSED_3};
ButtonState currentState = ButtonState:: INITIAL;
const uint8_t MASK_D2 = (1 << PD2);
const uint8_t DEBOUNCE_DELAY = 10;  
const uint8_t AMBER_DELAY = 10;
const uint8_t LED_GREEN = (1 << PA0);
const uint8_t LED_RED = (1 << PA1);


bool isButtonPressed()
{
    uint8_t signal1 = PIND & MASK_D2; 
    _delay_ms(DEBOUNCE_DELAY);
    uint8_t signal2 = PIND & MASK_D2;

    bool signalIsHigh = (signal1 == MASK_D2);
    bool signaIsStable = (signal1 == signal2);

    return signalIsHigh && signaIsStable;
}
// a modifier
void turnGreen()
{
    PORTA &= ~(LED_RED);
    PORTA |= LED_GREEN;
}   
// a modifier
void turnRed()
{
    PORTA &= ~(LED_GREEN);
    PORTA |= LED_RED;
}

void turnAmber()
{           
    turnGreen();
    _delay_ms(AMBER_DELAY);
    turnRed();
    _delay_ms(AMBER_DELAY);                 
}

void updateState(bool isPressed)
{
    switch(currentState)
    {        
        case ButtonState::INITIAL:
            if(isPressed)
            {
                currentState = ButtonState::BUTTON_PRESSED_1;
            }            
            break;
        case ButtonState::BUTTON_PRESSED_1:
            if(!isPressed)
            {
                currentState = ButtonState::BUTTON_RELEASED_1;
            }            
            break;
        case ButtonState::BUTTON_RELEASED_1:
            if(isPressed)
            {
                currentState = ButtonState::BUTTON_PRESSED_2;
            }            
            break;
        case ButtonState::BUTTON_PRESSED_2:
            if(!isPressed)
            {
                currentState = ButtonState::BUTTON_RELEASED_2;
            }            
            break;
        case ButtonState::BUTTON_RELEASED_2:
            if(isPressed)
            {
                currentState = ButtonState::BUTTON_PRESSED_3;
            }            
            break;
        case ButtonState::BUTTON_PRESSED_3:
            if(!isPressed)
            {
                currentState = ButtonState::INITIAL;
            }            
            break;            
    }
}

void excuteState()
{
    switch(currentState)
    {
        case ButtonState::INITIAL:
            turnRed();
            break;
        case ButtonState::BUTTON_PRESSED_1:                         
            turnAmber();
            break;
        case ButtonState::BUTTON_RELEASED_1:        
            turnGreen();
            break;
        case ButtonState::BUTTON_PRESSED_2:        
            turnRed();
            break;
        case ButtonState::BUTTON_RELEASED_2:        
            PORTA &= ~(LED_RED);
            break;
        case ButtonState::BUTTON_PRESSED_3:
            turnGreen();
            break; 
        }
}

int main()
{   
    DDRA |= LED_GREEN | LED_RED;    
    DDRD &= ~MASK_D2;    
    bool isPressed = false;            
    while(true)
    {           
        isPressed = isButtonPressed();
        excuteState();                
        updateState(isPressed);                                                                                                               
    }
}