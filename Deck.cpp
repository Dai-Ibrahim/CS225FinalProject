#include "Deck.h"
#include <iostream>
using namespace std;

Deck::Deck(int cardsInDeck) {
	cards = new Card[cardsInDeck];
	numberOfCards = cardsInDeck;
}

void Deck::Shuffle() {
	for (int i = 0; i < numberOfCards; i++) {
		cards[i].setNumber(rand() % 13 + 1);
		cards[i].setSuit(rand() % 4 + 1);
	}
}

Card* Deck::Deal(int amountToDeal) {
	Card* listToReturn = new Card[amountToDeal];
	if (numberOfCards - amountToDeal < 0) {
		cout << "Deck has too few cards to deal that much!\n";
		return nullptr;
	}
	for (int i = 0; i < amountToDeal; i++) {
		listToReturn[i] = cards[numberOfCards - 1 - i];
	}
	numberOfCards -= amountToDeal;
	return listToReturn;
}

void Deck::print() {
	for (int i = 0; i < numberOfCards; i++) {
		if (i % 10 == 0 && i != 0)
			cout << '\n';
		cards[i].print();
		cout << " ";
		
	}
}
//TEST CONDITION SAMPLES FUNCTIONS
//int main() {
//	Deck d(52);
//	d.Shuffle();
//	d.print();
//	cout << "\n\n\nNOW DEAL TEST\n";
//	Card *dealt = d.Deal(52);
//	d.print();
//	cout << "\nDEALT CARDS: ";
//	dealt[0].print();
//	dealt[1].print();
//	dealt[2].print();
//	dealt[3].print();
//	return 0;
//}