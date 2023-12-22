/*
auteurs : Ali Yacoubi, Kimia Foroudian, Kim Desroches et Ghadi Falouh

Date : 7 novembre 2023

But:  Recevoir via usart le contenu du fichier binaire (bytecode) et
l'écrire en dans la mémoire externe

*/

#define F_CPU 8000000
#define DELAY_WRITING_READING 5

#include <avr/io.h>
#include <util/delay.h>
#include "../../lib/memoire24.h"
#include "../../lib/led.h"
#include "../../lib/RS232.h"

void writeInMemory(uint8_t& byte, Memoire24CXXX& memoire, uint16_t& address, RS232& usart){
    byte = usart.receiveUsart();
    memoire.ecriture(address, byte);
    address++;

    _delay_ms(DELAY_WRITING_READING);
}

void writeByteCodeInMemory() {
    Memoire24CXXX memory;
    RS232 usart = RS232();
    usart.initialise();
    uint16_t address = 0x00;
    uint8_t byte = 0;
 
    writeInMemory(byte, memory, address, usart); // lecture et ecriture du 1er octet (le plus significatif)

    uint16_t size = byte;
    size = size << 8; //bitshift de 8 vers la gauche car la premiere lecture lis les 8 bits les plus significatifs
    
    writeInMemory(byte, memory, address, usart); // lecture et ecriture du 2eme octet (le moins significatif)

    size |= byte;

     while (address < size){
         writeInMemory(byte, memory, address, usart); // lecture et ecriture de chaque octet dans la memoire
    }
}

int main() {
    writeByteCodeInMemory();
    return 0;
}