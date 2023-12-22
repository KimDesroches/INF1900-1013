#include "Game.h"

Game::Game(){        
    _traject.InitializeMap();       
}

bool Game::isObstacle(){
    uint16_t sum = 0; 
    for(uint8_t i = 0; i < N_OBSTACLE_READING; i++){
        sum +=  _robot._can.lecture(DETECTION_SENSOR_PIN);
        delayMs(OBSTACLE_DELAY);
    }
    return (sum/N_OBSTACLE_READING >= READING_DISTANCE);
}

void Game::playNewWay(){   
        _robot._navigation.stop();
        _traject.changeMap(_nextNode);
        initializeWay();
        
        _traject.findWay(_way, _robot.getPosition(), convertToNode());
        _nElement = _traject.getNElement(_way) - 1;

        _robot._music.setNote(OBSTACLE_NOTE);
        delayMs(START_DELAY);
        _robot._music.stopMusic();
}

void Game::processMovement(Node& targetNode, volatile uint8_t& counter){
    if(_robot.getPosition() == targetNode.getNumber()){
        return;
    }
    bool isMovingForward = true;    
    bool isTurning = false;

    Node::directions potentielDirection = Node::directions::EAST;
    Node::directions targetDirection = Node::directions::SOUTH;    
    
    if(_robot.getPosition() == targetNode.getNumber() - 1){
        targetDirection = Node::directions::EAST;        
    }else if(_robot.getPosition() == targetNode.getNumber() + 1){
        targetDirection = Node::directions::WEST;        
    }else if(_robot.getPosition() == targetNode.getNumber() + 7){
        targetDirection = Node::directions::NORTH;        
    }else if(_robot.getPosition() == targetNode.getNumber() - 7){
        targetDirection = Node::directions::SOUTH;        
    }
    if(_robot.getDirection() == Node::directions::SOUTH){
        if(targetDirection == Node::directions::EAST) {
            potentielDirection = Node::directions::EAST;
            isMovingForward = false;         
            _robot._navigation.turnJunction(Navigation::TurnDirection::LEFT,isMovingForward);        
            isTurning = true;
        }
        else if(targetDirection == Node::directions::WEST){    
            potentielDirection = Node::directions::WEST;
            isMovingForward = false;                    
            _robot._navigation.turnJunction(Navigation::TurnDirection::RIGHT,isMovingForward);
            isTurning = true;
        }
        else if(targetDirection == Node::directions::SOUTH){
            if(isObstacle()){
                playNewWay();
                return;
            } 
            potentielDirection = Node::directions::SOUTH;
            _robot._navigation.startBoost();
            _robot._navigation.arriveToSegment(counter, TIME_NODE_1);
            _robot._navigation.switchNode(counter, TIME_NODE_2);  
        }
        else {
            isTurning = true;
            _robot._navigation.turn180();
            potentielDirection = Node::directions::NORTH;
        }
    }
    else if(_robot.getDirection() == Node::directions::NORTH){   
        if(targetDirection == Node::directions::EAST) {         
            potentielDirection = Node::directions::EAST;
            isTurning = true;
            isMovingForward = false;            
            _robot._navigation.turnJunction(Navigation::TurnDirection::RIGHT, isMovingForward);
        }
        else if(targetDirection == Node::directions::WEST) {         
            potentielDirection = Node::directions::WEST;
            isMovingForward = false;        
            isTurning = true;
            _robot._navigation.turnJunction(Navigation::TurnDirection::LEFT, isMovingForward);        
        }
        else if(targetDirection == Node::directions::NORTH){
            if(isObstacle()){
                playNewWay();
                return;
            }
            potentielDirection = Node::directions::NORTH;
            _robot._navigation.startBoost();
            _robot._navigation.arriveToSegment( counter, TIME_NODE_1);
            _robot._navigation.switchNode( counter, TIME_NODE_2);                    
        }
        else {
            isTurning = true;
            _robot._navigation.turn180();
            potentielDirection = Node::directions::SOUTH;
        }
    }
    else if(_robot.getDirection() == Node::directions::EAST){
        if(targetDirection == Node::directions::NORTH){      
            potentielDirection = Node::directions::NORTH;
            isMovingForward = false;  
            isTurning = true;               
            _robot._navigation.turnJunction(Navigation::TurnDirection::LEFT, isMovingForward);        
        }
        else if(targetDirection == Node::directions::SOUTH){         
            potentielDirection = Node::directions::SOUTH;
            isMovingForward = false;   
            isTurning = true;         
            _robot._navigation.turnJunction(Navigation::TurnDirection::RIGHT,isMovingForward);
        }
        else if(targetDirection == Node::directions::EAST){  
            if(isObstacle()){
                playNewWay();
                return;
            }
            potentielDirection = Node::directions::EAST;
            _robot._navigation.startBoost();
            _robot._navigation.arriveToSegment(counter, TIME_NODE_1);
            _robot._navigation.switchNode(counter, TIME_NODE_2);        

        }
        else {
            isTurning = true;
            _robot._navigation.turn180();
            potentielDirection = Node::directions::WEST;
        }
    }
    else if(_robot.getDirection() == Node::directions::WEST){        
        if(targetDirection == Node::directions::NORTH){        
            potentielDirection = Node::directions::NORTH;
            isMovingForward = false;                     
            _robot._navigation.turnJunction(Navigation::TurnDirection::RIGHT, isMovingForward);
            isTurning = true;
        }
        else if(targetDirection == Node::directions::SOUTH){
            potentielDirection = Node::directions::SOUTH;
            isMovingForward = false;                 
            _robot._navigation.turnJunction(Navigation::TurnDirection::LEFT, isMovingForward);        
            isTurning = true;
        }
        else if(targetDirection == Node::directions::WEST){
            if(isObstacle()){
                playNewWay();
                return;
            }
            potentielDirection = Node::directions::WEST;
            _robot._navigation.startBoost();
            _robot._navigation.arriveToSegment(counter, TIME_NODE_1);
            _robot._navigation.switchNode(counter, TIME_NODE_2);        

        }
        else {
            isTurning = true;
            _robot._navigation.turn180();
            potentielDirection = Node::directions::EAST;
        }
    }     
        delayMs(WAITING_DELAY);
        counter = 0; 
        _robot.setDirection(potentielDirection);

        if(isTurning){
            if(isObstacle()){
                 playNewWay();
                 return;
            }else{                
                _robot._navigation.startBoost();
                _robot._navigation.arriveToSegment(counter, TIME_NODE_1);
                _robot._navigation.switchNode(counter, TIME_NODE_2);
                _robot.setPosition(targetNode.getNumber());                  
            }
        }
        else {
            _robot.setPosition(targetNode.getNumber());  
        } 
        _robot._navigation.stop();        
        delayMs(WAITING_DELAY);  
}        



uint8_t Game::convertToNode(){
    return (_line - 1) * 7 +(_column - 1);
}

void Game::initializeWay(){
    Node node;
    for(uint8_t i = 0; i < N_NODES; i++){
        _way[i] = node;
    }
}

void Game::determineLine(volatile bool& isValidation,volatile bool& isSelection){
    screen.write("LIGNE");
    screen.write("1", SECOND_LINE);            
    while(isValidation == false){                  
        if (isSelection){                                            
            if(_line >= N_LINES) {
                _line = 1;
            }
            else {       
                _line += 1;
            }
        isSelection = false;
        screen.write("LIGNE           ");
        screen << _line;                
        }                                      
    }
    isValidation = false;    
}

void Game::determineColumn(volatile bool& isValidation,volatile bool& isSelection){
    screen.write("COLONNE");
    screen.write("1", SECOND_LINE);
    while(isValidation == false){
        if (isSelection){
            if(_column >= N_COLUMNS){
                _column = 1;
            }
            else{
                _column+=1;
            }
        isSelection=false;
        screen.write("COLONNE         ");
        screen << _column; 
        }
    }
    isValidation = false;
}

void Game::confirmChoice(volatile bool& isValidation,volatile bool& isSelection){
    screen << "("<< _line << "," <<_column<< ") OK?";
    screen.write("OUI", SECOND_LINE);
    while(!isValidation){
        if (isSelection){  
            isSelection= false;
            _finaleValidation = (!_finaleValidation);
            if(_finaleValidation){
                screen.write("OUI", SECOND_LINE);
            }
            else {
                screen.write("NON", SECOND_LINE);
            }
        }
    }
}

void Game::convertDirection(){
    if(_robot.getDirection() == Node::directions::EAST){
        _robot.setDirection(Node::directions::WEST);
    }else if(_robot.getDirection() == Node::directions::WEST){
        _robot.setDirection(Node::directions::EAST);
    }else if(_robot.getDirection() == Node::directions::NORTH){
        _robot.setDirection(Node::directions::SOUTH);
    }else if(_robot.getDirection() == Node::directions::SOUTH){
        _robot.setDirection(Node::directions::NORTH);
    }
}

void Game::executeState(volatile bool& isInterrupt,volatile bool& isSelection,volatile bool& isValidation, volatile uint8_t& counter, 
                        volatile  bool& isTimerDone, volatile bool& isCornerChallenge){
    switch(_robotState){
        case selectionState::START:  
            isCornerChallenge = false;
            if (isInterrupt){
                isInterrupt = false;
                _robotState=selectionState::CORNER;                    
            }
            if(isSelection){
                isSelection= false;
                _robotState=selectionState::INITIALIZE_TRAJECT;                                        
            }
            isValidation = false;
            break;

        case selectionState::CORNER:
            isCornerChallenge = true;
            counter = 0;
            screen.clear();
            _robot.doNothing();
            delayMs(START_DELAY);
            _corner.startCornerChallenge(_robot, counter, isTimerDone);
            _robotState = selectionState::START;   
            isInterrupt = false;
            sei();
            break;
            
        case selectionState::INITIALIZE_TRAJECT: 
            isSelection = false; 
            isValidation = false;
            _finaleValidation = true; 
            screen.clear(); 
            determineLine(isValidation,isSelection);
            _robotState = selectionState::SELECTION;
            screen.clear();
            break;

        case selectionState::SELECTION:            
            determineColumn(isValidation,isSelection);
            _robotState = selectionState::VALIDATION;
            screen.clear();
            break;

        case selectionState::VALIDATION:
            confirmChoice(isValidation,isSelection);
            if(_finaleValidation){
                _robotState = selectionState::TRAJECT;    
                screen.clear();  
            }
            else{
                _robotState=selectionState::INITIALIZE_TRAJECT;
                screen.clear();
                _line = 1;
                _column = 1;
            }
            isSelection = false; 
            isValidation = false;
            _finaleValidation = true;      
            break;

        case selectionState::TRAJECT: 
            _robot.doNothing();
            delayMs(START_DELAY);    
            _traject.findWay(_way, _robot.getPosition(), convertToNode());                                                      
            _nElement = _traject.getNElement(_way) - 1;                                 

            _nextNode = _way[_nElement];
            _robot._timer.startTimer(isTimerDone);
            while(true){  
                counter = 0;                                                                                                                                                                   
                _nElement--;
                processMovement(_nextNode, counter);                                                                                
                                    
                if(_nElement >= N_NODES){   
                    _traject.InitializeMap();
                    initializeWay();
                    
                    if(!(_robot._navigation._line.isReadingLine())){
                        _robot._navigation.turn180();
                        _robot._navigation.reverse();
                        delayMs(REVERSE_DELAY);
                        _robot._navigation.stop();
                        convertDirection();
                    }                   
                    _line = 1;
                    _column = 1;
                    for(uint8_t x = 0; x <= N_DESTINATION_NOTE; x++){
                        _robot._music.setNote(DESTINATION_NOTE);
                        delayMs(DESTINATION_NOTE_DELAY);
                        _robot._music.stopMusic();
                        delayMs(SILENCE_DELAY);
                    }                        
                    break;
                }             
                _nextNode = _way[_nElement];                                                           
            }
            screen.clear();
            _robotState=selectionState::INITIALIZE_TRAJECT;              
            break;
    }
}


