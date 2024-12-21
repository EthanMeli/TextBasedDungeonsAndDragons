#include "Map.h"
#include "MainPlayer.h"
#include "Companion.h"
#include "Merchant.h"
#include "Npc.h"

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

// Split function
int split(string input_string, char separator, string arr[], int arr_size)
{
    int temp = 0;
    int index = 0;
    if (input_string.length() < 1)
    {
        return 0;
    }
    for (int i = 0; i <= input_string.length(); i++)
    {
        if (input_string[i] == separator)
        {
            arr[index] = input_string.substr(temp, i-temp);
            temp = i+1;
            index++;
            i++;
        }
    }
    arr[index] = input_string.substr(temp);
    if (temp == 0)
    {
        arr[0] = input_string;
    }
    if (index >= arr_size)
    {
        return -1;
    }
    else
    {
        return index + 1;
    }
}

int main()
{
    // Declare main player and companions' names
    string main_player_name;
    string c1_name;
    string c2_name;
    string c3_name;
    string c4_name;
    string c5_name;

    // Prompt user for names
    cout << "Please enter your charater's name: " << endl;
    getline(cin, main_player_name);

    cout << "Please enter 4 companion names, press enter for each new name: " << endl;
    getline(cin, c1_name);
    getline(cin, c2_name);
    getline(cin, c3_name);
    getline(cin, c4_name);

    // Display good luck message to player and companions
    cout << "Great! We wish you, " << main_player_name << " and your companions: " << 
    c1_name << ", " << c2_name << ", " << c3_name << ", and " << 
    c4_name << " good luck on your adventure!" << endl;
    cout << endl << "=====================================" << endl << endl;

    // Create main player and companions based off user inputted names
    MainPlayer mp = MainPlayer(main_player_name);
    Companion c1 = Companion(c1_name);
    Companion c2 = Companion(c2_name);
    Companion c3 = Companion(c3_name);
    Companion c4 = Companion(c4_name);
    vector<Companion> party;
    party.push_back(c1);
    party.push_back(c2);
    party.push_back(c3);
    party.push_back(c4);

    // Construct default map and initialize important vars
    Map m = Map();
    int num_rooms = 0;
    int num_npcs = 0;
    int row;
    int col;
    Merchant merch = Merchant();
    int menu;
    int anger_level = 0;
    int party_size = 5;
    srand(time(0));
    int rand_num;

    // Randomize and place 5 unique rooms
    /**
     * Algorithm:
     * 1. Generate a random number between 0 and 12 for random row
     * 2. Generate a random number between 0 and 12 for random col
     * 3. If it is a free space
     *  3a. Add a room in that location
     *  3b. Increase number of rooms
     * 4. Else
     *  4a. Do nothing
     */
    while (num_rooms < 5)
    {
        row = (rand() % (11 - 0 + 1));
        col = (rand() % (11 - 0 + 1));
        if (m.isFreeSpace(row, col))
        {
            m.addRoom(row, col);
            num_rooms++;
        }
    }

    // Randomize and place 5 unique NPCs
    /**
     * Algorithm:
     * 1. Generate a random number between 0 and 12 for random row
     * 2. Generate a random number between 0 and 12 for random col
     * 3. If it is a free space
     *  3a. Add an NPC in that location
     *  3b. Increase number of NPCs
     * 4. Else
     *  4a. Do nothing
     */
    while (m.getNPCCount() < 5)
    {
        row = (rand() % (11 - 0 + 1));
        col = (rand() % (11 - 0 + 1));
        if (m.isFreeSpace(row, col))
        {
            m.addNPC(row, col);
            num_npcs++;
        }
    }

    // Display useful starting info
    cout << "Between the 5 of you, you have 100 gold pieces." << endl;
    cout << "You will need to spend the some of your money on the following items:" << endl << endl;
    cout << "- INGREDIENTS. To make food, you have to cook raw ingredients." << endl;
    cout << "- COOKWARE. If you want to cook, you have to have cookware first." << endl;
    cout << "- WEAPONS. You'll want at least one weapon per party member to fend off monsters." << endl;
    cout << "- ARMOR. Armor increases the chances of surviving a monster attack." << endl << endl;
    cout << "You can spend all of your money here before you start your journey, or you can save some to spend on merchants along the way." << endl << "But beware, some of the merchants in this dungeon are shady characters, and they won't always give you a fair price..." << endl;
    cout << endl;

    // Display first merchant
    merch.displayMerchant(mp.getGold(), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    cin >> menu;

    // Variables used for merchant
    int option;
    char confirm;
    int amt;

    // Loop the menu while the player decides to not leave
    while (menu != 6)
    {
        switch(menu)
        {
            // Case for when ingredients are selected
            case 1:
            cout << endl;
            cout << "How many kg of ingredients do you need [" << merch.getIngredients() << " Gold/kg]? (Enter a positive mulitple of 5, or 0 to cancel)" << endl;
            cin >> option;
            // Verify it is a valid input
            while (option % 5 != 0 || option < 0)
            {
                cout << "Please enter a positive multiple 5 or 0 to cancel!" << endl;
                cin >> option;
            }
            // Check to see if input is cancelled
            if (option == 0)
            {
                cout << "The transaction has been cancelled." << endl;
                merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
                mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
                mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
                cin >> menu;
                break;
            }
            // Check if player has enough money to purchase ingredients
            if (option * merch.getIngredients() > mp.getGold())
            {
                cout << "You have insufficient funds for this purchase." << endl;
                break;
            }
            // Check if the input is a positive number
            if (option > 0)
            {
                cout << "You want to buy " << option << " kg of ingredients for " << option * merch.getIngredients() << " Gold? (y/n)" << endl;
            }
            // Prompt user for confirmation, display messages based on input
            cin >> confirm;
            // Display confirmation menu for player
            switch (confirm)
            {
                // If player selects y (confirm)
                case 'y':
                mp.setIngredients(mp.getIngredients() + option);
                mp.addGold(-1 * (option * merch.getIngredients()));
                cout << "Thank you for your patronage! What else can I get for you?" << endl;
                break;
                // If player selects n (cancel)
                case 'n':
                cout << "Are you trying to waste my time? What else can I get for you?" << endl;
                break;
                // If player enters neither, display funny message, cancel
                default:
                cout << "I DON'T UNDERSTAND YOU!! (Transaction Failed)" << endl;
                break;
            }
            merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
            mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
            mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
            cin >> menu;
            break;
            // Case to display cookwear option
            case 2:
            cout << endl;
            cout << "I have a several types of cookware, which one would you like?" << endl;
            cout << "Each type has a different probability of breaking when used, marked with (XX%)." << endl;
            cout << endl;
            cout << "Choose one of the following:" << endl;
            cout << " 1. (15%) Pot [" << merch.getPot() << " Gold]" << endl;
            cout << " 2. ( 2%) Cauldron [" << merch.getCauldron() << " Gold]" << endl;
            cout << " 3. Cancel" << endl;
            cin >> option;
            // Prompt user for input
            switch (option)
            {
                // Case to select pots
                case 1:
                cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                cin >> amt;
                // Check input is positive
                while (amt < 0)
                {
                    cout << "Please enter a valid input!" << endl;
                    cin >> amt;
                }
                // Cancel if input is 0
                if (amt == 0)
                {
                    cout << "The transaction has been cancelled." << endl;
                    break;
                }
                // Check if player has enough gold to purchase pots
                if (amt * merch.getPot() > mp.getGold())
                {
                    cout << "You have insufficient funds for this purchase." << endl;
                    break;
                }
                // Display confirmation menu to player
                cout << "You want to buy " << amt << " Pot(s) for " << amt * merch.getPot() << " Gold? (y/n)" << endl;
                cin >> confirm;
                switch (confirm)
                {
                    // Confirmation menu, see comments above
                    case 'y':
                    mp.setCookwear(0, mp.getCookwear(0) + amt);
                    mp.addGold(-1 * (amt * merch.getPot()));
                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                    break;
                    case 'n':
                    cout << "Are you trying to waste my time? What else can I get for you?" << endl;
                    break;
                    default:
                    cout << "I DON'T UNDERSTAND YOU!! (Transaction Failed)" << endl;
                    break;
                }
                break;
                // Case to select cauldrons
                case 2:
                // See comments above, behaves in same way
                cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                cin >> amt;
                while (amt < 0)
                {
                    cout << "Please enter a valid input!" << endl;
                    cin >> amt;
                }
                if (amt == 0)
                {
                    cout << "The transaction has been cancelled." << endl;
                    break;
                }
                if (amt * merch.getCauldron() > mp.getGold())
                {
                    cout << "You have insufficient funds for this purchase." << endl;
                    break;
                }
                cout << "You want to buy " << amt << " Cauldron(s) for " << amt * merch.getCauldron() << " Gold? (y/n)" << endl;
                cin >> confirm;
                switch (confirm)
                {
                    // Confirmation menu, see comments above
                    case 'y':
                    mp.setCookwear(1, mp.getCookwear(1) + amt);
                    mp.addGold(-1 * (amt * merch.getCauldron()));
                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                    break;
                    case 'n':
                    cout << "Are you trying to waste my time? What else can I get for you?" << endl;
                    break;
                    default:
                    cout << "I DON'T UNDERSTAND YOU!! (Transaction Failed)" << endl;
                    break;
                }
                break;
                // Case to cancel
                case 3:
                cout << "The transaction has been cancelled." << endl;
                break;
                default:
                break;
            }
            merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
            mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
            mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
            cin >> menu;
            break;
            // Case for weapons
            case 3:
            cout << endl;
            if (mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) >= party_size)
            {
                cout << "You have purchased the maximum amount of weapons already!" << endl;
                merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
                mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
                mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
                cin >> menu;
                break;
            }
            // Display weapon options
            cout << "I have a plentiful collection of weapons to choose from, what would you like?" << endl;
            cout << "Note that some of them provide you a special bonus in combat, marked by a (+X)." << endl << endl;
            cout << "Choose one of the following:" << endl;
            cout << " 1. (+0) Bronze Sword [" << merch.getBronze() << " Gold]" << endl;
            cout << " 2. (+2) Iron Sword [" << merch.getIron() << " Gold]" << endl;
            cout << " 3. (+3) Dragon Sword [" << merch.getDragon() << " Gold]" << endl;
            cout << " 4. (+5) Ancient Rapier [" << merch.getRapier() << " Gold]" << endl;
            cout << " 5. Cancel" << endl;
            // Prompt user for input, and display messages accordingly
            cin >> option;
            switch (option)
            {
                // Bronze sword
                case 1:
                // Prompt user for amount they would like
                cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                cin >> amt;
                // Check if player doesn't already have max weapons
                if (amt + mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) > party_size)
                {
                    cout << "You are unable to purchase this amount of weapons." << endl;
                    cout << "You can only purchase a weapon for each party member." << endl;
                    cout << "Current max: " << party_size << endl;
                    break;
                }
                // Check input is a positive number
                while (amt < 0)
                {
                    cout << "Please enter a valid input!" << endl;
                    cin >> amt;
                }
                // Cancel if input is 0
                if (amt == 0)
                {
                    cout << "The transaction has been cancelled." << endl;
                    break;
                }
                // Check if player has enough gold to make purchase
                if (amt * merch.getBronze() > mp.getGold())
                {
                    cout << "You have insufficient funds for this purchase." << endl;
                    break;
                }
                cout << "You want to buy " << amt << " Bronze Sword(s) for " << amt * merch.getBronze() << " Gold? (y/n)" << endl;
                cin >> confirm;
                switch (confirm)
                {
                    // Confirmation menu, see comments above
                    case 'y':
                    mp.setWeapon(0, mp.getWeapon(0) + amt);
                    mp.addGold(-1 * (amt * merch.getBronze()));
                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                    break;
                    case 'n':
                    cout << "Are you trying to waste my time? What else can I get for you?" << endl;
                    break;
                    default:
                    cout << "I DON'T UNDERSTAND YOU!! (Transaction Failed)" << endl;
                    break;
                }
                break;
                // Iron Sword
                case 2:
                // Check comments for bronze sword, behaves in same way
                cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                cin >> amt;
                if (amt + mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) > party_size)
                {
                    cout << "You are unable to purchase this amount of weapons." << endl;
                    cout << "You can only purchase a weapon for each party member." << endl;
                    cout << "Current max: " << party_size << endl;
                    break;
                }
                while (amt < 0)
                {
                    cout << "Please enter a valid input!" << endl;
                    cin >> amt;
                }
                if (amt == 0)
                {
                    cout << "The transaction has been cancelled." << endl;
                    break;
                }
                if (amt * merch.getIron() > mp.getGold())
                {
                    cout << "You have insufficient funds for this purchase." << endl;
                    break;
                }
                cout << "You want to buy " << amt << " Iron Sword(s) for " << amt * merch.getIron() << " Gold? (y/n)" << endl;
                cin >> confirm;
                switch (confirm)
                {
                    case 'y':
                    mp.setWeapon(1, mp.getWeapon(1) + amt);
                    mp.addGold(-1 * (amt * merch.getIron()));
                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                    break;
                    case 'n':
                    cout << "Are you trying to waste my time? What else can I get for you?" << endl;
                    break;
                    default:
                    cout << "I DON'T UNDERSTAND YOU!! (Transaction Failed)" << endl;
                    break;
                }
                break;
                // Dragon Sword
                case 3:
                // Check comments for bronze sword, behaves in same way
                cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                cin >> amt;
                if (amt + mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) > party_size)
                {
                    cout << "You are unable to purchase this amount of weapons." << endl;
                    cout << "You can only purchase a weapon for each party member." << endl;
                    cout << "Current max: " << party_size << endl;
                    break;
                }
                while (amt < 0)
                {
                    cout << "Please enter a valid input!" << endl;
                    cin >> amt;
                }
                if (amt == 0)
                {
                    cout << "The transaction has been cancelled." << endl;
                    break;
                }
                if (amt * merch.getDragon() > mp.getGold())
                {
                    cout << "You have insufficient funds for this purchase." << endl;
                    break;
                }
                cout << "You want to buy " << amt << " Dragon Sword(s) for " << amt * merch.getDragon() << " Gold? (y/n)" << endl;
                cin >> confirm;
                switch (confirm)
                {
                    case 'y':
                    mp.setWeapon(2, mp.getWeapon(2) + amt);
                    mp.addGold(-1 * (amt * merch.getDragon()));
                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                    break;
                    case 'n':
                    cout << "Are you trying to waste my time? What else can I get for you?" << endl;
                    break;
                    default:
                    cout << "I DON'T UNDERSTAND YOU!! (Transaction Failed)" << endl;
                    break;
                }
                break;
                // Ancient Rapier
                case 4:
                // Check comments for bronze sword, behaves in same way
                cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                cin >> amt;
                if (amt + mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) > party_size)
                {
                    cout << "You are unable to purchase this amount of weapons." << endl;
                    cout << "You can only purchase a weapon for each party member." << endl;
                    cout << "Current max: " << party_size << endl;
                    break;
                }
                while (amt < 0)
                {
                    cout << "Please enter a valid input!" << endl;
                    cin >> amt;
                }
                if (amt == 0)
                {
                    cout << "The transaction has been cancelled." << endl;
                    break;
                }
                if (amt * merch.getRapier() > mp.getGold())
                {
                    cout << "You have insufficient funds for this purchase." << endl;
                    break;
                }
                cout << "You want to buy " << amt << " Ancient Rapier(s) for " << amt * merch.getRapier() << " Gold? (y/n)" << endl;
                cin >> confirm;
                switch (confirm)
                {
                    case 'y':
                    mp.setWeapon(3, mp.getWeapon(3) + amt);
                    mp.addGold(-1 * (amt * merch.getRapier()));
                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                    break;
                    case 'n':
                    cout << "Are you trying to waste my time? What else can I get for you?" << endl;
                    break;
                    default:
                    cout << "I DON'T UNDERSTAND YOU!! (Transaction Failed)" << endl;
                    break;
                }
                break;
                // Cancel
                case 5:
                cout << "The transaction has been cancelled." << endl;
                break;
                // Invalid Input
                default:
                cout << "Please Enter a Valid Input" << endl;
                cin >> option;
                break;
            }
            merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
            mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
            mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
            cin >> menu;
            break;
            // Case for armour
            case 4:
            // Check player doesn't have max armour
            if (mp.getArmour() >= mp.getCompanions() + 1)
            {
                cout << "You have already purchased the maximum amount of armour!" << endl;
                merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
                mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
                mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
                cin >> menu;
                break;
            }
            // Prompt user for input
            cout << "How many suits of armor can I get you? (Enter a positive integer, or 0 to cancel)" << endl;
            cin >> amt;
            // Check input is positive
            while (amt < 0)
            {
                cout << "Please enter a positive number!" << endl;
                cin >> amt;
            }
            // Cancel if input is 0
            if (amt == 0)
            {
                cout << "The transaction has been cancelled." << endl;
                merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
                mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
                mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
                cin >> menu;
                break;
            }
            // Check player can purchase amount of armour, doesn't exceed max
            if (mp.getArmour() + amt > mp.getCompanions() + 1)
            {
                cout << "You can not purchase this much armour!" << endl;
                cout << "Current max: " << party_size << endl;
                merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
                mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
                mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
                cin >> menu;
                break;
            }
            // Check player can afford purchase
            if (amt * merch.getArmour() > mp.getGold())
            {
                cout << "You have insufficient funds for this purchase." << endl;
                break;
            }
            cout << "You want to buy " << amt << " suit(s) of armor for " << amt * merch.getArmour() << " Gold? (y/n)" << endl;
            cin >> confirm;
            switch (confirm)
            {
                // Confirmation menu
                case 'y':
                mp.setArmour(amt);
                mp.addGold(-1 * (amt * merch.getArmour()));
                cout << "Thank you for your patronage! What else can I get for you?" << endl;
                break;
                case 'n':
                cout << "Are you trying to waste my time? What else can I get for you?" << endl;
                break;
                default:
                cout << "I DON'T UNDERSTAND YOU!! (Transaction Failed)" << endl;
                break;
            }
            merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
            mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
            mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
            cin >> menu;
            break;
            // Case for treasures
            case 5:
            cout << "What kind of treasure are you looking to sell?" << endl;
            cout << " 1. Emerald [15 Gold]" << endl;
            cout << " 2. Ruby [20 Gold]" << endl;
            cout << " 3. Platinum [30 Gold]" << endl;
            cout << " 4. Obsidian [50 Gold]" << endl;
            cout << " 5. Dragon Scale [100 Gold]" << endl;
            cout << " 6. Cancel" << endl;
            cin >> option;
            switch (option)
            {
                // Emeralds
                case 1:
                // Prompt user for input
                cout << "How many emeralds would you like to sell?" << endl;
                cin >> amt;
                // Make sure player has amount of treasure they're trying to sell
                if (amt > mp.getTreasure(0))
                {
                    cout << "You do not have this many emeralds!!" << endl;
                    break;
                }
                // Check that input is positive
                if (amt < 0)
                {
                    cout << "Invalid Input!" << endl;
                    break;
                }
                cout << "Are you sure you would like to sell " << amt << " emerald(s) for " << amt * merch.getEmerald() << " Gold? (y/n)" << endl;
                cin >> confirm;
                switch (confirm)
                {
                    // Confirmation menu
                    case 'y':
                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                    mp.addGold(amt * merch.getEmerald());
                    mp.setTreasure(0, mp.getTreasure(0) - amt);
                    break;
                    case 'n':
                    cout << "No problem. What else can I get for you?" << endl;
                    break;
                    default:
                    cout << "I DON'T UNDERSTAND YOU!!" << endl;
                    break;
                }
                break;
                // Rubies
                case 2:
                // Check comments for emerald
                cout << "How many rubies would you like to sell?" << endl;
                cin >> amt;
                if (amt > mp.getTreasure(1))
                {
                    cout << "You do not have this many rubies!!" << endl;
                    break;
                }
                if (amt < 0)
                {
                    cout << "Invalid Input!" << endl;
                    break;
                }
                cout << "Are you sure you would like to sell " << amt << " ruby(s) for " << amt * merch.getRuby() << " Gold? (y/n)" << endl;
                cin >> confirm;
                switch (confirm)
                {
                    case 'y':
                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                    mp.addGold(amt * merch.getRuby());
                    mp.setTreasure(1, mp.getTreasure(1) - amt);
                    break;
                    case 'n':
                    cout << "No problem. What else can I get for you?" << endl;
                    break;
                    default:
                    cout << "I DON'T UNDERSTAND YOU!!" << endl;
                    break;
                }
                break;
                // Platinums
                case 3:
                // Check comments for emerald
                cout << "How many platinums would you like to sell?" << endl;
                cin >> amt;
                if (amt > mp.getTreasure(2))
                {
                    cout << "You do not have this many platinums!!" << endl;
                    break;
                }
                if (amt < 0)
                {
                    cout << "Invalid Input!" << endl;
                    break;
                }
                cout << "Are you sure you would like to sell " << amt << " platinum(s) for " << amt * merch.getPlatinum() << " Gold? (y/n)" << endl;
                cin >> confirm;
                switch (confirm)
                {
                    case 'y':
                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                    mp.addGold(amt * merch.getPlatinum());
                    mp.setTreasure(2, mp.getTreasure(2) - amt);
                    break;
                    case 'n':
                    cout << "No problem. What else can I get for you?" << endl;
                    break;
                    default:
                    cout << "I DON'T UNDERSTAND YOU!!" << endl;
                    break;
                }
                break;
                // Obsidians
                case 4:
                // Check comments for emerald
                cout << "How many obsidians would you like to sell?" << endl;
                cin >> amt;
                if (amt > mp.getTreasure(3))
                {
                    cout << "You do not have this many obsidians!!" << endl;
                    break;
                }
                if (amt < 0)
                {
                    cout << "Invalid Input!" << endl;
                    break;
                }
                cout << "Are you sure you would like to sell " << amt << " obsidian(s) for " << amt * merch.getObsidian() << " Gold? (y/n)" << endl;
                cin >> confirm;
                switch (confirm)
                {
                    case 'y':
                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                    mp.addGold(amt * merch.getObsidian());
                    mp.setTreasure(3, mp.getTreasure(3) - amt);
                    break;
                    case 'n':
                    cout << "No problem. What else can I get for you?" << endl;
                    break;
                    default:
                    cout << "I DON'T UNDERSTAND YOU!!" << endl;
                    break;
                }
                break;
                // Dragon Scales
                case 5:
                // Check comments for emerald
                cout << "How many dragon scales would you like to sell?" << endl;
                cin >> amt;
                if (amt > mp.getTreasure(4))
                {
                    cout << "You do not have this many dragon scales!!" << endl;
                    break;
                }
                if (amt < 0)
                {
                    cout << "Invalid Input!" << endl;
                    break;
                }
                cout << "Are you sure you would like to sell " << amt << " dragon scale(s) for " << amt * merch.getScale() << " Gold? (y/n)" << endl;
                cin >> confirm;
                switch (confirm)
                {
                    case 'y':
                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                    mp.addGold(amt * merch.getScale());
                    mp.setTreasure(4, mp.getTreasure(4) - amt);
                    break;
                    case 'n':
                    cout << "No problem. What else can I get for you?" << endl;
                    break;
                    default:
                    cout << "I DON'T UNDERSTAND YOU!!" << endl;
                    break;
                }
                break;
                case 6:
                // Cancel sale
                cout << "The transaction has been cancelled." << endl;
                break;
                // Invalid Input
                default:
                cout << "Invalid Input. The transaction has been cancelled." << endl;
                break;
            }
            merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
            mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
            mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
            cin >> menu;
            break;
            default:
            cout << "Please enter a valid input!" << endl;
            merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
            mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
            mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
            cin >> menu;
            break;
        }
    }

    // Display Party's Status
    mp.displayParty(anger_level, party, 0);

    // Display map
    m.displayMap();

    // Set player's current tile to the tile they are initially on
    mp.setCurrentTile(m.getTile(m.getPlayerRow(), m.getPlayerCol()));

    char direction; // Used for player's input for moving
    string treasures[5] = {"Emerald", "Ruby", "Platinum",
    "Obsidian", "Dragon Scale"}; // Used to indicate what treasure the player has found
    int monsters_defeated = 0; // Store how many monsters defeated for specific level
    int monsters_stored = 0; // Number of monster stored
    int monsters_defeated_[25]; // Array of indexes of monsters defeated
    string monsters[25]; // Array of monster names
    int monster_levels[25]; // Array of monster levels
    string arr[2]; // Temporary array to store monsters and riddles with split function
    ifstream fin;
    fin.open("riddles.txt"); // Open riddle file
    string line; // Temporary string to store line for split function
    int i = 0;
    int w; // Number of weapons used in battle equation
    int d; // Special int used in battle equation
    int a; // Armour party has used in battle equation
    int c; // Current monster level used in battle equation
    int r_1; // One random int generated for battle equation
    int r_2; // Second random int generated for battle equation
    int temp; // Temp int
    Npc np = Npc(); // Create npc
    string riddles[20]; // Create array for all riddles
    string answers[20]; // Create array for all riddle answers
    int riddles_stored; // Riddles stored used to store all riddles
    int riddle; // Current riddle index
    string answer; // String answer for generated riddle
    int ans; // Int generated from random riddle
    // Loop through file and store all riddles in riddle array
    while (getline(fin, line))
    {
        if (split(line, '~', arr, 20) == 2)
        {
            riddles[riddles_stored] = arr[0];
            answers[riddles_stored] = arr[1];
        }
        riddles_stored++;
    }
    fin.close(); // Close riddle file
    fin.open("monsters.txt"); // Open monster filer
    // Loop through file and store all monsters in monster array
    while (getline(fin, line))
    {
        if (split(line, ',', arr, 25) == 2)
        {
            monsters[monsters_stored] = arr[0];
            monster_levels[monsters_stored] = stoi(arr[1]);
        }
        monsters_stored++;
    }
    fin.close(); // Close monster file
    // Loop through game
    while (mp.getCurrentTile() != 'Q')
    {
        // Check if tile is Npc -> Change to N if yes
        if (mp.getCurrentTile() == '-')
        {
            if (m.isNPCLocation(m.getPlayerRow(), m.getPlayerCol()))
            {
                mp.setCurrentTile('N');
            }
        }
        switch(mp.getCurrentTile())
        {
            // Normal Tile/Explored Tile
            case ' ':
            case '-':
            // Prompt normal tile menu
            cout << "You are on an ordinary tile, traveler." << endl;
            cout << "What would you like to do?" << endl;
            cout << " 1. Move" << endl;
            cout << " 2. Investigate" << endl;
            cout << " 3. Pick a Fight" << endl;
            cout << " 4. Cook and Eat" << endl;
            cout << " 5. Give Up" << endl;
            // Get user input
            cin >> option;
            switch (option)
            {
                // Move option
                case 1:
                cout << "What direction would you like to move? (w - up, s - down, a - left, d - right)" << endl;
                cin >> direction;
                m.move(direction);
                // Increase anger level on non-explored tiles
                if (!m.isExplored(m.getPlayerRow(), m.getPlayerCol()) && mp.getRoomsCleared() != 5)
                {
                    anger_level++;
                }
                // 20% you lose a fullness point
                rand_num = (rand() % 10) + 1;
                if (rand_num <= 2)
                {
                    cout << "You have lost a fullness point." << endl;
                    mp.setFullness(mp.getFullness() - 1);
                    cout << "Your current fullness: " << mp.getFullness() << endl;
                }
                for (int i = 0; i < mp.getCompanions(); i++)
                {
                    // 20% each person loses a fullness point
                    rand_num = (rand() % 10) + 1;
                    if (rand_num <= 2)
                    {
                        party[i].setFullness(party[i].getFullness() - 1);
                        cout << party[i].getName() << " has lost a fullness point." << endl;
                        cout << party[i].getName() << "'s current fullness: " << party[i].getFullness() << endl;
                    }
                }
                // Display status, map, and change tile
                mp.displayParty(anger_level, party, monsters_defeated);
                m.displayMap();
                mp.setCurrentTile(m.getTile(m.getPlayerRow(), m.getPlayerCol()));
                break;
                // Invesitage Option
                case 2:
                // Verify spot isn't already explored
                if (m.isExplored(m.getPlayerRow(), m.getPlayerCol()))
                {
                    cout << "This tile has already been explored." << endl;
                    mp.displayParty(anger_level, party, monsters_defeated);
                    m.displayMap();
                    break;
                }
                // Notify the tile has been explored
                cout << "You have explored the tile!" << endl;
                // 10% find a key
                rand_num = (rand() % 10) + 1;
                if (rand_num == 1)
                {
                    cout << "You have found a key!" << endl;
                    mp.addKey();
                    rand_num = (rand() % 10) + 1;
                    // 50% chance each person loses fullness point
                    if (rand_num <= 5)
                    {
                        cout << "You have lost a fullness point." << endl;
                        mp.setFullness(mp.getFullness() - 1);
                        cout << "Your current fullness: " << mp.getFullness() << endl;
                    }
                    for (int i = 0; i < mp.getCompanions(); i++)
                    {
                        rand_num = (rand() % 10) + 1;
                        if (rand_num <= 5)
                        {
                            party[i].setFullness(party[i].getFullness() - 1);
                            cout << party[i].getName() << " has lost a fullness point." << endl;
                            cout << party[i].getName() << "'s current fullness: " << party[i].getFullness() << endl;
                        }
                    }
                    // Explore the space, display party, display map
                    m.exploreSpace(m.getPlayerRow(), m.getPlayerCol());
                    mp.displayParty(anger_level, party, monsters_defeated);
                    m.displayMap();
                    break;
                }
                else if (rand_num == 2 || rand_num == 3) // 20% to find a gem, depending on amount of rooms cleared
                {
                    // Notify user of treasure
                    cout << "Congratulations! You have found a(n) " << treasures[mp.getRoomsCleared()] << "!" << endl;
                    mp.setTreasure(mp.getRoomsCleared(), mp.getTreasure(mp.getRoomsCleared()) + 1);
                    m.exploreSpace(m.getPlayerRow(), m.getPlayerCol());
                    // Same fullness properties as before
                    rand_num = (rand() % 10) + 1;
                    if (rand_num <= 5)
                    {
                        cout << "You have lost a fullness point." << endl;
                        mp.setFullness(mp.getFullness() - 1);
                        cout << "Your current fullness: " << mp.getFullness() << endl;
                    }
                    for (int i = 0; i < mp.getCompanions(); i++)
                    {
                        rand_num = (rand() % 10) + 1;
                        if (rand_num <= 5)
                        {
                            party[i].setFullness(party[i].getFullness() - 1);
                            cout << party[i].getName() << " has lost a fullness point." << endl;
                            cout << party[i].getName() << "'s current fullness: " << party[i].getFullness() << endl;
                        }
                    }
                    mp.displayParty(anger_level, party, monsters_defeated);
                    m.displayMap();
                    break;
                }
                else if (rand_num == 4 || rand_num == 5) // 20% chance to spawn monster
                {
                    // Spawn Monster
                    if (mp.getRoomsCleared() == 5) // If all rooms cleared, stop spawning monsters
                    {
                        cout << "You have defeated all of the monsters!" << endl;
                        cout << "Head to the dungeon exit, marked as 'E' on the map to escape!" << endl;
                    }
                    if (monsters_defeated == 4) // If all current level monsters defeated
                    {
                        cout << "You must clear another room to fight more monsters!" << endl;
                        mp.displayParty(anger_level, party, monsters_defeated);
                        m.displayMap();
                        break;
                    }
                    rand_num = (rand() % 4) + (4 * (mp.getRoomsCleared())); // Generate rand number between 4 * amount of rooms cleared and 4
                    while (i < monsters_defeated) // While i is less than monsters defeated (i = temp holder, counting amount of elements in monsters_defeated_)
                    {
                        if (monsters_defeated_[i] == rand_num) // If monster has already been defeated
                        {
                            rand_num = (rand() % 4) + (4 * (mp.getRoomsCleared())); // Generate new number
                            i = 0; // Set i to 0, begin from beginning of array
                        }
                        else
                        {
                            i++; // If not, increase i by 1 to move onto next element
                        }
                    }
                    temp = rand_num; // Store the rand_num (monster) in temp var
                    i = 0;
                    // Print level and name of monster encountered
                    cout << "LEVEL " << monster_levels[rand_num] << " " << monsters[rand_num] << " AHEAD! THEY LOOK HOSTILE!" << endl;
                    // If party has no weapons or no armour
                    if (mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) <= 0 || mp.getArmour() <= 0)
                    {
                        cout << "Your party was unprepared and you were forced to surrender!" << endl;
                        // Select party member at bottom of list (last left behind falls)
                        // Notify player of lost companion
                        cout << party[mp.getCompanions() - 1].getName() << " was unable to escape the monster's wrath." << endl;
                        cout << "You will have to continue the journey without them." << endl;
                        // Remove weapon and armour if player has more than party members alive
                        // If not, do nothing
                        if (mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) > mp.getCompanions())
                        {
                            for (int i = 0; i < 4; i++)
                            {
                                if (mp.getWeapon(i) > 0)
                                {
                                    mp.setWeapon(i, mp.getWeapon(i) - 1);
                                }
                            }
                        }
                        if (mp.getArmour() > mp.getCompanions())
                        {
                            mp.setArmour(mp.getArmour() - 1);
                        }
                        // Remove selected party member
                        party.pop_back();
                        mp.removeCompanion();
                        mp.displayParty(anger_level, party, monsters_defeated);
                        m.displayMap();
                        break;
                    }
                    // Prompt user with action options
                    cout << "What would you like to do?" << endl;
                    cout << " 1. Attack" << endl;
                    cout << " 2. Surrender" << endl;
                    cin >> amt;
                    switch (amt)
                    {
                        // Case attack
                        case 1:
                        // Calculate variables for monster fight
                        // Weapons owned my party
                        w = mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) + (mp.getWeapon(1) * 2) + (mp.getWeapon(2) * 3) + (mp.getWeapon(3) * 5);
                        // If all party members have a weapon
                        if (mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) >= mp.getCompanions() + 1)
                        {
                            d = 4;
                        }
                        else
                        {
                            d = 0;
                        }
                        a = mp.getArmour(); // Amount of armour owned by party
                        c = monster_levels[rand_num]; // Current level of monster
                        r_1 = (rand() % 6) + 1; // First rand number
                        r_2 = (rand() % 6) + 1; // Second rand number
                        // Fight against monster won
                        if ((r_1 * w + d) - ((r_2 * c)/a) > 0) // Formula for fight
                        {
                            // Display winning message
                            cout << "You have defeated the level " << monster_levels[rand_num] << " " << monsters[rand_num] << "!" << endl;
                            cout << "Your party moves on unscathed!" << endl;
                            cout << "You have received:" << endl;
                            cout << 10 * c << " Gold" << endl;
                            cout << 5 * c << " kg of ingredients" << endl;
                            mp.addGold(10 * c); // Receive 10 * level of monster gold
                            mp.setIngredients(mp.getIngredients() + (5 * c)); // Receive 5 * level of monster ingredients
                            rand_num = (rand() % 10) + 1;
                            if (rand_num == 1) // 10% chance for key drop
                            {
                                cout << "The monster has dropped a key!" << endl;
                                mp.addKey();
                            }
                            rand_num = (rand() % 10) + 1;
                            if (rand_num <= 5) // 50% chance to lose fullness point
                            {
                                mp.setFullness(mp.getFullness() - 1);
                                cout << "You have lost a fullness point!" << endl;
                                cout << "Your current fullness: " << mp.getFullness() << endl;
                            }
                            for (int i = 0; i < mp.getCompanions(); i++)
                            {
                                rand_num = (rand() % 10) + 1;
                                if (rand_num <= 5)
                                {
                                    party[i].setFullness(party[i].getFullness() - 1);
                                    cout << party[i].getName() << " has lost a fullness point!" << endl;
                                    cout << party[i].getName() << "'s current fullness: " << party[i].getFullness() << endl;
                                }
                            }
                            monsters_defeated_[monsters_defeated] = temp; // Stored the defeated monster
                            monsters_defeated++;
                            break;
                        }
                        // Fight against monster lost
                        else
                        {
                            // Display losing message
                            cout << "You have lost the battle!" << endl;
                            cout << "You have lost: " << endl << (int)(mp.getGold() * 0.25) << " Gold" << endl;
                            mp.addGold(-1 * (mp.getGold() * 0.25)); // Lose 25% of gold
                            mp.setIngredients(mp.getIngredients() - (r_1 * 5)); // Lose 0 - 30kg ingredients
                            cout << r_1 * 5 << " kg of ingredients" << endl;
                            rand_num = (rand() % 10) + 1;
                            if (rand_num <= mp.getCompanions() + 1) // Generate random num, chance of passing depends on amount of companions alive
                            {
                                // Remove party member, weapons, and armour if statement passes
                                cout << party[mp.getCompanions() - 1].getName() << " was unable to escape the monster's wrath." << endl;
                                cout << "You will have to continue the journey without them." << endl;
                                if (mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) > mp.getCompanions())
                                {
                                    for (int i = 0; i < 4; i++)
                                    {
                                        if (mp.getWeapon(i) > 0)
                                        {
                                            mp.setWeapon(i, mp.getWeapon(i) - 1);
                                        }
                                    }
                                }
                                if (mp.getArmour() > mp.getCompanions())
                                {
                                    mp.setArmour(mp.getArmour() - 1);
                                }
                                party.pop_back(); // Removes last companion
                                mp.removeCompanion();
                                break;
                            }
                            else
                            {
                                break;
                            } 
                        }
                        // Case surrender
                        case 2:
                        cout << "You have surrendered!" << endl;
                        cout << party[mp.getCompanions() - 1].getName() << " was unable to escape the monster's wrath." << endl;
                        cout << "You will have to continue the journey without them." << endl;
                        party.pop_back();
                        if (mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) > mp.getCompanions())
                        {
                            for (int i = 0; i < 4; i++)
                            {
                                if (mp.getWeapon(i) > 0)
                                {
                                    mp.setWeapon(i, mp.getWeapon(i) - 1);
                                }
                            }
                        }
                        if (mp.getArmour() > mp.getCompanions())
                        {
                            mp.setArmour(mp.getArmour() - 1);
                        }
                        mp.removeCompanion();
                        break;
                    }
                    m.exploreSpace(m.getPlayerRow(), m.getPlayerCol());
                    mp.displayParty(anger_level, party, monsters_defeated);
                    m.displayMap();
                    break;
                }
                // If nothing found
                else
                {
                    cout << "You didn't uncover anything." << endl;
                    rand_num = (rand() % 10) + 1;
                    if (rand_num <= 5) // Equal chance to lose fullness point
                    {
                        cout << "You have lost a fullness point." << endl;
                        mp.setFullness(mp.getFullness() - 1);
                        cout << "Your current fullness: " << mp.getFullness() << endl;
                    }
                    for (int i = 0; i < mp.getCompanions(); i++)
                    {
                        rand_num = (rand() % 10) + 1;
                        if (rand_num <= 5)
                        {
                            party[i].setFullness(party[i].getFullness() - 1);
                            cout << party[i].getName() << " has lost a fullness point." << endl;
                            cout << party[i].getName() << "'s current fullness: " << party[i].getFullness() << endl;
                        }
                    }
                    // Explore the space
                    m.exploreSpace(m.getPlayerRow(), m.getPlayerCol());
                    mp.displayParty(anger_level, party, monsters_defeated);
                    m.displayMap();
                    break;
                }
                // Pick a fight
                case 3:
                // Code is same above, check comments above
                if (mp.getRoomsCleared() == 5)
                {
                    cout << "You have defeated all of the monsters!" << endl;
                    cout << "Head to the dungeon exit, marked as 'E' on the map to escape!" << endl;
                }
                if (monsters_defeated == 4)
                {
                    cout << "You must clear another room to fight more monsters!" << endl;
                    mp.displayParty(anger_level, party, monsters_defeated);
                    m.displayMap();
                    break;
                }
                rand_num = (rand() % 4) + (4 * (mp.getRoomsCleared()));
                while (i < monsters_defeated)
                {
                    if (monsters_defeated_[i] == rand_num)
                    {
                        rand_num = (rand() % 4) + (4 * (mp.getRoomsCleared()));
                        i = 0;
                    }
                    else
                    {
                        i++;
                    }
                }
                temp = rand_num;
                i = 0;
                cout << "LEVEL " << monster_levels[rand_num] << " " << monsters[rand_num] << " AHEAD! THEY LOOK HOSTILE!" << endl;
                if (mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) <= 0 || mp.getArmour() <= 0)
                {
                    cout << "Your party was unprepared and you were forced to surrender!" << endl;
                    cout << party[mp.getCompanions() - 1].getName() << " was unable to escape the monster's wrath." << endl;
                    cout << "You will have to continue the journey without them." << endl;
                    if (mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) > mp.getCompanions())
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            if (mp.getWeapon(i) > 0)
                            {
                                mp.setWeapon(i, mp.getWeapon(i) - 1);
                            }
                        }
                    }
                    if (mp.getArmour() > mp.getCompanions())
                    {
                        mp.setArmour(mp.getArmour() - 1);
                    }
                    party.pop_back();
                    mp.removeCompanion();
                    mp.displayParty(anger_level, party, monsters_defeated);
                    m.displayMap();
                    break;
                }
                // Prompt user with action options
                cout << "What would you like to do?" << endl;
                cout << " 1. Attack" << endl;
                cout << " 2. Surrender" << endl;
                cin >> amt;
                switch (amt)
                {
                    case 1:
                    // Calculate variables for monster fight
                    w = mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) + (mp.getWeapon(1) * 2) + (mp.getWeapon(2) * 3) + (mp.getWeapon(3) * 5);
                    if (mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) >= mp.getCompanions() + 1)
                    {
                        d = 4;
                    }
                    else
                    {
                        d = 0;
                    }
                    a = mp.getArmour();
                    c = monster_levels[rand_num];
                    r_1 = (rand() % 6) + 1;
                    r_2 = (rand() % 6) + 1;
                    // Fight against monster won
                    if ((r_1 * w + d) - ((r_2 * c)/a) > 0)
                    {
                        // Display winning message
                        cout << "You have defeated the level " << monster_levels[rand_num] << " " << monsters[rand_num] << "!" << endl;
                        cout << "Your party moves on unscathed!" << endl;
                        cout << "You have received:" << endl;
                        cout << 10 * c << " Gold" << endl;
                        cout << 5 * c << " kg of ingredients" << endl;
                        mp.addGold(10 * c);
                        mp.setIngredients(mp.getIngredients() + (5 * c));
                        rand_num = (rand() % 10) + 1;
                        if (rand_num == 1)
                        {
                            cout << "The monster has dropped a key!" << endl;
                            mp.addKey();
                        }
                        rand_num = (rand() % 10) + 1;
                        if (rand_num <= 5)
                        {
                           mp.setFullness(mp.getFullness() - 1);
                           cout << "You have lost a fullness point!" << endl;
                           cout << "Your current fullness: " << mp.getFullness() << endl;
                        }
                        for (int i = 0; i < mp.getCompanions(); i++)
                        {
                            rand_num = (rand() % 10) + 1;
                            if (rand_num <= 5)
                            {
                                party[i].setFullness(party[i].getFullness() - 1);
                                cout << party[i].getName() << " has lost a fullness point!" << endl;
                                cout << party[i].getName() << "'s current fullness: " << party[i].getFullness() << endl;
                            }
                        }
                        monsters_defeated_[monsters_defeated] = temp;
                        monsters_defeated++;
                        mp.displayParty(anger_level, party, monsters_defeated);
                        m.displayMap();
                        break;
                    }
                    // Fight against monster lost
                    else
                    {
                        // Display losing message
                        cout << "You have lost the battle!" << endl;
                        cout << "You have lost: " << endl << (int)(mp.getGold() * 0.25) << " Gold" << endl;
                        mp.addGold(-1 * (mp.getGold() * 0.25));
                        mp.setIngredients(mp.getIngredients() - (r_1 * 5));
                        cout << r_1 * 5 << " kg of ingredients" << endl;
                        rand_num = (rand() % 10) + 1;
                        if (rand_num <= mp.getCompanions() + 1)
                        {
                            cout << party[mp.getCompanions() - 1].getName() << " was unable to escape the monster's wrath." << endl;
                            cout << "You will have to continue the journey without them." << endl;
                            if (mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) > mp.getCompanions())
                            {
                                for (int i = 0; i < 4; i++)
                                {
                                    if (mp.getWeapon(i) > 0)
                                    {
                                        mp.setWeapon(i, mp.getWeapon(i) - 1);
                                    }
                                }
                            }
                            if (mp.getArmour() > mp.getCompanions())
                            {
                                mp.setArmour(mp.getArmour() - 1);
                            }
                            party.pop_back();
                            mp.removeCompanion();
                            mp.displayParty(anger_level, party, monsters_defeated);
                            m.displayMap();
                            break;
                        }
                        else
                        {
                            mp.displayParty(anger_level, party, monsters_defeated);
                            m.displayMap();
                            break;
                        } 
                    }
                    break;
                    // If random int or 2 is pressed, case surrender
                    default:
                    case 2:
                    cout << "You have surrendered!" << endl;
                    cout << party[mp.getCompanions() - 1].getName() << " was unable to escape the monster's wrath." << endl;
                    cout << "You will have to continue the journey without them." << endl;
                    party.pop_back();
                    if (mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) > mp.getCompanions())
                    {
                        for (int i = 0; i < 4; i++)
                        {
                            if (mp.getWeapon(i) > 0)
                            {
                                mp.setWeapon(i, mp.getWeapon(i) - 1);
                            }
                        }
                    }
                    if (mp.getArmour() > mp.getCompanions())
                    {
                        mp.setArmour(mp.getArmour() - 1);
                    }
                    mp.removeCompanion();
                    mp.displayParty(anger_level, party, monsters_defeated);
                    m.displayMap();
                    break;
                }
                break;
                // Cook and Eat
                case 4:
                // Show user options
                cout << "What cookwear would you like to use?" << endl;
                cout << " 1. Pot (15%)" << endl;
                cout << " 2. Cauldron (2%)" << endl;
                cout << " 3. Cancel" << endl;
                cin >> option;
                switch (option)
                {
                    // Cook and Eat w/ Pot
                    case 1:
                    if (mp.getCookwear(0) < 1) // If user doesn't have pot
                    {
                        cout << "You do not have the required cookwear!" << endl;
                        mp.displayParty(anger_level, party, monsters_defeated);
                        m.displayMap();
                        break;
                    }
                    else if (mp.getIngredients() < 5) // If user doesn't have 5+ ingredients
                    {
                        cout << "You do not have the required ingredients to cook a meal!" << endl;
                        mp.displayParty(anger_level, party, monsters_defeated);
                        m.displayMap();
                        break;
                    }
                    cout << "How many ingredients would you like to cook? (Max amount: " << mp.getIngredients() << ")" << endl;
                    cin >> amt;
                    while (amt % 5 != 0 || amt < 0) // Make sure input is positive multiple of 5
                    {
                        cout << "Please enter a positive multiple 5!" << endl;
                        cin >> amt;
                    }
                    if (amt > mp.getIngredients()) // Make sure user has enough ingredients
                    {
                        cout << "You do not have enough ingredients for this meal!" << endl;
                        mp.displayParty(anger_level, party, monsters_defeated);
                        m.displayMap();
                        break;
                    }
                    rand_num = (rand() % 100) + 1;
                    if (rand_num <= 15) // 15% chance cook fails for pot
                    {
                        cout << "The cook has failed, you have lost your ingredients and cookwear!" << endl;
                        mp.setIngredients(mp.getIngredients() - amt); // Remove ingredients
                        mp.setCookwear(0, mp.getCookwear(0) - 1); // Remove cookwear
                        mp.displayParty(anger_level, party, monsters_defeated);
                        m.displayMap();
                        break;
                    }
                    mp.setFullness(mp.getFullness() + (amt/5)); // Increase 1 point of fullness for each player for every 5kg of ingredients
                    for (int i = 0; i < mp.getCompanions(); i++) // Increase for each player loop
                    {
                        party[i].setFullness(party[i].getFullness() + (amt/5));
                    }
                    // Display cook was successful, remove ingredients
                    cout << "The meal has successfully been created!" << endl;
                    cout << "Everyone in your party has received " << amt/5 << " fullness point(s)!" << endl;
                    mp.setIngredients(mp.getIngredients() - amt);
                    mp.displayParty(anger_level, party, monsters_defeated);
                    m.displayMap();
                    break;
                    // Cook and Eat w/ Cauldron
                    case 2:
                    // Minor changes, check comments aboce
                    if (mp.getCookwear(1) < 1) // Check if user has cauldron
                    {
                        cout << "You do not have the required cookwear!" << endl;
                        mp.displayParty(anger_level, party, monsters_defeated);
                        m.displayMap();
                        break;
                    }
                    else if (mp.getIngredients() < 5)
                    {
                        cout << "You do not have the required ingredients to cook a meal!" << endl;
                        mp.displayParty(anger_level, party, monsters_defeated);
                        m.displayMap();
                        break;
                    }
                    cout << "How many ingredients would you like to cook? (Max amount: " << mp.getIngredients() << ")" << endl;
                    cin >> amt;
                    while (amt % 5 != 0 || amt < 0)
                    {
                        cout << "Please enter a positive multiple 5!" << endl;
                        cin >> amt;
                    }
                    if (amt > mp.getIngredients())
                    {
                        cout << "You do not have enough ingredients for this meal!" << endl;
                        mp.displayParty(anger_level, party, monsters_defeated);
                        m.displayMap();
                        break;
                    }
                    rand_num = (rand() % 100) + 1;
                    if (rand_num <= 2) // 2% chance cauldron fails cook
                    {
                        cout << "The cook has failed, you have lost your ingredients and cookwear!" << endl;
                        mp.setIngredients(mp.getIngredients() - amt);
                        mp.setCookwear(1, mp.getCookwear(1) - 1);
                        mp.displayParty(anger_level, party, monsters_defeated);
                        m.displayMap();
                        break;
                    }
                    mp.setFullness(mp.getFullness() + (amt/5));
                    for (int i = 0; i < mp.getCompanions(); i++)
                    {
                        party[i].setFullness(party[i].getFullness() + (amt/5));
                    }
                    cout << "The meal has successfully been created!" << endl;
                    cout << "Everyone in your party has received " << amt/5 << " fullness point(s)!" << endl;
                    mp.setIngredients(mp.getIngredients() - amt);
                    mp.displayParty(anger_level, party, monsters_defeated);
                    m.displayMap();
                    break;
                    // Case to cancel the meal, do nothing
                    case 3:
                    cout << "You have cancelled the meal." << endl;
                    mp.displayParty(anger_level, party, monsters_defeated);
                    m.displayMap();
                    break;
                    // Case when rand int is inputted, do nothing
                    default:
                    cout << "Invalid Input. Option Cancelled." << endl;
                    mp.displayParty(anger_level, party, monsters_defeated);
                    m.displayMap();
                    break;
                }
                break;
                // Case give up
                case 5:
                // Ask user to confirm
                cout << "Are you sure you would like to end your quest? (y/n)" << endl;
                cin >> confirm;
                if (confirm == 'n')
                {
                    mp.displayParty(anger_level, party, monsters_defeated);
                    m.displayMap();
                }
                else
                {
                    // End game if user confirms option
                    cout << "I am sorry you have made this decision... Better luck next time." << endl;
                    return 0;
                }
                break;
                // Case rand int inputted, do nothing
                default:
                break;
            }
            rand_num = (rand() % 10) + 1;
            if (rand_num <= 4) // 40% chance of misfortune at end of the turn
            {
                mp.misfortune(party);
            }
            break;
            // NPC Tile
            case 'N':
            cout << "You are on an NPC tile, traveler." << endl;
            cout << "What would you like to do?" << endl;
            cout << " 1. Move" << endl;
            cout << " 2. Speak to NPC" << endl;
            cout << " 3. Give Up" << endl;
            m.exploreSpace(m.getPlayerRow(), m.getPlayerCol());
            cin >> option;
            switch (option)
            {
                // Case move, same code as above, check above comments
                case 1:
                cout << "What direction would you like to move? (w - up, s - down, a - left, d - right)" << endl;
                cin >> direction;
                m.move(direction);
                if (!m.isExplored(m.getPlayerRow(), m.getPlayerCol()))
                {
                    anger_level++;
                }
                rand_num = (rand() % 10) + 1;
                if (rand_num <= 2)
                {
                    cout << "You have lost a fullness point." << endl;
                    mp.setFullness(mp.getFullness() - 1);
                    cout << "Your current fullness: " << mp.getFullness() << endl;
                }
                for (int i = 0; i < mp.getCompanions(); i++)
                {
                    rand_num = (rand() % 10) + 1;
                    if (rand_num <= 2)
                    {
                        party[i].setFullness(party[i].getFullness() - 1);
                        cout << party[i].getName() << " has lost a fullness point." << endl;
                        cout << party[i].getName() << "'s current fullness: " << party[i].getFullness() << endl;
                    }
                }
                mp.displayParty(anger_level, party, monsters_defeated);
                m.displayMap();
                mp.setCurrentTile(m.getTile(m.getPlayerRow(), m.getPlayerCol()));
                break;
                // Case speak to npc
                case 2:
                ans = np.randomRiddle(); // Generate a random riddle, store answer
                cout << riddles[ans] << endl; // Display riddle
                cin >> answer; // Get user answer
                if (answer.compare(answers[ans]) == 0) // If user correctly guesses riddle
                {
                    // Display correct message
                    cout << "You have correctly solved the puzzle!" << endl;
                    cout << "The NPC thanks you by opening their shop!" << endl;
                    cout << endl;
                    // Set prices depending on the rooms clear
                    // Display merchant shop
                    // Merchant code same as above, check comments above
                    merch.setPrices(mp.getRoomsCleared());
                    merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
                    mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
                    mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
                    cin >> menu;
                    while (menu != 6)
                    {
                        switch(menu)
                        {
                            // Case for when ingredients are selected
                            case 1:
                            cout << endl;
                            cout << "How many kg of ingredients do you need [" << merch.getIngredients() << " Gold/kg]? (Enter a positive mulitple of 5, or 0 to cancel)" << endl;
                            cin >> option;
                            // Verify it is a valid input
                            while (option % 5 != 0 || option < 0)
                            {
                                cout << "Please enter a positive multiple 5 or 0 to cancel!" << endl;
                                cin >> option;
                            }
                            if (option == 0)
                            {
                                cout << "The transaction has been cancelled." << endl;
                                merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
                                mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
                                mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
                                cin >> menu;
                                break;
                            }
                            if (option * merch.getIngredients() > mp.getGold())
                            {
                                cout << "You have insufficient funds for this purchase." << endl;
                                break;
                            }
                            if (option > 0)
                            {
                                cout << "You want to buy " << option << " kg of ingredients for " << option * merch.getIngredients() << " Gold? (y/n)" << endl;
                            }
                            // Prompt user for confirmation, display messages based on input
                            cin >> confirm;
                            switch (confirm)
                            {
                                case 'y':
                                mp.setIngredients(mp.getIngredients() + option);
                                mp.addGold(-1 * (option * merch.getIngredients()));
                                cout << "Thank you for your patronage! What else can I get for you?" << endl;
                                break;
                                case 'n':
                                cout << "Are you trying to waste my time? What else can I get for you?" << endl;
                                break;
                                default:
                                cout << "I DON'T UNDERSTAND YOU!! (Transaction Failed)" << endl;
                                break;
                            }
                            merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
                            mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
                            mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
                            cin >> menu;
                            break;
                            // Case to display cookwear option
                            case 2:
                            cout << endl;
                            cout << "I have a several types of cookware, which one would you like?" << endl;
                            cout << "Each type has a different probability of breaking when used, marked with (XX%)." << endl;
                            cout << endl;
                            cout << "Choose one of the following:" << endl;
                            cout << " 1. (15%) Pot [" << merch.getPot() << " Gold]" << endl;
                            cout << " 2. ( 2%) Cauldron [" << merch.getCauldron() << " Gold]" << endl;
                            cout << " 3. Cancel" << endl;
                            cin >> option;
                            // Prompt user for input
                            switch (option)
                            {
                                // Case to select pots
                                case 1:
                                cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                                cin >> amt;
                                while (amt < 0)
                                {
                                    cout << "Please enter a valid input!" << endl;
                                    cin >> amt;
                                }
                                if (amt == 0)
                                {
                                    cout << "The transaction has been cancelled." << endl;
                                    merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
                                    mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
                                    mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
                                    cin >> menu;
                                    break;
                                }
                                if (amt * merch.getPot() > mp.getGold())
                                {
                                    cout << "You have insufficient funds for this purchase." << endl;
                                    break;
                                }
                                cout << "You want to buy " << amt << " Pot(s) for " << amt * merch.getPot() << " Gold? (y/n)" << endl;
                                cin >> confirm;
                                switch (confirm)
                                {
                                    case 'y':
                                    mp.setCookwear(0, mp.getCookwear(0) + amt);
                                    mp.addGold(-1 * (amt * merch.getPot()));
                                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                                    break;
                                    case 'n':
                                    cout << "Are you trying to waste my time? What else can I get for you?" << endl;
                                    break;
                                    default:
                                    cout << "I DON'T UNDERSTAND YOU!! (Transaction Failed)" << endl;
                                    break;
                                }
                                break;
                                // Case to select cauldrons
                                case 2:
                                cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                                cin >> amt;
                                while (amt < 0)
                                {
                                    cout << "Please enter a valid input!" << endl;
                                    cin >> amt;
                                }
                                if (amt == 0)
                                {
                                    cout << "The transaction has been cancelled." << endl;
                                    break;
                                }
                                if (amt * merch.getCauldron() > mp.getGold())
                                {
                                    cout << "You have insufficient funds for this purchase." << endl;
                                    break;
                                }
                                cout << "You want to buy " << amt << " Cauldron(s) for " << amt * merch.getCauldron() << " Gold? (y/n)" << endl;
                                cin >> confirm;
                                switch (confirm)
                                {
                                    case 'y':
                                    mp.setCookwear(1, mp.getCookwear(1) + amt);
                                    mp.addGold(-1 * (amt * merch.getCauldron()));
                                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                                    break;
                                    case 'n':
                                    cout << "Are you trying to waste my time? What else can I get for you?" << endl;
                                    break;
                                    default:
                                    cout << "I DON'T UNDERSTAND YOU!! (Transaction Failed)" << endl;
                                    break;
                                }
                                break;
                                // Case to cancel
                                case 3:
                                cout << "The transaction has been cancelled." << endl;
                                break;
                                default:
                                break;
                            }
                            merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
                            mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
                            mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
                            cin >> menu;
                            break;
                            // Case for weapons
                            case 3:
                            cout << endl;
                            if (mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) >= party_size)
                            {
                                cout << "You have purchased the maximum amount of weapons already!" << endl;
                                merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
                                mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
                                mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
                                cin >> menu;
                                break;
                            }
                            // Display weapon options
                            cout << "I have a plentiful collection of weapons to choose from, what would you like?" << endl;
                            cout << "Note that some of them provide you a special bonus in combat, marked by a (+X)." << endl << endl;
                            cout << "Choose one of the following:" << endl;
                            cout << " 1. (+0) Bronze Sword [" << merch.getBronze() << " Gold]" << endl;
                            cout << " 2. (+2) Iron Sword [" << merch.getIron() << " Gold]" << endl;
                            cout << " 3. (+3) Dragon Sword [" << merch.getDragon() << " Gold]" << endl;
                            cout << " 4. (+5) Ancient Rapier [" << merch.getRapier() << " Gold]" << endl;
                            cout << " 5. Cancel" << endl;
                            // Prompt user for input, and display messages accordingly
                            cin >> option;
                            switch (option)
                            {
                                // Bronze sword
                                case 1:
                                cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                                cin >> amt;
                                if (amt + mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) > party_size)
                                {
                                    cout << "You are unable to purchase this amount of weapons." << endl;
                                    cout << "You can only purchase a weapon for each party member." << endl;
                                    cout << "Current max: " << party_size << endl;
                                    break;
                                }
                                while (amt < 0)
                                {
                                    cout << "Please enter a valid input!" << endl;
                                    cin >> amt;
                                }
                                if (amt == 0)
                                {
                                    cout << "The transaction has been cancelled." << endl;
                                    break;
                                }
                                if (amt * merch.getBronze() > mp.getGold())
                                {
                                    cout << "You have insufficient funds for this purchase." << endl;
                                    break;
                                }
                                cout << "You want to buy " << amt << " Bronze Sword(s) for " << amt * merch.getBronze() << " Gold? (y/n)" << endl;
                                cin >> confirm;
                                switch (confirm)
                                {
                                    case 'y':
                                    mp.setWeapon(0, mp.getWeapon(0) + amt);
                                    mp.addGold(-1 * (amt * merch.getBronze()));
                                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                                    break;
                                    case 'n':
                                    cout << "Are you trying to waste my time? What else can I get for you?" << endl;
                                    break;
                                    default:
                                    cout << "I DON'T UNDERSTAND YOU!! (Transaction Failed)" << endl;
                                    break;
                                }
                                break;
                                // Iron Sword
                                case 2:
                                cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                                cin >> amt;
                                if (amt + mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) > party_size)
                                {
                                    cout << "You are unable to purchase this amount of weapons." << endl;
                                    cout << "You can only purchase a weapon for each party member." << endl;
                                    cout << "Current max: " << party_size << endl;
                                    break;
                                }
                                while (amt < 0)
                                {
                                    cout << "Please enter a valid input!" << endl;
                                    cin >> amt;
                                }
                                if (amt == 0)
                                {
                                    cout << "The transaction has been cancelled." << endl;
                                    break;
                                }
                                if (amt * merch.getIron() > mp.getGold())
                                {
                                    cout << "You have insufficient funds for this purchase." << endl;
                                    break;
                                }
                                cout << "You want to buy " << amt << " Iron Sword(s) for " << amt * merch.getIron() << " Gold? (y/n)" << endl;
                                cin >> confirm;
                                switch (confirm)
                                {
                                    case 'y':
                                    mp.setWeapon(1, mp.getWeapon(1) + amt);
                                    mp.addGold(-1 * (amt * merch.getIron()));
                                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                                    break;
                                    case 'n':
                                    cout << "Are you trying to waste my time? What else can I get for you?" << endl;
                                    break;
                                    default:
                                    cout << "I DON'T UNDERSTAND YOU!! (Transaction Failed)" << endl;
                                    break;
                                }
                                break;
                                // Dragon Sword
                                case 3:
                                cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                                cin >> amt;
                                if (amt + mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) > party_size)
                                {
                                    cout << "You are unable to purchase this amount of weapons." << endl;
                                    cout << "You can only purchase a weapon for each party member." << endl;
                                    cout << "Current max: " << party_size << endl;
                                    break;
                                }
                                while (amt < 0)
                                {
                                    cout << "Please enter a valid input!" << endl;
                                    cin >> amt;
                                }
                                if (amt == 0)
                                {
                                    cout << "The transaction has been cancelled." << endl;
                                    break;
                                }
                                if (amt * merch.getDragon() > mp.getGold())
                                {
                                    cout << "You have insufficient funds for this purchase." << endl;
                                    break;
                                }
                                cout << "You want to buy " << amt << " Dragon Sword(s) for " << amt * merch.getDragon() << " Gold? (y/n)" << endl;
                                cin >> confirm;
                                switch (confirm)
                                {
                                    case 'y':
                                    mp.setWeapon(2, mp.getWeapon(2) + amt);
                                    mp.addGold(-1 * (amt * merch.getDragon()));
                                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                                    break;
                                    case 'n':
                                    cout << "Are you trying to waste my time? What else can I get for you?" << endl;
                                    break;
                                    default:
                                    cout << "I DON'T UNDERSTAND YOU!! (Transaction Failed)" << endl;
                                    break;
                                }
                                break;
                                // Ancient Rapier
                                case 4:
                                cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                                cin >> amt;
                                if (amt + mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) > party_size)
                                {
                                    cout << "You are unable to purchase this amount of weapons." << endl;
                                    cout << "You can only purchase a weapon for each party member." << endl;
                                    cout << "Current max: " << party_size << endl;
                                    break;
                                }
                                while (amt < 0)
                                {
                                    cout << "Please enter a valid input!" << endl;
                                    cin >> amt;
                                }
                                if (amt == 0)
                                {
                                    cout << "The transaction has been cancelled." << endl;
                                    break;
                                }
                                if (amt * merch.getRapier() > mp.getGold())
                                {
                                    cout << "You have insufficient funds for this purchase." << endl;
                                    break;
                                }
                                cout << "You want to buy " << amt << " Ancient Rapier(s) for " << amt * merch.getRapier() << " Gold? (y/n)" << endl;
                                cin >> confirm;
                                switch (confirm)
                                {
                                    case 'y':
                                    mp.setWeapon(3, mp.getWeapon(3) + amt);
                                    mp.addGold(-1 * (amt * merch.getRapier()));
                                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                                    break;
                                    case 'n':
                                    cout << "Are you trying to waste my time? What else can I get for you?" << endl;
                                    break;
                                    default:
                                    cout << "I DON'T UNDERSTAND YOU!! (Transaction Failed)" << endl;
                                    break;
                                }
                                break;
                                // Cancel
                                case 5:
                                cout << "The transaction has been cancelled." << endl;
                                break;
                                // Invalid Input
                                default:
                                cout << "Please Enter a Valid Input" << endl;
                                cin >> option;
                                break;
                            }
                            merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
                            mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
                            mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
                            cin >> menu;
                            break;
                            // Case for armour
                            case 4:
                            if (mp.getArmour() >= party_size)
                            {
                                cout << "You have already purchased the maximum amount of armour!" << endl;
                                merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
                                mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
                                mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
                                cin >> menu;
                                break;
                            }
                            cout << "How many suits of armor can I get you? (Enter a positive integer, or 0 to cancel)" << endl;
                            cin >> amt;
                            while (amt < 0)
                            {
                                cout << "Please enter a positive number!" << endl;
                                cin >> amt;
                            }
                            if (amt == 0)
                            {
                                cout << "The transaction has been cancelled." << endl;
                                merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
                                mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
                                mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
                                cin >> menu;
                                break;
                            }
                            if (mp.getArmour() + amt > party_size)
                            {
                                cout << "You can not purchase this much armour!" << endl;
                                cout << "Current max: " << party_size << endl;
                                merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
                                mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
                                mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
                                cin >> menu;
                                break;
                            }
                            if (amt * merch.getArmour() > mp.getGold())
                            {
                                cout << "You have insufficient funds for this purchase." << endl;
                                break;
                            }
                            cout << "You want to buy " << amt << " suit(s) of armor for " << amt * merch.getArmour() << " Gold? (y/n)" << endl;
                            cin >> confirm;
                            switch (confirm)
                            {
                                case 'y':
                                mp.setArmour(amt);
                                mp.addGold(-1 * (amt * merch.getArmour()));
                                cout << "Thank you for your patronage! What else can I get for you?" << endl;
                                break;
                                case 'n':
                                cout << "Are you trying to waste my time? What else can I get for you?" << endl;
                                break;
                                default:
                                cout << "I DON'T UNDERSTAND YOU!! (Transaction Failed)" << endl;
                                break;
                            }
                            merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
                            mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
                            mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
                            cin >> menu;
                            break;
                            // Case for treasures
                            case 5:
                            cout << "What kind of treasure are you looking to sell?" << endl;
                            cout << " 1. Emerald [15 Gold]" << endl;
                            cout << " 2. Ruby [20 Gold]" << endl;
                            cout << " 3. Platinum [30 Gold]" << endl;
                            cout << " 4. Obsidian [50 Gold]" << endl;
                            cout << " 5. Dragon Scale [100 Gold]" << endl;
                            cout << " 6. Cancel" << endl;
                            cin >> option;
                            switch (option)
                            {
                                // Emeralds
                                case 1:
                                cout << "How many emeralds would you like to sell?" << endl;
                                cin >> amt;
                                if (amt > mp.getTreasure(0))
                                {
                                    cout << "You do not have this many emeralds!!" << endl;
                                    break;
                                }
                                if (amt < 0)
                                {
                                    cout << "Invalid Input!" << endl;
                                    break;
                                }
                                cout << "Are you sure you would like to sell " << amt << " emerald(s) for " << amt * merch.getEmerald() << " Gold? (y/n)" << endl;
                                cin >> confirm;
                                switch (confirm)
                                {
                                    case 'y':
                                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                                    mp.addGold(amt * merch.getEmerald());
                                    mp.setTreasure(0, mp.getTreasure(0) - amt);
                                    break;
                                    case 'n':
                                    cout << "No problem. What else can I get for you?" << endl;
                                    break;
                                    default:
                                    cout << "I DON'T UNDERSTAND YOU!!" << endl;
                                    break;
                                }
                                break;
                                // Rubies
                                case 2:
                                cout << "How many rubies would you like to sell?" << endl;
                                cin >> amt;
                                if (amt > mp.getTreasure(1))
                                {
                                    cout << "You do not have this many rubies!!" << endl;
                                    break;
                                }
                                if (amt < 0)
                                {
                                    cout << "Invalid Input!" << endl;
                                    break;
                                }
                                cout << "Are you sure you would like to sell " << amt << " ruby(s) for " << amt * merch.getRuby() << " Gold? (y/n)" << endl;
                                cin >> confirm;
                                switch (confirm)
                                {
                                    case 'y':
                                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                                    mp.addGold(amt * merch.getRuby());
                                    mp.setTreasure(1, mp.getTreasure(1) - amt);
                                    break;
                                    case 'n':
                                    cout << "No problem. What else can I get for you?" << endl;
                                    break;
                                    default:
                                    cout << "I DON'T UNDERSTAND YOU!!" << endl;
                                    break;
                                }
                                break;
                                // Platinums
                                case 3:
                                cout << "How many platinums would you like to sell?" << endl;
                                cin >> amt;
                                if (amt > mp.getTreasure(2))
                                {
                                    cout << "You do not have this many platinums!!" << endl;
                                    break;
                                }
                                if (amt < 0)
                                {
                                    cout << "Invalid Input!" << endl;
                                    break;
                                }
                                cout << "Are you sure you would like to sell " << amt << " platinum(s) for " << amt * merch.getPlatinum() << " Gold? (y/n)" << endl;
                                cin >> confirm;
                                switch (confirm)
                                {
                                    case 'y':
                                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                                    mp.addGold(amt * merch.getPlatinum());
                                    mp.setTreasure(2, mp.getTreasure(2) - amt);
                                    break;
                                    case 'n':
                                    cout << "No problem. What else can I get for you?" << endl;
                                    break;
                                    default:
                                    cout << "I DON'T UNDERSTAND YOU!!" << endl;
                                    break;
                                }
                                break;
                                // Obsidians
                                case 4:
                                cout << "How many obsidians would you like to sell?" << endl;
                                cin >> amt;
                                if (amt > mp.getTreasure(3))
                                {
                                    cout << "You do not have this many obsidians!!" << endl;
                                    break;
                                }
                                if (amt < 0)
                                {
                                    cout << "Invalid Input!" << endl;
                                    break;
                                }
                                cout << "Are you sure you would like to sell " << amt << " obsidian(s) for " << amt * merch.getObsidian() << " Gold? (y/n)" << endl;
                                cin >> confirm;
                                switch (confirm)
                                {
                                    case 'y':
                                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                                    mp.addGold(amt * merch.getObsidian());
                                    mp.setTreasure(3, mp.getTreasure(3) - amt);
                                    break;
                                    case 'n':
                                    cout << "No problem. What else can I get for you?" << endl;
                                    break;
                                    default:
                                    cout << "I DON'T UNDERSTAND YOU!!" << endl;
                                    break;
                                }
                                break;
                                // Dragon Scales
                                case 5:
                                cout << "How many dragon scales would you like to sell?" << endl;
                                cin >> amt;
                                if (amt > mp.getTreasure(4))
                                {
                                    cout << "You do not have this many dragon scales!!" << endl;
                                    break;
                                }
                                if (amt < 0)
                                {
                                    cout << "Invalid Input!" << endl;
                                    break;
                                }
                                cout << "Are you sure you would like to sell " << amt << " dragon scale(s) for " << amt * merch.getScale() << " Gold? (y/n)" << endl;
                                cin >> confirm;
                                switch (confirm)
                                {
                                    case 'y':
                                    cout << "Thank you for your patronage! What else can I get for you?" << endl;
                                    mp.addGold(amt * merch.getScale());
                                    mp.setTreasure(4, mp.getTreasure(4) - amt);
                                    break;
                                    case 'n':
                                    cout << "No problem. What else can I get for you?" << endl;
                                    break;
                                    default:
                                    cout << "I DON'T UNDERSTAND YOU!!" << endl;
                                    break;
                                }
                                break;
                                case 6:
                                // Cancel sale
                                cout << "The transaction has been cancelled." << endl;
                                break;
                                // Invalid Input
                                default:
                                cout << "Invalid Input. The transaction has been cancelled." << endl;
                                break;
                            }
                            merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
                            mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
                            mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
                            cin >> menu;
                            break;
                            default:
                            cout << "Please enter a valid input!" << endl;
                            merch.displayMerchant(mp.getGold(), mp.getIngredients(), mp.getCookwear(0), mp.getCookwear(1),
                            mp.getWeapon(0), mp.getWeapon(1), mp.getWeapon(2), mp.getWeapon(3), mp.getArmour(),
                            mp.getTreasure(0), mp.getTreasure(1), mp.getTreasure(2), mp.getTreasure(3), mp.getTreasure(4));
                            cin >> menu;
                            break;
                        }
                    }

                    // Display Party's Status
                    mp.displayParty(anger_level, party, 0);

                    // Display map
                    m.displayMap();

                    m.removeNPC(m.getPlayerRow(), m.getPlayerCol()); // Remove the npc from the map, replace with ' '
                    mp.setCurrentTile(m.getTile(m.getPlayerRow(), m.getPlayerCol())); // Set the player's current tile to ' '

                }
                else // Player incorrectly guesses riddle
                {
                    cout << "You have incorrectly solved the puzzle and the NPC has become hostile!" << endl;
                    cout << endl;

                    // Npc spawns monster (same as pick a fight code, see above comments)
                    if (mp.getRoomsCleared() == 5)
                    {
                        cout << "You have defeated all of the monsters!" << endl;
                        cout << "Head to the dungeon exit, marked as 'E' on the map to escape!" << endl;
                    }
                    if (monsters_defeated == 4)
                    {
                        cout << "You must clear another room to fight more monsters!" << endl;
                        mp.displayParty(anger_level, party, monsters_defeated);
                        m.displayMap();
                        break;
                    }
                    rand_num = (rand() % 4) + (4 * (mp.getRoomsCleared()));
                    while (i < monsters_defeated)
                    {
                        if (monsters_defeated_[i] == rand_num)
                        {
                            rand_num = (rand() % 4) + (4 * (mp.getRoomsCleared()));
                            i = 0;
                        }
                        else
                        {
                            i++;
                        }
                    }
                    temp = rand_num;
                    i = 0;
                    cout << "THE NPC HAS SUMMONED A LEVEL " << monster_levels[rand_num] << " " << monsters[rand_num] << " !" << endl;
                    if (mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) <= 0 || mp.getArmour() <= 0)
                    {
                        cout << "Your party was unprepared and you were forced to surrender!" << endl;
                        cout << party[mp.getCompanions() - 1].getName() << " was unable to escape the monster's wrath." << endl;
                        cout << "You will have to continue the journey without them." << endl;
                        if (mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) > mp.getCompanions())
                        {
                            for (int i = 0; i < 4; i++)
                            {
                                if (mp.getWeapon(i) > 0)
                                {
                                    mp.setWeapon(i, mp.getWeapon(i) - 1);
                                }
                            }
                        }
                        if (mp.getArmour() > mp.getCompanions())
                        {
                            mp.setArmour(mp.getArmour() - 1);
                        }
                        party.pop_back();
                        mp.removeCompanion();
                        mp.displayParty(anger_level, party, monsters_defeated);
                        m.displayMap();
                        break;
                    }
                    // Prompt user with action options
                    cout << "What would you like to do?" << endl;
                    cout << " 1. Attack" << endl;
                    cout << " 2. Surrender" << endl;
                    cin >> amt;
                    switch (amt)
                    {
                        case 1:
                        // Calculate variables for monster fight
                        w = mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) + (mp.getWeapon(1) * 2) + (mp.getWeapon(2) * 3) + (mp.getWeapon(3) * 5);
                        if (mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) >= mp.getCompanions() + 1)
                        {
                            d = 4;
                        }
                        else
                        {
                            d = 0;
                        }
                        a = mp.getArmour();
                        c = monster_levels[rand_num];
                        r_1 = (rand() % 6) + 1;
                        r_2 = (rand() % 6) + 1;
                        // Fight against monster won
                        if ((r_1 * w + d) - ((r_2 * c)/a) > 0)
                        {
                            // Display winning message
                            cout << "You have defeated the level " << monster_levels[rand_num] << " " << monsters[rand_num] << "!" << endl;
                            cout << "Your party moves on unscathed!" << endl;
                            cout << "You have received:" << endl;
                            cout << 10 * c << " Gold" << endl;
                            cout << 5 * c << " kg of ingredients" << endl;
                            mp.addGold(10 * c);
                            mp.setIngredients(mp.getIngredients() + (5 * c));
                            rand_num = (rand() % 10) + 1;
                            if (rand_num == 1)
                            {
                                cout << "The monster has dropped a key!" << endl;
                                mp.addKey();
                            }
                            rand_num = (rand() % 10) + 1;
                            if (rand_num <= 5)
                            {
                            mp.setFullness(mp.getFullness() - 1);
                            cout << "You have lost a fullness point!" << endl;
                            cout << "Your current fullness: " << mp.getFullness() << endl;
                            }
                            for (int i = 0; i < mp.getCompanions(); i++)
                            {
                                rand_num = (rand() % 10) + 1;
                                if (rand_num <= 5)
                                {
                                    party[i].setFullness(party[i].getFullness() - 1);
                                    cout << party[i].getName() << " has lost a fullness point!" << endl;
                                    cout << party[i].getName() << "'s current fullness: " << party[i].getFullness() << endl;
                                }
                            }
                            monsters_defeated_[monsters_defeated] = temp;
                            monsters_defeated++;
                            mp.displayParty(anger_level, party, monsters_defeated);
                            m.displayMap();
                            break;
                        }
                        // Fight against monster lost
                        else
                        {
                            // Display losing message
                            cout << "You have lost the battle!" << endl;
                            cout << "You have lost: " << endl << (int)(mp.getGold() * 0.25) << " Gold" << endl;
                            mp.addGold(-1 * (mp.getGold() * 0.25));
                            mp.setIngredients(mp.getIngredients() - (r_1 * 5));
                            cout << r_1 * 5 << " kg of ingredients" << endl;
                            rand_num = (rand() % 10) + 1;
                            if (rand_num <= mp.getCompanions() + 1)
                            {
                                cout << party[mp.getCompanions() - 1].getName() << " was unable to escape the monster's wrath." << endl;
                                cout << "You will have to continue the journey without them." << endl;
                                if (mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) > mp.getCompanions())
                                {
                                    for (int i = 0; i < 4; i++)
                                    {
                                        if (mp.getWeapon(i) > 0)
                                        {
                                            mp.setWeapon(i, mp.getWeapon(i) - 1);
                                        }
                                    }
                                }
                                if (mp.getArmour() > mp.getCompanions())
                                {
                                    mp.setArmour(mp.getArmour() - 1);
                                }
                                party.pop_back();
                                mp.removeCompanion();
                                mp.displayParty(anger_level, party, monsters_defeated);
                                m.displayMap();
                                break;
                            }
                            else
                            {
                                mp.displayParty(anger_level, party, monsters_defeated);
                                m.displayMap();
                                break;
                            } 
                        }
                        break;
                        default:
                        case 2:
                        cout << "You have surrendered!" << endl;
                        cout << party[mp.getCompanions() - 1].getName() << " was unable to escape the monster's wrath." << endl;
                        cout << "You will have to continue the journey without them." << endl;
                        party.pop_back();
                        if (mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) > mp.getCompanions())
                        {
                            for (int i = 0; i < 4; i++)
                            {
                                if (mp.getWeapon(i) > 0)
                                {
                                    mp.setWeapon(i, mp.getWeapon(i) - 1);
                                }
                            }
                        }
                        if (mp.getArmour() > mp.getCompanions())
                        {
                            mp.setArmour(mp.getArmour() - 1);
                        }
                        mp.removeCompanion();
                        mp.displayParty(anger_level, party, monsters_defeated);
                        m.displayMap();
                        break;
                    }

                    // Display Party's Status
                    mp.displayParty(anger_level, party, 0);

                    // Display map
                    m.displayMap();

                    m.removeNPC(m.getPlayerRow(), m.getPlayerCol());
                    mp.setCurrentTile(m.getTile(m.getPlayerRow(), m.getPlayerCol()));
                }
                break;
                // Case to give up (same as above code, seem above comments)
                case 3:
                cout << "Are you sure you would like to end your quest? (y/n)" << endl;
                cin >> confirm;
                if (confirm == 'n')
                {
                    mp.displayParty(anger_level, party, monsters_defeated);
                    m.displayMap();
                }
                else
                {
                    cout << "I am sorry you have made this decision... Better luck next time." << endl;
                    return 0;
                }
                break;
                default:
                break;
            }
            rand_num = (rand() % 10) + 1;
            if (rand_num <= 4) // 40% chance of misfortune
            {
                mp.misfortune(party);
            }
            break;
            // Room tile
            case 'R':
            // Prompt user with options
            cout << "You are on a Room tile, traveler." << endl;
            cout << "What would you like to do?" << endl;
            cout << " 1. Move" << endl;
            cout << " 2. Open Door" << endl;
            cout << " 3. Give Up" << endl;
            cin >> option;
            switch (option)
            {
                // Case move (same as above code, see above comments)
                case 1:
                cout << "What direction would you like to move? (w - up, s - down, a - left, d - right)" << endl;
                cin >> direction;
                m.move(direction);
                if (!m.isExplored(m.getPlayerRow(), m.getPlayerCol()))
                {
                    anger_level++;
                }
                rand_num = (rand() % 10) + 1;
                if (rand_num <= 2)
                {
                    cout << "You have lost a fullness point." << endl;
                    mp.setFullness(mp.getFullness() - 1);
                    cout << "Your current fullness: " << mp.getFullness() << endl;
                }
                for (int i = 0; i < mp.getCompanions(); i++)
                {
                    rand_num = (rand() % 10) + 1;
                    if (rand_num <= 2)
                    {
                        party[i].setFullness(party[i].getFullness() - 1);
                        cout << party[i].getName() << " has lost a fullness point." << endl;
                        cout << party[i].getName() << "'s current fullness: " << party[i].getFullness() << endl;
                    }
                }
                mp.displayParty(anger_level, party, monsters_defeated);
                m.displayMap();
                mp.setCurrentTile(m.getTile(m.getPlayerRow(), m.getPlayerCol()));
                break;
                // Case to open door
                case 2:
                if (mp.getKeys() > 0) // If player has at least 1 key
                {
                    // Same as pick a fight code, see above comments, however, monster isn't random, but based on amount of rooms cleared, spawns certain level boss
                    cout << "YOU HAVE ENCOUNTERED A LEVEL " << monster_levels[24 - mp.getRoomsCleared()] <<
                    " SORCERER'S APPRENTICE!" << endl;
                    // Calculate variables for monster fight
                    w = mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) + (mp.getWeapon(1) * 2) + (mp.getWeapon(2) * 3) + (mp.getWeapon(3) * 5);
                    if (mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) >= mp.getCompanions() + 1)
                    {
                        d = 4;
                    }
                    else
                    {
                        d = 0;
                    }
                    a = mp.getArmour();
                    c = monster_levels[rand_num];
                    r_1 = (rand() % 6) + 1;
                    r_2 = (rand() % 6) + 1;
                    // Fight against monster won
                    if ((r_1 * w + d) - ((r_2 * c)/a) > 0)
                    {
                        cout << "YOU HAVE DEFEATED THE SORCERER'S APPRENTICE!" << endl;
                        cout << "GOOD WORK TRAVELER!" << endl;
                        mp.addRoomCleared();
                        m.removeRoom(m.getPlayerRow(), m.getPlayerCol());
                        mp.setCurrentTile(m.getTile(m.getPlayerRow(), m.getPlayerCol()));
                        monsters_defeated = 0;
                        mp.displayParty(anger_level, party, monsters_defeated);
                        m.displayMap();
                        break;
                        // 60% for misfortune
                        rand_num = (rand() % 10) + 1;
                        if (rand_num <= 6)
                        {
                            mp.misfortune(party);
                        }
                    }
                    else
                    {
                        // Display losing message
                        // 40% for misfortune
                        cout << "You have lost the battle!" << endl;
                        cout << "You have lost: " << endl << (int)(mp.getGold() * 0.25) << " Gold" << endl;
                        mp.addGold(-1 * (mp.getGold() * 0.25));
                        mp.setIngredients(mp.getIngredients() - (r_1 * 5));
                        cout << r_1 * 5 << " kg of ingredients" << endl;
                        cout << "1 Key" << endl;
                        mp.removeKey();
                        rand_num = (rand() % 10) + 1;
                        if (rand_num <= mp.getCompanions() + 1)
                        {
                            cout << party[mp.getCompanions() - 1].getName() << " was unable to escape the monster's wrath." << endl;
                            cout << "You will have to continue the journey without them." << endl;
                            party.pop_back();
                            mp.removeCompanion();
                            if (mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) > mp.getCompanions())
                            {
                                for (int i = 0; i < 4; i++)
                                {
                                    if (mp.getWeapon(i) > 0)
                                    {
                                        mp.setWeapon(i, mp.getWeapon(i) - 1);
                                    }
                                }
                            }
                            if (mp.getArmour() > mp.getCompanions())
                            {
                                mp.setArmour(mp.getArmour() - 1);
                            }
                            rand_num = (rand() % 10) + 1;
                            if (rand_num <= 4)
                            {
                                mp.misfortune(party);
                            }
                            mp.displayParty(anger_level, party, monsters_defeated);
                            m.displayMap();
                            break;
                        }
                        else
                        {
                            mp.displayParty(anger_level, party, monsters_defeated);
                            m.displayMap();
                            break;
                        }
                    }
                }
                else // If player has no keys
                {
                    // Puzzle
                    // Prompt user with game of boulder, parchment, shears (rock, paper, scissors)
                    cout << "You have fallen into a trap because your party has no keys!" << endl;
                    cout << "You must win a game of Boulder, Parchment, Shears to proceed safely!" << endl << endl;
                    cout << "Boulder Beats Shears" << endl;
                    cout << "Parchment Beats Boulder" << endl;
                    cout << "Shears Beats Parchment" << endl << endl;
                    cout << "Choose one of the following:" << endl;
                    cout << " 1. Boulder" << endl;
                    cout << " 2. Parchment" << endl;
                    cout << " 3. Shears" << endl;
                    cin >> ans;
                    r_1 = (rand() % 3) + 1; // Generate door's answer
                    while (ans == r_1) // While it is a tie, display that they have tied, generate new rand number, and get new input from user
                    {
                        cout << "You have tied!" << endl;
                        cout << "Please select another option:" << endl;
                        cout << " 1. Boulder" << endl;
                        cout << " 2. Parchment" << endl;
                        cout << " 3. Shears" << endl;
                        cin >> ans;
                        r_1 = (rand() % 3) + 1;
                    }
                    if ((ans == 1 && r_1 == 3) || (ans == 2 && r_1 == 1) || (ans == 3 && r_1 == 2)) // All ways users can win
                    {
                        // Pick a fight with room generated boss
                        cout << "You have beaten the door!" << endl;
                        cout << "You are able to proceed into the room. Good Luck..." << endl;
                        cout << "YOU HAVE ENCOUNTERED A LEVEL " << monster_levels[24 - mp.getRoomsCleared()] <<
                        " SORCERER'S APPRENTICE!" << endl;
                        // Calculate variables for monster fight
                        w = mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) + (mp.getWeapon(1) * 2) + (mp.getWeapon(2) * 3) + (mp.getWeapon(3) * 5);
                        if (mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) >= mp.getCompanions() + 1)
                        {
                            d = 4;
                        }
                        else
                        {
                            d = 0;
                        }
                        a = mp.getArmour();
                        c = monster_levels[rand_num];
                        r_1 = (rand() % 6) + 1;
                        r_2 = (rand() % 6) + 1;
                        // Fight against monster won
                        if ((r_1 * w + d) - ((r_2 * c)/a) > 0)
                        {
                            cout << "YOU HAVE DEFEATED THE SORCERER'S APPRENTICE!" << endl;
                            cout << "GOOD WORK TRAVELER!" << endl;
                            mp.addRoomCleared();
                            m.removeRoom(m.getPlayerRow(), m.getPlayerCol());
                            mp.setCurrentTile(m.getTile(m.getPlayerRow(), m.getPlayerCol()));
                            monsters_defeated = 0;
                            mp.displayParty(anger_level, party, monsters_defeated);
                            m.displayMap();
                            break;
                            // 60% for misfortune
                            rand_num = (rand() % 10) + 1;
                            if (rand_num <= 6)
                            {
                                mp.misfortune(party);
                            }
                        }
                        else
                        {
                            // Display losing message
                            // 40% for misfortune
                            cout << "You have lost the battle!" << endl;
                            cout << "You have lost: " << endl << (int)(mp.getGold() * 0.25) << " Gold" << endl;
                            mp.addGold(-1 * (mp.getGold() * 0.25));
                            mp.setIngredients(mp.getIngredients() - (r_1 * 5));
                            cout << r_1 * 5 << " kg of ingredients" << endl;
                            cout << "1 Key" << endl;
                            mp.removeKey();
                            rand_num = (rand() % 10) + 1;
                            if (rand_num <= mp.getCompanions() + 1)
                            {
                                cout << party[mp.getCompanions() - 1].getName() << " was unable to escape the monster's wrath." << endl;
                                cout << "You will have to continue the journey without them." << endl;
                                party.pop_back();
                                mp.removeCompanion();
                                if (mp.getWeapon(0) + mp.getWeapon(1) + mp.getWeapon(2) + mp.getWeapon(3) > mp.getCompanions())
                                {
                                    for (int i = 0; i < 4; i++)
                                    {
                                        if (mp.getWeapon(i) > 0)
                                        {
                                            mp.setWeapon(i, mp.getWeapon(i) - 1);
                                        }
                                    }
                                }
                                if (mp.getArmour() > mp.getCompanions())
                                {
                                    mp.setArmour(mp.getArmour() - 1);
                                }
                                rand_num = (rand() % 10) + 1;
                                if (rand_num <= 4)
                                {
                                    mp.misfortune(party);
                                }
                                mp.displayParty(anger_level, party, monsters_defeated);
                                m.displayMap();
                                break;
                            }
                            else
                            {
                                mp.displayParty(anger_level, party, monsters_defeated);
                                m.displayMap();
                                break;
                            }
                        }
                    }
                    else // Lose rock, paper, scissors to soor
                    {
                        // Remove companion at end of the list, last left behind
                        cout << "You have lost to the door!" << endl;
                        mp.removeCompanion();
                        cout << "As a result, you have lost " << party[mp.getCompanions()].getName() << " to the dungeon." << endl;
                        cout << "You must continue your journey without them..." << endl;
                        party.pop_back();
                        mp.displayParty(anger_level, party, monsters_defeated);
                        m.displayMap();
                        break;
                    }
                }
                break;
                // Case to give up, same as above
                case 3:
                cout << "Are you sure you would like to end your quest? (y/n)" << endl;
                cin >> confirm;
                if (confirm == 'n')
                {
                    mp.displayParty(anger_level, party, monsters_defeated);
                    m.displayMap();
                }
                else
                {
                    cout << "I am sorry you have made this decision... Better luck next time." << endl;
                    return 0;
                }
                break;
                default:
                break;
            }
            break;
            // Dungeon Exit
            case 'E':
            if (mp.getRoomsCleared() >= 5 && mp.getCompanions() > 0) // If all rooms cleared and at least one companion alive
            {
                // Confirm player is ready to leave
                cout << "You have done well traveler, would you like to leave the dungeon (y/n)" << endl;
                cin >> confirm;
                if (confirm == 'y')
                {
                    cout << "Congratulations! You have defeated the sorcerer and escaped the dungeon alive! Well done, and safe travels." << endl;
                    return 0;
                }
                else // If not ready, allow user to move
                {
                    mp.displayParty(anger_level, party, monsters_defeated);
                    m.displayMap();
                    cout << "What would you like to do?" << endl;
                    cout << " 1. Move" << endl;
                    cin >> option;
                    while (option != 1)
                    {
                        mp.displayParty(anger_level, party, monsters_defeated);
                        m.displayMap();
                        cout << "What would you like to do?" << endl;
                        cout << " 1. Move" << endl;
                        cin >> option;
                    }
                    // Move player based on input
                    cout << "What direction would you like to move? (w - up, s - down, a - left, d - right)" << endl;
                    cin >> direction;
                    m.move(direction);
                    mp.setCurrentTile(m.getTile(m.getPlayerRow(), m.getPlayerCol()));
                    mp.displayParty(anger_level, party, monsters_defeated);
                    m.displayMap();
                }
            }
            else // Either all companions dead or not all rooms cleared
            {
                // User not allowed to leave dungeon
                mp.displayParty(anger_level, party, monsters_defeated);
                m.displayMap();
                cout << "You are unable to leave the dungeon yet traveler." << endl;
                cout << "What would you like to do?" << endl;
                cout << " 1. Move" << endl; // Player must move
                cin >> option;
                while (option != 1)
                {
                    mp.displayParty(anger_level, party, monsters_defeated);
                    m.displayMap();
                    cout << "What would you like to do?" << endl;
                    cout << " 1. Move" << endl;
                    cin >> option;
                }
                // Move player based on input
                cout << "What direction would you like to move? (w - up, s - down, a - left, d - right)" << endl;
                cin >> direction;
                m.move(direction);
                mp.setCurrentTile(m.getTile(m.getPlayerRow(), m.getPlayerCol()));
                mp.displayParty(anger_level, party, monsters_defeated);
                m.displayMap();
            }
            break;
        }
        // Check if anger level is 100 every turn, end game if it is
        if (anger_level == 100)
        {
            cout << "You have angered the sorcerer for far too long!" << endl;
            cout << "The dungeon has collapsed and your party did not make it out alive!" << endl;
            return 0;
        }
        // Check if at least one companion is alive each turn, end game if not
        if (mp.getCompanions() == 0)
        {
            cout << "You have lost all of your companions!" << endl;
            cout << "Better luck next time..." << endl;
            return 0;
        }
        // Check if player's fullness is above 0 every turn, if not, end game
        if (mp.getFullness() == 0)
        {
            cout << "You have died, traveler, causing your party to disband." << endl;
            cout << "Better luck next time..." << endl;
            return 0;
        }
        // Display warning if player's health below 10
        if (mp.getFullness() < 10)
        {
            cout << "Your fullness is getting low!" << endl;
            cout << "Try cooking a meal!" << endl;
        }
        // Check fullness of each companion
        for (int i = 0; i < mp.getCompanions(); i++)
        {
            if (party[i].getFullness() < 10) // Display warning if a companion's health is below 10
            {
                cout << party[i].getName() << "'s fullness is getting low!" << endl;
                cout << "Try cooking a meal!" << endl;
            }
            if (party[i].getFullness() == 0) // If a companion's fullness is 0
            {
                // Remove companion from party if they starve
                cout << "You have lost a companion!" << endl;
                cout << party[i].getName() << " has fallen..." << endl;
                cout << "You must continue the journey without them." << endl;
                cout << endl;
                mp.removeCompanion();
                party[i].setName(party[mp.getCompanions()].getName());
                party[i].setFullness(party[mp.getCompanions()].getFullness());
                party.pop_back();
            }
        }
    }
    return 0;
}