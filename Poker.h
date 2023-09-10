//s1061460 hw5 Poker
#ifndef DECKCARD_H
#define DECKCARD_H

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Card
{
public:
	static const size_t NumFaces = 13;
	static const size_t NumSuits = 4;
	Card(int f, int s): face(f), suit(s) {}
	string toString() const;
	int getFace() const
	{
		return face;
	}
	int getSuit() const
	{
		return suit;
	}
private:
	int face, suit;
	static const string suits[NumSuits];
	static const string faces[NumFaces];
};

class DeckOfCards
{
private:
	vector<Card> deck;
	int currentCard;

public:
	int getcurrentCard() const
	{
		return currentCard;
	}
	DeckOfCards();
	void shuffle();
	void operator!();
	Card dealCard();
	bool moreCards();
	void reset();
};

class Hand
{
	friend ostream& operator<<(ostream&, const Hand&);
private:
	vector<Card> hand;
	vector< int > faceCount;
public:
	Hand(DeckOfCards& deck);
	void print() const;
	void takeAgain(DeckOfCards& deck);
	void operator+=(DeckOfCards&);
	bool pair() const;
	bool twoPair() const;
	bool threeOfAKind() const;
	bool fourOfAKind() const;
	bool fullHouse() const;
	bool flush() const;
	bool straight() const;
};

#endif // DECKCARD_H

