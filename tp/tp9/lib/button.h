/*
auteurs : Ali Yacoubi, Kimia Foroudian, Kim Desroches et Ghadi Falouh

Date : 31 octobre 2023

But: générer des interruptions. Elle est faite pour travailler avec un
     bouton connecté au port D2. 
 
*/
#pragma once
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

typedef volatile uint8_t* Register;
enum class InteruptSensControl {LOW_LEVEL, ANY_EDGE, FALLING_EDGE, RISING_EDGE};


class Button{
public:
    Button(Register mode, InteruptSensControl interruptionType);    
private:        
    Register _mode;
    InteruptSensControl _interruptionType;
};