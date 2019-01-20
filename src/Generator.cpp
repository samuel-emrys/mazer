/**
 * @file Generator.cpp
 *
 * @brief Implementation of Generator class methods
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include "../includes/Generator.h"
#include <cstdlib>
#include <ctime>

unsigned Generator::mtRand(int upperLimit) //random number generation
{
	//uniform distribution of random numbers between 0 and upperLimit
	std::uniform_int_distribution<unsigned> dist(0,upperLimit);
	//generates random number
	unsigned num = dist(gen);
	 
	return num;
}

unsigned Generator::mtRand(int lowerLimit, int upperLimit)
{
	//uniform distribution of random numbers between lowerLimit and upperLimit
	std::uniform_int_distribution<unsigned> dist(lowerLimit,upperLimit);
	//generates random number
	unsigned num = dist(gen);

	return num;
}
