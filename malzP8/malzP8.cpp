/*
Benjamin Malz
malzP8.cpp (Assignment 8)
Purpose: This program simulates one game of the card game 'War' between two user-defined names.
Input: The user inputs two names, one for player one and another for player two. After every turn the user must press enter to simulate the next turn. At the very end the user must type a character
before hitting enter. This is so that if the user simply holds enter to quickly speed through the game, they will not instantly close the program before they can look at the results.
Output: The program displays a header for every hand that shows what number hand is being played, the players' names and the card each player played. Whoever wins the hand will have a message indicating
their victory displayed under their card. If both players have the same card value, the output will declare that war occurred and print all cards used on both sides as well as the winner. At the end of
every hand, the amount of cards each player has will be shown. When a player wins, a message will be displayed indicating that they won and why they won. (Getting all cards is not the only way to end the game...)
 */

#include<iostream>
#include<cstdlib>
#include<assert.h>
#include<time.h>
#include<queue>
#include<iomanip>
#include<sstream>
using namespace std;

struct card {
   int value;	// point value of card (2-14; Ace is high)
   string suit;	// Hearts, Diamonds, Clubs, Spades
   string face;	// Jack, Queen, King, or Ace (or none)
   bool dealt;	// if this card has been dealt
};

class gameOfWar
{
string player1;
string player2;
int handCount;
bool gameOver;
queue <card> playerOneHand;
queue <card> playerTwoHand;
queue <card> warPile;
void printCards();
void warRound();
public:
    gameOfWar();
    void playGame();
};

gameOfWar::gameOfWar()
{
    gameOver = false;
    handCount = 1;
}

class deckOfCards {
   card deck [52];   	// note: no constant here because things are hardcoded for a standard 52 card deck
   int numberDealt; 	// number of cards dealt so far

public:
   deckOfCards ();
   card dealCard ();
};

deckOfCards :: deckOfCards () {
/*
 *  Constructor.
 *  Set up a standard set of 52 cards.
 */
   int i;

   numberDealt = 0;

   for (i = 0; i < 52; i++) {
      deck[i].dealt = false;
      if (i < 13) {
         deck[i].value = i+2;
         deck[i].suit = "Hearts";
      } else if (i < 26) {
         deck[i].value = i-11;
         deck[i].suit = "Diamonds";
      } else if (i < 39) {
         deck[i].value = i-24;
         deck[i].suit = "Clubs";
      } else {
         deck[i].value = i-37;
         deck[i].suit = "Spades";
      }

      if (deck[i].value == 11)
         deck[i].face = "Jack";
      else if (deck[i].value == 12)
         deck[i].face = "Queen";
      else if (deck[i].value == 13)
         deck[i].face = "King";
      else if (deck[i].value == 14)
         deck[i].face = "Ace";
      else
         deck[i].face = "";
   }
}

card deckOfCards :: dealCard () {
/*
 * Deal one card from deck.
 * Precondition: Deck has been created
 * Postcondition: Returns a random card from the deck
 */

   int index;

   assert (numberDealt < 52);
   srand(time(NULL));
   index = rand () % 52;	// random number in range 0-51
   while (deck[index].dealt) {
      index = rand () % 52;
   }
   deck[index].dealt = true;
   numberDealt++;
   return deck[index];
}

void gameOfWar::playGame()
{
    deckOfCards game;
    char contInput;
    cout << "Enter Player One's name: ";
    cin >> player1;
    cout << "Enter Player Two's name: ";
    cin >> player2;
    cin.get(contInput);

    for (int i = 0; i < 26 ; i++)
    {
        playerOneHand.push(game.dealCard());
        playerTwoHand.push(game.dealCard());
    }

    while (!gameOver)
    {
        contInput = ' ';
        cout << "Hand: " << handCount << endl << endl;
        cout << left << setw(32) << player1 << right <<  player2 << endl;
        cout << "------------------------------------------------" << endl;
        printCards();
        if (playerOneHand.front().value > playerTwoHand.front().value)
        {
            playerOneHand.push(playerTwoHand.front());
            playerOneHand.push(playerOneHand.front());
            playerTwoHand.pop();
            playerOneHand.pop();
            cout << "Wins hand!" << endl << endl;
            cout << player1 << " now has " << playerOneHand.size() << " cards." << endl;
            cout << player2 << " now has " << playerTwoHand.size() << " cards." << endl << endl;
        }
        else if (playerTwoHand.front().value > playerOneHand.front().value)
        {
            playerTwoHand.push(playerOneHand.front());
            playerTwoHand.push(playerTwoHand.front());
            playerTwoHand.pop();
            playerOneHand.pop();
            cout << right << setw(42) << "Wins hand!" << endl << endl;
            cout << player1 << " now has " << playerOneHand.size() << " cards." << endl;
            cout << player2 << " now has " << playerTwoHand.size() << " cards." << endl << endl;
        }
        else
        {
            cout << right << setw(24) << "WAR!" << endl;
            warPile.push(playerOneHand.front());
            playerOneHand.pop();
            warPile.push(playerTwoHand.front());
            playerTwoHand.pop();
            if (playerOneHand.size() < 2)
            {
                cout << player1 << " doesn't have enough cards for war. " << player2 << " wins!" << endl;
                gameOver = true;
            }
            else if (playerTwoHand.size() < 2)
            {
                cout << player2 << " doesn't have enough cards for war. " << player1 << " wins!" << endl;
                gameOver = true;
            }
            else
                warRound();
        }


        cout << "Press <enter> to continue..." << endl;
        handCount++;
        if (playerOneHand.size() == 52)
        {
            cout << player1 << " has all cards and has won the game!" << endl;
            gameOver = true;
        }
        else if (playerTwoHand.size() == 52)
        {
            cout << player2 << " has all cards and has won the game!" << endl;
            gameOver = true;
        }
        while(contInput != '\n')
            cin.get(contInput); //Otherwise every character input before enter would advance the game one hand

    }
    cout << "The game is over. Please type any character and then press <enter> to exit." << endl; //So that if you hold enter you won't end the program accidentally before seeing the results
    cin >> contInput;
}

void gameOfWar::warRound()
{
    bool isWar = true;
    while (isWar)
        {
            warPile.push(playerOneHand.front());
            playerOneHand.pop();
            warPile.push(playerTwoHand.front());
            playerTwoHand.pop();
            cout << "Secret card" << setw(32) << "Secret card" << endl;
            printCards();
            if (playerOneHand.front().value > playerTwoHand.front().value)
            {
                isWar = false;
                playerOneHand.push(playerTwoHand.front());
                playerOneHand.push(playerOneHand.front());
                playerTwoHand.pop();
                playerOneHand.pop();
                while (warPile.size() > 0)
                {
                    playerOneHand.push(warPile.front());
                    warPile.pop();
                }

                cout << "Wins hand!" << endl << endl;
                cout << player1 << " now has " << playerOneHand.size() << " cards." << endl;
                cout << player2 << " now has " << playerTwoHand.size() << " cards." << endl << endl;
            }
            else if (playerTwoHand.front().value > playerOneHand.front().value)
            {
                isWar = false;
                playerTwoHand.push(playerOneHand.front());
                playerTwoHand.push(playerTwoHand.front());
                playerTwoHand.pop();
                playerOneHand.pop();
                while (warPile.size() > 0)
                {
                    playerTwoHand.push(warPile.front());
                    warPile.pop();
                }
                cout << right << setw(42) << "Wins hand!" << endl << endl;
                cout << player1 << " now has " << playerOneHand.size() << " cards." << endl;
                cout << player2 << " now has " << playerTwoHand.size() << " cards." << endl << endl;
            }
            else
            {
                warPile.push(playerOneHand.front());
                playerOneHand.pop();
                warPile.push(playerTwoHand.front());
                playerTwoHand.pop();
                if (playerOneHand.size() < 2)
                {
                    cout << player1 << " doesn't have enough cards to continue war. " << player2 << " wins!" << endl;
                    gameOver = true;
                }
                else if (playerTwoHand.size() < 2)
                {
                    cout << player2 << " doesn't have enough cards to continue war. " << player1 << " wins!" << endl;
                    gameOver = true;
                }
            }
        }
}

void gameOfWar::printCards()
{
    stringstream p1Card, p2Card;

    if (playerOneHand.front().value < 11)
        p1Card << playerOneHand.front().value << " of " << playerOneHand.front().suit;
    else if (playerOneHand.front().value >= 11)
        p1Card << playerOneHand.front().face << " of " << playerOneHand.front().suit;
    string p1CardString = p1Card.str();

    if (playerTwoHand.front().value < 11)
        p2Card << playerTwoHand.front().value << " of " << playerTwoHand.front().suit;
    else if (playerTwoHand.front().value >= 11)
        p2Card << playerTwoHand.front().face << " of " << playerTwoHand.front().suit;
    string p2CardString = p2Card.str();

    cout << left << setw(32) << p1CardString << p2CardString << endl;
}
int main()
{
    gameOfWar gameSession;
    gameSession.playGame();
    return 0;
}
