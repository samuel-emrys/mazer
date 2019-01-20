/**
 * @file GetBuilder.h
 *
 * @brief Definition of GetBuilder class, which is a factory for the type
 * of maze generation algorithm to be used
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include "Aldous.h"
#include "Ellers.h"
#include <memory>

class GetBuilder
{
private:
    Maze &MazeObj;
    unsigned long seed;
    
public:
	//creates object based on input arguments
    GetBuilder(Maze &_MazeObj, unsigned long _seed) : 
	    MazeObj(_MazeObj), seed(_seed) {};

    std::unique_ptr<Generator> operator() (enum builders builder_type);
    
    virtual ~GetBuilder() {};
};
