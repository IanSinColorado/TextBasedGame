#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

using namespace std;

class Player
{
    private:
        string player_name;
        int frustration_level;
        int dogecoins;
        int internet_provider_level;
        int num_vpn; // max of 2
        bool has_backup_computer; // max of 1
        int num_antivirus_stick;
        const int parts_size = 6;
        int numParts[6];
        int has_virius;
        int computer_maintenance;

    public:
        // constructor
        Player(string n);
        Player();

        // getters
        string getName();
        int getFrustration();
        int getDogecoins();
        int getInternetLevel();
        int getVPN();
        bool getBackupComputer();
        int getNumAntivirus();
        int getCPU();
        int getGPU();
        int getPowerSupplyUnits();
        int getComputerCases();
        int getInternetCards();
        int getKeyboardMouse();
        int hasVirius();
        int getComputerMaintenance();

        // setters
        void setName(string n);
        void setFrustration(int f);
        void setDogecoins(int d);
        void setInternetLevel(int l);
        void setVPN(int v);
        void setBackupComputer(bool c);
        void setNumAntivirus(int a);
        void setCPU(int cpu);
        void setGPU(int gpu);
        void setPowerSupplyUnits(int psu);
        void setComputerCases(int cc);
        void setInternetCards(int ic);
        void setKeyboardMouse(int km);
        void setVirius(int v);
        void setComputerMaintenance(int cm);

        // other methods
        bool canMakeComputer();
        void repairComputer();
};

#endif