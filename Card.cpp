#include <iostream>
#include "Card.h"
using namespace std;

int Card::getSuit() {
	return suit;
}

void Card::setSuit(int newSuit) {
	suit = newSuit;
}

bool Card::getState() {
	return state;
}
void Card::setState(bool newState) {
	state = newState;
}

int Card::getNumber() {
	return number;
}

void Card::setNumber(int newNum) {
	number = newNum;
}

Card::Card() {
	suit = 0;
	number = 0;
	state = true;
}
Card::Card(int newSuit, int newNumber, int newState) {
	suit = newSuit;
	number = newNumber;
	state = newState;
}

void Card::print() {
	switch (number) {
	case 11:
		cout << "J";
		break;
	case 12:
		cout << "Q";
		break;
	case 13:
		cout << "K";
		break;
	case 1:
		cout << "A";
		break;
	default:
		cout << number;
		break;
	}
}