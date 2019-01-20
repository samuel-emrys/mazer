/**
 * @file GetBuilder.cpp
 *
 * @brief Implementation of GetBuilder class methods
 *
 * @author Samuel Dowling
 * Contact: samuel.dowling@protonmail.com
 *
 */
#include "../includes/GetBuilder.h"

std::unique_ptr<Generator> GetBuilder::operator()(enum builders builder_type)
{
    std::unique_ptr<Generator> builder;
    
    switch (builder_type)
    {
        case ALDOUS:
        {
            //creates pointer for aldous object
            builder = std::make_unique<Aldous>(this->MazeObj, this->seed);
        }
        break;
            
        case ELLERS:
        {
            //creates pointer for eller object
            builder = std::make_unique<Ellers>(this->MazeObj, this->seed);
        }
        break;
    }
    //returns pointer to builder object
    return builder;
//    return std::move(builder);
}
