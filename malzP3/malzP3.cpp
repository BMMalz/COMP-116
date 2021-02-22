/*
Benjamin Malz
malz3.cpp (Assignment 3)
Purpose: This program finds the Riemann Sum of one of two equations of the user's choice. It finds the minimum number of intervals needed to get within the
user-inputted epsilon (difference in upper and lower sums) and then displays the number of intervals needed and the upper and lower sum.
Input: The user must select one of three options from a menu. If the user selected one of the two equations, they will prompted for the value of the rightmost
x for the Riemann Sum formula. The user then inputs the desired epsilon. When the calculations are finished the user can input the menu options once more. This
continues until they input '3' to quit.
Output: The program will immediately print a menu with three options for the user to pick. Once the user has inputted the options if they've chosen the former
two options, the program will print out the chosen function, rightmost x value, epsilon, intervals needed to reach that epsilon, and the upper and lower sums.
The program then prints the menu again, repeating the exciting process until they choose to quit.
 */

#include <iostream>
#include <iomanip>
#include <cmath>

int MAX_RECTANGLES = 5000; //Global variable for the maximum intervals desired.
using namespace std;

//Prototypes for functions.
float rightSum(int recNum, float rightX, char menuSelect);
float leftSum(int recNum, float rightX, char menuSelect);
void calculations(float rightX, float epsilon, char menuSelect);
int main()
{
    char menuSelect; //Character for the option the user chooses in the menu.
    float rightX, epsilon; //Floats for the user-inputted rightmost x value and epsilon.
    do //Do loop so the program runs at least once, and then reruns if the user didn't quit.
    {
        cout << endl; //Makes the program look better when rerunning.
        cout << "Please select an option using the corresponding number." << endl;
        cout << "_____________________________" << endl;
        cout << "1. " << "Function 1 - f(x) = x^2 + 3" << endl;
        cout << "2. " << "Function 2 - f(x) = 2 * sqrt(x)" << endl;
        cout << "3. " << "Exit the program." << endl;
        cout << "_____________________________" << endl;
        cout << "Enter your choice: ";
        cin >> menuSelect; //User inputs their selection
        while (menuSelect != '1' && menuSelect != '2' && menuSelect != '3') //If the user failed to put in a valid selection, tries again.
                {
                cout << "That is not a valid input. Try again!" << endl;
                cout << "Enter your choice: ";
                cin >> menuSelect;
                }
        switch(menuSelect)
        {
        case '1': //If the user picked option one, prompts for inputs for rightmost x and epsilon.
            {
            cout << "Enter the value of the rightmost x: ";
            cin >> rightX;
            cout << "Enter the desired epsilon: ";
            cin >> epsilon;
            calculations(rightX, epsilon, menuSelect); //Sends the info to function to be calculated.
            break;
            }
        case '2': //If the user picked option two, they input x and epsilon.
            {
            cout << "Enter the value of the rightmost x: ";
            cin >> rightX;
            cout << "Enter the desired epsilon: ";
            cin >> epsilon;
            calculations(rightX, epsilon, menuSelect); //Sends x and epsilon to be calculated.
            break;
            }
        case '3': //If the user chooses to quit, ends the program.
            {
            cout << "Quitting..." << endl;
            return 0;
            break;
            }
        default:
            break;
            }
    }while(menuSelect != 3); //Makes sure the do loop keeps going as long as the user doesn't quit.
}

float rightSum(int recNum, float rightX, char menuSelect)
    {
     /*Finds the upperSum with rightmost points.
     Pre-condition: the sum is 0.
     Post-condition: the sum is now the total area of the rectangle intervals.*/
    float sum = 0; //Ensures the sum resets each time the function is called.
    float recWidth = rightX/recNum; //Calculates the width of the rectangle intervals.
    float recHeight; //Establishes variable for the height of a rectangle interval.
    for (int i = 1; i <= recNum; i = i + 1) //Keeps calculating sums until i reaches the number of intervals.
        {
        float curX = i * recWidth; //Current interval's x value.
        if (menuSelect == '1') //If the function chosen was 1, calculates the height at point x.
            recHeight = (pow(curX,2) + 3);
        if (menuSelect == '2') //If the function chosen was 2, calculates the height at point x.
            recHeight = (2 * sqrt(curX));
        float recArea = recWidth * recHeight; //Finds the area of the rectangle interval.
        sum = sum + recArea; //Adds the sum of all rectangle intervals.
        }
    return sum; //Returns the sum.
    }
float leftSum(int recNum, float rightX, char menuSelect)
    {
    /* Finds the lower sum with rightmost point.
    Pre-condition: the sum is 0.
    Post-condition: the sum is the total area of the rectangle intervals.*/
    float sum = 0; //Resets sum each time function is called.
    float recWidth = (rightX/recNum); //Width of the rectangle intervals.
    float recHeight; //Establishing height.
    for (int i = 1; i <= recNum; i = i +1 ) //Calculates sums until i is equal to intervals.
        {
        float curX = ((i - 1) * recWidth); //Current interval's x value.
        if (menuSelect == '1') //If function chosen is 1, finds height at point x.
            recHeight = (pow(curX,2) + 3);
        if (menuSelect == '2') //If function chose is 2, finds height at point x.
            recHeight = (2 * sqrt(curX));
        float recArea = recWidth * recHeight; //Calculating the area of the rectangle interval.
        sum = sum + recArea; //Sum of all rectangle intervals.
        }

    return sum;//Returns the lower sum.
    }
void calculations(float rightX, float epsilon, char menuSelect)
    {
        /* Calculates the number of intervals needed to reach the epsilon.
        Pre-condition: rightX, epsilon and menuSelect are the inputted values.
        Post-condition: the values are unchanged.*/
    int recNum = 1; //Ensures that there's already one interval when calculations begin.
    float upperSum, lowerSum; //Establishing the variables for the sums.
    do //Ensures it does calculations at least once before completion.
    {
        upperSum = rightSum(recNum, rightX, menuSelect); //Calls function each time it needs to be calculated.
        lowerSum = leftSum(recNum, rightX, menuSelect); //Calls function each time it needs to be calculated.
        recNum = recNum + 1; //Increases number of rectangles to prevent infinite looping.
    }while(((upperSum - lowerSum) > epsilon) && (recNum < MAX_RECTANGLES)); //Stops the do loop once criteria for program is met.

    cout << endl;
    cout << "Function chosen: " << menuSelect << endl;
    cout << "Rightmost x value: " << rightX << endl;
    cout << "Epsilon: " << epsilon << endl;

    if (recNum == MAX_RECTANGLES) //If the epsilon was not reached, displays a message stating so.
        cout << "Failed to hit the epsilon within " << MAX_RECTANGLES << " intervals. Here are the sums before hitting the limit:" << endl;
    if (recNum != MAX_RECTANGLES) //The do loop always over-counts if it does not reach the limit. This fixes that for display purposes.
        recNum = recNum - 1;

    //All this displays remaining information, and cleans up output for the next loop around.
    cout << fixed << setprecision(4);
    cout << "Intervals needed to reach epsilon: " << recNum << endl;
    cout << "Upper sum at " << recNum << " intervals: " << upperSum << endl;
    cout << "Lower sum at " << recNum << " intervals: " << lowerSum << endl;
    cout << endl;
    cout << "_____________________________" << endl;
    }


