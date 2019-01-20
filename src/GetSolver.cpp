/**
 * @file GetSolver.cpp
 *
 * @brief Implementation of GetSolver class methods
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include "../includes/GetSolver.h"

std::unique_ptr<MazeSolver> GetSolver::operator()(enum solvers solver_type, 
    enum distanceType distance_type)
{
    std::unique_ptr<MazeSolver> solver;
    
    switch (solver_type)
    {
        case BREADTH:
        {
            //creates object pointer for breadth first search
            solver = std::make_unique<BFS>(this->MazeObj, this->goal_X, 
                this->goal_Y, this->startingPoint_X, this->startingPoint_Y);
        }
            break;
            
        case DEPTH:
        {
            //creates object pointer for depth first search
            solver = std::make_unique<DFS>(this->MazeObj, this->goal_X, 
                this->goal_Y, this->startingPoint_X, this->startingPoint_Y);
        }
            break;
        case DIJKSTRA:
        {
            //creates object pointer for dijkstras algorithm
            solver = std::make_unique<Dijkstra>(this->MazeObj, this->goal_X, 
                this->goal_Y, this->startingPoint_X, this->startingPoint_Y, 
                distance_type);
        }
    }
    //returns object pointer to solver type
    return solver;
//    return std::move(solver);
}
