#include "Companion.h"
#include <iostream>
#include <vector>
using namespace std;

// Construct companion with inputted name
Companion::Companion(string name)
{
    name_ = name;
}

// Return the companion's fullness
double Companion::getFullness()
{
    return current_fullness_;
}

// Return the companion's name
string Companion::getName()
{
    return name_;
}

// Set the fullness of companion
/**
 * Algorithm:
 * If fullness greater than max (50) -> Set fullness to max
 * If fullness less than min (0) - > Set fullness to 0
 * Else -> Set fullness to inputted number
 */
void Companion::setFullness(double fullness)
{
    if (fullness > MAX_FULLNESS_)
    {
        current_fullness_ = MAX_FULLNESS_;
    }
    else if (fullness < MIN_FULLNESS_)
    {
        current_fullness_ = MIN_FULLNESS_;
    }
    else
    {
        current_fullness_ = fullness;
    }
}

// Set the name of companion selected
void Companion::setName(string name)
{
    name_ = name;
}