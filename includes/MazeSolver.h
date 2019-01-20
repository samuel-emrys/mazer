/**
 * @file MazeSolver.h
 *
 * @brief Definition of MazeSolver class, which is an abstract class for inheritence
 * by maze solving classes
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include "Maze.h"

#pragma once
class MazeSolver
{
protected:
    std::vector<SolutionTree> queue;
    const int X_POS = 1;
    const int Y_POS = 0;
    
    Maze &MazeObj; //maze object reference
    SolutionTree goal; //goal location
    SolutionTree startingPoint; //starting location
    std::vector<SolutionTree> solution; //solution path

    int goal_X;
    int goal_Y;
    int startingPoint_X;
    int startingPoint_Y;
    
    void resetVisited();
    void initQueue(SolutionTree &c);
    void generateSolution();
    bool cellIsGoal(SolutionTree &c);
    bool notParentCell(SolutionTree &c, Edge &e);

    
public:

    MazeSolver(Maze &_MazeObj, int _goal_X, int _goal_Y, int _startingPoint_X,
        int _startingPoint_Y) : MazeObj(_MazeObj),
        goal(MazeObj.maze[_goal_Y][_goal_X]),
        startingPoint(MazeObj.maze[_startingPoint_Y][_startingPoint_X]),
        goal_X(_goal_X), goal_Y(_goal_Y), startingPoint_X(_startingPoint_X),
        startingPoint_Y(_startingPoint_Y) {};
    
    std::vector<SolutionTree> getSolution() { return solution; };
    
    virtual bool solveMaze()=0;
    virtual ~MazeSolver() {}
    
};

enum distanceType //enumeration for the type of distance to calculate
{
    EUCLIDEAN = 0,
    MANHATTAN,
    NA
};

enum solvers //enumeration for types of solvers 
{
    BREADTH = 0,
    DEPTH,
    DIJKSTRA
};