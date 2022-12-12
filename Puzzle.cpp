#include <iostream>
#include "Puzzle.h"

using namespace std;

// constructor
Puzzle::Puzzle(int n)
{
    puzzle_number = n;
}

// getters
int Puzzle::getPuzzleNumber()
{
    return puzzle_number;
}

// setters
void Puzzle::setPuzzleNumber(int pn)
{
    puzzle_number = pn;
}

// other methods
/*
* This function checks which puzzle number the puzzle object has and then displays the proper puzzle.
* It then asks the player for input and checks to see if they got the right answer. If they did, then return
* true, if not, then give them the correct answer and return false.
* Parameters: none
* Return: True or false depending on if the player got the correct answer or not
*/
bool Puzzle::displayPuzzle()
{
    // switch the object's puzzle number
    switch(getPuzzleNumber())
    {
        // if case 1, display the first puzzle and see if user gets correct
        case 1: {
            // print out the puzzle
            cout << "****FIND THE ERROR****" << endl;
            cout << "This code works perfectly except for one pesky bug. Enter the number of " << endl;
            cout << "the line on which the error appears to win this puzzle." << endl;
            cout << "1. #include <iostream>" << endl;
            cout << "2. using namespace std;" << endl;
            cout << "3." << endl;
            cout << "4. double frobenius(double arr1[][3], double arr2[][3]);" << endl;
            cout << "5." << endl;
            cout << "6. int main() {" << endl;
            cout << "7. double arr1[3][3];" << endl;
            cout << "8. double arr2[3][3];" << endl;
            cout << "9." << endl;
            cout << "10. for(int i = 0; i < 3; i++){" << endl;
            cout << "11. for(int j = 0; j < 3; j++) {" << endl;
            cout << "12. arr1[i][j] = i + j;" << endl;
            cout << "13. arr2[i][j] = i * j;" << endl;
            cout << "14. }" << endl;
            cout << "15. }" << endl;
            cout << "16." << endl;
            cout << "17. cout << frobenius(arr1, arr2) << endl;" << endl;
            cout << "18. return 0;" << endl;
            cout << "19. }" << endl;
            cout << "20." << endl;
            cout << "21. double frobenius(arr1[][3], arr2[][3]){" << endl;
            cout << "22. double innerProduct = 0;" << endl;
            cout << "23. for(int i = 0; i < 3; i++){" << endl;
            cout << "24. for(int j = 0; j < 3; j++){" << endl;
            cout << "25. innerProduct += arr1[i][j] * arr2[i][j];" << endl;
            cout << "26. }" << endl;
            cout << "27. }" << endl;
            cout << "28. return innerProduct;" << endl;
            cout << "29. }" << endl;
            cout << endl;

            // declare a string to hold the user's input
            string user_choice;

            // prompt them and get the user input
            cout << "What is the problem line?" << endl;
            cin >> user_choice;

            // check to see if the user got the correct answer
            if(checkAnswer(user_choice))
            {
                // if they did, then return true
                cout << "You are correct!" << endl;
                return true;
            }
            else
            {
                // if not, then give them the answer and return false
                cout << "You chose the wrong line. The correct answer was line 21." << endl;
                return false;
            }
        break;}

        // if case 2, display the second puzzle and see if user gets correct
        case 2: {
            // print out the puzzle
            cout << "****FIND THE ERROR****" << endl;
            cout << "This code works perfectly except for one pesky bug. Enter the number of " << endl;
            cout << "the line on which the error appears to win this puzzle." << endl;
            cout << "1. #include <iostream>" << endl;
            cout << "2. #include <fstream>" << endl;
            cout << "3." << endl;
            cout << "4. using namespace std;" << endl;
            cout << "5." << endl;
            cout << "6. int main() {" << endl;
            cout << "7. string fileName = 'fake_file.txt';" << endl;
            cout << "8. fstream infile(fileName);" << endl;
            cout << "9." << endl;
            cout << "10. if(infile.is_open()){" << endl;
            cout << "11. string line;" << endl;
            cout << "12. int lineNum = 0;" << endl;
            cout << "13. while(getline(line, infile)){" << endl;
            cout << "14. lineNum++;" << endl;
            cout << "15. cout << 'Line ' << lineNum << ': ' << line << endl;" << endl;
            cout << "16. }" << endl;
            cout << "17. }else{" << endl;
            cout << "18. cout << ÒFailed to open file.Ó << endl;" << endl;
            cout << "19. }" << endl;
            cout << "20. return 0;" << endl;
            cout << "21. }" << endl;
            cout << endl;

            // declare a string to hold the user's input
            string user_choice;

            // prompt them and get the user input
            cout << "What is the problem line?" << endl;
            cin >> user_choice;

            // check to see if the user got the correct answer
            if(checkAnswer(user_choice))
            {
                // if they did, then return true
                cout << "You are correct!" << endl;
                return true;
            }
            else
            {
                // if not, then give them the answer and return false
                cout << "You chose the wrong line. The correct answer was line 13." << endl;
                return false;
            }
        break;}

        // if case 3, display the third puzzle and see if user gets correct
        case 3: {
            // print out the puzzle
            cout << "****MULTIPLE CHOICE****" << endl;
            cout << "Consider the following snippet of code. How many times will the sentence " << endl;
            cout << "inside of the for loop be printed?" << endl;
            cout << "#include <iostream>" << endl;
            cout << "using namespace std;" << endl;
            cout << "int main(){" << endl;
            cout << "int begin = 5;" << endl;
            cout << "int end = 20;" << endl;
            cout << "for (int i = begin; i <= end; i+=2){" << endl;
            cout << "cout << 'This code does nothing important' << endl;" << endl;
            cout << "}" << endl;
            cout << "return 0;" << endl;
            cout << "}" << endl;
            cout << "A) 15" << endl;
            cout << "B) 8" << endl;
            cout << "C) 7" << endl;
            cout << "D) 10" << endl;
            cout << endl;

            // declare a string to hold the user's input
            string user_choice;

            // prompt them and get the user input
            cout << "What is the correct answer?" << endl;
            cin >> user_choice;

            // check to see if the user got the correct answer
            if(checkAnswer(user_choice))
            {
                // if they did, then return true
                cout << "You are correct!" << endl;
                return true;
            }
            else
            {
                // if not, then give them the answer and return false
                cout << "You chose the wrong answer. The correct answer was B." << endl;
                return false;
            }
        break;}

        // if case 4, display the fourth puzzle and see if user gets correct
        case 4: {
            // print out the puzzle
            cout << "****MULTIPLE CHOICE****" << endl;
            cout << "In the function below, word double before multiply represents what about " << endl;
            cout << "the function?" << endl;
            cout << "double multiply(double x, double y)" << endl;
            cout << "{" << endl;
            cout << "return x*y;" << endl;
            cout << "}" << endl;
            cout << "A) The type of return value" << endl;
            cout << "B) The name of the function" << endl;
            cout << "C) The type of parameter variable" << endl;
            cout << "D) The algorithm within the function" << endl;
            cout << endl;

            // declare a string to hold the user's input
            string user_choice;

            // prompt them and get the user input
            cout << "What is the correct answer?" << endl;
            cin >> user_choice;

            // check to see if the user got the correct answer
            if(checkAnswer(user_choice))
            {
                // if they did, then return true
                cout << "You are correct!" << endl;
                return true;
            }
            else
            {
                // if not, then give them the answer and return false
                cout << "You chose the wrong answer. The correct answer was A." << endl;
                return false;
            }
        break;}

        // if case 5, display the fith puzzle and see if user gets correct
        case 5: {
            // print out the puzzle
            cout << "****MULTIPLE CHOICE****" << endl;
            cout << "To defeat a hacker you need to use a brute force attack on his account. To " << endl;
            cout << "do this, you are using a text file that holds words, numbers and other " << endl;
            cout << "potential password combinations. Sometimes you come up with new word " << endl;
            cout << "combinations you would like to add to the list. Which of the following " << endl;
            cout << "streams should you use to both read and write from this file?" << endl;
            cout << "A) iofstream" << endl;
            cout << "B) ofstream" << endl;
            cout << "C) ifstream" << endl;
            cout << "D) fstream" << endl;
            cout << endl;

            // declare a string to hold the user's input
            string user_choice;

            // prompt them and get the user input
            cout << "What is the correct answer?" << endl;
            cin >> user_choice;

            // check to see if the user got the correct answer
            if(checkAnswer(user_choice))
            {
                // if they did, then return true
                cout << "You are correct!" << endl;
                return true;
            }
            else
            {
                // if not, then give them the answer and return false
                cout << "You chose the wrong answer. The correct answer was D." << endl;
                return false;
            }
        break;}
    }
    return false;
}

/*
* This function takes in a string as input. It then checks which puzzle number the puzzle object is
* and check to see if the input string is equal to the answer. If it is, then it returns true, if not
* then it returns false because the player got the wrong answer.
* Parameters: a string representing the player's answer
* Return: True or false depending on if the player got the right answer for the right puzzle number
*/
bool Puzzle::checkAnswer(string a)
{
    // first switch the puzzle number
    switch(puzzle_number)
    {
        // if case 1, then the puzzle's answer is 21
        case 1: {
            // check to see if they answered 21, if they did, then return true
            if(a == "21")
            {
                return true;
            }
        break;}

        // if case 2, then the puzzle's answer is 13
        case 2: {
            // check to see if they answered 13, if they did, then return true
            if(a == "13")
            {
                return true;
            }
        break;}

        // if case 3, then the puzzle's answer is B
        case 3: {
            // check to see if they answered B, if they did, then return true
            if(a == "B")
            {
                return true;
            }
        break;}

        // if case 4, then the puzzle's answer is A
        case 4: {
            // check to see if they answered A, if they did, then return true
            if(a == "A")
            {
                return true;
            }
        break;}

        // if case 5, then the puzzle's answer is D
        case 5: {
            // check to see if they answered D, if they did, then return true
            if(a == "D")
            {
                return true;
            }
        break;}
    }

    // return false if they did not get the correct answer
    return false;
}