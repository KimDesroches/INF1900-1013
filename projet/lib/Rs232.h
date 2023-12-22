/*
 * Nom: Rs232.h
 * Description: Classe pour transférer des données entre le microcontrôleur et l’ordinateur.
                Ce constructeur configure la communication à une vitesse de 2400
                baudes et défini le format des trames à 8 bits de données, 1 bit 
                d’arrêt et sans bit de parité. 
 * Équipe : 1013
 * Auteurs : Kim Desroches, Ghadi Falouh, Kimia Foroudian et Ali Yacoubi
 
*/
#pragma once

#include <avr/io.h>
#include <string.h>

class Rs232{
public:
    Rs232(){};    
    ~Rs232(){};
    void initialise();
    void readData(char* data);
    uint8_t receiveUsart(void);
    void transmitUsart(uint8_t data);    
};