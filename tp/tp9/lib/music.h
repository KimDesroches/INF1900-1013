/*
auteurs : Ali Yacoubi, Kimia Foroudian, Kim Desroches et Ghadi Falouh

Date : 8 novembre 2023

But:  contrôler le son émis. La classe permet de produire differentes
      sonorités en générant une fréquence donnée.

*/
#pragma once

#define F_CPU 8000000UL

#include <avr/io.h>

#define MUSIC_OUTPUT (1<< PD6) | (1<< PD7)

class Music{
public:        
    Music();
    double convertNote(uint8_t note);
    void setNote(uint8_t note);
    void stopMusic();

private:
    double _frequenceListe [36] = {
        116.54, 123.47, 130.81, 138.59, 146.83, 155.56, 164.81, 174.61, 185.00, 196.00,
        207.65, 220.00, 233.08, 246.94, 261.63, 277.18, 293.66, 311.13, 329.63, 349.23,
        369.99, 392.00, 415.30, 440.00, 466.16, 493.88, 523.25, 554.37, 587.33, 622.25,
        659.26, 698.46, 739.99, 783.99, 830.61, 880.00
    };
};