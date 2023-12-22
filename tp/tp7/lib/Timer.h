/*
auteurs : Ali Yacoubi, Kimia Foroudian, Kim Desroches et Ghadi Falouh

Date : 31 octobre 2023

But: configurer les registres d‘une minuterie à l’aide du Timer 1 
    en mode CTC (Clear Timer on Compare Match). Elle permettra de 
    générer une interruption après une durée donnée.   
 
*/

#pragma once
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>


typedef volatile uint8_t* Register;

class Timer{
public:
    Timer(uint16_t time, uint16_t prescaler, uint32_t frequency);
    void startTimer(volatile bool& isTimerExpired);
private:
    uint16_t _time;
    uint16_t _prescaler;
    uint32_t _frequency;
};