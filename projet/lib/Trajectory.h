/*
 * Nom: Trajectory.h
 * Description: Classe responsable de trouver le chemin le plus court avec
 *              l'algorithme Dijkstra. 
 * Équipe : 1013
 * Auteurs : Kim Desroches, Ghadi Falouh, Kimia Foroudian et Ali Yacoubi
 * 
 * Un node avec un poids de 100 signifie qu'il n'y a pas de connexion avec 
 * l'autre node. Sinon, il peut y avoir un poids de 1, 2 ou 5 avec un autre
 * node.
 * 
*/

#pragma once
#define N_NODES 28

#include "Node.h"
#include <avr/io.h>

enum class TrajectorySearchStates {CHOOSING_LINE,CHOOSING_COLUMN, CONFIRMATION 
                                    ,TRAJECTORY, OBSTACLE_DETECTED};

class Trajectory{
public: 
    Trajectory();
    void InitializeMap();        
    void findWay(Node* way, uint8_t indexBeginning, uint8_t indexEnd);
    void changeMap(Node node); 
    uint8_t getNElement(Node* way);
    TrajectorySearchStates _trajectoryState = TrajectorySearchStates::CHOOSING_LINE;

private:
    Node _map [28];
    uint8_t _numNodes = 0;
    uint8_t _maxDist = 100;       
};