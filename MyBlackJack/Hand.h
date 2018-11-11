#pragma once
#include <iostream>
#include <string>

enum class RoundResults {
	Tie,
	PlayerWin,
	PlayerLoss
};

enum class CardFace {
	joker,
	ace,
	two,
	three,
	four,
	five,
	six,
	seven,
	eight,
	nine,
	ten,
	jack,
	queen,
	king
};

enum class CardSuit {
	joker,
	clubs,
	spades,
	diamonds,
	hearts
};

struct Card {
	CardFace Face = CardFace::joker;
	CardSuit Suit = CardSuit::joker;
};

class Hand
{
public:
	Hand();
//	Card GetCardsInHand() const;
	int GetHandLength() const;
	int GetAcesTotal() const;
	int GetPointsInHand();
	
	void PrintNthCard(int);
	void AddCard(Card);
	void ReadOutHand(std::string);
	void PrintCardAsString(Card);
	int PointsForCard(Card);

private:
	Card CardsInHand[22];
	int HandLength;
	int AcesTotal;

};

