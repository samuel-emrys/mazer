/**
 * @file Generator.h
 *
 * @brief Definition of Generator class, to be inherited from by specific
 * generation classes
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "Maze.h"
#include "ArgumentException.h"
#include <random>
#include <chrono>

class Generator
{
	protected:

		const int MIN_DIM = 1;
		const int MAX_HEIGHT = 1000;
		const int MAX_WIDTH = 1000;
		const int ADJACENT_POSITIONS = 3;
		const int INITIAL_CELL = 1;
    
		unsigned long seed; //seed used for random gen
		std::mt19937 gen; //random generator
		Maze& MazeObj;
    
		unsigned mtRand(int upperLimit);
		unsigned mtRand(int lowerLimit, int upperLimit);

	public:
		//pure virtual functions, enforces implementation in child
		virtual void generate() = 0; 
		virtual void generate(int width, int height) = 0;

		Generator(Maze& maze_obj, unsigned long _seed) 
		: seed(_seed), gen((unsigned int)_seed), MazeObj(maze_obj) {};

		virtual ~Generator() {}; //destructor
};

enum compass //enumeration for movement direction
{
	NORTH = 0,
	EAST,
	SOUTH,
	WEST
};

enum builders //enumerations for generation types
{
    ALDOUS = 0,
    ELLERS
};