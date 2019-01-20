/**
 * @file DFS.cpp
 *
 * @brief Implementation of DFS class methods
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include "../includes/DFS.h"

bool DFS::solveMaze()
{
    // std::cout << "DFS" << std::endl;
    //ensures no cells are marked "visited" at the beginning
    resetVisited();
    //initialises the queue of visited cells
    initQueue(startingPoint);
    //creates a new queue for cells to be visited in the future (operational)
    std::vector<SolutionTree> searchQueue;
    //initialises the searchQueue
    searchQueue.push_back(startingPoint);
    
    //initialises current node
    SolutionTree currentNode = startingPoint;
    
    while (queue.size() > 0)
    {
        //test to see if current node is solution
        if (cellIsGoal(currentNode))
        {
            generateSolution();
            return true;
        }
        else
        {
            //removes current node from the beginning of the search queue
            searchQueue.erase(searchQueue.begin());

            for (unsigned i = 0; i < currentNode.adjacentCells.size(); i++)
            {
                int x2 = currentNode.adjacentCells[i].x2;
                int y2 = currentNode.adjacentCells[i].y2;
                int x1 = currentNode.location[X_POS];
                int y1 = currentNode.location[Y_POS];
                
                /*ensures adjacent cell has not been visited and is not a
                reference back to the parent cell*/
                if (!MazeObj.maze[y2][x2].visited && 
                    notParentCell(currentNode, currentNode.adjacentCells[i]))
                {
                    SolutionTree tempCell(MazeObj.maze[y2][x2], x1, y1);
                    //inserts adjacent cell to the beginning of search queue
                    searchQueue.insert(searchQueue.begin(), tempCell);
                    //records the cell to a separate queue for later analaysis
                    queue.push_back(tempCell);
                    //sets the cell as visited
                    MazeObj.setVisited(x2, y2);
                }
            }
            //next node to be analysed is first in the searchQueue
            currentNode = searchQueue.front();
        }
    }
    return false;
}