/*
This is the console executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction. For game logic, see the FBullCow class.
*/

#include <iostream>
#include <string>
#include "FBullCow.h"

using FText = FString;
using int32 = int;

void PrintIntro();
void PlayGame();
bool AskToPlayAgain();
FText GetValidGuess();

FBullCow BCGame; // Instantiate a new game

// Entry point for application
int main() 
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);

	return 0; // Exit the application
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		FBullCowCount FBullCowCount = BCGame.SubmitValidGuess(Guess); 

		std::cout << "Bulls = " << FBullCowCount.Bulls;
		std::cout << " Cows = " << FBullCowCount.Cows << std::endl << std::endl;
	}

	return;
}

void PrintIntro()
{
	std::cout << std::endl;
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;

	std::cout << "          }  {                  ___ " << std::endl;
	std::cout << "         (o  o)                (o o)" << std::endl;
	std::cout << "  /-------\\  /                  \\ /------\\" << std::endl;
	std::cout << " / | BULL |0                     0| COW  |\\" << std::endl;
	std::cout << "*  |-,--- |                       |------|  *"<< std::endl;
	std::cout << "   ^      ^                       ^      ^" << std::endl;

	std::cout << std::endl;

	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	return;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n) ";

	FText Response = "";
	std::getline(std::cin, Response);

	return Response[0] == 'y' || Response[0] == 'Y';
}

FText GetValidGuess()
{
	FText Guess = "";
	EWordStatus GuessStatus = EWordStatus::Invalid_Status;
	do
	{
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		EWordStatus Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EWordStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "Please enter an isogram (no letters repeat).\n";
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "Please enter only lower case letters.\n";
			break;
		default:
			return Guess;
		}
		std::cout << std::endl;
	} while (GuessStatus != EWordStatus::OK);

	return Guess;
}