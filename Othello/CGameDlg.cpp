#include "StdAfx.h"
#include "CGameDlg.h"
#include "resource.h"

CGameDlg::CGameDlg()
{
}


CGameDlg::~CGameDlg()
{
}
BEGIN_MESSAGE_MAP(CGameDlg, CDialog)
	ON_COMMAND(ID_NEWGAME, &CGameDlg::OnNewgame)
END_MESSAGE_MAP()


void CGameDlg::OnNewgame()
{
	// TODO: �ڴ���������������
	CGameDlg dlg;
	dlg.DoModal();
}
