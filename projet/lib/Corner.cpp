#include "Corner.h"

Corner::Corner(){}

void Corner::turnBack(Robot& robot, Navigation::TurnDirection firstDirection, Navigation::TurnDirection secondDirection){
    bool isLine = true;
    robot._navigation.turnJunction(firstDirection);
    while(isLine){
         isLine = robot._navigation.followLine();
    }
    robot._navigation.turnJunction(secondDirection);
    robot._navigation.stop();
}

void Corner::returnToCorner(Robot& robot, CornerPath corner){
    robot._music.setNote(DETECTION_NOTE);
    delayMs(SOUND_DELAY);
    robot._music.stopMusic();
    robot._led.controlColor(Led::LedColor::GREEN);

    switch (corner) {
        case CornerPath::TOP_LEFT_SOUTH:
            turnBack(robot,Navigation::TurnDirection::RIGHT,Navigation::TurnDirection::LEFT);
            screenCorner.write("(1,1)");
            screenCorner.write("SOUTH", SECOND_LINE);
            break;
        case CornerPath::TOP_LEFT_EAST:
            turnBack(robot,Navigation::TurnDirection::LEFT, Navigation::TurnDirection::RIGHT);
            screenCorner.write("(1,1)");
            screenCorner.write("EAST", SECOND_LINE);
            break;
        case CornerPath::TOP_RIGHT_WEST:
            turnBack(robot,Navigation::TurnDirection::LEFT, Navigation::TurnDirection::LEFT);
            screenCorner.write("(1,7)");
            screenCorner.write("WEST", SECOND_LINE);
            break;
        case CornerPath::TOP_RIGHT_SOUTH:
            turnBack(robot,Navigation::TurnDirection::LEFT, Navigation::TurnDirection::RIGHT);
            screenCorner.write("(1,7)");
            screenCorner.write("SOUTH", SECOND_LINE);
            break;
        case CornerPath::BOTTOM_LEFT_EAST:
            turnBack(robot,Navigation::TurnDirection::RIGHT, Navigation::TurnDirection::LEFT);
            screenCorner.write("(4,1)");
            screenCorner.write("EAST", SECOND_LINE);
            break;
        case CornerPath::BOTTOM_LEFT_NORTH:
            turnBack(robot,Navigation::TurnDirection::LEFT, Navigation::TurnDirection::RIGHT);
            screenCorner.write("(4,1)");
            screenCorner.write("NORTH", SECOND_LINE);
            break;
        case CornerPath::BOTTOM_RIGHT_NORTH:
            turnBack(robot,Navigation::TurnDirection::RIGHT, Navigation::TurnDirection::LEFT);
            screenCorner.write("(4,7)");
            screenCorner.write("NORTH", SECOND_LINE);
            break;
        case CornerPath::BOTTOM_RIGHT_WEST:
            turnBack(robot, Navigation::TurnDirection::LEFT, Navigation::TurnDirection::RIGHT);
            screenCorner.write("(4,7)");
            screenCorner.write("WEST", SECOND_LINE);
            break;
    }
}


void Corner::findCorner(Robot& robot, volatile uint8_t& counter, volatile bool& isTimerDone){  
    if(_firstSegmentLeft && counter > FIRST_SEGMENT_TIME ){
        returnToCorner(robot, CornerPath::TOP_RIGHT_WEST);
    }
    else if (_firstSegmentLeft && counter < FIRST_SEGMENT_TIME){
        returnToCorner(robot, CornerPath::TOP_LEFT_SOUTH);
    }
    else if (_secondSegmentLeft && counter < SECOND_SEGMENT_TIME) {
        returnToCorner(robot, CornerPath::BOTTOM_LEFT_EAST);
    }
    else if (_thirdSegmentLeft){
        returnToCorner(robot, CornerPath::BOTTOM_RIGHT_NORTH);
    }    
    else if (_firstSegmentRight && _secondSegmentRight && _thirdSegmentRight){
        returnToCorner(robot, CornerPath::BOTTOM_RIGHT_WEST);
    }
    else if (_firstSegmentRight && _thirdSegmentRight){
        returnToCorner(robot, CornerPath::TOP_RIGHT_SOUTH);
    }
    else if (_secondSegmentRight && _thirdSegmentRight){
        returnToCorner(robot, CornerPath::TOP_LEFT_EAST);
    }
    else if (_firstSegmentRight){
        returnToCorner(robot, CornerPath::BOTTOM_LEFT_NORTH);
    }
    /*else {
        counter = 0;
        restartCornerChallenge(robot, , counter, isTimerDone);
    }*/
} 
    
void Corner::checkJunction(volatile uint8_t& counter){   //verifie s'il y a intersection
    if( (PINA == JUNCTION_LEFT) || (PINA == BIG_JUNCTION_LEFT)){
        if (counter < FIRST_SEGMENT_TIME){
            _firstSegmentLeft = true;
        }
        else if (counter < SECOND_SEGMENT_TIME){
            _secondSegmentLeft = true;
        }
        else if (counter > SECOND_SEGMENT_TIME){
            _thirdSegmentLeft = true;
        }
    }
    else if(PINA == JUNCTION_RIGHT ||  PINA == BIG_JUNCTION_RIGHT){
        if(counter < FIRST_SEGMENT_TIME ){
            _firstSegmentRight = true;
        }
        else if (counter < SECOND_SEGMENT_TIME){
            _secondSegmentRight = true;
        }
        else if (counter > SECOND_SEGMENT_TIME){
            _thirdSegmentRight = true;
        }
    }    
}

//revoir si pertinent ???
void Corner::restartCornerChallenge(Robot& robot, volatile uint8_t& counter, volatile bool& isTimerDone){
    robot._navigation.turn180();
    robot._navigation.followLine();
    robot._navigation.turn180();
    robot._navigation.stop();
    startCornerChallenge(robot, counter, isTimerDone);
}

void Corner::startCornerChallenge(Robot& robot, volatile uint8_t& counter, volatile bool& isTimerDone){
    robot._timer.startTimer(isTimerDone);
    robot._navigation.startBoost();
    bool isLine = true;

    while(isLine){
        checkJunction(counter); 
        isLine = robot._navigation.followLine();
    }
    cli();
    findCorner(robot, counter, isTimerDone);    
}