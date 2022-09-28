/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "stdafx.h"
//#include "fdm.h"
#include "Dlg_Options_Downloads.h"
#include "vmsRegisteredApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlg_Options_Downloads::CDlg_Options_Downloads(CWnd* pParent )
	: CDlg_Options_Page(CDlg_Options_Downloads::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_Options_Downloads)
	//}}AFX_DATA_INIT
}

void CDlg_Options_Downloads::DoDataExchange(CDataExchange* pDX)
{
	CDlg_Options_Page::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Options_Downloads)
	DDX_Control(pDX, IDC_WHENDEL, m_wndWhenDel);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_Options_Downloads, CDlg_Options_Page)
	//{{AFX_MSG_MAP(CDlg_Options_Downloads)
	ON_BN_CLICKED(IDC_USEWC, OnUsewc)
	//ON_BN_CLICKED(IDC_CHECKIFMAL2, OnCheckifmal2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlg_Options_Downloads::OnInitDialog()
{
	CDlg_Options_Page::OnInitDialog();

	CSpinButtonCtrl *pSpin = (CSpinButtonCtrl*) GetDlgItem (IDC_WC_SPIN);
	pSpin->SetRange (1, UD_MAXVAL);

	m_wndWhenDel.AddString (LS (L_ASK));
	m_wndWhenDel.AddString (LS (L_DONTDELFILE));
	m_wndWhenDel.AddString (LS (L_DELFILE));

	m_wndWhenDel.SetCurSel (_DldsMgr.m_enDDR);

	CheckDlgButton (IDC_DONTSAVELOGS, _App.DontSaveLogs () ? BST_CHECKED : BST_UNCHECKED);

	CheckDlgButton (IDC_AUTODEL, _DldsMgr.m_bAutoDelCompleted ? BST_CHECKED : BST_UNCHECKED);
	CheckDlgButton (IDC_DETAILEDLOG, _DldsMgr.m_bDetLog ? BST_CHECKED : BST_UNCHECKED);

	CheckDlgButton (IDC_SIZEINBYTES, _pwndDownloads->m_wndDownloads.m_tasks.m_bSizesInBytes ? BST_CHECKED : BST_UNCHECKED);

	CheckDlgButton (IDC_SHOWDLDDLG, _App.DownloadDialog_Use () ? BST_CHECKED : BST_UNCHECKED);

	DWORD dw = _App.FileWriteCacheSize () / 1024 / 1024;
	CheckDlgButton (IDC_USEWC, dw ? BST_CHECKED : BST_UNCHECKED);
	SetDlgItemInt (IDC_WC_SIZE, dw ? dw : 1, FALSE);

	CheckDlgButton (IDC_PREVENT_STANDBY, _App.PreventStandbyWhileDownloading () ? BST_CHECKED : BST_UNCHECKED);

	ApplyLanguage ();
	UpdateEnabled ();

	return TRUE;
}

CString CDlg_Options_Downloads::get_PageTitle()
{
	return LS (L_ESSENTIAL);
}

CString CDlg_Options_Downloads::get_PageShortTitle()
{
	return LS (L_ESSENTIAL);
}

BOOL CDlg_Options_Downloads::Apply()
{
	_DldsMgr.m_enDDR = (fsDeleteDownloadReaction) m_wndWhenDel.GetCurSel ();
	_DldsMgr.m_bAutoDelCompleted = IsDlgButtonChecked (IDC_AUTODEL) == BST_CHECKED;
	_DldsMgr.UseDetailedLog (IsDlgButtonChecked (IDC_DETAILEDLOG) == BST_CHECKED);
	BOOL bSIB = IsDlgButtonChecked (IDC_SIZEINBYTES) == BST_CHECKED;
	if (bSIB != _pwndDownloads->m_wndDownloads.m_tasks.m_bSizesInBytes)
	{
		_pwndDownloads->m_wndDownloads.m_tasks.m_bSizesInBytes = bSIB;
		_pwndDownloads->m_wndDownloads.m_tasks.OnForceUpdate ();
	}

	_App.DontSaveLogs (IsDlgButtonChecked (IDC_DONTSAVELOGS) == BST_CHECKED);

	BOOL bShow = IsDlgButtonChecked (IDC_SHOWDLDDLG) == BST_CHECKED;
	if (!bShow !=  !_App.DownloadDialog_Use ())
	{
		_App.DownloadDialog_Use (bShow);
		if (bShow)
			_App.DownloadDialog_DontAskOnHide (FALSE);
	}

	DWORD dw = 0;
	if (IsDlgButtonChecked (IDC_USEWC) == BST_CHECKED)
		dw = GetDlgItemInt (IDC_WC_SIZE, NULL, FALSE) * 1024 * 1024;
	_App.FileWriteCacheSize (dw);

	_App.PreventStandbyWhileDownloading (IsDlgButtonChecked (IDC_PREVENT_STANDBY) == BST_CHECKED);

	return TRUE;
}

void CDlg_Options_Downloads::ApplyLanguage()
{
	fsDlgLngInfo lnginfo [] =  {
		fsDlgLngInfo (IDC__LISTOFDLDS, L_LISTOFDLDS),
			fsDlgLngInfo (IDC__WHENDEL, L_WHENDEL),
			fsDlgLngInfo (IDC_AUTODEL, L_AUTODEL),
			fsDlgLngInfo (IDC_DETAILEDLOG, L_DETAILEDLOG),
			fsDlgLngInfo (IDC_SIZEINBYTES, L_SHOWSIZESINBYTES),
			fsDlgLngInfo (IDC_DONTSAVELOGS, L_DONTSAVELOGS),
			fsDlgLngInfo (IDC_SHOWDLDDLG, L_SHOWDLDDLG),
			fsDlgLngInfo (IDC_USEWC, L_USEWRITECACHE),
			fsDlgLngInfo (IDC__WC_MB, L_MB),
			fsDlgLngInfo (IDC_PREVENT_STANDBY, L_PREVENT_STANDBY_WHILE_DLDING),
			fsDlgLngInfo (IDC__FDM_COMMUNITY, L_FDMCOMMUNITY),
			fsDlgLngInfo (IDC_SWITCHTOOPINIONS2, L_SWITCHTOOPINIONS),
			fsDlgLngInfo (IDC_CHECKIFMAL2, L_CHECKNEWDLDIFITISMALICIOUS),
			fsDlgLngInfo (IDC_DISPLAYOPINIONS2, L_DISPLAYOPINIONSWHENDOWNLOADING),
			fsDlgLngInfo (IDC__S0, L_CONSIDER_DLD_AS_MAL_IF_MIN_0),
			fsDlgLngInfo (IDC__S1, L_CONSIDER_DLD_AS_MAL_IF_MIN_1),
	};

	_LngMgr.ApplyLanguage (this, lnginfo, sizeof (lnginfo) / sizeof (fsDlgLngInfo), 0);
}

void CDlg_Options_Downloads::UpdateEnabled()
{
	BOOL b;
	b = IsDlgButtonChecked (IDC_USEWC) == BST_CHECKED;
	UINT aIDs2 [] = {IDC_WC_SIZE, IDC_WC_SPIN, IDC__WC_MB};
	for (UINT i = 0; i < sizeof (aIDs2) / sizeof (UINT); i++)
		GetDlgItem (aIDs2 [i])->EnableWindow (b);
}

void CDlg_Options_Downloads::OnUsewc()
{
	UpdateEnabled ();
}
