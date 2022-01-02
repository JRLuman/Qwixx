// plays.h header file for plays
// Jon Luman 4 Dec 2021

#include <string> 
#include <ctime>

#ifndef Die_H
#define Die_H


class Die {
public:
	std::string Color;  
	int Number;  

	Die(std::string c)
	{
		Color = c;
		Number = 0;
	}

	void Roll()
	{
		Number = 1 + std::rand() / ((RAND_MAX + 1u) / 6);
	}

};

#endif
