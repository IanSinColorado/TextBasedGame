#include <iostream>
#include "Player.h"

using namespace std;

// constructor
Player::Player(string n)
{
    player_name = n;
    frustration_level = 0;
    dogecoins = 200;
    internet_provider_level = 1;
    num_vpn = 1;
    has_backup_computer = false;
    has_virius = false;
    computer_maintenance = 100;
    num_antivirus_stick = 0;

    for(int i = 0; i < parts_size; i++)
    {
        numParts[i] = 0;
    }
}

// getters
string Player::getName()
{
    return player_name;
}

int Player::getFrustration()
{
    return frustration_level;
}

int Player::getDogecoins()
{
    return dogecoins;
}

int Player::getInternetLevel()
{
    return internet_provider_level;
}

int Player::getVPN()
{
    return num_vpn;
}

bool Player::getBackupComputer()
{
    return has_backup_computer;
}

int Player::getNumAntivirus()
{
    return num_antivirus_stick;
}

int Player::getCPU()
{
    return numParts[0];
}

int Player::getGPU()
{
    return numParts[1];
}

int Player::getPowerSupplyUnits()
{
    return numParts[2];
}

int Player::getComputerCases()
{
    return numParts[3];
}

int Player::getInternetCards()
{
    return numParts[4];
}

int Player::getKeyboardMouse()
{
    return numParts[5];
}

int Player::hasVirius()
{
    return has_virius;
}

int Player::getComputerMaintenance()
{
    return computer_maintenance;
}

// setters
void Player::setName(string n)
{
    player_name = n;
}

void Player::setFrustration(int f)
{
    if(f >= 0)
    {
        frustration_level = f;
    }
}

void Player::setDogecoins(int d)
{
    if(d >= 0)
    {
        dogecoins = d;
    }
}

void Player::setInternetLevel(int l)
{
    if(l >= 0)
    {
       internet_provider_level = l; 
    } 
}

void Player::setVPN(int v)
{
    if(v >= 0)
    {
        num_vpn = v;
    }
}

void Player::setBackupComputer(bool c)
{
    has_backup_computer = c;
}

void Player::setNumAntivirus(int a)
{
    if(a >= 0)
    {
        num_antivirus_stick = a;
    }
}

void Player::setCPU(int cpu)
{
    if(cpu >= 0)
    {
        numParts[0] = cpu;
    }
}

void Player::setGPU(int gpu)
{
    if(gpu >= 0)
    {
        numParts[1] = gpu;
    }
}

void Player::setPowerSupplyUnits(int psu)
{
    if(psu >= 0)
    {
        numParts[2] = psu;
    }
}

void Player::setComputerCases(int cc)
{
    if(cc >= 0)
    {
        numParts[3] = cc;
    }
}

void Player::setInternetCards(int ic)
{
    if(ic >= 0)
    {
        numParts[4] = ic;
    }
}

void Player::setKeyboardMouse(int km)
{
    if(km >= 0)
    {
        numParts[5] = km;
    }
}

void Player::setVirius(int v)
{ 
    if(v >= 0)
    {
        has_virius = v;
    }
}

void Player::setComputerMaintenance(int cm)
{
    if(cm >= 0 && cm <= 100)
    {
        computer_maintenance = cm;
    }
}

/*
* This function tells whether or not the player can make a new computer by seeing if the player has 
* at least 5 computer parts. It returns true if they can and false if they can't.
* Parameters: none
* Return: boolean representing whether or not they can make a computer. True if they can, false otherwise
*/
bool Player::canMakeComputer()
{
    // initialize a variable to hold what is returned
    bool can_make_computer = false;

    // initialize a variable to hold the total number of parts by adding up the numParts array
    int total_num_parts = numParts[0] + numParts[1] + numParts[2] + numParts[3] + numParts[4] + numParts[5];

    // check to make sure that the total number of parts is greater than 5
    if(total_num_parts > 5)
    {
        // if it is then return true
        can_make_computer = true;
    }

    // return the variable that holds the return
    return can_make_computer;
}

/*
* This function repairs the computer. It allows the player to select which computer parts to use to
* repair the computer. It does this through showing a menu of all of the computer parts the player
* has and allowing the player to select which one and the number of parts they would like to use. It
* then repairs the computer and removes the parts from the player's inventory.
* Parameters: None
* Return: Void, but will exit out of the menu if the computer has a virius
*/
void Player::repairComputer()
{
    // if the computer has a virus, it cannot be repaired, so check and if it does, then return
    if(hasVirius() > 0)
    {
        // print that it has a virius and cannot be repaired
        cout << "You cannot repair your computer if it has a virius." << endl;
        return;
    }

    // declare a variable to hold the user input
    int user_input;

    do
    {
        // print the computer's current maintenance level
        cout << "Current Computer Maintenance: " << getComputerMaintenance() << endl;

        // print all of the amounts of all of the parts
        cout << "Inventory:" << endl;
        cout << "1. CPU: " << getCPU() << endl;
        cout << "2. GPU: " << getGPU() << endl;
        cout << "3. Power Supply Units: " << getPowerSupplyUnits() << endl;
        cout << "4. Computer Case: " << getComputerCases() << endl;
        cout << "5. Internet Card: " << getInternetCards() << endl;
        cout << "6. Keyboard and Mouse: " << getKeyboardMouse() << endl;
        cout << "7. Quit" << endl;
        cout << "Each part gives 20 computer maintenance." << endl;

        // get user input for the part they want to use
        cout << "Enter the number you want to use for the repair: ";
        cin >> user_input;

        // switch the user input for each case
        switch(user_input)
        {
            // the first 6 cases are all the same except for different part types, which was gotten from the user's choice
            case 1: 
            case 2: 
            case 3: 
            case 4: 
            case 5: 
            case 6: {
                // make sure they have at least one of those parts
                if(numParts[user_input - 1] <= 0)
                {
                    // otherwise print that there are no computer parts of that type
                    cout << "You have no computer parts of that type" << endl;
                }
                // otherwise, they do have at least one of that part
                else
                {
                    // declare a variable and get user input for the number that computer parts they want to use
                    int user_choice = 0;
                    cout << "Enter the number of this part you want to use to repair the computer:" << endl;
                    cin >> user_choice;

                    // check to make sure the input is valid (less than or equal to their current number of parts and greater than 0)
                    // and the computer needs to be repaired
                    if(user_choice <= numParts[user_input - 1] && user_choice > 0 && getComputerMaintenance() < 100)
                    {
                        // get the current maintenance level
                        int current_maintenance = getComputerMaintenance();

                        // get the new maintenance level
                        int new_maintenance = (user_choice * 20) + current_maintenance;

                        // if the new maintenance is greater than 100, then just set it to 100
                        // because the maintenance can only have a maximum of 100
                        if(new_maintenance > 100)
                        {
                            new_maintenance = 100;
                        }

                        // set the current computer maintenance to the new maintenance
                        setComputerMaintenance(new_maintenance);

                        // get the current number of that part
                        int current_part = numParts[user_input - 1];

                        // subtract the number of parts used to repair the computer
                        numParts[user_input - 1] = current_part - user_choice;
                    }
                    else if(getComputerMaintenance() >= 100)
                    {
                        cout << "You do not need to repair your computer." << endl;
                    }
                    // otherwise they selected an invalid number of parts (more than they have or less than 0)
                    else
                    {
                        // print that they inputted an invalid number of parts
                        cout << "Invalid Number of Parts" << endl;
                    }
                }
            break;}

            // case 7 quits repairing the computer
            case 7: cout << "Current Computer Maintenance: " << getComputerMaintenance() << endl; break;

            // any other input is invalid, so print that
            default: cout << "Invalid input." << endl; break;
        }
    // this will loop until the user picks the option to quit the menu
    }while(user_input != 7);
}
