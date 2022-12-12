#include <iostream>
#include <time.h>
#include <cstdlib>
#include "Game.h"
#include "Player.h"
#include "Map.h"
#include "Puzzle.h"
#include "Hacker.h"

using namespace std;

// g++ -std=c++11 Game.cpp Hacker.cpp Map.cpp Player.cpp run.cpp

// the main function is used to create and then run the Game class
// it does no calculations or any of the game, except start it
int main()
{
    // create a game object
    Game game = Game();

    // start the game
    game.start();

    // print that the results are in results.txt
    cout << "Make sure to check your results in the results.txt file" << endl;
    
    return 0;
}
