/**
 * @file CmdLine.h
 *
 * @brief Definition of CmdLine class, which parses command line
 * arguments
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
#include "FileException.h"


class CmdLine
{
	private:
		int argc; //argument count
		std::vector <std::string> argv; //argument variables

	public:
		//struct vector holding flags and their arguments
    
		std::vector<struct Argument> args;
		bool mazeGenerated;
        bool solverSpecified = false;
		void displayUsage();
		
		CmdLine()
		{
			argc = 0;
			//initialises argv to blank strings
			for (int i = 0; i < argc; i++)
			{
				argv[i] = "";
			}
			mazeGenerated = false;
		}
		CmdLine(int argCount, char** argVar)
		{
			argc = argCount;
			//converts char * argv[] to string for easy manipulation
			for (int i = 0; i < argc; i++)
			{
				argv.push_back(std::string(argVar[i]));
			}
			mazeGenerated = false;
		}

		bool parseArgs();

		virtual ~CmdLine() {}; //destructor

};

//struct that holds the properties of arguments to be processed
struct Argument
{
	// std::string description;
	std::string flag;
	std::vector<unsigned long> intValues;
	std::string stringValue;
	bool executed;

	Argument() : flag(""), intValues(0), stringValue("") {};
};

