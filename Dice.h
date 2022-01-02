// PlaySheet.cpp 
// Written by Jon Luman

#include <vector>
#include <string>
#include "plays.h"
#include "die.h"
#include "PlaySheet.h"

#ifndef Dice_H
#define Dice_H


class Dice
{
public:
    void InitializeDice(std::vector<std::string>);
    void RollDice();
    void RollDice(std::vector<int>);
    //void removeDice(std::vector<PlaySheet*>);
    bool checkForEndofGame(std::vector<PlaySheet*>, int, int);
    std::vector<Play> GetPlays(std::string);
    int NumberOfDice();
    int closedColors = 0;
    int DieClosed(std::string);
    //std::vector<Play> GetPlaysForPlayer();
    //std::vector<Play> GetOptionalPlaysWhiteOnly();
    //std::vector<Play> GetOptionalPlaysMixed();

private:
    std::vector<Die> DiceBag;
};

#endif