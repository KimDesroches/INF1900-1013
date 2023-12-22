#include "music.h"

Music::Music(){
    DDRD |= MUSIC_OUTPUT;
}

double Music::convertNote(uint8_t note){
    uint8_t index = note - 45;
    return _frequenceListe[index];
}

void Music::setNote(uint8_t note){    
    double frequence = convertNote(note);
    OCR2A = (F_CPU / ((2*1024) * frequence)) - 1;
    TCCR2A |= (1 <<WGM21) | (1 << COM2A0);
    TCCR2B |= (1 << CS22) | (1 << CS21)| (1 << CS20);
}

void Music::stopMusic(){         
    TCCR2B = 0;     
}