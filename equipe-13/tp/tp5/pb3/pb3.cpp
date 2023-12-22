/*
 * Nom: pb3.cpp
 * Description: Écriture en mémoire, lecture et affichage sur le terminal
 * Équipe : 13
 * Auteurs : Kim Desroches et Kimia Foroudian
 
 Identification matérielles (Broches I/O) :
    - La broche A0 est connectée à borne négative de la DEL bicolore
    - La broche A1 est connectée à la borne positive de la DEL bicolore

*/

#include <avr/io.h>
#include <string.h>

#define F_CPU 8000000UL
#include <util/delay.h>
#include "memoire_24.h"

const uint8_t LED_PIN_GREEN = (1 << PA0);
const uint8_t LED_PIN_RED = (1 << PA1);
const uint8_t LED_OUTPUT_MODE = (1<<PA0) | (1<<PA1);

void turnOffLed(){
    PORTA &= ~(LED_PIN_GREEN| LED_PIN_RED);
}

void turnOnLed(uint8_t color){
    turnOffLed();
    PORTA |= color;
}

void initialisation(){
    DDRA |= LED_OUTPUT_MODE;
}

void compareMemoryString(char* memoryString, char* myString){
    if(!strcmp(memoryString, myString)){
        turnOnLed(LED_PIN_GREEN);
    }
    else{
        turnOnLed(LED_PIN_RED);
    }
}

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
    initialisation();
    initialisationUART();
    Memoire24CXXX memory;
    uint16_t startAddress = 0x0000;
    char words[30] = "Albert est le meilleur robot\n";
    uint8_t size = strlen(words);
    uint8_t readingBloc[size];
    const uint8_t WRITING_DELAY = 5;

    memory.ecriture(startAddress, (uint8_t*)words, size);
    _delay_ms(WRITING_DELAY);
    memory.lecture(startAddress, readingBloc, size);

    compareMemoryString((char*)readingBloc, words);

    for (uint8_t i = 0; i < 100; i++ ) {
        for (uint8_t  j = 0; j < 30; j++ ) {
            transmissionUART(readingBloc[j]);
        }
    }
}