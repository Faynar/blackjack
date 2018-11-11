#pragma once
#include "Hand.h"
#include <iostream>
#include <string>

Hand::Hand() // default constructor
{
	HandLength = 0;
	AcesTotal = 0;
}

int Hand::GetHandLength() const
{
	return HandLength;
}

int Hand::GetAcesTotal() const
{
	return AcesTotal;
}

//Prints nth card in the hand, counting from 0
void Hand::PrintNthCard(int ordinal)
{
	PrintCardAsString(CardsInHand[ordinal]);
	return;
}

//Adds a card to the deck, increasing the Length and Aces variables as needed
void Hand::AddCard(Card TargetCard)
{
	CardsInHand[HandLength] = TargetCard;
	HandLength++;
	if (TargetCard.Face == CardFace::ace) { AcesTotal++; }
	return;
}

// Reads out the cards in the hand
void Hand::ReadOutHand(std::string HandOwner)
{
	std::cout << HandOwner << "'s hand contains:\n";
	for (int i = 0; i < HandLength; i++) {
		PrintCardAsString(CardsInHand[i]);
		std::cout << std::endl;
	}
	return;
}

void Hand::PrintCardAsString(Card TargetCard)
{
	std::string CardsFace = "";
	std::string CardsSuit = "";

	// switch statement to get a string for card face
	switch (TargetCard.Face) {
	case CardFace::joker: CardsFace = "joker";
		break;
	case CardFace::ace: CardsFace = "ace";
		break;
	case CardFace::two: CardsFace = "two";
		break;
	case CardFace::three: CardsFace = "three";
		break;
	case CardFace::four: CardsFace = "four";
		break;
	case CardFace::five: CardsFace = "five";
		break;
	case CardFace::six: CardsFace = "six";
		break;
	case CardFace::seven: CardsFace = "seven";
		break;
	case CardFace::eight: CardsFace = "eight";
		break;
	case CardFace::nine: CardsFace = "nine";
		break;
	case CardFace::ten: CardsFace = "ten";
		break;
	case CardFace::jack: CardsFace = "jack";
		break;
	case CardFace::queen: CardsFace = "queen";
		break;
	case CardFace::king: CardsFace = "king";
		break;
	}

	// switch statement to get a string for card suit
	switch (TargetCard.Suit) {
	case CardSuit::joker: CardsSuit = "joker";
		break;
	case CardSuit::hearts: CardsSuit = "hearts";
		break;
	case CardSuit::spades: CardsSuit = "spades";
		break;
	case CardSuit::diamonds: CardsSuit = "diamonds";
		break;
	case CardSuit::clubs: CardsSuit = "clubs";
		break;
	}

	// If the card's a joker say that
	if (CardsFace == "joker" || CardsSuit == "joker") {
		std::cout << "a joker";
		return;
	}
	// Change grammar if card value starts with a value
	if (CardsFace[0] == 'a' || CardsFace[0] == 'e') {
		std::cout << "an ";
	}
	else { std::cout << "a "; }
	std::cout << CardsFace << " of " << CardsSuit;

	return;
}

// Returns point value for card, aces return 11
int Hand::PointsForCard(Card TargetCard)
{
	if (TargetCard.Face == CardFace::ace) { return 11; }
	else if (TargetCard.Face == CardFace::two) { return 2; }
	else if (TargetCard.Face == CardFace::three) { return 3; }
	else if (TargetCard.Face == CardFace::four) { return 4; }
	else if (TargetCard.Face == CardFace::five) { return 5; }
	else if (TargetCard.Face == CardFace::six) { return 6; }
	else if (TargetCard.Face == CardFace::seven) { return 7; }
	else if (TargetCard.Face == CardFace::eight) { return 8; }
	else if (TargetCard.Face == CardFace::nine) { return 9; }
	else if (TargetCard.Face == CardFace::ten) { return 10; }
	else if (TargetCard.Face == CardFace::jack) { return 10; }
	else if (TargetCard.Face == CardFace::queen) { return 10; }
	else if (TargetCard.Face == CardFace::king) { return 10; }
	return 0;// this would be a joker
}

// Returns points for the hand
int Hand::GetPointsInHand()
{
	int HandTotal = 0;
	int AceTally = 0;
	// starting with the cards in the players hand
	// for each card in the hand
	for (int i = 0; i < HandLength; i++) {
		// take the face of the card as a string
		int CardPoints = PointsForCard(CardsInHand[i]);
		if (CardPoints == 11) { AceTally += 1; } // if the card's an ace increase the ace tally
		HandTotal += CardPoints;
	}
	// if the total is over 21
	if (HandTotal > 21) {
		// if they have no aces return the hand total
		if (AceTally == 0) { return HandTotal; }
		else { // if they DO have aces
			   // while the total is still over 21 and there are still aces using high values
			while (HandTotal > 21 && AceTally > 0) {
				// use the low value for one more ace
				HandTotal -= 10;
				// reduce the number of aces available to change
				AceTally -= 1;
			}
		}
	}
	return HandTotal;
}

