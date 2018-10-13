#pragma once

class CPlay
{
private:
	int playerColor;
	int round;
	int boardArray[9][9];
	const static int edgeLT = 0, edgeRD = 8;
public:
	CPlay();
	~CPlay();
	const static int black = 1, white = -1, empty = 0;

	bool IsGameOver();

	//Reverse player and return player's color
	int ReverseColor();
	//only return the reversed color. It didn't do anything.
	int ReverseColor(int color);
	//Reverse the color of specified point. If the point is empty, do nothing. Attention: 0 <= x <= 7, 0 <= y <= 7
	int ReverseColor(int x, int y);

	int GetPlayer() { return playerColor; }
	int GetChessColor(int x, int y) { return boardArray[x][y]; }
	// use this function to caculate the coordinates of the pieces corresponding to the mouse placement
	CPoint CalChessView(CPoint point);
	CPoint CalChessArrow(CPoint point);

	// using this function to increase round count
	void IncRound(void) { round++; };
	// using this function to get the current number of round
	int GetRound() { return round; };
	// using this function to check if player played a chess out of rage or in the place where a chess has been played
	bool IsInvalidPlay(CPoint point);
	// using this function to detecte whether adjacent chesses is different from it
	bool IsAdjChessDif(CPoint point);
	bool IsAllowReverse(CPoint point, int i, int j);
	// using this function to reverse chess color on board. Use with ReverseColor(int x, int y)
	void DoReverse(CPoint point, int i, int j);
	// using this function to reverse from 8 direction
	bool ReversiCheck(CPoint point);
};

