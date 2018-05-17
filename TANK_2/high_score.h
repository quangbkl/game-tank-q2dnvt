#ifndef HIGH_SCORE
#define HIGH_SCORE

#include <iostream>
#include <fstream>

using namespace std;

static ifstream readFileHighScore;
static ofstream writeFileHighScore;

int getNumberHighScore();
string getHighScore();
string getHighScoreUser();
bool setHighScore(int _numScore, string username);	//Tra ve true neu _numScore > HighScore

#endif // !HIGH_SCORE
