/**
 * @file Dijkstra.cpp
 *
 * @brief Implementation of Dijkstra class methods
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include "../includes/Dijkstra.h"

bool Dijkstra::solveMaze()
{
    // std::cout << "Dijkstra" << std::endl;
    //resets visited status of cells
    resetVisited();
    startingPoint.distance = calcDistance(startingPoint);
    //initialises the binary heap by inserting the starting point
    heap.insert(startingPoint);
    
    while (heap.getMin().distance > 0)
    {
        SolutionTree parent = heap.getMin();
        
        for (unsigned i = 0; i < parent.adjacentCells.size(); i++)
        {
            int x1 = parent.adjacentCells[i].x1;
            int y1 = parent.adjacentCells[i].y1;
            int x2 = parent.adjacentCells[i].x2;
            int y2 = parent.adjacentCells[i].y2;
            
            SolutionTree child(MazeObj.maze[y2][x2], x1, y1);
            child.distance = calcDistance(child);
            if (!child.visited &&
                notParentCell(parent, parent.adjacentCells[i]))
            {
                heap.insert(child); //adds adjacent cell to heap
                MazeObj.setVisited(x2,y2);
            }
        }
        if (parent.adjacentCells.size() != 0 || heap.getMin() == goal)
        {
            queue.push_back(parent);
        }
        
        heap.deleteMin(); //deletes current cell from heap
        if (heap.size() == 0)
        {
            return false;
        }
        
    }
    queue.push_back(heap.getMin());
    generateSolution();
    return true;
}

int Dijkstra::calculateEuclidean(SolutionTree &a, SolutionTree &b)
{
    //calculates euclidean distance
    int x1 = a.location[X_POS];
    int x2 = b.location[X_POS];
    int y1 = a.location[Y_POS];
    int y2 = b.location[Y_POS];
    return sqrt( std::pow((x2-x1),2) + std::pow((y2-y1),2) );
}

int Dijkstra::calculateManhattan(SolutionTree &a, SolutionTree &b)
{
    //calculates manhattan distance
    int x1 = a.location[X_POS];
    int x2 = b.location[X_POS];
    int y1 = a.location[Y_POS];
    int y2 = b.location[Y_POS];
    return abs(x2-x1) + abs(y2-y1);
}

int Dijkstra::findPrevious(std::vector<SolutionTree> v, SolutionTree &c)
{
    //finds a cell in a vector and returns the index
    int found = -1;
    for (unsigned i = 0; i < v.size(); i++)
    {
        if (v[i].location[Y_POS] == c.yPrev && v[i].location[X_POS] == c.xPrev)
        {
            found = i;
        }
    }
    return found;
}

int Dijkstra::calcDistance(SolutionTree &a)
{
    //switch to calculate correct distance based on input arguments
    if (solveType == EUCLIDEAN)
    {
        return calculateEuclidean(a, goal);
    }
    else if (solveType == MANHATTAN)
    {
        return calculateManhattan(a, goal);
    }
    else
    {
        return -1;
    }
}