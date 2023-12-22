#include "button.h"

Button::Button(Register mode, InteruptSensControl interruptionType): _mode(mode), _interruptionType(interruptionType){    
    cli();
    DDRD &= ~(1 << PD2);
    EIMSK |= (1 << INT0) ;  
    switch(_interruptionType)
    {
        case:: InteruptSensControl::LOW_LEVEL:
            EICRA |= (0 << ISC01) | (0 << ISC00) ;    
            break;
        case:: InteruptSensControl::ANY_EDGE:
            EICRA |= (0 << ISC01) | (1 << ISC00) ;    
            break;
        case:: InteruptSensControl::FALLING_EDGE:
            EICRA |= (1 << ISC01) | (0 << ISC00) ;    
            break;
        case:: InteruptSensControl::RISING_EDGE:
            EICRA |= (1 << ISC01) | (1 << ISC00) ;    
            break;
    }
    sei();    
}