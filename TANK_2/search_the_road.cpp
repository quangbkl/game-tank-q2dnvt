#include "search_the_road.h"

bool isValid(int row, int col) {
	return (row >= 0) && (row < ROW) &&
		(col >= 0) && (col < COL);
}

bool isUnBlocked(int grid[][COL], int row, int col) {
	if (grid[row][col] == 1)
		return (true);
	else
		return (false);
}

bool isDestination(int row, int col, Pair dest) {
	if (row == dest.first && col == dest.second)
		return (true);
	else
		return (false);
}

double calculateHValue(int row, int col, Pair dest) {
	return ((double)sqrt((row - dest.first)*(row - dest.first)
		+ (col - dest.second)*(col - dest.second)));
}

stack<Pair> tracePath(cell cellDetails[][COL], Pair dest) {
	int row = dest.first;
	int col = dest.second;

	stack<Pair> Path;

	while (!(cellDetails[row][col].parent_i == row
		&& cellDetails[row][col].parent_j == col))
	{
		Path.push(make_pair(row, col));
		int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}

	Path.push(make_pair(row, col));

	return Path;
}

stack<Pair> aStarSearch(int grid[][COL], Pair src, Pair dest) {
	stack<Pair> Path;
	if (isValid(src.first, src.second) == false)
	{
		printf("Source is invalid\n");
		return Path;
	}

	if (isValid(dest.first, dest.second) == false)
	{
		printf("Destination is invalid\n");
		return Path;
	}

	if (isUnBlocked(grid, src.first, src.second) == false ||
		isUnBlocked(grid, dest.first, dest.second) == false)
	{
		printf("Source or the destination is blocked\n");
		return Path;
	}

	if (isDestination(src.first, src.second, dest) == true)
	{
		printf("We are already at the destination\n");
		Path.push(src);
		return Path;
	}

	bool closedList[ROW][COL];
	memset(closedList, false, sizeof(closedList));

	cell cellDetails[ROW][COL];

	int i, j;

	for (i = 0; i<ROW; i++)
	{
		for (j = 0; j<COL; j++)
		{
			cellDetails[i][j].f = FLT_MAX;
			cellDetails[i][j].g = FLT_MAX;
			cellDetails[i][j].h = FLT_MAX;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}

	i = src.first, j = src.second;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;

	set<pPair> openList;

	openList.insert(make_pair(0.0, make_pair(i, j)));

	bool foundDest = false;

	while (!openList.empty())
	{
		pPair p = *openList.begin();

		openList.erase(openList.begin());

		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;

		double gNew, hNew, fNew;

		if (isValid(i - 1, j) == true)
		{

			if (isDestination(i - 1, j, dest) == true)
			{
				cellDetails[i - 1][j].parent_i = i;
				cellDetails[i - 1][j].parent_j = j;
				foundDest = true;
				return tracePath(cellDetails, dest);
			}

			else if (closedList[i - 1][j] == false &&
				isUnBlocked(grid, i - 1, j) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i - 1, j, dest);
				fNew = gNew + hNew;

				if (cellDetails[i - 1][j].f == FLT_MAX ||
					cellDetails[i - 1][j].f > fNew)
				{
					openList.insert(make_pair(fNew,
						make_pair(i - 1, j)));

					cellDetails[i - 1][j].f = fNew;
					cellDetails[i - 1][j].g = gNew;
					cellDetails[i - 1][j].h = hNew;
					cellDetails[i - 1][j].parent_i = i;
					cellDetails[i - 1][j].parent_j = j;
				}
			}
		}

		if (isValid(i + 1, j) == true)
		{
			if (isDestination(i + 1, j, dest) == true)
			{
				cellDetails[i + 1][j].parent_i = i;
				cellDetails[i + 1][j].parent_j = j;
				foundDest = true;
				return tracePath(cellDetails, dest);
			}
			else if (closedList[i + 1][j] == false &&
				isUnBlocked(grid, i + 1, j) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i + 1, j, dest);
				fNew = gNew + hNew;

				if (cellDetails[i + 1][j].f == FLT_MAX ||
					cellDetails[i + 1][j].f > fNew)
				{
					openList.insert(make_pair(fNew, make_pair(i + 1, j)));
					cellDetails[i + 1][j].f = fNew;
					cellDetails[i + 1][j].g = gNew;
					cellDetails[i + 1][j].h = hNew;
					cellDetails[i + 1][j].parent_i = i;
					cellDetails[i + 1][j].parent_j = j;
				}
			}
		}

		//----------- 3rd Successor (East) ------------

		if (isValid(i, j + 1) == true)
		{
			if (isDestination(i, j + 1, dest) == true)
			{
				cellDetails[i][j + 1].parent_i = i;
				cellDetails[i][j + 1].parent_j = j;
				foundDest = true;
				return tracePath(cellDetails, dest);
			}

			else if (closedList[i][j + 1] == false &&
				isUnBlocked(grid, i, j + 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i, j + 1, dest);
				fNew = gNew + hNew;

				if (cellDetails[i][j + 1].f == FLT_MAX ||
					cellDetails[i][j + 1].f > fNew)
				{
					openList.insert(make_pair(fNew,
						make_pair(i, j + 1)));

					cellDetails[i][j + 1].f = fNew;
					cellDetails[i][j + 1].g = gNew;
					cellDetails[i][j + 1].h = hNew;
					cellDetails[i][j + 1].parent_i = i;
					cellDetails[i][j + 1].parent_j = j;
				}
			}
		}

		//----------- 4th Successor (West) ------------

		if (isValid(i, j - 1) == true)
		{
			if (isDestination(i, j - 1, dest) == true)
			{
				cellDetails[i][j - 1].parent_i = i;
				cellDetails[i][j - 1].parent_j = j;
				foundDest = true;
				return tracePath(cellDetails, dest);
			}

			else if (closedList[i][j - 1] == false &&
				isUnBlocked(grid, i, j - 1) == true)
			{
				gNew = cellDetails[i][j].g + 1.0;
				hNew = calculateHValue(i, j - 1, dest);
				fNew = gNew + hNew;

				if (cellDetails[i][j - 1].f == FLT_MAX ||
					cellDetails[i][j - 1].f > fNew)
				{
					openList.insert(make_pair(fNew,
						make_pair(i, j - 1)));

					cellDetails[i][j - 1].f = fNew;
					cellDetails[i][j - 1].g = gNew;
					cellDetails[i][j - 1].h = hNew;
					cellDetails[i][j - 1].parent_i = i;
					cellDetails[i][j - 1].parent_j = j;
				}
			}
		}
	}
	if (foundDest == false)
		printf("Failed to find the Destination Cell\n");
	return Path;
}

Pair findPositionMove(int grid[][COL], int srcX, int srcY, int destX, int destY) {
	Pair pos1 = make_pair(destX, destY);
	Pair pos2 = make_pair(destX, destY);

	while (true) {
		bool return_1 = true;
		bool return_2 = true;
		if (srcX < pos1.first) {
			if (grid[pos1.first - 1][pos1.second] == 1) {
				pos1.first--;
				return_1 = false;
			}
		}
		else if (srcX > pos1.first) {
			if (grid[pos1.first + 1][pos1.second] == 1) {
				pos1.first++;
				return_1 = false;
			}
		}
		if (srcY < pos2.second) {
			if (grid[pos2.first][pos2.second - 1] == 1) {
				pos2.second--;
				return_2 = false;
			}
		}
		else if (srcY > pos2.second) {
			if (grid[pos2.first][pos2.second + 1] == 1) {
				pos2.second++;
				return_2 = false;
			}
		}
		if (return_1 && return_2)
			break;
	}

	int d_1 = abs(pos1.first - srcX) + abs(pos1.second - srcY);
	int d_2 = abs(pos2.first - srcX) + abs(pos2.second - srcY);
	if (d_1 < d_2) {
		return pos1;
	}
	return pos2;
}

string findTheDirectionMove(int grid[][COL], int srcX, int srcY, int destX, int destY) {
	Pair src = make_pair(srcX, srcY);
	Pair dest = findPositionMove(grid, srcX, srcY, destX, destY);

	stack<Pair> Path;
	Path = aStarSearch(grid, src, dest);

	if (Path.empty()) {
		return "none";
	}
	Path.pop();
	if (!Path.empty()) {
		pair<int, int> p = Path.top();
		Path.pop();
		int posX = p.first;
		int posY = p.second;
		if (posX > srcX && posY == srcY)
			return "down";
		if (posX < srcX && posY == srcY)
			return "up";
		if (posY > srcY && posX == srcX)
			return "right";
		if (posY < srcY && posX == srcX)
			return "left";
	}
	return "kill";
}