#ifndef DECK_H
#define DECK_H
#include "Card.h"
class Deck {
private:
	int numberOfCards;
public:
	Deck(int numberOfCards);
	Card* cards;
	void Shuffle();
	Card* Deal(int amountToDeal);
	void print();
};

#endif