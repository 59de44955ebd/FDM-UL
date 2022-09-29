/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "FdmApp.h"
#include "mfchelp.h"
#include "SiteManagerSheet.h"
#include "MainFrm.h"
#include "fsPluginMgr.h"
#include "DownloadsWnd.h"
#include "ShedulerWnd.h"
#include "system.h"
#include "SitesWnd.h"
#include "inetutil.h"
#include "Dlg_ExportDownloads.h"
#include "Dlg_Find.h"
#include "Dlg_TUMChanged.h"
#include "Dlg_ShutdownType.h"
#include "Dlg_ChooseGroup.h"
#include "MyMessageBox.h"
#include "FdmBalloon.h"
#include "FdmBalloonContent.h"
#include "FdmBalloon_OnDownloadDone.h"
#include "Dlg_DL.h"
#include "vmsCommandLine.h"
#include "vmsFileUtil.h"
#include "Utils.h"
//#include "vmsAppGlobalObjects.h"
#include "vmsLogger.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_SHOW_BALLOON			(WM_APP + 1)
#define WM_MAINFRM_SAVEALLDATA	(WM_APP + 2)
#define WM_TRAYMSG				(WM_APP + 100)

#define ID_TUM_CHANGED			36999
#define ID_SWITCH_TO_START		37000
#define ID_SWITCH_TO_END		(ID_SWITCH_TO_START+100)

//#define ID_LNGMENU_START		(ID_SWITCH_TO_END+1)
//#define ID_LNGMENU_END			(ID_LNGMENU_START+100)
//#define ID_THREAD_UPDATE		10000

#define PLUGIN_MENU_VIEW_POS 5
//org:
//#define LFD_MENU_POS 15
//#define TUM_MENU_POS 17
#define TUM_MENU_POS 11

extern fsPluginMgr _PluginMgr;

extern CDownloadsWnd* _pwndDownloads;
extern CShedulerWnd* _pwndScheduler;
extern CSitesWnd* _pwndSites;

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_WM_CLOSE()
	ON_COMMAND(ID_DLDDEFOPTIONS, OnDlddefoptions)
	ON_COMMAND(ID_DLDROPTIONS, OnDldroptions)
	ON_COMMAND(ID_TUM_HEAVY, OnTumHeavy)
	ON_UPDATE_COMMAND_UI(ID_TUM_HEAVY, OnUpdateTumHeavy)
	ON_COMMAND(ID_TUM_LIGHT, OnTumLight)
	ON_UPDATE_COMMAND_UI(ID_TUM_LIGHT, OnUpdateTumLight)
	ON_COMMAND(ID_TUM_MEDIUM, OnTumMedium)
	ON_UPDATE_COMMAND_UI(ID_TUM_MEDIUM, OnUpdateTumMedium)
	ON_COMMAND(ID_DLD_CREATE, OnDldCreate)
	ON_COMMAND(ID_TASK_CREATE_NEW, OnTaskCreateNew)
	ON_COMMAND(ID_NEED_EXIT, OnNeedExit)
	ON_WM_SIZE()
	ON_WM_INITMENUPOPUP()
	ON_COMMAND(ID_APP_EXIT, OnAppExit)
	ON_WM_MEASUREITEM()
	ON_WM_DRAWITEM()
	ON_COMMAND(ID_SHOWMAINWINDOW, OnShowmainwindow)
	ON_COMMAND(ID_STARTALL, OnStartall)
	ON_COMMAND(ID_STOPALL, OnStopall)
//	ON_COMMAND(ID_PROGGENERALSETTINGS, OnProggeneralsettings)
	ON_WM_SYSCOMMAND()
	ON_WM_ENDSESSION()
	ON_COMMAND(ID_ADDSITE, OnAddsite)
	ON_COMMAND(ID_VIEW_SWBAR, OnViewSwbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SWBAR, OnUpdateViewSwbar)
	ON_WM_NCRBUTTONUP()
	ON_WM_TIMER()
	ON_WM_QUERYENDSESSION()
	ON_COMMAND(ID_INSERT, OnInsert)

	//ON_COMMAND(ID_DLLANGFILES, OnDllangfiles)
	ON_COMMAND(ID_PROCCEEDFURTHERINIT, OnProceedFurherInitialization)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_EXPORT_EXPORTLISTOFDOWNLOADS, OnExportlistofdownloads)
	ON_COMMAND(ID_FILE_IMPORT_IMPORTLISTOFDOWNLOADS, OnImportlistofdownloads)

	ON_COMMAND(ID_FIND, OnFind)
	ON_COMMAND(ID_FINDNEXT, OnFindnext)
	ON_UPDATE_COMMAND_UI(ID_FINDNEXT, OnUpdateFindnext)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_DLD_CREATEBATCH, OnDldCreatebatch)
	ON_COMMAND(ID_FILE_IMPORT_IMPORTLISTOFDOWNLOADSFROMCLIPBOARD, OnFileImportImportlistofdownloadsfromclipboard)
	ON_COMMAND(ID_OPTIONS_SM, OnOptionsSm)
//	ON_COMMAND(ID_LDF_CLEAR, OnLdfClear)
//	ON_UPDATE_COMMAND_UI(ID_LDF_CLEAR, OnUpdateLdfClear)
	ON_COMMAND(ID_PAUSEALLDLDS, OnPausealldlds)
	ON_UPDATE_COMMAND_UI(ID_PAUSEALLDLDS, OnUpdatePausealldlds)
	ON_COMMAND(ID_APP_EXIT_2, OnAppExit2)
	ON_COMMAND(ID_LOADATSTARTUP, OnLoadatstartup)
	ON_UPDATE_COMMAND_UI(ID_LOADATSTARTUP, OnUpdateLoadatstartup)
	ON_MESSAGE (WM_TRAYMSG, OnTrayMsg)
	ON_COMMAND(ID_VIEW_TOOLBAR, OnViewToolbar)
	ON_COMMAND(ID_VIEW_STATUS_BAR, OnViewStatusbar)

#ifdef FLOATING_WIN
	ON_COMMAND(ID_DLINFOBOX, OnDlinfobox)
	ON_UPDATE_COMMAND_UI(ID_DLINFOBOX, OnUpdateDlinfobox)
	ON_COMMAND(ID_DROPBOX, OnDropBox)
	ON_UPDATE_COMMAND_UI(ID_DROPBOX, OnUpdateDropBox)
#endif

	ON_COMMAND(ID_EXITWHENDONE, OnExitwhendone)
	ON_UPDATE_COMMAND_UI(ID_EXITWHENDONE, OnUpdateExitwhendone)

	ON_COMMAND(ID_TURNOFFWHENDONE, OnTurnoffwhendone)
	ON_UPDATE_COMMAND_UI(ID_TURNOFFWHENDONE, OnUpdateTurnoffwhendone)

	ON_COMMAND(ID_TOOLS_ACTIVATEWEBINTERFACE, OnActivateWebinterface)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_ACTIVATEWEBINTERFACE, OnUpdateActivateWebinterface)

	ON_MESSAGE(WM_SHOWTRAYMENU, OnShowTrayMenu)
	ON_MESSAGE(WM_POWERBROADCAST, OnPowerBroadCast)
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_SWITCH_TO_START, ID_SWITCH_TO_END, OnSwitchTo)
	ON_UPDATE_COMMAND_UI_RANGE(ID_SWITCH_TO_START, ID_SWITCH_TO_START+100, OnUpdateSwitchTo)
	//ON_UPDATE_COMMAND_UI_RANGE(WGP_MENU_VIEWSMPLITEM_CMDSTART, WGP_MENU_CMDLAST, OnUpdatePluginMenuView)

	ON_COMMAND_RANGE(ID_ALT1, ID_ALT9, OnAltPlusDigit)

	ON_COMMAND (ID_TUM_CHANGED, OnTUMChanged)
	//ON_COMMAND_RANGE (ID_LDF_0, ID_LDF_0+9, OnLDF)
	//ON_UPDATE_COMMAND_UI_RANGE(ID_LDF_0, ID_LDF_0+9, OnUpdateLdf0)
	ON_UPDATE_COMMAND_UI(ID_SB_TOTALSPEED, OnUpdateTotalSpeed)
	ON_MESSAGE(WM_SHOW_BALLOON, OnShowBalloon)
	ON_MESSAGE(WM_MYBALLOON_CLOSED, OnMyBalloonClosed)
	ON_MESSAGE(WM_DOMODAL, OnDoModal)

	ON_MESSAGE(WM_MAINFRM_SAVEALLDATA, OnSaveAllData)
	END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,
//	ID_SB_TRAFFIC_THISMONTH,
	ID_SB_TOTALSPEED,
};

CMainFrame::CMainFrame()
{
	m_hevShuttingDown = CreateEvent (NULL, TRUE, FALSE, NULL);
	m_bExitHandlerPerformed = false;

	m_cMenuMainItemsAdded = m_cMenuViewItemsAdded = 0;
	m_bQueryForExit = TRUE;
	ReadSettings ();

	m_cPluginMenuViewInserted = 0;

	m_umsgTaskBarCreated = 0;

	m_bTrayMenuShowing = m_bBalloonShowing = FALSE;

	m_bInited = FALSE;

	m_nShutdownMsg = RegisterWindowMessage ("FDM - shutdown");

	m_cThreadsRunning = 0;

	m_pFdmBalloon = NULL;
	m_pFdmBalloonContent = NULL;

#ifdef FLOATING_WIN
	m_pFloatWndsThread = NULL;
#endif
}

CMainFrame::~CMainFrame()
{
	SetEvent (m_hevShuttingDown);
	while (m_cThreadsRunning)
		Sleep (10);
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	UpdateTitle ();

	m_odmenu.Attach (GetMenu (), TRUE);

	LoadMenuImages ();

	if (FALSE == _TBMgr.Create (this))
		return -1;

	CBitmap bmp, bmpd, bmph;

	bmp.Attach (SBMP (IDB_TOOL0));
	bmpd.Attach (SBMP (IDB_TOOL0_D));

	if (_TB_USE_ALPHA)
	{
		ConvertBmp32WithAlphaToBmp32WithoutAlpha (bmp, GetSysColor (COLOR_3DFACE));
		ConvertBmp32WithAlphaToBmp32WithoutAlpha (bmpd, GetSysColor (COLOR_3DFACE));
	}

	wgTButtonInfo btns [] =
	{
		wgTButtonInfo (0, TBSTYLE_SEP, ""),
		wgTButtonInfo (ID_TUM_LIGHT, TBSTYLE_BUTTON, ""),
		wgTButtonInfo (ID_TUM_MEDIUM, TBSTYLE_BUTTON, ""),
		wgTButtonInfo (ID_TUM_HEAVY, TBSTYLE_BUTTON, ""),
		wgTButtonInfo (0, TBSTYLE_SEP, ""),
		wgTButtonInfo (ID_STARTALL, TBSTYLE_BUTTON, ""),
		wgTButtonInfo (ID_STOPALL, TBSTYLE_BUTTON, ""),
		wgTButtonInfo (ID_PAUSEALLDLDS, TBSTYLE_BUTTON, ""),
		wgTButtonInfo (0, TBSTYLE_SEP, ""),
		wgTButtonInfo (ID_DLDROPTIONS, TBSTYLE_BUTTON, ""),
	};

	if (FALSE == _TBMgr.InsertGroup (btns, &bmp, &bmpd, sizeof (btns) / sizeof (wgTButtonInfo)))
		return -1;

	_TBMgr.ShowGroup (0, 0);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;
	}

	UINT nID, nStyle;
	int cx;

	m_wndStatusBar.GetPaneInfo (0, nID, nStyle, cx);
	nStyle &= ~ SBPS_NOBORDERS;
	m_wndStatusBar.SetPaneInfo (0, nID, nStyle, cx);

	m_wndReBar.Create (this);

	m_wndReBar.AddBar (&_TBMgr, NULL, NULL, RBBS_FIXEDBMP|RBBS_NOGRIPPER|RBBS_BREAK);
	REBARBANDINFO rbbi;
	rbbi.cbSize = sizeof (rbbi);
	rbbi.fMask = RBBIM_ID;
	rbbi.wID = 1;
	VERIFY (m_wndReBar.GetReBarCtrl ().SetBandInfo (m_wndReBar.GetReBarCtrl ().GetBandCount ()-1, &rbbi));

	_ClipbrdMgr.Initialize (m_hWnd);

	if (!m_wndView.Create(AfxRegisterWndClass (0, LoadCursor (NULL, IDC_ARROW),
		(HBRUSH) (COLOR_3DFACE+1), NULL), NULL, AFX_WS_DEFAULT_VIEW | WS_CHILD,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}

	if (_App.View_Toolbar () == FALSE)
	{
		CControlBar* pBar = GetControlBar(AFX_IDW_TOOLBAR);
		if (pBar != NULL)
			ShowControlBar (pBar, FALSE, FALSE);
	}

	if (_App.View_Statusbar () == FALSE)
	{
		CControlBar* pBar = GetControlBar(AFX_IDW_STATUS_BAR);
		if (pBar != NULL)
			ShowControlBar (pBar, FALSE, FALSE);
	}

	ApplyLanguage ();

	m_umsgTaskBarCreated = RegisterWindowMessage(TEXT ("TaskbarCreated"));

	UINT pnIcons [] = {IDI_TRAY_NORMAL, IDI_TRAY_DOWNLOADING, IDI_TRAY_ERRORS, IDI_TRAY_UNKNOWN};
	_TrayMgr.Create (m_hWnd, pnIcons, sizeof (pnIcons) / sizeof (UINT),
		vmsFdmAppMgr::getAppName (), WM_TRAYMSG);

#ifdef FLOATING_WIN
	m_pFloatWndsThread = (CFloatingWndsThread*) AfxBeginThread (RUNTIME_CLASS (CFloatingWndsThread));
#endif

	PostMessage (WM_COMMAND, ID_PROCCEEDFURTHERINIT);

	UINT port = AfxGetApp()->GetProfileInt("Webinterface", "Port", 0);
	_httpServer.set_Port((unsigned short)port);
	if (AfxGetApp()->GetProfileInt("Webinterface", "AutoStart", 0) == 1)
	{
		_httpServer.Start();
	}

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

	WNDCLASS wc;
	ZeroMemory (&wc, sizeof (wc));
	wc.hbrBackground = (HBRUSH) (COLOR_WINDOW+1);
	wc.hCursor = LoadCursor (NULL, IDC_ARROW);
	wc.hIcon = LoadIcon (AfxGetInstanceHandle (), MAKEINTRESOURCE (IDR_MAINFRAME));
	wc.hInstance = AfxGetInstanceHandle ();
	wc.lpfnWndProc = ::DefWindowProc;
	wc.lpszClassName = "Free Download Manager Main Window";
	cs.lpszClass = wc.lpszClassName;

	return AfxRegisterClass (&wc);
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif

void CMainFrame::OnSetFocus(CWnd* )
{
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CMainFrame::AddPluginMenu(HMENU hSrcMenu, fsSetImage* pImages, int cImages)
{
	if (hSrcMenu == NULL)
		return;
	if (m_cMenuMainItemsAdded)
		return;
	int iAddAfter = GetMenu ()->GetMenuItemCount () - 3;
	int cSrcItems = m_odmenu.InsertMenu (CMenu::FromHandle (hSrcMenu), iAddAfter);
	m_cMenuMainItemsAdded = cSrcItems;
	if (pImages) m_odmenu.SetImages (pImages, cImages);
	DrawMenuBar ();
}

void CMainFrame::RemovePluginMenu()
{
	int iWhere = GetMenu ()->GetMenuItemCount () - 4;
	m_odmenu.RemoveMenu (iWhere, m_cMenuMainItemsAdded);
	m_cMenuMainItemsAdded = 0;
	DrawMenuBar ();
}

void CMainFrame::OnClose()
{
	if (onExit (m_bQueryForExit))
		CFrameWnd::OnClose();
}

void CMainFrame::OnDlddefoptions()
{
	_pwndDownloads->OnDownloadDefProperties ();
}

#include "Dlg_ProgramOptions.h"
void CMainFrame::OnDldroptions()
{
	CProgramOptions dlg;
	dlg.DoModal ();
}

void CMainFrame::OnTumHeavy()
{
	if (_TumMgr.GetTUM () == TUM_HEAVY)
		return;

	_TumMgr.SetTUM (TUM_HEAVY);
	_App.CurrentTUM (TUM_HEAVY);

	if (_App.View_TUMChanged ())
	{
		_TBMgr.GetToolBarCtrl ().SetState (ID_TUM_MEDIUM, TBSTATE_ENABLED);
		_TBMgr.GetToolBarCtrl ().SetState (ID_TUM_LIGHT, TBSTATE_ENABLED);
		PostMessage (WM_COMMAND, ID_TUM_CHANGED);
	}
	UpdateTumToolbarState();
}

void CMainFrame::OnUpdateTumHeavy(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (_TumMgr.GetTUM () == TUM_HEAVY);
}

void CMainFrame::OnTumLight()
{
	if (_TumMgr.GetTUM () == TUM_LIGHT)
		return;

	_TumMgr.SetTUM (TUM_LIGHT);
	_App.CurrentTUM (TUM_LIGHT);

	if (_App.View_TUMChanged ())
	{
		_TBMgr.GetToolBarCtrl ().SetState (ID_TUM_HEAVY, TBSTATE_ENABLED);
		_TBMgr.GetToolBarCtrl ().SetState (ID_TUM_MEDIUM, TBSTATE_ENABLED);
		PostMessage (WM_COMMAND, ID_TUM_CHANGED);
	}
	UpdateTumToolbarState();
}

void CMainFrame::OnUpdateTumLight(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (_TumMgr.GetTUM () == TUM_LIGHT);
}

void CMainFrame::OnTumMedium()
{
	if (_TumMgr.GetTUM () == TUM_MEDIUM)
		return;

	_TumMgr.SetTUM (TUM_MEDIUM);
	_App.CurrentTUM (TUM_MEDIUM);

	if (_App.View_TUMChanged ())
	{
		_TBMgr.GetToolBarCtrl ().SetState (ID_TUM_HEAVY, TBSTATE_ENABLED);
		_TBMgr.GetToolBarCtrl ().SetState (ID_TUM_LIGHT, TBSTATE_ENABLED);
		PostMessage (WM_COMMAND, ID_TUM_CHANGED);
	}
	UpdateTumToolbarState();
}

void CMainFrame::OnUpdateTumMedium(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (_TumMgr.GetTUM () == TUM_MEDIUM);
}

void CMainFrame::OnOptmaster()
{
	_pwndDownloads->OnOptimizationWizard ();
}

void CMainFrame::OnDldCreate()
{
	if (_DldsMgr.IsDeletingNow ())
		return;
	_pwndDownloads->OnDownloadCreate ();
}

void CMainFrame::OnTaskCreateNew()
{
	_pwndScheduler->OnCreatenewtask ();
}

void CMainFrame::OnNeedExit()
{
	m_bQueryForExit = FALSE;
	SendMessage (WM_CLOSE);
}

LRESULT CMainFrame::OnTrayMsg(WPARAM , LPARAM lp)
{
	switch (lp)
	{
		case WM_MOUSEMOVE:
			if (strlen (_TrayMgr.getTip ()))
				_TrayMgr.setTip ("");
			SetTimer (7, 1000, NULL);
			if (m_bBalloonShowing == FALSE)
			{
				POINT pt;
				GetCursorPos (&pt);
				m_balloonX = pt.x; m_balloonY = pt.y;
				SetTimer (4, 1000, NULL);
			}
			break;

		case WM_LBUTTONDOWN:
			if (IsIconic ())
				OnShowmainwindow ();
			else
				ShowWindow (SW_MINIMIZE);
			break;

		case WM_RBUTTONUP:
			if (is_MouseInTray ())
			{
				KillTimer (2);
				HideBalloon ();
				ShowTrayMenu ();
			}
			break;

		case NIN_BALLOONUSERCLICK:
		case NIN_BALLOONTIMEOUT:
		case NIN_BALLOONHIDE:
			m_bBalloonShowing = FALSE;
			m_strTimeoutBallon_Msgs = "";
			break;
	}

	return 0;
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	if (nType == SIZE_MINIMIZED)
	{
		if (m_bMinToTray)
			ShowWindow (SW_HIDE);
	}
	else
	{
		CFrameWnd::OnSize(nType, cx, cy);
		if (nType == SIZE_MAXIMIZED || nType == SIZE_RESTORED)
			RecalcLayout ();
	}

	_TBMgr.Invalidate (TRUE);
}

void CMainFrame::ShowTrayMenu(BOOL bModeTray)
{
	if (m_bTrayMenuShowing)
		return;

	m_bTrayMenuShowing = TRUE;

	CMenu menu;
	menu.LoadMenu (IDM_TRAY);
	CMenu *pPopup = menu.GetSubMenu (0);

//	const vmsFileRecentList* pLFD = _DldsMgr.get_LastFilesDownloaded ();
//	CMenu* pmenuLFD = pPopup->GetSubMenu (LFD_MENU_POS);
//	for (int i = 0; i < pLFD->get_Count (); i++)
//	{
//		if (i == 0)
//			pmenuLFD->RemoveMenu (0, MF_BYPOSITION);
//		LPCSTR pszDispName = pLFD->get_FileDispName (i);
//		if (*pszDispName == 0)
//			pszDispName = LS (L_UNKNOWN);
//		pmenuLFD->InsertMenu (0, MF_STRING | MF_BYPOSITION, ID_LDF_0 + i, pszDispName);
//	}

	pPopup->SetDefaultItem (ID_SHOWMAINWINDOW);

	CPoint pt;
	GetCursorPos (&pt);

	SetForegroundWindow ();

	m_odTrayMenu.Attach (&menu, FALSE);

	fsSetImage img [] =
	{
		fsSetImage (ID_DLD_CREATE, 18),
		fsSetImage (ID_TUM_LIGHT, 0),
		fsSetImage (ID_TUM_MEDIUM, 1),
		fsSetImage (ID_TUM_HEAVY, 2),
		fsSetImage (ID_STARTALL, 3),
		fsSetImage (ID_STOPALL, 4),
		fsSetImage (ID_PAUSEALLDLDS, 5),
		fsSetImage (ID_APP_ABOUT, 10),
	};

	m_odTrayMenu.SetImages (img, sizeof (img) / sizeof (fsSetImage));

	CString strSMW = LS (L_SHOWMAINWND); strSMW += '\t';
	CString strCND = LS (L_NEWDL); strCND += "\tIns";
	CString strL = LS (L_LIGHT); strL += "\tCtrl+1";
	CString strM = LS (L_MEDIUM); strM += "\tCtrl+2";
	CString strH = LS (L_HEAVY); strH += "\tCtrl+3";
	CString strExit = LS (L_EXIT); strExit += "\tAlt+X";
	CString sImpFromClip = LS (L_IMPORTURLSFROMCLIPBOARD); sImpFromClip += "\tCtrl+Shift+V";

	fsSetText texts [] = {
		fsSetText (ID_SHOWMAINWINDOW, strSMW),
		//fsSetText (ID_MONITORCLIPBOARD, LS (L_MONITORCLIPBOARD)),
		fsSetText (ID_DLD_CREATE, strCND),
		fsSetText (ID_DLD_CREATEBATCH, LS (L_CREATEBATCHDLD)),
		fsSetText (ID_FILE_IMPORT_IMPORTLISTOFDOWNLOADSFROMCLIPBOARD, sImpFromClip),
		fsSetText (ID_STARTALL, LS (L_STARTALLDLDS)),
		fsSetText (ID_STOPALL, LS (L_STOPALLDLDS)),
		fsSetText (ID_TUM_LIGHT, strL),
		fsSetText (ID_TUM_MEDIUM, strM),
		fsSetText (ID_TUM_HEAVY, strH),
		//fsSetText (ID_DLINFOBOX, LS (L_SHOWDLDSINFOWHILEDOWNLOADING)),
		//fsSetText (ID_DROPBOX, LS (L_DROPBOX)),
		fsSetText (ID_APP_ABOUT, LS (L_ABOUT)),
		fsSetText (ID_APP_EXIT, strExit),
//		fsSetText (ID_LDF_CLEAR, LS (L_CLEAR)),
		fsSetText (ID_PAUSEALLDLDS, LS (L_PAUSEALLDOWNLOADS)),
		fsSetText (ID_LOADATSTARTUP, LS (L_AUTOSTART)),
	};
	m_odTrayMenu.SetMenuItemsText (&menu, texts, sizeof (texts) / sizeof (fsSetText), FALSE);

	//m_odTrayMenu.SetMenuItemText (menu.GetSubMenu (0), LS (L_LASTDOWNLOADEDFILES), LFD_MENU_POS, TRUE);

	//if (pLFD->get_Count () == 0)
	//	m_odTrayMenu.SetMenuItemText (menu.GetSubMenu (0)->GetSubMenu (LFD_MENU_POS), LS (L_EMPTY), 0, TRUE);

	// trafic usage mode
	m_odTrayMenu.SetMenuItemText (menu.GetSubMenu (0), LS (L_TUM), TUM_MENU_POS, TRUE);

	UINT uFlags = TPM_RIGHTBUTTON;
	if (bModeTray)
		uFlags |=  TPM_BOTTOMALIGN | TPM_RIGHTALIGN;
	else
		uFlags |= TPM_LEFTALIGN | TPM_TOPALIGN;

	pPopup->TrackPopupMenu (uFlags,	pt.x, pt.y, this);
	m_odTrayMenu.Detach ();

	menu.DestroyMenu ();

	m_bTrayMenuShowing = FALSE;
}

void CMainFrame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	HMENU ahMenus [100];

	int i = 0;
	for (i = 0; i < m_cMenuMainItemsAdded; i++)
		ahMenus [i] = GetMenu ()->GetSubMenu (GetMenu ()->GetMenuItemCount () - 3 - m_cMenuMainItemsAdded + i)->m_hMenu;

	_PluginMgr.UpdateMenuMain ((HMENU*) ahMenus);

	if (m_cMenuViewItemsAdded)
	{
		for (i = 0; i < m_cMenuViewItemsAdded; i++)
			ahMenus [i] = GetMenu ()->GetSubMenu (1)->GetSubMenu (PLUGIN_MENU_VIEW_POS+i)->m_hMenu; //8 - 3

		_PluginMgr.UpdateMenuView ((HMENU*) ahMenus);
	}
}

void CMainFrame::OnAppExit()
{
	OnAppExit2 ();
}

void CMainFrame::OnMeasureItem(int , LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	m_odmenu.OnMeasureItem (lpMeasureItemStruct);
}

void CMainFrame::OnDrawItem(int , LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	m_odmenu.OnDrawItem (lpDrawItemStruct);
}

void CMainFrame::LoadMenuImages()
{
	if (!m_imgsMenu.Create (16, 16, ILC_COLOR32 | ILC_MASK, 30, 5))
		return;

	if (!m_dimgsMenu.Create (16, 16, ILC_COLOR32 | ILC_MASK, 30, 5))
		return;

	UINT aImgs[] = {
		IDB_TOOL0_16, IDB_TOOL_DLD_16, IDB_TOOL_DLD_16,
		IDB_TOOL_DLD_16,
		IDB_TOOL_SCH_16,
		IDB_TOOL_HFE_16, IDB_TOOL_SITES_16, IDB_TOOL_SPIDER_16,
	};

	UINT adImgs[] = {
		IDB_TOOL0_16_D, IDB_TOOL_DLD_16_D, IDB_TOOL_DLD_16_D,
		IDB_TOOL_DLD_16_D,
		IDB_TOOL_SCH_16_D,
		IDB_TOOL_HFE_16_D, IDB_TOOL_SITES_16_D, IDB_TOOL_SPIDER_16_D,
	};

	ASSERT (sizeof (aImgs) == sizeof (adImgs));

	for (int i = 0; i < sizeof (aImgs) / sizeof (UINT); i++)
	{
		CBitmap bmp, bmpd;

		bmp.Attach (SBMP (aImgs [i]));
		bmpd.Attach (SBMP (adImgs [i]));

		if (_TB_USE_ALPHA)
		{
			if (i == 0 || _SkinMgr.tbUseAlpha_ForAllPluginMenuImages ())
			{
				ConvertBmp32WithAlphaToBmp32WithoutAlpha (bmp, GetSysColor (COLOR_MENU));
				ConvertBmp32WithAlphaToBmp32WithoutAlpha (bmpd, GetSysColor (COLOR_MENU));

				m_imgsMenu.Add (&bmp, GetSysColor (COLOR_MENU));
				m_dimgsMenu.Add (&bmpd, RGB (255, 0, 255));
			}
			else
			{
				m_imgsMenu.Add (&bmp, RGB (255, 0, 255));
				m_dimgsMenu.Add (&bmpd, RGB (255, 0, 255));
			}
		}
		else
		{
			m_imgsMenu.Add (&bmp, RGB (255, 0, 255));
			m_dimgsMenu.Add (&bmpd, RGB (255, 0, 255));
		}
	}

	m_odmenu.SetImageList (&m_imgsMenu, &m_dimgsMenu);

	LoadToolImages ();
}

void CMainFrame::OnShowmainwindow()
{
	if (IsIconic ())
		ShowWindow (SW_RESTORE);
	else
		ShowWindow (SW_SHOW);

	SetForegroundWindow ();
}

void CMainFrame::OnStartall()
{
	_DldsMgr.StartAllDownloads (TRUE);
}

void CMainFrame::OnStopall()
{
	_DldsMgr.StopAllDownloads (TRUE);
}

void CMainFrame::OnHelp()
{
	::HtmlHelp (m_hWnd, "Help\\Free Download Manager.chm", HH_DISPLAY_TOC, NULL);
}

void CMainFrame::OnHomepage()
{
	fsOpenUrlInBrowser ("http://www.freedownloadmanager.org/");
}

//void CMainFrame::OnProggeneralsettings()
//{
//	CPrgSheet sheet (LS (L_PRGGENSET), this);
//
//	sheet.Init ();
//
//	_DlgMgr.OnDoModal (&sheet);
//	sheet.DoModal ();
//	SaveSettings (0xffffffff);
//	_DlgMgr.OnEndDialog (&sheet);
//}

void CMainFrame::ReadSettings()
{
	m_bCloseAsMinimize = _App.Prg_CloseAsMinimize ();
	m_bMinToTray = _App.Prg_MinToTray ();
}

void CMainFrame::SaveSettings(DWORD dwWhat)
{
	if (dwWhat & 1)
	{
		_App.Prg_CloseAsMinimize (m_bCloseAsMinimize);
		_App.Prg_MinToTray (m_bMinToTray);
	}
}

void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_CLOSE && m_bCloseAsMinimize)
	{
		ShowWindow (SW_MINIMIZE);
		return;
	}

	CFrameWnd::OnSysCommand(nID, lParam);
}

void CMainFrame::OnEndSession(BOOL bEnding)
{
	onExit (false);
	CFrameWnd::OnEndSession(bEnding);
}

void CMainFrame::OnTurnoffwhendone()
{
	fsShutdownType enType = (fsShutdownType) _App.WD_LastShutdownType ();

	if (_pwndScheduler->TurnoffWhenDone (enType))
	{
		_pwndScheduler->TurnoffWhenDone (enType, FALSE);
		return;
	}

	if (_App.WD_LastShutdownType_DontAsk () == FALSE)
	{
		CDlg_ShutdownType dlg;
		dlg.m_enType = enType;
		if (IDCANCEL == _DlgMgr.DoModal (&dlg))
			return;

		enType = dlg.m_enType;
		_App.WD_LastShutdownType (enType);

		if (dlg.m_bRemember)
			_App.WD_LastShutdownType_DontAsk (TRUE);
	}

	_pwndScheduler->TurnoffWhenDone (enType, TRUE);
}

void CMainFrame::OnUpdateTurnoffwhendone(CCmdUI* pCmdUI)
{
	fsShutdownType enType = (fsShutdownType) _App.WD_LastShutdownType ();
	pCmdUI->SetCheck (_pwndScheduler->TurnoffWhenDone (enType) ? 1 : 0);
}

void CMainFrame::UpdateTitle()
{
	SetWindowText (vmsFdmAppMgr::getAppName());
}

void CMainFrame::OnAddsite()
{
	_pwndSites->OnSitesAdd ();
}

void CMainFrame::BuildSwitchToMenu()
{
	CMenu *pMenu = GetMenu ()->GetSubMenu (1)->GetSubMenu (6 - 3);
	m_odmenu.RemoveMenuItem (pMenu, 0, TRUE);
	for (int i = 0; i < _PluginMgr.GetPluginCount (); i++)
	{
		fsPluginInfo *plug = &_PluginMgr.Plugin (i);
		CString str;
		str.Format ("%s\tAlt+%d", plug->strName.GetString(), i+1);
		fsODMenuItemData *pData = m_odmenu.AddItem (pMenu, ID_SWITCH_TO_START+i, str);
		if (pData)
			pData->iCheckImage = ODMENU_CHECKIMAGE_RADIO;
	}
}

void CMainFrame::OnSwitchTo(UINT nID)
{
	SetActivePlugin (nID - ID_SWITCH_TO_START);
}

void CMainFrame::OnUpdateSwitchTo(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck (pCmdUI->m_nID - ID_SWITCH_TO_START == (UINT)m_wndView.m_wndClient.m_plugs2.GetActivePlugin () ? 1 : 0);
}

void CMainFrame::OnViewSwbar()
{
}

void CMainFrame::OnUpdateViewSwbar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (m_wndView.m_wndClient.m_bShowSWBar ? 1 : 0);
}

void CMainFrame::RemovePluginMenuView()
{
	RemovePluginMenuView2 ();
	if (m_cPluginMenuViewInserted == 0)
		return;
	CMenu *pMenu = GetMenu ()->GetSubMenu (1);
	while (m_cPluginMenuViewInserted--)
	{
		m_odmenu.RemoveMenuItem (pMenu, PLUGIN_MENU_VIEW_POS, TRUE); //8 - 3
	}
	m_cPluginMenuViewInserted = 0;
	DrawMenuBar ();
}

void CMainFrame::AddPluginMenuView(HMENU hMenuView, fsSetImage* pImages, int cImages, wgMenuViewItem *pItems, int cItems)
{
	m_pPluginMenuViewItems = pItems;
	if (pItems)
	{
		m_cPluginMenuViewItems = cItems;
		CMenu *pMenu = GetMenu ()->GetSubMenu (1);
		int iStartPos = PLUGIN_MENU_VIEW_POS;//8 - 3;
		for (int i = 0; i < cItems; i++)
			m_odmenu.InsertMenuItem (pMenu, pItems [i].pszName, WGP_MENU_VIEWSMPLITEM_CMDSTART+i, iStartPos++, TRUE);
		m_cPluginMenuViewInserted = cItems;
	}
	AddPluginMenuView (hMenuView, pImages, cImages);
	DrawMenuBar ();
}

void CMainFrame::OnAltPlusDigit(UINT nID)
{
	int iPlug = nID - ID_ALT1;
	if (iPlug < _PluginMgr.GetPluginCount ())
		m_wndView.m_wndClient.m_plugs2.SetActivePlugin (iPlug);
}

//void CMainFrame::OnUpdatePluginMenuView(CCmdUI *pCmdUI)
//{
//	int iItem = pCmdUI->m_nID - WGP_MENU_VIEWSMPLITEM_CMDSTART;
//	if (iItem >= m_cPluginMenuViewItems)
//		return;
//	pCmdUI->SetCheck (*m_pPluginMenuViewItems [iItem].pbView ? 1 : 0);
//}

void CMainFrame::OnViewToolbar()
{
	CFrameWnd::OnBarCheck (AFX_IDW_TOOLBAR);
	CControlBar* pBar = GetControlBar(AFX_IDW_TOOLBAR);
	if (pBar != NULL)
		_App.View_Toolbar ((pBar->GetStyle() & WS_VISIBLE) != 0);
}

void CMainFrame::OnViewStatusbar()
{
	CFrameWnd::OnBarCheck (AFX_IDW_STATUS_BAR);
	CControlBar* pBar = GetControlBar(AFX_IDW_STATUS_BAR);
	if (pBar != NULL)
		_App.View_Statusbar ((pBar->GetStyle() & WS_VISIBLE) != 0);
}

void CMainFrame::SaveState(DWORD dwWhat)
{
	SaveSettings (dwWhat);

	if (dwWhat & 2)
	{
		m_wndView.m_wndClient.SaveState ();
		_App.View_SaveWndPlacement (this, "MainFrm");

#ifdef FLOATING_WIN
		if (m_pFloatWndsThread)
		{
			m_pFloatWndsThread->m_wndFloating.SaveState ();
			m_pFloatWndsThread->m_wndFloatingInfo.SaveState ();
		}
#endif

	}
}

void CMainFrame::ApplyLanguage()
{
	ApplyLanguageToMenu ();

	LPCSTR ppszToolTips [] = {
		"",
		LS (L_LIGHT), LS (L_MEDIUM), LS (L_HEAVY),
		"",
		LS (L_STARTALLDLDS), LS (L_STOPALLDLDS), LS (L_PAUSEALLDOWNLOADS),
		"",
		LS (L_SETTINGS)
	};

	_TBMgr.UpdateGroupToolTips (0, ppszToolTips, sizeof (ppszToolTips) / sizeof (LPCSTR));

	m_wndStatusBar.SetToolTipText (ID_SB_TOTALSPEED, LS (L_TOTAL_SPEED_SBTEXT));

	UpdateTitle ();
}

void CMainFrame::ApplyLanguageToMenu()
{
	RemovePluginMenu ();
	RemovePluginMenuView ();
	m_odmenu.Detach ();
	SetMenu (NULL);

	SetMenu (CMenu::FromHandle (LoadMenu (AfxGetInstanceHandle (), MAKEINTRESOURCE (IDR_MAINFRAME))));

	m_odmenu.Attach (GetMenu (), TRUE);

	_PluginMgr.OnNewLng();// _LngMgr.GetLngName(_LngMgr.GetCurLng()));

	SetMenuImages ();
	BuildSwitchToMenu ();

	fsSetText aMenuBarTexts [] = {
		fsSetText (0, LS (L_FILE)),
		fsSetText (1, LS (L_VIEW)),
		fsSetText (2, LS (L_OPTIONS)),
		fsSetText (3, LS (L_TOOLS)),
		fsSetText (4, LS (L_HELP)),
	};
	m_odmenu.SetMenuItemsText (GetMenu (), aMenuBarTexts, sizeof (aMenuBarTexts) / sizeof (fsSetText), TRUE);

	CString strCut = LS (L_CUT), strCopy = LS (L_COPY), strPaste = LS (L_PASTE),
		strDldOpt = LS (L_SETTINGS),
		strDldDef = LS (L_DLDDEFOPT),
		strPrgGen = LS (L_PRGGENSET),
		strLight = LS (L_LIGHT),
		strMedium = LS (L_MEDIUM),
		strHeavy = LS (L_HEAVY),
		strExit = LS (L_EXIT),
		strExport = LS (L_EXPORTSETTINGS),
		strSaveAll = LS (L_SAVEALL),
		//strSaveAll(MAKEINTRESOURCE(IDS_SAVEALL)),
		strImpFromClip = LS (L_IMPORTURLSFROMCLIPBOARD);

	strCut += "\tCtrl+X"; strCopy += "\tCtrl+C"; strPaste += "\tCtrl+V";
	strDldOpt += "\tCtrl+O";
	strDldDef += "\tCtrl+E";
	strPrgGen += "\tCtrl+P";
	strLight += "\tCtrl+1";
	strMedium += "\tCtrl+2";
	strHeavy += "\tCtrl+3";
	strExport += '\t';
	strSaveAll += "\tCtrl+S";
	strImpFromClip += "\tCtrl+Shift+V";

	fsSetText aMenu0Texts [] = {
		fsSetText (0, LS (L_EXPORT)),
		fsSetText (1, LS (L_IMPORT)),
	};
	m_odmenu.SetMenuItemsText (GetMenu ()->GetSubMenu (0), aMenu0Texts,
		sizeof (aMenu0Texts) / sizeof (fsSetText), TRUE);

	fsSetText aTexts [] = {
		fsSetText (ID_FILE_EXPORT_EXPORTLISTOFDOWNLOADS, LS (L_EXPORTLISTOFDLDS)),
		fsSetText (ID_FILE_IMPORT_IMPORTLISTOFDOWNLOADS, LS (L_IMPORTLISTOFDLDS)),
		fsSetText (ID_FILE_IMPORT_IMPORTLISTOFDOWNLOADSFROMCLIPBOARD, strImpFromClip),
		fsSetText (ID_APP_EXIT, strExit),
		fsSetText (ID_VIEW_TOOLBAR, LS (L_TOOLBAR)),
		fsSetText (ID_VIEW_STATUS_BAR, LS (L_STATUSBAR)),
		//fsSetText (ID_DLINFOBOX, LS (L_DLSINFO)),
		//fsSetText (ID_DROPBOX, LS (L_DROPBOX)),
		fsSetText (ID_DLDROPTIONS, strDldOpt),
		fsSetText (ID_OPTIONS_SM, LS (L_OPTIONS_SM)),
		fsSetText (ID_DLDDEFOPTIONS, strDldDef),
		fsSetText (ID_PROGGENERALSETTINGS, strPrgGen),
		fsSetText (ID_TUM_LIGHT, strLight),
		fsSetText (ID_TUM_MEDIUM, strMedium),
		fsSetText (ID_TUM_HEAVY, strHeavy),
		fsSetText (ID_TURNOFFWHENDONE, LS (L_TURNOFFWD)),
		fsSetText (ID_EXITWHENDONE, LS (L_EXITWHENDONE)),
		fsSetText (ID_APP_ABOUT, LS (L_ABOUT)),
	};

	m_odmenu.SetMenuItemsText (GetMenu (), aTexts, sizeof (aTexts) / sizeof (fsSetText), FALSE);
	m_odmenu.SetMenuItemText (GetMenu ()->GetSubMenu (1), LS (L_SWITCHTO), 6, TRUE);
	m_odmenu.SetMenuItemText (GetMenu ()->GetSubMenu (2), LS (L_TUM), GetTumMenuPosition (), TRUE);
	m_wndView.m_wndClient.m_plugs2.OnNewLng ();

	DrawMenuBar ();
}

void CMainFrame::SetMenuImages()
{
	fsSetImage images []  =
	{
		fsSetImage (ID_DLDROPTIONS, 6),
		fsSetImage (ID_DLDDEFOPTIONS, 9),

		fsSetImage (ID_TUM_LIGHT, 0),
		fsSetImage (ID_TUM_MEDIUM, 1),
		fsSetImage (ID_TUM_HEAVY, 2),

		fsSetImage (ID_APP_ABOUT, 10),
	};

	m_odmenu.SetImages (images, sizeof (images) / sizeof (fsSetImage));
}

void CMainFrame::UpdateSettings()
{
	_TumMgr.ReadSettings ();
	_DldsMgr.ReadSettings ();
	_DldsMgr.setNeedApplyTrafficLimit ();
}

#ifdef FLOATING_WIN
void CMainFrame::OnDropBox()
{
	m_pFloatWndsThread->m_wndFloating.Show (!_App.View_FloatingWindow ());
}

void CMainFrame::OnUpdateDropBox(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck (_App.View_FloatingWindow () ? 1 : 0);
}
#endif

UINT CMainFrame::m_umsgTaskBarCreated = 0;

LRESULT CMainFrame::WindowProc(UINT msg, WPARAM wp, LPARAM lp)
{
	if (msg == m_umsgTaskBarCreated)
		_TrayMgr.TestIcon ();

	else if (msg == m_nShutdownMsg)
		PostMessage (WM_COMMAND, ID_APP_EXIT_2);

	return CFrameWnd::WindowProc (msg, wp, lp);
}

void CMainFrame::OnNcRButtonUp(UINT nHitTest, CPoint point)
{
	CFrameWnd::OnNcRButtonUp(nHitTest, point);
}

void CMainFrame::OnTBQueryDelete(NMHDR *, LRESULT *res)
{
	*res = FALSE;
}

void CMainFrame::OnTBQueryInsert(NMHDR *, LRESULT *res)
{
	*res = FALSE;
}

void CMainFrame::OnTBBeginDrag(NMHDR *, LRESULT *res)
{
	*res = FALSE;
}

void CMainFrame::OnTBEndDrag(NMHDR *, LRESULT *res)
{
	*res = FALSE;
}

void CMainFrame::OnTBBeginAdjust(NMHDR *, LRESULT *res)
{

	*res = FALSE;
}

void CMainFrame::OnTBEndAdjust(NMHDR *, LRESULT *res)
{
	*res = FALSE;
}

void CMainFrame::OnTBCustHelp(NMHDR *, LRESULT *res)
{
	*res = FALSE;
}

void CMainFrame::OnTBReset(NMHDR *, LRESULT *res)
{
	*res = FALSE;
}

void CMainFrame::OnTBGetButtonInfo(NMHDR *nm, LRESULT *res)
{
	*res = _TBMgr.OnTBGetButtonInfo (nm);
}

void CMainFrame::OnTBChange(NMHDR *, LRESULT *res)
{
	*res = FALSE;
}

BOOL CMainFrame::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	LPNMHDR nm = (LPNMHDR) lParam;
	if (_TBMgr.OnNotify (nm) == FALSE && nm->code != TBN_GETINFOTIPW)
	{
		if (nm->idFrom == AFX_IDW_TOOLBAR)
		{
			switch (nm->code)
			{
				case TBN_QUERYDELETE:
					OnTBQueryDelete (nm, pResult);
					break;

				case TBN_QUERYINSERT:
					OnTBQueryInsert (nm, pResult);
					break;

				case TBN_BEGINADJUST:
					OnTBBeginAdjust (nm, pResult);
					break;

				case TBN_ENDADJUST:
					OnTBEndAdjust (nm, pResult);
					break;

				case TBN_BEGINDRAG:
					OnTBBeginDrag (nm, pResult);
					break;

				case TBN_ENDDRAG:
					OnTBEndDrag (nm, pResult);
					break;

				case TBN_CUSTHELP:
					OnTBCustHelp (nm, pResult);
					break;

				case TBN_RESET:
					OnTBReset (nm, pResult);
					break;

				case TBN_GETBUTTONINFO:
					OnTBGetButtonInfo (nm, pResult);
					break;

				case TBN_TOOLBARCHANGE:
					OnTBChange (nm, pResult);
					break;

				default:
					return DefWindowProc (WM_NOTIFY, wParam, lParam);
			}

			return TRUE;
		}
	}

	*pResult = FALSE;
	return FALSE;
}

void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
		case 1:
			KillTimer (1);
			break;

		case 2:
			if (FALSE == is_MouseInTray ())
			{
				KillTimer (2);
				HideBalloon ();
			}
			break;

		case 3:
			KillTimer (3);
			HideBalloon ();
			break;

		case 4:
			if (m_bBalloonShowing == FALSE)
			{
				if (is_MouseInTray ())
				{
					Balloon_ShowDLInfo (FALSE);
					SetTimer (2, 200, NULL);
				}
			}
			KillTimer (4);
		break;

		case 7:
			KillTimer (7);
			_TrayMgr.setTip (vmsFdmAppMgr::getAppName ());
			break;

		case 9:
			KillTimer (9);
			_TrayMgr.TestIcon ();
			break;
	}
}

void CMainFrame::AddPluginMenuView(HMENU hMenu, fsSetImage* pImages, int cImages)
{
	if (hMenu == NULL)
		return;

	if (m_cMenuViewItemsAdded)
		return;

	m_cMenuViewItemsAdded = m_odmenu.InsertMenu (CMenu::FromHandle (hMenu), PLUGIN_MENU_VIEW_POS, GetMenu ()->GetSubMenu (1)); //8 - 3

	if (pImages) m_odmenu.SetImages (pImages, cImages);
}

void CMainFrame::RemovePluginMenuView2()
{
	if (m_cMenuViewItemsAdded)
	{
		m_odmenu.RemoveMenu (PLUGIN_MENU_VIEW_POS + m_cMenuViewItemsAdded - 1, m_cMenuViewItemsAdded, GetMenu ()->GetSubMenu (1)); //8 - 3
		m_cMenuViewItemsAdded = 0;
	}
}

BOOL CMainFrame::OnQueryEndSession()
{
	if (!CFrameWnd::OnQueryEndSession())
		return FALSE;

	return _PluginMgr.QueryExit ();
}

void CMainFrame::OnInsert()
{
	fsPluginInfo& plug = _PluginMgr.Plugin (
		m_wndView.m_wndClient.m_plugs2.GetActivePlugin ());
	::PostMessage (plug.hWnd, WM_WGP_INSERT, 0, 0);
}

void CMainFrame::HideBalloon()
{
	if (m_bBalloonShowing)
	{
		m_strTimeoutBallon_Msgs = "";
		_TrayMgr.ShowBalloon ("", "");

		MSG msg;
		PeekMessage (&msg, m_hWnd, WM_TRAYMSG, WM_TRAYMSG, PM_REMOVE);

		if (m_pFdmBalloon)
		{
			SAFE_DELETE (m_pFdmBalloon);
			SAFE_DELETE (m_pFdmBalloonContent);
			m_enFdmBalloonContentType = FBCT_UNKNOWN;
		}

		m_bBalloonShowing = FALSE;
	}
}

void CMainFrame::ShowBalloon(LPCSTR pszInfo, LPCSTR pszTitle, BOOL bCheckSettings, DWORD dwIcon)
{
	if (bCheckSettings && _App.Notif_UseBalloon () == FALSE)
		return;

	if (m_bTrayMenuShowing == FALSE)
	{
		_TrayMgr.ShowBalloon (pszInfo, pszTitle, dwIcon);
		m_bBalloonShowing = TRUE;
	}
}

void CMainFrame::Balloon_ShowDLInfo(BOOL bCheckSettings)
{
	CString str;

	if (bCheckSettings && _App.Notif_UseBalloon () == FALSE)
		return;

	const fsDownloadsMgr::TotalProgress &tp = _DldsMgr.getTotalProgress ();
	try
	{
		if (tp.uTotalSize)
		{
			CString str2;

			double fDownloaded = (double)(__int64)tp.uDownloaded;
			fDownloaded /= (__int64)tp.uTotalSize;
			fDownloaded *= 100.0;

			str2.Format (LS (L_PERC_DOWNLOADED_INTOTAL), (int)fDownloaded);

			str += str2;

			if (tp.uSpeed)
			{
				double fTimeLeft = (double) ((__int64)(tp.uTotalSize-tp.uDownloaded));
				fTimeLeft /= (__int64)tp.uSpeed;
				str2.Format (LS (L_LEFT_TO_DOWNLOAD_AT), (LPCSTR)fsTimeInSecondsToStr((int)fTimeLeft));
				str += ", "; str += str2; str += ' ';
				str += (LPCSTR)BytesToString (tp.uSpeed);
				str += '/'; str += LS (L_S);
			}
			else
			{
				str += '.';
			}
		}
	}
	catch (const std::exception& ex)
	{
		ASSERT (FALSE);
		vmsLogger::WriteLog("CMainFrame::Balloon_ShowDLInfo " + tstring(ex.what()));
	}
	catch (...)
	{
		ASSERT (FALSE);
		vmsLogger::WriteLog("CMainFrame::Balloon_ShowDLInfo unknown exception");
	}

	if (!str.IsEmpty ())
		str += "\n";

	_DldsMgr.LockList (true);
	size_t nCount = _DldsMgr.GetCount ();
	for (size_t i = 0; i < nCount; i++)
	{
		vmsDownloadSmartPtr dld = _DldsMgr.GetDownload (i);

		if (dld->pMgr->IsRunning ())
		{
			if (i)
				str += '\n';

			CString strtmp;
			char szFile [MY_MAX_PATH];

			CDownloads_Tasks::GetFileName (dld, szFile);

			if (dld->pMgr->GetDownloadingSectionCount ())
				strtmp.Format ("%s - %d%%", szFile, (int) dld->pMgr->GetPercentDone ());
			else if (dld->pMgr->IsCantStart () == FALSE)
				strtmp.Format ("%s - %s...", szFile, LS (L_STARTING));
			else
				strtmp.Format ("%s - %s", szFile, LS (L_ERR));

			str += strtmp;
		}
	}
	_DldsMgr.UnlockList (true);

	if (str != "")
	{
		CString s = LS (L_ACTIVEDLDS);
		s += ':';
		ShowBalloon (str, s, FALSE);
	}
	else
	{
		ShowBalloon (LS (L_THEREARENOACTDLDS), vmsFdmAppMgr::getAppName (), FALSE);
	}
}

void CMainFrame::ShowTimeoutBalloon(LPCSTR pszInfo, LPCSTR pszTitle, DWORD dwIcon, BOOL bClear)
{
	TimeoutBalloonInfo *info = new TimeoutBalloonInfo;
	info->bClear = bClear;
	info->dwIcon = dwIcon;
	info->strInfo = pszInfo;
	info->strTitle = pszTitle;
	AfxGetApp ()->m_pMainWnd->PostMessage (WM_SHOW_BALLOON, 0, (LPARAM)info);
}

#ifdef FLOATING_WIN
void CMainFrame::OnDlinfobox()
{
	if (_App.View_FloatingInfoWindow ())
	{
		m_pFloatWndsThread->m_wndFloatingInfo.TurnOffWindow ();
	}
	else
	{
		_App.View_FloatingInfoWindow (TRUE);
		_pwndDownloads->UpdateTrayIconPlusOthers ();
	}
}
#endif

void CMainFrame::OnActivateWebinterface()
{
	if (_httpServer.is_Running())
		_httpServer.Shutdown();
	else
		_httpServer.Start();
}

void CMainFrame::OnUpdateActivateWebinterface(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (_httpServer.is_Running() ? 1 : 0);
}

void CMainFrame::RebuidDownloadsList()
{
#ifdef FLOATING_WIN
	if (m_pFloatWndsThread)
		m_pFloatWndsThread->m_wndFloatingInfo.RebuildList ();
#endif
}

void CMainFrame::RecalcLayout(BOOL bNotify)
{
	CFrameWnd::RecalcLayout(bNotify);

	if (IsWindow (_TBMgr) == FALSE ||
			IsWindow (m_wndView) == FALSE )
		return;

	_TBMgr.AutoSize ();

	REBARBANDINFO rbbi;
	rbbi.cbSize = sizeof (rbbi);
	rbbi.fMask = RBBIM_IDEALSIZE | RBBIM_SIZE;
	int nIndex = m_wndReBar.GetReBarCtrl ().IDToIndex (1);
	CRect rc; _TBMgr.GetWindowRect (&rc);
	rbbi.cx = rbbi.cxIdeal = rc.Width ();
	VERIFY (m_wndReBar.GetReBarCtrl ().SetBandInfo (nIndex, &rbbi));
}

void CMainFrame::OnProceedFurherInitialization()
{
	m_bInited = TRUE;
	CFdmApp* app = (CFdmApp*) AfxGetApp ();
	int i = 0;
	for (i = 0; i < app->m_vUrlsToAdd.size (); i++)
	{
		BOOL bSilent = app->m_vUrlsToAdd[i].bForceSilent;// ? TRUE : _App.Monitor_Silent();
		BOOL bAdded = UINT_MAX != _pwndDownloads->CreateDownload (app->m_vUrlsToAdd [i].strUrl, FALSE, NULL,
			NULL, bSilent);

		if (bAdded && bSilent)
			ShowTimeoutBalloon (app->m_vUrlsToAdd [i].strUrl, LS (L_DOWNLOADADDED), NIIF_INFO, TRUE);
	}

	_pwndScheduler->GetMgr ()->ExciteEvent (EV_STARTUP);

	_DldsMgr.setNeedProcessDownloads ();

	switch (_pwndDownloads->Get_DWWN ())
	{
		case DWWN_LISTOFDOWNLOADS:
			_pwndDownloads->ApplyCurrentFilter ();
			break;

		//case DWWN_HISTORY:
		//	_pwndDownloads->ApplyHistoryCurrentFilter ();
		//	break;
	}

	InterlockedIncrement (&m_cThreadsRunning);
	DWORD dw;
	CloseHandle (CreateThread (NULL, 0, _threadAutosave, this, 0, &dw));

	SetTimer (9, 30*1000, NULL);
}

void CMainFrame::OnAppAbout()
{
	if (_DldsMgr.IsDeletingNow ())
		return;
	((CFdmApp*) AfxGetApp ())->OnAppAbout ();
}

void CMainFrame::OnExportlistofdownloads()
{
	CDlgExportDownloads dlg;
	_DlgMgr.DoModal (&dlg);
}

void CMainFrame::OnImportlistofdownloads()
{
	CString strFilter;
	strFilter.Format ("%s (*.txt)|*.txt|%s (*.xml)|*.xml||", LS (L_URLLISTFILES), LS (L_DLINFOLISTFILES));
	CFileDialog dlg (TRUE, "txt", NULL, OFN_NOCHANGEDIR|OFN_HIDEREADONLY, strFilter, this);

	if (_DlgMgr.DoModal (&dlg) == IDCANCEL)
		return;

	if (dlg.GetFileExt ().CompareNoCase ("txt") == 0)
		ImportListOfDownloads_FromURLListFile (dlg.GetPathName ());
	else
		ImportListOfDownloads_FromDLInfoListFile (dlg.GetPathName ());
}

void CMainFrame::appendDiagnostics(CString&sMsg, const CString& sDiagnostics) const
{
	CString sTmp;
	sMsg = LS (L_CANT_DETECT_PATH_TO_ORBIT_APPDATA);
	CString sFmt = LS (L_SYS_DIAGNOSTICS_FMT);
	sTmp.Format((LPCTSTR)sFmt, (LPCTSTR)sDiagnostics);
	sMsg += " ";
	sMsg += sTmp;
}

void CMainFrame::appendErrorCode(CString& sMsg, HRESULT hr) const
{
	CString sTmp;
	CString sFmt = LS (L_ERROR_CODE_FMT);
	sTmp.Format((LPCTSTR)sFmt, hr, hr);
	sMsg += " ";
	sMsg += sTmp;
}

void CMainFrame::OnExitwhendone()
{
	_pwndScheduler->ExitWhenDone (_pwndScheduler->ExitWhenDone () == FALSE);
}

void CMainFrame::OnUpdateExitwhendone(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (_pwndScheduler->ExitWhenDone () ? 1 : 0);
}

void CMainFrame::OnFind()
{
	CDlgFind dlg;
	if (IDOK == _DlgMgr.DoModal (&dlg))
	{
		_pwndDownloads->FindDownloads_Start ();
		m_wndView.m_wndClient.m_plugs2.SetActivePlugin (0);
	}
}

void CMainFrame::OnFindnext()
{
	m_wndView.m_wndClient.m_plugs2.SetActivePlugin (0);
	_pwndDownloads->FindDownloads_FindNext ();
}

void CMainFrame::OnUpdateFindnext(CCmdUI* pCmdUI)
{
	pCmdUI->Enable (_pwndDownloads->IsFindNextAvail () ? 1 : 0);
}

BOOL CMainFrame::OnEraseBkgnd(CDC* pDC)
{
	return CFrameWnd::OnEraseBkgnd(pDC);
}

void CMainFrame::LoadToolImages()
{
	if (!m_imgsTool.Create (_TB_SIZE_X, _TB_SIZE_Y, ILC_COLOR32 | ILC_MASK, 10, 5))
		return;

	if (!m_dimgsTool.Create (_TB_SIZE_X, _TB_SIZE_Y, ILC_COLOR32 | ILC_MASK, 10, 5))
		return;

	CBitmap bmp, bmpd;

	bmp.Attach (SBMP (IDB_TOOL0));
	bmpd.Attach (SBMP (IDB_TOOL0_D));

	if (_TB_USE_ALPHA)
	{
		ConvertBmp32WithAlphaToBmp32WithoutAlpha (bmp, GetSysColor (COLOR_3DFACE));
		ConvertBmp32WithAlphaToBmp32WithoutAlpha (bmpd, GetSysColor (COLOR_3DFACE));
	}

	m_imgsTool.Add (&bmp, RGB (255, 0, 255));
	m_dimgsTool.Add (&bmpd, RGB (255, 0, 255));
}

LRESULT CMainFrame::OnShowTrayMenu(WPARAM, LPARAM)
{
	ShowTrayMenu (FALSE);
	return 0;
}

void CMainFrame::OnDldCreatebatch()
{
	_pwndDownloads->OnDldcreatebatch ();
}

#ifdef FLOATING_WIN
void CMainFrame::ShowFloatingInfoWindow(BOOL bShow)
{
	m_pFloatWndsThread->m_wndFloatingInfo.NeedToShow (bShow);
}

BOOL CMainFrame::IsFloatingInfoWindowVisible()
{
	return (m_pFloatWndsThread) ? ::IsWindowVisible (m_pFloatWndsThread->m_wndFloatingInfo.m_hWnd) : FALSE;
}
#endif

bool mainfrm__is_separator (char c)
{
	return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

void CMainFrame::OnFileImportImportlistofdownloadsfromclipboard()
{
	vmsDWCD_AdditionalParameters ap;
	ap.dwMask = DWCDAP_GROUP;

	CString strURLs = _ClipbrdMgr.Text ();
	LPCSTR pszURLs = strURLs;

	DLDS_LIST v;
	vmsDownloadsGroupSmartPtr pGrp;

	while (*pszURLs)
	{
		while (mainfrm__is_separator (*pszURLs))
			*pszURLs++;

		CString strURL;

		while (*pszURLs)
		{
			if (mainfrm__is_separator (*pszURLs))
			{
				LPCSTR psz = pszURLs+1;
				while (mainfrm__is_separator (*psz))
					psz++;
				if (*psz == 0)
					break;
				if (_strnicmp (psz, "http://", 7) == 0 ||
						_strnicmp (psz, "https://", 8) == 0 ||
						_strnicmp (psz, "ftp://", 6) == 0)
				{

					pszURLs = psz;
					break;
				}
			}

			strURL += *pszURLs++;
		}

		if (strURL != "")
		{
			if (pGrp == NULL)
			{
				CDlg_ChooseGroup dlg;
				if (IDOK != _DlgMgr.DoModal (&dlg))
					return;
				pGrp = dlg.m_pGroup;
			}

			vmsDownloadSmartPtr dld;
			Download_CreateInstance (dld);

			if (FALSE == _pwndDownloads->CreateDownloadWithDefSettings (dld, strURL))
				continue;

			dld->pGroup = pGrp;
			if (dld->pMgr->GetDownloadMgr ())
			{
				fsDownload_Properties *dp = dld->pMgr->GetDownloadMgr ()->GetDP ();
				SAFE_DELETE_ARRAY (dp->pszFileName);
				dp->pszFileName = new char [pGrp->strOutFolder.Length () + 1];
				lstrcpy (dp->pszFileName, pGrp->strOutFolder);
			}

			v.push_back (dld);
		}
	}

	if (v.size () != 0)
		_pwndDownloads->CreateDownloads (v, NULL);
}

void CMainFrame::OnOptionsSm()
{
	CSiteManagerSheet sheet (LS (L_OPTIONS_SM), this);
	_DlgMgr.DoModal (&sheet);
}

BOOL CMainFrame::is_MouseInTray()
{
	POINT pt;
	return GetCursorPos (&pt) && abs (pt.x-m_balloonX) < 3 && abs (pt.y-m_balloonY) < 3;
}

void CMainFrame::OnTUMChanged()
{
	CDlg_TUMChanged dlg;
	_DlgMgr.DoModal (&dlg);
}

BOOL CMainFrame::ImportListOfDownloads_FromURLListFile(LPCSTR pszFile)
{
	CStdioFile file;

	if (FALSE == file.Open (pszFile, CFile::modeRead))
	{
		MessageBox (LS (L_CANTOPENFILE), LS (L_ERR), MB_ICONERROR);
		return FALSE;
	}

	DLDS_LIST v;
	vmsDownloadsGroupSmartPtr pGrp;

	CString strUrl;
	do
	{
		file.ReadString (strUrl);

		if (strUrl != "")
		{
			if (pGrp == NULL)
			{
				CDlg_ChooseGroup dlg;
				if (IDOK != _DlgMgr.DoModal (&dlg))
					return FALSE;
				pGrp = dlg.m_pGroup;
			}

			vmsDownloadSmartPtr dld;
			Download_CreateInstance (dld);

			if (FALSE == _pwndDownloads->CreateDownloadWithDefSettings (dld, strUrl))
				continue;

			if (dld->pGroup != pGrp)
			{
				dld->pGroup = pGrp;
				LPSTR psz = new char [pGrp->strOutFolder.Length () + 1];
				lstrcpy (psz, pGrp->strOutFolder);
				delete [] dld->pMgr->GetDownloadMgr ()->GetDP ()->pszFileName;
				dld->pMgr->GetDownloadMgr ()->GetDP ()->pszFileName = psz;
			}

			v.push_back (dld);
		}
	}
	while (strUrl != "");

	if (v.size () != 0)
		_pwndDownloads->CreateDownloads (v, NULL);

	return TRUE;
}

BOOL CMainFrame::ImportListOfDownloads_FromDLInfoListFile(LPCSTR pszFile)
{
	IXMLDOMDocumentPtr spXML;
	IXMLDOMNodePtr spNode;

	spXML.CreateInstance (__uuidof (DOMDocument));

	if (spXML == NULL)
		return FALSE;

	spXML->put_async (FALSE);

	VARIANT_BOOL bRes;
	spXML->load (COleVariant (pszFile), &bRes);
	if (bRes == FALSE)
		return FALSE;

	spXML->selectSingleNode (L"FDM_Downloads_Info_List", &spNode);
	if (spNode == NULL)
		return FALSE;

	IXMLDOMNodeListPtr spNodeList;
	spNode->get_childNodes (&spNodeList);

	if (spNodeList == NULL)
		return FALSE;

	IXMLDOMNodePtr spItem;

	DLDS_LIST v;

	while (SUCCEEDED (spNodeList->nextNode (&spItem)) && spItem != NULL)
	{
		CComBSTR bstrName;
		spItem->get_nodeName (&bstrName);

		if (bstrName == L"download")
			ImportDownload (spItem, v);

		spItem = NULL;
	}

	if (v.size () != 0)
		_pwndDownloads->CreateDownloads (v, NULL);

	return TRUE;
}

BOOL CMainFrame::ImportDownload(IXMLDOMNode *pNode, DLDS_LIST_REF v)
{
	IXMLDOMNodeListPtr spNodeList;
	pNode->get_childNodes (&spNodeList);

	if (spNodeList == NULL)
		return FALSE;

	IXMLDOMNodePtr spItem;

	vmsDWCD_AdditionalParameters params;
	params.dwMask = 0;
	CString strUrl;
	CString strComment;

	while (SUCCEEDED (spNodeList->nextNode (&spItem)) && spItem != NULL)
	{
		CComBSTR bstrName;
		spItem->get_nodeName (&bstrName);

		if (bstrName == L"url")
		{
			COleVariant vtUrl;
			spItem->get_nodeTypedValue (&vtUrl);
			if (vtUrl.vt == VT_BSTR)
				strUrl = vtUrl.bstrVal;
		}
		else if (bstrName == L"comment")
		{
			COleVariant vt;
			spItem->get_nodeTypedValue (&vt);
			if (vt.vt == VT_BSTR)
				strComment = vt.bstrVal;
		}
		else if (bstrName == L"group")
		{
			COleVariant vt;
			spItem->get_nodeTypedValue (&vt);
			if (vt.vt == VT_BSTR)
			{
				CString str = vt.bstrVal;
				params.pGroup = _DldsGrps.FindGroupByName (str);
				if (params.pGroup == NULL)
					params.pGroup = _DldsGrps.FindGroup (GRP_OTHER_ID);
				params.dwMask |= DWCDAP_GROUP;
			}
		}

		spItem = NULL;
	}

	if (strUrl == "")
		return FALSE;

	vmsDownloadSmartPtr dld;
	Download_CreateInstance (dld);

	if (FALSE == _pwndDownloads->CreateDownloadWithDefSettings (dld, strUrl))
		return FALSE;

	if (params.dwMask & DWCDAP_GROUP)
	{
		if (dld->pGroup != params.pGroup)
		{
			dld->pGroup = params.pGroup;
			LPSTR psz = new char [params.pGroup->strOutFolder.Length () + 1];
			lstrcpy (psz, params.pGroup->strOutFolder);
			delete [] dld->pMgr->GetDownloadMgr ()->GetDP ()->pszFileName;
			dld->pMgr->GetDownloadMgr ()->GetDP ()->pszFileName = psz;
		}
	}

	dld->strComment = strComment;

	v.push_back (dld);

	return TRUE;
}

//void CMainFrame::OnUpdateLdf0(CCmdUI* pCmdUI)
//{
//	pCmdUI->Enable (_DldsMgr.get_LastFilesDownloaded ()->get_Count () != 0);
//}
//
//void CMainFrame::OnLDF(UINT nID)
//{
//	ShellExecute (NULL, "open", _DldsMgr.get_LastFilesDownloaded ()->get_FilePathName (nID - ID_LDF_0),
//		NULL, NULL, SW_SHOW);
//}
//
//void CMainFrame::OnLdfClear()
//{
//	_DldsMgr.LastFilesDownloaded_Clear ();
//}
//
//void CMainFrame::OnUpdateLdfClear(CCmdUI* pCmdUI)
//{
//	pCmdUI->Enable (_DldsMgr.get_LastFilesDownloaded ()->get_Count () != 0);
//}

void CMainFrame::OnPausealldlds()
{
	_TumMgr.setRestrainAll (!_TumMgr.getRestrainAll ());

	if (_TumMgr.getRestrainAll () && _App.View_DontShowPauseAlldldsEnabled () == FALSE)
	{
		UINT nRet = MyMessageBox (this, LS (L_PAUSEALLDLDSMODE_ON_MSG), _AppMgr.getAppName (),
			LS (L_DONTSHOWTHISWINDOWAGAIN), IDI_INFORMATION);
		if (nRet & 0x00010000)
			_App.View_DontShowPauseAlldldsEnabled (TRUE);
	}
}

void CMainFrame::OnUpdatePausealldlds(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (_TumMgr.getRestrainAll ());
}

void CMainFrame::OnUpdateTotalSpeed(CCmdUI *pCmdUI)
{
	CString str;
	str.Format("%s/%s", BytesToString(_pwndDownloads->getTotalDownloadingSpeed()).GetString(), LS(L_S));
	pCmdUI->SetText (str);
}

#ifdef FLOATING_WIN
void CMainFrame::OnUpdateDlinfobox(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (_App.View_FloatingInfoWindow () ? 1 : 0);
}
#endif

void CMainFrame::OnAppExit2()
{
	static bool _bWasExit = false;
	if (_bWasExit)
		return;
	_bWasExit = true;
	_DlgMgr.EndAllDialogs ();
	PostMessage (WM_CLOSE);
}

void CMainFrame::SetActivePlugin(int nIndex)
{
	m_wndView.m_wndClient.m_plugs2.SetActivePlugin (nIndex);
}

LRESULT CMainFrame::OnPowerBroadCast(WPARAM wParam, LPARAM)
{
	if (wParam == PBT_APMRESUMESUSPEND)
	{
		_pwndScheduler->GetMgr ()->RepairTasksNextTimes ();
		_pwndScheduler->m_wndTasks.Invalidate ();
	}
	return TRUE;
}

void CMainFrame::OnLoadatstartup()
{
	_AutorunMgr.SetAutoStart (!_AutorunMgr.IsAutoStart ());
}

void CMainFrame::OnUpdateLoadatstartup(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck (_AutorunMgr.IsAutoStart ());
}

int CMainFrame::GetTumMenuPosition()
{
	return 2;
}

DWORD WINAPI CMainFrame::_threadAutosave(LPVOID lp)
{
	CMainFrame *pthis = (CMainFrame*)lp;

	SetThreadPriority (GetCurrentThread (), THREAD_PRIORITY_LOWEST);

	while (WAIT_TIMEOUT == WaitForSingleObject (pthis->m_hevShuttingDown, _App.AutosaveInterval ()))
	{
		pthis->SaveAllData (1);
		pthis->PostMessage (WM_MAINFRM_SAVEALLDATA, 2);
	}

	InterlockedDecrement (&pthis->m_cThreadsRunning);

	return 0;
}

void CMainFrame::ShowOnDownloadDoneBalloon(fsDownload *dld)
{
	dld->AddRef ();
	AfxGetApp ()->m_pMainWnd->PostMessage (WM_SHOW_BALLOON, 1, (LPARAM)dld);
}

void CMainFrame::ShowFdmBalloon(CFdmBalloonContent* pContent, FdmBalloonContentType enCT)
{
	HideBalloon ();

	m_pFdmBalloon = new CFdmBalloon (pContent);
	m_enFdmBalloonContentType = enCT;
	if (m_pFdmBalloonContent)
		delete m_pFdmBalloonContent;
	m_pFdmBalloonContent = pContent;

	m_bBalloonShowing = true;
	m_pFdmBalloon->Create (this, true);

	SetTimer (3, _App.Notif_BalloonTimeout ()*1000, NULL);
}

LRESULT CMainFrame::OnShowBalloon(WPARAM wp, LPARAM lp)
{
	if (wp == 0)
	{
		TimeoutBalloonInfo *info = (TimeoutBalloonInfo*)lp;

		if (info->bClear)
			m_strTimeoutBallon_Msgs = "";

		CString str = m_strTimeoutBallon_Msgs;

		HideBalloon ();

		m_strTimeoutBallon_Msgs = info->strInfo;

		if (str != "")
		{
			m_strTimeoutBallon_Msgs += '\n';
			m_strTimeoutBallon_Msgs += str;
		}

		ShowBalloon (m_strTimeoutBallon_Msgs, info->strTitle, info->dwIcon);

		SetTimer (3, _App.Notif_BalloonTimeout ()*1000, NULL);

		delete info;
	}

	else if (wp == 1)
	{
		fsDownload *dld = (fsDownload*)lp;

		CFdmBalloon_OnDownloadDone *pOnDD = new CFdmBalloon_OnDownloadDone;

		if (m_pFdmBalloon != NULL && m_enFdmBalloonContentType == FBCT_ON_DOWNLOAD_DONE &&
			::IsWindow (m_pFdmBalloon->m_hWnd))
		{
			CFdmBalloon_OnDownloadDone *pOnDDnow = (CFdmBalloon_OnDownloadDone*)m_pFdmBalloonContent;
			size_t n0 = pOnDDnow->m_vItems.size () > 10 ? pOnDDnow->m_vItems.size () - 10 : 0;
			for (size_t i = n0; i < pOnDDnow->m_vItems.size (); i++)
				pOnDD->m_vItems.push_back (pOnDDnow->m_vItems [i]);
		}

		CFdmBalloon_OnDownloadDone::DownloadedItem dlitem;
		dlitem.strFile = dld->pMgr->get_OutputFilePathName ();
		char sz [MY_MAX_PATH] = "";
		CDownloads_Tasks::GetFileName (dld, sz);
		dlitem.strName = sz;
		pOnDD->m_vItems.push_back (dlitem);

		ShowFdmBalloon (pOnDD, FBCT_ON_DOWNLOAD_DONE);

		dld->Release ();
	}

	return 0;
}

LRESULT CMainFrame::OnMyBalloonClosed(WPARAM, LPARAM)
{
	ASSERT (m_pFdmBalloon != NULL);

	if (m_pFdmBalloon)
	{
		SAFE_DELETE (m_pFdmBalloon);
		SAFE_DELETE (m_pFdmBalloonContent);
		m_enFdmBalloonContentType = FBCT_UNKNOWN;
		m_bBalloonShowing = FALSE;
	}

	return 0;
}

LRESULT CMainFrame::OnDoModal(WPARAM, LPARAM lp)
{
	return _DlgMgr.DoModal ((CDialog*)lp);
}

void CMainFrame::SaveAllData (DWORD dwWhat)
{
	vmsAUTOLOCKSECTION (m_csSaveAllData);
	_pwndDownloads->SaveAll (dwWhat);
	_pwndScheduler->SaveAll (dwWhat);
	_pwndSites->SaveAll (dwWhat);
	SaveState (dwWhat);
	((CFdmApp*)AfxGetApp ())->SaveSettings ();
}

LRESULT CMainFrame::OnSaveAllData (WPARAM wp, LPARAM)
{
	SaveAllData (wp);
	return 0;
}

bool CMainFrame::onExit(bool bQueryExit)
{
	if (m_bExitHandlerPerformed)
		return true;

	vmsAUTOLOCKSECTION (m_csExit);

	if (_PluginMgr.IsWasExit ())
		return true;

	if (bQueryExit && !_PluginMgr.QueryExit ())
		return false;

	SetEvent (m_hevShuttingDown);

	SaveState (0xffffffff);

	m_odmenu.Detach ();
	_TrayMgr.Remove ();

#ifdef FLOATING_WIN
	m_pFloatWndsThread->m_wndFloating.HideAlways ();
	m_pFloatWndsThread->m_wndFloatingInfo.HideAlways ();
#endif

	ShowWindow (SW_HIDE);

	vmsAUTOLOCKSECTION (m_csSaveAllData);
	_PluginMgr.OnAppExit (FALSE);
	vmsAUTOLOCKSECTION_UNLOCK (m_csSaveAllData);

	((CFdmApp*)AfxGetApp ())->SaveSettings ();

	CFdmApp::ScheduleExitProcess (30);

	m_bExitHandlerPerformed = true;

	return true;
}

void CMainFrame::UpdateTumToolbarState()
{
	fsTUM FStum = _TumMgr.GetTUM ();
	CToolBarCtrl& toolBar = _TBMgr.GetToolBarCtrl ();

	toolBar.SetState(ID_TUM_HEAVY, FStum == TUM_HEAVY ? TBSTATE_PRESSED : TBSTATE_ENABLED);
	toolBar.SetState(ID_TUM_MEDIUM, FStum == TUM_MEDIUM ? TBSTATE_PRESSED : TBSTATE_ENABLED);
	toolBar.SetState(ID_TUM_LIGHT, FStum == TUM_LIGHT ? TBSTATE_PRESSED : TBSTATE_ENABLED);
}
