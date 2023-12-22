#include "RS232.h"

RS232::RS232(){};

void RS232::initialise(){
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0A = 0; 
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); 
};

void RS232::readData(char* data){
    for (uint8_t i = 0; i < 100; i++ ) {    
        for (uint8_t j=0; j < 20; j++ ) {
            transmitUART(data[j]);
        }
    }
};

void RS232::transmitUART(uint8_t data){
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
};