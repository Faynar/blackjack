#pragma once
#include "BlackJack.h"
#include <iostream>
#include <string>
#include <sstream>



BlackJack::BlackJack() // Default constructor
{
}



// TODO add rules and ascii art of blackjack and hookers?
void BlackJack::PrintIntro()
{
	std::cout << "Let's play some BlackJack!!\n";
	std::cout << "Hopefully you know the rules already because I haven't put them in yet!\n";

	return;
}

void BlackJack::PlayGame()
{
	Hand PlayerHand;
	Hand HouseHand;

	// 2 cards dealt out to player and hand read out to console
	PlayerHand.AddCard(PickARandomCard());
	PlayerHand.AddCard(PickARandomCard());
	std::cout << std::endl;
	PlayerHand.ReadOutHand("Player");

	// TODO reveals dealer's second card if the first card is an ace or something that gives 10 points
	// 1 card dealt out "face up" to house and read to console, 1 card dealt to house "face down"
	Card HouseCard1 = PickARandomCard();
	HouseHand.AddCard(HouseCard1);
	HouseHand.AddCard(PickARandomCard());
	std::cout << std::endl << "The house starts with a ";
	HouseHand.PrintCardAsString(HouseCard1);
	std::cout << " and another card facedown\n";
	std::cout << "\nThe house has at least " << HouseHand.PointsForCard(HouseCard1) << " points.\n";

	// while the player keeps saying hit it gives them a card, reads and prints hand back out, and asks again
	TurnStatus PlayerTurn;
	PlayerTurn = AskPlayerIfHit(PlayerHand);
	while (PlayerTurn == TurnStatus::Hit) {

		PlayerHand.AddCard(PickARandomCard());
		PlayerHand.ReadOutHand("Player");

		PlayerTurn = AskPlayerIfHit(PlayerHand);
	}

	// dealer reveals their hand and hits if needed
	std::cout << "The dealer's second card is ";
	HouseHand.PrintNthCard(1);
	std::cout << std::endl;

	TurnStatus HouseTurn = TurnStatus::Stand;

	int HouseScore = HouseHand.GetPointsInHand();
	while (HouseScore < 17) {
		Card NewHouseCard = PickARandomCard();
		std::cout << "The house draws ";
		HouseHand.PrintCardAsString(NewHouseCard);
		std::cout << std::endl;
		HouseHand.AddCard(NewHouseCard);
		HouseScore = HouseHand.GetPointsInHand();
	}
	std::cout << std::endl;
	// If the house has 17 points or more they must stand
	// If the house has under 17 it must hit
	
	// TODO make this it's own class, and output the ending scores for player and house at the end
	// round is evaluated, results are set, and asks if they'd like to play again
	RoundResults CurrentRound;
	switch (PlayerTurn) {
	// If the player busted
	case TurnStatus::Busted: 
		// and the house did too it's a tie
		if (HouseTurn == TurnStatus::Busted) {
			std::cout << "You both busted!";
			CurrentRound = RoundResults::Tie;
			break;
		} // if the house didn't bust as well the player loses
		std::cout << "You lost";
		CurrentRound = RoundResults::PlayerLoss;
		break;
	// If the player got blackjack
	case TurnStatus::BlackJack:
		// if the house also got blackjack it's a tie
		if (HouseTurn == TurnStatus::BlackJack) {
			std::cout << "Incredible! It's a Blackjack Tie!";
			CurrentRound = RoundResults::Tie;
			break;
		} // If the house didn't also get blackjack the player wins
		std::cout << "Awesome! You've won with Blackjack!";
		CurrentRound = RoundResults::PlayerWin;
		break;
	// If the player didn't bust or get blackjack
	case TurnStatus::Stand:
		// if the house got blackjack the player loses
		if (HouseTurn == TurnStatus::BlackJack) {
			std::cout << "Bummer! You lost to Blackjack!";
			CurrentRound = RoundResults::PlayerLoss;
			break;
		} // if the house busted the player wins
		else if (HouseTurn == TurnStatus::Busted) {
			std::cout << "Nice! The house busted!";
			CurrentRound = RoundResults::PlayerLoss;
			break;
		}
		// otherwise compare scores
		int PlayerScore = PlayerHand.GetPointsInHand();
		if (PlayerScore > HouseScore) {
			std::cout << "Congrats! You've won!";
			CurrentRound = RoundResults::PlayerWin;
			break;
		}
		else if (PlayerScore == HouseScore) {
			std::cout << "It's a tie!";
			CurrentRound = RoundResults::Tie;
			break;
		}
		else {
			std::cout << "You lost. Better luck next time!";
			CurrentRound = RoundResults::PlayerLoss;
			break;
		}
	}
	std::cout << std::endl;

	//TODO add betting

	std::cout << std::endl;
	return;
}

// Returns true if they want to play again
bool BlackJack::AskToPlayAgain()
{
	char Response = AskUserQuestion( "Would you like to play again? (y/n)\n", 'y', 'n');
	if (Response == 'y' || Response == 'Y') {
		std::cout << "\n\n";
		return true;
	}
	else {
		return false;
	}
}

// Asks the question to the user and then takes their response as a character, ignoring anything else input
char BlackJack::AskUserQuestion(std::string Question, char char1, char char2)
{
	int num;
	std::string FullResponse;
	char Response;
	// Outer loop keeps asking while they don't input any response at all or one that starts with a number
	do {
		std::cout << Question;
		std::getline(std::cin, FullResponse);
		if (!(Response = FullResponse[0])) {
			std::cout << "Invalid input, please try again.\n";
		}
	} while (Response != char1 && Response != toupper(char1)
		&& Response != char2 && Response != toupper(char2));
	
	return Response;
}

// Shows player's points then repeatedly asks the player if they'd like to hit or stand until they stand
TurnStatus BlackJack::AskPlayerIfHit(Hand TargetHand)
{
	int HandPoints = TargetHand.GetPointsInHand();
	std::cout << "You have " << HandPoints << " points.\n";
	// ends the match if they've won or lost
	if (HandPoints >= 21) {
		if (HandPoints == 21) {
			std::cout << "BLACKJACK!!!\n\n";
			return TurnStatus::BlackJack;
		}
		else {
			std::cout << "You've busted!\n\n";
			return TurnStatus::Busted;
		}
	}

	char Response = AskUserQuestion("Hit or stand?\n", 'h', 's');
	if (Response == 'h' || Response == 'H') {
		std::cout << "Hit!\n\n";
		return TurnStatus::Hit;
	}
	else if (Response == 's' || Response == 'S') {
		std::cout << "Stand!\n\n";
		return TurnStatus::Stand;
	}
	return TurnStatus::Hit;
}

//For testing new random number generators
Card BlackJack::RandomCardTest()
{
	Card ChosenCard;

	int CardsDrawn[15] = { 0 };
	int SuitsDrawn[5] = { 0 };

	//Generates i "random" card values
	for (signed int i = 0; i < 1000; i++) {
		int number = (rand() * i % 13) + 1;
		CardsDrawn[number]++;
		//std::cout << number << std::endl;
	}
	std::cout << std::endl;

	/*
	//Testing output of rand()%13
	for (int i = 0; i < 15; i++) {
	std::cout << "Card " << i << " drawn " << CardsDrawn[i] << " times.\n";
	}
	*/

	//Generates i "random" card suits
	for (signed int i = 0; i < 1000; i++) {
		int number = (rand() * i % 4) + 1;
		SuitsDrawn[number]++;
		//std::cout << number << std::endl;
	}
	std::cout << std::endl;

	/*
	//Testing output of rand()%4
	for (int i = 0; i < 5; i++) {
	std::cout << "Suit " << i << " drawn " << SuitsDrawn[i] << " times.\n";
	}
	*/

	return ChosenCard;
}

CardFace BlackJack::PickARandomCardFace()
{
	// Generate random card face value
	int FaceNumber = (rand() % 13) + 1;
	//std::cout << FaceNumber << std::endl;

	// return the appropriate card face
	if (FaceNumber == 0) {
		return CardFace::joker;
	}
	else if (FaceNumber == 1) {
		return CardFace::ace;
	}
	else if (FaceNumber == 2) {
		return CardFace::two;
	}
	else if (FaceNumber == 3) {
		return CardFace::three;
	}
	else if (FaceNumber == 4) {
		return CardFace::four;
	}
	else if (FaceNumber == 5) {
		return CardFace::five;
	}
	else if (FaceNumber == 6) {
		return CardFace::six;
	}
	else if (FaceNumber == 7) {
		return CardFace::seven;
	}
	else if (FaceNumber == 8) {
		return CardFace::eight;
	}
	else if (FaceNumber == 9) {
		return CardFace::nine;
	}
	else if (FaceNumber == 10) {
		return CardFace::ten;
	}
	else if (FaceNumber == 11) {
		return CardFace::jack;
	}
	else if (FaceNumber == 12) {
		return CardFace::queen;
	}
	else if (FaceNumber == 13) {
		return CardFace::king;
	}
	return CardFace::joker;
}

CardSuit BlackJack::PickARandomCardSuit()
{
	// Generate random card suit value
	int SuitNumber = (rand() % 4) + 1;
	//std::cout << SuitNumber << std::endl;

	if (SuitNumber == 0) {
		return CardSuit::joker;
	}
	if (SuitNumber == 1) {
		return CardSuit::clubs;
	}
	if (SuitNumber == 2) {
		return CardSuit::spades;
	}
	if (SuitNumber == 3) {
		return CardSuit::diamonds;
	}
	if (SuitNumber == 4) {
		return CardSuit::hearts;
	}

	return CardSuit();
}

// Returns a random card to simulate drawing from the deck
// TODO add a deck (or six) to make this draw from
// TODO improve random number generator
Card BlackJack::PickARandomCard()
{
	// Put them together into a card
	Card NewRandomCard;
	NewRandomCard.Face = PickARandomCardFace();
	NewRandomCard.Suit = PickARandomCardSuit();
	/*
	// Print the card out
	std::cout << "Drawing ";
	PrintCardAsString(NewRandomCard);
	std::cout << std::endl;
	*/
	return NewRandomCard;
}
