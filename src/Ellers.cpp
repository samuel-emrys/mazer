/**
 * @file Ellers.cpp
 *
 * @brief Implementation of Ellers class methods
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include "../includes/Ellers.h"

void Ellers::generate()
{
    const int INTS_PER_EDGE = 4;
    const int INIT_VALUES = 3;
    //Randomises height and width between min and max values
    MazeObj.setHeight( mtRand(MIN_DIM,MAX_HEIGHT) );
    MazeObj.setWidth( mtRand(MIN_DIM,MAX_WIDTH) );
    
    //Number of edges is 1 less than the product of the dimensions
    MazeObj.setEdges((MazeObj.getWidth()*MazeObj.getHeight())-INITIAL_CELL);
    MazeObj.init_maze(); //initialise maze
    
    EllersBuilder(); //generates the maze
    int newEdges = ((int)MazeObj.getIntsSize()-INIT_VALUES)/INTS_PER_EDGE;
    MazeObj.updateEdges(newEdges);
    
    std::cout << "Your seed value for this run is: " << seed << std::endl;
    
}

void Ellers::generate(int width, int height)
{
    const int INTS_PER_EDGE = 4;
    const int INIT_VALUES = 3;
    
    //user input assigned to width and height
    MazeObj.setHeight(height);
    MazeObj.setWidth(width);
    
    MazeObj.setEdges(MazeObj.getWidth()*MazeObj.getHeight()-INITIAL_CELL);
    MazeObj.init_maze();
    
    EllersBuilder(); //generates the maze
//    std::cout << MazeObj.getIntsSize() << std::endl;
    int newEdges = ((int)MazeObj.getIntsSize()-INIT_VALUES)/INTS_PER_EDGE;
    MazeObj.updateEdges(newEdges);
    
    std::cout << "Your seed value for this run is: " << seed << std::endl;
}

void Ellers::EllersBuilder()
{
    std::vector<int> currentRow;
    std::vector<int> nextRow;
    std::vector<std::vector<int>> rows;
    int setCounter = 1;
    bool propagated = false;
    MazeObj.initIntsVec(); //initialise ints vector
    
//    std::cout << "Ellers" << std::endl;
    for (int i = 1; i <= MazeObj.getWidth(); i++)
    {
        currentRow.push_back(i);
        setCounter++;
    }
    
    for (int row = 0; row < MazeObj.getHeight(); row++)
    {
        //randomly merge cells in different sets
        for (unsigned col = 0; col < currentRow.size(); col++) 
        {
            if (col == currentRow.size()-1)
            {
                break;
            }
            /*checks that the column doesnt equal next column and uses a 
            random generator to decide if columns should be merged. Or, if
            this is the last row, merge all columns.*/
            if ((currentRow[col] != currentRow[col+1] && mtRand(false,true)) ||
                 row == MazeObj.getHeight()-1)
            {
                //carves edges in the maze
                currentRow[col+1]=currentRow[col];
                Edge parentEdge(col, row, col+1, row);
                MazeObj.pushEdge(col, row, parentEdge);
                MazeObj.addToIntsVec(parentEdge);
                
                Edge childEdge(col+1, row, col, row);
                MazeObj.pushEdge(col+1, row, childEdge);
            }
        }
        if (row != MazeObj.getHeight()-1)
        {
            //propagates at least one column in each set down
            for (unsigned col = 0; col < currentRow.size(); col++)
            {
                if (col == 0)
                {
                    propagated = false;
                }
                else
                {
                    if (currentRow[col] != currentRow[col-1])
                    {
                        propagated = false; //reset propagation check
                    }
                }
                /*generates a random number, checks to see if a 
                row element has propagated down, and whether it's the 
                last number in its set*/
                if (mtRand(false,true) || 
                (!propagated && col == currentRow.size()-1) ||
                 (!propagated && currentRow[col] != currentRow[col+1]))
                {
                    //creates connections in the maze
                    nextRow.push_back(currentRow[col]);
                    Edge parentEdge(col, row, col, row+1);
                    MazeObj.pushEdge(col, row, parentEdge);
                    MazeObj.addToIntsVec(parentEdge);
                    
                    Edge childEdge(col, row+1, col, row);
                    MazeObj.pushEdge(col, row+1, childEdge);
                    propagated = true;
                }
                else
                {
                    nextRow.push_back(setCounter++);
                }
            }
        }
        // rows.push_back(currentRow);
        currentRow = nextRow; //makes the next row the current row
        nextRow.clear(); //deletes the next row for further use
    }
}
