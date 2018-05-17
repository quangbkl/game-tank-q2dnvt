#include "high_score.h"
#include "number_to_string.h"

int getNumberHighScore() {
	int resultHighScore = 0;
	readFileHighScore.open("data_game/high_score_point.txt");
	if (readFileHighScore.is_open()) {
		readFileHighScore >> resultHighScore; // 	lay dl tu file gan vao 1 bien
	}
	readFileHighScore.close();
	return resultHighScore;
}
string getHighScore() {
	int resultHighScore = getNumberHighScore();
	if (resultHighScore < 10)
		return ("0" + numberToString(resultHighScore));
	else
		return numberToString(resultHighScore);
}

string getHighScoreUser() {
	string resultName = "Q2DNVT";
	readFileHighScore.open("data_game/high_score_user.txt");
	if (readFileHighScore.is_open()) {
		//readFileHighScore >> resultName; // 	lay dl tu file gan vao 1 bien
		getline(readFileHighScore, resultName);	//Get ten xai getline
	}
	readFileHighScore.close();
	return resultName;
}

bool setHighScore(int _numScore, string username) {
	int _highScore = getNumberHighScore();
	if (_numScore > _highScore) {
		writeFileHighScore.open("data_game/high_score_point.txt");
		if (writeFileHighScore.is_open()) {
			writeFileHighScore << _numScore;
		}
		writeFileHighScore.close();

		//Ghi username
		writeFileHighScore.open("data_game/high_score_user.txt");
		if (writeFileHighScore.is_open()) {
			writeFileHighScore << username;
		}
		writeFileHighScore.close();
		return true;
	}
	return false;
}
