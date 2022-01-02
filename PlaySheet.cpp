// PlaySheet.cpp 
// Written by Jon Luman

#include <vector>
#include <string> 
#include "PlaySheet.h"

std::vector<std::string> Fcolors = { "Red", "Yellow"};
std::vector<std::string> Rcolors = { "Green", "Blue" };

int PlaySheet::callback(void* NotUsed, int argc, char** argv, char** azColName) {

    // int argc: holds the number of results
    // (array) azColName: holds each column returned
    // (array) argv: holds each value

    for (int i = 0; i < argc; i++)
    {
        // Show column name, value, and newline
        std::cout << azColName[i] << ": " << argv[i] << std::endl;
    }

    // Insert a newline
    std::cout << std::endl;

    // Return successful
    return 0;
}

void PlaySheet::InitializeSheet(std::vector<PlaySheet*> o, std::string n)
{
    name = n;
    availablePlays.reserve(1000);
    availablePlays.clear();
    scoredPlays.clear();
    score = 0;

    for (std::vector<std::string>::iterator t = Fcolors.begin(); t != Fcolors.end(); ++t)
    {
        Play Pre(*t, 2);
        availablePlays.push_back(Pre);

        for (int r = 3; r <= 11; r++)
        {
            Play Curr(*t, r, &availablePlays.at(availablePlays.size() - 1));
            availablePlays.push_back(Curr);
        }
    }

    for (std::vector<std::string>::iterator t = Rcolors.begin(); t != Rcolors.end(); ++t)
    {
        Play Pre(*t, 12);
        availablePlays.push_back(Pre);

        for (int r = 11; r >= 3; r--)
        {
            Play Curr(*t, r, &availablePlays.at(availablePlays.size() - 1));
            availablePlays.push_back(Curr);
        }
    }
    score = 0;
    slashes = 0;
    opp = o;

}

void PlaySheet::scorePlay(Play p)
{
    if (p.Color.compare("none") == 0)
    {
        slashes++;
    }
    else
    {

        scoredPlays.push_back(p);

        int nScored = 0;
        for (std::vector<Play>::iterator s = scoredPlays.begin(); s != scoredPlays.end(); ++s)
        {
            if (p.Color.compare(s->Color) == 0)
            {
                nScored++;
            }
        }
        if (nScored == 5)
        {
            if ((p.Color.compare(std::string("Red")) == 0) || (p.Color.compare(std::string("Yellow"))==0))
            {
                std::vector<Play>::iterator finder = availablePlays.begin();
                while (finder != availablePlays.end())
                {
                    if ((finder->Number == 11) && ((*finder).Color.compare(p.Color))==0)
                    {
                        break;
                    }
                    else
                    {
                        ++finder;
                    }
                }
                if (finder != availablePlays.end())
                {
                    availablePlays.emplace_back(p.Color, 12, &*finder);
                }
                else
                {
                    availablePlays.emplace_back(p.Color, 12, nullptr);
                }
            }
            else if ((p.Color.compare(std::string("Blue"))==0) || (p.Color.compare(std::string("Green"))==0))
            {
                std::vector<Play>::iterator finder = availablePlays.begin();
                while (finder != availablePlays.end())
                {
                    if ((finder->Number == 3) && ((*finder).Color.compare(p.Color))==0)
                    {
                        break;
                    }
                    else
                    {
                        ++finder;
                    }
                }
                if (finder != availablePlays.end())
                {
                    availablePlays.emplace_back(p.Color, 2, &*finder);
                }
                else
                {
                    availablePlays.emplace_back(p.Color, 2, nullptr);
                }
            }
        }

        for (std::vector<Play>::iterator it = availablePlays.begin(); it != availablePlays.end(); ++it)
        {
            if (p.Color == it->Color && p.Number == it->Number)
            {
                //Play h = *it;
                removePlay(&(*it));
            }
        }

        if (((p.Color.compare(std::string("Red"))==0) || (p.Color.compare(std::string("Yellow"))==0)) && (p.Number == 12))
        {
            scoredPlays.emplace_back(p.Color, 13);
        }
        if (((p.Color.compare(std::string("Green"))==0) || (p.Color.compare(std::string("Blue"))==0)) && (p.Number == 2))
        {
            scoredPlays.emplace_back(p.Color, 1);
        }
    }
    scoreSheet();
}

void PlaySheet::removePlay(Play* it)
{
    if ((*it).PrecedingPlay != nullptr)
    {
        PlaySheet::removePlay((*it).PrecedingPlay);
    }
    (*it).Color = "None";
    (*it).Number = 0;
    (*it).PrecedingPlay = nullptr;
}

void PlaySheet::scoreSheet()
{
    score = 0;
    std::vector<std::string> colors = { "Red", "Yellow","Green","Blue" };

    for(std::vector<std::string>::iterator c = colors.begin(); c != colors.end(); ++c)
    {
        int nColor = 0; 
        int colorScore = 0;
        for (std::vector<Play>::iterator p = scoredPlays.begin(); p != scoredPlays.end(); ++p)
        {
            if (p->Color.compare(*c) == 0)
            {
                nColor++;
                colorScore += nColor;
            }
        }
        score += colorScore;
    }
    score -= slashes * 5;
}
int PlaySheet::scoreColor(std::string Color)
{
    int nColor = 0;
    int colorScore = 0;
    for (std::vector<Play>::iterator p = scoredPlays.begin(); p != scoredPlays.end(); ++p)
    {
        if (p->Color.compare(Color) == 0)
        {
            nColor++;
            colorScore += nColor;
        }
    }
    return(colorScore);
}

//void PlaySheet::outputToSQLite(sqlite3* db, int Game_id, int totalTurns, int Rounds, std::vector<int> closed)
//{
//    int rc; 
//    char* zErrMsg = 0;
//
//    std::string sql = "insert into Games (Game_id, Player, NumberOfOpponents, Score, TotalTurns, "
//        " Rounds, NumberOfSlashes, RedClosed, YellowClosed, GreenClosed, BlueClosed, RedScore, YellowScore, GreenScore, BlueScore) "
//        " values ( "
//        + std::to_string(Game_id) + ", '"
//        + name + "', "
//        + std::to_string(opp.size()) + ", "
//        + std::to_string(score) + ", "
//        + std::to_string(totalTurns) + ", "
//        + std::to_string(Rounds) + ", "
//        + std::to_string(slashes) + ", "
//        + std::to_string(closed[0]) + ", "
//        + std::to_string(closed[1]) + ", "
//        + std::to_string(closed[2]) + ", "
//        + std::to_string(closed[3]) + ", "
//        + std::to_string(scoreColor(std::string("Red"))) + ", "
//        + std::to_string(scoreColor(std::string("Yellow"))) + ", "
//        + std::to_string(scoreColor(std::string("Green"))) + ", "
//        + std::to_string(scoreColor(std::string("Blue"))) + ") ";
//
//    char* sql_ = const_cast<char*>(sql.c_str());
//    //std::cout << sql_;
//
//    rc = sqlite3_exec(db, sql_, 0, 0, &zErrMsg);
//
//}
