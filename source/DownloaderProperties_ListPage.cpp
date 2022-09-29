/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "FdmApp.h"
#include "DownloaderProperties_ListPage.h"
#include "DownloadsWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CDownloadsWnd* _pwndDownloads;

IMPLEMENT_DYNCREATE(CDownloaderProperties_ListPage, CPropertyPage)

CDownloaderProperties_ListPage::CDownloaderProperties_ListPage() : CPropertyPage(CDownloaderProperties_ListPage::IDD)
{
	m_psp.dwFlags |= PSP_USETITLE;
	m_psp.pszTitle = LS (L_ALLDLDS);
}

CDownloaderProperties_ListPage::~CDownloaderProperties_ListPage()
{
}

void CDownloaderProperties_ListPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDownloaderProperties_ListPage)
	DDX_Control(pDX, IDC_WHENDEL, m_wndWhenDel);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDownloaderProperties_ListPage, CPropertyPage)
	//{{AFX_MSG_MAP(CDownloaderProperties_ListPage)
	ON_CBN_SELCHANGE(IDC_WHENDEL, OnSelchangeWhendel)
	ON_BN_CLICKED(IDC_AUTODEL, OnAutodel)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_WHATISTHIS, OnWhatisthis)
	ON_WM_HELPINFO()
	ON_BN_CLICKED(IDC_DETAILEDLOG, OnDetailedlog)
	ON_BN_CLICKED(IDC_SIZEINBYTES, OnSizeinbytes)
	ON_BN_CLICKED(IDC_SHOWDLDDLG, OnShowdlddlg)
	ON_BN_CLICKED(IDC_DONTSAVELOGS, OnDontsavelogs)
	ON_BN_CLICKED(IDC_USEWC, OnUsewc)
	ON_EN_CHANGE(IDC_WC_SIZE, OnChangeWcSize)
	ON_BN_CLICKED(IDC_PREVENT_STANDBY, OnPreventStandby)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDownloaderProperties_ListPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

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

void CDownloaderProperties_ListPage::OnSelchangeWhendel()
{
	SetModified ();
}

void CDownloaderProperties_ListPage::OnAutodel()
{
	SetModified ();
}

BOOL CDownloaderProperties_ListPage::OnApply()
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

	return CPropertyPage::OnApply();
}

void CDownloaderProperties_ListPage::OnContextMenu(CWnd* , CPoint point)
{
	PrepareCHMgr (point);
	_CHMgr.ShowMenu ();
}

void CDownloaderProperties_ListPage::OnWhatisthis()
{
	_CHMgr.OnWT ();
}

void CDownloaderProperties_ListPage::ApplyLanguage()
{
	fsDlgLngInfo lnginfo [] =
	{
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
	};

	_LngMgr.ApplyLanguage (this, lnginfo, sizeof (lnginfo) / sizeof (fsDlgLngInfo), 0);
}

BOOL CDownloaderProperties_ListPage::OnHelpInfo(HELPINFO* pHelpInfo)
{
	RECT rc;
	CWnd *pItem = GetDlgItem (pHelpInfo->iCtrlId);
	if (pItem == NULL)
		return TRUE;
	pItem->GetWindowRect (&rc);
	if (PtInRect (&rc, pHelpInfo->MousePos) == FALSE)
	{
		pHelpInfo->MousePos.x = rc.left + (rc.right - rc.left) / 2;
		pHelpInfo->MousePos.y = rc.top + (rc.bottom - rc.top) / 2;
	}
	PrepareCHMgr (pHelpInfo->MousePos);
	_CHMgr.OnWT ();
	return TRUE;
}

void CDownloaderProperties_ListPage::PrepareCHMgr(CPoint point)
{
	fsCtrlContextHelp aCH1 [] = {
		fsCtrlContextHelp (IDC__WHENDEL, LS (L_WHENDELHERE)),
		fsCtrlContextHelp (IDC_WHENDEL, LS (L_WHENDELHERE)),
		fsCtrlContextHelp (IDC_AUTODEL, LS (L_AUTODELHERE)),
		fsCtrlContextHelp (IDC_DETAILEDLOG, LS (L_DETAILEDLOGHERE)),
		fsCtrlContextHelp (IDC_SIZEINBYTES, LS (L_SIZEINBYTESHERE)),
		fsCtrlContextHelp (IDC_DONTSAVELOGS, LS (L_DONTSAVELOGS_HERE)),
		fsCtrlContextHelp (IDC_SHOWDLDDLG, LS (L_SHOWDLDDLG_HERE)),
		fsCtrlContextHelp (IDC_USEWC, LS (L_USEWRITECACHE_HERE)),
		fsCtrlContextHelp (IDC_WC_SIZE, LS (L_USEWRITECACHE_HERE)),
		fsCtrlContextHelp (IDC__WC_MB, LS (L_USEWRITECACHE_HERE)),
	};

    static fsCtrlContextHelp aCH [sizeof (aCH1) / sizeof (fsCtrlContextHelp)];
	CopyMemory (aCH, aCH1, sizeof (aCH));

	_CHMgr.PrepareContextMenu (this, point, aCH, sizeof (aCH) / sizeof (fsCtrlContextHelp));
}

void CDownloaderProperties_ListPage::OnDetailedlog()
{
	SetModified ();
}

void CDownloaderProperties_ListPage::OnSizeinbytes()
{
	SetModified ();
}

void CDownloaderProperties_ListPage::UpdateEnabled()
{
	BOOL b;
	b = IsDlgButtonChecked (IDC_USEWC) == BST_CHECKED;
	UINT aIDs2 [] = {IDC_WC_SIZE, IDC_WC_SPIN, IDC__WC_MB};
	for (int i = 0; i < sizeof (aIDs2) / sizeof (UINT); i++)
		GetDlgItem (aIDs2 [i])->EnableWindow (b);
}

void CDownloaderProperties_ListPage::OnShowdlddlg()
{
	SetModified ();
}

void CDownloaderProperties_ListPage::OnDontsavelogs()
{
	SetModified ();
}

void CDownloaderProperties_ListPage::OnUsewc()
{
	UpdateEnabled ();
	SetModified ();
}

void CDownloaderProperties_ListPage::OnChangeWcSize()
{
	SetModified ();
}

void CDownloaderProperties_ListPage::OnPreventStandby()
{
	SetModified ();
}
