/*
 * Nom: pb2.cpp
 * Description:
 * Équipe : 13
 * Auteurs : Kim Desroches et Kimia Foroudian
 
 Identification matérielles (Broches I/O) :
    -

*/

#include <avr/io.h>

#define F_CPU 8000000UL
#include <util/delay.h>
#include "memoire_24.h"


void initialisationUART () {
    UBRR0H = 0;
    UBRR0L = 0xCF;

    UCSR0A = (1 << RXC0) | (1 << TXC0); 
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void transmissionUART(uint8_t data){ 
    while ( !(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

int main(){
    initialisationUART();
    char mots[21] = "Le robot en INF1900\n";
    uint8_t i, j;

    for ( i = 0; i < 100; i++ ) {
        for ( j=0; j < 20; j++ ) {
            transmissionUART(mots[j]);
        }
    }
}