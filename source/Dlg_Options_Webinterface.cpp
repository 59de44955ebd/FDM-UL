/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "stdafx.h"

#include "Dlg_Options_Webinterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlg_Options_Webinterface::CDlg_Options_Webinterface(CWnd* pParent )
	: CDlg_Options_Page(CDlg_Options_Webinterface::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_Options_General_Misc)
	//}}AFX_DATA_INIT
}

BEGIN_MESSAGE_MAP(CDlg_Options_Webinterface, CDlg_Options_Page)
	//{{AFX_MSG_MAP(CDlg_Options_Webinterface)
	//ON_BN_CLICKED(IDC_SERV_AUTORUN, OnAutorun)
	//ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlg_Options_Webinterface::OnInitDialog()
{
	CDlg_Options_Page::OnInitDialog();

	CheckDlgButton(IDC_SERV_AUTORUN, _App.Webinterface_AutoStart() ? BST_CHECKED: BST_UNCHECKED);
	SetDlgItemInt(IDC_SERV_PORT, _App.Webinterface_Port(), FALSE);
	CheckDlgButton(IDC_SERV_USEPWD, _App.Webinterface_UsePwd() ? BST_CHECKED : BST_UNCHECKED);
	SetDlgItemText(IDC_SERV_USER, _App.Webinterface_Login());
	SetDlgItemText(IDC_SERV_PWD, _App.Webinterface_Password());

	//ApplyLanguage ();

	return TRUE;
}

CString CDlg_Options_Webinterface::get_PageTitle()
{
	return LS(L_WEBINTERFACE);
}

CString CDlg_Options_Webinterface::get_PageShortTitle()
{
	return LS (L_WEBINTERFACE);
}

BOOL CDlg_Options_Webinterface::Apply()
{
	_App.Webinterface_AutoStart(IsDlgButtonChecked(IDC_SERV_AUTORUN) == BST_CHECKED);
	_App.Webinterface_UsePwd(IsDlgButtonChecked(IDC_SERV_USEPWD) == BST_CHECKED);

	UINT port = GetDlgItemInt(IDC_SERV_PORT, NULL, FALSE);
	_App.Webinterface_Port(port);

	CString str;
	GetDlgItemText(IDC_SERV_USER, str);
	_App.Webinterface_Login(str);
	GetDlgItemText(IDC_SERV_PWD, str);
	_App.Webinterface_Password(str);

	if (_httpServer.is_Running() && _httpServer.get_Port() != (unsigned short)port)
	{
		_httpServer.Shutdown();
		_httpServer.set_Port((unsigned short)port);
		_httpServer.Start();
	}

	return TRUE;
}

//TODO
//IDC_SERV_AUTORUN
//IDC_SERV_USEPWD
//...
//void CDlg_Options_Webinterface::ApplyLanguage()
//{
	//fsDlgLngInfo lnginfo [] =  {
	//	fsDlgLngInfo (IDC_SERV_AUTORUN, L_SERV_AUTORUN),
	//};
	//_LngMgr.ApplyLanguage (this, lnginfo, sizeof (lnginfo) / sizeof (fsDlgLngInfo), 0);
//}

//void CDlg_Options_Webinterface::OnDestroy()
//{
//	CDlg_Options_Page::OnDestroy();
//}
