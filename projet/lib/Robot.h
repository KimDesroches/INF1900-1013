/*
 * Nom: Robot.h
 * Description: Classe permettant l'initialisation un robot pour accéder aux méthodes des 
 *              différents objets (Navigation, Led, Music, can, Timer) en attribut de la classe.
 * Équipe : 1013
 * Auteurs : Kim Desroches, Ghadi Falouh, Kimia Foroudian et Ali Yacoubi
 * 
 * _position représente le node initial sur lequel le robot commence un trajet.
*/
#pragma once

#define TIMER_PRESCALER 64
#define FREQUENCE 4

#include "Navigation.h"
#include "Led.h"
#include "Music.h"
#include "Timer.h"
#include "Button.h"
#include "Node.h"
#include "can.h"

class Robot{       
public:
    Robot();
    uint8_t getPosition();
    Node::directions getDirection();
    void setDirection(Node::directions direction);
    void setPosition(uint8_t position);
    //Le robot ne fait rien, donc tout est éteint
    void doNothing();
    
    Navigation _navigation;
    Led _led;
    Music _music;
    can _can;
    Timer _timer;

private:
    uint8_t _position = 0;
    Node::directions _direction = Node::directions::SOUTH; 
};