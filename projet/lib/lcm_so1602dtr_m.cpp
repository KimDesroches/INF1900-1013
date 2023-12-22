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
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "lcm_so1602dtr_m.h"

#define LCM_CL		~(_BV(LCM_RS) | _BV(LCM_RW) | _BV(LCM_DB7) | \
_BV(LCM_DB6) | _BV(LCM_DB5) | _BV(LCM_DB4))

/**
 * Remet � 0 les broches occup�es par l'afficheur LCD sur un port.
 *
 * @param port	Port AVR occup� par l'afficheur
 */
static inline void _lcm_cp(volatile uint8_t* port) {
	*port &= LCM_CL;
}

/**
 * Active, attend et d�sactive la ligne EN.
 *
 * @param port	Port AVR occup� par l'afficheur
 */
static void _lcm_fast_en(volatile uint8_t* port) {
	*port |= _BV(LCM_EN);
	_delay_loop_1(4); // Laisser le temps � l'afficheur de comprendre EN
	*port &= ~_BV(LCM_EN);
}

/**
 * Envoie une fonction � l'afficheur LCD.
 *
 * @param rs		Valeur de la ligne RS
 * @param rw		Valeur de la ligne R/W
 * @param db		Valeur du `data bus' (DB7-DB0)
 * @param w_10us	Nombre de (10 �s) � attendre apr�s l'envoi
 * @param port		Port AVR occup� par l'afficheur
 */
static void _lcm_function(const uint8_t rs, const uint8_t rw,
                          const uint8_t db, const uint8_t w_10us, volatile uint8_t* port) {
	uint8_t low_bits, high_bits, i;
	
	low_bits = ((db & 0x0f) << LCM_DB4) | (rs << LCM_RS) | (rw << LCM_RW);
	high_bits = ((db >> 4) << LCM_DB4) | (rs << LCM_RS) | (rw << LCM_RW);
	
	_lcm_cp(port);
	*port |= high_bits;
	_lcm_fast_en(port);
	
	_lcm_cp(port);
	*port |= low_bits;
	_lcm_fast_en(port);
	
	for (i = 0; i < w_10us; ++i) {
		_delay_us(10.0);
	}
}

/**
 * Pilote - efface l'affichage en cours avec le caract�re 0x20.
 *
 * @param port		Port AVR occup� par l'afficheur
 */
void lcmd_disp_clear(volatile uint8_t* port) {
	_lcm_function(0, 0, 0x01, 164, port);
}

/**
 * Pilote - effectue un `home' sur l'afficheur.
 *
 * @param port		Port AVR occup� par l'afficheur
 */
void lcmd_disp_home(volatile uint8_t* port) {
	_lcm_function(0, 0, 0x02, 164, port);
}

/**
 * Pilote - fixe le `Entry Mode' de l'afficheur.
 *
 * @param id		Incr�mentation ou d�cr�mentation des adresses
 * @param s		Activation du d�calage d'affichage
 * @param port		Port AVR occup� par l'afficheur
 */
void lcmd_entry_sm(const uint8_t id, const uint8_t s, volatile uint8_t* port) {
	const uint8_t db = (0x04 | (id << 1) | s);
	_lcm_function(0, 0, db, 4, port);
}

/**
 * Pilote - ajuste certains param�tres d'affichage.
 *
 * @param d		Activation de l'affichage
 * @param c		Activation du curseur
 * @param b		Activation du `blink'
 * @param port		Port AVR occup� par l'afficheur
 */
void lcmd_disp_on_off(const uint8_t d, const uint8_t c, const uint8_t b,
                      volatile uint8_t* port) {
	const uint8_t db = (0x08 | (d << 2) | (c << 1) | b);
	_lcm_function(0, 0, db, 4, port);
}

/**
 * Pilote - d�cale l'affichage complet vers la gauche ou vers la droite.
 *
 * @param sc		D�caler l'affichage ou d�placer le curseur
 * @param rl		Droite ou gauche
 * @param port		Port AVR occup� par l'afficheur
 */
void lcmd_disp_cur_shift(const uint8_t sc, const uint8_t rl,
                         volatile uint8_t* port) {
	const uint8_t db = (0x10 | (sc << 3) | (rl << 2));
	_lcm_function(0, 0, db, 4, port);
}

/**
 * Pilote - fixe certains param�tres de l'afficheur LCD.
 *
 * @param dl		`Data Length' de 8 ou 4 bits
 * @param n		`Dual Line' ou `Single Line'
 * @param port		Port AVR occup� par l'afficheur
 */
void lcmd_func_set(const uint8_t dl, const uint8_t n, volatile uint8_t* port) {
	const uint8_t db = (0x20 | (dl << 4) | (n << 3));
	_lcm_function(0, 0, db, 4, port);
}

/**
 * Pilote - fixe l'adresse en cours de la CG RAM.
 *
 * @param addr		Adresse de la CG RAM (0x00 � 0x3f)
 * @param port		Port AVR occup� par l'afficheur
 */
void lcmd_cgr_set_addr(const uint8_t addr, volatile uint8_t* port) {
	const uint8_t db = (0x40 | addr) & ~_BV(7);
	_lcm_function(0, 0, db, 4, port);
}

/**
 * Pilote - fixe l'adresse en cours de la DD RAM.
 *
 * @param addr		Adresse de la DD RAM (0x00 � 0x27 et 0x40 � 0x67)
 * @param port		Port AVR occup� par l'afficheur
 */
void lcmd_ddr_set_addr(const uint8_t addr, volatile uint8_t* port) {
	const uint8_t db = (0x80 | addr);
	_lcm_function(0, 0, db, 4, port);
}

/**
 * Pilote - �crit un octet � l'adresse en cours de la CG RAM ou de la DD RAM.
 *
 * @param data		Octet � �crire
 * @param port		Port AVR occup� par l'afficheur
 */
void lcmd_write(const uint8_t data, volatile uint8_t* port) {
	_lcm_function(1, 0, data, 4, port);
}

/**
 * Pilote - initialise l'afficheur LCD avec une interface 4-bit et `Dual Line'.
 *
 * @param ddr		`Data Direction Register' AVR occup� par l'afficheur
 * @param port		Port AVR occup� par l'afficheur
 */
void lcmd_init_4bit(volatile uint8_t* ddr, volatile uint8_t* port) {
	_delay_ms(15.0);
	
	_lcm_cp(ddr);
	*ddr |= ~LCM_CL | _BV(LCM_EN) | _BV(LCM_VO);
	
	_lcm_cp(port);
	*port |= _BV(LCM_DB5) | _BV(LCM_DB4);
	*port &= ~_BV(LCM_VO);
	_lcm_fast_en(port);
	_delay_ms(4.1);
    
	_lcm_fast_en(port);
	_delay_ms(0.1);
    
	_lcm_fast_en(port);
	_delay_us(40.0);
    
	_lcm_cp(port);
	*port |= _BV(LCM_DB5);
	_lcm_fast_en(port);
	_delay_us(40.0);
	
	_lcm_function(0, 0, 0x2c, 4, port);
	lcmd_disp_on_off(LCM_D_OFF, LCM_C_OFF, LCM_B_OFF, port);
	lcmd_disp_clear(port);
	lcmd_entry_sm(LCM_ID_INC, LCM_S_OFF, port);
	lcmd_disp_on_off(LCM_D_ON, LCM_C_OFF, LCM_B_OFF, port);
}
