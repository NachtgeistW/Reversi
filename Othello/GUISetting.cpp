#include "StdAfx.h"
#include "MainFrm.h"
#include "GUISetting.h"
#include "CPlay.h"
#include "resource.h"
/*
����������ˣ��Ͱ���Щ������
���Ű�CMFCStatusBar�ĳ�CStatusBar
*/

//set the status bar
void SetStatusBar(int blacknum, int whitenum, int curplayer)
{
	CString blackStatus;
	CString whiteStatus;
	blackStatus.Format("��ǰ��������%d", blacknum);
	whiteStatus.Format("��ǰ��������%d", whitenum);

	CMainFrame * pFrame = (CMainFrame*)AfxGetApp()->m_pMainWnd;
	CMFCStatusBar * pStatus = &pFrame->m_wndStatusBar;
	if (pStatus)
	{
		//set text
		pStatus->SetPaneText(1, blackStatus);
		pStatus->SetPaneText(2, whiteStatus);
		
		//set current player
		if (curplayer == CPlay::black)
			pStatus->SetPaneText(3, "�ڷ��Ļغ�");
		else if (curplayer == CPlay::white)
			pStatus->SetPaneText(3, "�׷��Ļغ�");

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
