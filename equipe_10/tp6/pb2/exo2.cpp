/*
Auteurs : Ghadi Falouh et ALi Yacoubi
Date : 17 octobre 2023
But: Faire un robot pouvant capter l'intensité lumineuse:
    Si la lumière est basse (en cachant la photorésistance), la DEL prendra la couleur verte.
    Si la lumière est à un bon niveau (lumière ambiante), la DEL tournera à l'ambré.
    Si la lumière est trop forte (photorésistance sous une lampe de poche), la DEL devient rouge.

Dans ce programme, on a initialisé les broches B0 et B1 comme étants outputs et la broche A0 comme 
    etant input. Il faut brancher B0 avec la broche - de la DEL libre et B1 avec sa broche +.
    De plus,le breadboard avec la photorésistance est branché avec le VCC et GND des 
    broches A, il est aussi branché au port analogique A0.
              
*/

#define F_CPU 8000000UL
#include <can.h>
#include <avr/io.h>
#include <util/delay.h>
#include <can.cpp>

const uint8_t MASK_D2 = (1 << PD2);
const uint8_t LED_GREEN = (1 << PB0);
const uint8_t READ_INTENSITY = (1 << PA0); 
const uint8_t LED_RED = (1 << PB1);
const uint8_t SET_LED_OFF = (LED_GREEN | LED_RED);
const uint8_t AMBER_DELAY_RED = 5;
const uint8_t AMBER_DELAY_GREEN = 20;
const uint8_t LOW_INTENSITY = 15;
const uint8_t AMBIENT_INTENSITY = 50;
enum class Color{RED, GREEN, OFF};


void setColor(Color color)
{    
    uint8_t ledOn = 0;
    uint8_t ledOff = 0;
    switch(color)
    {
        case Color::GREEN:            
            ledOff = LED_RED;
            ledOn = LED_GREEN;            
        break;
        case Color::RED:      
            ledOff = LED_GREEN;
            ledOn = LED_RED;      
        break;
        case Color::OFF:
            ledOff = SET_LED_OFF;
        break;        
    }

    PORTB &= ~(ledOff);
    PORTB |= ledOn;
}

void initialize()
{
    DDRA = READ_INTENSITY; 
    DDRB = LED_GREEN | LED_RED; 
}

void turnAmber()
{             
    setColor(Color::GREEN);
    _delay_ms(AMBER_DELAY_GREEN);            
    setColor(Color::RED);
    _delay_ms(AMBER_DELAY_RED);                 
}    

void controlLight(uint16_t  data)
{
    if(data < LOW_INTENSITY)
    {
        setColor(Color::GREEN);                              
    }
    else if(data < AMBIENT_INTENSITY)
    {   
        turnAmber();                   
    }
    else
    {            
        setColor(Color::RED);        
    }    
}

int main()
{  
    initialize();
    can converter = can();      
    while(true)
    {                
        controlLight(converter.lecture(PA0));
    }        
}  