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

	BOOL b;
	CString str;

	b = AfxGetApp()->GetProfileInt("Webinterface", "AutoStart", 0) == 1;
	CheckDlgButton(IDC_SERV_AUTORUN, b ? BST_CHECKED: BST_UNCHECKED);

	UINT port = AfxGetApp()->GetProfileInt("Webinterface", "Port", 0);
	SetDlgItemInt(IDC_SERV_PORT, port, FALSE);

	b = AfxGetApp()->GetProfileInt("Webinterface", "UsePwd", 0) == 1;
	CheckDlgButton(IDC_SERV_USEPWD, b ? BST_CHECKED : BST_UNCHECKED);

	str = AfxGetApp()->GetProfileString("Webinterface", "Login");
	SetDlgItemText(IDC_SERV_USER, str);

	str = AfxGetApp()->GetProfileString("Webinterface", "Password");
	SetDlgItemText(IDC_SERV_PWD, str);

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
	BOOL b;

	b = IsDlgButtonChecked(IDC_SERV_AUTORUN) == BST_CHECKED;
	AfxGetApp()->WriteProfileInt("Webinterface", "AutoStart", b ? 1 : 0);

	b = IsDlgButtonChecked(IDC_SERV_USEPWD) == BST_CHECKED;
	AfxGetApp()->WriteProfileInt("Webinterface", "UsePwd", b ? 1 : 0);

	UINT port = GetDlgItemInt(IDC_SERV_PORT, NULL, FALSE);
	AfxGetApp()->WriteProfileInt("Webinterface", "Port", port);

	CString str;
	GetDlgItemText(IDC_SERV_USER, str);
	AfxGetApp()->WriteProfileString("Webinterface", "Login", str);

	GetDlgItemText(IDC_SERV_PWD, str);
	AfxGetApp()->WriteProfileString("Webinterface", "Password", str);

	if (_httpServer.is_Running() && _httpServer.get_Port() != (unsigned short)port)
	{
		_httpServer.Shutdown();
		_httpServer.set_Port((unsigned short)port);
		_httpServer.Start();
	}

	return TRUE;
}

void CDlg_Options_Webinterface::ApplyLanguage()
{
	//fsDlgLngInfo lnginfo [] =  {
	//	fsDlgLngInfo (IDC__TOUTSFORCONFS, L_TOUTSFORCONFS),
	//	fsDlgLngInfo (IDC__EXIT, L_EXIT),
	//	fsDlgLngInfo (IDC__SHUTDOWN, L_SHUTDOWN),
	//	fsDlgLngInfo (IDC__LAUNCHDLD, L_LAUNCHDLD),
	//	fsDlgLngInfo (IDC_ASKFORST, L_ASKFORST),
	//	fsDlgLngInfo (IDC_DISABLEWDTASKAFTEREXEC, L_DISABLEWHENDONEAFTEREXEC),
	//	fsDlgLngInfo (IDC__AUTOSAVE, L_AUTOSAVE),
	//};

	//_LngMgr.ApplyLanguage (this, lnginfo, sizeof (lnginfo) / sizeof (fsDlgLngInfo), 0);
}

//void CDlg_Options_Webinterface::OnDestroy()
//{
//	CDlg_Options_Page::OnDestroy();
//}
