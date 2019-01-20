/**
 * @file BFS.cpp
 *
 * @brief Implementation of BFS class methods
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include "../includes/BFS.h"

bool BFS::solveMaze()
{

    unsigned i = 0;
    resetVisited();
    initQueue(startingPoint);
    
    while (i<queue.size())
    {
        //check to see if cell being interrogated is the goal
        if(cellIsGoal(queue[i]))
        {
            // removes all elements from the queue not part of the solution
            while (queue.size()-1 > i)
            {
                queue.pop_back();
            }
            generateSolution();
            return true;
        }
        else
        {
            //adds children of current cell to queue if it's not the goal
            addToQueue(queue[i]);
            i++;
        }
    }
    return false;
}

void BFS::addToQueue(struct SolutionTree c)
{
    for (unsigned i = 0; i < c.adjacentCells.size(); i++) 
    {
        //finds x, y coords
        int x2 = c.adjacentCells[i].x2;
        int y2 = c.adjacentCells[i].y2; 
        int x1 = c.location[X_POS];
        int y1 = c.location[Y_POS];
        
        /*checks that the adjacent cell isn't a reference back to parent, and
        that it hasn't been visited*/
        if (!MazeObj.maze[y2][x2].visited && 
            notParentCell(c, c.adjacentCells[i]))
        {
            SolutionTree newCell(MazeObj.maze[y2][x2], x1, y1);
            
            queue.push_back(newCell); 
            
            MazeObj.setVisited(x2, y2);
        }
    }
}
