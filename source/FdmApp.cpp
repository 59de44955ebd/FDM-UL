/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "stdafx.h"

#include "FdmApp.h"

#include "MainFrm.h"
#include "UrlWnd.h"
#include "fsFDMCmdLineParser.h"
#include "vmsFilesToDelete.h"
#include "vmsAppMutex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CFdmApp, CWinApp)
	//{{AFX_MSG_MAP(CFdmApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CFdmApp::CFdmApp()
{
#ifdef _DEBUG
	// temporarily turn off
	AfxEnableMemoryTracking(FALSE);
	AfxEnableMemoryLeakDump(FALSE);
#endif

	//_CrtSetBreakAlloc(19022);
	//_CrtSetBreakAlloc(19021);
	//_CrtSetBreakAlloc(19019);

	m_bEmbedding = FALSE;
	m_bStarting = TRUE;

	SYSTEMTIME time;
	GetLocalTime (&time);
	SystemTimeToFileTime (&time, &_timeAppHasStarted);

	m_pModuleState;



}

CFdmApp theApp;
vmsAppMutex _appMutex (_T ("Free Download Manager"));

BOOL CFdmApp::InitInstance()
{
	//if (strPath == "" || FALSE == SetCurrentDirectory (strPath))
	_dwAppState |= APPSTATE_PORTABLE_MODE;
	_dwAppState |= APPSTATE_PORTABLE_MODE_NOREG;

	char szExeDir [MY_MAX_PATH], szExeFile [MY_MAX_PATH];
	GetModuleFileName (NULL, szExeFile, sizeof (szExeFile));
	fsGetPath (szExeFile, szExeDir);

	SetCurrentDirectory (szExeDir);

	m_strAppPath = szExeDir;

	if (m_strAppPath.IsEmpty () == FALSE)
	{
		if (m_strAppPath [m_strAppPath.GetLength ()-1] != '\\' &&
				m_strAppPath [m_strAppPath.GetLength ()-1] != '/')
			m_strAppPath += '\\';
	}

	// load settings from INI file with same name as exe
	char * p = strrchr(szExeFile, '.');
	*p = 0;
	CString strIniFile = szExeFile;
	strIniFile += ".ini";

	free((void*)m_pszProfileName);
	m_pszProfileName = _tcsdup(strIniFile);

	//vmsAppSettingsStore* pStgs = _App.get_SettingsStore ();
	//CString strStgsFile = m_strAppPath + "Data\\settings.dat";
	//fsBuildPathToFile (strStgsFile);
	//pStgs->LoadSettingsFromFile (strStgsFile);

	_App.ApplySettingsToMutexes (); // ???


	BOOL bNoLng = FALSE;

	if (FALSE == InitLanguage ())
		bNoLng = TRUE;

	_SkinMgr.Initialize ();

	//vmsAppGlobalObjects::Create2 (currentVersionFirstRun);

	fsFDMCmdLineParser cmdline;

//	cmdline.Parse (fsFDMCmdLineParser::Elevated);
//	if (cmdline.isNeedExit ())
//		return FALSE;

	m_bForceSilentSpecified = cmdline.is_ForceSilentSpecified ();

	cmdline.Parse (fsFDMCmdLineParser::Normal);

	if (CheckFdmStartedAlready (m_bForceSilentSpecified == FALSE))
		return FALSE;

	vmsFilesToDelete::Process ();

#ifdef _AFXDLL
	Enable3dControls();
#else
	Enable3dControlsStatic();
#endif

	CheckLocked ();

	_Snds.ReadSettings ();

	CMainFrame* pFrame = NULL;
	fsnew1 (pFrame, CMainFrame);

	m_pMainWnd = pFrame;

	if (FALSE == pFrame->LoadFrame(IDR_MAINFRAME, WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE,
		NULL, NULL))
	{
		return FALSE;
	}

	BOOL bHidden = _tcscmp (m_lpCmdLine, _T ("-autorun")) == 0;

	_App.View_ReadWndPlacement (pFrame, "MainFrm",
		bHidden ? fsAppSettings::RWPA_FORCE_SWHIDE_AND_KEEP_MINIMIZED_MAXIMIZED_STATE : fsAppSettings::RWPA_NONE);

	if (!bHidden)
	{
		if (_App.Prg_StartMinimized ())
		{
			if (IsWindowVisible (pFrame->m_hWnd))
				pFrame->ShowWindow (SW_MINIMIZE);
		}
		else
		{
			pFrame->UpdateWindow();
			if (pFrame->IsWindowVisible ())
				pFrame->SetForegroundWindow ();
		}
	}

	m_bStarting = FALSE;

	return TRUE;
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CUrlWnd	m_wndDLURL;
	CUrlWnd	m_wndFirm;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	CFont m_fntUnderline;
	CFont m_fontRegInfo;
	CFont m_fontWarn;
	CUrlWnd m_wndSupport;
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
	m_fontRegInfo.CreateFont (10, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "MS Sans Serif");
	m_fontWarn.CreateFont (12, 0, 0, 0, FW_LIGHT, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "Arial");
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CFdmApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
   	_DlgMgr.OnDoModal (&aboutDlg);
	aboutDlg.DoModal();
    _DlgMgr.OnEndDialog (&aboutDlg);
}

int CFdmApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

    CFont* fnt = GetFont ();
	LOGFONT lf;
	fnt->GetLogFont (&lf);
	lf.lfUnderline = TRUE;
	m_fntUnderline.CreateFontIndirect (&lf);

	CString strVer;
	char szVer [] = "%s %s";
	strVer.Format (szVer, LS (L_VERSION), vmsFdmAppMgr::getVersion ()->m_tstrProductVersion.c_str ());

	SetDlgItemText (IDC__VER, strVer);

	m_wndFirm.SubclassDlgItem (IDC__DOWNLOAD, this);
	m_wndFirm.Init ();
	m_wndFirm.SetUrl ("https://github.com/59de44955ebd/FDM-UL");

	SetWindowText (LS (L_ABOUT2));

	return TRUE;
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->m_hWnd == m_wndFirm.m_hWnd ||
		 pWnd->m_hWnd == m_wndDLURL.m_hWnd ||
		 pWnd->m_hWnd == m_wndSupport.m_hWnd)
	{
		pDC->SetTextColor (GetSysColor (26));
        pDC->SelectObject (&m_fntUnderline);
	}

	return hbr;
}

BOOL CFdmApp::InitLanguage()
{
	m_nNoLngsErrReason = 0;

	if (FALSE == _LngMgr.Initialize ())
	{
		m_nNoLngsErrReason = 1;
		return FALSE;
	}

	//int iLang = _LngMgr.FindLngByName (_App.View_Language ());
	//if (iLang == -1)
	//	iLang = 0;

	//if (FALSE == _LngMgr.LoadLng (iLang))
	//{
	//	if (iLang == 0 || FALSE == _LngMgr.LoadLng (0))
	//	{
	//		m_nNoLngsErrReason = 2;
	//		return FALSE;
	//	}
	//}

	//if (FALSE == _LngMgr.LoadLng(0))
	//{
	//	m_nNoLngsErrReason = 2;
	//	return FALSE;
	//}
	return TRUE;
}

BOOL CFdmApp::CheckFdmStartedAlready(BOOL bSetForIfEx)
{
	LPCSTR pszMainWnd = "Free Download Manager Main Window";
	if (_appMutex.isAnotherInstanceStartedAlready ())
	{
		_appMutex.CloseMutex ();

		if (bSetForIfEx)
		{
			HWND hWnd = FindWindow (pszMainWnd, NULL);
			if (IsIconic (hWnd))
				ShowWindow (hWnd, SW_RESTORE);
			else
			{
				WINDOWPLACEMENT wc;
				GetWindowPlacement (hWnd, &wc);
				if (wc.showCmd == SW_HIDE)
					ShowWindow (hWnd, SW_RESTORE);
			}

			SetForegroundWindow (hWnd);
			SetFocus (hWnd);
		}

		return TRUE;
	}

	return FALSE;
}

CFdmApp::~CFdmApp()
{
}

BOOL CFdmApp::Is_Starting()
{
	return m_bStarting;
}

void CFdmApp::CheckLocked()
{
	DWORD dwRes;

	do
	{
		HANDLE hMx = CreateMutex (NULL, TRUE, "_mx_FDM_Lock_Start_");
		dwRes = GetLastError ();
		CloseHandle (hMx);

		if (dwRes == ERROR_ALREADY_EXISTS)
			Sleep (100);
	}
	while (dwRes == ERROR_ALREADY_EXISTS);
}

void CFdmApp::SaveSettings()
{
//		vmsAppSettingsStore* pStgs = _App.get_SettingsStore ();
//		CString strStgsFile = fsGetDataFilePath ("settings.dat");
//		pStgs->SaveSettingsToFile (strStgsFile);
}

DWORD WINAPI CFdmApp::_threadExitProcess(LPVOID lp)
{
	Sleep (((DWORD)lp) * 1000);
	ASSERT (LPCSTR ("_threadExitProcess is called") == NULL);
	HANDLE hProcess = OpenProcess (PROCESS_TERMINATE, FALSE, GetCurrentProcessId ());
	TerminateProcess (hProcess, (DWORD)-1);
	return 0;
}

void CFdmApp::ScheduleExitProcess(DWORD dwSeconds)
{
	DWORD dw;
	CloseHandle (
		::CreateThread (NULL, 0, _threadExitProcess, (LPVOID)dwSeconds, 0, &dw));
}

AFX_MODULE_STATE* CFdmApp::GetModuleState()
{
	return m_pModuleState;
}
