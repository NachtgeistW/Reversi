#include "StdAfx.h"
#include "CPlay.h"

CPlay::CPlay()
{
	round = 0;
	curPlayer = black;
	for (int i = 0; i <= 8; i++)
		for (int j = 0; j <= 8; j++)
			boardArray[i][j] = empty;
	boardArray[4][4] = boardArray[5][5] = white;
	boardArray[4][5] = boardArray[5][4] = black;
}


CPlay::~CPlay()
{
}


int CPlay::GameMain(CPoint point)
{
	//屏幕坐标x和y，x对应的是列y对应的是行
	CPoint paw = CalChessArrow(point.x, point.y);
	int xa = paw.x, ya = paw.y;
	bool validPlay = false;
	if (!IsGameOver() && !IsChessExist(xa, ya) && GlobalReversiCheck(xa, ya, curPlayer))
	{
		//八方向搜索并转换棋子颜色
		if (IsAllowReverse(xa, ya, -1, 0, curPlayer)) { ChessPlayed(xa, ya, curPlayer); DoReverse(xa, ya, -1, 0); validPlay = true; }
		if (IsAllowReverse(xa, ya, -1, -1, curPlayer)) { ChessPlayed(xa, ya, curPlayer); DoReverse(xa, ya, -1, -1); validPlay = true; }
		if (IsAllowReverse(xa, ya, 0, -1, curPlayer)) { ChessPlayed(xa, ya, curPlayer); DoReverse(xa, ya, 0, -1); validPlay = true; }
		if (IsAllowReverse(xa, ya, 1, -1, curPlayer)) { ChessPlayed(xa, ya, curPlayer); DoReverse(xa, ya, 1, -1); validPlay = true; }
		if (IsAllowReverse(xa, ya, 1, 0, curPlayer)) { ChessPlayed(xa, ya, curPlayer); DoReverse(xa, ya, 1, 0); validPlay = true; }
		if (IsAllowReverse(xa, ya, 1, 1, curPlayer)) { ChessPlayed(xa, ya, curPlayer); DoReverse(xa, ya, 1, 1); validPlay = true; }
		if (IsAllowReverse(xa, ya, 0, 1, curPlayer)) { ChessPlayed(xa, ya, curPlayer); DoReverse(xa, ya, 0, 1); validPlay = true; }
		if (IsAllowReverse(xa, ya, -1, 1, curPlayer)) { ChessPlayed(xa, ya, curPlayer); DoReverse(xa, ya, -1, 1); validPlay = true; }

		//对手能否落子，如果可以，交换执棋方
		int check = curPlayer;
		for (int i = edgeLT; i <= edgeRD; i++)
		{
			for (int j = edgeLT; j <= edgeRD; j++)
				if (GlobalReversiCheck(i, j, ReverseColor(check)) && GetChessColor(i, j) == empty && validPlay)
				{
					curPlayer = ReverseColor(check);
					return 0;
				}
		}
		return 0;
	}
	else if (!IsGameOver() && !IsChessExist(xa, ya) && !GlobalReversiCheck(xa, ya, curPlayer))
		return INVALID;
	else if (IsGameOver())
		return GAMEOVER;
	return 0;
}

//If Game Over, return true;
int CPlay::IsGameOver()
{
	if (CountChessNum(black) + CountChessNum(white) >= 64 ||
		CountChessNum(black) == 0 || CountChessNum(white) == 0)
		return true;

	int validPointCount = 0;
	for (int i = 1; i <= 8; i++)
	{
		for (int j = 1; j <= 8; j++)
		{
			if ((GlobalReversiCheck(i, j, black)) || (GlobalReversiCheck(i, j, white)) && GetChessColor(i, j) == empty)
				validPointCount++;
		}
	}
	return validPointCount <= 0;

}

//Reversed player and return player's color
int CPlay::ReverseColor() {
	if (curPlayer == black)curPlayer = white;
	else curPlayer = black;
	return curPlayer;
}
//only return the reversed color. It didn't do anything.
int CPlay::ReverseColor(int color) {
	if (color == black) return white;
	else return black;
}
//Reverse the color of specified point. If the point is empty, do nothing. Attention: edgeLT <= x, y <= edgeRD
int CPlay::ReverseColor(int x, int y)
{
	if (boardArray[x][y] == black)	boardArray[x][y] = white;
	else if (boardArray[x][y] == white) boardArray[x][y] = black;
	return boardArray[x][y];
}

// using this function to caculate the coordinates of the chess corresponding to the mouse placement
CPoint CPlay::CalChessView(int xv, int yv)
{
	int x = 0, y = 0;
	x = xv / 100 * 100;
	y = yv / 100 * 100;
	return CPoint(x, y);
}

CPoint CPlay::CalChessArrow(int xv, int yv)
{
	int x = 0, y = 0;
	x = xv / 100;
	y = yv / 100;
	return CPoint(y, x);
}

// using this function to check if player played a chess in the place where a chess has been played. If existed, return true.
bool CPlay::IsChessExist(int xa, int ya)
{
	return boardArray[xa][ya] != 0;
}

// using this function to detecte whether adjacent chesses is different from it. If different, return true
bool CPlay::IsAdjChessDif(int xa, int ya, int i, int j, int color)
{
	return boardArray[xa + i][ya + j] == ReverseColor(color);
}

//i and j are the direction. To search for left side, set i as -1; for upper side, set j as -1.
bool CPlay::IsAllowReverse(int xa, int ya, int i, int j, int player)
{
	if (IsAdjChessDif(xa, ya, i, j, player) == false)
		return false;
	int x = xa, y = ya, search = 0;
	while (x >= edgeLT && x <= edgeRD && y >= edgeLT && y <= edgeRD)
	{
		x += i;
		y += j;
		if (boardArray[x][y] == player)
			return search > 0;
		else if (boardArray[x][y] == empty)
			return false;
		else
			search++;

	}
	//越界了都没找到，不存在
	return false;
}

// using this function to reverse from 8 direction. If a valid place be found, return true
bool CPlay::GlobalReversiCheck(int xa, int ya, int player)
{
	bool boolen = (IsAllowReverse(xa, ya, -1, 0, player)) || (IsAllowReverse(xa, ya, -1, -1, player)) ||
		(IsAllowReverse(xa, ya, 0, -1, player)) || (IsAllowReverse(xa, ya, 1, -1, player)) ||
		(IsAllowReverse(xa, ya, 1, 0, player)) || (IsAllowReverse(xa, ya, 1, 1, player)) ||
		(IsAllowReverse(xa, ya, 0, 1, player)) || (IsAllowReverse(xa, ya, -1, 1, player));
	return boolen;
}

// using this function to reverse chess color on board. Use with ReverseColor()
void CPlay::DoReverse(int xa, int ya, int i, int j)
{
	int x = xa, y = ya;
	while (x >= 1 && x <= 8 && y >= 1 && y <= 8)
	{
		x += i;
		y += j;
		if (boardArray[x][y] == empty || boardArray[x][y] == curPlayer)
			break;
		else
			ReverseColor(x, y);
	}
}

void CPlay::ChessPlayed(int xa, int ya, int color)
{
	boardArray[xa][ya] = color;
}

// using this function to count the number of specified chess.
int CPlay::CountChessNum(int color)
{
	int num = 0;
	for (int i = edgeLT; i <= edgeRD; i++)
		for (int j = edgeLT; j <= edgeRD; j++)
			if (boardArray[i][j] == color)
				num++;
	return num;
}


CString CPlay::Result()
{
	int blacknum = CountChessNum(black), whitenum = CountChessNum(white);
	if (blacknum > whitenum)
		return "黑方获胜！";
	else if (blacknum < whitenum)
		return "白方获胜！";
	else
		return "平局。";
}
