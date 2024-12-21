#ifndef COMPANION_H
#define COMPANION_H

#include <iostream>
#include <vector>
using namespace std;

class Companion
{
    private:

    const double MAX_FULLNESS_ = 50; // Max fullness level
    const double MIN_FULLNESS_ = 0; // Min fullness level
    double current_fullness_ = 50; // Current fullness level
    string name_ = ""; // Name of main character

    public:

    // Constructor
    Companion(string name);

    // Getters
    double getFullness();
    string getName();

    // Setters
    void setFullness(double fullness);
    void setName(string name);
};

#endif