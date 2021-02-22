/*
Benjamin Malz
malzP4.cpp (Assignment 4)
Purpose: This program reads in a user-defined filename and displays the Sudoku board it would form, and then checks each row and column for duplicate numbers.
Input: The user is prompted for a filename for the program to read.
Output: If the user failed to input a valid filename, the program displays a message and closes immediately. If not, then the program displays the Sudoku board
formed from the data in the file, as well as displaying any duplicate numbers in the rows or columns of the board.
 */

#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

const int TOTAL_SQUARES = 81; //Constant for total number of squares
const int SQUARE_ROOT = 9; //Constant for the square root of the total squares, used for 2D array
const int SQUARE_SQUARE = 3; //Constant for the square root of the square root, used to calculate box size
string fileName; //Filename user is prompted to enter
class sudoku
{
    int sudokUrray[SQUARE_ROOT][SQUARE_ROOT]; //2D array for the x and y axis of the grid
    public:
        void readFile(string);
        void printTable();
        void checkDupes();
};
int main()
{
    cout << "Please enter your filename with extension included." << endl;
    cin >> fileName; //User inputs filename
    sudoku theSudoku; //Allows sudoku class to be accessed
    theSudoku.readFile(fileName); //Reads data from specified file, or tells user it does not exist
    theSudoku.printTable(); //Displays the sudoku grid
    theSudoku.checkDupes(); //Checks for duplicate numbers across both the x and y axes
    return 0; //Ends program once finished
}

void sudoku::readFile(string fileName)
/* Reads the filename, looks at each number and stores it in its respective position in a 2D array */
{
    ifstream inFP;
    inFP.open(fileName.c_str()); //String needs to be changed to C string to be opened as file
    if (inFP == 0) //No file found
    {
        cout << "Invalid file. Program closing." << endl;
        exit(EXIT_FAILURE); //Exits program without needing to return
    }
    int loopCount = 0; //Counter for total times gone around loop
    int arrayXPos = 0; //Counter for the X axis of the Sudoku 2D array
    int arrayYPos = 0; //Counter for the Y axis of the Sudoku 2D array
    char fileNumber; //Looks at file on character at a time
    while (loopCount < TOTAL_SQUARES) //The loop should never run for more than the total number of sudoku squares.
    {
        inFP >> fileNumber; //Reads the next character
        int charToInt = (fileNumber - 48); //The ASCII values for 0-9 start at 048 and are in order, subtracting 48 yields the real number value.
        sudokUrray[arrayXPos][arrayYPos] = charToInt; //Adds the converted number to the 2D array.
        arrayXPos ++; //Increases X position of the array so it's stored in a grid-style fashion
        if (arrayXPos == SQUARE_ROOT)
        {
            arrayXPos = 0; //If the array position goes beyond the length of that portion of the array, resets to zero.
            arrayYPos++; //Increases the position of the other part of the 2D array.
        }
        loopCount ++; //Increases loop count by one.
    }
    inFP.close(); //Closes file since it's no longer needed
/*----------END----------*/
}

void sudoku::printTable()
/* Translates the 2D array into a visual Sudoku board displayed in the console */
{
    int breakLines = 1; //When set to 1, prints the plus signs and hyphens needed between grids
    int arrayXPos = 0; //2D array's x-axis position
    int arrayYPos = 0; //2D array's y-axis position
    int plusSpacing = ((SQUARE_SQUARE * 2) + 1); //Calculates the number of spaces needed between plus signs for prints
    while (arrayYPos <= SQUARE_ROOT)
    {
        if (arrayYPos == SQUARE_ROOT)
            arrayYPos++; //Once the final loop has started, increases Y so it actually ends after printing the final break line
        if (breakLines == 1) //When breakLines is set to 1, prints the hyphens and plus signs
        {
            int loopCount = 0; //Counter for the first while loop
            int innerLoopCount = 0; //Counter for the second while loop
            while (loopCount <= SQUARE_SQUARE)
            {
                cout << "+"; //Prints a plus between hyphens
                innerLoopCount = 0; //Resets inner loop count each time to ensure hyphens are printed between the plus signs
                while (innerLoopCount < plusSpacing && loopCount < SQUARE_SQUARE) //Runs as long as the outside loop isn't running a final time, ensures that final plus is printed on break
                {
                    cout << "-"; //Each time it loops, prints one hyphen until the count for plus spacings needed has been reached
                    innerLoopCount++;
                }
                loopCount++;
            }
        breakLines = 0; //Ensures it won't print a second time if conditions are not met
            cout << endl;
        }
        if ((arrayXPos == 0 && arrayYPos < SQUARE_ROOT) || ((arrayXPos % SQUARE_SQUARE) == 0 && arrayYPos < SQUARE_ROOT)) //
            cout << "| ";
        if (arrayYPos < SQUARE_ROOT) //As long as the maximum Y value is not reached, prints the next X value and a space between the values or | symbol
            {
            cout << sudokUrray[arrayXPos][arrayYPos] << " ";
            arrayXPos++; //Increases X value after printed
            }
        if (arrayXPos == SQUARE_ROOT && arrayYPos < SQUARE_ROOT) //Once the array hits its final X position, prints a final | symbol and resets the X position while upping the Y position
        {
            cout << "|" << endl;
            arrayXPos = 0;
            arrayYPos++;
            if ((arrayYPos % SQUARE_SQUARE) == 0) //Every time the grid maximum lines have been reached, sets breakLines to 1 so it can print a new line break
                breakLines = 1;
        }
    }
/*----------END----------*/
}

void sudoku::checkDupes()
/* Checks the 2D array as though it were an actual Sudoku grid and determines if there are any rule-breaking duplicates in the rows or columns*/
{
    for (int yAxis = 0; yAxis < SQUARE_ROOT; yAxis++) //Does inner loops for all Y axis columns
    {
        for (int xAxis = 0; xAxis < SQUARE_ROOT; xAxis++)//Does inner loop each time X increases
        {
            int currentXNumCheck = sudokUrray[xAxis][yAxis]; //Sets variable for current array position to be checked against all numbers in the row
            for (int subXAxis = 0; subXAxis < SQUARE_ROOT; subXAxis++) //Compares every number in row to current position
            {
                if (subXAxis == xAxis)
                {
                //Do nothing, just acknowledges that this is a duplicate because it's the same number and therefore not noteworthy
                }
                else if (currentXNumCheck == sudokUrray[subXAxis][yAxis] && xAxis < SQUARE_ROOT && yAxis < SQUARE_ROOT) //If the number is a duplicate and the arrays actually exist, print message
                {
                             cout << "Uh oh! Duplicate number or numbers in row: " << (yAxis + 1) << endl; //Print message while formatting array position to correspond with the row number
                             subXAxis = SQUARE_ROOT; //The row already has a duplicate, no need to keep searching
                             yAxis++; //Increase Y axis and restart search
                }
            }
        }
    }
    for (int xAxis = 0; xAxis < SQUARE_ROOT; xAxis++) //Increases X after every Y value in the column is checked
    {
        for (int yAxis = 0; yAxis < SQUARE_ROOT; yAxis++) //Increases Y after every value is checked
        {
            int currentYNumCheck = sudokUrray[xAxis][yAxis]; //Variable for current position being checked
            for (int subYAxis = 0; subYAxis < SQUARE_ROOT; subYAxis++) //Checks every number in the column against current position
            {
                if (subYAxis == yAxis)
                {
                //Do nothing as while it is a duplicate it's the same number as the one being checked
                }
                else if (currentYNumCheck == sudokUrray[xAxis][subYAxis] && xAxis < SQUARE_ROOT && yAxis < SQUARE_ROOT) //If it is a duplicate display message
                {
                             cout << "That's not right... duplicate number or numbers in column: " << (xAxis + 1) << endl;
                             subYAxis = SQUARE_ROOT;
                             xAxis++; //Column is confirmed to have a duplicate, restart search in next column
                }
            }
        }
    }
/*----------END----------*/
}
