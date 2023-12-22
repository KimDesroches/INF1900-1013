#define F_CPU 8000000

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>


const uint8_t MASK_D2 = (1 << PD2);
const uint8_t DEBOUNCE_DELAY = 10;  
const uint8_t AMBER_DELAY = 10;
const uint8_t LED_GREEN = (1 << PA0);
const uint8_t LED_RED = (1 << PA1);

enum class ButtonState{INITIAL, BUTTON_PRESSED_1, BUTTON_RELEASED_1, BUTTON_PRESSED_2, BUTTON_RELEASED_2, BUTTON_PRESSED_3};
ButtonState currentState = ButtonState:: INITIAL;
volatile bool isButtonPressed = false;





void turnGreen()
{
    PORTA &= ~(LED_RED);
    PORTA |= LED_GREEN;
}   

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

// placer le bon type de signal d'interruption
// à prendre en charge en argument
ISR ( INT0_vect) 
{
    // laisser un délai avant de confirmer la réponse du
    // bouton-poussoir: environ 30 ms (anti-rebond)
    _delay_ms ( 30 );
    // se souvenir ici si le bouton est pressé ou relâché
    if(isButtonPressed)
    {
        isButtonPressed = false;
    }
    else 
    {
        isButtonPressed = true;
    }
    
    // changements d'état tels que ceux de la
    // semaine précédente
    updateState(isButtonPressed);
        
    // Voir la note plus bas pour comprendre cette instruction et son rôle
    EIFR |= (1 << INTF0) ;
}

void initialisation ( void ) 
{
    // cli est une routine qui bloque toutes les interruptions.
    // Il serait bien mauvais d'être interrompu alors que
    // le microcontrôleur n'est pas prêt...
    cli ();
    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables

    DDRA |= LED_GREEN | LED_RED;    
    DDRD &= ~MASK_D2;    
    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes

    EIMSK |= (1 << INT0) ;
    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= (0 << ISC01) | (1 << ISC00) ;
    // sei permet de recevoir à nouveau des interruptions.
    sei ();
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

    // PORTA &= ~(LED_RED);
    //PORTA &= ~(LED_GREEN);
    //_delay_ms(1000);

}


int main()
{
    initialisation();
    while(true)
    {        
        excuteState();
    }    
}
