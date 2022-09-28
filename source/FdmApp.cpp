/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "stdafx.h"

#include "FdmApp.h"

//#include "dbghelp.h"
//#include "vmsDLL.h"

#include "MainFrm.h"
#include "UrlWnd.h"

//#include <initguid.h>
//#include "WGUrlReceiver.h"
//#include "../Fdm_i.c"
//#include "Dlg_UE.h"

//#include "WgUrlListReceiver.h"
//#include "CFDM.h"
//#include "FDMDownloadsStat.h"
//#include "FDMDownload.h"

#include "fsFDMCmdLineParser.h"
#include "mfchelp.h"
#include "vmsFilesToDelete.h"


#include "inetutil.h"
#include "vmsNotEverywhereSupportedFunctions.h"
//#include "SpiderWnd.h"

//extern CSpiderWnd *_pwndSpider;

//#include "vmsIeHelper.h"

//#include "FdmUiWindow.h"

//#include "CmdHistorySaver.h"
#include "vmsAppMutex.h"
//#include "vmsElevatedFdm.h"
//#include "vmsFdmCrashReporter.h"
#include "vmsTmpFileName.h"
#include "vmsRegisteredAppPath.h"
//#include "vmsFdmFilesDeleter.h"
//#include "vmsWinSecurity.h"

#include <crtdbg.h>

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

	//m_bCOMInited = m_bATLInited = m_bATLInited2 = FALSE;
	m_bEmbedding = FALSE;
	m_bStarting = TRUE;

	SYSTEMTIME time;
	GetLocalTime (&time);
	SystemTimeToFileTime (&time, &_timeAppHasStarted);

	m_pModuleState;
}

CFdmApp theApp;
vmsAppMutex _appMutex (_T ("Free Download Manager"));

//vmsFdmCrashReporter _CrashReporter;

BOOL CFdmApp::InitInstance()
{
	AfxEnableControlContainer ();

	//SetRegistryKey (IDS_COMPANY);


	//bool bContinue = true;
	//if (_CrashReporter.CheckIfSubmitDumpIsRequestedByCommandLine (bContinue))
	//{
	//	if (!bContinue)
	//		return FALSE;
	//}

	//CheckRegistry ();

	//fsIECatchMgr::CleanIEPluginKey ();

	//CString strPath = GetProfileString ("", "Path", "");
	//BOOL bNeedLocalRegister = FALSE;
	//if (strPath == "")
	//{
	//	CRegKey key;
	//	if (ERROR_SUCCESS == key.Open (HKEY_CURRENT_USER, "Software\\FreeDownloadManager.ORG\\Free Download Manager", KEY_WRITE))
	//		vmsSHCopyKey (HKEY_LOCAL_MACHINE, "Software\\FreeDownloadManager.ORG\\Free Download Manager", key);
	//	strPath = GetProfileString ("", "Path", "");
	//	bNeedLocalRegister = strPath != "";
	//}

	//TEST
	CString strPath = "";

	//if (GetFileAttributes (strPath + "\\fdm.exe") == DWORD (-1))
	//{
	//	strPath = "";
	//	//bNeedLocalRegister = false;
	//}

	if (strPath == "" || FALSE == SetCurrentDirectory (strPath))
		_dwAppState |= APPSTATE_PORTABLE_MODE;

	char szExeDir [MY_MAX_PATH], szExeFile [MY_MAX_PATH];
	GetModuleFileName (NULL, szExeFile, sizeof (szExeFile));
	fsGetPath (szExeFile, szExeDir);

	if (IS_PORTABLE_MODE)
	{
		strPath = szExeDir;
		SetCurrentDirectory (strPath);
	}

	m_strAppPath = strPath;
	if (m_strAppPath.IsEmpty () == FALSE)
	{
		if (m_strAppPath [m_strAppPath.GetLength ()-1] != '\\' &&
				m_strAppPath [m_strAppPath.GetLength ()-1] != '/')
			m_strAppPath += '\\';
	}

	//if (IS_PORTABLE_MODE == FALSE)
	//{
	//	CString strDataFldr = szExeDir;
	//	strDataFldr += "Data";

	//	if (m_strAppPath.CompareNoCase (szExeDir) &&
	//		 DWORD (-1) != GetFileAttributes (strDataFldr))
	//	{
	//		_dwAppState |= APPSTATE_PORTABLE_MODE;
	//		_dwAppState |= APPSTATE_PORTABLE_MODE_NOREG;
	//		m_strAppPath = szExeDir;
	//	}
	//}

	if (IS_PORTABLE_MODE)
	{
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

		_App.ApplySettingsToMutexes ();
	}

	BOOL bNoLng = FALSE;

	if (FALSE == InitLanguage ())
		bNoLng = TRUE;

	//if (strcmp (m_lpCmdLine, "-suis") == 0 ||
	//		strcmp (m_lpCmdLine, "-euis") == 0 ||
	//		strcmp (m_lpCmdLine, "-duis") == 0)
	//{
	//	IntegrationSettings ();
	//	return FALSE;
	//}

//	if (IS_PORTABLE_MODE)
//	{
//		char szTmpFile [MY_MAX_PATH];
//		CString str = m_strAppPath;
//		str += "Data";
//		CreateDirectory (str, NULL);
//		if (0 == GetTempFileName (str, "fdm", 0, szTmpFile))
//			MessageBox (NULL, LS (L_NOWRITEACCESSTODATAFOLDER), vmsFdmAppMgr::getAppName (), MB_ICONWARNING);
//		else
//			DeleteFile (szTmpFile);
//	}

	_SkinMgr.Initialize ();

	//_IECatchMgr.ReadSettings ();
	//_NOMgr.Initialize ();
	//_IECMM.ReadState ();

	//HRESULT hRes = OleInitialize (NULL);
	//
	//if (FAILED(hRes))
	//	return FALSE;
	//
	//m_bCOMInited = TRUE;

//	const tstring currentVersion = vmsFdmAppMgr::getVersion ()->m_fileVersion.ToString ();
//	bool currentVersionFirstRun = currentVersion != _App.RecentVersionRun ();
//	if (currentVersionFirstRun)
//		_App.RecentVersionRun (currentVersion);

	//vmsAppGlobalObjects::Create2 (currentVersionFirstRun);

	fsFDMCmdLineParser cmdline;

	cmdline.Parse (fsFDMCmdLineParser::Elevated);

	//if (cmdline.isRunAsElevatedTasksProcessor ())
	//{
	//	RunAsElevatedTasksProcessor (cmdline);
	//	return FALSE;
	//}

	if (cmdline.isNeedExit ())
		return FALSE;

	m_bForceSilentSpecified = cmdline.is_ForceSilentSpecified ();

	//if (cmdline.isNeedRegisterServer ())
	//{
	//	onNeedRegisterServer ();
	//	return FALSE;
	//}
	//else if (cmdline.isNeedUnregisterServer ())
	//{
	//	onNeedUnregisterServer ();
	//	return FALSE;
	//}

	//if (vmsWinSecurity::IsVistaOrHigher () && strncmp (m_lpCmdLine, "-nelvcheck", 10) && stricmp (m_lpCmdLine, "-autorun"))
	//{
	//	if (vmsWinSecurity::IsProcessElevated ())
	//	{
	//		WCHAR wsz [MAX_PATH] = L"";
	//		GetModuleFileNameW (NULL, wsz, MAX_PATH);
	//		std::wstring wstr = L"\"";
	//		wstr += wsz;
	//		wstr += L"\" -nelvcheck ";
	//		wstr += CT2WEX<> (m_lpCmdLine);
	//		_appMutex.CloseMutex ();
	//		STARTUPINFOW si = {0}; PROCESS_INFORMATION pi = {0};
	//		si.cb = sizeof (si);
	//		if (vmsWinSecurity::RunAsDesktopUser (wsz, (LPWSTR)wstr.c_str (), NULL, si, pi))
	//			return FALSE;
	//		_appMutex.Create ();
	//	}
	//}

	cmdline.Parse (fsFDMCmdLineParser::Normal);

	if (CheckFdmStartedAlready (m_bForceSilentSpecified == FALSE))
		return FALSE;

	//if (!InitATL())
	//	return FALSE;

//	_App.StartCount (_App.StartCount () + 1);

	//if (IS_PORTABLE_MODE && (_dwAppState & APPSTATE_PORTABLE_MODE_NOREG) == 0)
	//	Install_RegisterServer ();

	vmsFilesToDelete::Process ();

	//if (bNeedLocalRegister)
	//	RegisterServer (FALSE);

#ifdef _AFXDLL
	Enable3dControls();
#else
	Enable3dControlsStatic();
#endif

	CheckLocked ();

	_Snds.ReadSettings ();

	CMainFrame* pFrame = NULL;

	fsnew1 (pFrame, CMainFrame);
	//pFrame = new CMainFrame();

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

	//hRes = _Module.RegisterClassObjects (CLSCTX_LOCAL_SERVER,
	//			REGCLS_MULTIPLEUSE);
	//if (FAILED (hRes))
	//{
	//	LPVOID lpMsgBuf;
	//	FormatMessage(
	//			FORMAT_MESSAGE_ALLOCATE_BUFFER |
	//			FORMAT_MESSAGE_FROM_SYSTEM |
	//			FORMAT_MESSAGE_IGNORE_INSERTS,
	//			NULL,
	//			hRes,
	//			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	//			(LPTSTR) &lpMsgBuf,
	//			0,
	//			NULL
	//			);
	//
	//		MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );
	//
	//		LocalFree( lpMsgBuf );
	//}
	//m_bATLInited2 = SUCCEEDED (hRes);

	//m_bATLInited2 = FALSE; //VS

	//TEST
//	UINT port = AfxGetApp()->GetProfileInt("Webinterface", "Port", 0);
//	m_http.set_Port((unsigned short)port);
//	//SetDlgItemInt(IDC_PORT, m_http.get_Port());
//
//	if (AfxGetApp()->GetProfileInt("Webinterface", "AutoStart", 0) == 1)
//		m_http.Start();

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
	//if (m_bATLInited2)
	//	_Module.RevokeClassObjects();

	//if (IS_PORTABLE_MODE && (_dwAppState & APPSTATE_PORTABLE_MODE_NOREG) == 0)
	//	Install_UnregisterServer ();

	//if (m_bATLInited)
	//	_Module.Term();

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

	//m_wndDLURL.SubclassDlgItem (IDC__DOWNLOAD, this);
	//m_wndDLURL.Init ();
	//m_wndDLURL.SetUrl ("http://www.freedownloadmanager.org/download.htm");

	CString strVer;
	//char szVer [] = "%s %s build %s";
	//strVer.Format (szVer, LS (L_VERSION), vmsFdmAppMgr::getVersion ()->m_tstrProductVersion.c_str (), vmsFdmAppMgr::getBuildNumberAsString ());

	char szVer [] = "%s %s";
	strVer.Format (szVer, LS (L_VERSION), vmsFdmAppMgr::getVersion ()->m_tstrProductVersion.c_str ());

	SetDlgItemText (IDC__VER, strVer);

	m_wndFirm.SubclassDlgItem (IDC__DOWNLOAD, this);
	m_wndFirm.Init ();
	m_wndFirm.SetUrl ("https://github.com/59de44955ebd/FDM-UL");

	//SetDlgItemText (IDC__SUPPORT, LS (L_SUPPORTANDOTHER));
	//m_wndSupport.SubclassDlgItem (IDC__SUPPORT, this);
	//m_wndSupport.Init ();
	//m_wndSupport.SetUrl ("http://www.freedownloadmanager.org/support.htm");

	//SetDlgItemText (IDC__DOWNLOAD, LS (L_DLLATESTVERSION));

	//SetDlgItemText (IDC__WARN, LS (L_LICWARN));

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

	//if (pWnd->m_hWnd == GetDlgItem (IDC__WARN)->m_hWnd)
	//	pDC->SelectObject (&m_fontWarn);

	return hbr;
}

CFdmModule _Module;

//BEGIN_OBJECT_MAP(ObjectMap)
//OBJECT_ENTRY(CLSID_WGUrlReceiver, CWGUrlReceiver)
//OBJECT_ENTRY(CLSID_WGUrlListReceiver, CWgUrlListReceiver)
//OBJECT_ENTRY(CLSID_FDM, CFDM)
//OBJECT_ENTRY(CLSID_FDMDownloadsStat, CFDMDownloadsStat)
//OBJECT_ENTRY(CLSID_FDMDownload, CFDMDownload)
//OBJECT_ENTRY(CLSID_FdmUiWindow, CFdmUiWindow)
//END_OBJECT_MAP()

LONG CFdmModule::Unlock()
{
	AfxOleUnlockApp();
	return 0;
}

LONG CFdmModule::Lock()
{
	AfxOleLockApp();
	return 1;
}
LPCTSTR CFdmModule::FindOneOf(LPCTSTR p1, LPCTSTR p2)
{
	while (*p1 != NULL)
	{
		LPCTSTR p = p2;
		while (*p != NULL)
		{
			if (*p1 == *p)
				return CharNext(p1);
			p = CharNext(p);
		}
		p1++;
	}
	return NULL;
}

//BOOL CFdmApp::InitATL()
//{
//	m_bEmbedding = FALSE;
//
//	if (m_bATLInited == FALSE)
//	{
//		m_bATLInited = TRUE;
//		_Module.Init (ObjectMap, AfxGetInstanceHandle());
//		_Module.dwThreadID = GetCurrentThreadId ();
//	}
//
//	return TRUE;
//}

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
	//if (m_bCOMInited)
	//	CoUninitialize();
}

//LONG CFdmApp::_UEF(_EXCEPTION_POINTERS *info)
//{
//	static BOOL _b = FALSE;
//
//	if (_b)
//		return EXCEPTION_EXECUTE_HANDLER;
//
//	_b = TRUE;
//
//	typedef BOOL (WINAPI *FNMDWD)(HANDLE, DWORD, HANDLE, MINIDUMP_TYPE,
//		PMINIDUMP_EXCEPTION_INFORMATION, PMINIDUMP_USER_STREAM_INFORMATION, PMINIDUMP_CALLBACK_INFORMATION);
//	vmsDLL dll ("dbghelp.dll");
//	FNMDWD pfnMiniDumpWriteDump;
//	pfnMiniDumpWriteDump = (FNMDWD) dll.GetProcAddress ("MiniDumpWriteDump");
//	if (pfnMiniDumpWriteDump == NULL)
//		return EXCEPTION_EXECUTE_HANDLER;
//
//	MINIDUMP_EXCEPTION_INFORMATION eInfo;
//    eInfo.ThreadId = GetCurrentThreadId();
//    eInfo.ExceptionPointers = info;
//    eInfo.ClientPointers = FALSE;
//
//	char szFile [MAX_PATH]; char szName [100];
//	wsprintf (szName, "fdm%s.dmp", vmsFdmAppMgr::getBuildNumberAsString ());
//	GetTempPath (MAX_PATH, szFile);
//	lstrcat (szFile, szName);
//	HANDLE hFile = CreateFile (szFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
//		0, NULL);
//
//    pfnMiniDumpWriteDump(
//        GetCurrentProcess(),
//        GetCurrentProcessId(),
//        hFile,
//        MiniDumpNormal,
//        &eInfo,
//        NULL,
//        NULL);
//
//	CloseHandle (hFile);
//
//	//CUEDlg dlg;
//	//dlg.DoModal ();
//
//	TerminateProcess (GetCurrentProcess (), 0);
//	return 0;
//}

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
	//TODO
	if (IS_PORTABLE_MODE)
	{
//		vmsAppSettingsStore* pStgs = _App.get_SettingsStore ();
//		CString strStgsFile = fsGetDataFilePath ("settings.dat");
//		pStgs->SaveSettingsToFile (strStgsFile);
	}
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
