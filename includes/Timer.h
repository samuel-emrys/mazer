/**
 * @file Timer.h
 *
 * @brief Definition of Timer class, used to get information about runtime of various
 * algorithms
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include <chrono>
#include <iostream>
#pragma once

class Timer
{
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
	public:
		//initialise class with current time and allocate to start_time
		Timer() : start_time(std::chrono::high_resolution_clock::now()) {};
		float getDuration();
		void reset();
};

float Timer::getDuration()
{
	//get current time and compare to stored time on instantiation
	auto current_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::milli> dTime = current_time - start_time;
    return dTime.count();
}

void Timer::reset()
{
	//reset timer at a specific location
	start_time = std::chrono::high_resolution_clock::now();
}
