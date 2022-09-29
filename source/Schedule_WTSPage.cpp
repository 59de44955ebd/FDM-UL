/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "FdmApp.h"
#include "Schedule_WTSPage.h"
#include "fsScheduleMgr.h"
#include "DownloadsWnd.h"
#include "system.h"

extern CDownloadsWnd* _pwndDownloads;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CSchedule_WTSPage, CPropertyPage)

CSchedule_WTSPage::CSchedule_WTSPage() : CPropertyPage(CSchedule_WTSPage::IDD)
{
	m_psp.dwFlags |= PSP_USETITLE;
	m_psp.pszTitle = LS (L_WTS);
}

CSchedule_WTSPage::~CSchedule_WTSPage()
{
}

void CSchedule_WTSPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSchedule_WTSPage)
	DDX_Control(pDX, IDC_UNSELDLDS, m_wndUnselDlds);
	DDX_Control(pDX, IDC_SELDLDS, m_wndSelDlds);
	DDX_Control(pDX, IDC_TUM, m_wndTUM);
	DDX_Control(pDX, IDC_TOUNSEL, m_btnToUnsel);
	DDX_Control(pDX, IDC_TOSEL, m_btnToSel);
	DDX_Control(pDX, IDC_SHUTDOWNTYPE, m_wndShutdownType);
	DDX_Control(pDX, IDC_CHOOSENAME, m_btnChoose);
	DDX_Control(pDX, IDC_WTS, m_wndWTS);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSchedule_WTSPage, CPropertyPage)
	//{{AFX_MSG_MAP(CSchedule_WTSPage)
	ON_CBN_SELCHANGE(IDC_WTS, OnSelchangeWts)
	ON_EN_CHANGE(IDC_PROGNAME, OnChangeProgname)
	ON_EN_CHANGE(IDC_ARGUMENTS, OnChangeArguments)
	ON_BN_CLICKED(IDC_CHOOSENAME, OnChoosename)
	ON_NOTIFY(NM_CLICK, IDC_UNSELDLDS, OnClickUnseldlds)
	ON_NOTIFY(NM_CLICK, IDC_SELDLDS, OnClickSeldlds)
	ON_BN_CLICKED(IDC_TOSEL, OnTosel)
	ON_BN_CLICKED(IDC_TOUNSEL, OnTounsel)
	ON_CBN_SELCHANGE(IDC_TUM, OnSelchangeTum)
	ON_CBN_SELCHANGE(IDC_SHUTDOWNTYPE, OnSelchangeShutdowntype)
	ON_BN_CLICKED(IDC_FORCEEXIT, OnForceexit)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_WHATISTHIS, OnWhatisthis)
	ON_WM_HELPINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CSchedule_WTSPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_btnChoose.SetIcon (SICO (IDI_CHOOSEFOLDER));
	m_btnToSel.SetIcon (SICO (IDI_TOSEL));
	m_btnToUnsel.SetIcon (SICO (IDI_TOUNSEL));

	m_wndShutdownType.AddString (LS (L_SHUTDOWN));
	m_wndShutdownType.AddString (LS (L_RESTARTCOMP));
	m_wndShutdownType.AddString (LS (L_LOGOFF));
	m_wndShutdownType.AddString (LS (L_HIBERNATE));
	m_wndShutdownType.AddString (LS (L_STANDBY));

	m_wndTUM.AddString (LS (L_LIGHT));
	m_wndTUM.AddString (LS (L_MEDIUM));
	m_wndTUM.AddString (LS (L_HEAVY));

	CRect rc;
	m_wndSelDlds.GetClientRect (&rc);
	m_wndUnselDlds.InsertColumn (0, LS (L_ALLDLDS), LVCFMT_LEFT, rc.right);
	m_wndSelDlds.InsertColumn (0, "", LVCFMT_LEFT, rc.right);

	m_wndWTS.AddString (LS (L_LAUNCHPRG));
	m_wndWTS.AddString (LS (L_STARTDLDS));
	m_wndWTS.AddString (LS (L_STOPDLDS));
	m_wndWTS.AddString (LS (L_STARTALLDLDS));
	m_wndWTS.AddString (LS (L_STOPALLDLDS));
	m_wndWTS.AddString (LS (L_CHANGETUM));
	m_wndWTS.AddString (LS (L_EXITFROM));
	m_wndWTS.AddString (LS (L_SHUTDOWNCOMP));
	m_wndWTS.AddString (LS (L_PAUSEALLDOWNLOADS));

	for (int i = 0; i < 9; i++)
		ShowGroup (i, FALSE);

	m_iWTS = m_task->wts.enType;
	m_wndWTS.SetCurSel (m_iWTS);
	OnSelchangeWts ();

	if (m_task->wts.enType != WTS_PROGRAM)
	{
		SetDlgItemText (IDC_PROGNAME, _App.Scheduler_LastTask_ProgName ());
		SetDlgItemText (IDC_ARGUMENTS, _App.Scheduler_LastTask_ProgArgs ());
	}

	ApplyLanguage ();

	return TRUE;
}

void CSchedule_WTSPage::ShowGroup(int iGrp, BOOL bShow, BOOL bEnabled)
{
	static UINT ppGrpID [][20] = {
		{5, IDC__PROGNAME, IDC_PROGNAME, IDC_CHOOSENAME, IDC__ARGUMENTS, IDC_ARGUMENTS},
		{5, IDC_SELDLDS, IDC_TOSEL, IDC_TOUNSEL, IDC_UNSELDLDS, IDC_RESTARTDLDIFDONE},
		{4, IDC_SELDLDS, IDC_TOSEL, IDC_TOUNSEL, IDC_UNSELDLDS},
		{0},
		{0},
		{2, IDC__TUM, IDC_TUM},
		{0},
		{3, IDC__TYPE, IDC_SHUTDOWNTYPE, IDC_FORCEEXIT},
		{3, IDC_RAD_ENABLE, IDC_RAD_DISABLE, IDC_RAD_INVERT},
	};

	UINT nShow = bShow ? SW_SHOW : SW_HIDE;

	for (UINT i = 0; i < ppGrpID [iGrp][0]; i++)
	{
		CWnd *pWnd = GetDlgItem (ppGrpID [iGrp][i+1]);
		pWnd->ShowWindow (nShow);
		if (bEnabled == FALSE)
			pWnd->EnableWindow (FALSE);
	}
}

void CSchedule_WTSPage::OnSelchangeWts()
{
	ShowGroup (m_iWTS, FALSE);

	m_iWTS = m_wndWTS.GetCurSel ();

	LPCSTR psz1 = "", psz2 = "";

	switch (m_iWTS)
	{
		case WTS_PROGRAM:

			if (m_iWTS == m_task->wts.enType)
			{
				psz1 = m_task->wts.prog.pszName;
				psz2 = m_task->wts.prog.pszArgs;
			}

			SetDlgItemText (IDC_PROGNAME, psz1);
			SetDlgItemText (IDC_ARGUMENTS, psz2);
		break;

		case WTS_STARTDOWNLOAD:
			BuildDownloadsList ();
			CheckDlgButton (IDC_RESTARTDLDIFDONE,
				m_task->wts.dlds.dwFlags & SDI_RESTART_COMPLETED_DOWNLOADS ? BST_CHECKED : BST_UNCHECKED);
			LVCOLUMN col;
			col.mask = LVCF_TEXT;
			col.pszText = (LPSTR) LS (L_DLDSTOSTART);
			m_wndSelDlds.SetColumn (0, &col);
		break;

		case WTS_STOPDOWNLOAD:
			BuildDownloadsList ();
			col.mask = LVCF_TEXT;
			col.pszText = (LPSTR) LS (L_DLDSTOSTOP);
			m_wndSelDlds.SetColumn (0, &col);
		break;

		case WTS_CHANGE_TUM:
			if (m_iWTS == m_task->wts.enType)
				m_wndTUM.SetCurSel (m_task->wts.enTUM);
			else
				m_wndTUM.SetCurSel (0);
		break;

		case WTS_SHUTDOWN:
			if (m_iWTS == m_task->wts.enType)
			{
				m_wndShutdownType.SetCurSel (m_task->wts.shutdown.enShutdown);
				CheckDlgButton (IDC_FORCEEXIT, m_task->wts.shutdown.bForce ? BST_CHECKED : BST_UNCHECKED);
			}
			else
			{
				m_wndShutdownType.SetCurSel (0);
				CheckDlgButton (IDC_FORCEEXIT, BST_UNCHECKED);
			}
		break;

		case WTS_RESTRAINALLDLDS:
			if (WTS_RESTRAINALLDLDS == m_task->wts.enType)
			{
				CheckRadioButton (IDC_RAD_ENABLE, IDC_RAD_INVERT, IDC_RAD_ENABLE +
					m_task->wts.enRAD);
			}
		break;
	}

	ShowGroup (m_iWTS);
	UpdateEnabled ();
	SetModified ();
}

void CSchedule_WTSPage::BuildDownloadsList()
{
	m_wndUnselDlds.DeleteAllItems ();
	m_wndSelDlds.DeleteAllItems ();

	DLDS_LIST vSel, vUnsel;

	_DldsMgr.LockList (true);

	int cDlds = _DldsMgr.GetCount ();
	vUnsel.reserve (cDlds);

	for (int i = 0; i < cDlds; i++)
	{
		vmsDownloadSmartPtr dld = _DldsMgr.GetDownload (i);
		BOOL bToUnsel = TRUE;

		if (m_task->wts.enType == m_iWTS && m_task->wts.dlds.pvIDs != NULL)
		{
			for (int j = m_task->wts.dlds.pvIDs->size () - 1; j >= 0; j--)
			{
				if (m_task->wts.dlds.pvIDs->at (j) == dld->nID)
				{
					bToUnsel = FALSE;
					break;
				}
			}
		}

		if (bToUnsel)
			vUnsel.push_back (dld);
		else
			vSel.push_back (dld);
	}

	_DldsMgr.UnlockList (true);

	for (size_t i = 0; i < vSel.size (); i++)
	{
		m_wndSelDlds.InsertItem (i, vSel [i]->pMgr->get_URL (), 0);
		m_wndSelDlds.SetItemData (i, vSel [i]->nID);
	}

	for (size_t i = 0; i < vUnsel.size (); i++)
	{
		m_wndUnselDlds.InsertItem (i, vUnsel [i]->pMgr->get_URL (), 0);
		m_wndUnselDlds.SetItemData (i, vUnsel [i]->nID);
	}
}

void CSchedule_WTSPage::UpdateEnabled()
{
	switch (m_iWTS)
	{
		case WTS_STARTDOWNLOAD:
		case WTS_STOPDOWNLOAD:
			m_btnToSel.EnableWindow (m_wndUnselDlds.GetSelectedCount ());
			m_btnToUnsel.EnableWindow (m_wndSelDlds.GetSelectedCount ());
			break;
	}
}

void CSchedule_WTSPage::OnChangeProgname()
{
	SetModified ();
}

void CSchedule_WTSPage::OnChangeArguments()
{
	SetModified ();
}

void CSchedule_WTSPage::OnChoosename()
{
	CString strFilter;
	strFilter.Format ("%s (*.com; *.exe)|*.com;*.exe|%s (*.*)|*.*||", LS (L_APPS), LS (L_ALLFILES));
	CFileDialog dlg (TRUE, NULL, NULL, OFN_HIDEREADONLY|OFN_FILEMUSTEXIST|OFN_NOCHANGEDIR,
		strFilter, this);

    _DlgMgr.OnDoModal (&dlg);

	if (IDOK != dlg.DoModal ())
	{
		_DlgMgr.OnEndDialog (&dlg);
		return;
	}

    _DlgMgr.OnEndDialog (&dlg);

	SetDlgItemText (IDC_PROGNAME, dlg.GetPathName ());
}

void CSchedule_WTSPage::OnClickUnseldlds(NMHDR* , LRESULT* pResult)
{
	UpdateEnabled ();
	*pResult = 0;
}

void CSchedule_WTSPage::OnClickSeldlds(NMHDR* , LRESULT* pResult)
{
	UpdateEnabled ();
	*pResult = 0;
}

void CSchedule_WTSPage::OnTosel()
{
	POSITION pos = m_wndUnselDlds.GetFirstSelectedItemPosition ();
	int cItems = m_wndSelDlds.GetItemCount ();
	fs::list <int> vItems;

	while (pos)
	{
		int iItem = m_wndUnselDlds.GetNextSelectedItem (pos);
		m_wndSelDlds.InsertItem (cItems, m_wndUnselDlds.GetItemText (iItem, 0), 0);
		m_wndSelDlds.SetItemData (cItems++, m_wndUnselDlds.GetItemData (iItem));
		vItems.add (iItem);
	}

	for (int i = vItems.size () - 1; i >= 0; i--)
	{
		m_wndUnselDlds.DeleteItem (vItems [i]);
	}

	UpdateEnabled ();
	SetModified ();
}

void CSchedule_WTSPage::OnTounsel()
{
	POSITION pos = m_wndSelDlds.GetFirstSelectedItemPosition ();
	int cItems = m_wndUnselDlds.GetItemCount ();
	fs::list <int> vItems;

	while (pos)
	{
		int iItem = m_wndSelDlds.GetNextSelectedItem (pos);
		m_wndUnselDlds.InsertItem (cItems, m_wndSelDlds.GetItemText (iItem, 0), 0);
		m_wndUnselDlds.SetItemData (cItems++, m_wndSelDlds.GetItemData (iItem));
		vItems.add (iItem);
	}

	for (int i = vItems.size () - 1; i >= 0; i--)
	{
		m_wndSelDlds.DeleteItem (vItems [i]);
	}

	UpdateEnabled ();
	SetModified ();
}

void CSchedule_WTSPage::OnSelchangeTum()
{
	SetModified ();
}

void CSchedule_WTSPage::OnSelchangeShutdowntype()
{
	SetModified ();
}

BOOL CSchedule_WTSPage::OnApply()
{
	switch (m_iWTS)
	{
		case WTS_PROGRAM:
			if (FALSE == ApplyProg ())
				return FALSE;
		break;

		case WTS_STARTDOWNLOAD:
		case WTS_STOPDOWNLOAD:
			if (FALSE == ApplyStartStopDownloads ())
				return FALSE;
			m_task->wts.enType = (fsWhatToStartType) m_iWTS;
		break;

		case WTS_STARTALLDOWNLOADS:
		case WTS_STOPALLDOWNLOADS:
		case WTS_EXIT:
			FreeSchedule ();
			m_task->wts.enType = (fsWhatToStartType) m_iWTS;
		break;

		case WTS_CHANGE_TUM:
			FreeSchedule ();
			m_task->wts.enType = WTS_CHANGE_TUM;
			m_task->wts.enTUM = (fsTUM) m_wndTUM.GetCurSel ();
		break;

		case WTS_SHUTDOWN:
			FreeSchedule ();
			m_task->wts.enType = WTS_SHUTDOWN;
			m_task->wts.shutdown.enShutdown = (fsShutdownType) m_wndShutdownType.GetCurSel ();
			m_task->wts.shutdown.bForce = IsDlgButtonChecked (IDC_FORCEEXIT) == BST_CHECKED;
		break;

		case WTS_RESTRAINALLDLDS:
			FreeSchedule ();
			m_task->wts.enType = WTS_RESTRAINALLDLDS;
			if (IsDlgButtonChecked (IDC_RAD_ENABLE) == BST_CHECKED)
				m_task->wts.enRAD = RAD_ENABLE;
			else if (IsDlgButtonChecked (IDC_RAD_DISABLE) == BST_CHECKED)
				m_task->wts.enRAD = RAD_DISABLE;
			else
				m_task->wts.enRAD = RAD_INVERT;
		break;
	}

	fsScheduleEx* pschScheduleParam = (fsScheduleEx*)m_task;
	if (pschScheduleParam->m_ppoTaskWrapper)
		pschScheduleParam->m_ppoTaskWrapper->setDirty();

	return CPropertyPage::OnApply();
}

BOOL CSchedule_WTSPage::ApplyProg()
{
	CString strProg, strArgs;

	GetDlgItemText (IDC_PROGNAME, strProg);
	GetDlgItemText (IDC_ARGUMENTS, strArgs);

	if (strProg.GetLength () == 0)
	{
		MessageBox (LS (L_ENTERPRGNAME), LS (L_INPERR), MB_ICONEXCLAMATION);
		return FALSE;
	}

	FreeSchedule ();

	m_task->wts.enType = (fsWhatToStartType) m_iWTS;

	fsnew (m_task->wts.prog.pszName, char, strProg.GetLength () + 1);
	fsnew (m_task->wts.prog.pszArgs, char, strArgs.GetLength () + 1);

	strcpy (m_task->wts.prog.pszName, strProg);
	strcpy (m_task->wts.prog.pszArgs, strArgs);

	fsScheduleEx* pschScheduleParam = (fsScheduleEx*)m_task;
	if (pschScheduleParam->m_ppoTaskWrapper)
		pschScheduleParam->m_ppoTaskWrapper->setDirty();

	return TRUE;
}

void CSchedule_WTSPage::FreeSchedule()
{
	fsScheduleMgr::FreeTask (m_task);
}

BOOL CSchedule_WTSPage::ApplyStartStopDownloads()
{
	if (m_wndSelDlds.GetItemCount () == 0)
	{
		MessageBox (LS (L_ENTERDLDS), LS (L_INPERR), MB_ICONEXCLAMATION);
		return FALSE;
	}

	FreeSchedule ();

	fsnew1 (m_task->wts.dlds.pvIDs, fs::list <UINT>);

	int cItems = m_wndSelDlds.GetItemCount ();

	for (int i = 0; i < cItems; i++)
		m_task->wts.dlds.pvIDs->add (m_wndSelDlds.GetItemData (i));

	m_task->wts.dlds.dwFlags = 0;
	if (IsDlgButtonChecked (IDC_RESTARTDLDIFDONE) == BST_CHECKED)
		m_task->wts.dlds.dwFlags |= SDI_RESTART_COMPLETED_DOWNLOADS;

	fsScheduleEx* pschScheduleParam = (fsScheduleEx*)m_task;
	if (pschScheduleParam->m_ppoTaskWrapper)
		pschScheduleParam->m_ppoTaskWrapper->setDirty();

	return TRUE;
}

void CSchedule_WTSPage::OnForceexit()
{
	SetModified ();
}

void CSchedule_WTSPage::OnContextMenu(CWnd* , CPoint point)
{
	PrepareCHMgr (point);
	_CHMgr.ShowMenu ();
}

void CSchedule_WTSPage::OnWhatisthis()
{
	_CHMgr.OnWT ();
}

void CSchedule_WTSPage::ApplyLanguage()
{
	fsDlgLngInfo lnginfo [] =  
	{
		fsDlgLngInfo (IDC__PROGNAME, L_PRGNAME),
		fsDlgLngInfo (IDC__ARGUMENTS, L_ARGS),
		fsDlgLngInfo (IDC__TYPE, L_SHUTDOWNTYPE),
		fsDlgLngInfo (IDC_FORCEEXIT, L_FORCEAPPS),
		fsDlgLngInfo (IDC_RAD_ENABLE, L_ENABLE),
		fsDlgLngInfo (IDC_RAD_DISABLE, L_DISABLE),
		fsDlgLngInfo (IDC_RAD_INVERT, L_SWITCH),
		fsDlgLngInfo (IDC_RESTARTDLDIFDONE, L_RESTARTCOMPLDLDS),
	};

	CString str = LS (L_CHANGETUMTO); str += ':';
	SetDlgItemText (IDC__TUM, str);

	_LngMgr.ApplyLanguage (this, lnginfo, sizeof (lnginfo) / sizeof (fsDlgLngInfo), 0);
}

void CSchedule_WTSPage::PrepareCHMgr(CPoint point)
{
	fsCtrlContextHelp aCH1 [] = 
	{
		fsCtrlContextHelp (IDC__TUM, LS (L_SETTUMHERE)),
		fsCtrlContextHelp (IDC_TUM, LS (L_SETTUMHERE)),
		fsCtrlContextHelp (IDC_SELDLDS, LS (L_SELDLDSHERE)),
		fsCtrlContextHelp (IDC_UNSELDLDS, LS (L_ALLDLDSHERE)),
		fsCtrlContextHelp (IDC_TOSEL, LS (L_TOSELHERE)),
		fsCtrlContextHelp (IDC_TOUNSEL, LS (L_TOUNSELHERE)),
		fsCtrlContextHelp (IDC__PROGNAME, LS (L_PROGNAMEHERE)),
		fsCtrlContextHelp (IDC_PROGNAME, LS (L_PROGNAMEHERE)),
		fsCtrlContextHelp (IDC_CHOOSENAME, LS (L_CHOOSEPROGHERE)),
		fsCtrlContextHelp (IDC__ARGUMENTS, LS (L_ARGSHERE)),
		fsCtrlContextHelp (IDC_ARGUMENTS, LS (L_ARGSHERE)),
		fsCtrlContextHelp (IDC__TYPE, LS (L_TYPEHERE)),
		fsCtrlContextHelp (IDC_SHUTDOWNTYPE, LS (L_TYPEHERE)),
		fsCtrlContextHelp (IDC_FORCEEXIT, LS (L_FORCEEXITHERE)),
		fsCtrlContextHelp (IDC_WTS, LS (L_WTSHERE)),
		fsCtrlContextHelp (IDC_RAD_INVERT, LS (L_RAD_INVERT_HERE)),
	};

    static fsCtrlContextHelp aCH [sizeof (aCH1) / sizeof (fsCtrlContextHelp)];
	CopyMemory (aCH, aCH1, sizeof (aCH));

	_CHMgr.PrepareContextMenu (this, point, aCH, sizeof (aCH) / sizeof (fsCtrlContextHelp));
}

BOOL CSchedule_WTSPage::OnHelpInfo(HELPINFO* pHelpInfo)
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
