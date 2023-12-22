/*
auteurs : Ali Yacoubi, Kimia Foroudian, Kim Desroches et Ghadi Falouh

Date : 31 octobre 2023

But: permettre un délai en ms. 
 
*/
#pragma once

#ifndef F_CPU
	# define F_CPU 8000000
#endif

#include <avr/io.h>
#include <util/delay.h>

void delayMs(uint16_t duration);