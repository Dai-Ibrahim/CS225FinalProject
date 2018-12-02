#include "Deck.h"
#include <iostream>
#include <ctime>
using namespace std;

//Constructor Initializes Deck and seeds rand
Deck::Deck(int cardsInDeck) {
	cards = new Card[cardsInDeck];
	numberOfCards = cardsInDeck;
	srand(time(0));
}

//Gives random suit and number values to every card
void Deck::Shuffle() {
	for (int i = 0; i < numberOfCards; i++) {
		cards[i].setNumber(rand() % 13 + 1);
		cards[i].setSuit(rand() % 4 + 1);
	}
}

//Deals cards from deck and removes them
Card* Deck::Deal(int amountToDeal) {
	Card* listToReturn = new Card[amountToDeal];
	if (numberOfCards - amountToDeal < 0) {
		cout << "Deck has too few cards to deal that much!\n";
		return nullptr;
	}
	for (int i = 0; i < amountToDeal; i++) {
		//populate the array to return
		listToReturn[i] = cards[numberOfCards - 1 - i];
	}
	numberOfCards -= amountToDeal;
	return listToReturn;
}

//Prints the contents of the deck in rows of 20
void Deck::print() {
	cout << endl;
	for (int i = 0; i < numberOfCards; i++) {
		if (i % 20 == 0 && i != 0)
			cout << '\n';
		cards[i].print();
		cout << " ";
	}
	cout << endl;
}
