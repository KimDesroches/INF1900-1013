/*
auteurs : Ali Yacoubi, Kimia Foroudian, Kim Desroches et Ghadi Falouh

Date : 31 octobre 2023

But: transférer des données entre le microcontrôleur et l’ordinateur.
     Ce constructeur configure la communication à une vitesse de 2400
     baudes et défini le format des trames à 8 bits de données, 1 bit 
     d’arrêt et sans bit de parité. 
 
*/
#include <avr/interrupt.h>
#include <avr/io.h>

class RS232{
public:
    RS232();    
    static void initialise();
    static void readData(char* data);
private:
    static void transmitUART(uint8_t data);
};