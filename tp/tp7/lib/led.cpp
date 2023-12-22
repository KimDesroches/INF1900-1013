/*
auteurs : Ali Yacoubi, Kimia Foroudian, Kim Desroches et Ghadi Falouh

Date : 31 octobre 2023

But:  contrôler la del présente sur la carte mère du robot. Elle permet
      d’allumer la couleur selon l’énumation ledColor. 
 
*/

#include "led.h"

Led::Led(Register port, Register mode, uint8_t pinGreen, uint8_t pinRed): _port(port), _mode(mode), _pinGreen(pinGreen), _pinRed(pinRed){
    *_mode |= (1 << _pinGreen) | (1 << _pinRed);
};

void Led::off(){
    *_port &= ~((1 << _pinGreen) | (1 << _pinRed));
}

void Led::controlColor(ledColor color,const uint8_t RED_DELAY, const uint8_t GREEN_DELAY){
    switch(color){
        case ledColor::GREEN:
            off();
            *_port |= (1 << _pinGreen);
            break;
        case ledColor::RED:
            off();
            *_port |= (1 << _pinRed);
            break;
        case ledColor::AMBER:
            off();
            amber(color, RED_DELAY, GREEN_DELAY);
            break;
    }
}

void Led::pwm(ledColor color, uint16_t maxValue, uint16_t DELAY_A, const uint16_t DELAY_B, const uint8_t ArateDecrease=6){
    for(uint8_t dutyCycle = 0; dutyCycle < maxValue; dutyCycle++){
        controlColor(color);
        _delay_loop_2(DELAY_A);
        off();
        _delay_loop_2(DELAY_B-DELAY_A);
        DELAY_A -= ArateDecrease; 
   }
}

void Led::blinkingLed(ledColor color, uint8_t duration, const uint16_t BLINKING_DELAY){       
    for (uint8_t i = 0; i < duration; i++) {
        controlColor(color);     
        delayMs(BLINKING_DELAY);
        off();
        delayMs(BLINKING_DELAY);    
    }
}

void Led::amber(ledColor color, const uint8_t RED_DELAY, const uint8_t GREEN_DELAY){
    controlColor(color);
    delayMs(RED_DELAY);
    controlColor(color);
    delayMs(GREEN_DELAY);
}