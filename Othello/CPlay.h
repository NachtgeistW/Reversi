#pragma once
class CPlay
{
private:
	int round;
	const static int black = 1, white = -1, empty = 0;
	int boardArray[8][8];
public:
	//the left and top edge of the board
public:
	CPlay();
	~CPlay();
	// use this function to caculate the coordinates of the pieces corresponding to the mouse placement
	CPoint CalChessPoint(CPoint point);
	// using this function to increase round count
	void IncRound(void) { round++; };
	// using this function to get the current number of round
	int GetRound() { return round; };
	// using this function to check if player played a chess out of rage or in the place where a chess has been played
	bool IsInvalidPlay(CPoint point);
};

