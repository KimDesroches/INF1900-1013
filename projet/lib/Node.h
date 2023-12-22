/*
 * Nom: Node.h
 * Description: Classe pour déterminer les points voisins.
 * Équipe : 1013
 * Auteurs : Kim Desroches, Ghadi Falouh, Kimia Foroudian et Ali Yacoubi
 * 
 * Un node représente un point parmis 28 et la relation avec les autres 
 * point selon l'orientation (nord, sud, est, ouest).
 * 
*/

#pragma once

#define N_NEIGHBORS 4

class Node{
public:
    Node();
    Node(int east, int west, int north, int south);

    void resetCounter();
    void setState(bool isVisited);
    int getNorth();
    int getEast();
    int getSouth();
    int getWest();
    bool getState();
    int getNumber();
    void setNorth(int north);
    void setEast(int east);
    void setSouth(int south);
    void setWest(int west);
    void setAllDirections(int newValue);
    enum class directions { EAST, WEST, NORTH, SOUTH};
    
private:
    int _neighbors[N_NEIGHBORS];
    bool _isVisited = false;
    int _number;
};