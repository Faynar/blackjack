#pragma once
#include "Hand.h"


enum class TurnStatus {
	Hit,
	Stand,
	BlackJack,
	Busted
};

class BlackJack
{
public:
	BlackJack();

	void PrintIntro();
	void PlayGame();
	bool AskToPlayAgain();
	char AskUserQuestion(std::string, char, char);

private:
	TurnStatus AskPlayerIfHit(Hand);
	Card RandomCardTest();
	CardFace PickARandomCardFace();
	CardSuit PickARandomCardSuit();
	Card PickARandomCard();
};
