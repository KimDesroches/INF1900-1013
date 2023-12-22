#include "navigation.h"

Navigation::Navigation(){
    DDRB |= (RIGHT_MOTOR_PIN | LEFT_MOTOR_PIN);
    DDRB |= (RIGHT_MOTOR_DIRECTION | LEFT_MOTOR_DIRECTION);
};

void Navigation::setSpeed(uint8_t rightPercent, uint8_t leftPercent){
    const uint8_t TOP = 255;
    OCR0A = TOP*leftPercent/100;
    OCR0B = TOP*rightPercent/100;
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1) | (1 << WGM00) ;
    TCCR0B |= (1 << CS01);
};

void Navigation::foward(uint8_t rightPercent, uint8_t leftPercent){
    PORTB &= ~(RIGHT_MOTOR_DIRECTION | LEFT_MOTOR_DIRECTION);
    setSpeed(rightPercent, leftPercent);
};
    
void Navigation::reverse(uint8_t rightPercent, uint8_t leftPercent){
    PORTB |= (RIGHT_MOTOR_DIRECTION | LEFT_MOTOR_DIRECTION);
    setSpeed(rightPercent, leftPercent);
};

void Navigation::stop(){
    PORTB &= ~(RIGHT_MOTOR_DIRECTION | LEFT_MOTOR_DIRECTION);
    setSpeed(STOP_SPEED, STOP_SPEED);
}

void Navigation::turnRight(uint8_t duration){
    PORTB &= ~(RIGHT_MOTOR_DIRECTION);
    PORTB |= LEFT_MOTOR_DIRECTION;
    setSpeed(TURN_SPEED, TURN_SPEED);
    delayMs(duration);
};

void Navigation::turnLeft(uint8_t duration){
    PORTB &= ~(LEFT_MOTOR_DIRECTION);
    PORTB |= RIGHT_MOTOR_DIRECTION;
    setSpeed(TURN_SPEED, TURN_SPEED);
    delayMs(duration);
};