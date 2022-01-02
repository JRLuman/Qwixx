#include <iostream>
#include <vector>
#include <string> 
#include "plays.h"
#include "PlaySheet.h"

class PlayEval {
public:
	Play p;
	int NumberToSkip;
	int NumberScoredInColor;
	int NumberRemainingInColor;
	int NumberSkippedInColor;
	int NumberScored;
	int NumberRemaining;
	int NumberSkipped;
	int round;
	int NumberOfSlashes;
	int NumberOfOpponentSlashes;
	int NumberOfClosedColors;
	int Score;
	int OppScore;
	long int Game_id;
	long int Eval_id;
	long int Play_id;
	//void outputToSQLite(sqlite3*);


	PlayEval(Play pp, PlaySheet ss, std::vector<PlaySheet*> oo, int rr, int cc, long int gid, long int eid, long int pid)
	{
		p = pp; // play
		s = ss; //score shee
		o = oo; // opponent score sheets
		Game_id = gid;
		Eval_id = eid;
		Play_id = pid;

		NumberToSkip = calcNumberToSkip(&p,-1);
		NumberScoredInColor = calcNumberScoredInColor(p.Color);
		if (NumberScoredInColor == 0)
		{
			NumberToSkip++;
		}
		NumberRemainingInColor = calcNumberRemainingInColor(p.Color);
		NumberSkippedInColor = calcNumberSkippedInColor(p.Color);
		NumberScored = calcNumberScored();
		NumberRemaining = calcNumberRemaining();
		NumberSkipped = calcNumberSkipped();
		round = rr;
		NumberOfSlashes = s.slashes;
		NumberOfOpponentSlashes = calcNumberOfOpponentSlashes();
		NumberOfClosedColors = cc;
		Score = ss.score;
		OppScore = GetMaxOppScore();
	}
private:
	int calcNumberToSkip(Play*,int);
	int calcNumberScoredInColor(std::string);
	int calcNumberRemainingInColor(std::string);
	int calcNumberSkippedInColor(std::string);
	int calcNumberScored();
	int calcNumberRemaining();
	int calcNumberSkipped();
	int calcNumberOfOpponentSlashes();
	int GetMaxOppScore();
	int callback(void* , int , char** , char** );

	PlaySheet s;
	std::vector<PlaySheet*> o;
};

