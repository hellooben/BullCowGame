//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Ben Bailey on 7/5/17.
//  Copyright © 2017 Ben Bailey. All rights reserved.
//
#pragma once

#include "FBullCowGame.hpp"
#include <map>

//making syntax Unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() {
    reset();
}


bool FBullCowGame::gameWon() const {
    return bGameIsWon;
}


void FBullCowGame::reset() {
    
    const FString HIDDEN_WORD = "ham"; //this MUST be an isogram
    hiddenWord = HIDDEN_WORD;
    
    currentTry = 1;
    bGameIsWon = false;
    return;
}


int32 FBullCowGame::getMaxTries() const {
    TMap<int32, int32> wordLengthToMaxTries { {3, 4}, {4, 7}, {5, 10}, {6, 15}, {7, 20} };
    return wordLengthToMaxTries[hiddenWord.length()];
}


int32 FBullCowGame::getCurrentTry() const {
    return currentTry;
}


int32 FBullCowGame::getHiddenWordLength() const {
    return hiddenWord.length();
}


EGuessStatus FBullCowGame::checkGuess(FString x) const {
    if (!isIsogram(x)) {
        return EGuessStatus::Not_Isogram;
    }
    else if (!isLowerCase(x)) {
        return EGuessStatus::Not_Lowercase;
    }
    else if (getHiddenWordLength() != x.length()) {
        return EGuessStatus::Wrong_Length;
    }
    else {
        return EGuessStatus::OK;
    }
}



FBullCowCount FBullCowGame::submitValidGuess(FString guess) {
    currentTry ++;
    FBullCowCount count;
    
    int32 wordLen = hiddenWord.length();
    for (int32 i = 0; i < wordLen; i++) {
        for (int32 j = 0; j < wordLen; j++) {
            if (guess[j] == hiddenWord[i]) {
                if ( i == j) {
                    count.bulls ++;
                }
                else {
                    count.cows ++;
                }
            }
        }
    }
    
    if (count.bulls == wordLen) {
        bGameIsWon = true;
    }
    else {
        bGameIsWon = false;
    }
    
    return count;
}

bool FBullCowGame::isIsogram(FString word) const{
    if (word.length() <= 1) {
        return true;
    }
    
    TMap<char, bool> letterSeen;
    for (auto letter : word) {
        letter = tolower(letter);
        if (letterSeen[letter]) {
            return false;
        }
        else {
            letterSeen[letter] = true;
        }
    }
    
    return true;
}

bool FBullCowGame::isLowerCase(FString word) const {
    for (auto letter : word) {
        if (!islower(letter)) {
            return false;
        }
    }
    return true;
}






