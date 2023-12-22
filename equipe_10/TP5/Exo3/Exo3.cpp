#define F_CPU 8000000

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "memoire_24.h"

void initialisationUART ( void ) {

    // 2400 bauds. Nous vous donnons la valeur des deux

    // premiers registres pour vous éviter des complications.

    UBRR0H = 0;

    UBRR0L = 0xCF;

    // permettre la réception et la transmission par le UART0

    UCSR0A = 0 ; // a revoir page 185
    
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0) ; 

    // Format des trames: 8 bits, 1 stop bits, sans parité
    // (0 << UPMn0 ) | (0 <<  UPMn1) pour disabel parity mode
    // (0 << USBSn) pour  1 stop bit
    
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00) ; //

}


// Du USART vers le PC
void transmissionUART ( uint8_t donnee ) 
{
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = donnee; 
}





int main()
{
    initialisationUART();
    Memoire24CXXX memory;
    uint8_t startAdresse = 0x00;  
    const uint8_t endAdresse = 0xAA; 

    uint8_t lectureMemoire;  

    while(startAdresse != endAdresse)
    {        
        //memory.lecture(startAdresse, (uint8_t*) lectureMemoire);
        transmissionUART(startAdresse);
        startAdresse++;
    }
    
    /*
    char mots[21] = "Le robot en INF1900\n";

    uint8_t i, j;
    for ( i = 0; i < 100; i++ ) 
    {
    for ( j=0; j < 20; j++ ) 
    {
    transmissionUART ( mots[j] );
    }
    }
    */

}
