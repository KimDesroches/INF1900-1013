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

#ifndef _CUSTOMPROCS_H
#define _CUSTOMPROCS_H

#include <avr/io.h>

#define CP_HEX_CHARLIST		"0123456789abcdef" // Liste des caractères hex.
// #define CP_HEX_CHARLIST	"0123456789abcdef" // Majuscules...

uint16_t cp_strlen(const char*);
char* cp_itoa(char*, uint16_t, const uint8_t);
void cp_wait_ms(const uint16_t);

#endif // _CUSTOMPROCS_H
