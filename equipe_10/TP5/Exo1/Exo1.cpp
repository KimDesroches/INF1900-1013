#define F_CPU 8000000UL

#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <string.h>
#include "memoire_24.h"

const uint8_t LED_GREEN = (1 << PA0);
const uint8_t LED_RED = (1 << PA1); 

void verification(uint8_t liste[], uint8_t listeLecture[])
{
    int i = 0;
    for (i = 0; i < strlen((char*)liste); i++)
    {
        if(liste[i] != listeLecture[i])
        {
            PORTA |= LED_RED;
            return;
        }
    }
    PORTA |= LED_GREEN;
}

int main()
{
    DDRA |= LED_GREEN | LED_RED; 

    Memoire24CXXX memory;
    const uint8_t startAdresse = 0x00;    
    uint8_t liste[] = "PAIN";
    memory.ecriture(startAdresse,(uint8_t*) liste, strlen((char*)liste));

    uint8_t listeLecture(strlen((char*)liste)); 
    memory.lecture(startAdresse,(uint8_t*) listeLecture, strlen((char*)liste));

    //uint8_t liste2[] = "PAIN";
    
    //verification((uint8_t*) liste, (uint8_t*) listeLecture);
    verification((uint8_t*) liste, (uint8_t*) listeLecture);
    //verification((uint8_t*) liste, liste2);
}
