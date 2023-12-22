#include "MainAlgo.h"

ISR(INT0_vect){ //bouton Interrupt    
    uint8_t firstReading = (PIND & MASK_BUTTOND2);
    _delay_ms(DEBOUNCE_DELAY1);    
    uint8_t secondeReading = (PIND & MASK_BUTTOND2);
    if(secondeReading == firstReading){
      isInterrupt = true;                
    }else{
      isInterrupt = false;    
    }    
    EIFR |= (1 << INTF0) ;
}


ISR(INT1_vect){ //bouton Selection (gauche)  
    uint8_t firstReading = (PIND & MASK_BUTTOND3);
    _delay_ms(DEBOUNCE_DELAY2);    
    uint8_t secondeReading = (PIND & MASK_BUTTOND3);  
    if(secondeReading == firstReading){
      isSelection = true;    
    }else{
      isSelection = false;    
    }    
    EIFR |= (1 << INTF1);
}


ISR(INT2_vect){ //bouton Validation (droite)  
    uint8_t firstReading = (PIND & MASK_BUTTONB2);
    _delay_ms(DEBOUNCE_DELAY2);    
    uint8_t secondeReading = (PIND & MASK_BUTTONB2);  
    if(secondeReading == firstReading){
      isValidation = true;     
    }
    else{
      isValidation = false;     
    }               
    EIFR |= (1 << INTF2);
}

ISR(TIMER1_COMPA_vect){
    isTimerDone = true;
    if(isCornerChallenge){
      PORTD ^= (1 << PD0);
    };
    counter++;
};

int main(){

    Led led;
    led.controlColor(Led::LedColor::RED);
    
    Button interrupt(InteruptButton::BUTTON_D2);
    interrupt.initialize();
    
    Button selection(InteruptButton::BUTTON_D3);
    selection.initialize();
    
    Button validation(InteruptButton::BUTTON_B2);    
    validation.initialize();
  
    Game game;   

    while (true) {     
      game.executeState(isInterrupt, isSelection, isValidation, counter, isTimerDone, isCornerChallenge);        
    }    
}