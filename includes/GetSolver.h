/**
 * @file GetSolver.h
 *
 * @brief Definition of GetSolver class, which is a factory for the type of
 * maze solver to be used
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include "Dijkstra.h"
#include "BFS.h"
#include "DFS.h"
#include <memory>

class GetSolver
{
private:
    Maze &MazeObj;
    SolutionTree goal;
    SolutionTree startingPoint;
    
    int goal_X;
    int goal_Y;
    int startingPoint_X;
    int startingPoint_Y;
    
public:
    GetSolver(Maze &_MazeObj, int _goal_X, int _goal_Y, int _startingPoint_X, 
        int _startingPoint_Y) : MazeObj(_MazeObj), 
        goal(MazeObj.maze[_goal_Y][_goal_X]), 
        startingPoint(MazeObj.maze[_startingPoint_Y][_startingPoint_X]),
        goal_X(_goal_X), goal_Y(_goal_Y), startingPoint_X(_startingPoint_X),
        startingPoint_Y(_startingPoint_Y) {};
        
    std::unique_ptr<MazeSolver> operator() (enum solvers solver_type, 
        enum distanceType distance_type);
    
    virtual ~GetSolver() {};
};
