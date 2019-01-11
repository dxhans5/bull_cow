#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCow
{
public:
	FBullCow(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;

	void Reset(); // TODO: make a more rich return value
	EWordStatus CheckGuessValidity(FString) const;
	FBullCowCount SubmitValidGuess(FString);


// Please try and ignore this and focus on the interface above
private:
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

	// See constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	int32 MyBullCount;
};