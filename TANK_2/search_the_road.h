#pragma once
//Thuat toan copy tai https://www.geeksforgeeks.org/a-search-algorithm/
#include <iostream>
#include <cmath>
#include <stack>
#include <set>

using namespace std;

#define ROW 13
#define COL 16

typedef pair<int, int> Pair;

typedef pair< double, pair<int, int> > pPair;

struct cell {
	int parent_i, parent_j;
	double f, g, h;
};


bool isValid(int row, int col);

bool isUnBlocked(int grid[][COL], int row, int col);

bool isDestination(int row, int col, Pair dest);

double calculateHValue(int row, int col, Pair dest);

stack<Pair> tracePath(cell cellDetails[][COL], Pair dest);

stack<Pair> aStarSearch(int grid[][COL], Pair src, Pair dest);

string findTheDirectionMove(int grid[][COL], int srcX, int srcY, int destX, int destY);