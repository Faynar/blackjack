/* This is my first attempt at a non-tutorial game in c++
It's going to be a BlackJack game
Made by Zander
*/

#pragma once
#include <iostream> // cin, cout, getline
#include <string> // string
#include <time.h> //  time() for random seed
#include "BlackJack.h"


// TODO add splitting pairs, doubling down, insurance
// Entry point for the game
int main()
{
	srand(time(NULL)); // starting seed for random number generator
	BlackJack BJGame;

	BJGame.PrintIntro();
	//PrintIntro();

	do {
		BJGame.PlayGame();
	} while (BJGame.AskToPlayAgain());
	//} while (AskToPlayAgain());

	return 0;
}
