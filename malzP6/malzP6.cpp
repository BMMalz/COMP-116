/*
Benjamin Malz
malzP6.cpp (Assignment 6)
Purpose: This program reads in a user-defined filename and displays stats for its words in multiple ways, including a user defined lowest and highest occurrences.
Input: The user is prompted for a filename to be read followed by a highest and lowest number of occurrences to display. The remaining input is done automatically from a text document.
Output: If the filename provided by the user was invalid, a message is displayed and the program finishes. Otherwise, a list of all the words in the filename that were found more than once
are displayed alongside the number of times they appeared. They are then followed by a list of all the words that appeared once, again in alphabetical order.
Afterwards, the user enters a lowest and highest number. If the highest number is less than or equal to the lowest number, a message is displayed. Otherwise,
the program displays all words that appeared for a number of times in the range of the high and low. Finally, all words that appeared more than once are displayed in
reverse alphabetical order.
 */
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct myNode{ //Contains all the pointers that are commonly used for the linked list.
    string data; //This string contains the word stored in a linked list node.
    int wordTotal; //This string stores the number of times a word appears in a text file.
    myNode *next; //This pointer will point to the next node in a linked list, or NULL if there is none.
    myNode *head; //This pointer will always indicate the first item in a linked list.
    myNode *tail; //This pointer will always indicate the final item in a linked list.
};

class laBlenk
{
    myNode *head, *tail, *newitem; //Creates class pointers for the nodes
    void reverseAlphabet(myNode *node);
    void isDuplicate(string word);
    void alphabetize();

public:
    laBlenk(); //Default constructor
    bool readText(string fileName);
    void displayStats();
    void displayStats(int low, int high);
    void displayStats(char letter);
};
int main()
{
    laBlenk myList; //Creates an instance of laBlenk class. Everyone loves Merc laBlenk.
    string fileName; //String for the filename
    int low, high; //Two ints that are used later

    cout << "Enter file name: ";
    cin >> fileName;

    if (myList.readText(fileName)) { //If the method returns true, continue with the program
        myList.displayStats(); //Print the words and their number of occurrences

        cout << "Enter low counter: ";
        cin >> low; //This will determine what the lowest frequency number displayed
        cout << "Enter high counter: ";
        cin >> high; //This will determine the highest frequency number displayed
        myList.displayStats(low, high); //Sends the low and high to be displayed

        myList.displayStats('R'); //Displays the words and occurrences in reverse alphabetical order
    } else //If the method returns false, end the program
        cout << "Error - problem reading file." << endl;

    return 0;
}
laBlenk::laBlenk()
//Default constructor
{
    head = NULL; //Sets head to NULL as there are no nodes yet
    tail = NULL; //Sets tail to NULL as there are no nodes yet
}
bool laBlenk::readText(string fileName)
{
    ifstream inFP;
    string word; //Variable for each word
    int nodeCounter = 0;
    inFP.open(fileName.c_str()); //Open file (needs to be a C string to open)
    if (inFP == 0) //If the filename is invalid returns false
    {
        return false;
    }
    else
    {
        while (inFP >> word) //While inFP is still reading words
        {
            if (word != "DONE") //Avoids reading in the DONE at the end of a file
            {
                int wordLength = word.length(); //Variable for length of word read
                for (int i = 0; i < wordLength; i++)
                {
                    word[i] = tolower(word[i]); //Changes every letter to lowercase
                }
                if (word.find_first_of("./,!?\"", 0) != -1) //Checks if any typical punctuation was found on the word
                {
                    while (word.find_first_of("./,!?\"", 0) != -1)
                    {
                        int position = word.find_first_of("./,!?\"", 0); //Finds the position the punctuation was located at
                        word.erase(position, 1); //Deletes the punctuation
                    }
                }
                newitem = new myNode; //Once the word has been checked, create a node in the linked list
                newitem -> data = word; //Stores the word into the node
                newitem -> next = NULL; //Pointer to next node is null as there is either no next node or this node needs to be checked for duplicate

                if (head == NULL)
                {
                    newitem -> wordTotal = 1; //If there is no nodes in the list yet, create one and set the word count to 1
                    head = newitem; //The head is now this node
                    tail = newitem; //As is the tail
                }
                else
                {
                    isDuplicate(word); //If the head is not null, send
                }

            }
        }
        inFP.close();

        return true;
    }



}

void laBlenk::isDuplicate(string word)
//Checks if a word is already in the linked list, if not calls for the node to be sorted
{
    myNode *cur; //Pointer that keeps track of the current node being looked at
    cur = head; //Starts off at the head
    while (cur != NULL) //Loops while there is still nodes to be checked
    {
        if (cur->data == word) //If the current node's stored word is a match, increase the word count of that node
        {
            cur->wordTotal += 1;
            cur = NULL; //Exit loop
        }
        else if (cur->next == NULL) //If all nodes were checked, the node must be sorted into list as a new node
        {
            cur = NULL; //Exit loop
            alphabetize(); //Call for the current node to be placed in list
        }
        else
        {
            cur = cur->next; //Increase position in linked list
        }
    }
}

void laBlenk::alphabetize()
//Sorts a node into a linked list so it remains in alphabetical order
{
    myNode *cur; //Keeps track of current pointer being looked at
    myNode *prev; //Keeps track of the last pointer to be looked at
    prev = NULL; //Previous is currently behind the head which does not exist
    cur = head; //Starting at head
    bool found = false; //Variable used to loop until a match is found

    while (cur != NULL && found == false) //While the nodes exist and the spot has not been found, check nodes for a place to put new node
    {
        if (newitem->data < cur->data) //If the item's string is in the alphabetical order when compared with current node, its spot has been found
        {
            found = true;
        }
        else //Otherwise move to next node, making previous the node that was being looked at this loop
        {
            prev = cur;
            cur = cur->next;
        }
    }

   if (prev != NULL) //Assuming not the first item, place the node into its spot
        {
        newitem->next = cur;
        prev->next = newitem;
        newitem->wordTotal = 1; //Create a count for this word
        }
   else //If it is the first item in the list, make the new node the head
    {
        newitem->next = head;
        newitem->wordTotal = 1; //Create count for this word
        head = newitem; //The new node is now the head
    }
}

void laBlenk::displayStats()
//Prints out words
{
    myNode *cur; //Keeps track of current node being looked at
    cur = head; //Start at head
    cout << "Words in alphabetical order:" << endl;
    cout << "Word" << setw(21) << "Count" << endl;
    cout << "=========================" << endl;
    while (cur != NULL) //While there are still nodes to print
    {
        if (cur->wordTotal > 1) //Print everything that has more than one word here
        {
            cout << left << setw(15) << cur->data << right << setw(10) << cur->wordTotal << endl; //Right justified numbering for appearance
        }
        cur = cur->next; //Move to next node
    }
    cur = head; //Reset to head to print counts of one
    cout << endl << "Words with count = 1" << endl;
    cout << "====================" << endl;
    while (cur != NULL)
    {
        if (cur->wordTotal == 1) //If the word count is one, print it
        {
            cout << cur->data << " ";
        }
        cur = cur->next;
    }
    cout << endl << endl;
}

void laBlenk::displayStats(int low, int high)
//Prints the words with counts between high and low
{
    myNode *cur; //Current pointer
    cur = head; //Begin at head
    int currentNum = high; //Variable to know which number to print
    if (low < high)
    {
        cout << endl << "Words in frequency order: " << endl;
        cout << "Word" << setw(21) << "Count" << endl;
        cout << "=========================" << endl;
        while (cur != NULL)
        {
            if (cur->wordTotal == currentNum) //Prints all words that match the current count needed
            {
                cout << left << setw(15) << cur->data << right << setw(10) << cur->wordTotal << endl;
            }
            if (cur->next == NULL && currentNum != low) //If the counter has not reached the lowest number yet and all nodes have been looked at, decrease by one
            {
                cur = head; //Start at the head again
                currentNum--;
            }
            else //Move to next node
            {
                cur = cur->next;
            }
        }
    }
    else //If something went wrong displaying the high-low, display message
    {
        cout << "Your 'high' number is lower than or equal to your 'low' number! Try again!" << endl;
    }
}

void laBlenk::displayStats(char letter)
//Prints header for reverse alphabet and calls on recursive method
{
    if (letter == 'R') //The parameter must be the letter R in order to work
    {
        cout << endl << "Words in reverse alphabetical order:" << endl;
        cout << "Word" << setw(21) << "Count" << endl;
        cout << "=========================" << endl;
        reverseAlphabet(head); //Call recursive method beginning at head of list
    }
    else //Warns user that method call in the code has the wrong char
    {
        cout << "Check the code, friend! This fuction's parameters should only take a capital 'R'!" << endl;
    }
}

void laBlenk::reverseAlphabet(myNode *pointer)
//Prints the words with a count greater than 1 in reverse alphabetical order
{
    if (pointer->next != NULL) //If the end of the list has not been reached
    {
        reverseAlphabet(pointer->next); //Send the next node to be processed
        if (pointer->wordTotal > 1) //After all nodes ahead have been printed, print this one assuming it is not one
        {
            cout << left << setw(15) << pointer->data << right << setw(10) << pointer->wordTotal << endl;
        }
    }
    else if (pointer->next == NULL) //If the end of the list has been reached, stop function call and print final node info if greater than one
    {
        if (pointer->wordTotal > 1)
        {
            cout << left << setw(15) << pointer->data << right << setw(10) << pointer->wordTotal << endl;
        }
    }

}

