/*
auteurs : Ali Yacoubi, Kimia Foroudian, Kim Desroches et Ghadi Falouh

Date : 7 novembre 2023

But: Permettre au robot d'interpreter le code binaire en mémoire externe
et d'executer les instructions associées.
*/

#define F_CPU 8000000
#define MINIMUM_DELAY 25
#define MAX_PWM 255
#define DELAY_READING 10
#define MAX_OPERAND 255
#define MIN_OPERAND 0

#include "../../lib/RS232.h"
#include "../../lib/memoire24.h"
#include "../../lib/led.h"
#include "../../lib/navigation.h"
#include "../../lib/music.h"

enum colorOperand{
    GREEN = 1,
    RED = 2
};

enum instructions{
    DBT  = 0x01,
    ATT  = 0x02,
    DAL  = 0x44,
    DET  = 0x45,
    SGO  = 0x48,
    SAR  = 0x09,
    MAR1 = 0x60,
    MAR2 = 0x61,
    MAV  = 0x62,
    MRE  = 0x63,
    TRD  = 0x64,
    TRG  = 0x65,
    DBC  = 0xC0,
    FBC  = 0xC1,
    FIN  = 0xFF
};

void stopRobot(Led& led, Navigation& nav, Music& music){
    led.off();
    nav.stop();
    music.stopMusic();
}

void executeColor(uint8_t operand, Led& led){
    switch(operand){
        case colorOperand::GREEN:
            led.controlColor(Led::ledColor::GREEN);
            break;
        case colorOperand::RED:
            led.controlColor(Led::ledColor::RED);
            break;
    }
}

void executeInstruction(uint16_t& address, uint8_t instruction, uint8_t operand, Led& led, Navigation& nav, Music& music){
    uint8_t percent = operand * 100/MAX_PWM;
    static uint8_t nIterations = 0;
    static uint8_t counter = 0;
    static uint16_t loopAddress = 0;
    
    switch(instruction){
        case instructions::ATT:             //attendre
            delayMs(MINIMUM_DELAY * operand);
            break;
        case instructions::DAL:             //allumer la del
            executeColor(operand, led);
            break;
        case instructions::DET:             //eteindre la del
            led.off();
            break;
        case instructions::SGO:             //jouer sonorité
            music.setNote(operand);
            break;
        case instructions::SAR:             //arret sonorité
            music.stopMusic();
            break;
        case instructions::MAR1:            //arret des moteurs
            nav.stop();
            break;
        case instructions::MAR2:            //arret des moteurs
            nav.stop();
            break;
        case instructions::MAV:             //avancer
            nav.foward(percent, percent);
            break;
        case instructions::MRE:             //reculer
            nav.reverse(percent, percent);
            break;
        case instructions::TRD:             //tourner à droite (90 degre)
            nav.turn90(Navigation::turnDirection::RIGHT);
            break;
        case instructions::TRG:             //tourner à gauche
            nav.turn90(Navigation::turnDirection::LEFT);
            break;
        case instructions::DBC:             //debut boucle
            loopAddress = address;
            nIterations = operand;
            counter = nIterations;
            break;
        case instructions::FBC:             //fin boucle
            if(counter > 0){
                address = loopAddress;
                counter--;
            }
            break;
        case instructions::FIN:
            stopRobot(led, nav, music);
            break;
    }
    
}


void reading(Memoire24CXXX& memory, Led& led, Navigation& nav, Music& music){
    uint16_t address = 0x00;
    uint8_t instruction = 0;
    uint8_t operand = 0;
    uint8_t byte = 0;
    bool isReading = false;

    memory.lecture(address, &byte);
    address++;
    _delay_ms(DELAY_READING);

    uint16_t size = byte;
    size = size << 8;
    
    memory.lecture(address, &byte);
    address++;
    _delay_ms(DELAY_READING);

    size |= instruction;
    
    while(true){
        
        memory.lecture(address, &instruction);
        
        address++;
        _delay_ms(DELAY_READING);

        memory.lecture(address, &operand);
        /*if(address == 0x0b && operand == 0x00){
            led.controlColor(Led::ledColor::RED);
        }
        */
        address++;
        _delay_ms(DELAY_READING);

        if(instruction == DBT){
            isReading = true;
        }
        if(isReading){
            executeInstruction(address,instruction, operand, led, nav, music);
        
        }
        if(instruction == FIN){
            isReading = false;
            break;
        }
    }
}

int main(){
    Memoire24CXXX memory;
    Led led(&PORTA, &DDRA, PA0, PA1);
    Navigation nav;
    Music music;
    reading(memory, led, nav, music);
}
