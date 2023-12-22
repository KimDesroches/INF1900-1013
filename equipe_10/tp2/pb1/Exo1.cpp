/*
Auteurs : Ghadi Falouh et ALi Yacoubi
Date : 8 septembre
But: Ce programme permet d'allumer la DEL en vert apres avoir appuyer 3 fois sur 
     le bouton poussoir.

Cette opération peut être représentée par la table d'états suivante:

+-------------------+-----------------+-------------------+--------+
|   currentState    | isButtonPressed |     nextState     | output |
+-------------------+-----------------+-------------------+--------+
| INITIAL           |               0 | INITIAL           | RED    |
| INITIAL           |               1 | BUTTON_PRESSED_1  | RED    |
| BUTTON_PRESSED_1  |               0 | BUTTON_RELEASED_1 | OFF    |
| BUTTON_PRESSED_1  |               1 | BUTTON_PRESSED_1  | OFF    |
| BUTTON_RELEASED_1 |               0 | BUTTON_RELEASED_1 | OFF    |
| BUTTON_RELEASED_1 |               1 | BUTTON_PRESSED_2  | OFF    |
| BUTTON_PRESSED_2  |               0 | BUTTON_RELEASED_2 | OFF    |
| BUTTON_PRESSED_2  |               1 | BUTTON_PRESSED_2  | OFF    |
| BUTTON_RELEASED_2 |               0 | BUTTON_RELEASED_2 | OFF    |
| BUTTON_RELEASED_2 |               1 | BUTTON_PRESSED_3  | OFF    |
| BUTTON_PRESSED_3  |               0 | BUTTON_RELEASED_3 | OFF    |
| BUTTON_PRESSED_3  |               1 | BUTTON_PRESSED_3  | OFF    |
| BUTTON_RELEASED_3 |               0 | BUTTON_RELEASED_3 | GREEN  |
| BUTTON_RELEASED_3 |               1 | INITIAL           | GREEN  |
+-------------------+-----------------+-------------------+--------+



Dans ce programme, on a initialiser les broches A0 et A1 comme étant outputs et 
    la broche D2 en input.
Il faut brancher A0 a la broche - de la DEL et A1 a la broche + de la DEL. Alors 
    que la broche D2 est branchee avec le boutton poussoir.



*/

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

const uint8_t MASK_D2 = (1 << PD2);
const uint8_t DEBOUNCE_DELAY = 10;
const uint8_t LED_GREEN = (1 << PA0);
const uint8_t LED_RED = (1 << PA1);
const uint16_t LIGHT_DELAY = 2000;

enum class ButtonState{INITIAL, BUTTON_PRESSED_1, BUTTON_RELEASED_1, BUTTON_PRESSED_2, BUTTON_RELEASED_2, BUTTON_PRESSED_3,BUTTON_RELEASED_3};
ButtonState buttonState = ButtonState:: INITIAL;

bool isButtonPressed()
{
    uint8_t scan1 = PIND & MASK_D2; 
    _delay_ms(DEBOUNCE_DELAY);
    uint8_t scan2 = PIND & MASK_D2;    
    return scan1 && scan2;
}


void updateButtonState(bool press)
{
    switch(buttonState)
    {
        case ButtonState::INITIAL: 
            if(press)
            {
                buttonState = ButtonState::BUTTON_PRESSED_1;          
            }        
            break;
        case ButtonState::BUTTON_PRESSED_1:
            if(!press)
            {
                buttonState = ButtonState::BUTTON_RELEASED_1;                
            }                
            break;
        case ButtonState::BUTTON_RELEASED_1:
            if(press)
            {
                buttonState = ButtonState::BUTTON_PRESSED_2;                
            }                
            break;
        case ButtonState::BUTTON_PRESSED_2:
            if(!press)
            {
                buttonState = ButtonState::BUTTON_RELEASED_2;                
            }                
            break;
        case ButtonState::BUTTON_RELEASED_2:
            if(press)
            {
                buttonState = ButtonState::BUTTON_PRESSED_3;                
            }                
            break;
        case ButtonState::BUTTON_PRESSED_3:                        
            if(!press)
            {
                buttonState = ButtonState::BUTTON_RELEASED_3;                
            } 
            break;
        case ButtonState::BUTTON_RELEASED_3:  
            buttonState = ButtonState::INITIAL;                             
            break;              
            
    }
}

void turnOffRed()
{
    PORTA &= ~(LED_RED);
}

void turnOnGreen()
{
    //turnOffRed();
    PORTA |= LED_GREEN;
    
}   

void turnOffGreen()
{
    //turnOffRed();
    PORTA &= ~(LED_GREEN); 
}

void excuteState()
{         
    if  (buttonState == ButtonState::BUTTON_RELEASED_3)
    {
        turnOnGreen();
        _delay_ms(LIGHT_DELAY);
        turnOffGreen();           
    }
}

int main()
{
    DDRA |= LED_GREEN | LED_RED;     
    DDRD &= ~(MASK_D2);    
    bool press;
    while(true)
    {        
        press = isButtonPressed();
        excuteState();
        updateButtonState(press);       
                              
    }
}  