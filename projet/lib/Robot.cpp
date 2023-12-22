#include "Robot.h"

Robot::Robot(){
    DDRA = (1 << PA5); 
    _timer = Timer(FREQUENCE, TIMER_PRESCALER, F_CPU);
}

uint8_t Robot::getPosition(){
    return _position;
}

Node::directions Robot::getDirection(){
    return _direction;
}

void Robot::setPosition(uint8_t position){
    _position = position;
}

void Robot::setDirection(Node::directions direction){
    _direction = direction;
}

void Robot::doNothing(){
    _navigation.stop();
    _led.off();
    _music.stopMusic();
}