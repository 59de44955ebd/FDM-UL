/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "stdafx.h"
//#include "fdm.h"
#include "Dlg_ProgramOptions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CProgramOptions::CProgramOptions(CWnd* pParent, LPCSTR pszStartPage)
	: CDlg_Options(pParent, pszStartPage)
{
	//{{AFX_DATA_INIT(CDlgProgramOptions)
	//}}AFX_DATA_INIT
}

void CProgramOptions::DoDataExchange(CDataExchange* pDX)
{
	CDlg_Options::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProgramOptions)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CProgramOptions, CDlg_Options)
	//{{AFX_MSG_MAP(CDlgProgramOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CProgramOptions::InitializeData()
{
	LPOPTIONS_PAGES_TREE pt = m_tPages->AddLeaf (LS (L_GENERAL));
	pt->AddLeaf (&m_general);
	pt->AddLeaf (&m_notifications);
	pt->AddLeaf (&m_general_misc);
	pt->AddLeaf (&m_webinterface);

	pt = m_tPages->AddLeaf (LS (L_DOWNLOADS));
	pt->AddLeaf (&m_downloads);
	pt->AddLeaf (&m_downloads_timelimit);
	pt->AddLeaf (&m_downloads_newdld);
	pt->AddLeaf (&m_downloads_network);

	pt->AddLeaf (&m_sitemgr);
}

BOOL CProgramOptions::OnInitDialog()
{
	CDlg_Options::OnInitDialog();
	SetWindowText (LS (L_SETTINGS));
	return TRUE;
}
