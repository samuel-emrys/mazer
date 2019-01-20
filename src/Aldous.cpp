/**
 * @file Aldous.cpp
 *
 * @brief Implementation of Aldous class methods
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include "../includes/Aldous.h"

void Aldous::generate()
{
    
    //Randomises height and width between min and max values
    MazeObj.setHeight( mtRand(MIN_DIM,MAX_HEIGHT) );
    MazeObj.setWidth( mtRand(MIN_DIM,MAX_WIDTH) );
    
    //Number of edges is 1 less than the product of the dimensions
    MazeObj.setEdges((MazeObj.getWidth()*MazeObj.getHeight())-INITIAL_CELL);
    MazeObj.init_maze(); //initialise maze
    
    AldousBuilder(); //generates the maze
    
    std::cout << "Your seed value for this run is: " << seed << std::endl;
    
}

void Aldous::generate(int width, int height)
{
    //user input assigned to width and height
    MazeObj.setHeight(height);
    MazeObj.setWidth(width);
    
    MazeObj.setEdges(MazeObj.getWidth()*MazeObj.getHeight()-INITIAL_CELL);
    MazeObj.init_maze();
    
    AldousBuilder(); //generates the maze
    
    std::cout << "Your seed value for this run is: " << seed << std::endl;
}

void Aldous::AldousBuilder()
{
    /*adjustment for index value offset of 1 due to array index starting
     at 0 */
    const int INDEX_ADJUST = 1;
    
    struct Edge tempEdge;
    int dx = 0;
    int dy = 0;
    enum compass dir;
    int x = -1;
    int y = -1;
    
    //ensures random number generator returns a value between limits
    while ( y < 0 || y > MazeObj.getHeight() || x < 0 ||
           x > MazeObj.getWidth())
    {
        //gets random initial starting position
        y = mtRand(MIN_DIM, MazeObj.getHeight()-INDEX_ADJUST);
        x = mtRand(MIN_DIM, MazeObj.getWidth()-INDEX_ADJUST);
    }
    
    int remainingCells = MazeObj.getEdges();
    
    MazeObj.initIntsVec(); //initialise ints vector
    
    /*controlling loop, determines direction of next move and where
     the path will be carved */
    while (remainingCells > 0)
    {
        dir = (enum compass) mtRand(ADJACENT_POSITIONS);
        
        if (dir == NORTH)
        {
            dy = -1;
            dx = 0;
        }
        else if (dir == EAST)
        {
            dy = 0;
            dx = 1;
        }
        else if (dir == SOUTH)
        {
            dy = 1;
            dx = 0;
        }
        else if (dir == WEST)
        {
            dy = 0;
            dx = -1;
        }
        else
        {
            //indicates random generator has given a value outside of range
            //do nothing - continue generating
        }
        //check to see if the next cell is out of maze bounds
        if (y+dy >= 0 && y+dy < MazeObj.getHeight() && x+dx >= 0 &&
            x+dx < MazeObj.getWidth())
        {
            // check to see if the next cell has been visited
            if (!MazeObj.hasBeenVisited(x+dx, y+dy))
            {
                //allocates values to maze if not visited
                Edge parentEdge(x, y, x+dx, y+dy);
                MazeObj.pushEdge(x, y, parentEdge);
                
                Edge childEdge(x+dx, y+dy, x, y);
                MazeObj.pushEdge(x+dx, y+dy, childEdge);
                
                MazeObj.setVisited(x+dx,y+dy);
                remainingCells--;
                //adds edge to the output vector
                MazeObj.addToIntsVec(parentEdge);
            }
            /*moves the current position to new cell, regardless of
             whether a path has been carved to it */
            x=x+dx;
            y=y+dy;
        }
    }
}