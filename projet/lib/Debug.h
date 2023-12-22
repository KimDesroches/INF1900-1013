/*
 * Nom: Debug.h
 * Description: Définir les macros associés à « #define DEBUG ». Lorsque la 
 *              commande « make debug » est exécuté, DEBUG est défini, ce qui 
 *              permet de satisfaire la condition « ifdef DEBUG ». Ainsi, les 
 *              autres macros sont définis et par du code qui permet la 
 *              transmission de données via RS-232. 
 * Équipe : 1013
 * Auteurs : Kim Desroches, Ghadi Falouh, Kimia Foroudian et Ali Yacoubi
*/

#pragma once

#include "Rs232.h"

void debugPrint(char* x);

#ifdef DEBUG
    #define DEBUG_TRANSMIT(x) debugPrint(x);
#else
    #define DEBUG_TRANSMIT(x) do {} while (0);
#endif