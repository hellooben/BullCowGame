//
//  main.cpp
//  BullCowGame
//
//  Created by Ben Bailey on 7/5/17.
//  Copyright © 2017 Ben Bailey. All rights reserved.
//

/*
This is the console executable that uses the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all user interaction. For game logic, see FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

//making syntax Unreal friendly
using FText = std::string;
using int32 = int;

void printIntro();
void printGameSummary();
FText getValidGuess();
void playGame();
bool playAgain();

FBullCowGame BCGame;


//entry point for our game
int main() {
    
    bool bPlay = false;
    do {
        printIntro();
        playGame();
        bPlay = playAgain();
    }
    while (bPlay);
    
    return 0;
}


void printIntro() {
    std::cout << std::endl << "Welcome to Bulls and Cows, a fun word game!" << std::endl << std::endl;
    std:: cout << "         |^^^^|" << std:: endl;
    std:: cout << "         |    |" << std:: endl;
    std:: cout << "        @|   Oo" << std:: endl;
    std:: cout << "         |  ._>" << std:: endl;
    std:: cout << "         \\   /" << std:: endl;
    std:: cout << "  /---------" << std:: endl;
    std:: cout << " / |      ||" << std:: endl;
    std:: cout << "*  ||-----||" << std:: endl;
    std:: cout << "   ^^     ^^" << std:: endl;
    std:: cout << " Bart Simpcow" << std:: endl << std::endl;
    std::cout << "In this game, a bull is a correct letter in the correct position." << std::endl;
    std::cout << "A cow is a correct letter in the wrong position." << std::endl;
    std::cout << "An isogram is a word with no repeating letters." << std::endl << std::endl;
    std::cout << "Can you guess the " << BCGame.getHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;
    std::cout << "Give it a try." << std::endl;
    return;
}


FText getValidGuess() {
    FText guess = "";
    EGuessStatus status = EGuessStatus::Invalid_Status;
    do {
        int32 currTry = BCGame.getCurrentTry();
    
        std::cout << "Try " << currTry << " of " << BCGame.getMaxTries() << ". Enter a word: ";
    
        getline(std::cin, guess);
    
        status = BCGame.checkGuess(guess);
        switch (status) {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.getHiddenWordLength() << " letter word." << std::endl << std::endl;
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters." << std::endl << std::endl;
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter all lowercase letters" << std::endl << std::endl;
                break;
            default:
                return guess;
        }
    } while (status != EGuessStatus::OK);
    return guess;
}

//Plays a single game to completion
void playGame() {
    BCGame.reset();
    
    int32 maxTries = BCGame.getMaxTries();
    
    while (!BCGame.gameWon() && BCGame.getCurrentTry() <= maxTries) {
        FText guess = getValidGuess();
        
        FBullCowCount BullCowCount = BCGame.submitValidGuess(guess);
        
        std::cout << "Bulls = " << BullCowCount.bulls;
        std::cout << ". Cows = " << BullCowCount.cows << std::endl << std::endl;
    }
    printGameSummary();
    return;
}

bool playAgain() {
    std::cout << "Do you want to play again with the same hidden word? (y/n) " << std::endl;
    FText response = "";
    getline(std::cin, response);
    
    if (response[0] == 'y' || response[0] == 'Y') {
        std::cout << std::endl;
        return true;
    }
    else {return false;}
}

void printGameSummary() {
    if (BCGame.gameWon()) {
        std::cout << "WELL DONE - YOU WIN!" << std::endl;
    }
    else {
        std::cout << "Better luck next time :(" << std::endl;
    }
}



