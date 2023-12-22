#include "Navigation.h"

Navigation::Navigation(){
    DDRB |= (RIGHT_MOTOR_PIN | LEFT_MOTOR_PIN);
    DDRB |= (RIGHT_MOTOR_DIRECTION | LEFT_MOTOR_DIRECTION);
}

void Navigation::setSpeed(uint8_t leftPercent, uint8_t rightPercent){
    const uint8_t TOP = 255;
    OCR0A = TOP*rightPercent/100;
    OCR0B = TOP*leftPercent/100;    
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00) ;
    TCCR0B |= (1 << CS01);
}

void Navigation::setPwm(Direction direction,uint8_t leftPercent, uint8_t rightPercent ){
    switch (direction){
    case Direction::FORWARD:
        PORTB &= ~(RIGHT_MOTOR_DIRECTION | LEFT_MOTOR_DIRECTION);
        break;
    case Direction::REVERSE:
        PORTB |= (RIGHT_MOTOR_DIRECTION | LEFT_MOTOR_DIRECTION);
        break;
    }
    setSpeed(leftPercent, rightPercent);
}    

void Navigation::forward(){
    setPwm(Direction::FORWARD, NORMAL_SPEED, NORMAL_SPEED+RIGHT_MOTOR_AJUST_SPEED);
}

void Navigation::reverse(){
    setPwm(Direction::REVERSE, NORMAL_SPEED, NORMAL_SPEED+RIGHT_MOTOR_AJUST_SPEED);
}

void Navigation::stop(){
    delayMs(STOP_DELAY);  
    TCCR0A &= ~(1 << COM0A1 | 1 << COM0B1);
    TCCR0A &= ~(1 << COM0A0 | 1 << COM0B0);
}

void Navigation::ajustToRight(){  
    setPwm(Direction::FORWARD, 52, 40);
}

void Navigation::ajustToExtremeRight(){  
    setPwm(Direction::FORWARD, 50, 45);
}

void Navigation::ajustToLeft(){
    setPwm(Direction::FORWARD, 35, 60);
}

void Navigation::ajustToExtremeLeft(){
    setPwm(Direction::FORWARD, 45, 60);
}

void Navigation::turn(TurnDirection direction, uint8_t forwardSpeed, uint8_t reverseSpeed){
    switch (direction) {
        case TurnDirection::RIGHT:
            PORTB &= ~(LEFT_MOTOR_DIRECTION);
            PORTB |= RIGHT_MOTOR_DIRECTION;
            setSpeed(forwardSpeed, reverseSpeed);
            break;
        case TurnDirection::LEFT:
            PORTB &= ~(RIGHT_MOTOR_DIRECTION);
            PORTB |= LEFT_MOTOR_DIRECTION;
            setSpeed(reverseSpeed, forwardSpeed);
            break;
    }
}

bool Navigation::followLine(){
    if (!(_line.isReadingLine())) {
        delayMs(STOP_DELAY);

        if (!(_line.isReadingLine())) {
            stop();
            return false;
        }
    }
    else if (!(PINA & MIDDLE_SENSOR)) {
        if(PINA & FURTHER_LEFT_SENSOR) {
            ajustToExtremeLeft();        
        }
        else if(PINA & MIDDLE_LEFT_SENSOR) {
            ajustToLeft(); 
        }
        else if (PINA & FURTHER_RIGHT_SENSOR) {
            ajustToExtremeRight();        
        }
        else if (PINA & MIDDLE_RIGHT_SENSOR) {
            ajustToRight();
        }
    }
    else {
        forward();
    }
    return true;
}

void Navigation::startBoostTurn(TurnDirection direction){
    turn(direction, BOOST_SPEED, BOOST_SPEED+RIGHT_MOTOR_AJUST_SPEED);
    delayMs(BOOST_DELAY);
}

void Navigation::startBoost(){
    setPwm(Direction::FORWARD, BOOST_SPEED, BOOST_SPEED+RIGHT_MOTOR_AJUST_SPEED);
    delayMs(BOOST_DELAY);
}


void Navigation::turnJunction(TurnDirection direction, bool isMovingForward){
    if(isMovingForward){
        forwardToTurn();
    };

    startBoostTurn(direction);
    switch (direction) {
        case TurnDirection::LEFT:
            while(!(PINA & FURTHER_LEFT_SENSOR)){
                turn(direction, TURN_SPEED+RIGHT_MOTOR_AJUST_SPEED, TURN_SPEED);
            }
            break;
        case TurnDirection::RIGHT:
            while(!(PINA & FURTHER_RIGHT_SENSOR)){
                turn(direction, TURN_SPEED, TURN_SPEED+RIGHT_MOTOR_AJUST_SPEED);
            }
            break;
    }
    stop();
    delayMs(TURN_DELAY);

    ajustAfterTurn(direction);
    stop();
    delayMs(TURN_DELAY);
}

bool Navigation::isIntersection(){
    return (PINA & JUNCTION_LEFT || PINA & BIG_JUNCTION_LEFT || PINA & JUNCTION_RIGHT || 
            PINA & BIG_JUNCTION_RIGHT || PINA & JUNCTION_LEFT_RIGHT);
}

void Navigation::forwardToTurn(){
    stop();     
    startBoost();
    forward();    
    delayMs(FORWARD_TO_TURN_DELAY);
    stop();
    delayMs(WAITING_DELAY);
}

void Navigation::arriveToSegment(volatile uint8_t& counter, uint8_t time){
    bool isLine = true;
    counter = 0;
    while(isLine){
         isLine = followLine();
         if(counter > time){
            stop();  
            break; 
        }
    }
}

void Navigation::switchNode(volatile uint8_t& counter, uint8_t time){
    delayMs(100);
    if (!(_line.isReadingLine())){
        forwardToTurn();
    }
    else {
        counter = 0;
        while(counter < time){
            followLine();
            if (!(_line.isReadingLine())){
                forwardToTurn();
            }
        }
        stop();
    }
}

void Navigation::ajustAfterTurn(TurnDirection direction){
    while (!(PINA & MIDDLE_SENSOR)) {
        if(PINA & FURTHER_LEFT_SENSOR) {
            ajustToExtremeLeft();        
        }
        else if(PINA & MIDDLE_LEFT_SENSOR) {
            ajustToLeft(); 
        }
        else if (PINA & FURTHER_RIGHT_SENSOR) {
            ajustToExtremeRight();        
        }
        else if (PINA & MIDDLE_RIGHT_SENSOR) {
            ajustToRight();
        }
    }
}

void Navigation::turn180(){
    startBoostTurn(TurnDirection::LEFT);
    turn(TurnDirection::LEFT, TURN_SPEED+RIGHT_MOTOR_AJUST_SPEED, TURN_SPEED);
    delayMs(TURN_180_DELAY);
    turnJunction(TurnDirection::LEFT, false);
}