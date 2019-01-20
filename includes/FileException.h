/**
 * @file FileException.h
 *
 * @brief Definition of FileException class
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

class FileException: public std::runtime_error
{
private:
	std::string error_msg;
public:
	//constructor utilises runtime error and concatonates string
	FileException(std::string _filename, std::string _error_msg) 
		: runtime_error("Invalid file '" + _filename +"': "), 
		error_msg(std::runtime_error::what() + _error_msg) {};

	virtual const char* what() const throw()
	{
		//override of exception what() method
		return error_msg.c_str();
	}
};
