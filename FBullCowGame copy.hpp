//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Ben Bailey on 7/5/17.
//  Copyright © 2017 Ben Bailey. All rights reserved.
//

/* The game logic (no view code or direct user interaction)
 The game is a simple guess the word game based on Mastermind
 */

#pragma once

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>
#include <string>

//making syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount {
    int32 bulls = 0;
    int32 cows = 0;
};

enum class EGuessStatus {
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame {
public:
    
    FBullCowGame();
    
    int32 getMaxTries() const;
    int32 getCurrentTry() const;
    int32 getHiddenWordLength() const;
    
    bool gameWon() const;
    EGuessStatus checkGuess(FString x) const;
    
    void reset();
    
    FBullCowCount submitValidGuess(FString);
    
private:
    //check constructor for initialization
    int32 currentTry;
    int32 maxTries;
    bool isIsogram(FString x);
    FString hiddenWord;
    bool bGameIsWon;
    
    bool isIsogram(FString) const;
    bool isLowerCase(FString) const;
};

#endif /* FBullCowGame_hpp */
