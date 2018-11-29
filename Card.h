#ifndef CARD_H
#define CARD_H

class Card {
public:
	Card(int newSuit, int newNumber, int newState);
	Card();
	void print();

	int getSuit();
	void setSuit(int newSuit);

	bool getState();
	void setState(bool newState);

	int getNumber();
	void setNumber(int newNum);
private:
	int suit;
	int number;
	bool state;

};
#endif
