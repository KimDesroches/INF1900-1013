#define F_CPU 8000000

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>

const uint8_t MASK_D2 = (1 << PD2);
const uint8_t INIT_B0 = (1 << PB0);
const uint8_t INIT_B1 = (1 << PB1);


void ajustementPwm ( float rapportAB) {

// mise à un des sorties OC1A et OC1B sur comparaison

// réussie en mode PWM 8 bits, phase correcte

// et valeur de TOP fixe à 0xFF (mode #1 de la table 16-5

// page 130 de la description technique du ATmega324PA)

OCR1A = (uint8_t) (rapportAB*255) ;

OCR1B = (uint8_t) (rapportAB*255) ;


// division d'horloge par 8 - implique une fréquence de PWM fixe

TCCR1A |= (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10)  ;

TCCR1B |=  (1 << CS11) ;

TCCR1C = 0;

}

void ControlMotor()
{

    ajustementPwm(0);
    _delay_ms(2000);    
    
    ajustementPwm(0.25);
    _delay_ms(2000);

    ajustementPwm(0.50);
    _delay_ms(2000);

    ajustementPwm(0.75);
    _delay_ms(2000);

    ajustementPwm(1);
    _delay_ms(2000);
    
}



int main()
{
    //DDRB |= INIT_B0 | INIT_B1; 
    DDRD |= (1 << PD4) | (1 << PD5) | (1 << PD2);

    while(true)
        ControlMotor();
}