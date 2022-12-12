#ifndef PUZZLE_H
#define PUZZLE_H

#include <iostream>

using namespace std;

class Puzzle
{
    private:
        int puzzle_number;

    public:
        // constructor
        Puzzle(int n);

        // getters
        int getPuzzleNumber();

        // setters
        void setPuzzleNumber(int pn);

        // other methods
        bool displayPuzzle();
        bool checkAnswer(string a);
};

#endif