#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "Deck.h"
#include "Card.h"

class BlackJack {
public:
	Deck* deck;
	BlackJack(int deckSize);
	void start();
private:
	
	int bank = 1000;
	int playerCardAmount = 0;
	int dealerCardAmount = 0;
	Card* playerHand;
	Card* dealerHand;
	void play();
	void checkInitialCards();
	void push();
	void playerWin(int amount);
	void reset();
	void hit();
	void stand(int betAmount);
	void doubleDown();
	void dealInitialCards();
	bool bet();
	int getHandSum(Card*, int);
	void printHand(Card*, int);
	char getInput();
};
#endif