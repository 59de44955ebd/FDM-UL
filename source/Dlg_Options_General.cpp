/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "Dlg_Options_General.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlg_Options_General::CDlg_Options_General(CWnd* pParent )
	: CDlg_Options_Page (CDlg_Options_General::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_Options_General)

	//}}AFX_DATA_INIT
}

void CDlg_Options_General::DoDataExchange(CDataExchange* pDX)
{
	CDlg_Options_Page::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Options_General)
	//DDX_Control(pDX, IDC_SKIN2, m_wndSkins);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_Options_General, CDlg_Options_Page)
	//{{AFX_MSG_MAP(CDlg_Options_General)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlg_Options_General::OnInitDialog()
{
	CDlg_Options_Page::OnInitDialog();

	CMainFrame *pFrame = (CMainFrame*) AfxGetApp ()->m_pMainWnd;

	CheckDlgButton (IDC_AUTOSTART, _AutorunMgr.IsAutoStart () ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton (IDC_STARTMINIMIZED, _App.Prg_StartMinimized () ? BST_CHECKED : BST_UNCHECKED);

	CheckDlgButton (IDC_MINTOTRAY, pFrame->m_bMinToTray ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton (IDC_CLOSEASMINIMIZE, pFrame->m_bCloseAsMinimize ? BST_CHECKED : BST_UNCHECKED);

	//SetDlgItemText (IDC_UPDATEURL, _UpdateMgr.m_strUpdateUrl);
	//CheckRadioButton (IDC_AUTOUPDATES_INSTALL, IDC_AUTOUPDATES_TURNOFF,
	//	IDC_AUTOUPDATES_INSTALL + _UpdateMgr.m_enAUT);

	//m_wndSkins.AddString (LS (L_NEWSTYLE));
	//for (int i = 0; i < _SkinMgr.get_Count (); i++)
	//{
	//	CString str = _SkinMgr.get_Skin (i)->strName;
	//	if (str.CompareNoCase ("Old Style") == 0)
	//		str = LS (L_OLDSTYLE);
	//	m_wndSkins.AddString (str);
	//}
	//m_wndSkins.SetCurSel (_SkinMgr.get_Current ()+1);

	//DWORD dw = _App.Skin_Flags ();
	//CheckDlgButton (IDC_ALLOWICONS2, dw & SM_ALLOWICONS ? BST_CHECKED : BST_UNCHECKED);
	//CheckDlgButton (IDC_ALLOWBITMAPS2, dw & SM_ALLOWBITMAPS ? BST_CHECKED : BST_UNCHECKED);

	ApplyLanguage ();

	return TRUE;

}

CString CDlg_Options_General::get_PageTitle()
{
	return LS (L_ESSENTIAL);
}

CString CDlg_Options_General::get_PageShortTitle()
{
	return LS (L_ESSENTIAL);
}

BOOL CDlg_Options_General::Apply()
{
	CMainFrame *pFrame = (CMainFrame*) AfxGetApp ()->m_pMainWnd;

	_AutorunMgr.SetAutoStart (IsDlgButtonChecked (IDC_AUTOSTART) == BST_CHECKED);

	_App.Prg_StartMinimized (IsDlgButtonChecked (IDC_STARTMINIMIZED) == BST_CHECKED);

	pFrame->m_bCloseAsMinimize = IsDlgButtonChecked (IDC_CLOSEASMINIMIZE) == BST_CHECKED;
	pFrame->m_bMinToTray = IsDlgButtonChecked (IDC_MINTOTRAY) == BST_CHECKED;

	return TRUE;
}

void CDlg_Options_General::ApplyLanguage()
{
	fsDlgLngInfo lnginfo [] =  {
		fsDlgLngInfo (IDC__STARTUP, L_STARTUP),
		fsDlgLngInfo (IDC_AUTOSTART, L_AUTOSTART),
		fsDlgLngInfo (IDC_STARTMINIMIZED, L_STARTMINIMIZED),
		fsDlgLngInfo (IDC__SYSTEM, L_SYSTEM),
		fsDlgLngInfo (IDC_MINTOTRAY, L_MINTOTRAY),
		fsDlgLngInfo (IDC_CLOSEASMINIMIZE, L_CLOSEASMINIMIZE),
	};

	_LngMgr.ApplyLanguage (this, lnginfo, sizeof (lnginfo) / sizeof (fsDlgLngInfo), 0);
}
