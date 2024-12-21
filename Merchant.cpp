#include "Merchant.h"
#include <iostream>
#include <vector>
using namespace std;

// Default constructed (does nothing)
Merchant::Merchant()
{

}

// Set the prices of the merchant depending on how many rooms are cleared
void Merchant::setPrices(int rooms_cleared)
{
    // Loop through all items and increase by 25% * number of cleared rooms
    // (Increases prices by 25% per room cleared)
    for (int i = 0; i < 4; i++)
    {
        weapons_[i] = weapons_[i] * (1 + 0.25 * rooms_cleared);
    }
    for (int i = 0; i < 2; i++)
    {
        cookwear_[i] = cookwear_[i] * (1 + 0.25 * rooms_cleared);
    }
    armour_[0] = armour_[0] * (1 + 0.25 * rooms_cleared);
    ingredients_[0] = ingredients_[0] * (1 + (0.25 * rooms_cleared));
}

// Return price of Bronze Sword
int Merchant::getBronze()
{
    return weapons_[0];
}

// Return price of Iron Sword
int Merchant::getIron()
{
    return weapons_[1];
}

// Return price of Dragon Sword
int Merchant::getDragon()
{
    return weapons_[2];
}

// Return price of Ancient Rapier
int Merchant::getRapier()
{
    return weapons_[3];
}

// Return price of Pot
int Merchant::getPot()
{
    return cookwear_[0];
}

// Return price of Cauldron
int Merchant::getCauldron()
{
    return cookwear_[1];
}

// Return price of armour
int Merchant::getArmour()
{
    return armour_[0];
}

// Return price of ingredients
int Merchant::getIngredients()
{
    return ingredients_[0];
}

// Return price of emerald
int Merchant::getEmerald()
{
    return treasures_[0];
}

// Return price of ruby
int Merchant::getRuby()
{
    return treasures_[1];
}

// Return price of platinum
int Merchant::getPlatinum()
{
    return treasures_[2];
}

// Return price of obsidian
int Merchant::getObsidian()
{
    return treasures_[3];
}

// Return price of dragon scale
int Merchant::getScale()
{
    return treasures_[4];
}

// Display Merchant options
void Merchant::displayMerchant(int player_gold, int num_ingredients, int pots, int cauldrons, int bronze,
    int iron, int dragon, int rapier, int armour, int emeralds, int rubies, int platinums,
    int obsidians, int scales)
{
    cout << "+-------------+" << endl;
    cout << "| INVENTORY   |" << endl;
    cout << "+-------------+" << endl;
    cout << "| Gold        | " << player_gold << endl;
    cout << "| Ingredients | " << num_ingredients << " kg" << endl;
    cout << "| Cookware    | P: " << pots << " | C: " << cauldrons << endl;
    cout << "| Weapons     | B: " << bronze << " | I: " << iron << " | D: " << dragon << " | R: " <<
    rapier << endl;
    cout << "| Armor       | " << armour << endl;
    cout << "| Treasures   | E: " << emeralds << " | R: " << rubies << " | P: " << platinums << " | O: "
    << obsidians << " | S: " << scales << endl << endl;
    cout << "Choose one of the following:" << endl;
    cout << " 1. Ingredients: To make food, you have to cook raw ingredients." << endl;
    cout << " 2. Cookware: You will need something to cook those ingredients." << endl;
    cout << " 3. Weapons: It's dangerous to go alone, take this!" << endl;
    cout << " 4. Armor: If you want to survive monster attacks, you will need some armor." << endl;
    cout << " 5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands." << endl;
    cout << " 6. Leave: Make sure you get everything you need, I'm leaving after this sale!" << endl;
}