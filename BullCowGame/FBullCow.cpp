#include <iostream>
#include <map>
#include "FBullCow.h"

#define TMap std::map
#define FText std::string
#define int32 int

FBullCow::FBullCow() { Reset(); }

int32 FBullCow::GetMaxTries() const { return MyMaxTries; }
int32 FBullCow::GetCurrentTry() const { return MyCurrentTry; }

void FBullCow::Reset()
{
	constexpr int32 CURRENT_TRY = 1;
	constexpr int32 MAX_TRIES = 8;
	constexpr int32 BULL_COUNT = 0;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyCurrentTry = CURRENT_TRY;
	MyHiddenWord = HIDDEN_WORD;
	MyBullCount = BULL_COUNT;

	return;
}

int32 FBullCow::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

// Receives a VALID guess, increments turn and returns count
FBullCowCount FBullCow::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	for (int32 HWChar = 0; HWChar < WordLength; HWChar++)
	{
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (Guess[GChar] == MyHiddenWord[HWChar]) 
			{
				if (HWChar == GChar) // if they are in the same place
				{
					BullCowCount.Bulls++;
					MyBullCount = BullCowCount.Bulls;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
		
	}

	return BullCowCount;
}

bool FBullCow::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;

	for (auto Letter : Guess) 
	{ // for all Letters of the Guess
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false; // we do not have an isogram
		}
		else 
		{
			LetterSeen[Letter] = true; // add the letter to the map
		}
	}

	return true; // for example in cases where /0 is entered
}

bool FBullCow::IsLowercase(FString Guess) const
{
	for (auto Letter : Guess)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}
	return true;
}

bool FBullCow::IsGameWon() const
{
	if (MyBullCount == MyHiddenWord.length())
	{
		return true;
	}
	else
	{
		return false;
	}
}

EWordStatus FBullCow::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EWordStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EWordStatus::Not_Lowercase;
	}
	else if (GetHiddenWordLength() != Guess.length())
	{
		return EWordStatus::Wrong_Length;
	}
	else
	{
		return EWordStatus::OK;
	}
}

