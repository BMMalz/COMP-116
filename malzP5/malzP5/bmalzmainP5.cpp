#include "bmalzP5.h"

int main()
{
    binary one, two, three; //Creates three instances of the binary class.
    int inum;

    cout << "Type in two binary numbers to add." << endl;
    cin >> one; //Takes in a binary value for instance one.
    cin >> two; //Takes in a binary value for instance two.
    cout << "Number one: " << one << endl;
    cout << "Number two: " << two << endl;
    cout << "Decimal one: ";
    cout << one.toDecimal() << endl; //Prints the decimal value of instance one.
    cout << "Decimal two: ";
    cout << two.toDecimal() << endl; //Prints the decimal value of instance two.
    one = one + two; //Adding instance one to two.
    cout << "Sum is: " << one << endl; //Displaying the sum.
    cout << "As a decimal: " << one.toDecimal() << endl; //Displaying the decimal sum.

    inum = 18;
    three = inum; //Setting instance three equal to inum.
    three = three + 4; //Adding 4 to instance three.
    three++; //Incrementing instance three by one.
    cout << "Binary value of three is: " << three << endl; //Displaying the final result.
    cout << "Decimal value is: " << three.toDecimal() << endl; //As a decimal too.
    return 0;
}
