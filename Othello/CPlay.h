#pragma once

class CPlay
{
private:
	int curPlayer;
	int round;
	int boardArray[9][9];
	const static int edgeLT = 1, edgeRD = 8;
public:
	CPlay();
	~CPlay();
	const static int black = 1, white = -1, empty = 0;

	//the main function of game
	int GameMain(CPoint point);

	bool IsGameOver();

	//Reverse player and return player's color
	int ReverseColor();
	//only return the reversed color. It didn't do anything.
	int ReverseColor(int color);
	//Reverse the color of specified point. If the point is empty, do nothing. Attention: edgeLT <= x, y <= edgeRD
	int ReverseColor(int x, int y);

	int GetPlayer() { return curPlayer; }
	int GetChessColor(int xa, int ya) { return boardArray[xa][ya]; }
	// use this function to caculate the coordinates of the pieces corresponding to the mouse placement
	CPoint CalChessView(int xv, int yv);
	CPoint CalChessArrow(int xv, int yv);

	// using this function to increase round count
	void IncRound(void) { round++; };
	// using this function to get the current number of round
	int GetRound() { return round; };
	// using this function to check if player played a chess out of rage or in the place where a chess has been played
	bool IsInvalidPlay(int xa, int ya);
	// using this function to detecte whether adjacent chesses is different from it
	bool IsAdjChessDif(int xa, int ya);
	bool IsAllowReverse(int xa, int ya, int i, int j, int player);
	// using this function to reverse chess color on board. Use with ReverseColor(int x, int y)
	void DoReverse(int xa, int ya, int i, int j);
	// using this function to reverse from 8 direction
	bool GlobalReversiCheck(int xa, int ya, int player);
	void ChessPlayed(int xa, int ya, int color);
};

