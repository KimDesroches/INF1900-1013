/*
 * Nom: Delay.h
 * Description: Classe permettant d'utiliser un délais dans des fonctions.
 *              Elle permet d'utiliser des délais en milisecondes avec des 
 *              variables plutôt que de nécessité des constantes lors de la
 *              compilation.
 * Équipe : 1013
 * Auteurs : Kim Desroches, Ghadi Falouh, Kimia Foroudian et Ali Yacoubi
*/
#pragma once

#define F_CPU 8000000
#define FUNCTION_DELAY 50

#include <avr/io.h>
#include <util/delay.h>

void delayMs(uint16_t duration);