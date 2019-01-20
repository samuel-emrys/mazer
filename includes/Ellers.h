/**
 * @file Ellers.h
 *
 * @brief Definition of Ellers class, implementing Ellers Algorithm
 * to generate a maze
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include "Generator.h"
#pragma once

class Ellers : public Generator
{
private:
    void EllersBuilder();
    
public:
    void generate() override;
    void generate(int width, int height) override;
    
    Ellers(Maze& _MazeObj, unsigned long _seed) : Generator(_MazeObj, _seed) 
    	{};
    
    virtual ~Ellers() {}; //destructor

};
