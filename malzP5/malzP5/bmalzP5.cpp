#include "bmalzP5.h"

binary::binary()
//Default constructor, sets the length, binary value and decimal value to 0
{

    counter = 0;
    *(binarray) = 0;
    decimalValue = 0;
}

binary::binary(const binary& bin)
//Copy constructor
{
    binary newBinary;
    newBinary.decimalValue = bin.decimalValue;
    newBinary.toBinary(decimalValue, newBinary);
}

istream& operator>>(istream& ci, binary& bin)
//Overloaded input operator. Allows user to input characters that are converted to integers and stored in the binary array.
{
    char input = 0; //Variable for the inputted character.
    while(input != '\n') //While loop that will execute as long as the input is not a newline character.
    {
        ci.get(input); //Each loop will read in one character.
        if (input == '\n')
            bin.counter = bin.counter; //Just telling it to not do anything important so it does not execute the else statement and next loop it recognizes the input is newline.
        else
        {
            int charToInt = (input - 48); //Convert the character from an ASCII number to an actual integer.
            *(bin.binarray + bin.counter) = charToInt; //The position in the array is then filled by the converted integer.
            bin.counter++; //Increase the counter for the length of the binary number.
        }
    }
    bin.decimalValue = bin.toDecimal(); //Convert the final product into a decimal for use in later parts of the program.
    return ci;
}

ostream& operator<<(ostream& co, binary& bin)
//Outputs the binary number one array value at a time.
{
    int outcounter = 0; //Counter that tracks the loops in this overloaded operator.
    while (outcounter < bin.counter) //Executes as long as the loop counter is below the length of the binary number.
    {
        co << *(bin.binarray + outcounter); //Prints the value stored in the specific array position.
        outcounter++; //Increases the loop count.
    }
    return co;
}

int binary::toDecimal()
//Method that converts the binary number to its decimal counterpart.
{
    int reverseCount = (counter - 1); //Variable that goes in reverse order of the binary number's length to suit the manual conversion which also goes in reverse order.
    int deciVal = 0; //Variable for the decimal value of the specific number.
    for(int i = 0; i < counter; i++)
    {
        int powTimesBin; //Integer for the current power multiplied by the current binary integer.
        int currentPow = pow(2, i); //Variable for two to the power of the current loop number.
        int currentBin = *(binarray + reverseCount); //Takes the current array number as an int.
        if (currentBin == 0)
            powTimesBin = 0; //If the binary value is 0, then the result is 0.
        else
        {
            powTimesBin = currentPow; //Otherwise, the value is the current square root value.
        }
        deciVal = (deciVal + powTimesBin); //Adds the current power result to the decimal value.
        reverseCount--; //Decrease the count.
    }
    return deciVal;
}

void binary::toBinary(int decimalValue, binary& bin)
//Convert a decimal value to binary. Since this is by reference, no return type.
{
    bin.counter = 0; //Sets the length to zero for the new binary value.
    int numerator = decimalValue; //The numerator is the decimal value, but will be divided up, hence the new variable.
    while (numerator > 1) //While loop to determine the length of the binary integer.
    {
        numerator = (numerator / 2); //Halves the numerator.
        bin.counter++; //Increases the length of the array.
        if (numerator == 1) //Once the numerator is one, increase the length one last time.
            bin.counter ++;
    }
    numerator = decimalValue; //Resetting numerator.
    int reverseCount = (bin.counter - 1); //Another reverse count like in the toDecimal method.
    for (int i = 0; i < bin.counter; i++) //Now that the length is known, the value can be stored.
    {
        int binaryAppend = (numerator % 2); //The remainder of the halved number is the binary value.
        numerator = (numerator / 2); //Divide the numerator again.
        *(bin.binarray + reverseCount) = binaryAppend; //Storing in array.
        reverseCount--; //Decrease count.
    }

}



binary& operator+(binary& binone, binary& bintwo)
//Adds two binary objects together.
{
    int decOne = binone.toDecimal(); //Converts the binary value of the first object to a decimal value.
    int decTwo = bintwo.toDecimal(); //Converts the binary value of the second object to a decimal value.
    int resultCombine = (decOne + decTwo); //Adds the two values together.
    binone.decimalValue = resultCombine; //Changes the value of the first object.
    binone.toBinary(binone.decimalValue, binone); //Changes the binary value to reflect the new value.
    return binone;
}

int operator+(int operInt, binary& bin)
//Adds a binary object's value to an integer.
{
    int binDec = bin.toDecimal(); //The binary object's value.
    int resultCombine = (operInt + binDec); //Combines the integer with the binary value.
    return resultCombine;
}

binary& operator+(binary& bin, int operInt)
//Adds an integer to a binary object.
{
    int binDec = bin.toDecimal(); //The object's decimal value as an int.
    int decCombine = (binDec + operInt); //Combines the decimal value with the int.
    bin.decimalValue = decCombine; //Changes the old decimal value to the new one.
    bin.toBinary(bin.decimalValue, bin); //Converts it to binary.
    return bin;
}

binary& binary::operator=(int operInt)
//Sets a binary object's value to an integer's value.
{
    this->decimalValue = operInt; //Sets the binary decimal value to the integer's value.
    this->toBinary(decimalValue, *this); //Converts the value to binary.
    return *this;
}

binary& operator+=(binary& bin, binary& bintwo)
//Increases a binary object's value by another binary object's value.
{
    int decOne = bin.decimalValue; //Decimal value of object one.
    int decTwo = bintwo.decimalValue; //Decimal value of object two.
    int decCombine = (decOne + decTwo); //Combined values.
    bin.decimalValue = decCombine; //Sets the first object's decimal value to the combined value.
    bin.toBinary(bin.decimalValue, bin); //Converts the new value to binary.

    return bin;

}

binary& operator++(binary& bin, int num)
//Increments a binary object by one.
{
    num = 1;
    int binDec = bin.decimalValue; //Decimal value of the object.
    int newVal = binDec + num; //Adds one to decimal value.
    bin.decimalValue = newVal; //Changes the object's decimal value.
    bin.toBinary(bin.decimalValue, bin); //Converts it to binary.

    return bin;
}
