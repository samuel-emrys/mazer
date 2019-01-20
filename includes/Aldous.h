/**
 * @file Aldous.h
 *
 * @brief Definition of Aldous class, implementing Aldous-Border maze generation 
 * techniques
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include "Generator.h"
#pragma once

class Aldous : public Generator
{
private:
    void AldousBuilder();

public:
    void generate() override;
    void generate(int width, int height) override;
    
    Aldous(Maze& _MazeObj, unsigned long _seed) : Generator(_MazeObj, _seed){};
    
    virtual ~Aldous() {};
};

