/*
 * Nom: Navigation.h
 * Description: Classe pour effectuer le contrôle des moteurs (des roues) 
 *              du robot d’où son nom (permet la navigation). Le timer0 
 *              est utilisé pour générer les signaux PWM. Le mode choisi 
 *              est PWM phase correct avec une valeur top de 0xFF et un 
 *              prescaler de 8. Le mode de comparaison est « Clear OC0A 
 *              and OC0B on compare match ». 
 * Équipe : 1013
 * Auteurs : Kim Desroches, Ghadi Falouh, Kimia Foroudian et Ali Yacoubi
 *
 *  Identification matérielles (Broches I/O) :
 *  - La broche B4 (PB3) est connectée avec E de JM1.
 *  - La broche B6 (PB5) est connectée avec D de JM1.
 *  - La broche B5 (PB4) est connectée avec E de JM2.
 *  - La broche B7 (PB6) est connectée avec D de JM2.
*/

#pragma once

#include <stdint.h>
#include <avr/io.h>
#include "Delay.h"
#include "LineFollower.h"

#define RIGHT_MOTOR_PIN (1 << PB3)
#define LEFT_MOTOR_PIN (1 << PB4)
#define RIGHT_MOTOR_DIRECTION (1 << PB5)
#define LEFT_MOTOR_DIRECTION (1 << PB6)

#define STOP_DELAY 100
#define TURN_180_DELAY 2000   
#define BOOST_DELAY 100
#define WAITING_DELAY 200
#define TURN_DELAY 300
//To go forward if there is no line detected
#define FORWARD_TO_TURN_DELAY 900
#define HALF_NODE_TIME 7

enum Pwm {
        NORMAL_SPEED                = 50,
        RIGHT_MOTOR_AJUST_SPEED     = 8,    //roue droite plus lente
        BOOST_SPEED                 = 90,
        TURN_SPEED                  = 43,
};

enum SensorReading {
        JUNCTION_LEFT       = 0b00000111,
        BIG_JUNCTION_LEFT   = 0b00001111,
        JUNCTION_RIGHT      = 0b00011100,
        BIG_JUNCTION_RIGHT  = 0b00011110,  
        JUNCTION_LEFT_RIGHT = 0b00011111
};

class Navigation{
public:
    enum class TurnDirection {LEFT, RIGHT};
    enum class Direction {FORWARD, REVERSE};
    Navigation();
    void setSpeed(uint8_t leftPercent, uint8_t rightPercent);
    void setPwm(Direction direction,uint8_t leftPercent, uint8_t rightPercent);
    void forward();
    void reverse();
    void stop();
    /*Avancer un peu avant de tourner quand aucune ligne n'est detecté*/
    void forwardToTurn();
    /*Mettre les moteurs au maximum pour vaincre la friction des roues pour avancer*/
    void startBoost();
    /*Mettre les moteurs au maximum pour vaincre la friction des roues pour tourner*/
    void startBoostTurn(TurnDirection direction);
    void turn180();
    bool followLine();
    void turn(TurnDirection direction, uint8_t forwardSpeed, uint8_t reverseSpeed);
    /*Tourner sur une ligne*/
    void turnJunction(TurnDirection direction, bool isMovingForward = true);
    bool isIntersection();
    /*Place le nez du robot sur le point*/
    void arriveToSegment(volatile uint8_t& counter, uint8_t time);
    /*Place le centre de rotation du robot sur le point après l'appel de arriveToSegment()*/
    void switchNode(volatile uint8_t& counter, uint8_t time);
    void ajustAfterTurn(TurnDirection direction);
    LineFollower _line;

private:
    void ajustToRight();
    void ajustToLeft();
    void ajustToExtremeRight();
    void ajustToExtremeLeft();
};
