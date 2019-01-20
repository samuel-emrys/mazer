/**
 * @file MazeException.h
 *
 * @brief Definition of MazeException class
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */

#pragma once
#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <string>

class MazeException: public std::runtime_error
{
private:
	std::string error_msg;
public:
	//constructor utilises runtime error and concatonates string
	MazeException(std::string _flag, std::string _error_msg) 
		: runtime_error("Invalid argument for '" + _flag +"': "), 
		error_msg(std::runtime_error::what() + _error_msg) {};

	MazeException(std::string _error_msg) 
		: runtime_error("Invalid argument: "), 
		error_msg(std::runtime_error::what() + _error_msg) {};

	virtual const char* what() const throw()
	{
		//overrides exception what() method
		return error_msg.c_str();
	}
};