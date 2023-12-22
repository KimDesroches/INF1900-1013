/*
C++ framework wrapping the LCM-SO1602DTR/M driver.
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

#ifndef _LCM_SO1602DTR_M_FR_H
#define _LCM_SO1602DTR_M_FR_H

#include <avr/io.h>

#define LCM_FW_TOT_CH		32 // Nombre total de cases sur les deux lignes
#define LCM_FW_HALF_CH		16 // Moitié précise de LCM_TOT_CH

#define LCM_FW_CL_DEFCHAR	' ' // Caractère d'effacement par défaut
#define LCM_FW_UINT_DEFFORMAT	"%u" // Format `printf' par défaut pour uint16_t
#define LCM_FW_INT_DEFFORMAT	"%i" // Format `printf' par défaut pour int16_t
#define LCM_FW_DEF_BLINK_EN	false // Activation par défaut du `blink'
#define LCM_FW_DEF_CUR_EN	false // Activation par défaut du curseur

class LCM {
	public:
	LCM(volatile uint8_t*, volatile uint8_t*);
	~LCM(void);
	LCM& put(const char);
	void write(const char*, const uint8_t = 0, const bool = false);
	void clear(void);
	void build_cc(const uint8_t index, const uint8_t* rows);
	void en_blink(const bool);
	void en_cur(const bool);
	void set_bc_index(const uint8_t);
	LCM& operator<<(const char*);
	LCM& operator<<(const uint16_t);
	LCM& operator<<(const int16_t);
	LCM& operator<<(const char);
	const char* operator=(const char*);
	LCM& operator[](const uint8_t index);
	void operator-=(uint8_t);
		
	private:
	uint8_t _last_index; // Dernier curseur (non `blink'/curseur)
	uint8_t _last_bc_index; // Index du `blink'/curseur (correspond toujours
	                        // à l'adresse réellede la DD RAM)
	bool _blink_en; // Activation du `blink'
	bool _cur_en; // Activation du curseur
	volatile uint8_t* _port; // Port AVR utilisé par l'afficheur LCD
	char* _buf; // Buffer pour certaines méthodes
	bool _lib; // `Last Is Bracket' (prochain assignment sera spécifique)
	uint8_t _li; // `Last Position' (utile lorsque `_lib' est vrai)
	
	// Protection contre copie :
	LCM(const LCM&);
	LCM& operator=(const LCM&);
};

#endif // _LCM_SO1602DTR_M_FR_H

