// PlaySheet.h - Header file for the player score sheet
// Written by Jon Luman

#include <iostream>
#include <vector>
#include <string> 
#include "plays.h"
//#include "sqlite3.h" 

#ifndef PlaySheet_H
#define PlaySheet_H

class PlaySheet
{
public:
	// Initializes the player sheet with 40 avaiable plays
	void InitializeSheet(std::vector<PlaySheet*>, std::string);

	// moves play to scorePlays and removes play (and subsequents) from avaiable plays
	void scorePlay(Play);

	void scoreSheet();
	int scoreColor(std::string);
	//void outputToSQLite(sqlite3*, int, int, int, std::vector<int>);

	std::string name;
	int score = 0;
	int slashes = 0;

	std::vector<Play> RollPlays;
	std::vector<Play> availablePlays;
	std::vector<Play> scoredPlays;
	std::vector<PlaySheet*> opp;

private:

	void removePlay(Play*);
	int callback(void*, int, char**, char**);

};

#endif