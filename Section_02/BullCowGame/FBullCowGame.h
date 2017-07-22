#pragma once

#include <string>
#include <iostream>
#include <vector>


using int32 = int;
using FText = std::string;

struct FBullCowCount {
	int bulls, cows;
};

enum class EWordStatus {
	OK,
	Not_Isogram,
	Not_Same_Length,
	Not_lowercase,
	Unknown
};
class FBullCowGame{
public:
	FBullCowGame();
	~FBullCowGame();
	void start();
	void reset();
	void finish();
	EWordStatus validity(FText s) const;
	FBullCowCount guess(FText s);
	bool isOver() const;
	int32 getMaxTries() const;
	int32 getCurrentTries() const;
	FText getHiddenWord() const;
	int32 HiddenWordLength() const;
private:
	int32 CurrentTries;
	FText HiddenWord;
	std::vector<FText> words;
	bool bwon;
	bool isIsogram(FText s) const;
	bool isLowercase(FText s) const;
};