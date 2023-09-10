//s1061460 hw5 Poker
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "s1061460_Poker.h"

using namespace std;

const string Card::suits[NumSuits] = { "Hearts", "Diamonds", "Clubs", "Spades" };
const string Card::faces[NumFaces] = { "Ace", "Deuce", "Three", "Four", "Five", "Six","Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King" };


string Card::toString() const
{
	string CardName = faces[face] + " of " + suits[suit];
	return CardName;
}

DeckOfCards::DeckOfCards()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			Card k(j, i);
			deck.push_back(k);					//新增元素至 vector 的尾端
		}
	}
}

void DeckOfCards::shuffle()
{
	srand(time(NULL));
	for (int i = 0; i < 52; i++) {

		int currentCard = rand() % 52;				//隨機挑選另一張牌
		swap(deck[currentCard], deck[i]);			//與currentCard所代表的牌交換
	}
	currentCard = 51;
}

void DeckOfCards::operator!()
{
	srand(time(NULL));
	for (int i = 0; i < 52; i++) {

		int currentCard = rand() % 52;				//隨機挑選另一張牌
		swap(deck[currentCard], deck[i]);			//與currentCard所代表的牌交換
	}
	currentCard = 51;
}

Card DeckOfCards::dealCard()
{
	Card c = deck[currentCard--];
	deck.pop_back();							//刪除 vector 最尾端的元素
	return c;
}

bool DeckOfCards::moreCards()
{
	return currentCard < deck.size();
}

void DeckOfCards::reset()
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 13; j++) {
			Card k(j, i);
			deck.push_back(k);					//新增元素至 vector 的尾端
		}
	}
	for (int i = 0; i < 52; i++) {

		int currentCard = rand() % 52;				//隨機挑選另一張牌
		swap(deck[currentCard], deck[i]);			//與currentCard所代表的牌交換
	}
	currentCard = 51;
}

Hand::Hand(DeckOfCards& deck)
	: faceCount(Card::NumFaces)
{
	for (int i = 0; i < 5; i++)
		hand.push_back(deck.dealCard());

	for (int i = 0; i < hand.size(); ++i)
		++faceCount[hand[i].getFace()];
}

void Hand::print() const
{
	cout << "Hand is:\n";
	for (int i = 0; i < hand.size(); i++)
		cout << hand[i].toString() << '\n';
	cout << endl;
}

ostream& operator<<(ostream& output, const Hand& hand)
{
	output << "Hand is:\n";
	for (int i = 0; i < 5; i++)
		output << hand.hand[i].toString() << '\n';
	return output;
}

void Hand::takeAgain(DeckOfCards& deck)
{

	for (int i = 0; i < 5; i++) {
		hand.pop_back();
	}
	for (int i = 0; i < 13; i++) {
		faceCount[i] = 0;
	}
	for (int i = 0; i < 5; i++) {
		hand.push_back(deck.dealCard());
	}
	for (int i = 0; i < hand.size(); i++) {
		faceCount[hand[i].getFace()]++;
	}
}

void Hand::operator+=(DeckOfCards& deck)
{
	for (int i = 0; i < 5; i++) {
		hand.pop_back();
	}
	for (int i = 0; i < 13; i++) {
		faceCount[i] = 0;
	}
	for (int i = 0; i < 5; i++) {
		hand.push_back(deck.dealCard());
	}
	for (int i = 0; i < hand.size(); i++) {
		faceCount[hand[i].getFace()]++;
	}
}

bool Hand::pair() const
{
	for (int i = 0; i < faceCount.size(); i++)
		if (faceCount[i] == 2)
			return true;
	return false;
}

bool Hand::twoPair() const
{
	bool foundOne = false;
	for (int i = 0; i < faceCount.size(); i++)
	{
		if (faceCount[i] == 2 && foundOne)
			return true;
		else if (faceCount[i] == 2)
			foundOne = true;
	}
	return false;
}

bool Hand::threeOfAKind() const
{
	for (int i = 0; i < faceCount.size(); i++)
		if (faceCount[i] == 3)
			return true;
	return false;
}

bool Hand::fourOfAKind() const
{
	for (int i = 0; i < faceCount.size(); i++)
		if (faceCount[i] == 4)
			return true;
	return false;
}

bool Hand::fullHouse() const
{
	bool foundOne = false;
	for (int i = 0; i < faceCount.size(); i++) {
		if (faceCount[i] == 3 && foundOne)
			return true;
		else if (faceCount[i] == 2)
			foundOne = true;
	}
	return false;
}

bool Hand::flush() const
{
	int suit = hand[0].getSuit();
	for (int i = 1; i < hand.size(); i++)
		if (hand[i].getSuit() != suit)
			return false;
	return true;
}

bool Hand::straight() const
{
	vector< int > tmp = faceCount;
	tmp.push_back(tmp[0]); 
	if (tmp[0] == 1 && tmp[1] == 1 && tmp[2] == 1 && tmp[3] == 1 && tmp[4] == 1)
		return true;
	int i = 1;
	while (i < tmp.size() && tmp[i] == 0)
		++i;
	int start = i;
	while (i < tmp.size() && tmp[i] == 1)
		++i;
	return i == start + 5;
}