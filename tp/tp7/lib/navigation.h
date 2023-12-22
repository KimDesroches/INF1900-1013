/*
auteurs : Ali Yacoubi, Kimia Foroudian, Kim Desroches et Ghadi Falouh

Date : 31 octobre 2023

But: effectuer le contrôle des moteurs (des roues) du robot d’où son 
     nom (permet la navigation). Le timer0 est utilisé pour générer les
     signaux PWM. Le mode choisi est PWM phase correct avec une valeur 
     top de 0xFF et un prescaler de 8. Le mode de comparaison est 
     « Clear OC0A and OC0B on compare match ».  

Il faut brancher B5 avec D de JM1, B3 avec E de JM1. De plus, 
    il faut brancher B4 avec E de JM2, B2 avec D de JM2.
*/
#pragma once

#include <stdint.h>
#include <avr/io.h>
#include "delay.h"

#define RIGHT_MOTOR_PIN (1 << PB3)
#define LEFT_MOTOR_PIN (1 << PB4)
#define RIGHT_MOTOR_DIRECTION (1 << PB5)
#define LEFT_MOTOR_DIRECTION (1 << PB2)
#define STOP_SPEED 0
#define TURN_SPEED 50

class Navigation{
public:
    Navigation();
    void foward(uint8_t rightPercent, uint8_t leftPercent);
    void reverse(uint8_t rightPercent, uint8_t leftPercent);
    void stop();
    void turnRight(uint8_t duration);
    void turnLeft(uint8_t duration);
private:
    void setSpeed(uint8_t rightPercent, uint8_t leftPercent);
};