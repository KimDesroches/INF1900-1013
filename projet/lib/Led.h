/*
 * Nom: Led.h
 * Description: Classe pour contrôler la del présente sur la carte mère du robot. 
 *              Elle permet d’allumer la couleur selon l’énumération LedColor.
 * Équipe : 1013
 * Auteurs : Kim Desroches, Ghadi Falouh, Kimia Foroudian et Ali Yacoubi
 *
 *  Identification matérielles (Broches I/O) :
 *  - La broche D1 (PD0) est connectée à borne négative de la DEL bicolore en sortie.
 *  - La broche D2 (PD1) est connectée à la borne positive de la DEL bicolore en sortie.
*/
#pragma once

#include <stdint.h>
#include "Delay.h"

typedef volatile uint8_t* Register;

class Led {
public:
    enum class LedColor {GREEN, RED, AMBER};
    Led();
    void controlColor(LedColor color, const uint8_t RED_DELAY=1, const uint8_t GREEN_DELAY=5);
    void pwm(LedColor color, uint16_t maxValue, uint16_t DELAY_A, const uint16_t DELAY_B, const uint8_t rateDecrease);
    void blinkingLed(LedColor color, uint8_t duration, const uint16_t BLINKING_DELAY);
    void off();

private:
    void setAmberColor(LedColor color, const uint8_t RED_DELAY, const uint8_t GREEN_DELAY);    
    Register _port = &PORTD;
    Register _mode = &DDRD;
    uint8_t _pinGreen = PD0;
    uint8_t _pinRed = PD1;
};