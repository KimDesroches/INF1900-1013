/*
auteurs : Ali Yacoubi, Kimia Foroudian, Kim Desroches et Ghadi Falouh

Date : 31 octobre 2023

But: définir les macros associés à « #define DEBUG ». Lorsque la commande
  « make debug » est exécuté, DEBUG est défini, ce qui permet de satisfaire
   la condition « ifdef DEBUG ». Ainsi, les autres macros sont définis et 
   par du code qui permet la transmission de données via RS-232. 
 
*/
#pragma once

#include "RS232.h"

void debugPrint(char* x);

#ifdef DEBUG
    #define DEBUG_TRANSMIT(x) debugPrint(x);
#else
    #define DEBUG_TRANSMIT(x) do {} while (0);
#endif