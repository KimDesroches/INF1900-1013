#include "Button.h"

Button::Button(InteruptButton interuptButton): _interuptButton(interuptButton){}
void Button::initialize(){
    cli();    
    switch(_interuptButton)
    {
        case InteruptButton::BUTTON_D2:                                
            DDRD &= ~(1 << PD2);
            EIMSK |= (1 << INT0) ;  
            EICRA |= (1 << ISC01) | (0 << ISC00);    //falling
            break;
        case  InteruptButton::BUTTON_D3:              
            DDRD &= ~(1 << PD3);
            EIMSK |= (1 << INT1) ;  
            EICRA |= (1 << ISC11) | (1 << ISC10);    
            break;
        case  InteruptButton::BUTTON_B2:  
            DDRB &= ~(1 << PB2);
            EIMSK |= (1 << INT2) ;                     
            EICRA |= (1 << ISC21) | (1 << ISC20);    
            break;
    }        
    sei();    
}