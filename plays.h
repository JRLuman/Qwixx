// plays.h header file for plays
// Jon Luman 29 Nov 2021

#include <string>
//#include "sqlite3.h"

#ifndef Play_H
#define Play_H

class Play {
public:
	std::string Color;  // Attribute
	int Number;  // Attribute
	Play *PrecedingPlay = nullptr;
	int Mixed;
	int Optional;
	int MyTurn;

	long int Play_id;
	void set_ID(long int);
	//void outputToSQLite(sqlite3* db, int, int, std::string, int);

	Play()
	{	}

	Play(std::string c, int n)
	{
		Color = c;
		Number = n;
	}

	Play(std::string c, int n, Play* p)
	{
		Color = c;
		Number = n;
		PrecedingPlay = p;
	}

	Play(std::string c, int n, int m)
	{
		Color = c;
		Number = n;
		Mixed = m;
	}

};

#endif
