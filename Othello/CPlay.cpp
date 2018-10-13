#include "StdAfx.h"
#include "CPlay.h"

CPlay::CPlay()
{
	round = 0;
	playerColor = black;
	for (int i = 0; i <= 8; i++)
		for (int j = 0; j <= 8; j++)
			boardArray[i][j] = empty;
	boardArray[4][4] = boardArray[5][5] = white;
	boardArray[4][5] = boardArray[5][4] = black;
}


CPlay::~CPlay()
{
}

bool CPlay::IsGameOver()
{
	if (round >= 64)
		return true;
	else
		return false;
}
//Reversed player and return player's color
int CPlay::ReverseColor() {
	if (playerColor == black)playerColor = white;
	else playerColor = black;
	return playerColor;
}

//only return the reversed color. It didn't do anything.
int CPlay::ReverseColor(int color) {
	if (color == black) return white;
	else return black;
}

//Reverse the color of specified point. If the point is empty, do nothing. Attention: 0 <= x <= 7, 0 <= y <= 7
int CPlay::ReverseColor(int x, int y)
{
	if (boardArray[x][y] == black)	boardArray[x][y] = white;
	else if (boardArray[x][y] == white) boardArray[x][y] = black;
	return boardArray[x][y];
}

// use this function to caculate the coordinates of the chess corresponding to the mouse placement
CPoint CPlay::CalChessView(CPoint point)
{
	int x = 0, y = 0;
	x = point.x / 100 * 100;
	y = point.y / 100 * 100;
	return CPoint(x, y);
}

CPoint CPlay::CalChessArrow(CPoint point)
{
	int x = 0, y = 0;
	x = point.x / 100;
	y = point.y / 100;
	return CPoint(x, y);
}
// using this function to check if player played a chess which can't reverse or in the place where a chess has been played
bool CPlay::IsInvalidPlay(CPoint point)
{
	bool boolen = 0;
	int chessPointX = CalChessView(point).x / 100, chessPointY = CalChessView(point).y / 100;
	int chessState = boardArray[chessPointX][chessPointY];
	for (int i = 0; i < 8; i++)
	{
		if (IsAdjChessDif(point) && chessState == 0)
		{
			boolen = false;
			break;
		}
		else
		{
			boolen = true;
			continue;
		}
	}
	
	return boolen;
}

// using this function to detecte whether adjacent chesses is different from it.
// If true, return true
bool CPlay::IsAdjChessDif(CPoint point)
{
	int chessPointX = CalChessView(point).x / 100, chessPointY = CalChessView(point).y / 100;
	int chessState = boardArray[chessPointX][chessPointY];

	if (boardArray[chessPointX - 1][chessPointY - 1] == ReverseColor(playerColor) ||
		boardArray[chessPointX][chessPointY - 1] == ReverseColor(playerColor) ||
		boardArray[chessPointX + 1][chessPointY - 1] == ReverseColor(playerColor) ||
		boardArray[chessPointX - 1][chessPointY] == ReverseColor(playerColor) ||
		boardArray[chessPointX + 1][chessPointY] == ReverseColor(playerColor) ||
		boardArray[chessPointX - 1][chessPointY + 1] == ReverseColor(playerColor) ||
		boardArray[chessPointX][chessPointY + 1] == ReverseColor(playerColor) ||
		boardArray[chessPointX + 1][chessPointY + 1] == ReverseColor(playerColor) )
		return true;
	else
		return false;
}


bool CPlay::IsAllowReverse(CPoint point, int i, int j)
{
	CPoint curPoint = CalChessArrow(point);
	int x = curPoint.x, y = curPoint.y, search = 0;
	while (x >= 1 && x <= 8 && y >= 1 && y <= 8)
	{
		x += i;
		y += j;
		/*
		if (boardArray[x][y] != empty)
		{
			//布尔值严重有问题
			//如果同颜色的棋子在隔壁，说明这个方向不行
			if (boardArray[x][y] == playerColor && search == 0)
				return false;
			//如果隔了一个或以上，说明可以
			else if (boardArray[x][y] == playerColor && search > 0)
			{
				ReverseColor(x, y);
				return true;
			}
			//同色棋子，继续搜
			else
				search++;
		}
		//如果搜到空位了，说明一直都没有符合条件的棋子，这个方向不行
		else
			return false;
			*/
		if (boardArray[x][y] == playerColor)
			return search > 0;
		else if (boardArray[x][y] == empty)
			return false;
		else
			search++;

	}
	//越界了都没找到，不存在
	return false;
}

// using this function to reverse chess color on board. Use with ReverseColor()
void CPlay::DoReverse(CPoint point, int i, int j)
{
	CPoint curPoint = CalChessArrow(point);
	int x = curPoint.x, y = curPoint.y;
	while (x >= 1 && x <= 8 && y >= 1 && y <= 8)
	{
		x += i;
		y += j;
		if (boardArray[x][y] == empty || boardArray[x][y] == playerColor)
			break;
		else
			ReverseColor(x, y);
	}

}


// using this function to reverse from 8 direction
bool CPlay::ReversiCheck(CPoint point)
{
	bool boolen = (IsAllowReverse(point, -1, 0)) || (IsAllowReverse(point, -1, -1)) ||
		(IsAllowReverse(point, 0, -1)) || (IsAllowReverse(point, 1, -1)) ||
		(IsAllowReverse(point, 1, 0)) || (IsAllowReverse(point, 1, 1)) ||
		(IsAllowReverse(point, 0, 1)) || (IsAllowReverse(point, -1, 1));
	return boolen;
}
