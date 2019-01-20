/**
 * @file DFS.h
 *
 * @brief Definition of DFS class, implementing Depth First Search
 * maze solving techniques
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include "MazeSolver.h"
#pragma once

class DFS : public MazeSolver
{
private:
    
    bool DFSrecursive(SolutionTree &c);

public:
    bool solveMaze();
    
    DFS(Maze &_MazeObj, int goal_X, int goal_Y, int startingPoint_X, 
    	int startingPoint_Y) : MazeSolver(_MazeObj, goal_X, goal_Y, 
    	startingPoint_X, startingPoint_Y) {};
    
    virtual ~DFS() {};

};