// BLACKJACK.cpp : Defines the entry point for the console application.
#include "stdafx.h"
#include "Deck.h"
#include "Card.h"
#include "BLACKJACK.h"
#include <iostream>
using namespace std;

BlackJack::BlackJack(int deckSize) {
	deck = new Deck(260);
	deck->Shuffle();
	playerHand = new Card[10];
	dealerHand = new Card[10];
}

STATUS BlackJack::gameStatusCheck() {
	if (getHandSum(playerHand, playerCardAmount) > 21)
		return LOSE;
	else
		return CONTINUE;
}

void BlackJack::play() {
	STATUS gameStatus = CONTINUE;
	cout << "Bank Roll: $" << bank << endl;
	bank -= 100;
	cout << "You bet $100. You have $" << bank << " left." << endl;
	dealCards(playerHand, 2, &playerCardAmount);
	dealCards(dealerHand, 2, &dealerCardAmount);
	while (gameStatus == CONTINUE) {
		cout << "Dealer shows a ";
		printHand(dealerHand, 1);
		cout << "Your hand: ";
		printHand(playerHand, playerCardAmount);
		char playerChoice = getInput();
		switch (playerChoice) {
		case 'H':
		case 'h':
			cout << "playerCardamount before: " << playerCardAmount << endl;
			dealCards(playerHand, 1, &playerCardAmount);
			cout << "Your hand: ";
			printHand(playerHand, playerCardAmount);
			cout << "Player card amount after: " << playerCardAmount << endl;
			gameStatus = gameStatusCheck();
			break;
		case 's':
		case 'S':
			while (getHandSum(dealerHand, dealerCardAmount) < 17)
				dealCards(dealerHand, 1, &dealerCardAmount);
			cout << "Dealer's hand: ";
			printHand(dealerHand, dealerCardAmount);
			if (getHandSum(dealerHand, dealerCardAmount) > 21) {
				cout << "Dealer Busts\n";
				gameStatus = WIN;
			}
			else {
				gameStatus = (getHandSum(dealerHand, dealerCardAmount) > getHandSum(playerHand, playerCardAmount) ? LOSE : WIN);
				if (gameStatus == WIN) {
					bank += 200;
					cout << "You win $200!!!!\n";
				}
				else
					cout << "Dealer Wins";
			}
			break;
		}
	}
	play();
	
}

void BlackJack::dealCards(Card* hand, int amountToDeal, int *cardsInHand) {
	Card* dealtCards = deck->Deal(amountToDeal);
	int count = 0;
	
	for (int i = *cardsInHand; i < amountToDeal; i++) {
		hand[i] = dealtCards[count];
		count++;
		cardsInHand++;
	}
	cout << "Cardsinhand: " << *cardsInHand << endl;
}

char BlackJack::getInput() {
	char playerChoice;
	if (getHandSum(playerHand, playerCardAmount) == 10 || getHandSum(playerHand, playerCardAmount == 11))
		cout << "Your choices are (S)tand, (H)it, ($)how, (Q)uit, **(D)ouble Down**";
	else
		cout << "Your choices are (S)tand, (H)it, ($)how, (Q)uit";
	cin >> playerChoice;
	return playerChoice;
}

int BlackJack::getHandSum(Card* hand, int amountOfCards) {
	int sum = 0;
	for (int i = 0; i < amountOfCards; i++) {
		sum += hand[i].getNumber();
	}
	return sum;
}

void BlackJack::printHand(Card* handToPrint, int numberOfCards) {
	for (int i = 0; i < numberOfCards; i++) {
		handToPrint[i].print();
		if (i != numberOfCards - 1)
			cout << ", ";
	}
	cout << endl;
}

/*
using namespace std;

enum STATUS : int { CONTINUE, WIN, LOSE, PUSH };

void printHand(Card* handToPrint, int numberOfCards) {
	for (int i = 0; i < numberOfCards; i++) {
		handToPrint[i].print();
		if (i != numberOfCards - 1)
			cout << ", ";
	}
}

STATUS gameStatusCheck(Card* playerHand, Card* dealerHand, int playerCards, int dealerCards) {
	int playerHandTotal = 0;
	int dealerHandTotal = 0;
	for (int i = 0; i < playerCards; i++)
		//Get player number
		playerHandTotal += playerHand[i].getNumber();
	for (int i = 0; i < dealerCards; i++)
		//Get dealer number
		dealerHandTotal += dealerHand[i].getNumber();
	//Status checks
	if (playerHandTotal < 21 && dealerHandTotal < 21)
		//If game should continue
		return CONTINUE;
	else if (playerHandTotal > 21)
		//Player busts
		return LOSE;
	else if (dealerHandTotal > 21)
		return WIN;

	
		
}

int main()
{
	STATUS gameStatus = CONTINUE;
	int bank = 1000;
	Deck Deck(260);
	Deck.Shuffle();
	Card* DealerHand = new Card[10];
	int playerCardAmount = 0;
	int dealerCardAmount = 0;
	int totalCardAmount = 0;
	Card* PlayerHand = new Card[10];
	Card* CardsDealt = Deck.Deal(20); 
	for (int i = 0; i < 2; i++)
	{
		//initial 2 cards
		DealerHand[i] = CardsDealt[i];
		dealerCardAmount++;
		PlayerHand[i] = CardsDealt[i + 1];
		playerCardAmount++;
		totalCardAmount = playerCardAmount + dealerCardAmount;
	}
	
	cout << "Bank Roll: $" << bank << endl;
	bank -= 100;
	cout << "You bet $100. You have $" << bank << " left.\n";
	while (gameStatus == CONTINUE)
	{
		char input;
		cout << "Dealer shows a ";
		printHand(DealerHand, 1);
		cout << endl;
		cout << "Your hand: ";
		printHand(PlayerHand, playerCardAmount);
		cout << "(S)tand, (H)it: ";
		cin >> input;
		switch (input) {
		case 'h':
		case 'H':
			PlayerHand[playerCardAmount] = CardsDealt[totalCardAmount];
			totalCardAmount++;
			playerCardAmount++;
			gameStatus = gameStatusCheck();
			break;

		case 's':
		case 'S':

		}
	}

    return 0;
}
*/

