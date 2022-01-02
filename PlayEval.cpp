#include <iostream>
#include <vector>
#include <string> 
#include "PlayEval.h"

int PlayEval::callback(void* NotUsed, int argc, char** argv, char** azColName) {

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

int PlayEval::calcNumberToSkip(Play* p, int r)
{
	if ((*p).PrecedingPlay != nullptr)
	{
		calcNumberToSkip((*p).PrecedingPlay, r +1);
	}
	else
	{
		return(r);
	}
}

int PlayEval::calcNumberScoredInColor(std::string Color)
{
	int n = 0;
	for (std::vector<Play>::iterator i = s.scoredPlays.begin(); i != s.scoredPlays.end(); ++i)
	{
		if ((*i).Color.compare(Color) == 0)
		{
			n++;
		}
	}
	return(n);
}

int PlayEval::calcNumberRemainingInColor(std::string Color)
{
	int n = 0;
	for (std::vector<Play>::iterator i = s.availablePlays.begin(); i != s.availablePlays.end(); ++i)
	{
		if ((*i).Color.compare(Color) == 0)
		{
			n++;
		}
	}
	return(n);
}

int PlayEval::calcNumberSkippedInColor(std::string Color)
{
	//int n_avail = 0;
	//int n_scored = 0;
	//int n_plays = 10;
	//for (std::vector<Play>::iterator i = s.availablePlays.begin(); i != s.availablePlays.end(); ++i)
	//{
	//	if (i->Color.compare(p.Color) == 0)
	//	{
	//		n_avail++;
	//	}
	//	if (((i->Color.compare("Red") == 0) || (i->Color.compare("Yellow") == 0)) && i->Number == 12)
	//	{
	//		n_plays++;
	//	}
	//	else if (((i->Color.compare("Green") == 0) || (i->Color.compare("Blue") == 0)) && i->Number == 2)
	//	{
	//		n_plays++;
	//	}
	//}
	//for (std::vector<Play>::iterator i = s.scoredPlays.begin(); i != s.scoredPlays.end(); ++i)
	//{
	//	if (i->Color.compare(p.Color) == 0)
	//	{
	//		n_scored++;
	//	}
	//}
	//return (n_plays - n_avail + n_scored);
	
	int n_plays = 10;
	if (NumberScoredInColor >= 5)
	{
		n_plays++;
	}

	return (n_plays - NumberScoredInColor - NumberRemainingInColor);
}

int PlayEval::calcNumberScored()
{
	return(s.scoredPlays.size());
}

int PlayEval::calcNumberRemaining()
{
	int n = 0;
	for (std::vector<Play>::iterator i = s.availablePlays.begin(); i != s.availablePlays.end(); ++i)
	{
		if ((*i).Color.compare("None") != 0 )
		{
			n++;
		}
	}
	return(n);

}

int PlayEval::calcNumberSkipped()
{
	//int n_avail = 0;
	//int n_scored = 0;
	//int n_plays = 40;
	//for (std::vector<Play>::iterator i = s.availablePlays.begin(); i != s.availablePlays.end(); ++i)
	//{
	//	if (i->Color.compare("None") != 0)
	//	{
	//		n_avail++;
	//	}
	//	if (((i->Color.compare("Red") == 0) || (i->Color.compare("Yellow") == 0)) && i->Number == 12)
	//	{
	//		n_plays++;
	//	}
	//	else if (((i->Color.compare("Green") == 0) || (i->Color.compare("Blue") == 0)) && i->Number == 2)
	//	{
	//		n_plays++;
	//	}
	//}
	//n_scored = s.scoredPlays.size();
	//return (n_plays - n_avail + n_scored);
	int n_plays = 40;
	std::vector<std::string> colors = { "Red","Yellow","Green","Blue" };
	for (std::vector<std::string>::iterator c = colors.begin(); c != colors.end(); ++c)
	{
		if (calcNumberScoredInColor(*c) >= 5)
		{
			n_plays++;
		}
	}
	return (n_plays - NumberScored - NumberRemaining);
}

int PlayEval::calcNumberOfOpponentSlashes()
{
	int n_slashes = 0;
	for (std::vector<PlaySheet*>::iterator opp = o.begin(); opp != o.end(); ++opp)
	{
		if ((**opp).slashes > n_slashes)
		{
			n_slashes = (**opp).slashes;
		}
	}
	return(n_slashes);
}

int PlayEval::GetMaxOppScore()
{
	int score = 0;
	for (std::vector<PlaySheet*>::iterator opp = o.begin(); opp != o.end(); ++opp)
	{
		if ((**opp).score > score)
		{
			score = (**opp).score;
		}
	}
	return(score);
}

//void PlayEval::outputToSQLite(sqlite3* db)
//{
//	int rc;
//	char* zErrMsg = 0;
//
//	std::string sql = "insert into PlayEval (Game_id, Play_id, Eval_id, Player, Color, Number, NumberToSkip, "
//		" NumberScoredInColor, NumberRemainingInColor, NumberSkippedInColor, NumberScored, NumberRemaining, "
//		" NumberSkipped, NumberOfSlashes, NumberOfOpponentSlashes, NumberOfClosedColors, Score, OpponentScore)  values ( "
//		+ std::to_string(Game_id) + ", "
//		+ std::to_string(Play_id) + ", "
//		+ std::to_string(Eval_id) + ", '"
//		+ s.name + "', '"
//		+ p.Color + "', "
//		+ std::to_string(p.Number) + ", "
//		+ std::to_string(NumberToSkip) + ", "
//		+ std::to_string(NumberScoredInColor) + ", "
//		+ std::to_string(NumberRemainingInColor) + ", "
//		+ std::to_string(NumberSkippedInColor) + ", "
//		+ std::to_string(NumberScored) + ", "
//		+ std::to_string(NumberRemaining) + ", "
//		+ std::to_string(NumberSkipped) + ", "
//		+ std::to_string(NumberOfSlashes) + ", "
//		+ std::to_string(NumberOfOpponentSlashes) + ", "
//		+ std::to_string(NumberOfClosedColors) + ", "
//		+ std::to_string(Score) + ", "
//		+ std::to_string(OppScore) + ") ";
//
//	char* sql_ = const_cast<char*>(sql.c_str());
//	//std::cout << sql_;
//
//	rc = sqlite3_exec(db, sql_, 0, 0, &zErrMsg);
//
//
//}