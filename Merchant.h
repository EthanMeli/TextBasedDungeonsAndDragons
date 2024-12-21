#ifndef MERCHANT_H
#define MERCHANT_H

#include <iostream>
#include <vector>

class Merchant
{
    private:

    // Cost of weapons
    int weapons_[4] = {10, 20, 50, 75}; // Bronze sword, iron sword, dragon sword, rapier

    // Cost of cookwear
    int cookwear_[2] = {5, 15}; // Pot, cauldron

    // Cost of armour
    int armour_[1] = {5}; // Armour

    // Cost of ingredients
    int ingredients_[1] = {1}; // Ingredients

    // Cost of treasures
    int treasures_[5] = {15, 20, 30, 50, 100}; // Emerald, ruby, platinum, obsidian, dragon scale

    public:

    // Constructor
    Merchant();

    // Getters

    // (Weapons)
    int getBronze();
    int getIron();
    int getDragon();
    int getRapier();

    // (Cookwear)
    int getPot();
    int getCauldron();

    // (Armour)
    int getArmour();

    // (Ingredients)
    int getIngredients();

    // (Treasures)
    int getEmerald();
    int getRuby();
    int getPlatinum();
    int getObsidian();
    int getScale();

    void setPrices(int rooms_cleared);

    // Display merchant information
    void displayMerchant(int player_gold, int num_ingredients, int pots, int cauldrons, int bronze,
    int iron, int dragon, int rapier, int armour, int emeralds, int rubies, int platinums,
    int obsidians, int scales);
};

#endif