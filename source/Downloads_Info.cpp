/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "FdmApp.h"
#include "Downloads_Info.h"
#include "fsDownloadsMgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDownloads_Info::CDownloads_Info()
{
}

CDownloads_Info::~CDownloads_Info()
{
}

BEGIN_MESSAGE_MAP(CDownloads_Info, CTabCtrl)
	//{{AFX_MSG_MAP(CDownloads_Info)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, OnSelchange)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDownloads_Info::Create(CWnd *pParent)
{
	CRect rc (50, 50, 275, 70);

	if (FALSE == CTabCtrl::Create (TCS_SINGLELINE|TCS_RIGHTJUSTIFY|TCS_FOCUSNEVER,
			rc, pParent, 0x5111))
		return FALSE;

	LOGFONT lf;
	NONCLIENTMETRICS nm;

	ZeroMemory (&nm, sizeof (nm));
	nm.cbSize = sizeof (nm);
	SystemParametersInfo (SPI_GETNONCLIENTMETRICS, nm.cbSize, &nm, 0);
	lf = nm.lfMenuFont;
	lf.lfCharSet = DEFAULT_CHARSET;

	m_itemsFont.CreateFontIndirect (&lf);

	SetFont (&m_itemsFont, FALSE);

	CBitmap bmp;
	bmp.Attach (SBMP (IDB_DOWNLOADSINFO));
	m_images.Create (16, 16, ILC_COLOR24 | ILC_MASK, 1, 1);
	m_images.Add (&bmp, RGB (255,0,255));
	SetImageList (&m_images);

	InsertItem (0, LS (L_LOG), 0);
	InsertItem (1, LS (L_PROGRESS), 1);

	int nCurTab = _App.View_DldInfoCurTab ();
	set_CurTab (nCurTab);

	ShowWindow (SW_SHOW);

	return TRUE;
}

int CDownloads_Info::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTabCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rc;
	GetItemRect (0, &rc);
	m_cy = rc.bottom - rc.top;

	if (!m_frame.Create (this))
		return -1;

	if (!m_log.Create (&m_frame))
		return -1;

	if (!m_progress.Create (&m_frame))
		return -1;

	m_frame.SetChildWnd (&m_log);

	return 0;
}

void CDownloads_Info::OnSize(UINT nType, int cx, int cy)
{
	CTabCtrl::OnSize(nType, cx, cy);

	CRect rc;
	GetItemRect (0, &rc);
	m_cy = rc.bottom - rc.top;
	m_cy+=3;

	m_frame.MoveWindow (0, m_cy, cx, cy - m_cy);
}

void CDownloads_Info::OnPaint()
{
	CTabCtrl::OnPaint();
	CDC *dc = GetDC ();
	CRect rc;
	GetClientRect (&rc);
	dc->SetPixel (rc.right-1, 22, GetSysColor (COLOR_3DFACE));
	ReleaseDC (dc);
}

void CDownloads_Info::OnSelchange(NMHDR*, LRESULT* pResult)
{
	ApplyCurTab ();
	*pResult = 0;
}

void CDownloads_Info::ApplyLanguage()
{
	TCITEM item;
	ZeroMemory (&item, sizeof (item));

	item.mask = TCIF_TEXT;
	item.pszText = (LPSTR) LS (L_LOG);
	SetItem (0, &item);

	item.pszText = (LPSTR) LS (L_PROGRESS);
	SetItem (1, &item);

	m_log.ApplyLanguage ();
}

void CDownloads_Info::SaveState()
{
	m_log.SaveState ("DownloadsLog");
	_App.View_DldInfoCurTab(get_CurTab());// m_bBtTabWasActive ? DIT_BT : get_CurTab());
	//m_video.SaveState ();
}

void CDownloads_Info::ApplyCurTab()
{
	int cur = GetCurSel ();
	if (cur == 0)
	{
		m_progress.ShowWindow (SW_HIDE);
		m_log.ShowWindow (SW_SHOW);
		m_frame.SetChildWnd (&m_log);
	}
	else if (cur == 1)
	{
		m_log.ShowWindow (SW_HIDE);
		m_progress.ShowWindow (SW_SHOW);
		m_frame.SetChildWnd (&m_progress);
	}
}

vmsDownloadSmartPtr CDownloads_Info::Get_ActiveDownload()
{
	return m_progress.GetActiveDownload ();
}

void CDownloads_Info::Set_ActiveDownload(vmsDownloadSmartPtr dld)
{
	m_activeDld = dld;
	m_progress.SetActiveDownload (dld);
	m_log.SetActiveDownload (dld);
}

void CDownloads_Info::UpdateActiveDownload()
{
	if (m_progress.IsWindowVisible ())
		m_progress.UpdateDownload ();
}

void CDownloads_Info::AddDownloadEvent(fsDownloadEvents *event)
{
	m_log.AddRecord (event);
}

CDownloads_Log* CDownloads_Info::Get_LogWindow()
{
	return &m_log;
}

CDownloads_Progress* CDownloads_Info::Get_ProgressWindow()
{
	return &m_progress;
}

BOOL CDownloads_Info::OnEraseBkgnd(CDC* pDC)
{
	//if (m_video.m_wndVideo.m_player.Get_State () != VFPS_CLOSED)
	//{
 //   	CRect rc;
	//	//m_video.GetWindowRect(&rc);
	//	ScreenToClient(&rc);
	//	pDC->ExcludeClipRect(&rc);
	//}

	return CTabCtrl::OnEraseBkgnd(pDC);
}

void CDownloads_Info::set_CurTab(int nIndex)
{
	if (nIndex != DIT_LOG)// && m_bBtTabShowing == false)
		nIndex--;
	SetCurSel (nIndex);
	ApplyCurTab ();
}

int CDownloads_Info::get_CurTab()
{
	int cur = GetCurSel ();
	if (cur != DIT_LOG)// && m_bBtTabShowing == false)
		cur++;
	return cur;
}
