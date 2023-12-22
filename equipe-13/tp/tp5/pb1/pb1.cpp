/*
 * Nom: pb1.cpp
 * Description:
 * Équipe : 13
 * Auteurs : Kim Desroches et Kimia Foroudian
 
 Identification matérielles (Broches I/O) :
    - La broche A0 est connectée à borne négative de la DEL bicolore
    - La broche A1 est connectée à la borne positive de la DEL bicolore

*/

#include <avr/io.h>

#define F_CPU 8000000UL
#include <util/delay.h>
#include <string.h>
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

int main(){
    initialisation();
    Memoire24CXXX memory;
    uint16_t startAddress = 0x0000;
    char stringToRead[] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
    uint8_t size = strlen(stringToRead);
    uint8_t readingBloc[size];
    const uint8_t WRITING_DELAY = 5;


    memory.ecriture(startAddress, (uint8_t*)stringToRead, size);
    _delay_ms(WRITING_DELAY);
    memory.lecture(startAddress, readingBloc, size);
    
    compareMemoryString((char*)readingBloc, stringToRead);
}