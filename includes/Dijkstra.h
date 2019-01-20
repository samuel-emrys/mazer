/**
 * @file Dijkstra.h
 *
 * @brief Definition of Dijkstra class, implementing Dijkstra's algorithm
 * to find a path through a maze
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include "MazeSolver.h"
#include "MinHeap.h"
#pragma once

class Dijkstra : public MazeSolver
{
private:
    MinHeap<SolutionTree> heap; //binary heap
    distanceType solveType; //type of distance to calculate

public:
    Dijkstra(Maze &_MazeObj, int goal_X, int goal_Y, int startingPoint_X, 
    	int startingPoint_Y, enum distanceType _solveType) : 
    MazeSolver(_MazeObj, goal_X, goal_Y, startingPoint_X, startingPoint_Y), 
    solveType(_solveType) {};

    bool solveMaze();
    int findPrevious(std::vector<SolutionTree> v, SolutionTree &c);
    int calculateEuclidean(SolutionTree &a, SolutionTree &b);
    int calculateManhattan(SolutionTree &a, SolutionTree &b);
    int calcDistance(SolutionTree &a);

    virtual ~Dijkstra() {};
};

