/*
 * Nom: game.h
 * Description: Classe permettant l'initialisation de l'épreuve. 
 * Équipe : 1013
 * Auteurs : Kim Desroches, Ghadi Falouh, Kimia Foroudian et Ali Yacoubi
 * 
 Table d'états:
+--------------------+----+----+------+---------------------+----------------------+
|   Current State    | D2 | D3 | B2   |     Next State      |   Robot Behaviour    |
+--------------------+----+----+------+---------------------+----------------------+
| START              | 1  |  0 |  X   | CORNER              | startCornerChallenge |
| START              | 0  |  1 |  X   | INITIALIZE_TRAJECT  | determineLine        |
| CORNER             | X  |  X |  X   | START               | Choose Challenge     |
| INITIALIZE_TRAJECT | X  |  1 |  0   | INITIALIZE_TRAJECT  | determineLine        |
| INITIALIZE_TRAJECT | X  |  X |  1   | SELECTION           | determineColumn      |
| SELECTION          | X  |  1 |  0   | SELECTION           | determineColumn      |
| SELECTION          | X  |  X |  1   | VALIDATION          | confirmChoice        |
| VALIDATION         | X  |  1 |  0   | VALIDATION          | confirmChoice        |
| VALIDATION         | X  |  0 |  1   | TRAJECT             | processMovement      |
| TRAJECT            | X  |  X |  X   | INITIALIZE_TRAJECT  | determineLine        |
+--------------------+----+----+------+---------------------+----------------------+


Description du comportement du robot dans les différents états (Robot Behaviour):

Dans l’état Start, l’utilisateur pourra choisir l’épreuve que le robot doit effectuer. 
Dans les états suivants, le comportement du robot est décrit à l’aide de différentes fonctions. 
La fonction startCornerChallenge va commencer l’épreuve de la détection des coins. 
La fonction determineLine va déterminer la ligne où devra se rendre le robot et 
la fonction determineColumn va déterminer la colonne.
Par la suite, la fonction confirmChoice permettra la confirmation des coordonnées à atteindre.
La fonction processMovement va effectuer le trajet, une fois que les coordonnées seront confirmées.
*/

#pragma once

#define DEMO_DDR	DDRC
#define DEMO_PORT	PORTC

#define SECOND_LINE 16
#define TIME_NODE_1 7
#define TIME_NODE_2 4

#define START_DELAY 2000
#define SILENCE_DELAY 100
#define DESTINATION_NOTE_DELAY 200
#define OBSTACLE_DELAY 10
#define REVERSE_DELAY 400

#define OBSTACLE_NOTE 60
#define DESTINATION_NOTE 84

#define N_OBSTACLE_READING 50
#define READING_DISTANCE 14
#define DETECTION_SENSOR_PIN PA5
#define N_LINES 4
#define N_COLUMNS 7
#define N_DESTINATION_NOTE 4

#include <avr/io.h>
#include "Robot.h"
#include "Node.h"
#include "Trajectory.h"
#include "Corner.h"
#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"

static LCM screen(&DEMO_DDR, &DEMO_PORT); 

class Game{
public:
    Game(); 
    enum class selectionState {START, CORNER, INITIALIZE_TRAJECT, SELECTION, VALIDATION, TRAJECT};  
    void determineLine(volatile bool& isInterrupt, volatile bool& isSelection);   
    void determineColumn(volatile bool& isValidation, volatile bool& isSelection);
    void confirmChoice(volatile bool& isValidation, volatile bool& isSelection);
      
    void processMovement(Node& targetNode, volatile uint8_t& counter);
    void executeState(volatile bool& isInterrupt,volatile bool& isSelection, volatile bool& isValidation, 
                      volatile uint8_t& counter, volatile  bool& isTimerDone, volatile bool& isCornerChallenge);    
    uint8_t convertToNode();  
    void convertDirection();
    void initializeWay();    
    bool isObstacle();
    void playNewWay();
           
private:   
    uint8_t _line= 1;
    uint8_t _column = 1;
    bool _finaleValidation = true;
    selectionState _robotState = selectionState::START;
    Robot _robot;
    Trajectory _traject;
    Corner _corner;
    Node _way[28];
    uint8_t _nElement = 0;
    Node _nextNode; 
};
