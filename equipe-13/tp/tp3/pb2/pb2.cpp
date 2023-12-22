/*
 * Nom: pb1.cpp
 * Description:
 * Équipe : 13
 * Auteurs : Kim Desroches et Kimia Foroudian
 
 Identification matérielles (Broches I/O) :
    - La broche B0 est connectée
    - La broche B1 est connectée 

*/

#include <avr/io.h>

#define F_CPU 8000000UL
#include <util/delay.h>

const uint8_t WHEEL_PIN_DIRECTION = (1 << PB1);
const uint8_t WHEEL_PIN = (1 << PB0);

void wheelDirection(){
    PORTB |= WHEEL_PIN;
}

main(){
    DDRB |= ((1<<PB0) | (1<<PB1));
    //DDRD &= ~(1<<PD2);

}