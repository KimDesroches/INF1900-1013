/*
 * Nom: Timer.h
 * Description: Classe pour configurer les registres d‘une minuterie à l’aide 
 *              du Timer 1 en mode CTC (Clear Timer on Compare Match). Elle 
 *              permettra de générer une interruption après une durée donnée.   
 * Équipe : 1013
 * Auteurs : Kim Desroches, Ghadi Falouh, Kimia Foroudian et Ali Yacoubi
*/

#pragma once
#include <stdint.h>
#include <avr/interrupt.h>
#include <avr/io.h>

class Timer{
public:
    Timer();
    Timer(uint8_t time, uint16_t prescaler, uint32_t frequency);
    void startTimer(volatile bool& isTimerExpired);
private:
    uint16_t _time;
    uint16_t _prescaler;
    uint32_t _frequency;
};