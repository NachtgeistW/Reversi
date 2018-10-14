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
	//��Ļ����x��y��x��Ӧ������y��Ӧ������
	CPoint paw = CalChessArrow(point.x, point.y);
	int xa = paw.x, ya = paw.y;
	if (IsAdjChessDif(xa, ya))
	{
		//�˷���������ת��������ɫ
		if (IsAllowReverse(xa, ya, -1, 0, curPlayer)) { ChessPlayed(xa, ya, curPlayer); DoReverse(xa, ya, -1, 0); }
		if (IsAllowReverse(xa, ya, -1, -1, curPlayer)) { ChessPlayed(xa, ya, curPlayer); DoReverse(xa, ya, -1, -1); }
		if (IsAllowReverse(xa, ya, 0, -1, curPlayer)) { ChessPlayed(xa, ya, curPlayer); DoReverse(xa, ya, 0, -1); }
		if (IsAllowReverse(xa, ya, 1, -1, curPlayer)) { ChessPlayed(xa, ya, curPlayer); DoReverse(xa, ya, 1, -1); }
		if (IsAllowReverse(xa, ya, 1, 0, curPlayer)) { ChessPlayed(xa, ya, curPlayer); DoReverse(xa, ya, 1, 0); }
		if (IsAllowReverse(xa, ya, 1, 1, curPlayer)) { ChessPlayed(xa, ya, curPlayer); DoReverse(xa, ya, 1, 1); }
		if (IsAllowReverse(xa, ya, 0, 1, curPlayer)) { ChessPlayed(xa, ya, curPlayer); DoReverse(xa, ya, 0, 1); }
		if (IsAllowReverse(xa, ya, -1, 1, curPlayer)) { ChessPlayed(xa, ya, curPlayer); DoReverse(xa, ya, -1, 1); }

		//�����ܷ����ӣ�������ԣ�����ִ�巽
		int check = curPlayer;
		for (int i = edgeLT; i <= edgeRD; i++)
		{
			for (int j = edgeLT; j <= edgeRD; j++)
				if (GlobalReversiCheck(i, j, ReverseColor(check)))
				{
					curPlayer = ReverseColor(curPlayer);
					return 0;
				}
		}
	}
	return 0;
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

//��Ļ����x��y��x��Ӧ������y��Ӧ�����У��������̱�����Ƿ���
// use this function to caculate the coordinates of the chess corresponding to the mouse placement
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
// using this function to check if player played a chess which can't reverse or in the place where a chess has been played
bool CPlay::IsInvalidPlay(int xa, int ya)
{
	bool boolen = 0;
	int chessPointX = xa, chessPointY = ya;
	int chessState = boardArray[chessPointX][chessPointY];
	for (int i = 0; i < 8; i++)
	{
		if (IsAdjChessDif(xa, ya) && chessState == 0)
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
bool CPlay::IsAdjChessDif(int xa, int ya)
{
	int chessPointX = xa, chessPointY = ya;
	int chessState = boardArray[chessPointX][chessPointY];

	if (boardArray[chessPointX - 1][chessPointY - 1] == ReverseColor(curPlayer) ||
		boardArray[chessPointX][chessPointY - 1] == ReverseColor(curPlayer) ||
		boardArray[chessPointX + 1][chessPointY - 1] == ReverseColor(curPlayer) ||
		boardArray[chessPointX - 1][chessPointY] == ReverseColor(curPlayer) ||
		boardArray[chessPointX + 1][chessPointY] == ReverseColor(curPlayer) ||
		boardArray[chessPointX - 1][chessPointY + 1] == ReverseColor(curPlayer) ||
		boardArray[chessPointX][chessPointY + 1] == ReverseColor(curPlayer) ||
		boardArray[chessPointX + 1][chessPointY + 1] == ReverseColor(curPlayer) )
		return true;
	else
		return false;
}

//i and j are the direction. To search for left side, set i as -1; for upper side, set j as -1.
bool CPlay::IsAllowReverse(int xa, int ya, int i, int j, int player)
{
	int x = xa, y = ya, search = 0;
	while (x >= 1 && x <= 8 && y >= 1 && y <= 8)
	{
		x += i;
		y += j;
		/*
		if (boardArray[x][y] != empty)
		{
			//����ֵ����������
			//���ͬ��ɫ�������ڸ��ڣ�˵�����������
			if (boardArray[x][y] == playerColor && search == 0)
				return false;
			//�������һ�������ϣ�˵������
			else if (boardArray[x][y] == playerColor && search > 0)
			{
				ReverseColor(x, y);
				return true;
			}
			//ͬɫ���ӣ�������
			else
				search++;
		}
		//����ѵ���λ�ˣ�˵��һֱ��û�з������������ӣ����������
		else
			return false;
			*/
		if (boardArray[x][y] == player)
			return search > 0;
		else if (boardArray[x][y] == empty)
			return false;
		else
			search++;

	}
	//Խ���˶�û�ҵ���������
	return false;
}

// using this function to reverse from 8 direction
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
