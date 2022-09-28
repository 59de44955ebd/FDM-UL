/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "FdmApp.h"
#include "Dlg_FindAdvanced.h"
#include "DownloadsWnd.h"
#include "vmsDialogHelper.h"

extern CDownloadsWnd* _pwndDownloads;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlgFindAdvanced::CDlgFindAdvanced(CWnd* pParent )
	: CDialog(CDlgFindAdvanced::IDD, pParent)
{
	//m_bTimeSet = FALSE;
	m_wndGroups.m_bHasAllGroupsItem = true;
}

void CDlgFindAdvanced::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFindAdvanced)
	DDX_Control(pDX, IDC_MINSIZEDIM, m_wndDim2);
	DDX_Control(pDX, IDC_MAXSIZEDIM, m_wndDim1);
	DDX_Control(pDX, IDC_GROUPS, m_wndGroups);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgFindAdvanced, CDialog)
	//{{AFX_MSG_MAP(CDlgFindAdvanced)
	ON_WM_CONTEXTMENU()
	ON_WM_HELPINFO()
	ON_COMMAND(ID_WHATISTHIS, OnWhatisthis)
	ON_CBN_SELCHANGE(IDC_GROUPS, OnSelchangeGroups)
	ON_BN_CLICKED(IDC_LISTOFDLDS, OnListofdlds)
	ON_BN_CLICKED(IDC_DELETED, OnDeleted)
	ON_BN_CLICKED(IDC_USESIZE, OnUsesize)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgFindAdvanced::OnInitDialog()
{
	CDialog::OnInitDialog();

	DWORD dwFlags = _App.Find_Flags ();

	if (dwFlags & SEARCHWH_LISTOFDLDS)
		CheckDlgButton (IDC_LISTOFDLDS, BST_CHECKED);

	if (dwFlags & SEARCHWH_DELETED)
		CheckDlgButton (IDC_DELETED, BST_CHECKED);

	m_wndGroups.Fill ();
	m_wndGroups.SelectGroup (NULL);

	if (dwFlags & SEARCHU_DLDGROUP)
		m_wndGroups.SelectGroupById (_App.Find_GroupId ());

	if (dwFlags & SEARCHU_TIME)
		CheckDlgButton (IDC_USETIME, BST_CHECKED);

	if (dwFlags & SEARCHU_FILESIZE)
		CheckDlgButton (IDC_USESIZE, BST_CHECKED);

	m_wndDim1.AddString (LS (L_B)); m_wndDim2.AddString (LS (L_B));
	m_wndDim1.AddString (LS (L_KB)); m_wndDim2.AddString (LS (L_KB));
	m_wndDim1.AddString (LS (L_MB)); m_wndDim2.AddString (LS (L_MB));

	vmsDialogHelper::SetDlgBytesGroup (this, _App.Find_FileSizeFrom (), IDC_MINSIZEVAL, IDC_MINSIZEDIM);
	vmsDialogHelper::SetDlgBytesGroup (this, _App.Find_FileSizeTo (), IDC_MAXSIZEVAL, IDC_MAXSIZEDIM);

	ApplyLanguage ();
	UpdateEnabled ();

	return TRUE;
}

void CDlgFindAdvanced::OnContextMenu(CWnd* , CPoint point)
{
	PrepareCHMgr (point);
	_CHMgr.ShowMenu ();
}

BOOL CDlgFindAdvanced::OnHelpInfo(HELPINFO* pHelpInfo)
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

void CDlgFindAdvanced::OnWhatisthis()
{
	_CHMgr.OnWT ();
}

void CDlgFindAdvanced::UpdateEnabled()
{
	BOOL b = IsDlgButtonChecked (IDC_LISTOFDLDS) == BST_CHECKED;
	b = b || IsDlgButtonChecked (IDC_DELETED) == BST_CHECKED;
	GetDlgItem (IDC__SEARCHINGROUP)->EnableWindow (b);
	GetDlgItem (IDC_GROUPS)->EnableWindow (b);

	b = IsDlgButtonChecked (IDC_USESIZE) == BST_CHECKED;
	GetDlgItem (IDC__MINIMUM)->EnableWindow (b);
	GetDlgItem (IDC_MINSIZEVAL)->EnableWindow (b);
	GetDlgItem (IDC_MINSIZEDIM)->EnableWindow (b);
	GetDlgItem (IDC__MAXIMUM)->EnableWindow (b);
	GetDlgItem (IDC_MAXSIZEVAL)->EnableWindow (b);
	GetDlgItem (IDC_MAXSIZEDIM)->EnableWindow (b);

	b = IsDlgButtonChecked (IDC_LISTOFDLDS) == BST_CHECKED;
	b = b || IsDlgButtonChecked (IDC_DELETED) == BST_CHECKED;
	//b = b || IsDlgButtonChecked (IDC_HISTOFDLDS) == BST_CHECKED;
	GetDlgItem (IDOK)->EnableWindow (b);
}

void CDlgFindAdvanced::ApplyLanguage()
{
	fsDlgLngInfo lnginfo [] =  {
		fsDlgLngInfo (IDC__FINDWHERE, L_FINDWHERE),
		fsDlgLngInfo (IDC_LISTOFDLDS, L_FINDINLISTOFDLDS),
		fsDlgLngInfo (IDC__SEARCHINGROUP, L_FINDINGROUP),
		fsDlgLngInfo (IDC_DELETED, L_FINDINDELETED),
		fsDlgLngInfo (IDC_USESIZE, L_FINDUSESIZE),
		fsDlgLngInfo (IDC__MINIMUM, L_MAXIMAL),
		fsDlgLngInfo (IDC__MAXIMUM, L_MINIMAL),
		fsDlgLngInfo (IDCANCEL, L_CANCEL),
	};

	_LngMgr.ApplyLanguage (this, lnginfo, sizeof (lnginfo) / sizeof (fsDlgLngInfo), L_FIND);
}

void CDlgFindAdvanced::PrepareCHMgr(CPoint point)
{
	fsCtrlContextHelp aCH1 [] = {
		fsCtrlContextHelp (IDC_LISTOFDLDS, LS (L_FINDLISTOFDLDSHERE)),
		fsCtrlContextHelp (IDC__SEARCHINGROUP, LS (L_FINDINGROUPHERE)),
		fsCtrlContextHelp (IDC_GROUPS, LS (L_FINDINGROUPHERE)),
		fsCtrlContextHelp (IDC_DELETED, LS (L_FINDDELETEDHERE)),
		fsCtrlContextHelp (IDC_USESIZE, LS (L_FINDUSESIZEHERE)),
		fsCtrlContextHelp (IDC__MINIMUM, LS (L_FINDMINSIZEHERE)),
		fsCtrlContextHelp (IDC_MINSIZEVAL, LS (L_FINDMINSIZEHERE)),
		fsCtrlContextHelp (IDC__MAXIMUM, LS (L_FINDMAXSIZEHERE)),
		fsCtrlContextHelp (IDC_MAXSIZEVAL, LS (L_FINDMAXSIZEHERE)),
		fsCtrlContextHelp (IDC_MINSIZEDIM, LS (L_DIMHERE)),
		fsCtrlContextHelp (IDC_MAXSIZEDIM, LS (L_DIMHERE)),
	};

    static fsCtrlContextHelp aCH [sizeof (aCH1) / sizeof (fsCtrlContextHelp)];
	CopyMemory (aCH, aCH1, sizeof (aCH));

	_CHMgr.PrepareContextMenu (this, point, aCH, sizeof (aCH) / sizeof (fsCtrlContextHelp));
}

void CDlgFindAdvanced::OnOK()
{
	BOOL bListOfDlds = IsDlgButtonChecked (IDC_LISTOFDLDS) == BST_CHECKED;
	BOOL bDeleted = IsDlgButtonChecked (IDC_DELETED) == BST_CHECKED;

	DWORD dwFlags = _App.Find_Flags ();

	dwFlags &= ~(SEARCHWH_LISTOFDLDS|SEARCHWH_DELETED); //|SEARCHWH_HISTOFDLDS

	if (bListOfDlds)
		dwFlags |= SEARCHWH_LISTOFDLDS;

	if (bDeleted)
		dwFlags |= SEARCHWH_DELETED;

	dwFlags &= ~SEARCHU_DLDGROUP;

	if (bListOfDlds || bDeleted)
	{
		if (m_wndGroups.GetSelectedGroup () != NULL)
		{
			dwFlags |= SEARCHU_DLDGROUP;
			_App.Find_GroupId (m_wndGroups.GetSelectedGroup ()->nId);
		}
	}

	if (IsDlgButtonChecked (IDC_USESIZE) == BST_CHECKED)
	{
		dwFlags |= SEARCHU_FILESIZE;

		UINT64 u;

		vmsDialogHelper::GetDlgBytesGroup (this, IDC_MINSIZEVAL, IDC_MINSIZEDIM, &u);
		_App.Find_FileSizeFrom (u);

		vmsDialogHelper::GetDlgBytesGroup (this, IDC_MAXSIZEVAL, IDC_MAXSIZEDIM, &u);
		_App.Find_FileSizeTo (u);
	}
	else
		dwFlags &= ~SEARCHU_FILESIZE;

	_App.Find_Flags (dwFlags);

	CDialog::OnOK();
}

void CDlgFindAdvanced::OnSelchangeGroups()
{

}

void CDlgFindAdvanced::OnListofdlds()
{
	UpdateEnabled ();
}

void CDlgFindAdvanced::OnDeleted()
{
	UpdateEnabled ();
}

void CDlgFindAdvanced::OnUsesize()
{
	UpdateEnabled ();
}
