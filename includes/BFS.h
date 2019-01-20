/**
 * @file BFS.h
 *
 * @brief Definition of BFS class, implementing Breadth First Search
 * maze solving techniques
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include "MazeSolver.h"
#pragma once

class BFS : public MazeSolver
{
private:
    void addToQueue(struct SolutionTree c);

public:
    BFS(Maze &_MazeObj, int goal_X, int goal_Y, int startingPoint_X, 
    	int startingPoint_Y) : MazeSolver(_MazeObj, goal_X, goal_Y, 
    	startingPoint_X, startingPoint_Y) {};

    bool solveMaze();

    virtual ~BFS() {};

};