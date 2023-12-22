/*
auteurs : Ali Yacoubi, Kimia Foroudian, Kim Desroches et Ghadi Falouh

Date : 31 octobre 2023

But:  contrôler la del présente sur la carte mère du robot. Elle permet 
      d’allumer la couleur selon l’énumation ledColor. 

*/
#pragma once
#include <stdint.h>
#include "delay.h"

typedef volatile uint8_t* Register;

class Led {
public:
    enum class ledColor {GREEN, RED, AMBER};
    Led(Register port, Register mode, uint8_t pinGreen, uint8_t pinRed);
    void controlColor(ledColor color, const uint8_t RED_DELAY=1, const uint8_t GREEN_DELAY=5);
    void pwm(ledColor color, uint16_t maxValue, uint16_t DELAY_A, const uint16_t DELAY_B, const uint8_t rateDecrease);
    void blinkingLed(ledColor color, uint8_t duration, const uint16_t BLINKING_DELAY);
    void off();

private:
    void amber(ledColor color, const uint8_t RED_DELAY, const uint8_t GREEN_DELAY);    
    Register _port;
    Register _mode;
    uint8_t _pinGreen;
    uint8_t _pinRed;
};