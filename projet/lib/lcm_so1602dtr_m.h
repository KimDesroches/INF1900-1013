/*
 LCM-SO1602DTR/M driver for the ATmega16 (or any other compatible AVR chip).
 Copyright (C) 2009  Philippe Proulx (philippe.proulx@polymtl.ca)
 
 2012-02-08 - Ajout:
 Broche 0 � 0V reli�e � VO pour un contraste maximal. - L. Tremblay
 
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

#ifndef _LCM_SO1602DTR_M_H
#define _LCM_SO1602DTR_M_H

#include <avr/io.h>

#define LCM_RS		7 // Index de la broche sur RS
#define LCM_RW		6 // Index de la broche sur R/W
#define LCM_EN		5 // Index de la broche sur EN
#define LCM_DB7		4 // Index de la broche sur DB7
#define LCM_DB6		3 // Index de la broche sur DB6
#define LCM_DB5		2 // Index de la broche sur DB5
#define LCM_DB4		1 // Index de la broche sur DB4
#define LCM_VO		0 // Index de la broche sur VO
#define LCM_LINE1_ADR	0x00 // Adresse du d�but de la premi�re ligne
#define LCM_LINE2_ADR	0x40 // Adresse du d�but de la seconde ligne

#define LCM_D_ON	1 // `Display ON'
#define LCM_D_OFF	0 // `Display OFF'
#define LCM_C_ON	1 // `Cursor ON'
#define LCM_C_OFF	0 // `Cursor OFF'
#define LCM_B_ON	1 // `Blink ON'
#define LCM_B_OFF	0 // `Blink OFF'
#define LCM_ID_INC	1 // Incr�menter l'adresse (apr�s chaque transfert)
#define LCM_ID_DEC	0 // D�cr�menter l'adresse (apr�s chaque transfert)
#define LCM_S_ON	1 // `Display Shift ON'
#define LCM_S_OFF	0 // `Display Shift OFF'
#define LCM_SC_SHIFT	1 // `Shift Display'
#define LCM_SC_MOVE	0 // `Move Cursor'
#define LCM_RL_RIGHT	1 // `Shift Right'
#define LCM_RL_LEFT	0 // `Shift Left'
#define LCM_N_DUAL	1 // `Dual Line'
#define LCM_N_SINGLE	0 // `Single Line'

void lcmd_disp_clear(volatile uint8_t*);
void lcmd_disp_home(volatile uint8_t*);
void lcmd_entry_sm(const uint8_t, const uint8_t, volatile uint8_t*);
void lcmd_disp_on_off(const uint8_t, const uint8_t, const uint8_t ,
                      volatile uint8_t*);
void lcmd_disp_cur_shift(const uint8_t, const uint8_t, volatile uint8_t*);
void lcmd_func_set(const uint8_t, const uint8_t, volatile uint8_t*);
void lcmd_cgr_set_addr(const uint8_t, volatile uint8_t*);
void lcmd_ddr_set_addr(const uint8_t, volatile uint8_t*);
void lcmd_write(const uint8_t, volatile uint8_t*);
void lcmd_init_4bit(volatile uint8_t*, volatile uint8_t*);

#endif // _LCM_SO1602DTR_M_H
