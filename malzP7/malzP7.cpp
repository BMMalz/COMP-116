/*
Benjamin Malz
malzP7.cpp (Assignment 7)
Purpose: This program asks the user to input an infix equation. The program then converts the formula to postfix notation and solves it, displaying the answer to three decimal points of precision.
Input: The user must input an infix formula in the format of a float followed by an operator (+, -, *, /, or ^) repeated as many times as desired, finishing with a float and then '=', followed by pressing Enter.
Output: The program will display the answer to the inputted equation. There is an optional line of code (line 102) which, when enabled, displayed the postfix notation version of the inputted equation.
 */
#include <iostream>
#include <iomanip>
#include <cassert>
#include <sstream>
#include <cmath>

using namespace std;

bool isOp(char checkOp, char nextOp);
int precedenceChecker(float checkOp);
char floatToChar(float ascii);
float operandEvaluator(char oper, float leftOperand, float rightOperand);

template<class Type>
struct nodeType
{
    Type info; //Contains the data for the node
    nodeType<Type> *link; //Points to the next node if it exists
};

template <class Type>
class linkedStackType
{
public:
    //const linkedStackType<Type>& operator=(const linkedStackType<Type>&);
    void initializeStack();
    bool isEmptyStack() const;
    //bool isFullStack() const;
    void push(const Type& newItem);
    Type top() const;
    void pop();
    linkedStackType();
    //linkedStackType(const linkedStackType<Type>& otherStack);
    ~linkedStackType();
private:
    nodeType<Type> *stackTop; //Points to the node that is on top of the stack
    //void copyStack(const linkedStackType<Type>& otherStack);
};

int main()
{
    linkedStackType<float> myStack; //Initializing the float stack to be used in the program
    char opInput; //Variable for the inputted operators
    float floatInput; //Variable for the inputted floats
    float opAsFloat; //Variable that will be used to convert operators to floats so they are compatible with the stack
    bool inPlace; //Boolean to determine if the newly inputted operator is in the right place in the stack
    float finalAnswer; //Variable for the final answer
    stringstream postfixStringStream; //String stream to append pieces of the postfix equation as they are found

    cout << "Input your infix problem:" << endl;

    while (opInput != '=') //This loop will continue until the input is finished, which is when an '=' in input
    {
        inPlace = false; //Each time the loop goes around the new operator must again be put in place, so it is set to false
        cin >> floatInput; //Getting the     float input
        postfixStringStream << floatInput << " "; //Adding to the string stream with a space after
        cin.get(opInput); //Getting the operator input
        opAsFloat = opInput; //Converting it to its ASCII value so it can go in the stack
        if (opInput != '=') //Since the final input WILL be an '=' it should not be put into the stack
        {
            if(myStack.isEmptyStack()) //If the stack is empty there is no need to check anything, just put the operator in
            {
                myStack.push(opAsFloat); //Place the operator on the stack
            }
            else //If not empty
            {
                while (inPlace == false) //Loop so that the body is executed until the operator is in its rightful place
                    {
                        if (precedenceChecker(myStack.top()) >= precedenceChecker(opAsFloat)) //If the top operator has higher precedence than the new one
                        {
                            postfixStringStream << floatToChar(myStack.top()) << ' '; //Add the top operator and a space to the string stream
                            myStack.pop(); //Remove the top operator
                            if (myStack.isEmptyStack())
                            {
                                myStack.push(opAsFloat); //If the stack is empty, the new operator is added on
                                inPlace = true; //The new operator has found its place
                            }
                        }
                        else if (precedenceChecker(myStack.top()) <= precedenceChecker(opAsFloat)) //If the new operator has higher precedence, push it onto the stack
                        {
                            myStack.push(opAsFloat);
                            inPlace = true; //The operator is now in place
                        }
                    }
            }
        }
    }

    while(!myStack.isEmptyStack()) //After the input is complete, empty the remainder of the stack and add it to the end of the string stream
    {
        postfixStringStream << floatToChar(myStack.top()) << " ";
        myStack.pop(); //Ensure the stack is empty
    }

    string postfixString = postfixStringStream.str(); //Create a string of the string stream

    //cout << "Here it is in postfix: " << endl << postfixString << endl; //Display the postfix string if you so desire

    float newFloat; //Variable for floats read from string stream
    char newOper; //Variable for operators read from string stream
    for (int i = 0; i < postfixString.length();) //The for loop will go until the end of the string is reached
    {
        if (postfixString[i] == ' ')
        {
            i++; //If the current location is a space, move on
        }
        else if(!isOp(postfixString[i], postfixString[i+1])) //If the isOp function finds that the current position does not contain an operator
        {
            postfixStringStream >> newFloat; //Take in the float from the original string stream (Each time something is read from it, it maintains the position automatically
            stringstream lengthGetter; //String stream to take the float so it can be added to string
            lengthGetter << newFloat; //Read float
            string lengthGet = lengthGetter.str(); //Convert float to string
            int valueLength = lengthGet.length(); //Get the length of the float's characters
            myStack.push(newFloat); //Add the float to the stack
            i+=valueLength; //Move the pointer past the float processed
        }
        else if(isOp(postfixString[i], postfixString[i+1])) //If the isOp function finds that the current position does contain an operator
        {
            postfixStringStream >> newOper; //Read the operator from the string stream
            float rightOperand = myStack.top(); //Set the right operand to the current stack top
            myStack.pop(); //Remove it from the stack
            float leftOperand = myStack.top(); //Set the left operand to the value in the stack that was below the right operand
            myStack.pop(); //Remove that as well
            myStack.push(operandEvaluator(newOper, leftOperand, rightOperand)); //Push the result of the operation onto the stack
            i++; //Increase the position being looked at by the for loop by the length of the operator which is always one
        }
    }

    finalAnswer = myStack.top(); //After the whole string is evaluated, the only item in the stack is the answer
    cout << "And the answer is... ";
    cout << fixed << setprecision(3) << finalAnswer; //Displays the answer to 3 decimal places

    return 0; //Exit the program
}

template <class Type>
void linkedStackType<Type>::initializeStack()
//Creates the class' stack
{
    nodeType<Type> *temp; //Creates a temporary node

    while (stackTop != NULL)
    {
        temp = stackTop; //The temporary node is copied to stackTop
        stackTop = stackTop->link; //stackTop now points to something
        delete temp; //Removes temp from memory
    }
}

template <class Type>
bool linkedStackType<Type>::isEmptyStack() const
//Checks if the stack is empty. If stackTop is null, then the stack is empty.
{
    return (stackTop == NULL);
}

/*template <class Type>
bool linkedStackType<Type>::isFullStack() const
{
    return false;
}*/

template <class Type>
void linkedStackType<Type>::push(const Type& newItem)
//Takes in the data being pushed, creates a node for it and sets the new node as stackTop since it is on top
{
    nodeType<Type> *newNode; //Creating pointer to the new node

    newNode = new nodeType<Type>; //Creating the actual new node

    newNode->info = newItem; //The info in newNode is now the data being pushed
    newNode->link = stackTop; //The new node's link points to stackTop
    stackTop = newNode; //stackTop is now the new node
}

template <class Type>
Type linkedStackType<Type>::top() const
//Returns the data of the top node of the stack
{
    assert(stackTop != NULL); //Exits program if the stack top is null as this cannot return data otherwise
    return stackTop->info; //Return the data stored in the top item of the stack
}

template <class Type>
void linkedStackType<Type>::pop()
//Removes the top item from the stack
{
    nodeType<Type> *temp; //Temporary pointer

    if (stackTop != NULL) //Only executes if the stack is not empty
    {
        temp = stackTop; //Temporary pointer is stack top
        stackTop = stackTop->link; //stackTop is now next item in stack
        delete temp; //Delete temp and therefore the item being removed from the stack
    }
    else
    {
        cout << "Cannot remove from an empty stack." << endl;
    }
}

template <class Type>
linkedStackType<Type>::linkedStackType()
//Constructor, sets stackTop to null as no data yet
{
    stackTop = NULL;
}

template <class Type>
linkedStackType<Type>::~linkedStackType()
//Destructor - frees memory that was being used by a class once the class no longer exists.
{
    initializeStack();
}

int precedenceChecker(float checkOp)
//Takes in a float representing an operator and checks its precedence. Returns a number representing its precedence.
{
    if (checkOp == 43 || checkOp == 45)
        return 1; //'+' and '-' have the lowest operator precedence.
    if (checkOp == 42 || checkOp == 47)
        return 2; //'*' and '/' have higher precedence than '+' and '-'
    if (checkOp == 94)
        return 3; //'^' has the highest precedence
    else //The value given does not represent an operator. This should not happen as long as the input is valid.
    {
        cout << "Invalid operator." << endl;
        return 0;
    }
}

char floatToChar (float ascii)
//Takes in a float representing an ASCII value and checks what character it represents, then returns the character
{
    if (ascii == 43)
        return '+';
    if (ascii == 45)
        return '-';
    if (ascii == 42)
        return '*';
    if (ascii == 47)
        return '/';
    if (ascii == 94)
        return '^';
    else //If the value is not one of the 5 valid operators, return a ! representing invalid operator
        return '!';
}

bool isOp(char checkOp, char nextOp)
//Takes two chars and checks if the first is a valid operator, and examines the second if the first was a '-' to see if it just represents a negative number. Returns true or false.
{
    if(checkOp == '+')
        return true;
    if(checkOp == '-')
    {
        if(nextOp != ' ') //If the character following the '-' is anything other than a space, then it's a negative number
            return false;
        else
            return true;
    }
    if(checkOp == '*')
        return true;
    if(checkOp == '/')
        return true;
    if(checkOp == '^')
        return true;
    else //If the character was not an operator, return false
        return false;
}

float operandEvaluator(char oper, float leftOperand, float rightOperand)
//Takes a char and two operands and performs the char's operator's operation on the operands. Returns result.
{
    if (oper == '+')
    {
        return (leftOperand + rightOperand);
    }
    if (oper == '-')
    {
        return (leftOperand - rightOperand);
    }
    if (oper == '*')
    {
        return (leftOperand * rightOperand);
    }
    if (oper == '/')
    {
        if (rightOperand != 0)
            return (leftOperand/rightOperand);
        else //If dividing by 0, display a message and return 0 so there's still at least an answer to the rest of the equation
        {
            cout << "You can't divide by zero... will make result of division 0." << endl;
            return 0;
        }
    }
    if (oper == '^')
        return (pow(leftOperand, rightOperand));
    else //In scenario where the operator given is not valid, simply return 0
    {
        return 0;
    }
}
