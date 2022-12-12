#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include <time.h>
#include "Hacker.h"
#include "Player.h"
#include "Map.h"

using namespace std;

class Game
{
    private:
        const int num_hackers = 20;
        Hacker hackers[20];
        int carmen_progress;
        int current_server_room;
        int num_hackers_defeated;
        int room_hackers_defeated;
        Player player = Player("PLAYER");
        Map map = Map();

    public:
        // constructor
        Game();

        // getters
        int getCarmenProgress();
        int getServerRoom();
        int getNumHackersDefeated();
        Hacker getHacker(int i);
        int getRoomHackersDefeated();
        // Player getPlayer();
        // Map getMap();

        // setters
        void setCarmenProgress(int cp);
        void setServerRoom(int r);
        void setNumHackersDefeated(int d);
        void setRoomHackersDefeated(int rh);
        // void setPlayer(Player p);
        // void setMap(Map m);

        // other methods
        void start();
        void displayStats();
        void turn();
        bool readHackers();
        void printHackers();
        int fightHacker(Hacker hack);
        void talkToNPC(bool c);
        void bestbuy();
        void browseStackOverflow();
        void moveServerRoom();
        bool checkCoordinates(int row, int col, int row_holder[], int col_holder[], int arr_size, int index);
        bool canMoveRoom();
        void gameEnd(int w);
        int split(string ori_string, char separator, string array[], int size);
        int removeRandomComputerPart();
        int addRandomComputerPart();
        void misfortune();
};

#endif