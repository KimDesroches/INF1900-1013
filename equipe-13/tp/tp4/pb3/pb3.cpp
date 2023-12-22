/*
 * Nom: pb3.cpp
 * Description:
 * Équipe : 13
 * Auteurs : Kim Desroches et Kimia Foroudian
 
 Identification matérielles (Broches I/O) :
    - La broche D4 est connectée sur la broche du bas
    - La broche D5 est connectée sur la broche du haut

*/

#include <avr/interrupt.h>
#include <avr/io.h>

#define F_CPU 8000000UL
#include <util/delay.h>

const uint8_t WHEEL_PIN_DIRECTION = (1 << PD4);
const uint8_t WHEEL_PIN_ROTATION = (1 << PD5);

void initialisation(){
    DDRD |= (WHEEL_PIN_DIRECTION)|(WHEEL_PIN_ROTATION);
}

void ajustPwm(uint16_t timeA, uint16_t timeB) {
    OCR1A = timeA;
    OCR1B = timeB;
    TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10) ;
    TCCR1B = (1 << CS11);
    TCCR1C = 0;
}

int main(){
    const uint8_t PWM_100 = 255;
    const uint8_t PWM_75 = 191.25;
    const uint8_t PWM_50 = 127.5;
    const uint8_t PWM_25 = 63.75;
    const uint8_t PWM_0 = 0;

    initialisation();
    ajustPwm(PWM_100, PWM_100);
    _delay_ms(2000);
    ajustPwm(PWM_75, PWM_75);
    _delay_ms(2000);
    ajustPwm(PWM_50, PWM_50);
    _delay_ms(2000);
    ajustPwm(PWM_25,PWM_25);
    _delay_ms(2000);
    ajustPwm(PWM_0, PWM_0);
    _delay_ms(2000);
}