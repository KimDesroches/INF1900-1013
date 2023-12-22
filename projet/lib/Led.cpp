#include "Led.h"

Led::Led(){
    *_mode |=  (1 << _pinGreen) | (1 << _pinRed);
}

void Led::off(){
    *_port &= ~((1 << _pinGreen) | (1 << _pinRed));
}

void Led::controlColor(LedColor color,const uint8_t RED_DELAY, const uint8_t GREEN_DELAY){
    switch(color){
        case LedColor::GREEN:
            off();
            *_port |= (1 << _pinGreen);
            break;
        case LedColor::RED:
            off();
            *_port |= (1 << _pinRed);
            break;
        case LedColor::AMBER:
            off();
            setAmberColor(color, RED_DELAY, GREEN_DELAY);
            break;
    }
}

void Led::pwm(LedColor color, uint16_t maxValue, uint16_t DELAY_A, const uint16_t DELAY_B, const uint8_t ArateDecrease=6){
    for(uint8_t dutyCycle = 0; dutyCycle < maxValue; dutyCycle++){
        controlColor(color);
        _delay_loop_2(DELAY_A);
        off();
        _delay_loop_2(DELAY_B-DELAY_A);
        DELAY_A -= ArateDecrease; 
   }
}

void Led::blinkingLed(LedColor color, uint8_t duration, const uint16_t BLINKING_DELAY){       
    for (uint8_t i = 0; i < duration; i++) {
        controlColor(color);     
        delayMs(BLINKING_DELAY);
        off();
        delayMs(BLINKING_DELAY);    
    }
}

void Led::setAmberColor(LedColor color, const uint8_t RED_DELAY, const uint8_t GREEN_DELAY){
    controlColor(color);
    delayMs(RED_DELAY);
    controlColor(color);
    delayMs(GREEN_DELAY);
}