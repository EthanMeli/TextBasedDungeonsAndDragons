#include "Npc.h"
#include <iostream>
using namespace std;

// Default constructer - does nothing
Npc::Npc()
{

}

// Generate a random number between 0 and 19
// Number used to get random riddle and answer in driver
int Npc::randomRiddle()
{
    int rand_num;
    rand_num = (rand() % 19);
    return rand_num;
}