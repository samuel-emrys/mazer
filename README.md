# README

Personal Note: This was a program that I wrote in my first year learning to program, and before I had taken any algorithms courses. It was enormously educational, however there is some implementation here that can be improved significantly. I've documented this in an anlysis I did of this program, available in docs/mazer_performance_analysis.pdf

## Mazer
------------------------------------------------------------------------------
This program is designed to generate mazes using both the Aldous-Broder and
Eller algorithms, save them in either binary or scaled vector graphic (SVG) 
format, and solve them using either Depth First Search, Breadth First Search,
or Dijkstras Algorithm. Dijkstras Algorithm has the option to use either
euclidean or manhattan cost functions to determine preference. Mazes can also
be loaded from a binary file.

## Compiling
------------------------------------------------------------------------------
Compilation of Mazer may be achieved in a number of ways:
1. Directly using the following compilation arguments:

		g++ -Wall -pedantic -Wextra -std=c++14 src/*.cpp -o bin/mazer

2. Using CMake:
Navigate to the project root and execute the following:

		$ cmake src
		$ make

Both of these methods will result in the formation of an executable named
'mazer' within the 'bin' directory. If the second method was used, the command
line argument "make clean" can be utilised to remove the executable.

## Usage
------------------------------------------------------------------------------
Mazer may be executed using the command './mazer', followed by the following 
arguments:

	--ga : Generate a Maze using Aldous Broder algorithm.
	--ge : Generate a Maze using Ellers algorithm.

These require no input arguments for random generation, however also accept 
the following arguments:

		seed : Specify a seed generator
		width : Specify a maze width
		height : Specify a maze height

However, these arguments may only be used as detailed in the example usage:

		EXAMPLE USAGE:
		--g
		--g seed
		--g width height
		--g seed width height

	--lb : Load a maze from binary file. The following arguments must be
			specified:
		filename.maze : Name of the binary file

		EXAMPLE USAGE:
		--lb filename.maze

	--sb : Save a maze to binary file. The following arguments must be
			specified:
		filename.maze : Name of the binary file

		EXAMPLE USAGE:
		--sb filename.maze

	--sv : Save a maze to SVG file. The following arguments must be specified:
		filename.svg : Name of the SVG file

		EXAMPLE USAGE:
		--sv filename.svg

	--pb : Solve maze using breadth first search

	--pd : Solve maze using depth first search

	--pe : Solve maze using Dijkstras algorithm, using euclidean distance 
		heuristics

	--pm : Solve maze using Dijkstras algorithm, using manhattan distance 
		heuristics

	--h : Display correct program usage

PLEASE NOTE:
- The flags --g and --lb cannot be used together.
- The input arguments must contain ONE of either --g OR --lb. It cannot contain
	both.
- Both --g and --lb and their arguments are required to preceed --sb and --sv
- In order to save a maze to both binary and SVG, use both --sb and --sv input
	arguments

EXAMPLE USAGE:

	./mazer --lb filename.maze
	./mazer --lb filename.maze --sv filename.svg --pm
	./mazer --g
	./mazer --g --sb filename.maze --sv filename.svg --pd
	./mazer --g seed --sv filename.svg
	./mazer --g width height filename.maze
	./mazer --g seed width height --sb filename.maze --pb
	./mazer --h

## Known Bugs
-----------------------------------------------------------------------------
1. The mersenne twister random number generator, as implemented, will 
	intermittently produce a result outside the dictated distribution range.
	This has a minimal effect on the operation of the program as it is simply
	handled as an invalid result, and re-run until a valid result is produced.