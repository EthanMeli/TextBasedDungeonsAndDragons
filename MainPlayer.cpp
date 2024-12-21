#include "MainPlayer.h"
#include "Companion.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Default constructor
MainPlayer::MainPlayer(string name)
{
    name_ = name;
}

// Return fullness level
double MainPlayer::getFullness()
{
    return current_fullness_;
}

// Return name
string MainPlayer::getName()
{
    return name_;
}

// Return gold
int MainPlayer::getGold()
{
    return gold_;
}

// Return player's current tile
char MainPlayer::getCurrentTile()
{
    return current_tile_type_;
}

// Return num of keys
int MainPlayer::getKeys()
{
    return keys_;
}

// Add or remove gold
void MainPlayer::addGold(int gold)
{
    gold_ = gold_ + gold;
}

// Set the player's fullness level
/**
 * Algorithm:
 * If fullness greater than max (50) -> Set fullness to max
 * If fullness less than min (0) - > Set fullness to 0
 * Else -> Set fullness to inputted number
 */
void MainPlayer::setFullness(double fullness)
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

// Set current tile
void MainPlayer::setCurrentTile(char c)
{
    current_tile_type_ = c;
}

// Return amount of ingredients player has
int MainPlayer::getIngredients()
{
    return ingredients_;
}

// Return amount of cookwear in index i of cookwear_
int MainPlayer::getCookwear(int i)
{
    return cookwear_[i];
}

// Return amount of weapons in index i of weapons_
int MainPlayer::getWeapon(int i)
{
    return weapons_[i];
}

// Return amount of armour
int MainPlayer::getArmour()
{
    return armour_;
}

// Return amount of treasure in position i of treasures_
int MainPlayer::getTreasure(int i)
{
    return treasures_[i];
}

// Return amount of rooms cleared
int MainPlayer::getRoomsCleared()
{
    return rooms_cleared_;
}

// Set ingredients of player
// If input num less than 0 -> Set ingredients to 0
void MainPlayer::setIngredients(int num)
{
    if (num < 0)
    {
        ingredients_ = 0;
    }
    else
    {
        ingredients_ = num;
    }
}

// Set cookwear in position i of cookwear_ to num
// If input num less than 0 -> Set cookwear_[i] to 0
void MainPlayer::setCookwear(int i, int num)
{
    if (num < 0)
    {
        cookwear_[i] = 0;
    }
    else
    {
        cookwear_[i] = num;
    }
}

// Set weapons_[i] of player to num
void MainPlayer::setWeapon(int i, int num)
{
    weapons_[i] = num;
}

// Set amount of armour player has
// If input is less than 0 -> Set armour to 0
void MainPlayer::setArmour(int num)
{
    if (num < 0)
    {
        armour_ = 0;
    }
    else
    {
        armour_ = num;
    }
}

// Set amount of teasure in index i to num
void MainPlayer::setTreasure(int i, int num)
{
    treasures_[i] = num;
}

// Add a key to the player's inventory
void MainPlayer::addKey()
{
    keys_++;
}

// Return number of alive companions
int MainPlayer::getCompanions()
{
    return num_companions_;
}

// Reduces number of companions by 1
void MainPlayer::removeCompanion()
{
    num_companions_--;
}

// Adds 1 to number of cleared rooms
void MainPlayer::addRoomCleared()
{
    rooms_cleared_++;
}

// Calculate probability of different misfortunes
/**
 * Algorithm:
 * 1. Generate a random number from 1-10
 * 2. If this number is less than or equal to 3 (30%)
 *  2a. Inform user they have been robbed
 *  2b. Generate random number from 1-3
 *  2c. Depending on number, take item away from user, and inform them what was stolen
 * 3. If the number is equal to 4 (10%)
 *  3a. If the player has no weapons - Explain they are lucky and do nothing
 *  3b. If not, generate a number from 0-3
 *  3c. Break one of the player's weapons depending on what number is generated, and whether
 *      they have a weapon in that position or not, if they don't, generate a new number
 * 4. If the number is greater than 4 but less than or equal to 7
 *  4a. Generate a random number between 0 and the current number of alive companions - 1
 *  4b. Remove 10 fullness from the companion in position r_2 of the companions_ array
 * 5. If the number is greater than 7 and the player is currently in a room
 *  5a. Remove the companion in the last spot of companions_
 *  5b. Reduce party size by 1
 * 6. Else
 *  6a. Do nothing
 */
void MainPlayer::misfortune(vector<Companion> companions_)
{
    srand(time(0));
    int r_1;
    int r_2;
    r_1 = (rand() % 10) + 1;
    if (r_1 <= 3)
    {
        cout << "OH NO! Your team was robbed by badits!" << endl;
        r_2 = (rand() % 3) + 1;
        switch (r_2)
        {
            case 1:
            cout << "You lost 1 Cauldron!" << endl;
            setCookwear(1, getCookwear(1) - 1);
            break;
            case 2:
            cout << "You lost 10 kg!" << endl;
            setIngredients(getIngredients() - 10);
            break;
            case 3:
            cout << "You lost 1 armour!" << endl;
            setArmour(getArmour() - 1);
            break;
         }
    }
    else if (r_1 == 4)
    {
        if (getWeapon(0) + getWeapon(1) + getWeapon(2) + getWeapon(3) == 0)
        {
            cout << "You have no weapons to break!" << endl;
            cout << "You are lucky this time!" << endl;
        }
        else
        {
            r_2 = (rand() % 3);
            while (weapons_[r_2] == 0)
            {
                r_2 = (rand() % 3);
            }
            switch (r_2)
            {
                case 0:
                cout << "You have broken a Bronze Sword!" << endl;
                break;
                case 1:
                cout << "You have broken an Iron Sword!" << endl;
                break;
                case 2:
                cout << "You have broken a Dragon Sword!" << endl;
                break;
                case 3:
                cout << "You have broken an Ancient Rapier!" << endl;
                break;
            }
            setWeapon(r_2, getWeapon(r_2) - 1);
        }
    }
    else if (r_1 > 4 && r_1 <= 7)
    {
        r_2 = (rand() % num_companions_ - 1);
        companions_[r_2].setFullness(companions_[r_2].getFullness() - 10);
    }
    else if (r_1 > 7 && current_tile_type_ == 'R')
    {
        cout << "Your teammate " << companions_[num_companions_ - 1].getName() << " is trapped in the previous room and is unable to get through. You must continue without them." << endl;
        companions_.pop_back();
        removeCompanion();
        cout << "Your party has reduced to " << getCompanions() + 1 << endl;
    }
    else
    {

    }
}

// Remove a single key
void MainPlayer::removeKey()
{
    keys_--;
}

// Display Player's Status
void MainPlayer::displayParty(int anger_level, vector<Companion> companions_, int defeated_monsters_)
{
    cout << "+-------------+" << endl;
    cout << "| STATUS      |" << endl;
    cout << "+-------------+" << endl;
    cout << "| Rooms Cleared: " << rooms_cleared_ << " | Keys: " << keys_ << " | Anger Level: " << anger_level << " | Monsters Defeated: " << defeated_monsters_ << endl;
    cout << "+-------------+" << endl;
    cout << "| INVENTORY   |" << endl;
    cout << "+-------------+" << endl;
    cout << "| Gold        | " << gold_ << endl;
    cout << "| Ingredients | " << ingredients_ << " kg" << endl;
    cout << "| Cookware    | P: " << cookwear_[0] << " | C: " << cookwear_[1] << endl;
    cout << "| Weapons     | B: " << weapons_[0] << " | I: " << weapons_[1] << " | D: " << weapons_[2] << " | R: " <<
    weapons_[3] << endl;
    cout << "| Armor       | " << armour_ << endl;
    cout << "| Treasures   | E: " << treasures_[0] << " | R: " << treasures_[1] << " | P: " << treasures_[2] << " | O: "
    << treasures_[3] << " | S: " << treasures_[4] << endl;
    cout << "+-------------+" << endl;
    cout << "| PARTY       |" << endl;
    cout << "+-------------+" << endl;
    cout << "| " << name_ << " | Fullness: " << current_fullness_ << endl;
    for (int i = 0; i < companions_.size(); i++)
    {
        cout << "| " << companions_[i].getName() << " | Fullness: " << companions_[i].getFullness() << endl;
    }
    cout << "+-------------+" << endl << endl;
}