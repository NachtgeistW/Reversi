#include "StdAfx.h"
#include "CPlay.h"


CPlay::CPlay()
{
	round = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			boardArray[i][j] = empty;
	boardArray[4][4] = boardArray[5][5] = white;
	boardArray[4][5] = boardArray[5][4] = black;
}


CPlay::~CPlay()
{
}

// use this function to caculate the coordinates of the chess corresponding to the mouse placement
CPoint CPlay::CalChessPoint(CPoint point)
{
	int x = 0, y = 0;
	x = point.x / 100 * 100;
	y = point.y / 100 * 100;
	return CPoint(x, y);
}

// using this function to check if player played a chess which can't reverse or in the place where a chess has been played
bool CPlay::IsInvalidPlay(CPoint point)
{
	bool boolen = 0;
	int chessState = boardArray[CalChessPoint(point).x / 100][CalChessPoint(point).y / 100];
	if (chessState != 0)
		boolen = true;
	else
		boolen = false;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//here is something wrong... fix it after getting up
			if ()
			{
				boolen = true;
				continue;
			}
			else
			{
				boolen = false;
				break;
			}
		}
	}
	return boolen;
}
