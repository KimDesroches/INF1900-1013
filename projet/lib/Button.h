/*
 * Nom: Button.h
 * Description: Classe permettant l'initialisation de boutons par interruption.
 * Équipe : 1013
 * Auteurs : Kim Desroches, Ghadi Falouh, Kimia Foroudian et Ali Yacoubi
 *
 * Identifications matérielles (Broches I/O) :
 *  - Le bouton interrupt est connecté à la broche D3 (PD2) en entrée.
 *  - Le bouton de sélection sur le breadboard est connecté à la broche D4 
 *    (PD3) en entrée via le fil de données.
 *  - Le bouton de validation sur le breadboard est connecté à la broche B3 
 *    (PB2) en entrée via le fil de données.
 *
 * Les boutons sur le breadboard sont en low enable : 
 *  - à 0 (bouton relaché), le courant passe
 *  - à 1 (bouton appuyé), aucun courant ne passe
 * 
 * Le mode des interruptions est falling edge.
*/

#pragma once

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

typedef volatile uint8_t* Register;

enum class InteruptButton {BUTTON_D2, BUTTON_D3, BUTTON_B2};    
class Button{
public:
    Button(InteruptButton interuptButton);     
    void initialize();   
private:        
    InteruptButton _interuptButton;
};