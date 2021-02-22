/*
Benjamin Malz
malz2.cpp (Assignment 2)
Purpose: This program allows users to select one of four items at the esteemed Rinky Dinky Palinky store. Once the item is selected, a discount can be applied
and the user will be prompted to input the money amount they will spend. The program will then calculate how much change they receive after discount and taxes.
Input: The user must input a character, A, B, C, or D to select an item from the menu. Afterwards, they will be asked to input either a 'Y' or 'N' to answer
if they have a discount. If they do, they are asked to put in the percent of discount they have. If not, the program proceeds to the next step without a discount.
They are then prompted to input the amount of money they are paying.
Output: On startup, the program displays a menu with four products, their respective letter code, and their prices. After going through the input steps, the receipt
will display the price of the item, the discount percentage and how much money that takes off their purchase (if applicable), the Massachusetts tax and how much that
adds to the purchase, the total amount of money, the amount paid and the change due. In addition to displaying this information in the console, the information is
saved in the same format to a text file called "salesSlip.txt" which is created and placed in the folder containing the .cpp file. */


#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int main()
{
    char inpCode, percentSymb, discAnswer; //Characters for the selection code, percentage symbol and answer to discount question.
    float BLUE_PRICE, RED_PRICE, LITTLE_PRICE, RINKY_PRICE, MA_TAX, discountAmount, discountAsPercent, moneyTendered; //Local variables for prices and tax, discount percentage and discount before being converted to percentage, and money tendered.
    BLUE_PRICE = 24.99;
    RED_PRICE = 22.99;
    LITTLE_PRICE = 20.99;
    RINKY_PRICE = 10.99;
    MA_TAX = .0625;
    cout << "Welcome to the Rinky Dinky Palinky store!" << endl;
    cout << "Enter the corresponding letter to order the item. Our wares are as follows:" << endl;
    cout << " Code" << setw(7) << "Price" << setw(7) << "Type" << endl;
    cout << "------------------------------------------" << endl;
    cout << setw(3) << "A" << setw(9) << BLUE_PRICE << setw(22) << "Big Blue Pinkie Boo" << endl;
    cout << setw(3) << "B" << setw(9) << RED_PRICE << setw(13) << "Red Rinkie" << endl;
    cout << setw(3) << "C" << setw(9) << LITTLE_PRICE << setw(15) << "Little Dinky" << endl;
    cout << setw(3) << "D" << setw(9) << RINKY_PRICE << setw(23) << "Rinky Dinky Doohinky" << endl;
    cout << "What is your selection?" << endl;
    cin >> inpCode; //The user puts in a single character. It is used in switch statements later.
    cout << "And do you have a discount? (Y/N)" << endl;
    cin >> discAnswer; //If the user answers with a 'y' or 'Y' they are prompted for the discount.
    if (discAnswer == 'Y'|| discAnswer == 'y')
        {
        cout << "What is your discount percentage? (Please input the percent sign too)" << endl;
        cin >> discountAsPercent >> percentSymb; //The user must also put in the percent sign too because it looks proper that way.
        discountAmount = discountAsPercent / 100; //This makes the percentage compatible with the price for calculation purposes
        }
    else
    {

        discountAsPercent = 0; //Sets the variable values because later parts of the program require them.
        discountAmount = 0;
    }
    cout << "How much will you be paying?" << endl;
    cin >> moneyTendered; //The money being given is needed for both calculations and actually getting paid.
    switch (inpCode) //Based on the character input earlier in the code, calculations are done for the math of the respective items.
    {
        case 'A':
            {


            ifstream inFP; //Preparing variables for writing to files
            ofstream outFP;
            cout << fixed << showpoint; //Forces decimals to appear after all numbers
            outFP.open("salesSlip.txt"); //Opens a new text file to write to
            float actualDiscount, actualTax, actualTotal, changeDue; // Variables to do the math in the switch statement
            actualDiscount = (BLUE_PRICE * discountAmount); //Calculates the actual monetary value of the discount with respect to the selection
            actualTax = (BLUE_PRICE * MA_TAX); //Calculates the monetary value of the discount with respect to the selection
            actualTotal = (BLUE_PRICE - actualDiscount + actualTax); //Calculates the total money due after the discount (if there is one) and with taxes added
            changeDue = (moneyTendered - actualTotal); //Calculates change due with money given
            cout << "Price (Code A)..........." << setw(8) << setprecision(2) << BLUE_PRICE << endl;
            outFP << "Price (Code A)..........." << setw(8) << setprecision(2) << BLUE_PRICE << endl; //Writes every line printed to console in the text file
            if (discountAsPercent != 0 && discountAsPercent > 0) //If there is a discount, prints the discount
            {
                cout << "Discount (" << discountAsPercent << "%)........." << setw(7) << setprecision(2) << actualDiscount << endl;
                outFP << "Discount (" << discountAsPercent << "%)........." << setw(7) << setprecision(2) << actualDiscount << endl;

            }
            cout << "MA Tax (6.25%)..........." << setw(8) << setprecision(2) << actualTax << endl;
            outFP << "MA Tax (6.25%)..........." << setw(8) << setprecision(2) << actualTax << endl;
            cout << endl;
            outFP << endl;
            cout << "TOTAL...................." << setw(8) << setprecision(2) << actualTotal << endl;
            outFP << "TOTAL...................." << setw(8) << setprecision(2) << actualTotal << endl;
            cout << endl;
            outFP << endl;
            cout << "Money given.............." << setw(8) << setprecision(2) << moneyTendered << endl;
            outFP << "Money given.............." << setw(8) << setprecision(2) << moneyTendered << endl;
            cout << "Change..................." << setw(8) << setprecision(2) << changeDue << endl;
            outFP << "Change..................." << setw(8) << setprecision(2) << changeDue << endl;
            cout << endl;
            outFP << endl;
            cout << "Thanks for shopping here! Please come again soon!";
            outFP << "Thanks for shopping here! Please come again soon!";
            outFP.close(); //Closes the text file as it's no longer needed.
            break;
    }

        case 'a': //The rest of the cases function the same as case A with tweaks for the different products.
            {

            ifstream inFP;
            ofstream outFP;
            cout << fixed << showpoint; //Forces decimals to appear after all numbers
            outFP.open("salesSlip.txt");
            float actualDiscount, actualTax, actualTotal, changeDue; // Variables to do the math in the switch statement
            actualDiscount = (BLUE_PRICE * discountAmount);
            actualTax = (BLUE_PRICE * MA_TAX);
            actualTotal = (BLUE_PRICE - actualDiscount + actualTax);
            changeDue = (moneyTendered - actualTotal);
            cout << "Price (Code A)..........." << setw(8) << setprecision(2) << BLUE_PRICE << endl;
            outFP << "Price (Code A)..........." << setw(8) << setprecision(2) << BLUE_PRICE << endl;
            if (discountAsPercent != 0 && discountAsPercent > 0)
            {
                cout << "Discount (" << discountAsPercent << "%)........." << setw(7) << setprecision(2) << actualDiscount << endl;
                outFP << "Discount (" << discountAsPercent << "%)........." << setw(7) << setprecision(2) << actualDiscount << endl;

            }
            cout << "MA Tax (6.25%)..........." << setw(8) << setprecision(2) << actualTax << endl;
            outFP << "MA Tax (6.25%)..........." << setw(8) << setprecision(2) << actualTax << endl;
            cout << endl;
            outFP << endl;
            cout << "TOTAL...................." << setw(8) << setprecision(2) << actualTotal << endl;
            outFP << "TOTAL...................." << setw(8) << setprecision(2) << actualTotal << endl;
            cout << endl;
            outFP << endl;
            cout << "Money given.............." << setw(8) << setprecision(2) << moneyTendered << endl;
            outFP << "Money given.............." << setw(8) << setprecision(2) << moneyTendered << endl;
            cout << "Change..................." << setw(8) << setprecision(2) << changeDue << endl;
            outFP << "Change..................." << setw(8) << setprecision(2) << changeDue << endl;
            cout << endl;
            outFP << endl;
            cout << "Thanks for shopping here! Please come again soon!";
            outFP << "Thanks for shopping here! Please come again soon!";
            outFP.close();
            break;
            }

        case 'B':
            {


            ifstream inFP;
            ofstream outFP;
            cout << fixed << showpoint; //Forces decimals to appear after all numbers
            outFP.open("salesSlip.txt");
            float actualDiscount, actualTax, actualTotal, changeDue; // Variables to do the math in the switch statement
            actualDiscount = (RED_PRICE * discountAmount);
            actualTax = (RED_PRICE * MA_TAX);
            actualTotal = (RED_PRICE - actualDiscount + actualTax);
            changeDue = (moneyTendered - actualTotal);
            cout << "Price (Code B)..........." << setw(8) << setprecision(2) << RED_PRICE << endl;
            outFP << "Price (Code B)..........." << setw(8) << setprecision(2) << RED_PRICE << endl;
            if (discountAsPercent != 0 && discountAsPercent > 0)
            {
                cout << "Discount (" << discountAsPercent << "%)........." << setw(7) << setprecision(2) << actualDiscount << endl;
                outFP << "Discount (" << discountAsPercent << "%)........." << setw(7) << setprecision(2) << actualDiscount << endl;

            }
            cout << "MA Tax (6.25%)..........." << setw(8) << setprecision(2) << actualTax << endl;
            outFP << "MA Tax (6.25%)..........." << setw(8) << setprecision(2) << actualTax << endl;
            cout << endl;
            outFP << endl;
            cout << "TOTAL...................." << setw(8) << setprecision(2) << actualTotal << endl;
            outFP << "TOTAL...................." << setw(8) << setprecision(2) << actualTotal << endl;
            cout << endl;
            outFP << endl;
            cout << "Money given.............." << setw(8) << setprecision(2) << moneyTendered << endl;
            outFP << "Money given.............." << setw(8) << setprecision(2) << moneyTendered << endl;
            cout << "Change..................." << setw(8) << setprecision(2) << changeDue << endl;
            outFP << "Change..................." << setw(8) << setprecision(2) << changeDue << endl;
            cout << endl;
            outFP << endl;
            cout << "Thanks for shopping here! Please come again soon!";
            outFP << "Thanks for shopping here! Please come again soon!";
            outFP.close();
            break;
            }

        case 'b':
            {


            ifstream inFP;
            ofstream outFP;
            cout << fixed << showpoint; //Forces decimals to appear after all numbers
            outFP.open("salesSlip.txt");
            float actualDiscount, actualTax, actualTotal, changeDue; // Variables to do the math in the switch statement
            actualDiscount = (RED_PRICE * discountAmount);
            actualTax = (RED_PRICE * MA_TAX);
            actualTotal = (RED_PRICE - actualDiscount + actualTax);
            changeDue = (moneyTendered - actualTotal);
            cout << "Price (Code B)..........." << setw(8) << setprecision(2) << RED_PRICE << endl;
            outFP << "Price (Code B)..........." << setw(8) << setprecision(2) << RED_PRICE << endl;
            if (discountAsPercent != 0 && discountAsPercent > 0)
            {
                cout << "Discount (" << discountAsPercent << "%)........." << setw(7) << setprecision(2) << actualDiscount << endl;
                outFP << "Discount (" << discountAsPercent << "%)........." << setw(7) << setprecision(2) << actualDiscount << endl;

            }
            cout << "MA Tax (6.25%)..........." << setw(8) << setprecision(2) << actualTax << endl;
            outFP << "MA Tax (6.25%)..........." << setw(8) << setprecision(2) << actualTax << endl;
            cout << endl;
            outFP << endl;
            cout << "TOTAL...................." << setw(8) << setprecision(2) << actualTotal << endl;
            outFP << "TOTAL...................." << setw(8) << setprecision(2) << actualTotal << endl;
            cout << endl;
            outFP << endl;
            cout << "Money given.............." << setw(8) << setprecision(2) << moneyTendered << endl;
            outFP << "Money given.............." << setw(8) << setprecision(2) << moneyTendered << endl;
            cout << "Change..................." << setw(8) << setprecision(2) << changeDue << endl;
            outFP << "Change..................." << setw(8) << setprecision(2) << changeDue << endl;
            cout << endl;
            outFP << endl;
            cout << "Thanks for shopping here! Please come again soon!";
            outFP << "Thanks for shopping here! Please come again soon!";
            outFP.close();
            break;
            }

        case 'C':
            {


            ifstream inFP;
            ofstream outFP;
            cout << fixed << showpoint; //Forces decimals to appear after all numbers
            outFP.open("salesSlip.txt");
            float actualDiscount, actualTax, actualTotal, changeDue; // Variables to do the math in the switch statement
            actualDiscount = (LITTLE_PRICE * discountAmount);
            actualTax = (LITTLE_PRICE * MA_TAX);
            actualTotal = (LITTLE_PRICE - actualDiscount + actualTax);
            changeDue = (moneyTendered - actualTotal);
            cout << "Price (Code C)..........." << setw(8) << setprecision(2) << LITTLE_PRICE << endl;
            outFP << "Price (Code C)..........." << setw(8) << setprecision(2) << LITTLE_PRICE << endl;
            if (discountAsPercent != 0 && discountAsPercent > 0)
            {
                cout << "Discount (" << discountAsPercent << "%)........." << setw(7) << setprecision(2) << actualDiscount << endl;
                outFP << "Discount (" << discountAsPercent << "%)........." << setw(7) << setprecision(2) << actualDiscount << endl;

            }
            cout << "MA Tax (6.25%)..........." << setw(8) << setprecision(2) << actualTax << endl;
            outFP << "MA Tax (6.25%)..........." << setw(8) << setprecision(2) << actualTax << endl;
            cout << endl;
            outFP << endl;
            cout << "TOTAL...................." << setw(8) << setprecision(2) << actualTotal << endl;
            outFP << "TOTAL...................." << setw(8) << setprecision(2) << actualTotal << endl;
            cout << endl;
            outFP << endl;
            cout << "Money given.............." << setw(8) << setprecision(2) << moneyTendered << endl;
            outFP << "Money given.............." << setw(8) << setprecision(2) << moneyTendered << endl;
            cout << "Change..................." << setw(8) << setprecision(2) << changeDue << endl;
            outFP << "Change..................." << setw(8) << setprecision(2) << changeDue << endl;
            cout << endl;
            outFP << endl;
            cout << "Thanks for shopping here! Please come again soon!";
            outFP << "Thanks for shopping here! Please come again soon!";
            outFP.close();
            break;
            }

        case 'c':
            {


            ifstream inFP;
            ofstream outFP;
            cout << fixed << showpoint; //Forces decimals to appear after all numbers
            outFP.open("salesSlip.txt");
            float actualDiscount, actualTax, actualTotal, changeDue; // Variables to do the math in the switch statement
            actualDiscount = (LITTLE_PRICE * discountAmount);
            actualTax = (LITTLE_PRICE * MA_TAX);
            actualTotal = (LITTLE_PRICE - actualDiscount + actualTax);
            changeDue = (moneyTendered - actualTotal);
            cout << "Price (Code C)..........." << setw(8) << setprecision(2) << LITTLE_PRICE << endl;
            outFP << "Price (Code C)..........." << setw(8) << setprecision(2) << LITTLE_PRICE << endl;
            if (discountAsPercent != 0 && discountAsPercent > 0)
            {
                cout << "Discount (" << discountAsPercent << "%)........." << setw(7) << setprecision(2) << actualDiscount << endl;
                outFP << "Discount (" << discountAsPercent << "%)........." << setw(7) << setprecision(2) << actualDiscount << endl;

            }
            cout << "MA Tax (6.25%)..........." << setw(8) << setprecision(2) << actualTax << endl;
            outFP << "MA Tax (6.25%)..........." << setw(8) << setprecision(2) << actualTax << endl;
            cout << endl;
            outFP << endl;
            cout << "TOTAL...................." << setw(8) << setprecision(2) << actualTotal << endl;
            outFP << "TOTAL...................." << setw(8) << setprecision(2) << actualTotal << endl;
            cout << endl;
            outFP << endl;
            cout << "Money given.............." << setw(8) << setprecision(2) << moneyTendered << endl;
            outFP << "Money given.............." << setw(8) << setprecision(2) << moneyTendered << endl;
            cout << "Change..................." << setw(8) << setprecision(2) << changeDue << endl;
            outFP << "Change..................." << setw(8) << setprecision(2) << changeDue << endl;
            cout << endl;
            outFP << endl;
            cout << "Thanks for shopping here! Please come again soon!";
            outFP << "Thanks for shopping here! Please come again soon!";
            outFP.close();
            break;
            }

        case 'D':
            {


            ifstream inFP;
            ofstream outFP;
            cout << fixed << showpoint; //Forces decimals to appear after all numbers
            outFP.open("salesSlip.txt");
            float actualDiscount, actualTax, actualTotal, changeDue; // Variables to do the math in the switch statement
            actualDiscount = (RINKY_PRICE * discountAmount);
            actualTax = (RINKY_PRICE * MA_TAX);
            actualTotal = (RINKY_PRICE - actualDiscount + actualTax);
            changeDue = (moneyTendered - actualTotal);
            cout << "Price (Code D)..........." << setw(8) << setprecision(2) << RINKY_PRICE << endl;
            outFP << "Price (Code D)..........." << setw(8) << setprecision(2) << RINKY_PRICE << endl;
            if (discountAsPercent != 0 && discountAsPercent > 0)
            {
                cout << "Discount (" << discountAsPercent << "%)........." << setw(7) << setprecision(2) << actualDiscount << endl;
                outFP << "Discount (" << discountAsPercent << "%)........." << setw(7) << setprecision(2) << actualDiscount << endl;

            }
            cout << "MA Tax (6.25%)..........." << setw(8) << setprecision(2) << actualTax << endl;
            outFP << "MA Tax (6.25%)..........." << setw(8) << setprecision(2) << actualTax << endl;
            cout << endl;
            outFP << endl;
            cout << "TOTAL...................." << setw(8) << setprecision(2) << actualTotal << endl;
            outFP << "TOTAL...................." << setw(8) << setprecision(2) << actualTotal << endl;
            cout << endl;
            outFP << endl;
            cout << "Money given.............." << setw(8) << setprecision(2) << moneyTendered << endl;
            outFP << "Money given.............." << setw(8) << setprecision(2) << moneyTendered << endl;
            cout << "Change..................." << setw(8) << setprecision(2) << changeDue << endl;
            outFP << "Change..................." << setw(8) << setprecision(2) << changeDue << endl;
            cout << endl;
            outFP << endl;
            cout << "Thanks for shopping here! Please come again soon!";
            outFP << "Thanks for shopping here! Please come again soon!";
            outFP.close();
            break;
            }

        case 'd':
            {


             ifstream inFP;
            ofstream outFP;
            cout << fixed << showpoint; //Forces decimals to appear after all numbers
            outFP.open("salesSlip.txt");
            float actualDiscount, actualTax, actualTotal, changeDue; // Variables to do the math in the switch statement
            actualDiscount = (RINKY_PRICE * discountAmount);
            actualTax = (RINKY_PRICE * MA_TAX);
            actualTotal = ((RINKY_PRICE - actualDiscount) + actualTax);
            changeDue = (moneyTendered - actualTotal);
            cout << "Price (Code D)..........." << setw(8) << setprecision(2) << RINKY_PRICE << endl;
            outFP << "Price (Code D)..........." << setw(8) << setprecision(2) << RINKY_PRICE << endl;
            if (discountAsPercent != 0 && discountAsPercent > 0)
            {
                cout << "Discount (" << discountAsPercent << "%)........." << setw(7) << setprecision(2) << actualDiscount << endl;
                outFP << "Discount (" << discountAsPercent << "%)........." << setw(7) << setprecision(2) << actualDiscount << endl;

            }
            actualTotal = ((RINKY_PRICE - actualDiscount) + actualTax);
            changeDue = (moneyTendered - actualTotal);
            cout << "MA Tax (6.25%)..........." << setw(8) << setprecision(2) << actualTax << endl;
            outFP << "MA Tax (6.25%)..........." << setw(8) << setprecision(2) << actualTax << endl;
            cout << endl;
            outFP << endl;
            cout << "TOTAL...................." << setw(8) << setprecision(2) << actualTotal << endl;
            outFP << "TOTAL...................." << setw(8) << setprecision(2) << actualTotal << endl;
            cout << endl;
            outFP << endl;
            cout << "Money given.............." << setw(8) << setprecision(2) << moneyTendered << endl;
            outFP << "Money given.............." << setw(8) << setprecision(2) << moneyTendered << endl;
            cout << "Change..................." << setw(8) << setprecision(2) << changeDue << endl;
            outFP << "Change..................." << setw(8) << setprecision(2) << changeDue << endl;
            cout << endl;
            outFP << endl;
            cout << "Thanks for shopping here! Please come again soon!";
            outFP << "Thanks for shopping here! Please come again soon!";
            outFP.close();
            break;
            }

        default: //If the user fails to input a character that leads to a real choice, they will receive this message.
            {
            cout << "The code you entered is not valid. Sorry!";
            break;
            }
    }




}
