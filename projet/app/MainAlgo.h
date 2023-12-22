/*
 * Nom: MainAlgo.h
 * Description: Main du projet final.
 * Équipe : 1013
 * Auteurs : Kim Desroches, Ghadi Falouh, Kimia Foroudian et Ali Yacoubi
 * 
 * Le cavalier DbgEN et MemEN sont retirés de la carte mère.
 * L'écran LCD est connecté sur les broches du port C en sortie.
 * Le capteur de distance est connecté à la broche A6 (PA5) en entrée.
*/

#define F_CPU 8000000

#define MASK_BUTTONB2 (1 << PB2)
#define MASK_BUTTOND2 (1 << PD2)
#define MASK_BUTTOND3 (1 << PD3)
#define DEBOUNCE_DELAY1 70
#define DEBOUNCE_DELAY2 100

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "Button.h"
#include "Game.h"
#include "Led.h"

volatile bool isInterrupt = false;
volatile bool isSelection = false;
volatile bool isValidation = false;

volatile uint8_t counter = 0;
volatile bool isTimerDone = false;
volatile bool isCornerChallenge = false;