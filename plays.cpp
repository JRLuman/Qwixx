// plays.h header file for plays
// Jon Luman 29 Nov 2021

#include <string>
#include "plays.h"

void Play::set_ID(long int id)
{
	Play_id = id;
}

//void Play::outputToSQLite(sqlite3* db, int Round, int PlayNumber, std::string name, int Game_id)
//{
//	int rc;
//	char* zErrMsg = 0;
//
//	std::string sql = "insert into Plays (Game_id, Play_id, Player, Round, PlayNumber,  "
//		" Optional, Mixed, Color, Number, MyTurn)  values ( "
//		+ std::to_string(Game_id) + ", "
//		+ std::to_string(Play_id) + ", '"
//		+ name + "', "
//		+ std::to_string(Round) + ", "
//		+ std::to_string(PlayNumber) + ", "
//		+ std::to_string(Optional) + ", "
//		+ std::to_string(Mixed) + ", '"
//		+ Color + "', "
//		+ std::to_string(Number) + ", "
//		+ std::to_string(MyTurn) +  ") ";
//
//	char* sql_ = const_cast<char*>(sql.c_str());
//	//std::cout << sql_;
//
//	rc = sqlite3_exec(db, sql_, 0, 0, &zErrMsg);
//
//}
