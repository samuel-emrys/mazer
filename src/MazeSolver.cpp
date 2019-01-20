/**
 * @file MazeSolver.cpp
 *
 * @brief Implementation of MazeSolver class methods
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include "../includes/MazeSolver.h"

void MazeSolver::resetVisited()
{
    //resets the visited status to false of all cells in the maze
    for (int i = 0; i < MazeObj.getHeight(); i++)
    {
        for (int j = 0; j < MazeObj.getWidth(); j++)
        {
            MazeObj.maze[i][j].visited = false;
        }
    }
}

void MazeSolver::initQueue(SolutionTree &c)
{    
    //initialises the queue for solving
    queue.push_back(c); 
}

void MazeSolver::generateSolution()
{
    //finds the solution path by tracking backwards from the goal
    SolutionTree tempCell = queue[queue.size()-1];
    while (true)
    {
        solution.push_back(tempCell);
        if (tempCell.xPrev == -1 && tempCell.yPrev == -1)
        {
            break;
        }
        for (unsigned i = 0; i < queue.size(); i++)
        {
            if (queue[i].location[X_POS] == tempCell.xPrev &&
                queue[i].location[Y_POS] == tempCell.yPrev)
            {
                tempCell = queue[i];
                break;
            }
        }
    }    
}

bool MazeSolver::cellIsGoal(SolutionTree &c)
{
    //checks to see if the input cell is the goal
    // struct Cell goal = 
    //     MazeObj.maze[MazeObj.getHeight()-1][MazeObj.getWidth()-1];
    
    if (c.location[Y_POS] == goal.location[Y_POS] &&
        c.location[X_POS] == goal.location[X_POS])
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool MazeSolver::notParentCell(SolutionTree &c, Edge &e)
{
    //determines whether the edge and input cell are the same
    if (c.location[X_POS] == e.x2 && c.location[Y_POS] == e.y2)
    {
        return false;
    }
    return true;
}