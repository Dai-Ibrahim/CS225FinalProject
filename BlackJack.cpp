#include "Deck.h"
#include "Card.h"
#include "BlackJack.h"
#include <iostream>
using namespace std;

//Constructor initializes hands and shuffles deck
BlackJack::BlackJack(int deckSize) {
	deck = new Deck(260);
	deck->Shuffle();
	playerHand = new Card[10];
	dealerHand = new Card[10];
}

//Returns false if player does not have enough money to play
bool BlackJack::bet() {
	cout << "Bank roll: $" << bank << endl;
	bank -= 100;
	if (bank < 0)
		return false;
	else {
		cout << "You bet $100. You have $" << bank << " left.\n";
		return true;
	}
}

//The start of every new hand
void BlackJack::start() {
	if (bet() == true) {
		//Start the hand if the player was able to bet
		dealInitialCards();
		play();
	}
	else
		cout << "You ran out of money.";
}

//Deals first 2 cards to player and dealer
void BlackJack::dealInitialCards() {
	for (int i = 0; i < 2; i++) {
		playerHand[i] = *(deck->Deal(1));
		dealerHand[i] = *(deck->Deal(1));
		playerCardAmount++;
		dealerCardAmount++;
	}
}

//Empties the player and dealer hands
void BlackJack::reset() {
	playerCardAmount = 0;
	dealerCardAmount = 0;
}

//Winning message and adjust the player bank balance
void BlackJack::playerWin(int amount) {
	cout << "You win $" << amount << endl;
	bank += amount;
}

//Adds card from deck to player's hand. Handles logic
void BlackJack::hit() {
	playerHand[playerCardAmount] = *(deck->Deal(1));
	cout << "You draw a ";
	playerHand[playerCardAmount].print();
	playerCardAmount++;
	if (getHandSum(playerHand, playerCardAmount) > 21) {
		//Start a new hand if player busts
		cout << "\nYou bust.\n";
		reset();
		start();
	} else {
		//continue the hand
		cout << endl;
		play();
	}
}

//Outputs push message and gives back player's bet
void BlackJack::push() {
	cout << "Game is a push. You got your initial bet back.\n";
	bank += 100;
}

//Handles stand logic
void BlackJack::stand(int betAmount) {
	while (getHandSum(dealerHand, dealerCardAmount) < 17) {
		//Dealer draws cards until sum of at least 17
		dealerHand[dealerCardAmount] = *(deck->Deal(1));
		dealerCardAmount++;
	}
	cout << "Dealer's hand: ";
	printHand(dealerHand, dealerCardAmount);
	if (getHandSum(dealerHand, dealerCardAmount) > 21) {
		//Player wins if dealer busts
		cout << "Dealer busts\n";
		playerWin(betAmount);
		reset();
		start();
	}
	else if (getHandSum(dealerHand, dealerCardAmount) > getHandSum(playerHand, playerCardAmount)) {
		//If dealer has better cards
		cout << "Dealer wins.\n";
		reset();
		start();
	}
	else if (getHandSum(dealerHand, dealerCardAmount) < getHandSum(playerHand, playerCardAmount)) {
		//If player has better cards
		playerWin(betAmount);
		reset();
		start();
	}
	else {
		//If game is a push
		push();
		reset();
		start();
	}
}

//If the player gets 21 on first 2 cards
void BlackJack::checkInitialCards() {
	int dealerValue = getHandSum(dealerHand, dealerCardAmount);
	int playerValue = getHandSum(playerHand, playerCardAmount);
	if (playerValue == 21 && dealerValue == 21) {
		//If game is a push
		push();
		reset();
		start();
	}
	else if (playerValue == 21) {
		//If player has blackjack
		playerWin(250);
		reset();
		start();
	}
}

//Handles double down logic
void BlackJack::doubleDown() {
	if (bank - 50 < 0) {
		//If the player can't double down, start the hand over
		cout << "You don't have enough money to double down, start the hand over.\n";
		play();
	}
	else {
		//The player draws a card and then stands for an increased bet return
		bank -= 50;
		cout << "You bet an additional $50. You now have $" << bank << endl;
		playerHand[playerCardAmount] = *(deck->Deal(1));
		cout << "You draw a ";
		playerHand[playerCardAmount].print();
		playerCardAmount++;
		cout << endl;
		if (getHandSum(playerHand, playerCardAmount) > 21) {
			//Start a new hand if player busts
			cout << "\nYou bust.\n";
			reset();
			start();
		} else
			stand(300);
	}
}

//Handles player input for hitting/standing etc
void BlackJack::play() {
	cout << "\nDealer shows a ";
	dealerHand[0].print();
	cout << endl << "Your hand: ";
	printHand(playerHand, playerCardAmount);
	if (playerCardAmount == 2)
		checkInitialCards();
	char input = getInput();
	switch (input) {
	case 'H':
	case 'h':
		hit();
		break;
	case 'S':
	case 's':
		stand(200);
		break;
	case '$':
		deck->print();
		play();
		break;
	case 'q':
	case 'Q':
		exit(0);
		break;
	case 'd':
	case 'D':
		doubleDown();
		break;
	default:
		cout << "Invalid character. Start the hand over again.\n";
		play();
		break;
	} //End switch

}

//Gets player's decision for next move
char BlackJack::getInput() {
	char playerChoice;
	int sum = getHandSum(playerHand, playerCardAmount);
	if ((sum == 10 || sum == 11) && playerCardAmount == 2)
		cout << "Your choices are (S)tand, (H)it, ($)how, (Q)uit, **(D)ouble Down**  ";
	else
		cout << "Your choices are (S)tand, (H)it, ($)how, (Q)uit:  ";
	cin >> playerChoice;
	if ((playerChoice == 'd' && (sum < 10 || sum > 11)) || (playerChoice == 'D' && (sum < 10 || sum > 11)))
		//If player tries to double down when its not allowed, set it to invalid
		playerChoice = 'x';
	return playerChoice;
}

//Calculates what a hand is worth, decides best value for aces
int BlackJack::getHandSum(Card* hand, int amountOfCards) {
	int sum = 0;
	int aceCount = 0;
	for (int i = 0; i < amountOfCards; i++) {
		if (hand[i].getNumber() == 1)
			//If a card is an ace, remember it for later
			aceCount++;
		else if (hand[i].getNumber() >= 11)
			//If it is a face card it is worth 10
			sum += 10;
		else
			//Otherwise it is worth its number
			sum += hand[i].getNumber();
	}
	for (int i = 0; i < aceCount; i++) {
		//For every ace in the hand
		if ((sum + 11) <= 21)
			//If 11 can be added, do so
			sum += 11;
		else
			//Otherwise ace is worth 1
			sum += 1;
	}
	return sum;
}

//Prints the number values of a hand
void BlackJack::printHand(Card* handToPrint, int numberOfCards) {
	for (int i = 0; i < numberOfCards; i++) {
		//print each card in a list followed by a comma
		handToPrint[i].print();
		if (i != numberOfCards - 1)
			cout << ", ";
	}
	cout << endl;
}
