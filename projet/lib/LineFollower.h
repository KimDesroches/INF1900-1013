/*
 * Nom: LineFollower.h
 * Description: Classe pour lire une ligne avec le suiveur de ligne
 *              Maker Line de Cytron.
 * Équipe : 1013
 * Auteurs : Kim Desroches, Ghadi Falouh, Kimia Foroudian et Ali Yacoubi
 *
 *  Identification matérielles (Broches I/O) :
 *  - Le connecteur D1 du capteur est connecté à la broche A1 de la carte mère.
 *  - Le connecteur D2 du capteur est connecté à la broche A2 de la carte mère.
 *  - Le connecteur D3 du capteur est connecté à la broche A3 de la carte mère.
 *  - Le connecteur D4 du capteur est connecté à la broche A4 de la carte mère.
 *  - Le connecteur D5 du capteur est connecté à la broche A5 de la carte mère.
 * Tout est connecté en entrée.
 * 
*/

#pragma once

#define FURTHER_LEFT_SENSOR  (1 << PA0) 
#define MIDDLE_LEFT_SENSOR   (1 << PA1)
#define MIDDLE_SENSOR        (1 << PA2)
#define MIDDLE_RIGHT_SENSOR  (1 << PA3)
#define FURTHER_RIGHT_SENSOR (1 << PA4)

#include <avr/io.h>

class LineFollower {
public:
    LineFollower();
    bool isReadingLine();
    
};
