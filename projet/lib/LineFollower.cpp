#include "LineFollower.h"

LineFollower::LineFollower(){
    DDRA &= ~(  FURTHER_LEFT_SENSOR |
                MIDDLE_LEFT_SENSOR |
                MIDDLE_SENSOR |
                MIDDLE_RIGHT_SENSOR |
                FURTHER_RIGHT_SENSOR );
}

bool LineFollower::isReadingLine(){
    return ((PINA & FURTHER_LEFT_SENSOR) || (PINA & MIDDLE_LEFT_SENSOR) || (PINA & MIDDLE_SENSOR) || 
            (PINA & MIDDLE_RIGHT_SENSOR) || (PINA & FURTHER_RIGHT_SENSOR) );
}

