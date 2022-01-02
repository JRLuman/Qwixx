// Dice.cpp 
// Written by Jon Luman

#include <vector>
#include <string>
#include <iostream>
#include "die.h"
#include "plays.h"
#include "Dice.h"


void Dice::InitializeDice(std::vector<std::string> colors)
{
    DiceBag.clear();
    
    for (std::vector<std::string>::iterator t = colors.begin(); t != colors.end(); ++t)
    {
        DiceBag.emplace_back(*t);
    }

}

void Dice::RollDice()
{
    for (std::vector<Die>::iterator d = DiceBag.begin(); d != DiceBag.end(); ++d)
    {
        (*d).Roll();
    }

}
void Dice::RollDice(std::vector<int> fixed)
{
    std::vector<int>::iterator f = fixed.begin();
    for (std::vector<Die>::iterator d = DiceBag.begin(); d != DiceBag.end(); ++d)
    {
        (*d).Number = (*f);
        f++;
    }

}

bool Dice::checkForEndofGame(std::vector<PlaySheet*> Players, int MaxClosed, int MaxSlashes)
{
    bool GameOver = false;
    bool openColor = true;
    int numSlashes = 0;
    std::vector<Die>::iterator Die = DiceBag.begin();
    while (Die != DiceBag.end())
    {
        openColor = true;
        if ((Die->Color.compare("Red") == 0) || (Die->Color.compare("Yellow") == 0))
        {
            for (std::vector<PlaySheet*>::iterator Player = Players.begin(); Player != Players.end(); ++Player)
            {

                for (std::vector<Play>::iterator Play = (**Player).scoredPlays.begin(); Play != (**Player).scoredPlays.end(); ++Play)
                {
                    if (Play->Color.compare(Die->Color) == 0 and Play->Number == 12)
                    {
                        openColor = false;
                        closedColors++;
                    }
                }
            }

        }
        if ((Die->Color.compare("Green") == 0) || (Die->Color.compare("Blue") == 0))
        {
            for (std::vector<PlaySheet*>::iterator Player = Players.begin(); Player != Players.end(); ++Player)
            {

                for (std::vector<Play>::iterator Play = (**Player).scoredPlays.begin(); Play != (**Player).scoredPlays.end(); ++Play)
                {
                    if (Play->Color.compare(Die->Color) ==0 and Play->Number == 2)
                    {
                        openColor = false;
                        closedColors++;
                    }
                }
            }

        }
        if (!openColor)
        {
            Die = DiceBag.erase(Die);
        }
        else
        {
            ++Die;
        }

    }
    for (std::vector<PlaySheet*>::iterator Player = Players.begin(); Player != Players.end(); ++Player)
    {
        if ((**Player).slashes > numSlashes)
        {
            numSlashes = (**Player).slashes;
        }

    }
    if (numSlashes >= MaxSlashes or  closedColors >= MaxClosed)
    {
        GameOver = true;
    }
    return(GameOver);
}



std::vector<Play> Dice::GetPlays(std::string opt)
{
    std::vector<Play> possiblePlays;
    for (std::vector<Die>::iterator d1 = DiceBag.begin(); d1 != DiceBag.end(); ++d1)
        if ((*d1).Color != "White")
        {
            //for (std::vector<Die>::iterator d2 = d1; d2 != DiceBag.end(); ++d2)
            std::vector<Die>::iterator d2 = d1;
            ++d2;
            while ((*d2).Color != "White")
            {
                ++d2;
            }
            std::vector<Die>::iterator d3 = d2;
            ++d3;
            while ((*d3).Color != "White")
            {
                ++d3;
            }
            if (opt.compare(std::string("Mixed")) == 0 || (opt.compare(std::string("Both")) == 0 ))
            {
                possiblePlays.emplace_back((*d1).Color, (*d1).Number + (*d2).Number, true);
                if ((*d2).Number != (*d3).Number)
                {
                    possiblePlays.emplace_back((*d1).Color, (*d1).Number + (*d3).Number, true);
                }
            }
            if ((opt.compare(std::string("Other")) == 0) ||
                ((opt.compare(std::string("Both")) == 0) && (*d1).Number != (*d3).Number && (*d1).Number != (*d2).Number ))
            {
                possiblePlays.emplace_back((*d1).Color, (*d2).Number + (*d3).Number, false);
            }
        }
    return(possiblePlays);
}

int Dice::NumberOfDice()
{
    return(DiceBag.size() - 2);
}

int Dice::DieClosed(std::string Color)
{
    int closed = 0;
    for (std::vector<Die>::iterator d = DiceBag.begin(); d != DiceBag.end(); ++d)
    {
        if (d->Color.compare(Color) == 0)
        {
            closed = 1;
        }
    }
    return(1-closed);
}