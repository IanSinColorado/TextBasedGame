// CS1300 Fall 2021
// Author: Ian Stewart
// Recitation: 115 – Alexander Ray
// Project 3 - Code Skeleton

#include <iostream>
#include "Game.h"
#include "Hacker.h"
#include "Player.h"
#include "Puzzle.h"

using namespace std;

// g++ -std=c++11 Game.cpp Player.cpp Hacker.cpp Puzzle.cpp classesDriver.cpp

int main()
{
    // testing the Player class
    // instantiating an object with the only constructor (there will be no case where a name is not imputted)
    Player test1 = Player("Player");

    // testing all of the getter functions and initial values of the palyer constructor
    cout << "Name: " << test1.getName() << endl; // prints "Player"
    cout << "Frustration Level: " << test1.getFrustration() << endl; // prints 0
    cout << "Dogecoins: " << test1.getDogecoins() << endl; // prints 200
    cout << "Internet Level: " << test1.getInternetLevel() << endl; // prints 1
    cout << "Number of VPNs: " << test1.getVPN() << endl; // prints 1
    cout << "Has Backup Computer: " << test1.getBackupComputer() << endl; // prints 0 or false
    cout << "Number of Antivirius Sticks: " << test1.getNumAntivirus() << endl; // prints 0
    cout << "Number of CPUs: " << test1.getCPU() << endl; // prints 0
    cout << "Number of GPUs: " << test1.getGPU() << endl; // prints 0
    cout << "Number of Power Supply Units: " << test1.getPowerSupplyUnits() << endl; // prints 0
    cout << "Number of Computer Cases: " << test1.getComputerCases() << endl; // prints 0
    cout << "Number of Internet Cards: " << test1.getInternetCards() << endl; // prints 0
    cout << "Number of Keyboard and Mouses: " << test1.getKeyboardMouse() << endl; // prints 0
    cout << "Has Virius: " << test1.hasVirius() << endl; // prints 0 or false
    cout << "Computer Maintenance: " << test1.getComputerMaintenance() << endl; // prints 100
    cout << endl;

    // testing all of the setter functions (no setter for name because that should not be able to change)
    test1.setFrustration(100);
    test1.setDogecoins(100);
    test1.setInternetLevel(5);
    test1.setVPN(3);
    test1.setBackupComputer(true);
    test1.setNumAntivirus(1);
    test1.setCPU(3);
    test1.setGPU(3);
    test1.setPowerSupplyUnits(3);
    test1.setComputerCases(3);
    test1.setInternetCards(3);
    test1.setKeyboardMouse(3);
    test1.setVirius(true);
    test1.setComputerMaintenance(0);

    // reprinting the values to see if the setter functions worked
    cout << "Frustration Level: " << test1.getFrustration() << endl; // prints 100
    cout << "Dogecoins: " << test1.getDogecoins() << endl; // prints 100
    cout << "Internet Level: " << test1.getInternetLevel() << endl; // prints 5
    cout << "Number of VPNs: " << test1.getVPN() << endl; // prints 3
    cout << "Has Backup Computer: " << test1.getBackupComputer() << endl; // prints 1 or true
    cout << "Number of Antivirius Sticks: " << test1.getNumAntivirus() << endl; // prints 1
    cout << "Number of CPUs: " << test1.getCPU() << endl; // prints 3
    cout << "Number of GPUs: " << test1.getGPU() << endl; // prints 3
    cout << "Number of Power Supply Units: " << test1.getPowerSupplyUnits() << endl; // prints 3
    cout << "Number of Computer Cases: " << test1.getComputerCases() << endl; // prints 3
    cout << "Number of Internet Cards: " << test1.getInternetCards() << endl; // prints 3
    cout << "Number of Keyboard and Mouses: " << test1.getKeyboardMouse() << endl; // prints 3
    cout << "Has Virius: " << test1.hasVirius() << endl; // prints 1 or true
    cout << "Computer Maintenance: " << test1.getComputerMaintenance() << endl; // prints 0
    cout << endl;

    cout << endl;

    // testing the Puzzle class
    // instantiating an object with the only constructor
    Puzzle test2 = Puzzle(1, "answer");

    // testing the getter methods
    cout << "Puzzle Number: " << test2.getPuzzleNumber() << endl; // prints 1
    cout << "Puzzle Answer: " << test2.getPuzzleAnswer() << endl; // prints "answer"
    cout << endl;

    // testing the setter methods
    test2.setPuzzleNumber(2);
    test2.setPuzzleAnswer("wrong");

    // reprinting with the getter methods
    cout << "Puzzle Number: " << test2.getPuzzleNumber() << endl; // prints 2
    cout << "Puzzle Answer: " << test2.getPuzzleAnswer() << endl; // prints "wrong"
    cout << endl;

    cout << endl;

    // testing the Hacker class
    // instantiating an object with the default constructor
    Hacker test3 = Hacker();

    // testing the getter functions and default values of the default constructor
    cout << "Hacker Name: " << test3.getName() << endl; // prints a blank line
    cout << "Hacker Room: " << test3.getRoomNum() << endl; // prints 0
    cout << "Hacker Alive: " << test3.getAlive() << endl; // prints 0 or false
    cout << endl;

    // testing the setter functions
    test3.setName("Name");
    test3.setRoomNum(1);
    test3.setAlive(true);

    // reprinting with the getter methods
    cout << "Hacker Name: " << test3.getName() << endl; // prints "Name"
    cout << "Hacker Room: " << test3.getRoomNum() << endl; // prints 1
    cout << "Hacker Alive: " << test3.getAlive() << endl; // prints 1 or true
    cout << endl;

    // instantiating an object with the parameterized constructor
    Hacker test4 = Hacker("myNameIsJeff", 5);

    // printing the parameterized values
    cout << "Hacker Name: " << test4.getName() << endl; // prints "myNameIsJeff"
    cout << "Hacker Room: " << test4.getRoomNum() << endl; // prints 5
    cout << "Hacker Alive: " << test4.getAlive() << endl; // prints 0 or false
    cout << endl;

    cout << endl;

    // testing the Game class
    // instantiating an object with the only constructor
    Game test5 = Game();

    // testing the getter methods and initialized values of the constructor
    cout << "Carmen Progress: " << test5.getCarmenProgress() << endl; // prints 0
    cout << "Current Server Room: " << test5.getServerRoom() << endl; // prints 1
    cout << "Number of Hackers Defeated: " << test5.getNumHackersDefeated() << endl; // prints 0
    cout << endl;

    // testing the setter methods
    test5.setCarmenProgress(100);
    test5.setServerRoom(2);
    test5.setNumHackersDefeated(5);

    // reprinting with the getter mehtods
    cout << "Carmen Progress: " << test5.getCarmenProgress() << endl; // prints 100
    cout << "Current Server Room: " << test5.getServerRoom() << endl; // prints 2
    cout << "Number of Hackers Defeated: " << test5.getNumHackersDefeated() << endl; // prints 5

    return 0;
}