/**
 * @file main.h
 *
 * @brief main header file, contains appropriate includes and definition of 
 * input arguments
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#pragma once

#include "CmdLine.h"
#include "Aldous.h"
#include "Ellers.h"
#include "Dijkstra.h"
#include "BFS.h"
#include "DFS.h"
#include <cstdlib> //req'd for EXIT_SUCCESS
#include "Timer.h"
#include "GetBuilder.h"
#include "GetSolver.h"
#pragma once

//constant string flags for comparison
const std::string gaFlag = "--ga"; //generate using aldous broder
const std::string geFlag = "--ge"; //generate using ellers
const std::string pmFlag = "--pm"; //solve using dijkstra's manhattan
const std::string peFlag = "--pe"; //solve using dijkstra's euclidean
const std::string pbFlag = "--pb"; //solve using breadth first search
const std::string pdFlag = "--pd"; //solve using depth first search
const std::string lbFlag = "--lb"; //load binary
const std::string svFlag = "--sv"; //save svg
const std::string sbFlag = "--sb"; //save binary
const std::string hFlag = "--h"; //help


/*void saveToFile(int dimension, std::string solve_type, std::string gen_type,
 std::string distance)*/
//{
//    std::string filename = "timeData.txt";
//    std::ofstream writer;
//    writer.open(filename, std::ios::out | std::ios::app);
//    if (!writer)
//    {
//        throw FileException(filename, "The file does not exist!");
//    }
//    
//    writer << dimension << "," << gen_type << "," << genTime << ","
//    << solve_type << "," << distance << "," << solveTime << ",binary," 
//		<< binTime
//    << ",svg," << svgTime <<std::endl;
//}
