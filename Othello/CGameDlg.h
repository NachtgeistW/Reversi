#pragma once
#include <afxwin.h>
class CGameDlg :
	public CDialog
{
public:
	CGameDlg();
	~CGameDlg();
	DECLARE_MESSAGE_MAP()
	afx_msg
	void OnNewgame();
};

