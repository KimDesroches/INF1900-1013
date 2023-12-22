/*
Custom procedures, mainly related to character arrays.
Copyright (C) 2009  Philippe Proulx (philippe.proulx@polymtl.ca)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "customprocs.h"

/**
 * Longueur d'une cha�ne ASCIIZ.
 *
 * @param str	Cha�ne ASCIIZ
 * @return	Longueur de la cha�ne
 */
uint16_t cp_strlen(const char* str) {
	uint16_t i = '\0';

	while (str[++i] != '\0');

	return i;
}

/**
 * R�impl�mentation d'un `itoa'.
 *
 * @param buf16		Buffer de 16 B � fournir
 * @param val		Valeur NON sign�e � convertir
 * @param base		Base de conversion (2 � 16)
 * @return		Adresse de la cha�ne obtenue
 */
char* cp_itoa(char* buf16, uint16_t val, const uint8_t base) {
	uint8_t i = 14;
	buf16[i + 1] = 0;

	if (val == 0) {
		buf16[i] = '0';
		return &buf16[i];
	}

	for(; val && i; --i, val /= base) {
		buf16[i] = CP_HEX_CHARLIST[val % base];
	}

	return &buf16[i + 1];
}

/**
 * Attend un nombre de millisecondes.
 *
 * @param ms	Nombre de millisecondes � attendre.
 */
void cp_wait_ms(const uint16_t ms) {
	uint16_t i;

	for (i = 0; i < ms; ++i) {
		_delay_ms(1.0);
	}
}
