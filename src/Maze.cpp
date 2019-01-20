/**
 * @file Maze.cpp
 *
 * @brief Implementation of Maze class methods
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include "../includes/Maze.h"
#include "../includes/MinHeap.h"

bool Maze::loadBinary(std::string filename)
{
	const int MAZE_INFO_POS = 3; //number of maze info positions
	const int INTS_PER_EDGE = 4;
	std::ifstream reader(filename);

	//if the filename doesn't exist
	if (!reader)
	{
		throw FileException(filename, "The file does not exist!");
	}
	//while reader is valid (i.e. not EOF)
	while(reader)
	{
		int i;
		//read size of int into variable i
		reader.read((char*)&i, sizeof(int));
		//add i to maze_ints vector
		maze_ints.push_back(i);
	}
	//allocates maze dimensions and edges
	width = maze_ints[WIDTH_POS];
	height = maze_ints[HEIGHT_POS];
	numberOfEdges = maze_ints[NO_EDGES_POS];

	//check that edges match what's specified
	if (((int)maze_ints.size()-MAZE_INFO_POS)/INTS_PER_EDGE != numberOfEdges)
	{
		throw FileException(filename, "The number of edges don't match what "
			"was specified in the file");
	}
//check that edges match width/height specification - not relevant with ellers
//	else if (width*height-INITIAL_ELEMENT != numberOfEdges)
//	{
//		throw FileException(filename, "The width and height specified in the "
//			"file don't match the number of edges in the file.");
//	}
	init_maze(); //initialises maze locations

	//populates the maze with data read from binary file
	for (unsigned i = NO_EDGES_POS+NEXT_ELEMENT; i < maze_ints.size();
		 i=i+COORDS_PER_LINE)
	{
		//ensure theres no access out of vector bounds
		if (i+Y2_POS > maze_ints.size())
		{
			break;
		}
		//check if any of the recorded positions are out of maze bounds
		else if (maze_ints[i+X1_POS] < 0 || maze_ints[i+X1_POS] > width ||
		 maze_ints[i+Y1_POS] < 0 || maze_ints[i+Y1_POS] > height || 
		 maze_ints[i+X2_POS] < 0 || maze_ints[i+X2_POS] > width || 
		 maze_ints[i+Y2_POS] < 0 || maze_ints[i+Y2_POS] > height)
		{
			throw FileException(filename, "Edge ("
				+std::to_string(maze_ints[i+X1_POS])+","
				+std::to_string(maze_ints[i+Y1_POS])+")("
				+std::to_string(maze_ints[i+X2_POS])+","
				+std::to_string(maze_ints[i+Y2_POS])+
				") exceeds expected width or height");
		}
		struct Edge tempEdge(maze_ints[i+X1_POS], maze_ints[i+Y1_POS],
		 	maze_ints[i+X2_POS], maze_ints[i+Y2_POS]);
		//ensures edge hasn't already been recorded
		if (!isDuplicateEdge(tempEdge.x1, tempEdge.y1, tempEdge.x2,
			 tempEdge.y2))
		{
			//allocate edge to maze
			maze[tempEdge.y1][tempEdge.x1].adjacentCells.push_back(tempEdge);
		}
	}
	return true;
}

bool Maze::saveSVG(std::string filename)
{
	const int EXTRANEOUS_INT = 1;
	std::ofstream writer;
	writer.open(filename);
    if (!writer)
    {
        throw FileException(filename, "The file does not exist!");
    }

	//set desireable SVG display size in pixels
	float outputDimension = 800;
	float scalingFactor;

	//determines scaling factor for largest dimension
	if (width > height)
	{
		scalingFactor = outputDimension/width;
	}
	else
	{
		scalingFactor = outputDimension/height;
	}
	//adjustment of stroke to scaling factor
	float stroke = 0.5*scalingFactor;
    float strokePath = 0.2*scalingFactor;


	//write SVG headers

	writer << "<svg width=\"" << width*scalingFactor << "\" height=\"" 
	<< height*scalingFactor << "\" xmlns=\"http://www.w3.org/2000/svg\">" 
	<< std::endl;

	writer << "<rect width=\"" << width*scalingFactor << "\" height=\"" 
	<< height*scalingFactor << "\" style=\"fill:black\" />" << std::endl;

	 /*loop through maze and write each edge to SVG. Each dimension is 
	 	multiplied by scaling factor*/
	for (unsigned i = NO_EDGES_POS+NEXT_ELEMENT; 
		i < maze_ints.size()-EXTRANEOUS_INT; i=i+COORDS_PER_LINE)
	{
		writer << "<line stroke=\"white\" x1=\"" 
		<< maze_ints[i+X1_POS]*scalingFactor << "\" x2=\"" 
		<< maze_ints[i+X2_POS]*scalingFactor << "\" y1=\"" 
		<< maze_ints[i+Y1_POS]*scalingFactor << "\" y2=\"" 
		<< maze_ints[i+Y2_POS]*scalingFactor << "\" stroke-width=\"" 
		<< stroke << "\" />"
		<< std::endl;
	}
    
    for (unsigned i = 0; i < solution_ints.size(); i=i+COORDS_PER_LINE)
    {
        writer << "<line stroke=\"red\" x1=\""
        << solution_ints[i+X1_POS]*scalingFactor << "\" x2=\""
        << solution_ints[i+X2_POS]*scalingFactor << "\" y1=\""
        << solution_ints[i+Y1_POS]*scalingFactor << "\" y2=\""
        << solution_ints[i+Y2_POS]*scalingFactor << "\" stroke-width=\""
        << strokePath << "\" />"
        << std::endl;
    }
    
	writer << "</svg>" << std::endl;
	return true;
}

bool Maze::saveBinary(std::string filename)
{
	std::ofstream binFile;
	//opens the file as a binary file
	binFile.open (filename, std::ios::out | std::ios::binary);
	//writes each int in maze_ints out as binary to filename
    if (!binFile)
    {
        throw FileException(filename, "The file does not exist!");
    }
	for (unsigned i = 0; i  < maze_ints.size(); i++)
	{
		binFile.write((char*)&maze_ints[i], sizeof(maze_ints[i]));
	}
	return true;
}

//Setters
void Maze::init_maze()
{
	//to store location as [y,x] to match [row,column] convention
    const int XLOC_POS = 1; 
    const int YLOC_POS = 0;
	std::vector<struct Cell> column;
	struct Cell tempCell;

	//ensures maze dimensions are defined
	if (width <= 0 || height <= 0)
	{
		throw MazeException("Maze Dimensions not defined. Cannot initialise "
			"maze.");
	}
	else
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				//intiitalises a temporary cell
                tempCell.location[YLOC_POS] = i;
				tempCell.location[XLOC_POS] = j;
				//allocates this cell to a temporary column
				column.push_back(tempCell);
			}
			//adds the temporary column to the maze for each increment of i
			maze.push_back(column);
			//clears the column values to start again
			column.clear();
		}
	}
}

void Maze::addToIntsVec(struct Edge tempEdge)
{
	//adds elements of input edge to the end of the maze_ints vector
	maze_ints.push_back(tempEdge.x1);
	maze_ints.push_back(tempEdge.y1);
	maze_ints.push_back(tempEdge.x2);
	maze_ints.push_back(tempEdge.y2);
}

void Maze::initIntsVec()
{
	//ensures maze properties are within scope
	if (height <= 0 || width <= 0 || numberOfEdges <= 0)
	{
		throw MazeException("Maze Dimensions not defined. Cannot initialise "
			"maze vector.");
	}
	else
	{
		//adds maze properties to maze_ints vec
		maze_ints.push_back(width);
		maze_ints.push_back(height);
		maze_ints.push_back(numberOfEdges);
	}
}
void Maze::pushEdge(int x, int y, struct Edge tempEdge) 
{ 
	//adds adjacent edges to a maze cell
	maze[y][x].adjacentCells.push_back(tempEdge); 
}
void Maze::setVisited(int x, int y) 
{ 
	//updates a cells visited status
	maze[y][x].visited = true; 
}

//Getters
bool Maze::hasBeenVisited(int x, int y) 
{ 
	//returns a cells visited status
	return maze[y][x].visited; 
}

bool Maze::isDuplicateEdge(int x1, int y1, int x2, int y2)
{
	const int _Y1_POS = 0; //stored as [y,x] to match [row, column] convention
	const int _X1_POS = 1;
	unsigned long numberOfAdjEdges_pos2 = maze[y2][x2].adjacentCells.size();

	for (unsigned long i = 0; i < numberOfAdjEdges_pos2; i++)
	{
		/*checks for equality between original edge and edges stored at the 
			second coordinate*/
		if (maze[y2][x2].adjacentCells[i].y2 == maze[y1][x1].location[_Y1_POS] 
		&& maze[y2][x2].adjacentCells[i].x2 == maze[y1][x1].location[_X1_POS])
		{
			return true;
		}
	}
	return false;
}

void Maze::makeSolutionInts()
{
	//converts solution to printable integers in vector form
    const int Y1 = 0;
    const int X1 = 1;
    const int Y2 = 0;
    const int X2 = 1;
    
    for (unsigned i = 0; i < solution.size()-1; i++)
    {
        solution_ints.push_back(solution[i].location[X1]);
        solution_ints.push_back(solution[i].location[Y1]);
        solution_ints.push_back(solution[i+1].location[X2]);
        solution_ints.push_back(solution[i+1].location[Y2]);
    }
}

void Maze::updateSolution(std::vector<SolutionTree> _solution)
{
	//updates the solution in maze object
    solution = _solution;
    makeSolutionInts();
}

void Maze::updateEdges(int _numberOfEdges)
{
    numberOfEdges = _numberOfEdges;
    maze_ints[NO_EDGES_POS] = _numberOfEdges;
}

