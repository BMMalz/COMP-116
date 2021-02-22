//Benjamin Malz
//bmalzP1.cpp (Assignment P1)
//Purpose: This program tackles the difficult issue of how to efficiently purchase palinkies. The program will conveniently sort palinkies into their box sizes
//in the most cost and space efficient manner.
//Input: The program prompts users to enter an integer, representative of the amount of palinkies they are interesting in buying.
//Output: The program displays information for how many of each type of palinky box to purchase based on the inputted integer. The program adds up all boxes,
//their prices and displays both the individual prices and quantity of each box size as well as the total cost and amount of boxes needed.


#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int hugeBox, lrgBox, medBox, smlBox, totalBox; //Variables for amounts of the sizes of boxes, as well as totals boxes.
    int totalAmt; //Variable for total amount of palinkies.
    float hugeCost, lrgCost, medCost, smlCost, totalCost; //Variables for the cost of each box size, and total cost.
    int divPalink; //The total amount of palinkies that is later divided to determine box amounts.
    cout << "How many palinkies do you want?" <<endl;
    cin >> totalAmt; //Prompts user for amount of palinkies desired.
    divPalink = totalAmt; //Alternate variable for total that can be altered without messing up real total palinky count.
    hugeBox = divPalink/25; //Determines how many of the palinkies can be taken care of using large boxes.
    divPalink = divPalink%25; //This remainder is the new total amount of palinkies that must be boxed.
    lrgBox = divPalink/10; //Determines how many of the remaining unboxed palinkies can be dealt with using large boxes.
    divPalink = divPalink%10; //New total number of unboxed palinkies.
    medBox = divPalink/5; //How many of the remaining unboxed palinkies can be fit into medium boxes.
    divPalink = divPalink%5; //The final time the palinky remainder needs to be calculated.
    smlBox = divPalink/1; //The remaining palinkies that do not fit into any other box size can be placed in here.
    totalBox = hugeBox + lrgBox + medBox + smlBox; //Adds total amount of boxes and assigns to totalBox variable.
    hugeCost = hugeBox * 2.50; //Multiplies amount of huge sized boxes by their cost of $2.50 for a total huge box price.
    lrgCost = lrgBox * 1.50; //Multiplies large boxes by cost of $1.50 for total large box price.
    medCost = medBox * 1.00; //Multiplies medium boxes by cost of $1.00 for total medium box price.
    smlCost = smlBox * 0.25; //Multiplies small boxes by cost of $0.25 for total small box price.
    totalCost = hugeCost + lrgCost + medCost + smlCost; //Adds up all costs for the total cost of buying the various boxes.
    cout << fixed << showpoint; //For formatting purposes, allows setprecision() to work as intended.
    cout << "Palinkies desired:" << setw(5) << totalAmt << endl;
    cout << setw(19) << "Boxes" << setw(8) << "Cost" << endl;
    cout << "Huge Boxes:" << setw(8) << hugeBox << setw(8) << setprecision(2) << hugeCost << endl;
    cout << "Large Boxes:" << setw(7) << lrgBox << setw(8) << setprecision(2) << lrgCost << endl;
    cout << "Medium Boxes:" << setw(6) << medBox << setw(8) << setprecision(2) << medCost << endl;
    cout << "Small Boxes:" << setw(7) << smlBox << setw(8) << setprecision(2) << smlCost << endl;
    cout << "_____________________________" << endl;
    cout << "Totals:" << setw(12) << totalBox << setw(5) << "$" << setprecision(2) << totalCost << endl;


}
