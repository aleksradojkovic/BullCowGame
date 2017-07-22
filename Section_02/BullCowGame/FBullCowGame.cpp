#include "FBullCowGame.h"
#include <unordered_map>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <time.h>

bool FBullCowGame::isOver() const { return bwon; }
int32 FBullCowGame::getMaxTries() const {
	std::unordered_map<int32, int32> len = { {3,5},{4,8},{5,12},{6,16},{7,20} };
	return len.find(HiddenWord.length())->second;
}
int32 FBullCowGame::getCurrentTries() const { return CurrentTries; }
FText FBullCowGame::getHiddenWord() const
{
	return HiddenWord;
}
int32 FBullCowGame::HiddenWordLength() const { return HiddenWord.length(); }

FBullCowGame::FBullCowGame() { 
	std::ifstream myfile;
	myfile.open("isograms.txt");
	if (myfile.is_open()) {
		while (!myfile.eof()) {
			FText s;
			getline(myfile, s);
			words.push_back(s);
		}
	}
	myfile.close();
	srand(time(NULL));
	reset(); 
}


FBullCowGame::~FBullCowGame()
{
}

void FBullCowGame::start()
{
}

void FBullCowGame::reset() {
	HiddenWord = words[rand() % words.size()];
	CurrentTries = 1;
	bwon = false;
}

void FBullCowGame::finish()
{
}

EWordStatus FBullCowGame::validity(FText s) const
{
	if (s.length() != HiddenWord.length()) {
		return EWordStatus::Not_Same_Length;
	}
	else if (!isLowercase(s)) {
		return EWordStatus::Not_lowercase;
	}
	else if (!isIsogram(s)) {
		return EWordStatus::Not_Isogram;
	}
	else return EWordStatus::OK;
}

FBullCowCount FBullCowGame::guess(FText s)
{
	CurrentTries++;

	FBullCowCount cnt = { 0,0 };

	for (int32 i = 0; i < HiddenWord.length(); i++) {
		for (int32 j = 0; j < s.length(); j++) {
			if (HiddenWord[i] == s[j]) {
				if (i == j) cnt.bulls++;
				else cnt.cows++;
			}
		}
	}
	bwon = (cnt.bulls == HiddenWord.length());
	return cnt;
}


bool FBullCowGame::isIsogram(FText s) const
{
	std::unordered_map<char, int> mapped;
	for (int i = 0; i < s.length(); i++) {
		if (mapped.end() == mapped.find(s[i])) mapped.insert({ tolower(s[i]),i });
		else return false;
	}
	return true;
}

bool FBullCowGame::isLowercase(FText s) const
{
	for (auto Letter : s) {
		if (isalpha(Letter) && !islower(Letter)) return false;
	}
	return true;
}
