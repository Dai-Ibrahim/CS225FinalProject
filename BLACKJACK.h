#pragma once
#include "stdafx.h"
#include "Deck.h"
#include "Card.h"
enum CHOICE : char { HIT = 'h', STAND = 's', SHOW = '?', DOUBLEDOWN = 'd', QUIT = 'q' };
enum STATUS : int { CONTINUE, PUSH, WIN, LOSE };

class BlackJack {
public:
	Deck* deck;
	BlackJack(int deckSize);
	void play ();
private:
	STATUS gameStatusCheck();
	int getHandSum(Card*, int);
	void printHand(Card*, int);
	int playerCardAmount = 0;
	int dealerCardAmount = 0;
	void dealCards(Card*, int, int*);
	char getInput();
	int bank = 1000;
	Card* playerHand;
	Card* dealerHand;
	
	
};