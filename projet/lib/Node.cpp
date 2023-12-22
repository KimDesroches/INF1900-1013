#include "Node.h"

static int counter = 0;

Node::Node()
{
    _neighbors[0] = 100;
    _neighbors[1] = 100;
    _neighbors[2] = 100;
    _neighbors[3] = 100;
    _number = -1;
}

Node::Node(int east, int west, int north, int south) {
    _neighbors[0] = east;
    _neighbors[1] = west;
    _neighbors[2] = north;
    _neighbors[3] = south;
    _number = counter;
    counter++;
}

void Node::resetCounter(){
    counter = 0;
}

void Node::setState(bool isVisited){
    _isVisited = isVisited;
}

int Node::getEast(){
        return _neighbors[0];
}

int Node::getWest(){
        return _neighbors[1];
}

int Node::getNorth(){
        return _neighbors[2];
}


int Node::getSouth(){
        return _neighbors[3];
}

void Node::setNorth(int north)
{
    _neighbors[2] = north;
}

void Node::setEast(int east)
{
    _neighbors[0] = east;
}

void Node::setSouth(int south)
{
    _neighbors[3] = south;
}

void Node::setWest(int west)
{
    _neighbors[1] = west;
}

void Node::setAllDirections(int newValue)
{
    _neighbors[0] = newValue;
    _neighbors[1] = newValue;
    _neighbors[2] = newValue;
    _neighbors[3] = newValue;
}

bool Node::getState(){
    return _isVisited;
}

int Node::getNumber(){
    return _number;
}