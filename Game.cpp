#include <iostream>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include "Game.h"
#include "Hacker.h"
#include "Map.h"
#include "Player.h"
#include "Puzzle.h"

using namespace std;

// constructor
Game::Game()
{
    carmen_progress = 0;
    current_server_room = 0;
    num_hackers_defeated = 0;
    room_hackers_defeated = 1;

    for(int i = 0; i < num_hackers; i++)
    {
        hackers[i] = Hacker();
    }

    Player player = Player("PLAYER");
}

// getters
int Game::getCarmenProgress()
{
    return carmen_progress;
}

int Game::getServerRoom()
{
    return current_server_room;
}

int Game::getNumHackersDefeated()
{
    return num_hackers_defeated;
}

Hacker Game::getHacker(int i)
{
    return hackers[i];
}

int Game::getRoomHackersDefeated()
{
    return room_hackers_defeated;
}

// setters
void Game::setCarmenProgress(int cp)
{
    carmen_progress = cp;
}

void Game::setServerRoom(int r)
{
    current_server_room = r;
}

void Game::setNumHackersDefeated(int d)
{
    num_hackers_defeated = d;
}

void Game::setRoomHackersDefeated(int rd)
{
    room_hackers_defeated = rd;
}

// the methods that control the game
/*
* This function does the setting up of the game. It does this by calling the necessary function for
* start up such as reading the hackers into their array, getting the player's name and player object,
* allowing the player to buy things in the first room, creating the server room, and starting their first turn.
* Parameters: none
* Return: nothing
*/
void Game::start()
{
    // initialize a variable to hold the return of the readHackers function
    bool read = readHackers();
    
    // check to make sure the hackers were properly read
    if(!read)
    {
        // if not, state that it has failed and return
        // (if this does ever happen, the game will need to be restarted)
        cout << "Failed, Please Restart" << endl;
        return;
    }

    // declare a variable to hold the player's name and get the players name through their input
    string player_name;
    cout << "Welcome! Please enter your name: ";
    cin >> player_name;

    // set their name to be what they inputted
    player.setName(player_name);

    // welcome the player personally
    cout << "Welcome, " << player.getName() << "!" << endl;

    // print out what the player needs to do to play the game
    cout << "Carmen and her hackers are trying to steal all of the information from 5 server rooms." << endl;
    cout << "Your job is to explore the server rooms and defeat the hackers!" << endl;
    cout << "You need to do this before you get too frustrated, your computer breaks down, or Carmen reaches 100% progress." << endl;
    cout << endl;
    cout << "However, you will need to purchase some starting items before you go." << endl;

    // print what they currently have inventory wise
    cout << "You have 200 dogecoins, 1 computer and 1 VPN." << endl;
    cout << "You will need to spend your money wisely, but be warned." << endl;
    cout << "As you progress, the prices only increase." << endl;
    cout << "(The description of the item is shown when you select it in the menu.)" << endl;
    cout << endl;

    // send them to best buy to start
    bestbuy();

    // call the move server room function, but this actually just generates the first map
    moveServerRoom();

    // start their first turn
    turn();
}

/*
* This function displays the current stats of the player and game. It gives their computer's maintenance,
* number of viruses, number of each computer, number of antivirius, number of VPNs, their internet provider
* level, their current amount of dogecoin, their frustration level, carmen's progess, and the number of hackers
* they have defeated.
* Parameters: none
* Return: void, but prints all stats
*/
void Game::displayStats()
{
    // print out each individual stat on a separate line with getter functions
    cout << "Status Update:" << endl;
    cout << "Computer Maintenance Level: " << player.getComputerMaintenance() << endl;
    cout << "Number of Viruses in Computer: " << player.hasVirius() << endl;
    cout << "Computer Parts Available:" << endl;
    cout << "Number of CPUs: " << player.getCPU() << endl;
    cout << "Number of GPUs: " << player.getGPU() << endl;
    cout << "Number of Power Supply Units: " << player.getPowerSupplyUnits() << endl;
    cout << "Number of Computer Cases: " << player.getComputerCases() << endl;
    cout << "Number of Internet Cards: " << player.getInternetCards() << endl;
    cout << "Number of Keyboards and Mice: " << player.getKeyboardMouse() << endl;
    cout << "Number of Antivirus USB Sticks: " << player.getNumAntivirus() << endl;
    cout << "VPNs Available: " << player.getVPN() << endl;
    cout << "Internet Provider Level: " << player.getInternetLevel() << endl;
    cout << "Dogecoin Available: " << player.getDogecoins() << endl;
    cout << "Frustration Level: " << player.getFrustration() << endl;
    cout << "Carmen’s Progress: " << getCarmenProgress() << endl;
    cout << "Number of Hackers Defeated: " << getNumHackersDefeated() << endl; 
    cout << endl;
}

/*
* This function controls each turn through looping displaying a menu of options and then looping 
* until the player quits or the player wins or loses.
* The first action is to fight a hacker, which is done if the player is on a hacker tile. The second
* action is to talk to an NPC, which is done if the player is on a NPC tile. The third action is to repair 
* the player's computer. The fourth action is to use antivirus software on the computer to remove viruses.
* The fifth action is to explore the server room (or move server rooms if the player is able to). The sixth 
* action is to browse stackoverflow to lower frustration. The seventh action is to quit the game.
* Parameters: none
* Return: void, but will always eventually call the gameEnd function and then break.
*/
void Game::turn()
{
    // declare a variable to hold user input
    int user_choice = 0;

    // do-while loop is perfect because it prints the menu first before switch the user input
    do
    {
        // print out the menu of choices
        cout << "==========Actions==========" << endl;
        cout << "1. Fight a Hacker" << endl;
        cout << "2. Speak to NPC" << endl;
        cout << "3. Repair your Computer" << endl;
        cout << "4. Use Antivirus Software" << endl;
        cout << "5. Explore Server Room (or move server room)" << endl;
        cout << "6. Browse StackOverflow" << endl;
        cout << "7. Quit" << endl;

        // get user input and store in variable declared earlier
        cout << "Please Enter an Action: ";
        cin >> user_choice;

        // switch the user's input
        switch(user_choice)
        {
            // if case 1, then fight hacker
            case 1: {
                // first make sure the player is located on a hacker
                if(!map.isHackerLocation())
                {
                    // otherwise state they are not next to a hacker and break the case
                    cout << "You are not currently next to a hacker!" << endl;
                    break;
                }

                // start a random seed with time(NULL)
                srand(time(NULL));

                // declare a variable to hold a random number from 0-4
                int rand_num = rand() % 4;

                // declare a variable to hold the hacker's number in the hackers array
                int hacker_number = 0;

                // declare a blank hacker to hold the selected hacker
                Hacker hack;

                // loop until an appropriate hacker is found
                do
                {
                    // generate a random number from 0 to 4
                    rand_num = rand() % 4;

                    // switch the current server room
                    switch(current_server_room)
                    {
                        // each case correspons to a different server room 1-5
                        case 1: {
                            // set the hack to be a hacker with level 1
                            // (index in the hacker's array 0-3)
                            hack = hackers[rand_num];

                            // set the hacker number to be the random number
                            hacker_number = rand_num;
                        break;}

                        case 2: {
                            // set the hack to be a hacker with level 2
                            // (index in the hacker's array 4-7)
                            hack = hackers[rand_num + 4];

                            // set the hacker number to be the random number
                            hacker_number = rand_num + 4;
                        break;}

                        case 3: {
                            // set the hack to be a hacker with level 3
                            // (index in the hacker's array 8-11)
                            hack = hackers[rand_num + 8];

                            // set the hacker number to be the random number
                            hacker_number = rand_num + 8;
                        break;}

                        case 4: {
                            // set the hack to be a hacker with level 4
                            // (index in the hacker's array 12-15)
                            hack = hackers[rand_num + 12];

                            // set the hacker number to be the random number
                            hacker_number = rand_num + 12;
                        break;}

                        case 5: {
                            // set the hack to be a hacker with level 5
                            // (index in the hacker's array 16-19)
                            hack = hackers[rand_num + 16];

                            // set the hacker number to be the random number
                            hacker_number = rand_num + 16;
                        break;}
                    }
                // loop until an alive hacker at the appropriate level is found
                }while(!hack.getAlive());

                // call the fightHacker with the hack selected earlier and store the result
                int fight_result = fightHacker(hack);

                // if the fight result is 0, the player won the battle
                if(fight_result == 0)
                {
                    // the hacker was defeated, so set them to be not alive, so they will not be encountered again
                    hackers[hacker_number].setAlive(false);

                    // print that the player won, get 50 dogecoins, but still lose a computer part
                    cout << "You WIN!" << endl;
                    cout << "You get 50 dogecoins, but still manage to drop a computer part." << endl;

                    // get their current amount of dogecoings and add 50
                    int current_doge = player.getDogecoins();
                    player.setDogecoins(current_doge + 50);

                    // 10% of getting virus
                    // generate a random number from 0-9
                    int rand_virius = rand() % 10;

                    // if the random number is 0, then infect the computer with a virus
                    if(rand_virius == 0)
                    {
                        // increase the current number of viruses by 1
                        int current_virius = player.hasVirius();
                        player.setVirius(current_virius + 1);

                        // print that the player was infected with a virus
                        cout << "Your computer has been infected with a virius!" << endl;
                    }

                    // 30% chance of taking 10 computer maintenance
                    // generate a random number from 0-9
                    int rand_main = rand() % 10;

                    // make sure the server room is not 5
                    if(current_server_room == 5)
                    {
                        // nothing happends if the player is in the last server room
                    }
                    // if the random number is 0, 1, or 2, then decrease computer maintenance by 10
                    // (because if it is either one of these then the player got the 30% chance of dropping 10 maintenance)
                    else if(rand_main == 0 || rand_main == 1 || rand_main == 2)
                    {
                        // decrease the current computer maintenance by 10
                        int current_maintenance = player.getComputerMaintenance();
                        player.setComputerMaintenance(current_maintenance - 10);

                        // print that the computer dropped by 10 maintenance
                        cout << "Hm, your 'e' key fell off. Your computer's maintenance dropped by 10." << endl;
                    }

                    // call the function removeRandomComputerPart to remove the computer part
                    removeRandomComputerPart();

                    // increase the number of room hackers defeated by 1
                    // (the total hackers defeated is )
                    int current_room_defeated = getRoomHackersDefeated();
                    setRoomHackersDefeated(current_room_defeated + 1);
                }
                // if the fight result is -1, the player lost and the hacker won
                else if(fight_result == -1)
                {
                    // increase carmen's current progress by 25
                    int current_carmen = getCarmenProgress();
                    setCarmenProgress(current_carmen + 25);

                    // print that the player lost the battle and carmen gained 25 progress and lost 20 maintenance
                    cout << "You lost the battle! Carmen's progress level has increased by 25 and your computer has lost 20 of its maintenance!" << endl;

                    // decrease the current computer maintenance by 20
                    int current_maintenance = player.getComputerMaintenance();
                    player.setComputerMaintenance(current_maintenance - 20);

                    // 10% to get a virus
                    // generate a random number between 0-9
                    int rand_virius = rand() % 10;

                    // if the random number is 0, then infect the computer with a virus
                    if(rand_virius == 0)
                    {
                        // increase the current number of viruses by 1
                        int current_virius = player.hasVirius();
                        player.setVirius(current_virius + 1);

                        // print that the player was infected with a virus
                        cout << "Your computer has been infected with a virius!" << endl;
                    }

                    // 30% chance of dropping 10 computer maintenance
                    // generate a random number from 0-9
                    int rand_main = rand() % 10;

                    // make sure the server room is not 5
                    if(current_server_room == 5)
                    {
                        // nothing happends if the player is in the last server room
                    }
                    // if the random number is 0, 1, or 2, then decrease computer maintenance by 10
                    // (because if it is either one of these then the player got the 30% chance of dropping 10 maintenance)
                    else if(rand_main == 0 || rand_main == 1 || rand_main == 2)
                    {
                        // decrease the current computer maintenance by 10
                        int current_maintenance = player.getComputerMaintenance();
                        player.setComputerMaintenance(current_maintenance - 10);

                        // print that the computer dropped by 10 maintenance
                        cout << "Hm, your 'h' key fell off. Your computer's maintenance dropped by 10." << endl;
                    }

                    // call the function removeRandomComputerPart to remove the computer part
                    removeRandomComputerPart();
                }
                // if the fight result is -2, the player decided to forfeit
                else if(fight_result == -2)
                {
                    // print that they lost all of their spare computer parts
                    cout << "You decided to forfeit and lost all of your spare computer parts!" << endl;

                    // set each computer part to 0
                    player.setCPU(0);
                    player.setGPU(0);
                    player.setPowerSupplyUnits(0);
                    player.setComputerCases(0);
                    player.setInternetCards(0);
                    player.setKeyboardMouse(0);
                }
            break;}

            // if case 2, then the player wants to talk to an NPC
            case 2: {
                // make sure the player is next to an NPC on the map
                if(!map.isNPCLocation())
                {
                    // if not, then print that they are not and break the case
                    cout << "You are not next to a NPC." << endl;
                    break;
                }

                // declare a variable to hold whether or not the player wants to play a puzzle or take their chances
                bool c = false;

                // declare a character to hold the input
                char user_input;

                // propt the user and accept user input about whether they would like to do a puzzle or take their chances
                cout << "Do you want to do the NPC's puzzle or take your chances? (y or n)" << endl;
                cin >> user_input;

                // check to see if the player inputted yes
                if(user_input == 'y')
                {
                    // set that they do want to complete a puzzle
                    c = true;
                }
                // otherwise they inputted no or an invalid input
                else
                {
                    // set that they want to take their chances with the NPC
                    c = false;   
                }

                // call the function talkToNPC with the user's choice as a parameter
                talkToNPC(c);
            break;}

            // if case 3, then the player wants to repair their computer
            case 3: {
                // call the repair computer function in the player class
                player.repairComputer();
            break;}

            // if case 4, then use antivirus software
            case 4: {
                // check to make sure the player actually has a virus on their computer
                if(player.hasVirius() <= 0)
                {
                    // if they don't, then print that and break the case
                    cout << "You don't have any viriuses on your computer!" << endl;
                    break;
                }

                // get the player's current number of antivirus sticks
                int num_anti = player.getNumAntivirus();

                // make sure the player has an antivirus stick and a virus
                if(num_anti > 1 && player.hasVirius() > 1)
                {
                    // decrease the number of antivirus sticks by 1
                    player.setNumAntivirus(num_anti - 1);

                    // set the number of virus to 0
                    player.setVirius(0);
                }
                // otherwise, the player does not have a stick of antivirus
                else
                {
                    // print that the player does not have a stick
                    cout << "You don't have a stick of antivirius to remove the virus." << endl;
                }

            break;}

            // if case 5, then move around the map for up to 10 turns
            case 5: {
                // print that they will move 10 times, but will stop at npcs, and bestbuys. A hack will instantly try to fight them
                cout << "You get to move 10 times before your next turn and will stop if you encounter an npc, bestbuy, or hacker!" << endl;

                // see if the player can move server rooms if the number of room hackers defeated is greater than 1
                if(room_hackers_defeated > 0)
                {
                    // declare a variable to hold the player's input
                    char input;

                    // propt the player to move server rooms and get user input
                    cout << "You have defeated at least one hacker in this room, would you like to move server rooms? (y or n)" << endl;
                    cin >> input;

                    // check to see if they said yes
                    if(input == 'y')
                    {
                        // if they did, then move rooms and allow them to move around the new room
                        cout << "You have chosen to move server rooms. Explore the new room!" << endl;

                        // call the moveServerRoom function
                        moveServerRoom();
                    }
                }

                // declare a variable to hold the player's move
                char player_move;

                // loop for 10 times
                for(int i = 0; i < 10; i++) {
                    // display the map with the displayMap function
                    map.displayMap();

                    // display the valid moves with the displayMoves function
                    cout << "Valid moves are: " << endl; 
                    map.displayMoves();
                    
                    // prompt the user and get a valid move
                    cout << "Input a valid move: "; 
                    cin >> player_move;
                    cout << endl;

                    // execute the move with the executeMove function
                    map.executeMove(player_move);

                    // check to see if the position the player is now on is a best buy
                    if (map.isBestBuyLocation()) {
                        // if it is, say that they have stopped at the best buy
                        cout << "You have stopped at the Best Buy!" << endl;

                        // call the bestbuy function
                        bestbuy();

                        // break from the case
                        break;
                    }

                    // check to see if the position the player is now next to a hacker
                    if (map.isHackerLocation()) {
                        // if they are, then print it
                        cout << "You ran into one of Carmen's Hackers!" << endl;

                        // start a random seed with time(NULL)
                        srand(time(NULL));

                        // declare a variable to hold a random number from 0-4
                        int rand_num = rand() % 4;

                        // declare a variable to hold the hacker's number in the hackers array
                        int hacker_number = 0;

                        // declare a blank hacker to hold the selected hacker
                        Hacker hack;

                        // loop until an appropriate hacker is found
                        do
                        {
                            // generate a random number from 0 to 4
                            rand_num = rand() % 4;

                            // switch the current server room
                            switch(current_server_room)
                            {
                                // each case correspons to a different server room 1-5
                                case 1: {
                                    // set the hack to be a hacker with level 1
                                    // (index in the hacker's array 0-3)
                                    hack = hackers[rand_num];

                                    // set the hacker number to be the random number
                                    hacker_number = rand_num;
                                break;}

                                case 2: {
                                    // set the hack to be a hacker with level 2
                                    // (index in the hacker's array 4-7)
                                    hack = hackers[rand_num + 4];

                                    // set the hacker number to be the random number
                                    hacker_number = rand_num + 4;
                                break;}

                                case 3: {
                                    // set the hack to be a hacker with level 3
                                    // (index in the hacker's array 8-11)
                                    hack = hackers[rand_num + 8];

                                    // set the hacker number to be the random number
                                    hacker_number = rand_num + 8;
                                break;}

                                case 4: {
                                    // set the hack to be a hacker with level 4
                                    // (index in the hacker's array 12-15)
                                    hack = hackers[rand_num + 12];

                                    // set the hacker number to be the random number
                                    hacker_number = rand_num + 12;
                                break;}

                                case 5: {
                                    // set the hack to be a hacker with level 5
                                    // (index in the hacker's array 16-19)
                                    hack = hackers[rand_num + 16];

                                    // set the hacker number to be the random number
                                    hacker_number = rand_num + 16;
                                break;}
                            }
                        // loop until an alive hacker at the appropriate level is found
                        }while(!hack.getAlive());

                        // call the fightHacker with the hack selected earlier and store the result
                        int fight_result = fightHacker(hack);

                        // if the fight result is 0, the player won the battle
                        if(fight_result == 0)
                        {
                            // the hacker was defeated, so set them to be not alive, so they will not be encountered again
                            hackers[hacker_number].setAlive(false);

                            // print that the player won, get 50 dogecoins, but still lose a computer part
                            cout << "You WIN!" << endl;
                            cout << "You get 50 dogecoins, but still manage to drop a computer part." << endl;

                            // get their current amount of dogecoings and add 50
                            int current_doge = player.getDogecoins();
                            player.setDogecoins(current_doge + 50);

                            // 10% of getting virus
                            // generate a random number from 0-9
                            int rand_virius = rand() % 10;

                            // if the random number is 0, then infect the computer with a virus
                            if(rand_virius == 0)
                            {
                                // increase the current number of viruses by 1
                                int current_virius = player.hasVirius();
                                player.setVirius(current_virius + 1);

                                // print that the player was infected with a virus
                                cout << "Your computer has been infected with a virius!" << endl;
                            }

                            // 30% chance of taking 10 computer maintenance
                            // generate a random number from 0-9
                            int rand_main = rand() % 10;

                            // make sure the server room is not 5
                            if(current_server_room == 5)
                            {
                                // nothing happends if the player is in the last server room
                            }
                            // if the random number is 0, 1, or 2, then decrease computer maintenance by 10
                            // (because if it is either one of these then the player got the 30% chance of dropping 10 maintenance)
                            else if(rand_main == 0 || rand_main == 1 || rand_main == 2)
                            {
                                // decrease the current computer maintenance by 10
                                int current_maintenance = player.getComputerMaintenance();
                                player.setComputerMaintenance(current_maintenance - 10);

                                // print that the computer dropped by 10 maintenance
                                cout << "Hm, your 'e' key fell off. Your computer's maintenance dropped by 10." << endl;
                            }

                            // call the function removeRandomComputerPart to remove the computer part
                            removeRandomComputerPart();

                            // increase the number of room hackers defeated by 1
                            // (the total hackers defeated is )
                            int current_room_defeated = getRoomHackersDefeated();
                            setRoomHackersDefeated(current_room_defeated + 1);
                        }
                        // if the fight result is -1, the player lost and the hacker won
                        else if(fight_result == -1)
                        {
                            // increase carmen's current progress by 25
                            int current_carmen = getCarmenProgress();
                            setCarmenProgress(current_carmen + 25);

                            // print that the player lost the battle and carmen gained 25 progress and lost 20 maintenance
                            cout << "You lost the battle! Carmen's progress level has increased by 25 and your computer has lost 20 of its maintenance!" << endl;

                            // decrease the current computer maintenance by 20
                            int current_maintenance = player.getComputerMaintenance();
                            player.setComputerMaintenance(current_maintenance - 20);

                            // 10% to get a virus
                            // generate a random number between 0-9
                            int rand_virius = rand() % 10;

                            // if the random number is 0, then infect the computer with a virus
                            if(rand_virius == 0)
                            {
                                // increase the current number of viruses by 1
                                int current_virius = player.hasVirius();
                                player.setVirius(current_virius + 1);

                                // print that the player was infected with a virus
                                cout << "Your computer has been infected with a virius!" << endl;
                            }

                            // 30% chance of dropping 10 computer maintenance
                            // generate a random number from 0-9
                            int rand_main = rand() % 10;

                            // make sure the server room is not 5
                            if(current_server_room == 5)
                            {
                                // nothing happends if the player is in the last server room
                            }
                            // if the random number is 0, 1, or 2, then decrease computer maintenance by 10
                            // (because if it is either one of these then the player got the 30% chance of dropping 10 maintenance)
                            else if(rand_main == 0 || rand_main == 1 || rand_main == 2)
                            {
                                // decrease the current computer maintenance by 10
                                int current_maintenance = player.getComputerMaintenance();
                                player.setComputerMaintenance(current_maintenance - 10);

                                // print that the computer dropped by 10 maintenance
                                cout << "Hm, your 'h' key fell off. Your computer's maintenance dropped by 10." << endl;
                            }

                            // call the function removeRandomComputerPart to remove the computer part
                            removeRandomComputerPart();
                        }
                        // if the fight result is -2, the player decided to forfeit
                        else if(fight_result == -2)
                        {
                            // print that they lost all of their spare computer parts
                            cout << "You decided to forfeit and lost all of your spare computer parts!" << endl;

                            // set each computer part to 0
                            player.setCPU(0);
                            player.setGPU(0);
                            player.setPowerSupplyUnits(0);
                            player.setComputerCases(0);
                            player.setInternetCards(0);
                            player.setKeyboardMouse(0);
                        }

                        // break the case, so they stop moving
                        break;
                    }

                    // check to see if the player ran into an NPC
                    if (map.isNPCLocation()) {
                        // if they did, then print that they stopped next to them
                        cout << "You have stopped next to an NPC!" << endl;

                        // break from the case
                        break;
                    }

                    // there is a chance of misfortune after every step the player takes, so call the misfortune function
                    // after every step
                    misfortune();
                }
            break;}

            // if case 6, then browse stack overflow
            case 6: {
                // call the browseStackOverflow function
                browseStackOverflow();
            break;}

            // if case 7, then the player has decided to quit the game
            case 7: {
                // print thank you for playing
                cout << "Thanks for playing!" << endl;

                // call the gameEnd function with 4 as the parameter
                gameEnd(4);

                // return the void function, so get kicked out of the function
                return;
            break;}

            // if any other input, its invalid, so print that
            default: cout << "Please enter an integer between 1 and 7" << endl; break;
            
        }

        // after every turn, 30% chance of misfortune, so call misfortune function
        misfortune();

        // after every turn, frustration goes up by 2
        int current_frustration = player.getFrustration();
        player.setFrustration(current_frustration + 2);

        // after every turn, increase money by 5 and 5 per GPU they have
        int current_doge = player.getDogecoins();
        player.setDogecoins(current_doge + 5 + (5 * player.getGPU()));

        // after every turn, update computer maintenance
        int current_maintenance = player.getComputerMaintenance();
        player.setComputerMaintenance(current_maintenance + (10 * player.hasVirius()));

        // after every turn, check to see if game lost or won
        // check to make sure carmen's progress is not at 100
        if(getCarmenProgress() >= 100)
        {
            // if it is, then print that the game has lost
            cout << "OH NO! It looks like the hackers have succeed in stealing all of the information out of the servers." << endl;
            cout << "Better luck next time!" << endl;

            // run the game end function with 1 as the parameter
            gameEnd(1);

            // return the void function, so get kicked out of the function
            return;
        }

        // check to see if the computer's maintenance is at or below 0
        if(player.getComputerMaintenance() <= 0)
        {
            // if it is at or below 0, then check to see if they have a backup computer
            if(player.getBackupComputer())
            {
                // if they do, then remove the backup computer and set the maintenance to 100
                player.setBackupComputer(false);
                player.setComputerMaintenance(100);

                // print that the computer did run out of maintenance, but that they had a backup
                cout << "Your computer just ran out of maintenance, but luckily you had a backup!" << endl;
            }
            // otherwise, they don't have a backup computer and the game is lost
            else
            {
                // print out that the computer broke down and they have no backup
                cout << "Your computer just ran out of maintenance and can no longer function." << endl;
                cout << "You didn't have a backup, so you have lost!" << endl;

                // call the gameEnd function with 2 as the parameter
                gameEnd(2);

                // return the void function, so get kicked out of the function
                return;
            }
        }

        // check to see if the player has 100 or more frustration
        if(player.getFrustration() >= 100)
        {
            // if they have, then they rage quit the game
            // print that they have rage quit
            cout << "OH NO! You have rage quit!" << endl;
            cout << "Looks like you couldn’t handle Carmen’s hackers." << endl;

            // call the gameEnd function with 3 as the parameter
            gameEnd(3);

            // return the void function, so get kicked out of the function
            return;
        }

        // check to see if the player has won the game by getting to the final server room and defeated a hacker
        if(getRoomHackersDefeated() > 0 && current_server_room == 5)
        {
            // if they have, then print that they won
            cout << "YOU WIN!" << endl;
            cout << "You managed to defeat a hacker in every room and stop Caren from stealing all of the server information!" << endl;

            // increase the hackers defeated by the number of hackers defeated in room 5
            int current_hackers_defeated = getNumHackersDefeated();
            setNumHackersDefeated(current_hackers_defeated + getRoomHackersDefeated());

            // call the gameEnd function with 0 as the parameter
            gameEnd(0);

            // return the void function, so get kicked out of the function
            return;
        }

        // after every turn, display stats
        displayStats();
        
    // loop until the player chooses to quit or the function is returned
    }while(user_choice != 7);
}


// this method reads the lines from the hackers.txt file and puts each hacker into the hackers array
// Algorithm:
// 1: open the file
// 2: read each line and split it to put into each hacker
// 3: close the file
// 4: return true if the file could be opened and false otherwise
/*
* This method reads the lines from the hackers.txt file and separates each line into hacker name
* and room number. It then puts this into the hacker array for later use.
* Parameters: No parameters
* Return: true if the array was successfully updated and false otherwise
*/
bool Game::readHackers()
{
    // create a variable to read the file
    ifstream fin;

    // try to open the file
    fin.open("hackers.txt");

    // check to make sure the file opened and return false if it did not
    if(!fin.is_open())
    {
        return false;
    }

    // initialize a variable to hold the index in the hackers array
    int index = 0;

    // declare a string variable to hold each line of the file 
    string line;

    // initialize a variable to hold the size of the split array
    int split_size = 2;
    // declare a string array to hold the split
    string split_line[split_size];

    // loop until the end of the file or the hackers array is full
    while(!fin.eof() && index < 20)
    {
        // get each line from the file
        getline(fin, line);

        // check to make sure it is actually a line
        if(!isspace(line[0]) && line.length() > 1)
        {
            // call the split function
            split(line, ',', split_line, split_size);

            // set the hacker at the current index to be the two parts of the split array
            hackers[index] = Hacker(split_line[0], stoi(split_line[1]));

            // increase the current index of the hackers
            index++;
        }
    }

    // close the file
    fin.close();

    // return true because the hackers were successfully uploaded
    return true;
}

/*
* This was a testing function for the read hackers method. It simply prints all of the 
* hackers names in the order of the array
* Parameters: None
* Return: void, but prints out all of the hackers names currently stored in the hackers array
*/
void Game::printHackers()
{
    // loop through the hackers array and print each name
    for(int i = 0; i < num_hackers; i++)
    {
        cout << hackers[i].getName() << endl;
    }
}

/*
* This function takes a hacker and then prompts the player if they want to fight the hacker or 
* forfeit. If they choose to fight, the hacker's stats are compared against the player and the
* calculation from the write up is done. If the end result is greater than 0, the player wins,
* but if the result is less than 0, the hacker wins. It then returns 0 if the player wins, -1 if
* the hacker wins, and -2 if the player decides to forfeit.
* Parameter: an object of type Hacker
* Return: 0 if the player wins, -1 if the hacker wins, and -2 if the player forfeits
*/
int Game::fightHacker(Hacker hack)
{
    // declare a variable to hold user input
    int user_input = 0;

    // do-while for the menu
    do
    {
        // print the menu and its options
        cout << "You have encountered " << hack.getName() << "!" << endl;
        cout << "Do you choose to " << endl;
        cout << "1. FIGHT" << endl;
        cout << "2. FORFEIT" << endl;

        // prompt the user and get user input
        cout << "Enter an integer:" << endl;
        cin >> user_input;

        // switch the user input for the 4 options it could be
        switch(user_input)
        {
            // if case 1, the player has decided to fight the hacker
            case 1: {
                // generate a random seed with time(NULL)
                srand(time(NULL));

                // generate two random numbers between 1-6
                int rand_1 = (rand() % 6) + 1;
                int rand_2 = (rand() % 6) + 1;

                // store the player's current internet level
                int internet_level = player.getInternetLevel();

                // store the hacker's room number
                int hacker_room = hack.getRoomNum();

                // store the player's number of VPNs
                int vpn = player.getVPN();

                // run the calculation from the writeup
                double battle_score = ((double)rand_1 * (double)internet_level) - (((double)rand_2 * (double)hacker_room) / (double)vpn);

                // check to see what the score was greater or less than 0
                if(battle_score > 0)
                {
                    // if it was greater than 0, then the player won, so return 0
                    return 0;
                }
                // otherwise the score was less than 0
                else
                {
                    // the hacker won, so return -1
                    return -1;
                }

            break;}

            // if case 2, the player decided to forfeit
            case 2: {
                // return -2 to signify that the player forfeited
                return -2;
            break;}

            // if any other input, it is invalid, so print it to show the player
            default: cout << "Invalid Input." << endl; break;
        }
    // loop until 
    }while(user_input != 2 || user_input != 1);

    // in case something breaks, the function returns something
    return 0;
}

/*
* This function allows the player to talk to an npc. The one boolean parameter is if the player wants to solve
* a puzzle or take their chances. This parameter will be true if the player want to complete a puzzle, and false
* if the player wants to take their chances. If it is true, then the player gets a random puzzle and must get it
* correct in order to get a random computer part. If the it is false, then the computer does a random generation of
* three numbers and depending on that the player is attacked, helped, or nothing happends.
* Parameter: boolean representing the player's choice to either complete a puzzle or take their chances
* Return: void, but prints the result of the encounter and adds or takes away random computer parts
*/
void Game::talkToNPC(bool c)
{
    // check to see if the choice is true or false
    if(c)
    {
        // if it is true, then the player wants to complete a puzzle, so print that they chose this option
        cout << "You have chosen to complete a puzzle for a random computer part" << endl;

        // generate a random seed with time(NULL)
        srand(time(NULL));

        // generate a random number between 1-5
        int puzzle_num = (rand() % 5) + 1;

        // put the random number as the puzzle number
        Puzzle puzzle = Puzzle(puzzle_num);

        // call the displayPuzzle function and store the result in a boolean variable
        bool puzzle_result = puzzle.displayPuzzle();

        // check to see if the player got the puzzle correct
        if(puzzle_result)
        {
            // if they did, then print that the NPC is giving a computer part
            cout << "The NPC is giving you a random computer part" << endl;

            // call the addRandomComputerPart function to give the computer part
            addRandomComputerPart();
        }
    }
    // otherwise, the player chose to take their chances against the NPC
    else
    {
        // generate a random seed with time(NULL)
        srand(time(NULL));

        // generate a random number between 0-2
        int rand_num = rand() % 3;

        // each one of these if statements is a 33% chance of occuring because they are each a 1 in 3 chance
        if(rand_num == 0)
        {
            // if the random number is 0, then the NPC is friendly, so print that
            cout << "The NPC is friendly and is giving you a random computer part!" << endl;

            // call the addRandomComputerPart function to give the computer part
            addRandomComputerPart();
        }
        // if the random number is 1, then the NPC is friendly
        else if(rand_num == 1)
        {
            // print so the player can see
            cout << "The NPC is neutral and does nothing" << endl;
        }
        // if the random number is 2, then the NPC is an enemy
        else if(rand_num == 2)
        {
            // print so the player can see
            cout << "The NPC is an enemy and is stealing a random computer part from you!" << endl;

            // call the removeRandomComputerPart function to remove a computer part
            removeRandomComputerPart();
        }
    }
}

/*
* This function allows the player to buy from best buy. It does this by first setting up the proper multiplier
* depending on the room number, then giving them a menu to select computer parts, antivirus software, VPNs, 
* or a certain level of internet. The computer parts and level of internet go into separate menus to show
* all of those specific wares. It then allows the player to select the number of items they would like to 
* purchase and keeps a running total. If at any time the player cannot make a purchase, it tells them and 
* the purchase does not go through.
* Parameters: none
* Return: void, but allows the player to purchase items for their inventory
*/
void Game::bestbuy()
{
    // print to wlcome them to best buy
    cout << "Welcome to best buy!" << endl;

    // initialize a variable to hold the price multiplier
    double multiplier = 1.0;

    // switch the multiplier, so the prices go up depending on the server room
    switch(current_server_room)
    {
        // if case 1, multiplier is just 1
        case 1: multiplier = 1.0; break;

        // if case 2, then add an extra 10%
        case 2: multiplier = 1.1; break;

        // if case 3, then add an extra 20%
        case 3: multiplier = 1.2; break;

        // if case 4, then add an extra 25%
        case 4: multiplier = 1.25; break;

        // if case 5, then add an extra 30%
        case 5: multiplier = 1.3; break;
    }

    // declare a variable to hold the user's input
    int user_choice = 0;

    // declare variable to hold a running total and current total
    int running_total = 0;
    int current_total = 0;

    // declare a variable to hold the number of products the player wants
    int num_product = 0;

    // do-while loop is perfect becasuse of displaying menus
    do
    {
        // display the menu
        cout << "========Items========" << endl;
        cout << "1. Computer Parts" << endl;
        cout << "2. Antivirius Software" << endl;
        cout << "3. Virtual Private Network (VPN)" << endl;
        cout << "4. Internet Provider" << endl;
        cout << "5. Checkout" << endl;
        
        // prompt the user and get user input
        cout << "What would you like to buy?" << endl;
        cin >> user_choice;

        // switch the user input
        switch(user_choice)
        {
            // if case 1, then computer parts
            case 1: {
                // declare a variable to hold the choice of computer part
                int computer_choice = 0;

                // print the menu
                cout << "You can have a maximum of 3 of each computer parts and 1 extra premade computer." << endl;
                cout << "Computer Parts:" << endl;
                cout << "1. CPU (" << int(10.0 * multiplier) << " dogecoins)" << endl;
                cout << "2. GPU (" << int(20.0 * multiplier) << " dogecoins)"<<endl;
                cout << "3. Power Supply Unit (" << int(5.0 * multiplier) << " dogecoins)" << endl;
                cout << "4. Computer Case (" << int(15.0 * multiplier) << " dogecoins)" << endl;
                cout << "5. Internet Card (" << int(5.0 * multiplier) << " dogecoins)" << endl;
                cout << "6. Keyboard and Mouse (" << int(10.0 * multiplier) << " dogecoins)" << endl;
                cout << "7. Premade Computer (" << int(100.0 * multiplier) << " dogecoins)" << endl;
                cout << "8. Nothing" << endl;

                // get user input
                cin >> computer_choice;

                // make sure the user input is valid
                if(computer_choice >= 1 && computer_choice <= 6)
                {
                    // if it is valid, then prompt the user to see how many computer parts they would like
                    cout << "How many would you like to purchase?" << endl;

                    // get user input
                    cin >> num_product;

                    // make sure the user input is greater than 0
                    if(num_product < 0)
                    {
                        // if it is less than 0, then set it to 0
                        num_product = 0;
                    }
                }

                // switch the choice of computer part
                switch(computer_choice)
                {
                    // if case 1, then the player wants CPUs
                    case 1: {
                        // see what the current number of CPUs the player has
                        int current_num = player.getCPU();

                        // make sure the player has room in their inventory for the CPUs they are about to purchase
                        if((current_num + num_product) > 3)
                        {
                            // if they can't then print, so the player can see
                            cout << "You cannot have more than 3 CPUs." << endl;
                        }
                        // otherwise, make sure the player has enough money remaining
                        else if(((num_product * int(10 * multiplier)) + running_total) > player.getDogecoins())
                        {
                            // if they don't, then print that they don't have enough money
                            cout << "You do not have enough dogecoins to make that purchase." << endl;
                        }
                        // otherwise they do have enough money
                        else
                        {
                            // add the money to the running total
                            running_total += num_product * int(10 * multiplier);

                            // give the player their CPUs
                            player.setCPU(current_num + num_product);
                        }
                    break;}

                    // if case 2, then the player wants GPUs
                    case 2: {
                        // store their current number of GPUs
                        int current_num = player.getGPU();

                        // make sure their inventory can handle the purchase
                        if((current_num + num_product) > 3)
                        {
                            // otherwise, print that they cannot have more that 3
                            cout << "You cannot have more than 3 GPUs." << endl;
                        }
                        // check to make sure they have enough dogecoins
                        else if(((num_product * int(20 * multiplier)) + running_total) > player.getDogecoins())
                        {
                            // otherwise, print that they do not have enough
                            cout << "You do not have enough dogecoins to make that purchase." << endl;
                        }
                        // otherwise they do have enough money and inventory space
                        else
                        {
                            // add the purchase to the running total
                            running_total += num_product * int(20 * multiplier);

                            // give the player their GPUs
                            player.setGPU(current_num + num_product);
                        }
                    break;}

                    // if case 3, then the player wants some power supply units
                    case 3: {
                        // store their current amount of power supply units
                        int current_num = player.getPowerSupplyUnits();

                        // make sure their inventory can handle the purchase
                        if((current_num + num_product) > 3)
                        {
                            // otherwise, print that they cannot have more that 3
                            cout << "You cannot have more than 3 power supply units." << endl;
                        }
                        // check to make sure they have enough dogecoins
                        else if(((num_product * int(5 * multiplier)) + running_total) > player.getDogecoins())
                        {
                            cout << "You do not have enough dogecoins to make that purchase." << endl;
                        }
                        // otherwise they do have enough money and inventory space
                        else
                        {
                            // add the purchase amount to the running total
                            running_total += num_product * int(5 * multiplier);

                            // add the items to their inventory
                            player.setPowerSupplyUnits(current_num + num_product);
                        }
                    break;}

                    case 4: {
                        // store the current number of computer cases
                        int current_num = player.getComputerCases();

                        // make sure their inventory can handle the purchase
                        if((current_num + num_product) > 3)
                        {
                            // otherwise, print that they cannot have more that 3
                            cout << "You cannot have more than 3 computer cases." << endl;
                        }
                        // check to make sure they have enough dogecoins
                        else if(((num_product * int(15 * multiplier)) + running_total) > player.getDogecoins())
                        {
                            // otherwise, print that they do not have enough dogecoins
                            cout << "You do not have enough dogecoins to make that purchase." << endl;
                        }
                        // otherwise they do have enough money and inventory space
                        else
                        {
                            // add the purchase amount to the running total
                            running_total += num_product * int(15 * multiplier);

                            // add the items to their inventory
                            player.setComputerCases(current_num + num_product);
                        }
                    break;}

                    case 5: {
                        // store the current number of internet cards
                        int current_num = player.getInternetCards();

                        // make sure their inventory can handle the purchase
                        if((current_num + num_product) > 3)
                        {
                            // otherwise, print that they cannot have more that 3
                            cout << "You cannot have more than 3 internet cards." << endl;
                        }
                        // check to make sure they have enough dogecoins
                        else if(((num_product * int(5 * multiplier)) + running_total) > player.getDogecoins())
                        {
                            // otherwise, print that they do not have enough dogecoins
                            cout << "You do not have enough dogecoins to make that purchase." << endl;
                        }
                        // otherwise they do have enough money and inventory space
                        else
                        {
                            // add the purchase to the running total
                            running_total += num_product * int(5 * multiplier);

                            // add the items to their inventory
                            player.setInternetCards(current_num + num_product);
                        }
                    break;}

                    case 6: {
                        // store the current number of keyboards and mice
                        int current_num = player.getKeyboardMouse();

                        // make sure their inventory can handle the purchase
                        if((current_num + num_product) > 3)
                        {
                            // otherwise, print that they cannot have more that 3
                            cout << "You cannot have more than 3 CPUs." << endl;
                        }
                        // check to make sure they have enough dogecoins
                        else if(((num_product * int(10 * multiplier)) + running_total) > player.getDogecoins())
                        {
                            // otherwise, print that they do not have enough dogecoins
                            cout << "You do not have enough dogecoins to make that purchase." << endl;
                        }
                        // otherwise they do have enough money and inventory space
                        else
                        {
                            // add the total to the running total
                            running_total += num_product * int(10 * multiplier);

                            // add the items to their inventory
                            player.setKeyboardMouse(current_num + num_product);
                        }
                    break;}

                    case 7: {
                        // store the state of their backup computer
                        bool has_backup = player.getBackupComputer();

                        // make sure they don't already have a premade computer
                        if(has_backup)
                        {
                            // otherwise, print that they cannot have more than 1
                            cout << "You cannot have more than 1 premade computer." << endl;
                        }
                        // check to make sure they have enough dogecoins
                        else if((int(100 * multiplier) + running_total) > player.getDogecoins())
                        {
                            // otherwise, print that they do not have enough doge coins
                            cout << "You do not have enough dogecoins to make that purchase." << endl;
                        }
                        // otherwise they do have enough money and inventory space
                        else
                        {
                            // add the cost to the running total
                            running_total += int(100 * multiplier);

                            // add the backup computer to their inventory
                            player.setBackupComputer(true);
                        }
                    break;}

                    // if case 8, then the player does not want to purchase any computer parts at the time
                    case 8: cout << "You have selected that you do not want to purchase any computer parts." << endl; break;
                    
                    // if any otheri input, it is invalid, so print that to the console
                    default: cout << "Invalid Input." << endl; break;
                }

            break;}

            // if case 2, then the player wants some antivirus
            case 2: {
                // print a description, the price, and prompt the user to input the number they want
                cout << "With one stick of antivirius, you can take out all of those pesky viriuses on your computer!" << endl;
                cout << "Each stick of antivirius costs " << int(10 * multiplier) << " dogecoins." << endl;
                cout << "How many would you like to purchase?" << endl;

                // accept user input
                cin >> num_product;

                // make srue the input is greater than 0
                if(num_product < 0)
                {
                    // if not, then set it to 0
                    num_product = 0;
                }

                // check to make sure the player can pay for it
                if(((int(10 * multiplier) * num_product) + running_total) > player.getDogecoins())
                {
                    // if they can't, then print to the console that they dont have enough money
                    cout << "You do not have enough dogecoins to make that purchase." << endl;
                }
                // otherwise they do have enough money
                else
                {
                    // add the purchase amout to the running total
                    running_total += int(10 * multiplier) * num_product;

                    // store their current amount of antivirus sticks
                    int current_anti = player.getNumAntivirus();

                    // add the amount they purchased
                    player.setNumAntivirus(current_anti + num_product);
                }
            break;}

            // if case 3, then the player wants some VPNs
            case 3: {
                // print a description, the max number, the price, and prompt the user to see how many they would like
                cout << "VPNs reduce your chances of getting hacked by preventing hackers from tracking down your main computer!" << endl;
                cout << "The increase in security maxes out at 2 VPNs." << endl;
                cout << "Each new VPN costs " << int(20 * multiplier) << " dogecoins." << endl;
                cout << "How many would you like to purchase?" << endl;

                // get user input for the number they would like to purchase
                cin >> num_product;

                // make sure the input is greater than 0
                if(num_product < 0)
                {
                    // otherwise set it to 0
                    num_product = 0;
                }

                // store the player's current number of VPNs
                int current_num = player.getVPN();

                // make sure that this purchase will not put them over the limit of 2
                if((current_num + num_product) > 2)
                {
                    // otherwise print that they can only have a max of 2
                    cout << "You can only have a maximum of 2 VPNs." << endl;
                }
                // make sure they have enough dogecoins to make the purchase
                else if(((int(20 * multiplier) * num_product) + running_total) > player.getDogecoins())
                {
                    // otherwise, print that they do not have enough dogecoins
                    cout << "You do not have enough dogecoins to make that purchase." << endl;
                }
                // otherwise, they have enough dogecoins and inventory space
                else
                {
                    // increase the running total
                    running_total += num_product * int(20 * multiplier);

                    // increase the number currently in their inventory
                    player.setVPN(current_num + num_product);
                }
            break;}

            // if case 4, then the player wants some level of internet provider
            case 4: {
                // print out the menu of all of the levels of internet and their prices
                cout << "The better your internet provider level, the better you are at hacking!" << endl;
                cout << "Internet provider level 2 (" << int(10 * multiplier) << " dogecoins)" << endl;
                cout << "Internet provider level 3 (" << int(25 * multiplier) << " dogecoins)" << endl;
                cout << "Internet provider level 4 (" << int(40 * multiplier) << " dogecoins)" << endl;
                cout << "Internet provider level 5 (" << int(50 * multiplier) << " dogecoins)" << endl;

                // prompt the user for the level of internet they want and store their input
                cout << "What level would you like to buy?" << endl;
                cin >> num_product;

                // make sure the input is a new level of internet and a viable level of internet
                if(num_product > player.getInternetLevel() && num_product <= 5)
                {
                    // initialize a boolena to check the money
                    bool money_check = true;

                    // loop until the player either reaches the level of internet requested or they run out of money
                    while(player.getInternetLevel() != num_product && money_check)
                    {
                        // get the player's current level of internet
                        int current_level = player.getInternetLevel();

                        // increase that by 1
                        current_level++;

                        // switch the current level of internet
                        switch(current_level)
                        {
                            // if case 2, then upgrading from 1 to 2
                            case 2: {
                                // make sure the player has enough dogecoins
                                if((int(10 * multiplier) + running_total) > player.getDogecoins())
                                {
                                    // otherwise, print that they don't have enough dogecoins
                                    cout << "You do not have enough dogecoins for level 2!" << endl;

                                    // break out of the loop by setting the money check to false
                                    money_check = false;
                                }
                                // otherwise they do have enough money
                                else
                                {
                                    // add this total to the running total
                                    running_total += int(10 * multiplier);

                                    // give the player their new level of internet
                                    player.setInternetLevel(2);
                                }
                            break;}

                            // if case 3, then upgrading from 2 to 3
                            case 3: {
                                // make sure the player has enough dogecoins
                                if((int(25 * multiplier) + running_total) > player.getDogecoins())
                                {
                                    // otherwise, print that they don't have enough dogecoins
                                    cout << "You do not have enough dogecoins for level 3!" << endl;

                                    // break out of the loop by setting the money check to false
                                    money_check = false;
                                }
                                // otherwise they do have enough money
                                else
                                {
                                    // add this total to the running total
                                    running_total += int(25 * multiplier);

                                    // give the player their new level of internet
                                    player.setInternetLevel(3);
                                }
                            break;}

                            // if case 4, then upgrading from 3 to 4
                            case 4: {
                                // make sure the player has enough dogecoins
                                if((int(40 * multiplier) + running_total) > player.getDogecoins())
                                {
                                    // otherwise, print that they don't have enough dogecoins
                                    cout << "You do not have enough dogecoins for level 4!" << endl;

                                    // break out of the loop by setting the money check to false
                                    money_check = false;
                                }
                                // otherwise they do have enough money
                                else
                                {
                                    // add this total to the running total
                                    running_total += int(40 * multiplier);

                                    // give the player their new level of internet
                                    player.setInternetLevel(4);
                                }
                            break;}

                            // if case 5, then upgrading from 4 to 5
                            case 5: {
                                // make sure the player has enough dogecoins
                                if((int(50 * multiplier) + running_total) > player.getDogecoins())
                                {
                                    // otherwise, print that they don't have enough dogecoins
                                    cout << "You do not have enough dogecoins for level 5!" << endl;

                                    // break out of the loop by setting the money check to false
                                    money_check = false;
                                }
                                // otherwise they do have enough money
                                else
                                {
                                    // add this total to the running total
                                    running_total += int(50 * multiplier);

                                    // give the player their new level of internet
                                    player.setInternetLevel(5);
                                }
                            break;}

                        }
                    }

                    // print out the player's new level of internet
                    cout << "Your internet level is " << player.getInternetLevel() << "." << endl;
                }
                // otherwise, check to make sure they did not select over 5
                else if(num_product > 5)
                {
                    // if they did, then print that the max is 5
                    cout << "Internet level maxex out at 5!" << endl;
                }
                // otherwise, the player already has that level of internet
                else
                {
                    // print that to the console
                    cout << "You already have that level of internet!" << endl;
                }

            break;}

            // if case 5, then the player wants to stop shopping and check out, so print their total
            case 5: cout << "Your total is " << running_total << " dogecoins." << endl; break;

            // all other input is invlid, so print that
            default: cout << "Invalid Input." << endl; break;
        }

        // check to see if the running total + the current total is ever greater than their current money
        if((running_total + current_total) > player.getDogecoins())
        {
            // if it is higher, then print that
            cout << "Sorry, but you don't have enough dogecoins to purchase that!" << endl;
        }
        // otherwise, they do have enough money
        else
        {
            // add the current total to the running total
            running_total += current_total;

            // print their current total
            cout << "Your current total is " << running_total << " dogecoins." << endl;
        }

        // reset the current total for the next round of buying
        current_total = 0;

    // loop until the user decides to check out
    }while(user_choice != 5);

    // print the user 
    cout << "You just spent " << running_total << " dogecoins!" << endl;

    // calculate the player's new amount of dogecoins
    int new_doge = player.getDogecoins() - running_total;

    // make them spend the money
    player.setDogecoins(new_doge);

    // print a thank you message
    cout << "Thank you for shopping at Best Buy!" << endl;
    cout << endl;
}

/*
* This function allows the player to browse stack overflow to lower their levels of frustration. It
* does this by first asking if the player would like to solve a puzzle or play rock paper scissors.
* If they want to solve a puzzle, then one is generated for them, and if they would like to play rock
* paper scissors, then they play against a computer with randomized output. This continues until the
* player decides to get off the website
* Parameter: none
* Return: void, but allows the player to solve puzzles and play rock paper scissors
*/
void Game::browseStackOverflow()
{
    // declare a variable to hold the user's input
    int player_choice = 0;

    // welcome the player to the website
    cout << "Welcome to Stack Overflow. Here you can lower your frustration by playing fun games and solving puzzles!" << endl;

    // loop through until the player decides to quit
    do
    {
        // print out the menu and accept user input
        cout << "Would you like to solve a puzzle or play rock, paper, scissors?" << endl;
        cout << "1. Puzzle" << endl;
        cout << "2. Rock, Paper, Scissors" << endl;
        cout << "3. Quit" << endl;
        cin >> player_choice;

        // switch the player's choice
        switch(player_choice)
        {
            // if case 1, the player wants to solve a puzzle
            case 1: {
                // generate a random seed with time(NULL)
                srand(time(NULL));

                // generate a random number between 1-5
                int puzzle_num = (rand() % 5) + 1;

                // generate a puzzle with the random number
                Puzzle puzzle = Puzzle(puzzle_num);

                // have the player solve the puzzle and store the result in a bool variable
                bool puzzle_result = puzzle.displayPuzzle();

                // check to see if the player won (bool is true)
                if(puzzle_result)
                {
                    // if they did, then print that they are correct and their frustration dropped by 5
                    cout << "You are correct and your satisifaction decreased your frustration by 5!" << endl;

                    // get the current frustration
                    int current_frustration = player.getFrustration();

                    // make sure that the drop in frustration will not go below 0
                    if((current_frustration - 5) <= 0)
                    {
                        // if it does, then just set it to 0
                        player.setFrustration(0);
                    }
                    // otherwise, it will not go below 0
                    else
                    {
                        // so, set it to the current - 5
                        player.setFrustration(current_frustration - 5);
                    }
                }
                // otherwise the player was wrong in their answer
                else
                {
                    // print that they are wrong, but nothing happends
                    cout << "You are wrong, but luckily nothing happended." << endl;
                }
            break;}

            // if case 2, then the player wants to play rock paper scissors
            case 2: {
                // initialize a variable to hold the player's choice in rock paper scissors
                int rps_choice = 1;

                // display the menu and recieve user input
                cout << "Choose one of the following options:" << endl;
                cout << "1. Rock" << endl;
                cout << "2. Paper" << endl;
                cout << "3. Scissors" << endl;
                cin >> rps_choice;

                // switch the player's choice to print out their choice
                switch(rps_choice)
                {
                    // if case 1, then rock
                    case 1: {
                        // print that the player chose rock
                        cout << player.getName() << ": ROCK" << endl;
                    break;}

                    // if case 2, then paper
                    case 2: {
                        // print that the player chose paper
                        cout << player.getName() << ": PAPER" << endl;
                    break;}

                    // if case 3, then scissors
                    case 3: {
                        // print that the player chose scissors
                        cout << player.getName() << ": SCISSORS" << endl;
                    break;}

                    // any other input is invalid, so print it, but set the choice to 0
                    default: rps_choice = 0; cout << "Invalid input." << endl; break;
                }

                // declare a variable to hold the computer's choice
                int comp_choice = 1;

                // check to make sure the player's choice is valid
                if(rps_choice != 0)
                {
                    // generate a new seed with time(NULL)
                    srand(time(NULL));

                    // set the computer's choice to between 1-3, just like the player
                    comp_choice = (rand() % 3) + 1;

                    // switch the computer's choice
                    switch(comp_choice)
                    {
                        // if case 1, then rock
                        case 1: {
                            // print that the computer chose rock
                            cout << "Computer: ROCK" << endl;
                        break;}

                        // if case 2, then paper
                        case 2: {
                            // print that the computer chose paper
                            cout << "Computer: PAPER" << endl;
                        break;}

                        // if case 3, then scissors
                        case 3: {
                            // print that the computer chose scissors
                            cout << "Computer: SCISSORS" << endl;
                        break;}
                    }
                }

                // check to make sure the player's choice was valid
                if(rps_choice == 0)
                {
                    // otherwise print that that is not how you play rock paper scissors
                    cout << "That is not how you play rock, paper, scissors!" << endl;
                }
                // check to see if the player and computer drawed
                else if(rps_choice == comp_choice)
                {
                    // if they did, then print that nothing happends
                    cout << "Draw. Nothing happends." << endl;

                    // (also, by checking in this order, if this is false, then I know that the player and computer
                    // did not get the same result, so one of them must have won or lost and the computer's must be
                    // one of the other 2 in comparison to the player)
                }
                // check to see if the player chose 1 or rock
                else if(rps_choice == 1)
                {
                    // if they did, then check to make sure the computer chose 2 or paper
                    if(comp_choice == 2)
                    {
                        // if it did, then the computer wins and wish the player better luck next time
                        cout << "Computer WINS! Paper beats Rock!" << endl;
                        cout << "Better luck next time!" << endl;
                    }
                    // otherwise the computer chose 3 or scissors
                    else
                    {
                        // print that the player wins and looses 5 frustration
                        cout << player.getName() << " WINS! Rock beats Scissors!" << endl;
                        cout << "In your satisfaction you lose 5 frustration!" << endl;

                        // store their current frustration
                        int current_frustration = player.getFrustration();

                        // check to make sure that removing 5 frustration would not be below 0
                        if((current_frustration - 5) <= 0)
                        {
                            // if it does, then set it to 0
                            player.setFrustration(0);
                        }
                        // otherwise it does not go below 0
                        else
                        {
                            // so, just set it to a value 5 lower
                            player.setFrustration(current_frustration - 5);
                        }
                    }
                }
                // check to see if the player chose 2 or paper
                else if(rps_choice == 2)
                {
                    // check to see if the computer chose 1 or rock
                    if(comp_choice == 1)
                    {
                        // the player wins this, so print that they won and lose 5 frustration
                        cout << player.getName() << " WINS! Paper beats Rock!" << endl;
                        cout << "In your satisfaction you lose 5 frustration!" << endl;

                        // store their current frustration
                        int current_frustration = player.getFrustration();

                        // check to make sure that removing 5 frustration would not be below 0
                        if((current_frustration - 5) <= 0)
                        {
                            // if it does, then set it to 0
                            player.setFrustration(0);
                        }
                        // otherwise it does not go below 0
                        else
                        {
                            // so, just set it to a value 5 lower
                            player.setFrustration(current_frustration - 5);
                        }
                    }
                    // otherwise the computer chose 3 or scissors
                    else
                    {
                        // if it did, then the computer wins and wish the player better luck next time
                        cout << "Computer WINS! Scissors beats Paper!" << endl;
                        cout << "Better luck next time!" << endl;
                    }
                }
                // check to see if the player chose 3 or scissors
                else if(rps_choice == 3)
                {
                    // check to see if the computer chose 1 or rock
                    if(comp_choice == 1)
                    {
                        // if it did, then the computer wins and wish the player better luck next time
                        cout << "Computer WINS! Rock beats Scissors!" << endl;
                        cout << "Better luck next time!" << endl;
                    }
                    // otherwise, the computer chose paper
                    else
                    {
                        // the player wins this, so print that they won and lose 5 frustration
                        cout << player.getName() << " WINS! Scissors beats Paper!" << endl;
                        cout << "In your satisfaction you lose 5 frustration!" << endl;

                        // store their current level of frustration
                        int current_frustration = player.getFrustration();

                        // check to make sure that removing 5 frustration would not be below 0
                        if((current_frustration - 5) <= 0)
                        {
                            // if it does, then set it to 0
                            player.setFrustration(0);
                        }
                        // otherwise it does not go below 0
                        else
                        {
                            // so, just set it to a value 5 lower
                            player.setFrustration(current_frustration - 5);
                        }
                    }
                }
            break;}

            // if case 3, then the player wants to leave, so print a good bye message
            case 3: cout << "Thank you for visiting Stack Overflow!" << endl; break;

            // all other input is invalid, so print that
            default: cout << "Invalid Input." << endl; break;
        }

    // loop until the player chooses 3 or quits
    }while(player_choice != 3);
}

/*
* This function moves the server room by generating a new map and increasing the current server room. It
* first checks to make sure the server room can be moved, and will not if it can't. If it can, then it resets
* the map and generates new places for the bestbuy, NPCs, and hackers. It then prints the name of the room and
* display's the new map. It finally sets the room hackers defeated to 0 after adding them to the number of hackers
* defeated.
* Parameters: none
* Return: void, but generates a new server room
*/
void Game::moveServerRoom()
{
    // check to make sure the room can be moved
    if(!canMoveRoom())
    {
        // return the void function if it cannot
        return;
    }

    // make sure the server room is less than 5
    if(current_server_room < 5)
    {
        // increase if it is
        current_server_room++;
    }

    // reset the map with the resetMap function
    map.resetMap();

    // get a random seed with time(NULL)
    srand(time(NULL));

    // declare two variables to hold the current row and column
    int current_row = 0;
    int current_col = 0;

    // declare a variable to be a testing boolean
    bool test = false;

    // if the server room is the first one, then the best buy get spawned on 0,0
    if(current_server_room == 1)
    {
        // if it is, then spawn the best buy on 0, 0
        map.spawnBestBuy(0, 0);
    }
    // otherwise, the best buy can be spawned anywhere randomly
    else
    {
        // do-while is perfect becasue it will run until it properly spawns
        do
        {
            // generate two random numbers: one for the row between 0-3 and one for the column between 0-7
            current_row = rand() % 4;
            current_col = rand() % 8;

            // try to spawn the best buy and store the opposite of the output in the testing boolean
            test = !map.spawnBestBuy(current_row, current_col);

        // loop until the best buy has spawned or the test is false
        }while(test);
    }

    // generate a random number of NPCs to be spawned between 1-3
    int rand_npc_count = (rand() % 3) + 1;

    // make sure the npc count is between 1 and 3
    if(rand_npc_count < 1 || rand_npc_count > 3)
    {
        // otherwise, just set it to be 3
        rand_npc_count = 3;
    }

    // loop until the number of NPCs is equal to the random npc count generated earlier
    while(map.getNPCCount() != rand_npc_count)
    {
        // this is the first instance of a loop inside of another loop
        do
        {
            // generate two random numbers: one for the row between 0-3 and one for the column between 0-7
            current_row = rand() % 4;
            current_col = rand() % 8;

            // try to spawn the NPC and store the opposite of the output in the testing boolean
            test = !map.spawnNPC(current_row, current_col);

        // loop until the NPC has spawned or the test is false
        }while(test);
    }

    // generate a random number of hackers to be spawned between 1-3
    int rand_hacker_count = (rand() % 3) + 1;

    // make sure the npc count is between 1 and 3
    if(rand_hacker_count < 1 || rand_hacker_count > 3)
    {
        // otherwise, just set it to be 3
        rand_hacker_count = 3;
    }

    // loop until the number of NPCs is equal to the random npc count generated earlier
    while(map.getHackerCount() != rand_hacker_count)
    {
        // this is the second instance of a loop inside of another loop
        do
        {
            // generate two random numbers: one for the row between 0-3 and one for the column between 0-7
            current_row = rand() % 4;
            current_col = rand() % 8;

            // try to spawn the hacker and store the opposite of the output in the testing boolean
            test = !map.spawnHacker(current_row, current_col);

        // loop until the hacker has spawned or the test is false
        }while(test);
    }

    // switch the server room
    switch(current_server_room)
    {
        // if case 1, it is the Turing room, so welcome the player
        case 1: cout << "Welcome to the Turing Room!" << endl; break;

        // if case 2, it is the Ellis room, so welcome the player
        case 2: cout << "Welcome to the Ellis Room!" << endl; break;

        // if case 3, it is the Johnson room, so welcome the player
        case 3: cout << "Welcome to the Johnson Room!" << endl; break;

        // if case 4, it is the Hopper room, so welcome the player
        case 4: cout << "Welcome to the Hopper Room!" << endl; break;

        // if case 5, it is the Moore room, so welcome the player
        case 5: cout << "Welcome to the Moore Room!" << endl; break;
    }

    // display the new map with the display map function
    map.displayMap();

    // check to make sure the server room is not 1 (this value is initially 1, when the player has not done anything, which is
    // why this check is present)
    if(current_server_room != 1)
    {
        // if it is not, then add the number of room hackers defeated to the total number of hackers defeated
        num_hackers_defeated += getRoomHackersDefeated();
    }

    // reset the number of room hackers defeated
    setRoomHackersDefeated(0);
}

/*
* This function checks the number of room hackers defeated to see if the player can move server
* rooms. The function returns true if the number of room hackers defeated is greater than 0 and
* false if the number of room hackers defeated is not greater than 0
* Parameters: none
* Return: Boolean: true if the player can move server rooms and false otherwise
*/
bool Game::canMoveRoom()
{
    // check to see if the number of room hackers defeated is greater than 0
    if(room_hackers_defeated > 0)
    {
        // if it is, then return true because they can move server rooms
        return true;
    }

    // otherwise, the player can't, so return false
    return false;
}

/*
* This function controls the end of the game. It has one parameter that controls which ending the player got
* and which ending to both print to the console and the results text file. It first creates an ofstream object
* and opens a file called results.txt. From there it checks what the parameter is and prints some the result of 
* the game to the player with a few stats. It then stores the rest of the stats into the file and closes the file.
* Parameter: an int that repesents the certain game end
* Return: void, but prints the results of the game to the player and stores the stats in results.txt
*/
void Game::gameEnd(int w)
{
    // declare the ofstream object
    ofstream fout;
    
    // open the file results.txt
    fout.open("results.txt");

    // check to see what end the player got
    // if the parameter is equal to 0, then the player won
    if(w == 0)
    {
        // player wins
        // print that the player won along with their number of hackers defeated, dogecoins, a thank you message,
        // and a reminder to check the results.txt for all of their stats
        cout << "Congratulations " << player.getName() << " you beat Carmen and the hackers!" << endl;
        cout << "Hackers Defeated: " << getNumHackersDefeated() << endl;
        cout << "Dogecoins: " << player.getDogecoins() << endl;
        cout << "Thank you for playing!" << endl;
        cout << "The rest of your stats are stored in results.txt." << endl;

        // sets the first line of the results.txt file to be the player won
        fout << "Win. " << player.getName() << " defeated Carmen and the hackers." << endl;
    }
    else if(w == 1)
    // if the parameter is equal to 0, then Carmen's progress reached 100
    {
        // carmen wins
        // print the player's number of hackers defeated, dogecoins, a thank you message,
        // and a reminder to check the results.txt for all of their stats
        cout << "Hackers Defeated: " << getNumHackersDefeated() << endl;
        cout << "Dogecoins: " << player.getDogecoins() << endl;
        cout << "Better luck next time! Thank you for playing!" << endl;
        cout << "The rest of your stats are stored in results.txt." << endl;

        // sets the first line of the results.txt file to be the player lost to Carmen
        fout << "Lose. " << player.getName() << " could not stop Carmen and the hackers in time." << endl;
    }
    // if the parameter is equal to 0, then the computer ran out of maintenance
    else if(w == 2)
    {
        // no more computer
        // print the player's number of hackers defeated, dogecoins, a thank you message,
        // and a reminder to check the results.txt for all of their stats
        cout << "Hackers Defeated: " << getNumHackersDefeated() << endl;
        cout << "Dogecoins: " << player.getDogecoins() << endl;
        cout << "Better luck next time! Thank you for playing!" << endl;
        cout << "The rest of your stats are stored in results.txt." << endl;

        // sets the first line of the results.txt file to be the player ran out of computer maintenance
        fout << "Lose. " << player.getName() << "'s computer broke down and didn't have a backup." << endl;
    }
    // if the parameter is equal to 0, then the player rage quit because their frustration got too high
    else if(w == 3)
    {
        // rage quit
        // print the player's number of hackers defeated, dogecoins, a thank you message,
        // and a reminder to check the results.txt for all of their stats
        cout << "Hackers Defeated: " << getNumHackersDefeated() << endl;
        cout << "Dogecoins: " << player.getDogecoins() << endl;
        cout << "Better luck next time! Thank you for playing!" << endl;
        cout << "The rest of your stats are stored in results.txt." << endl;

        // sets the first line of the results.txt file to be the player rage quit
        fout << "Lose. " << player.getName() << " rage quit before they could beat Carmen and the hackers." << endl;
    }
    // if the parameter is equal to 0, then the player quit from the turn menu
    else if(w == 4)
    {
        // player just quits from menu
        // print the player's number of hackers defeated, dogecoins, a thank you message,
        // and a reminder to check the results.txt for all of their stats
        cout << "Hackers Defeated: " << getNumHackersDefeated() << endl;
        cout << "Dogecoins: " << player.getDogecoins() << endl;
        cout << "Better luck next time! Thank you for playing!" << endl;
        cout << "The rest of your stats are stored in results.txt." << endl;

        // sets the first line of the results.txt file to be the player decided to quit from the turn menu
        fout << "Lose. " << player.getName() << " quit of their own accord." << endl;
    }

    // store the rest of the player's stats into the results.txt file
    fout << "Player Name: " << player.getName() << endl;
    fout << "Computer Maintenance Level: " << player.getComputerMaintenance() << endl;
    fout << "Number of Viruses in Computer: " << player.hasVirius() << endl;
    fout << "Computer Parts:" << endl;
    fout << "Number of CPUs: " << player.getCPU() << endl;
    fout << "Number of GPUs: " << player.getGPU() << endl;
    fout << "Number of Power Supply Units: " << player.getPowerSupplyUnits() << endl;
    fout << "Number of Computer Cases: " << player.getComputerCases() << endl;
    fout << "Number of Internet Cards: " << player.getInternetCards() << endl;
    fout << "Number of Keyboards and Mice: " << player.getKeyboardMouse() << endl;
    fout << "Number of Antivirus USB Sticks: " << player.getNumAntivirus() << endl;
    fout << "VPNs Available: " << player.getVPN() << endl;
    fout << "Internet Provider Level: " << player.getInternetLevel() << endl;
    fout << "Dogecoin Available: " << player.getDogecoins() << endl;
    fout << "Frustration Level: " << player.getFrustration() << endl;
    fout << "Carmen’s Progress: " << getCarmenProgress() << endl;
    fout << "Number of Hackers Defeated: " << getNumHackersDefeated() << endl; 

    // close the file
    fout.close();
}

/*
* This function takes a string, character separator, array, and size of array to split the string at
* every instance of the separator character, counts the number of separations and stores each
* separation in the string. It returns the number of separations
* Parameters: a string, a character to denote separators in the string
* array to hold the separated strings, and the size of the array
* Return: the number of pieces that the string was split into and the array is updated
* with the separated pieces of the string
*/
int Game::split(string ori_string, char separator, string array[], int size)
{
    // initialize values for the number of separators, return value,
    // and length of the string
    int num_separators = 0;
    int return_value = 0;
    int string_length = ori_string.length();

    // checks to make sure that the string has some length
    if(string_length > 0){

        // loop through the string to find the number of separators
        for(int i = 0; i < string_length; i++)
        {
            // if the string at a certain index equal the separator, 
            // add one to the number of separators
            if(ori_string[i] == separator)
            {
                num_separators++;
            }
        }

        // check that the number of separators is greater than 0
        if(num_separators > 0){
            // create an array to hold the index of each separator
            // with size equal to the number of separators
            int index_separator[num_separators];

            // create a value, index, to hold the current index of the separator index array
            int index = 0;

            // loop through the string again and record the position of each separator
            for(int i = 0; i < string_length; i++)
            {
                // checks if the string equal the separator at a certain index
                if(ori_string[i] == separator)
                {
                    // set the index separator to i
                    index_separator[index] = i;
                    // increase the index of the index separator
                    index++;
                }
            }

            // reset the index of the separator index array
            index = 0;

            // loop through the size of the array
            for(int i = 0; i < size; i++)
            {
                // the first value of the array is different from the rest
                if(i != 0)
                {
                    // makes the array at position i equal to a substring of the origional string
                    // starting from the first letter after a comma (so the separator index + 1)
                    // with length equal to the next separator index - the current separator index
                    array[i] = ori_string.substr(index_separator[index] + 1, 
                    (index_separator[index + 1] - 1) - index_separator[index]);
                    // increment the separator index
                    index++;
                }
                // this else statement handels the 0 case
                else
                {
                    // for case 0, the string starts from position 0 and has the length
                    // until the first instance of the separator
                    array[0] = ori_string.substr(0, index_separator[0]);
                }
            }

            // set the return value equal to the number of separators + 1 becasue
            // the number of strings is equal to the number of separators + 1
            return_value = num_separators + 1;

            // make sure that the number of separators is not equal to 0
            if(num_separators == 0)
            {
                return_value = 0;
            }
            // make sure that the number of separators is greater than the size of the 
            // array because that is a special case to return -1
            if(num_separators >= size)
            {
                return_value = -1;
            }

            // return the return value calculated previously
            return return_value;
        }
        // otherwise put the string inside the first index of the array
        else
        {
            // the first instance of the array is just the string becasue it does not
            // get split up becasue there are no separators in the string
            array[0] = ori_string;
            return 1;
        }
    }
    // otherwise no changes have been made, so retrun 0;
    else
    {
        return 0;
    }
}

/*
* This function removes a random computer part from the player's inventory. If there are no computer parts
* to remove it decreases the computer's maintenance by 10. It will only do either of these two actions if
* the current server room is not 5. It returns -2 if nothing happends, -1 if decreases maintenance by 10
* and 0-5 depending on the computer part lost.
* Parameters: none
* Return: an integer representing what was taken. -2 if nothing happends, -1 if the computer's maintenance 
* decreased by 10, and 0-5 depending on which computer part was removed from the player's inventory
*/
int Game::removeRandomComputerPart()
{
    // declare a boolean for later checking
    bool check = true;

    // check to make sure the server room is not 5
    if(current_server_room == 5)
    {
        // if it is 5, then nothing is taken, so return -2
        return -2;  
    }
    // otherwise, check to make sure the player actually has some computer parts
    else if(player.getCPU() == 0 && player.getGPU() == 0 && player.getPowerSupplyUnits() == 0 &&
    player.getComputerCases() == 0 && player.getKeyboardMouse() == 0 && player.getInternetCards() == 0)
    {
        // if they don't, then print that they have none, so their maintenance will decrease by 10
        cout << "You don't have any computer parts, so nothing can be taken, but your computer's maintenance dropped by 10." << endl;

        // get the current maintenance
        int current_maintenance = player.getComputerMaintenance();

        // set the maintenance to 10 lower than the current
        player.setComputerMaintenance(current_maintenance - 10);

        // return -1 because the computer dropped 10 maintenance
        return -1;
    }
    // otherwise the player has at least one computer part
    else if(player.getCPU() >= 0 && player.getGPU() >= 0 && player.getPowerSupplyUnits() >= 0 &&
    player.getComputerCases() >= 0 && player.getKeyboardMouse() >= 0 && player.getInternetCards() >= 0)
    {
        // do-while loop is perfect because it goes until the desire result is achieved 
        do
        {
            // generate a random seed with time(NULL)
            srand(time(NULL));

            // generate a random number between 0-5
            int rand_num = rand() % 6;

            // switch the random number
            switch(rand_num)
            {
                // if case 0, try to remove a cpu
                case 0: {
                    // store current number of cpus
                    int cpu = player.getCPU();

                    // check to make sure they have at least one
                    if(cpu > 0)
                    {
                        // if there is at least 1, remove 1 cpu
                        player.setCPU(cpu - 1);

                        // print that a cpu was lost
                        cout << "You lost a CPU." << endl;

                        // return 0 to signify a decrease in cpus
                        return 0;

                        // set the check to false
                        check = false;
                    }

                    // if not, then the loop generates a new number until a suitable computer part is found
                break;}

                // if case 1, try to remove a gpu
                case 1: {
                    // store current number of gpus
                    int gpu = player.getGPU();

                    // check to make sure they have at least one
                    if(gpu > 0)
                    {
                        // if there is at least 1, remove 1 gpu
                        player.setGPU(gpu - 1);

                        // print that a gpu was lost
                        cout << "You lost a GPU." << endl;

                        // return 1 to signify a decrease in gpus
                        return 1;

                        // set the check to false
                        check = false;
                    }

                    // if not, then the loop generates a new number until a suitable computer part is found
                break;}

                // if case 2, try to remove a power supply unit
                case 2: {
                    // store current number of power supply units
                    int psu = player.getPowerSupplyUnits();

                    // check to make sure they have at least one
                    if(psu > 0)
                    {
                        // if there is at least 1, remove 1 power supply unit
                        player.setPowerSupplyUnits(psu - 1);

                        // print that a power supply unit was lost
                        cout << "You lost a power supply unit." << endl;

                        // return 2 to signify a decrease in power supply units
                        return 2;

                        // set the check to false
                        check = false;
                    }

                    // if not, then the loop generates a new number until a suitable computer part is found
                break;}

                // if case 3, try to remove a computer case
                case 3: {
                    // store current number of computer cases
                    int comp_case = player.getComputerCases();

                    // check to make sure they have at least one
                    if(comp_case > 0)
                    {
                        // if there is at least 1, remove 1 computer case
                        player.setComputerCases(comp_case - 1);

                        // print that a computer case was lost
                        cout << "You lost a computer case." << endl;

                        // return 3 to signify a decrease in computer cases
                        return 3;

                        // set the check to false
                        check = false;
                    }

                    // if not, then the loop generates a new number until a suitable computer part is found
                break;}

                // if case 4, try to remove an internet card
                case 4: {
                    // store current number of internet cards
                    int ic = player.getInternetCards();

                    // check to make sure they have at least one
                    if(ic > 0)
                    {
                        // if there is at least 1, remove 1 internet card
                        player.setInternetCards(ic - 1);

                        // print that an internet card was lost
                        cout << "You lost an internet card." << endl;

                        // return 4 to signify a decrease in internet cards
                        return 4;

                        // set the check to false
                        check = false;
                    }

                    // if not, then the loop generates a new number until a suitable computer part is found
                break;}

                // if case 5, try to remove a keyboard and mouse
                case 5: {
                    // store current number of keyboards and mice
                    int km = player.getKeyboardMouse(); 

                    // check to make sure they have at least one
                    if(km > 0)
                    {
                        // if there is at least 1, remove 1 keyboard and mouse
                        player.setKeyboardMouse(km - 1);

                        // print that a keyboard and mouse was lost
                        cout << "You lost a keyboard and mouse." << endl;

                        // return 5 to signify a decrease in keyboards and mice
                        return 5;

                        // set the check to false
                        check = false;
                    }

                    // if not, then the loop generates a new number until a suitable computer part is found
                break;}
            }
        // loop until the check is triggered
        }while(check);
    }

    // return -2 so something is always returned
    return -2;
}

/*
* This function adds a random computer part. It does this by seeing if the player has maxed out parts.
* If they do, then the computer's maintenance is increased by 10, otherwise a random computer part is 
* added to their inventory. It returns -1 if the computer is repaired, and 0-5 depending on the computer
* part added to their inventory
* Parameter: none
* Return: integer representing what was done: -1 if the computer was repaired and 0-5 depending on which
* computer part was added to the player's inventory
*/
int Game::addRandomComputerPart()
{
    // declare a boolean for later checking 
    bool check = true;

    // see if the player's inventory is full with computer parts
    if(player.getCPU() >= 3 && player.getGPU() >= 3 && player.getPowerSupplyUnits() >= 3 &&
    player.getComputerCases() >= 3 && player.getKeyboardMouse() >= 3 && player.getInternetCards() >= 3)
    {
        // if it is, then they have max computer parts, so print that instead the maintenance will be increased by 10
        cout << "You have max computer parts, so nothing can be given, but your computer's maintenance increased by 10." << endl;

        // store the current level of maintenance
        int current_maintenance = player.getComputerMaintenance();

        // make sure the maintenance does not go above 100
        if((current_maintenance + 10) > 100)
        {
            // if it does, then set the computer maintenance to 100
            player.setComputerMaintenance(100);
        }
        // otherwise, the change will not go above 100
        else
        {
            // increase the computer's maintenance by 10
            player.setComputerMaintenance(current_maintenance + 10);
        }

        // return -1 to signify the change
        return -1;
    }
    // otherwise the player does not have max computer parts
    else
    {
        // do-while loop is perfect because it goes until the desire result is achieved
        do
        {
            // generate a random seed with time(NULL)
            srand(time(NULL));

            // generate a random number between 0-5
            int rand_num = rand() % 6;

            // switch the random number
            switch(rand_num)
            {
                // if case 0, try to add a cpu
                case 0: {
                    // store the current number of cpus
                    int cpu = player.getCPU();

                    // make sure the player has inventory space
                    if(cpu < 3)
                    {
                        // if they do, then increase the cpu by 1
                        player.setCPU(cpu + 1);

                        // print that the player got a cpu
                        cout << "You gained a CPU." << endl;

                        // return 0 to signify an increase in cpus
                        return 0;

                        // set the check to false
                        check = false;
                    }

                    // if not, then the loop generates a new number until a suitable computer part is found
                break;}

                // if case 1, try to add a gpu
                case 1: {
                    // store the current number of gpus
                    int gpu = player.getGPU();

                    // make sure the player has inventory space
                    if(gpu < 3)
                    {
                        // if they do, then increase the gpu by 1
                        player.setGPU(gpu + 1);

                        // print that the player got a gpu
                        cout << "You gained a GPU." << endl;

                        // return 1 to signify an increase in gpus
                        return 1;

                        // set the check to false
                        check = false;
                    }

                    // if not, then the loop generates a new number until a suitable computer part is found
                break;}

                // if case 2, try to add a power supply unit
                case 2: {
                    // store the current number of power supply units
                    int psu = player.getPowerSupplyUnits();

                    // make sure the player has inventory space
                    if(psu < 3)
                    {
                        // if they do, then increase the power supply units by 1
                        player.setPowerSupplyUnits(psu + 1);

                        // print that the player got a power supply unit
                        cout << "You gained a power supply unit." << endl;

                        // return 2 to signify an increase in power supply units
                        return 2;

                        // set the check to false
                        check = false;
                    }

                    // if not, then the loop generates a new number until a suitable computer part is found
                break;}

                // if case 3, try to add a computer case
                case 3: {
                    // store the current number of computer cases
                    int comp_case = player.getComputerCases();

                    // make sure the player has inventory space
                    if(comp_case < 3)
                    {
                        // if they do, then increase the computer cases by 1
                        player.setComputerCases(comp_case + 1);

                        // print that the player got a computer case
                        cout << "You gained a computer case." << endl;

                        // return 3 to signify an increase in computer cases
                        return 3;

                        // set the check to false
                        check = false;
                    }

                    // if not, then the loop generates a new number until a suitable computer part is found
                break;}

                // if case 4, try to add an internet card
                case 4: {
                    // store the current number of internet cards
                    int ic = player.getInternetCards();

                    // make sure the player has inventory space
                    if(ic < 3)
                    {
                        // if they do, then increase the internet cards by 1
                        player.setInternetCards(ic + 1);

                        // print that the player got an internet card
                        cout << "You gained an internet card." << endl;

                        // return 4 to signify an increase in internet cards
                        return 4;

                        // set the check to false
                        check = false;
                    }

                    // if not, then the loop generates a new number until a suitable computer part is found
                break;}

                // if case 5, try to add a keyboard and mouse
                case 5: {
                    // store the current number of keyboards and mice
                    int km = player.getKeyboardMouse(); 

                    // make sure the player has inventory space
                    if(km < 3)
                    {
                        // if they do, then increase the keyboards and mice by 1
                        player.setKeyboardMouse(km + 1);

                        // print that the player got a keyboard and mouse
                        cout << "You gained a keyboard and mouse." << endl;

                        // return 5 to signify an increase in keyboards and mice
                        return 5;

                        // set the check to false
                        check = false;
                    }

                    // if not, then the loop generates a new number until a suitable computer part is found
                break;}
            }

        // loop until the check is triggered
        }while(check);
    }

    // return -1 so something is always returned
    return -1;
}

/*
* This function handels misfortunes. It first generates a random number and then sees
* if the random number is one of the three "bad numbers" and punishes the player based
* on this random number.
* Parameter: none
* Return: void, but chances the player to get misfortunes and then does the misfortune
*/
void Game::misfortune()
{
    // generate a random seed with time(NULL)
    srand(time(NULL));

    // generate a random number between 0-9
    int rand_num = rand() % 10;

    // check to see if the player got a random number of 0, 1, or 2 because these are the misfortune numbers
    // (this also makes it a 30% chance because it is 3/10 * 100 which equals 30%)
    // check to see if the player got 0
    if(rand_num == 0)
    {
        // if they did, then remove all of their spare computer parts and antivirus
        player.setCPU(0);
        player.setGPU(0);
        player.setPowerSupplyUnits(0);
        player.setComputerCases(0);
        player.setInternetCards(0);
        player.setKeyboardMouse(0);
        player.setNumAntivirus(0);

        // print out what just happened
        cout << "OH NO! Your team was robbed by Carmen’s dastardly hackers!" << endl;
        cout << "You have no computer parts/antivirus software left!" << endl;
    }
    // check to see if the player got 1
    else if(rand_num == 1)
    {
        // if they did, then the computer takes 10 damage
        // get the current maintenance level
        int current_maintenance = player.getComputerMaintenance();

        // set the new maintenance to be 10 less
        player.setComputerMaintenance(current_maintenance - 10);

        // print out what just happened
        cout << "OH NO! Your computer was damaged!" << endl;
    }
    // check to see if the player got 2
    else if(rand_num == 2)
    {
        // if they did, then their frustration goes up by 10
        // store the current frustration
        int current_frustration = player.getFrustration();

        // set their frustration to be 10 higher
        player.setFrustration(current_frustration + 10);

        // print out what just happened
        cout << "OH NO! Why won’t my code work!!!!" << endl;
        cout << "Your frustration level was increased." << endl;
    }
    // otherwise, the player lucked out and did not get a misfortune
    else
    {
        // return to exit out of the function
        return;
    }
}