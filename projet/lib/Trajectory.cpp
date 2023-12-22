#include "Trajectory.h"

Trajectory::Trajectory(){
    _numNodes = 28;
}

void Trajectory::InitializeMap(){  
    _map->resetCounter();
    _map[0] = Node(1, 100, 100, 1);
    _map[1] = Node(1, 1, 100, 100);
    _map[2] = Node(1, 1, 100, 1);
    _map[3] = Node(100, 1, 100, 1);
    _map[4] = Node(1, 100, 100, 100);
    _map[5] = Node(2, 1, 100, 2);
    _map[6] = Node(100, 2, 100, 1);

    // line 2
    _map[7] = Node(5, 100, 1, 100);
    _map[8] = Node(1, 5, 100, 1);
    _map[9] = Node(100, 1, 1, 5);
    _map[10] = Node(2, 100, 1, 100);
    _map[11] = Node(1, 2, 100, 5);
    _map[12] = Node(1, 1, 2, 1);
    _map[13] = Node(100, 1, 1, 1);

    // line 3
    _map[14] = Node(2, 100, 100, 5);
    _map[15] = Node(1, 2, 1, 100);
    _map[16] = Node(1, 1, 5, 1);
    _map[17] = Node(5, 1, 100, 1);
    _map[18] = Node(100, 5, 5, 5);
    _map[19] = Node(100, 100, 1, 1);
    _map[20] = Node(100, 100, 1, 1);

    // line 4
    _map[21] = Node(1, 100, 5, 100);
    _map[22] = Node(1, 1, 100, 100);
    _map[23] = Node(100, 1, 1, 100);
    _map[24] = Node(2, 100, 1, 100);
    _map[25] = Node(5, 2, 5, 100);
    _map[26] = Node(1, 5, 1, 100);
    _map[27] = Node(100, 1, 1, 100);
  
}

uint8_t Trajectory::getNElement(Node* way){
    uint8_t nElement = 0; 
    for (uint8_t i = 0; i < N_NODES; i++) {
        if (way[i].getNumber() >= 0) { 
            nElement++;
        }        
    }    
    return nElement;
}

void Trajectory::findWay(Node* way, uint8_t indexBeginning, uint8_t indexEnd){
    uint8_t shortestDist[_numNodes + 1];
    Node previous[_numNodes + 1];    
    for (uint8_t i = 0; i < _numNodes; i++) {
        shortestDist[i] = _maxDist;
    }

    //_map[indexBeginning].setState(true); // node de depart est visitee
    shortestDist[indexBeginning] = 0;    

    for (uint8_t round = 1; round <= 10; round++) { 
        for (uint8_t i = 0; i < _numNodes; i++) {

            Node& actualNode = _map[i];            
            //actualNode.setState(true);

            if (i + 1 % 7 != 0) { // gerer les exceptions
                if (shortestDist[i + 1] > actualNode.getEast() + shortestDist[i]) {
                    shortestDist[i + 1] = actualNode.getEast() + shortestDist[i];
                    previous[i + 1] = actualNode;
                }
            }

            if (i % 7 != 0) { // gerer les exceptions
                if (shortestDist[i - 1] > actualNode.getWest() + shortestDist[i]) {
                    shortestDist[i - 1] = actualNode.getWest() + shortestDist[i];
                    previous[i - 1] = actualNode;
                }
            }

            if (!(i <= 6)) { // gerer les exceptions
                if (shortestDist[i - 7] > actualNode.getNorth() + +shortestDist[i]) {
                    shortestDist[i - 7] = actualNode.getNorth() + shortestDist[i];
                    previous[i - 7] = actualNode;
                }
            }

            if (i < 21) { // gerer les exceptions
                if (shortestDist[i + 7] > actualNode.getSouth() + shortestDist[i]) {
                    shortestDist[i + 7] = actualNode.getSouth() + shortestDist[i];
                    previous[i + 7] = actualNode;
                }
            }
        }
    }

    // Partie 2 (trouver chemin specifique) :
    // ca marche mais le tabeau est de 28 et il y pas 28 element dedans en plus     
    
    Node element = _map[indexEnd];
    uint8_t wayIndex = 0;
    uint8_t next = indexEnd;    

    while (true) {                        
        if (element.getNumber() == indexBeginning) {            
            break;
        }
        way[wayIndex] = element;
        element = previous[next];
        next = previous[next].getNumber();        
        wayIndex++;
    } 
}

void Trajectory::changeMap(Node node){
    uint8_t index = node.getNumber();                

    node.setAllDirections(_maxDist);

    if (index % 7 != 0)
        _map[index - 1].setEast(_maxDist);
    if (index + 1 % 7 != 0)    
        _map[index + 1].setWest(_maxDist);
    if (index < 21)    
        _map[index + 7].setNorth(_maxDist);
    if (!(index <= 6))
        _map[index - 7].setSouth(_maxDist);
}

