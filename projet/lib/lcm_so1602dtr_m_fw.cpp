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

#define F_CPU 8000000UL
#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

#include "lcm_so1602dtr_m_fw.h"
#include "lcm_so1602dtr_m.h"
#include "customprocs.h"

#define LCM_FW_BUF_SIZE		16 // Taille du buffer local

/**
 * Construit un objet LCM.
 *
 * @param ddr	`Data Direction Register' AVR utilis� par l'afficheur
 * @param port	Port AVR occup� par l'afficheur
 */
LCM::LCM(volatile uint8_t* ddr, volatile uint8_t* port) : _last_index(0),
_last_bc_index(0), _blink_en(LCM_FW_DEF_BLINK_EN), _cur_en(LCM_FW_DEF_CUR_EN),
_port(port), _lib(false), _li(0) {	
	lcmd_init_4bit(ddr, port); // Initialisation
	lcmd_entry_sm(LCM_ID_INC, LCM_S_OFF, _port);
	
	_buf = (char*) malloc(LCM_FW_BUF_SIZE); // Allocation du buffer local
}

/**
 * D�truit proprement un objet LCM.
 *
 */
LCM::~LCM(void) {
	free(_buf);
}

/**
 * Ajoute un caract�re et positionne le curseur apr�s.
 *
 * @param ch	Caract�re (du jeu de caract�res de l'afficheur)
 * @return	Auto-r�f�rence
 */
LCM& LCM::put(const char ch) {
	char buf [2] = {ch, '\0'};
	*this << buf;
	
	return *this;
}

/**
 * �crit une cha�ne � l'index d�sir�, en effa�ant tout avant ou non.
 *
 * @param msg	Message � �crire (cha�ne ASCIIZ compos�e du jeu de l'afficheur)
 * @param index	Index o� �crire le message (0 � 31)
 * @param cb	Effacer tout le contenu affich� avant
 */
void LCM::write(const char* msg, const uint8_t index, const bool cb) {
	if (msg == NULL) {
		return;
	}
	uint8_t msg_len = cp_strlen(msg), // Taille totale de la cha�ne
		up_len = 0, // Taille de la sous-cha�ne sur la premi�re ligne
		i;

	// D�sactiver le `blink'/curseur pendant l'ajout (esth�tique)
	const bool blink_en_bkup = _blink_en, cur_en_bkup = _cur_en;
	en_blink(false);
	en_cur(false);
	
	if (cb) {
		clear();
	}
	if (index >= LCM_FW_TOT_CH || LCM_FW_TOT_CH - index < msg_len) {
		return;
	}
	
	
	if (index < LCM_FW_HALF_CH) {
		if (msg_len + index < LCM_LINE1_ADR + LCM_FW_HALF_CH) {
			up_len = msg_len;
		} else {
			up_len = LCM_FW_HALF_CH - index;
		}
		
		lcmd_ddr_set_addr(index + LCM_LINE1_ADR, _port);
		for (i = 0; i < up_len; ++i) {
			lcmd_write(msg[i], _port);
		}
		
		lcmd_ddr_set_addr(LCM_LINE2_ADR, _port);
		for (i = up_len; i < msg_len; ++i) {
			lcmd_write(msg[i], _port);
		}
	} else {
		lcmd_ddr_set_addr(index + LCM_LINE2_ADR - LCM_FW_HALF_CH,
			_port);
		for (i = 0; i < msg_len; ++i) {
			lcmd_write(msg[i], _port);
		}
	}

	// R�activer le `blink'/curseur
	set_bc_index(_last_bc_index);
	en_blink(blink_en_bkup);
	en_cur(cur_en_bkup);
	
	// Ajuster l'index virtuel
	_last_index = index + msg_len;
}

/**
 * Efface le contenu de l'afficheur LCD.
 *
 */
void LCM::clear() {
	lcmd_disp_clear(_port); // `Display Clear' mat�riel
	_last_index = 0; // R�initialiser l'index virtuel
	set_bc_index(_last_bc_index); // Fixer la position du `blink'/curseur
}

/**
 * Active le `blink' (clignotement noir d'un caract�re).
 *
 * @param state		Nouvel �tat
 */
void LCM::en_blink(const bool state) {
	lcmd_disp_on_off(LCM_C_ON, _cur_en ? LCM_C_ON : LCM_C_OFF,
		state ? LCM_B_ON : LCM_B_OFF, _port);
	_blink_en = state;
}

/**
 * Active le curseur "r�el" (curseur sous un caract�re).
 *
 * @param state		Nouvel �tat
 */
void LCM::en_cur(const bool state) {
	lcmd_disp_on_off(LCM_C_ON, state ? LCM_C_ON : LCM_C_OFF,
		_blink_en ? LCM_B_ON : LCM_B_OFF, _port);
	_cur_en = state;
}

/**
 * Fixe l'index du `blink'/curseur (partag�e).
 *
 * @param index		Nouvel index
 */
void LCM::set_bc_index(const uint8_t index) {
	if (index >= LCM_FW_TOT_CH) {
		return;
	}
	_last_bc_index = index;
	
	if (index < LCM_FW_HALF_CH) {
		lcmd_ddr_set_addr(index + LCM_LINE1_ADR, _port);
	} else {
		lcmd_ddr_set_addr(index + LCM_LINE2_ADR - LCM_FW_HALF_CH,
			_port);
	}
}

/**
 * Construit un nouveau caract�re personnalis�.
 *
 * @param index		Index du nouveau caract�re dans la CG RAM (0 � 7)
 * @param rows		Tableau des rang�es (8 entiers dont les 5 LSBs sont
 *			les 5 pixels d'une rang�e, le premier pixel de chaque
 *			rang�e �tant le LSB et la premi�re rang�e �tant le
 *			premier entier)
 */
void LCM::build_cc(const uint8_t index, const uint8_t* rows) {
	if (index > 7 || rows == NULL) {
		return;
	}
	lcmd_cgr_set_addr(index << 3, _port);

	for (uint8_t i = 0; i < 8; ++i) {
		lcmd_write(rows[i], _port); // �crire la rang�e actuelle
	}
}

/**
 * Raccourci pour ajouter une sous-cha�ne � l'index en cours.
 *
 * @param msg	Sous-cha�ne � joindre (voir "LCM::write")
 * @return	Auto-r�f�rence
 */
LCM& LCM::operator<<(const char* msg) {
	if (msg == NULL) {
		return *this;
	}
	write(msg, _last_index, false);
	
	return *this;
}

/**
 * Raccourci pour ajouter un entier non sign� � l'index en cours.
 *
 * @param u	Entier non sign� � joindre (voir "LCM::write")
 * @return	Auto-r�f�rence
 */
LCM& LCM::operator<<(const uint16_t u) {
	sprintf(_buf, LCM_FW_UINT_DEFFORMAT, u);
	*this << _buf;
	
	return *this;
}

/**
 * Raccourci pour ajouter un entier sign� � l'index en cours.
 *
 * @param i	Entier non sign� � joindre (voir "LCM::write")
 * @return	Auto-r�f�rence
 */
LCM& LCM::operator<<(const int16_t i) {
	sprintf(_buf, LCM_FW_INT_DEFFORMAT, i);
	*this << _buf;
	
	return *this;
}

/**
 * Raccourci pour ajouter un entier sign� � l'index en cours.
 *
 * @param i	Entier non sign� � joindre (voir "LCM::write")
 * @return	Auto-r�f�rence
 */
LCM& LCM::operator<<(const char c) {
	sprintf(_buf, "%c", c);
	*this << _buf;
	
	return *this;
}

/**
 * Raccourci pour remplacer le contenu actuel par une cha�ne (index 0) ou par
 * une cha�ne sp�cifique selon la valeur de `_lpos' et `_lib'.
 *
 * @param msg	Cha�ne � �crire (voir "LCM::write")
 * @return	Sous-cha�ne � ajouter
 */
const char* LCM::operator=(const char* msg) {
	if (msg == NULL) {
		return msg;
	}
	
	write(msg, _li, !_lib);
	if (_lib) {
		_lib = false;
		_li = 0;
	}
	
	return msg;
}

/**
 * Fait en sorte que le prochain operator= appel� �crira � un index sp�cifique.
 *
 * @param index		Index d'�criture pour le prochain operator=
 * @return		Auto-r�f�rence
 */
LCM& LCM::operator[](const uint8_t index) {
	if (index >= LCM_FW_TOT_CH) {
		return *this;
	}
	
	_li = index;
	_lib = true;
	
	return *this;
}

/**
 * Efface un ou plusieurs caract�res avant l'index virtuel en utilisant le
 * caract�re LCM_FW_CL_DEFCHAR.
 *
 * @param rem	Nombre de caract�res � effacer.
 */
void LCM::operator-=(uint8_t rem) {
	if (rem > _last_index) {
		rem = _last_index;
	}
	
	_last_index -= rem;
	for (uint8_t i = 0; i < rem; ++i) {
		put(LCM_FW_CL_DEFCHAR);
	}
	_last_index -= rem;
}
