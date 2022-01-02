// Jon Luman 29 Nov 2021

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
//#include "sqlite3.h" 

#include "die.h"
#include "plays.h"
#include "PlaySheet.h"
#include "Dice.h"
#include "PlayEval.h"


//std::vector<PlayEval> makeEvals(PlaySheet s, std::vector<PlaySheet*> o, int round, int c, sqlite3* db, long int GameID, long int nextEvalID, long int nextPlayID)
std::vector<PlayEval> makeEvals(PlaySheet s, std::vector<PlaySheet*> o, int round, int c,              long int GameID, long int nextEvalID, long int nextPlayID)
{
    std::vector<PlayEval> ePlays;
    for (std::vector<Play>::iterator r = s.RollPlays.begin(); r != s.RollPlays.end(); ++r)
    {
        std::vector<Play>::iterator a = s.availablePlays.begin();
        while (a != s.availablePlays.end())
        {
            if (((*a).Color == (*r).Color) && ((*a).Number == (*r).Number))
            {
                (*a).Mixed = (*r).Mixed;
                PlayEval EP(*a, s, o, round, c, GameID, nextEvalID, nextPlayID);
                nextEvalID++;
                ePlays.push_back(EP);
                //EP.outputToSQLite(db);
                break;
            }
            else
            {
                ++a;
            }
        }
    }
    return(ePlays);
}

Play selectPlay(std::vector<PlayEval> ePlays)
{
    if (ePlays.size() == 0)
    {
        return(Play(std::string("none"), 0));
    }
    else
    {
        int n2s = 10;
        int nSinC = 0;
        int nRinC = 10;
        std::vector<Play> best;
        for (std::vector<PlayEval>::iterator e = ePlays.begin(); e != ePlays.end(); ++e)
        {
            if (e->NumberToSkip < n2s)
            {
                n2s = e->NumberToSkip;
                best.clear();
                best.push_back(e->p);
            }
            else if (e->NumberToSkip == n2s)
            {
                if (e->NumberScoredInColor < nSinC)
                {
                    nSinC = e->NumberScoredInColor;
                    best.clear();
                    best.push_back(e->p);
                }
                else if (e->NumberScoredInColor == nSinC)
                {
                    if (e->NumberRemainingInColor > nRinC)
                    {
                        nRinC = e->NumberRemainingInColor;
                        best.clear();
                        best.push_back(e->p);
                    }
                    else
                    {
                        best.push_back(e->p);
                    }
                }
            }
            else
            {
                best.push_back(e->p);
            }
        }
        if (best.size() > 0)
        {
            Play P = best[rand() % best.size()];
            return(P);
        }
        else
        {
            std::cout << "hold here";
            return(Play("none",0));
        }
    }
}

bool choosePlayOrNo(double prob)
{
    double r = (1.0 *std::rand() )/ RAND_MAX;
    if ( r < prob)
    {
        return true;
    }
    else
        return false;
}

int main()
{
    
    //sqlite3* db; // I've taken out all the writes to SQL, it's a real bear to setup.  get started with it turned off.
    char* zErrMsg = 0;
    int rc;

    //rc = sqlite3_open("qwixx_v01.db", &db);

    // initilize randomizer
    std::srand(time(nullptr));

    //initilize unique identifiers.
    long int GameID = 880000000;
    long int nextPlayID = 660000000;
    long int nextEvalID = 440000000;
    int nGames = 0;

    // initilize game counter stuff.
    int turnInRound = 0;
    bool gameOver = false;
    int round = 0;
    int totalPlays = 0;

    PlaySheet Player1, Player2, Player3; // create players
    std::vector<PlaySheet*> Players = { &Player1,&Player2,&Player3 }; // set vector of players
    Dice GameDice; // make die
    std::vector<PlayEval> evals; // initilize play evaluator
    Play P; // initilize play

    while (nGames < 100) // run X games.
    {

        std::vector<std::string> DiceColors = { "Red", "Yellow", "Green", "Blue","White","White" };
        GameDice.InitializeDice(DiceColors);
        Player1.InitializeSheet(std::vector<PlaySheet*> { &Player2, & Player3 }, "Player1"); // set opponents
        Player2.InitializeSheet(std::vector<PlaySheet*> { &Player1, & Player3 }, "Player2");
        Player3.InitializeSheet(std::vector<PlaySheet*> { &Player1, & Player2 }, "Player3");
        GameDice.closedColors = 0;

        round = 0;
        totalPlays = 0;


        GameID++;
        gameOver = false;
        while (!gameOver) // main game loop
        {
            // increment unique identifiers.
            round++;
            turnInRound = 0;
            evals.clear();
            nextEvalID++;
            nextPlayID++;

            // loop over players to create a round
            for (std::vector<PlaySheet*>::iterator Player = Players.begin(); Player != Players.end(); ++Player)
            {
                if (!gameOver)
                {
                    turnInRound++;
                    totalPlays++;

                    GameDice.RollDice();

                    (**Player).RollPlays = GameDice.GetPlays(std::string("Both")); // compute valid plays
                    //evals = makeEvals((**Player), (**Player).opp, round, 6, db, GameID, nextEvalID, nextPlayID);
                    evals = makeEvals((**Player), (**Player).opp, round, 6, GameID, nextEvalID, nextPlayID);
                    nextEvalID += evals.size();
                    P = selectPlay(evals); // this is specific to player's turn.
                    P.set_ID(nextPlayID);
                    P.Optional = 0;
                    P.MyTurn = 1;
                    (**Player).scorePlay(P); 
                    //P.outputToSQLite(db, round, totalPlays, (**Player).name, GameID);
                    nextPlayID++;


                    if (P.Mixed == 1) // if the best play was a colored die and a white die, check if you want to score two white dice
                    {
                        (**Player).RollPlays = GameDice.GetPlays(std::string("Other")); // need to add other player's white dice plays
                    }
                    else // otherwise, the best play was two white dice, check if you want to score a white die and a colored die
                    {
                        (**Player).RollPlays = GameDice.GetPlays(std::string("Mixed")); // need to add other player's white dice plays
                    }

                    //evals = makeEvals((**Player), (**Player).opp, round, 6, db, GameID, nextEvalID, nextPlayID); // this is specific to player's turn.
                    evals = makeEvals((**Player), (**Player).opp, round, 6, GameID, nextEvalID, nextPlayID); // this is specific to player's turn.
                    nextEvalID += evals.size();
                    P = selectPlay(evals); // select the best play
                    if (P.Color.compare("none") != 0)
                    {
                        P.Optional = 1;
                        P.MyTurn = 1;


                        if (choosePlayOrNo(double(0.5)))  // right now, it's 50/50 if the next best play is scored, this is where the AI gets folded in.
                        {
                            P.set_ID(nextPlayID);
                            (**Player).scorePlay(P); 
                            //P.outputToSQLite(db, round, totalPlays, (**Player).name, GameID);
                            nextPlayID++;
                        }
                    }

                    // loop over opponents, see if they want to score a play
                    for (std::vector<PlaySheet*>::iterator Other = (**Player).opp.begin(); Other != (**Player).opp.end(); ++Other)
                    {
                        (**Other).RollPlays = GameDice.GetPlays(std::string("Other"));

                        //evals = makeEvals((**Other), (**Other).opp, round, 6, db, GameID, nextEvalID, nextPlayID);
                        evals = makeEvals((**Other), (**Other).opp, round, 6, GameID, nextEvalID, nextPlayID);
                        nextEvalID += evals.size();
                        P = selectPlay(evals); 
                        if (P.Color.compare("none") != 0)
                        {
                            P.Optional = 1;
                            P.MyTurn = 0;

                            if (choosePlayOrNo(double(0.5))) // 50/50 if they score the best play or not.  Add AI here.
                            {
                                P.set_ID(nextPlayID);
                                (**Other).scorePlay(P); 
                                //P.outputToSQLite(db, round, totalPlays, (**Other).name, GameID);
                                nextPlayID++;
                            }
                        }
                    }


                    gameOver = GameDice.checkForEndofGame(Players, 2, 4); // 2 closed colors, 4 failed throws.
                }
            }

        }
        std::vector<int> diceClosed = { GameDice.DieClosed(std::string("Red")),
                                        GameDice.DieClosed(std::string("Yellow")),
                                        GameDice.DieClosed(std::string("Green")),
                                        GameDice.DieClosed(std::string("Blue")) };  

        //Player1.outputToSQLite(db, GameID, totalPlays, round, diceClosed);
        //Player2.outputToSQLite(db, GameID, totalPlays, round, diceClosed);
        //Player3.outputToSQLite(db, GameID, totalPlays, round, diceClosed);


        std::cout << "game: " << nGames << "\n";
        nGames++;
    }
    //sqlite3_close(db);
    std::cout << "all done\n";
}



