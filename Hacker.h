#ifndef HACKER_H
#define HACKER_H

#include <iostream>

using namespace std;

class Hacker
{
    private:
        int room_num;
        string hacker_name;
        bool alive;

    public:
        // constructors
        Hacker();
        Hacker(string n, int r);

        // getters
        string getName();
        int getRoomNum();
        bool getAlive();

        // setters
        void setName(string n);
        void setRoomNum(int n);
        void setAlive(bool d);
};

#endif