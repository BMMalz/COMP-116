/*
Benjamin Malz
malzP5.zip (Assignment 5)
Purpose: This program allows the user to input their own binary values of up to 20, and then add them, increment them, display them, set them equal to each other, add an integer
to the binary value, add the binary value to the integer, or increment the binary value. In the included main file, three binary instances are made. Two of them are input by the user
and are then displayed, and then instance two is added to one and displayed. A third instance is set equal to 18, then increased by 4, incremented and then displayed.
Input: The user is prompted for however many binary instances main() asks for. In the included main file, the user must input two binary integers, hitting enter after each one.
Output: The program will display whatever binary instance it is asked to, and will display the decimal value if prompted using binary.toDecimal() in cout. In the included main file, the
output is two binary values in both binary and decimal forms, and then the sum of the two binary values, again as both binary and decimal. A third instance that the user does not input is
also displayed as binary and decimal.
 */

#include <iostream>
#include <cmath>


using namespace std;
const int MAX_SPACE = 20; //The maximum amount of characters the binary array will take.


class binary
{
    int binarray[MAX_SPACE]; //An array to store the binary values inputted. The name is hilarious. Please laugh.
    int counter; //This variable counts the number of digits in the array for input and other purposes
    int decimalValue; //Variable for the eventual converted decimal amount

public:
    binary(); //Constructor prototype
    binary(const binary& bin); //Copy constructor prototype
    friend istream& operator>>(istream& ci, binary& bin); //Overloaded input prototype
    friend ostream& operator<<(ostream& co, binary& bin); //Overloaded output prototype
    friend binary& operator+(binary& binone, binary& bintwo); //Overloaded binary on binary addition prototype
    friend int operator+(int operInt, binary& bin); //Overloaded integer plus binary addition prototype
    friend binary& operator+(binary& bin, int operInt); //Overloaded binary plus integer addition prototype
    binary& operator=(int operInt); //Overloaded equals operator prototype
    friend binary& operator+=(binary& bin, binary& bintwo); //Overloaded plus equals operator prototype
    friend binary& operator++(binary& bin, int); //Overloaded post-increment ++ operator prototype
    int toDecimal(); //Prototype for method that converts binary to decimal
    void toBinary(int decimalValue, binary& bin); //Prototype for method that converts decimal to binary
};
