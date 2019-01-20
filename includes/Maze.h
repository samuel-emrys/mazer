/**
 * @file Maze.h
 *
 * @brief Definition of Maze class, defining the maze
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include "MazeException.h"
#include "FileException.h"
#include <limits>


class Maze
{
	private:

		int width;
		int height;
		int numberOfEdges;
		std::vector<int> maze_ints; //int description of maze for output
        std::vector<struct SolutionTree> solution;
        std::vector<int> solution_ints;

		const int WIDTH_POS = 0;
		const int HEIGHT_POS = 1;
		const int NO_EDGES_POS = 2;
		const int X1_POS = 0;
		const int X2_POS = 2;
		const int Y1_POS = 1;
		const int Y2_POS = 3;
		const int COORDS_PER_LINE = 4;
		const int NEXT_ELEMENT = 1;
//		const int INITIAL_ELEMENT = 1;

	public:
        std::vector<std::vector<struct Cell>> maze; //maze data structure

		Maze() : width(0), height(0), numberOfEdges(0), maze_ints(0), maze(0)
		{};
		bool saveBinary(std::string filename);
		bool saveSVG(std::string filename);
		bool loadBinary(std::string filename);
		void init_maze();
		bool isDuplicateEdge(int x1, int y1, int x2, int y2);
		void addToIntsVec(struct Edge tempEdge);
		void initIntsVec();


		//Getters
		int getWidth() { return width; };
		int getHeight() { return height; };
		int getEdges() { return numberOfEdges; };
        unsigned long getIntsSize() { return maze_ints.size(); }
		bool hasBeenVisited(int x, int y);

		/*Setters (req'd because maze class is instantiated in main and 
			allocated to in Generator). This was deemed to be a better 
			alternative than making the variables public, so that their 
			use can be controlled. */
		void setEdges(int _numberOfEdges) { numberOfEdges = _numberOfEdges; };
        void updateEdges(int _numberOfEdges);
		void setHeight(int _height) { height = _height; };
		void setWidth(int _width) { width = _width; };
		void pushEdge(int x, int y, struct Edge tempEdge);
		void setVisited(int x, int y);
        void updateSolution(std::vector<SolutionTree> _solution);
        void makeSolutionInts();

		virtual ~Maze() {};
};

//Edge struct holds coordinates and visited status of each edge
struct Edge
{
	int x1;
	int y1;
	int x2;
	int y2;
	bool visited;

	Edge() : x1(0), y1(0), x2(0), y2(0), visited(false) {};
	Edge(int _x1, int _y1, int _x2, int _y2) : visited(false)
	{
		x1 = _x1;
		y1 = _y1;
		x2 = _x2;
		y2 = _y2;
	};
};

//Cell struct holds the coordinates of each cell and a list of adjacent edges
struct Cell
{
	std::vector<int> location;
	std::vector<struct Edge> adjacentCells;
	bool visited;
//    Cell() {};
	Cell() : location(2), adjacentCells(0), visited(false) {};
	Cell(const struct Cell &c) : location(c.location), 
	adjacentCells(c.adjacentCells), visited(c.visited) {};
};


struct SolutionTree : Cell
{
    int xPrev;
    int yPrev;
    int distance;
    
    SolutionTree(struct Cell &c) : Cell(c), xPrev(-1), yPrev(-1), distance(std::numeric_limits<int>::max()) {};
    SolutionTree(struct Cell &c, int _x, int _y) : Cell(c), xPrev(_x), yPrev(_y), distance(std::numeric_limits<int>::max()) {};

    friend bool operator> (const SolutionTree &a, const SolutionTree &b)
    {
        return (a.distance > b.distance);
    }
    
    friend bool operator>= (const SolutionTree &a, const SolutionTree &b)
    {
        return (a.distance >= b.distance);
    }
    
    friend bool operator< (const SolutionTree &a, const SolutionTree &b)
    {
        return (a.distance < b.distance);
    }
    
    friend bool operator<= (const SolutionTree &a, const SolutionTree &b)
    {
        return (a.distance <= b.distance);
    }
    
    friend bool operator== (const SolutionTree &a, const SolutionTree &b)
    {
        return (a.location[0] == b.location[0] && a.location[1] == b.location[1]);
    }
    
    friend bool operator!= (const SolutionTree &a, const SolutionTree &b)
    {
        return (a.location[0] != b.location[0] || a.location[1] != b.location[1]);
    }
};




