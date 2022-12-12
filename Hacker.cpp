#include <iostream>
#include "Hacker.h"

using namespace std;

// constructors
Hacker::Hacker()
{
    hacker_name = "";
    room_num = 0;
    alive = false;
}

Hacker::Hacker(string n, int r)
{
    hacker_name = n;
    room_num = r;
    alive = true;
}

// getters
string Hacker::getName()
{
    return hacker_name;
}

int Hacker::getRoomNum()
{
    return room_num;
}

bool Hacker::getAlive()
{
    return alive;
}

// setters
void Hacker::setName(string n)
{
    hacker_name = n;
}

void Hacker::setRoomNum(int n)
{
    room_num = n;
}

void Hacker::setAlive(bool d)
{
    alive = d;
}