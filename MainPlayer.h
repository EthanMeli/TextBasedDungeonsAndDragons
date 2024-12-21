#ifndef MAINPLAYER_H
#define MAINPLAYER_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Companion.h"
using namespace std;

class MainPlayer
{
    private:

    const double MAX_FULLNESS_ = 50; // Max fullness level
    const double MIN_FULLNESS_ = 0; // Min fullness level
    double current_fullness_ = 50; // Current fullness level
    string name_ = ""; // Name of main character
    char current_tile_type_; // Tile that player is currently on
    int gold_ = 100; // Number of gold pieces player begins with
    int ingredients_ = 0; // Ingredients player starts with
    int cookwear_[2] = {0, 0}; // Cookwear player begins with
    int weapons_[4] = {0, 0, 0, 0}; // Weapons player begins with
    int armour_ = 0; // Armour player begins with
    int treasures_[5] = {0, 0, 0, 0}; // Treasures player begins with
    int rooms_cleared_ = 0; // Starts with 0 rooms cleared
    int keys_ = 0; // Keys found at start
    int num_companions_ = 4; // Number of companions at start of game

    public:

    // Constructor
    MainPlayer(string name);

    // Getters
    double getFullness();
    string getName();
    int getGold();
    char getCurrentTile();
    int getIngredients();
    int getCookwear(int i);
    int getWeapon(int i);
    int getArmour();
    int getTreasure(int i);
    int getRoomsCleared();
    int getKeys();
    int getCompanions();

    // Setters
    void addGold(int gold);
    void setFullness(double fullness);
    void setCurrentTile(char c);
    void setIngredients(int num);
    void setCookwear(int i, int num);
    void setWeapon(int i, int num);
    void setArmour(int num);
    void setTreasure(int i, int num);
    void addKey();
    void removeKey();
    void removeCompanion();
    void addRoomCleared();
    void misfortune(vector<Companion> companions_);

    // Display status/inventory
    void displayParty(int anger_level, vector<Companion> companions_, int defeated_monsters_);
};

#endif