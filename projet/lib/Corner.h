/*
 * Nom: Corner.h
 * Description: Classe permettant d'identifier un coin dans l'épreuve finale
 * Équipe : 1013
 * Auteurs : Kim Desroches, Ghadi Falouh, Kimia Foroudian et Ali Yacoubi
 * 
 * Les variables booléennes représentent à quel(s) endroit(s) il y a un intersection.
*/
#pragma once

#define FIRST_SEGMENT_TIME 12 
#define SECOND_SEGMENT_TIME 24
#define SOUND_DELAY 1000
#define DETECTION_NOTE 80

//Pour l'ecran LCD
#define DEMO_DDR	DDRC // `Data Direction Register' AVR occupé par l'aff.
#define DEMO_PORT	PORTC // Port AVR occupé par l'afficheur
#define SECOND_LINE 16

#include "Robot.h"
#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"

static LCM screenCorner(&DEMO_DDR, &DEMO_PORT);

class Corner {
public:
    enum class CornerPath{
        TOP_LEFT_SOUTH,
        TOP_LEFT_EAST,
        TOP_RIGHT_WEST,
        TOP_RIGHT_SOUTH,
        BOTTOM_LEFT_EAST,
        BOTTOM_LEFT_NORTH,
        BOTTOM_RIGHT_NORTH,
        BOTTOM_RIGHT_WEST
    };
    Corner();
    /*Function to return to the initial corner after finding which corner it is*/
    void turnBack(Robot& robot, Navigation::TurnDirection firstDirection, Navigation::TurnDirection secondDirection);
    /* Function that detect if there is an intersection on the path*/
    void checkJunction(volatile uint8_t& counter);
    /*Function that do all the corner identification*/
    void startCornerChallenge(Robot& robot, volatile uint8_t& counter, volatile bool& isTimerDone);
    /*Function that identify which corner it is*/
    void findCorner(Robot& robot, volatile uint8_t& counter, volatile bool& isTimerDone);
    /* Function to return to the initial corner with the LCD display*/
    void returnToCorner(Robot& robot, CornerPath corner);
    /*Function to start again to find the right corner*/
    void restartCornerChallenge(Robot& robot, volatile uint8_t& counter, volatile bool& isTimerDone);

private:
    bool _firstSegmentLeft = false;
    bool _secondSegmentLeft = false;
    bool _thirdSegmentLeft = false;
    bool _firstSegmentRight = false;
    bool _secondSegmentRight = false;
    bool _thirdSegmentRight = false;
};