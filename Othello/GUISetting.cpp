#include "StdAfx.h"
#include "MainFrm.h"
#include "GUISetting.h"
#include "CPlay.h"
#include "resource.h"
/*
如果出问题了，就按这些方法改
试着把CMFCStatusBar改成CStatusBar
*/

//set the status bar
void SetStatusBar(int blacknum, int whitenum, int curplayer)
{
	CString blackStatus;
	CString whiteStatus;
	blackStatus.Format("当前黑棋数：%d", blacknum);
	whiteStatus.Format("当前白棋数：%d", whitenum);

	CMainFrame * pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CMFCStatusBar * pStatus = &pFrame->m_wndStatusBar;
	if (pStatus)
	{
		//set text
		pStatus->SetPaneText(1, blackStatus);
		pStatus->SetPaneText(2, whiteStatus);
		
		//set current player
		if (curplayer == CPlay::black)
			pStatus->SetPaneText(3, "黑方的回合");
		else if (curplayer == CPlay::white)
			pStatus->SetPaneText(3, "白方的回合");

		//set widght
		pStatus->SetPaneInfo(1, ID_SEPARATOR, NULL, 180);
		pStatus->SetPaneInfo(2, ID_SEPARATOR, NULL, 180);
		pStatus->SetPaneInfo(3, ID_SEPARATOR, NULL, 180);

	}

}

void ShowNewGameDlg()
{
	CGameDlg dlg;
	dlg.DoModal();
}
