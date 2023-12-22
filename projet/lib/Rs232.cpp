#include "Rs232.h"

void Rs232::initialise(){
    // 2400 bauds. Nous vous donnons la valeur des deux.
    UBRR0H = 0;
    UBRR0L = 0xCF;
    // Permettre la réception et la transmission par le UART0.
    UCSR0A = 0;
    UCSR0B |= (1 << TXEN0 | 1 << RXEN0);

    // Format des trames: 8 bits, 1 stop bits, sans parité.
    // Asynchronous USART par défaut.
    UCSR0C &= ~(1 << UCSZ02);
    UCSR0C |= (1 << UCSZ01 | 1 << UCSZ00);
}

void Rs232::readData(char* data){    
    for (uint8_t j=0; j <  strlen(data); j++ ) {
        transmitUsart(data[j]);
    }    
};

void Rs232::transmitUsart(uint8_t data){
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
};

uint8_t Rs232::receiveUsart(void){
    while (!((UCSR0A) & (1 << RXC0))); 
    return UDR0;
}