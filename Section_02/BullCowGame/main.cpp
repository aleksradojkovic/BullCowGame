#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void Printintro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

int main() {
	do {
		Printintro();
		PlayGame();
		PrintGameSummary();
	} while (AskToPlayAgain());
	return 0;
}

void PlayGame()
{
	int32 MaxTries = BCGame.getMaxTries();
	while(!BCGame.isOver() && BCGame.getCurrentTries() <= BCGame.getMaxTries()) {
		FText s = GetGuess();
		FBullCowCount BCCount = BCGame.guess(s);
		std::cout << "Bulls: " << BCCount.bulls << ", Cows = " << BCCount.cows << std::endl << std::endl;
	}
}

void Printintro() {
	std::cout << "\n\nWelcome to game Bulls & Cows!\nCan you guess the " << BCGame.HiddenWordLength() << " letter word with no repeating letters?\n";
}

FText GetGuess() {
	FText toRet = "";
	EWordStatus status;
	do {
		std::cout << "Try " << BCGame.getCurrentTries() << " out of " <<BCGame.getMaxTries() <<". Guess??? -----> ";
		getline(std::cin, toRet);
		status = BCGame.validity(toRet);
		switch (status) {
		case EWordStatus::Not_Same_Length:
			std::cout << "Please enter a " << BCGame.HiddenWordLength() << " letter word length.\n\n";
			break;
		case EWordStatus::Not_lowercase:
			std::cout << "Please enter a lowecase word.\n\n";
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "Please enter a word with no repeating letters.\n\n";
			break;
	}
	} while (status != EWordStatus::OK);
	return toRet;
}

bool AskToPlayAgain()
{
	BCGame.reset();
	std::cout << "\n\nDo you want to play again? (Y/N)\n";
	char a;
	while (1) {
		a = getchar();
		if (a == 'y' || a == 'Y') {
			while(getchar() != '\n'); return true;
		}
		else if (a == 'n' || a == 'N') {
			while (getchar() != '\n'); return false;
		}
	}
}

void PrintGameSummary() {
	std::cout << "***********************************************************\n";
	std::cout << "***********************************************************\n";
	if (BCGame.isOver()) {
		std::cout << "Good job. You matched the word in " << BCGame.getCurrentTries() - 1;
		
		if (BCGame.getCurrentTries() == 2) std::cout << " try. ";
		else
			std::cout << " tries. ";
			
		std::cout << "Well done :)\n";
	}
	else {
		std::cout << "Bad luck. Next time more luck. Searching word was: " << BCGame.getHiddenWord() << std::endl;
	}
	std::cout << "***********************************************************\n";
	std::cout << "***********************************************************\n";
}