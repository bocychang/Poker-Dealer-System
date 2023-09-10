//s1061460 hw5 Poker
#include <iostream>
#include <iomanip>
#include "s1061460_Poker.h" 
using namespace std;

bool PressEnterToContinue(string mesg = "Press ENTER to continue... ")
{
	int c;
	cout << mesg << endl;
	cout.flush();
	do c = getchar(); while ((c != '\n') && (c != EOF));
	return true;
}

int main()
{
	cout << "I am s1061460" << endl;
	DeckOfCards myDeckOfCards;
	//myDeckOfCards.shuffle(); // place Cards in random order

	!myDeckOfCards;			//Use operator! to perform shuffle()

	// ISSUEs 01 - print all 52 Cards in the order in which they are dealt
	for (int i = 1; myDeckOfCards.moreCards(); i++)
	{
		// deal and display a Card
		cout << left << setw(19) << myDeckOfCards.dealCard().toString();

		if (i % 5 == 0) // output newline every 5 cards
			cout << endl;
	} // end for

	cout << endl << "--------------------------------------" << endl;
	myDeckOfCards.reset(); // place Cards in random order (reset current card #)
	Hand hand(myDeckOfCards);

	// ISSUEs 02 - deal a hand from the deck
	do
	{
		//hand.print(); // display hand

		cout << hand << endl;					//Use operator<< to perform print()

		// check for each type of hand by decreasing ranking
		if (hand.fourOfAKind())
			cout << "Hand contains four of a kind" << endl;
		else if (hand.flush())
			cout << "Hand contains a flush" << endl;
		else if (hand.straight())
			cout << "Hand contains a straight" << endl;
		else if (hand.fullHouse())
			cout << "Hand contains a fullHouse" << endl;
		else if (hand.threeOfAKind())
			cout << "Hand contains three of a kind" << endl;
		else if (hand.twoPair())
			cout << "Hand contains two pairs" << endl;
		else if (hand.pair())
			cout << "Hand contains a pair" << endl;
		else
			cout << "Too bad, you get nothing..." << endl;

		if (myDeckOfCards.getcurrentCard() >= 5) {
			//hand.takeAgain(myDeckOfCards);
			hand += myDeckOfCards;			//Use operator+= to take new cards
		}
		else
			break;
	} while (PressEnterToContinue() && myDeckOfCards.moreCards());

	PressEnterToContinue("Press ENTER to endgame... ");
} // end main