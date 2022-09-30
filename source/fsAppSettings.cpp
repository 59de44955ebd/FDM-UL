/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "FdmApp.h"
#include "fsAppSettings.h"
#include "fsFindDownloadMgr.h"
#include "MainFrm.h"

//#include "fsWebPageDownloader.h"
#include "fsScheduleMgr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

fsAppSettings::fsAppSettings()
{
	m_dwWriteCacheSize = DWORD (-1);
	m_dwNonUtf8NameFixed = DWORD (-1);
	m_bPreventStandbyWhileDownloading = BOOL (-1);
	m_bDontSaveLogs = BOOL (-1);
}

fsAppSettings::~fsAppSettings()
{
}

fsInternetAccessTypeEx fsAppSettings::InternetAccessType()
{
	return (fsInternetAccessTypeEx) m_stgs.GetProfileInt (_T ("Network"), _T ("InternetAccessType"), IATE_NOPROXY);
}

void fsAppSettings::InternetAccessType(fsInternetAccessTypeEx enType)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("InternetAccessType"), enType);
}

CString fsAppSettings::UserName()
{
	return m_stgs.GetProfileString (_T ("Network"), _T ("UserName"), _T (""));
}

void fsAppSettings::UserName(LPCTSTR pszStr)
{
	m_stgs.WriteProfileString (_T ("Network"), _T ("UserName"), pszStr);
}

CString fsAppSettings::UserPassword()
{
	return m_stgs.GetProfileString (_T ("Network"), _T ("UserPassword"), _T (""));
}

void fsAppSettings::UserPassword(LPCTSTR pszStr)
{
	m_stgs.WriteProfileString (_T ("Network"), _T ("UserPassword"), pszStr);
}

CString fsAppSettings::Referer()
{
	return m_stgs.GetProfileString (_T ("Network"), _T ("Referer"), _T (""));
}

void fsAppSettings::Referer(LPCTSTR pszStr)
{
	m_stgs.WriteProfileString (_T ("Network"), _T ("Referer"), pszStr);
}

BOOL fsAppSettings::UseHttp11()
{
	return m_stgs.GetProfileInt (_T ("Network"), _T ("UseHttp1.1"), TRUE);
}

void fsAppSettings::UseHttp11(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("UseHttp1.1"), b);
}

DWORD fsAppSettings::FtpFlags()
{
	return m_stgs.GetProfileInt (_T ("Network"), _T ("FtpFlags"), FTP_USEPASSIVEMODE);
}

void fsAppSettings::FtpFlags(DWORD dw)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("FtpFlags"), dw);
}

fsFtpTransferType fsAppSettings::FtpTransferType()
{
	return (fsFtpTransferType) m_stgs.GetProfileInt (_T ("Network"), _T ("TransferType"), FTT_UNKNOWN);
}

void fsAppSettings::FtpTransferType(fsFtpTransferType enType)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("TransferType"), enType);
}

CString fsAppSettings::ASCIIExts()
{
	return m_stgs.GetProfileString (_T ("Network"), _T ("ASCIIExts"), _T ("txt htm html shtml"));
}

void fsAppSettings::ASCIIExts(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("Network"), _T ("ASCIIExts"), psz);
}

UINT fsAppSettings::RetriesTime()
{
	return m_stgs.GetProfileInt (_T ("Network"), _T ("RetriesTime"), 5000);
}

void fsAppSettings::RetriesTime(UINT u)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("RetriesTime"), u);
}

UINT fsAppSettings::SectionMinSize()
{
	return m_stgs.GetProfileInt (_T ("Network"), _T ("SectionMinSize"), 300*1024);
}

void fsAppSettings::SectionMinSize(UINT u)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("SectionMinSize"), u);
}

UINT fsAppSettings::MaxSections()
{
	return m_stgs.GetProfileInt (_T ("Network"), _T ("MaxSections"), 10);
}

void fsAppSettings::MaxSections(UINT u)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("MaxSections"), u);
}

UINT fsAppSettings::TrafficRestriction()
{
	return m_stgs.GetProfileInt (_T ("Network"), _T ("TrafficRestriction"), UINT_MAX);
}

void fsAppSettings::TrafficRestriction(UINT u)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("TrafficRestriction"), u);
}

UINT fsAppSettings::MaxAttempts()
{
	return m_stgs.GetProfileInt (_T ("Network"), _T ("MaxAttempts"), 20);
}

void fsAppSettings::MaxAttempts(UINT u)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("MaxAttempts"), u);
}

BOOL fsAppSettings::IgnoreRestrictions()
{
	return m_stgs.GetProfileInt (_T ("Network"), _T ("IgnoreRestrictions"), FALSE);
}

void fsAppSettings::IgnoreRestrictions(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("IgnoreRestrictions"), b);
}

BOOL fsAppSettings::RestartSpeedLow()
{
	return m_stgs.GetProfileInt (_T ("Network"), _T ("RestartSpeedLow"), FALSE);
}

void fsAppSettings::RestartSpeedLow(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("RestartSpeedLow"), b);
}

CString fsAppSettings::Agent()
{
	CString str = m_stgs.GetProfileString (_T ("Network"), _T ("Agent"), "");
	if (str == "")
		str = vmsFdmAppMgr::getAppAgentName ();
	if (str == "FDM 1.x")
		str = vmsFdmAppMgr::getAppAgentName ();
	return str;
}

void fsAppSettings::Agent(LPCSTR psz)
{
	if (lstrcmpi (psz, vmsFdmAppMgr::getAppAgentName ()) == 0)
		psz = "";
	m_stgs.WriteProfileString (_T ("Network"), _T ("Agent"), psz);
}

BOOL fsAppSettings::ReserveDiskSpace ()
{
	return m_stgs.GetProfileInt (_T ("Network"), _T ("ReserveDiskSpace"), TRUE);
}

void fsAppSettings::ReserveDiskSpace(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("ReserveDiskSpace"), b);
}

UINT fsAppSettings::Timeout()
{
	return m_stgs.GetProfileInt (_T ("Network"), _T ("Timeout"), 120000);
}

void fsAppSettings::Timeout(UINT u)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("Timeout"), u);
}

CString fsAppSettings::HttpProxy_Name()
{
	return m_stgs.GetProfileString (_T ("Network"), _T ("HttpProxy_Name"), "");
}

void fsAppSettings::HttpProxy_Name(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("Network"), _T ("HttpProxy_Name"), psz);
}

CString fsAppSettings::HttpProxy_UserName()
{
	return m_stgs.GetProfileString (_T ("Network"), _T ("HttpProxy_UserName"), "");
}

void fsAppSettings::HttpProxy_UserName(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("Network"), _T ("HttpProxy_UserName"), psz);
}

CString fsAppSettings::HttpProxy_Password()
{
	return m_stgs.GetProfileString (_T ("Network"), _T ("HttpProxy_Password"), "");
}

void fsAppSettings::HttpProxy_Password(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("Network"), _T ("HttpProxy_Password"), psz);
}

CString fsAppSettings::HttpsProxy_Name()
{
	return m_stgs.GetProfileString (_T ("Network"), _T ("HttpsProxy_Name"), "");
}

void fsAppSettings::HttpsProxy_Name(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("Network"), _T ("HttpsProxy_Name"), psz);
}

CString fsAppSettings::HttpsProxy_UserName()
{
	return m_stgs.GetProfileString (_T ("Network"), _T ("HttpsProxy_UserName"), "");
}

void fsAppSettings::HttpsProxy_UserName(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("Network"), _T ("HttpsProxy_UserName"), psz);
}

CString fsAppSettings::HttpsProxy_Password()
{
	return m_stgs.GetProfileString (_T ("Network"), _T ("HttpsProxy_Password"), "");
}

void fsAppSettings::HttpsProxy_Password(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("Network"), _T ("HttpsProxy_Password"), psz);
}

CString fsAppSettings::FtpProxy_Name()
{
	return m_stgs.GetProfileString (_T ("Network"), _T ("FtpProxy_Name"), "");
}

void fsAppSettings::FtpProxy_Name(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("Network"), _T ("FtpProxy_Name"), psz);
}

CString fsAppSettings::FtpProxy_UserName()
{
	return m_stgs.GetProfileString (_T ("Network"), _T ("FtpProxy_UserName"), "");
}

void fsAppSettings::FtpProxy_UserName(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("Network"), _T ("FtpProxy_UserName"), psz);
}

CString fsAppSettings::FtpProxy_Password()
{
	return m_stgs.GetProfileString (_T ("Network"), _T ("FtpProxy_Password"), "");
}

void fsAppSettings::FtpProxy_Password(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("Network"), _T ("FtpProxy_Password"), psz);
}

CString fsAppSettings::SocksProxy_Name()
{
	return m_stgs.GetProfileString (_T ("Network"), _T ("SocksProxy_Name"), "");
}

void fsAppSettings::SocksProxy_Name(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("Network"), _T ("SocksProxy_Name"), psz);
}

BOOL fsAppSettings::UseCookie()
{
	return m_stgs.GetProfileInt (_T ("Network"), _T ("UseCookie"), TRUE);
}

void fsAppSettings::UseCookie(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("UseCookie"), b);
}

BOOL fsAppSettings::UseSocksProxy()
{
	return m_stgs.GetProfileInt (_T ("Network"), _T ("UseSocksProxy"), FALSE);
}

void fsAppSettings::UseSocksProxy(BOOL bUse)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("UseSocksProxy"), bUse);
}

fsDownloadFileErrorProcessing fsAppSettings::NotFoundReaction()
{
	return (fsDownloadFileErrorProcessing) m_stgs.GetProfileInt (_T ("Network"), _T ("OnNotFound"), DFEP_STOP);
}

void fsAppSettings::NotFoundReaction(fsDownloadFileErrorProcessing val)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("OnNotFound"), val);
}

fsDownloadFileErrorProcessing fsAppSettings::AccDeniedReaction()
{
	return (fsDownloadFileErrorProcessing) m_stgs.GetProfileInt (_T ("Network"), _T ("OnAccDenied"), DFEP_STOP);
}

void fsAppSettings::AccDeniedReaction(fsDownloadFileErrorProcessing val)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("OnAccDenied"), val);
}

fsAlreadyExistReaction fsAppSettings::AlreadyExistReaction()
{
	return (fsAlreadyExistReaction) m_stgs.GetProfileInt (_T ("Network"), _T ("OnAlreadyExist"), AER_RENAME);
}

void fsAppSettings::AlreadyExistReaction(fsAlreadyExistReaction val)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("OnAlreadyExist"), val);
}

fsSizeChangeReaction fsAppSettings::SizeChangeReaction()
{
	return (fsSizeChangeReaction) m_stgs.GetProfileInt (_T ("Network"), _T ("OnSizeChange"), SCR_STOP);
}

void fsAppSettings::SizeChangeReaction(fsSizeChangeReaction val)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("OnSizeChange"), val);
}

CString fsAppSettings::AdditionalExtension()
{
	return m_stgs.GetProfileString (_T ("Network"), _T ("AddExt"), "");
}

void fsAppSettings::AdditionalExtension(LPCSTR pszExt)
{
	m_stgs.WriteProfileString (_T ("Network"), _T ("AddExt"), pszExt);
}

void fsAppSettings::Set_TUM(vmsTrafficUsageModeRawSettings aTUM[3])
{
	m_stgs.WriteProfileBinary (_T ("Network"), _T ("TUM"),
		(LPBYTE) aTUM, 3*sizeof (vmsTrafficUsageModeRawSettings));
}

BOOL fsAppSettings::Get_TUM(vmsTrafficUsageModeRawSettings aTUM[3])
{
	BYTE *pb;
	UINT sz;

	if (m_stgs.GetProfileBinary (_T ("Network"), _T ("TUM"), &pb, &sz))
	{
		if (sz == 3*sizeof (vmsTrafficUsageModeRawSettings))
		{
			CopyMemory (aTUM, pb, sz);
			delete [] pb;
			return TRUE;
		}
	}

	return FALSE;
}

fsTUM fsAppSettings::CurrentTUM()
{
	return (fsTUM) m_stgs.GetProfileInt (_T ("Network"), _T ("CurrentTUM"), TUM_HEAVY);
}

void fsAppSettings::CurrentTUM(fsTUM en)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("CurrentTUM"), en);
}

void fsAppSettings::DDR(fsDeleteDownloadReaction en)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("DDR"), en);
}

fsDeleteDownloadReaction fsAppSettings::DDR()
{
	return (fsDeleteDownloadReaction) m_stgs.GetProfileInt (_T ("Network"), _T ("DDR"), DDR_ASK);
}

void fsAppSettings::AutoDelCompleted(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("AutoDelCompleted"), b);
}

BOOL fsAppSettings::AutoDelCompleted()
{
	return m_stgs.GetProfileInt (_T ("Network"), _T ("AutoDelCompleted"), FALSE);
}

UINT fsAppSettings::AutosaveInterval()
{
	return m_stgs.GetProfileInt (_T ("Network"), _T ("Autosave"), 3*60*1000);
}

void fsAppSettings::AutosaveInterval(UINT nVal)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("Autosave"), nVal);
}

int fsAppSettings::NOW()
{
	return m_stgs.GetProfileInt (_T ("Network"), _T ("NOW"), 0);
}

void fsAppSettings::NOW(int i)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("NOW"), i);
}

int fsAppSettings::ActivePlugin()
{
	return m_stgs.GetProfileInt (_T ("Last"), _T ("ActivePlugin"), 0);
}

void fsAppSettings::ActivePlugin(int i)
{
	m_stgs.WriteProfileInt (_T ("Last"), _T ("ActivePlugin"), i);
}

UINT fsAppSettings::CreateDld_IdOfLastGrpSelected()
{
	return m_stgs.GetProfileInt (_T ("Last"), _T ("GrpId"), 0);
}

void fsAppSettings::CreateDld_IdOfLastGrpSelected(UINT n)
{
	m_stgs.WriteProfileInt (_T ("Last"), _T ("GrpId"), n);
}

BOOL fsAppSettings::Prg_StartMinimized()
{
	return m_stgs.GetProfileInt (_T ("General"), _T ("StartMinimized"), FALSE);
}

void fsAppSettings::Prg_StartMinimized(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("General"), _T ("StartMinimized"), b);
}

BOOL fsAppSettings::Prg_CloseAsMinimize()
{
	return m_stgs.GetProfileInt (_T ("General"), _T ("CloseAsMinimize"), TRUE);
}

void fsAppSettings::Prg_CloseAsMinimize(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("General"), _T ("CloseAsMinimize"), b);
}

BOOL fsAppSettings::Prg_MinToTray()
{
	return m_stgs.GetProfileInt (_T ("General"), _T ("MinToTray"), TRUE);
}

void fsAppSettings::Prg_MinToTray(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("General"), _T ("MinToTray"), b);
}

BOOL fsAppSettings::View_SWBar()
{
	return m_stgs.GetProfileInt (_T ("View"), _T ("SWBar"), TRUE);
}

void fsAppSettings::View_SWBar(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("View"), _T ("SWBar"), b);
}

BOOL fsAppSettings::View_AllGroups()
{
	return m_stgs.GetProfileInt (_T ("View"), _T ("AllGroups"), TRUE);
}

void fsAppSettings::View_AllGroups(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("View"), _T ("AllGroups"), b);
}

BOOL fsAppSettings::View_DLInfo()
{
	return m_stgs.GetProfileInt (_T ("View"), _T ("DLInfo"), TRUE);
}

void fsAppSettings::View_DLInfo(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("View"), _T ("DLInfo"), b);
}

BOOL fsAppSettings::View_SchedulerLog()
{
	return m_stgs.GetProfileInt (_T ("View"), _T ("SchedulerLog"), TRUE);
}

void fsAppSettings::View_SchedulerLog(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("View"), _T ("SchedulerLog"), b);
}

BOOL fsAppSettings::View_Toolbar()
{
	return m_stgs.GetProfileInt (_T ("View"), _T ("Toolbar"), TRUE);
}

void fsAppSettings::View_Toolbar(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("View"), _T ("Toolbar"), b);
}

BOOL fsAppSettings::View_Statusbar()
{
	return m_stgs.GetProfileInt (_T ("View"), _T ("StatusBar"), TRUE);
}

void fsAppSettings::View_Statusbar(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("View"), _T ("StatusBar"), b);
}

void fsAppSettings::View_SaveWndSize(CWnd *pWnd, LPCSTR pszName)
{
	CRect rc;
	pWnd->GetWindowRect (&rc);
	CString strx = pszName, stry = pszName;
	strx += 'x'; stry += 'y';
	m_stgs.WriteProfileInt (_T ("Windows"), strx, rc.right-rc.left);
	m_stgs.WriteProfileInt (_T ("Windows"), stry, rc.bottom-rc.top);
}

void fsAppSettings::View_ReadWndSize(CWnd *pWnd, LPCSTR pszName)
{
	CString strx = pszName, stry = pszName;
	strx += 'x'; stry += 'y';
	int cx, cy;
	cx = m_stgs.GetProfileInt (_T ("Windows"), strx, 0);
	cy = m_stgs.GetProfileInt (_T ("Windows"), stry, 0);

	if (cx > GetSystemMetrics (SM_CXSCREEN))
		cx = 0;
	if (cy > GetSystemMetrics (SM_CYSCREEN))
		cy = 0;

	if (cx && cy)
		pWnd->MoveWindow (0, 0, cx, cy);
}

void fsAppSettings::View_SaveWndPlacement(CWnd *pWnd, LPCSTR pszName)
{
	WINDOWPLACEMENT wp;
	wp.length = sizeof (wp);
	if (FALSE == pWnd->GetWindowPlacement (&wp))
		return;
	if (wp.showCmd == 0)
		return;
	m_stgs.WriteProfileBinary (_T ("Windows"), pszName, (LPBYTE)&wp, sizeof (wp));
}

void fsAppSettings::View_ReadWndPlacement(CWnd *pWnd, LPCSTR pszName, ReadWndPlacementAdjustment enRWPA)
{
	WINDOWPLACEMENT *wp;
	LPBYTE lp;
	UINT uSize;

	if (m_stgs.GetProfileBinary (_T ("Windows"), pszName, &lp, &uSize))
	{
		wp = (WINDOWPLACEMENT*) lp;

		CRect rcWA;

		HMONITOR hMon = MonitorFromRect (&wp->rcNormalPosition, MONITOR_DEFAULTTONEAREST);

		if (hMon)
		{
			MONITORINFO mi;
			mi.cbSize = sizeof(mi);
			GetMonitorInfo (hMon, &mi);
			rcWA = mi.rcWork;
		}
		else
		{
			if (!SystemParametersInfo (SPI_GETWORKAREA, 0, &rcWA, FALSE))
				rcWA = CRect (0, 0, GetSystemMetrics (SM_CXSCREEN), GetSystemMetrics (SM_CYSCREEN));
		}

		CRect rcIntersect;
		if (!IntersectRect (&rcIntersect, &rcWA, &wp->rcNormalPosition) || rcIntersect.Width () < 50 || rcIntersect.Height () < 50)
		{
			if (wp->rcNormalPosition.left >= rcWA.right || wp->rcNormalPosition.right <= rcWA.left)
			{
				wp->rcNormalPosition.left = rcWA.left + rcWA.Width () / 2;
				wp->rcNormalPosition.right = wp->rcNormalPosition.left + 40;
			}
			if (wp->rcNormalPosition.top >= rcWA.bottom || wp->rcNormalPosition.bottom <= rcWA.top)
			{
				wp->rcNormalPosition.top = rcWA.top + rcWA.Height () / 2;
				wp->rcNormalPosition.bottom = wp->rcNormalPosition.top + 40;
			}
		}

		bool bHide = false;

		if (enRWPA == RWPA_FORCE_SWHIDE)
			wp->showCmd = SW_HIDE;
		else if (enRWPA == RWPA_FORCE_SWHIDE_AND_KEEP_MINIMIZED_MAXIMIZED_STATE)
		{
			if (wp->showCmd == SW_MINIMIZE || wp->showCmd == SW_SHOWMINIMIZED ||
					wp->showCmd == SW_SHOWMINNOACTIVE)
			{
				bHide = true;
			}
			else if (wp->showCmd == SW_SHOWMAXIMIZED)
			{
				wp->flags |= WPF_RESTORETOMAXIMIZED;
				wp->showCmd = SW_SHOWMINIMIZED;
				bHide = true;
			}
			else
			{
				wp->showCmd = SW_HIDE;
			}
		}

		pWnd->SetWindowPlacement (wp);
		delete [] lp;

		if (bHide)
			pWnd->ShowWindow (SW_HIDE);
	}
	else
	{
		pWnd->ShowWindow (
			enRWPA == RWPA_FORCE_SWHIDE || enRWPA == RWPA_FORCE_SWHIDE_AND_KEEP_MINIMIZED_MAXIMIZED_STATE ? SW_HIDE : SW_SHOW);
	}
}

void fsAppSettings::View_SplitterRatio(LPCSTR pszName, float fRatio)
{
	m_stgs.WriteProfileBinary (_T ("Splitters"), pszName, (LPBYTE)&fRatio, sizeof (fRatio));
}

float fsAppSettings::View_SplitterRatio(LPCSTR pszName)
{
	LPBYTE pf;
	UINT nSize;
	float f = 0.5f;

	if (m_stgs.GetProfileBinary (_T ("Splitters"), pszName, &pf, &nSize))
	{
		if (pf [0] == 0 && pf [1] == 0 && pf [2] == 192 && pf [3] == 255)
			f = 0.1f;
		else
			CopyMemory (&f, pf, sizeof (f));

		delete [] pf;

		if (f < 0 || f > 1)
			f = 0.5;
	}

	return f;
}

void fsAppSettings::View_Language(LPCSTR pszLang)
{
	m_stgs.WriteProfileString (_T ("View"), _T ("Language"), pszLang);
}

CString fsAppSettings::View_Language()
{
	CString strLang = m_stgs.GetProfileString (_T ("View"), _T ("Language"), _T (""));
	if (strLang == "")
	{
		strLang = "English";
	}
	return strLang;
}

int fsAppSettings::Last_Autostart()
{
	return m_stgs.GetProfileInt (_T ("Last"), _T ("AutoStart"), 0);
}

void fsAppSettings::Last_Autostart(int i)
{
	m_stgs.WriteProfileInt (_T ("Last"), _T ("AutoStart"), i);
}

int fsAppSettings::View_DldInfoCurTab()
{
	return m_stgs.GetProfileInt (_T ("View"), _T ("DldInfoCurTab"), 0);
}

void fsAppSettings::View_DldInfoCurTab(int i)
{
	m_stgs.WriteProfileInt (_T ("View"), _T ("DldInfoCurTab"), i);
}

fsTUMManage fsAppSettings::TUMManage()
{
	return (fsTUMManage) m_stgs.GetProfileInt (_T ("Network"), _T ("TUMManage"), TM_OFF);
}

void fsAppSettings::TUMManage(fsTUMManage en)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("TUMManage"), en);
}

BYTE fsAppSettings::DropBoxWndBlend()
{
	return (BYTE) m_stgs.GetProfileInt (_T ("View"), _T ("DropBoxWndBlend"), 150);
}

void fsAppSettings::DropBoxWndBlend(BYTE b)
{
	m_stgs.WriteProfileInt (_T ("View"), _T ("DropBoxWndBlend"), b);
}

BYTE fsAppSettings::DownloadsInfoWndBlend()
{
	return (BYTE) m_stgs.GetProfileInt (_T ("View"), _T ("DownloadsInfoWndBlend"), 150);
}

void fsAppSettings::DownloadsInfoWndBlend(BYTE b)
{
	m_stgs.WriteProfileInt (_T ("View"), _T ("DownloadsInfoWndBlend"), b);
}

BOOL fsAppSettings::View_FloatingWindow()
{
	return m_stgs.GetProfileInt (_T ("View"), _T ("ShowFW"), TRUE);
}

void fsAppSettings::View_FloatingWindow(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("View"), _T ("ShowFW"), b);
}

BOOL fsAppSettings::DetLog()
{
	return m_stgs.GetProfileInt (_T ("Network"), _T ("DetLog"), FALSE);
}

void fsAppSettings::DetLog(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("DetLog"), b);
}

CString fsAppSettings::Download_CreateExt()
{
	return m_stgs.GetProfileString (_T ("Network"),"CreateExt", "");
}

void fsAppSettings::Download_CreateExt(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("Network"),"CreateExt", psz);
}

BOOL fsAppSettings::View_SizesInBytes()
{
	return m_stgs.GetProfileInt (_T ("View"), _T ("SizesInBytes"), FALSE);
}

void fsAppSettings::View_SizesInBytes(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("View"), _T ("SizesInBytes"), b);
}

//BOOL fsAppSettings::Avir_Perform()
//{
//	return m_stgs.GetProfileInt (_T ("Avir"), _T ("Perform"), FALSE);
//}
//
//void fsAppSettings::Avir_Perform(BOOL b)
//{
//	m_stgs.WriteProfileInt (_T ("Avir"), _T ("Perform"), b);
//}
//
//CString fsAppSettings::Avir_Name()
//{
//	return m_stgs.GetProfileString (_T ("Avir"), _T ("Name"), "");
//}
//
//void fsAppSettings::Avir_Name(LPCSTR psz)
//{
//	m_stgs.WriteProfileString (_T ("Avir"), _T ("Name"), psz);
//}
//
//CString fsAppSettings::Avir_Args()
//{
//	return m_stgs.GetProfileString (_T ("Avir"), _T ("Args"), "%file%");
//}
//
//void fsAppSettings::Avir_Args(LPCSTR psz)
//{
//	m_stgs.WriteProfileString (_T ("Avir"), _T ("Args"), psz);
//}
//
//CString fsAppSettings::Avir_Exts()
//{
//	return m_stgs.GetProfileString (_T ("Avir"), _T ("Exts"),
//		"exe com msi zip rar arj tar t?z bin cab doc");
//}
//
//void fsAppSettings::Avir_Exts(LPCSTR psz)
//{
//	m_stgs.WriteProfileString (_T ("Avir"), _T ("Exts"), psz);
//}

BOOL fsAppSettings::NewVerExists()
{
	return m_stgs.GetProfileInt (_T ("Update"), _T ("NewVerExists"), FALSE);
}

void fsAppSettings::NewVerExists(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Update"), _T ("NewVerExists"), b);
}

BOOL fsAppSettings::Network_Br_SettingsSaved()
{
	return m_stgs.GetProfileInt (_T ("Network"), _T ("BrUA_Saved"), FALSE);
}

void fsAppSettings::Network_Br_SettingsSaved(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("BrUA_Saved"), b);
}

BOOL fsAppSettings::Notif_UseBalloon()
{
	return m_stgs.GetProfileInt (_T ("Notifications"), _T ("UseBalloons"), TRUE);
}

void fsAppSettings::Notif_UseBalloon(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Notifications"), _T ("UseBalloons"), b);
}

DWORD fsAppSettings::Notif_BalloonTimeout()
{
	return m_stgs.GetProfileInt (_T ("Notifications"), _T ("BalloonTimeout"), 3);
}

#pragma warning (disable : 4100)

void fsAppSettings::Notif_BalloonTimeout(DWORD dw)
{
	m_stgs.WriteProfileInt (_T ("Notifications"), _T ("BalloonTimeout"), dw);
}

//BOOL fsAppSettings::View_FloatingInfoWindow()
//{
//	return m_stgs.GetProfileInt (_T ("View"), _T ("ShowFIW"), TRUE);
//}
//
//void fsAppSettings::View_FloatingInfoWindow(BOOL b)
//{
//	m_stgs.WriteProfileInt (_T ("View"), _T ("ShowFIW"), b);
//}

void fsAppSettings::NewDL_GroupId(UINT n)
{
	m_stgs.WriteProfileInt (_T ("NewDownload"), _T ("GroupId"), n);
}

UINT fsAppSettings::NewDL_GroupId()
{
	return m_stgs.GetProfileInt (_T ("NewDownload"), _T ("GroupId"),
		-1);
}

void fsAppSettings::NewDL_Group_old(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("NewDownload"), _T ("Group"), psz);
}

CString fsAppSettings::NewDL_Group_old()
{
	return m_stgs.GetProfileString (_T ("NewDownload"), _T ("Group"), "");
}

//BOOL fsAppSettings::Monitor_Silent()
//{
//	return m_stgs.GetProfileInt (_T ("Monitor"), _T ("Silent"), FALSE);
//}
//
//void fsAppSettings::Monitor_Silent(BOOL b)
//{
//	m_stgs.WriteProfileInt (_T ("Monitor"), _T ("Silent"), b);
//}

CString fsAppSettings::Snd_DownloadComplete()
{
	return m_stgs.GetProfileString (_T ("Sounds"), _T ("DownloadComplete"), "");
}

void fsAppSettings::Snd_DownloadComplete(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("Sounds"), _T ("DownloadComplete"), psz);
}

CString fsAppSettings::Snd_DownloadAdded()
{
	return m_stgs.GetProfileString (_T ("Sounds"), _T ("DownloadAdded"), "");
}

void fsAppSettings::Snd_DownloadAdded(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("Sounds"), _T ("DownloadAdded"), psz);
}

CString fsAppSettings::Snd_NoActiveDownloads()
{
	return m_stgs.GetProfileString (_T ("Sounds"), _T ("NoActiveDownloads"), "");
}

void fsAppSettings::Snd_NoActiveDownloads(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("Sounds"), _T ("NoActiveDownloads"), psz);
}

CString fsAppSettings::Snd_DownloadFailed()
{
	return m_stgs.GetProfileString (_T ("Sounds"), _T ("DownloadFailed"), "");
}

void fsAppSettings::Snd_DownloadFailed(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("Sounds"), _T ("DownloadFailed"), psz);
}

BOOL fsAppSettings::Snd_Use()
{
	return m_stgs.GetProfileInt (_T ("Sounds"), _T ("Use"), FALSE);
}

void fsAppSettings::Snd_Use(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Sounds"), _T ("Use"), b);
}

int fsAppSettings::Export_WhichDlds()
{
	return m_stgs.GetProfileInt (_T ("Export"), _T ("WhichDlds"), 0);
}

void fsAppSettings::Export_WhichDlds(int i)
{
	m_stgs.WriteProfileInt (_T ("Export"), _T ("WhichDlds"), i);
}

BOOL fsAppSettings::Export_DontExpCompleted()
{
	return m_stgs.GetProfileInt (_T ("Export"), _T ("DontComp"), TRUE);
}

void fsAppSettings::Export_DontExpCompleted(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Export"), _T ("DontComp"), b);
}

BOOL fsAppSettings::Export_Append()
{
	return m_stgs.GetProfileInt (_T ("Export"), _T ("Append"), TRUE);
}

void fsAppSettings::Export_Append(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Export"), _T ("Append"), b);
}

fsDLsWndWhatIsNow fsAppSettings::View_DWWN()
{
	return (fsDLsWndWhatIsNow) m_stgs.GetProfileInt (_T ("View"), _T ("DWWN"), DWWN_LISTOFDOWNLOADS);
}

void fsAppSettings::View_DWWN(fsDLsWndWhatIsNow en)
{
	m_stgs.WriteProfileInt (_T ("View"), _T ("DWWN"), en);
}

BOOL fsAppSettings::Deleted_Bypass()
{
	return m_stgs.GetProfileInt (_T ("Deleted"), _T ("Bypass"), FALSE);
}

void fsAppSettings::Deleted_Bypass(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Deleted"), _T ("Bypass"), b);
}

UINT fsAppSettings::Deleted_MaxCount()
{
	return m_stgs.GetProfileInt (_T ("Deleted"), _T ("MaxCount"), 500);
}

void fsAppSettings::Deleted_MaxCount(UINT u)
{
	m_stgs.WriteProfileInt (_T ("Deleted"), _T ("MaxCount"), u);
}

BOOL fsAppSettings::Deleted_ConfirmDeletion()
{
	return m_stgs.GetProfileInt (_T ("Deleted"), _T ("ConfirmDeletion"), TRUE);
}

void fsAppSettings::Deleted_ConfirmDeletion(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Deleted"), _T ("ConfirmDeletion"), b);
}

BOOL fsAppSettings::Deleted_BypassCompleted()
{
	return m_stgs.GetProfileInt (_T ("Deleted"), _T ("BypassCompleted"), TRUE);
}

void fsAppSettings::Deleted_BypassCompleted(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Deleted"), _T ("BypassCompleted"), b);
}

void fsAppSettings::Find_What(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("Find"), _T ("What"), psz);
}

CString fsAppSettings::Find_What()
{
	return m_stgs.GetProfileString (_T ("Find"), _T ("What"), "");
}

DWORD fsAppSettings::Find_Flags()
{
	return m_stgs.GetProfileInt (_T ("Find"), _T ("Flags"),
		SEARCHIN_FILENAME | SEARCHIN_URL | SEARCHIN_COMMENT | SEARCHIN_LOCFILENAME |
		SEARCHWH_LISTOFDLDS);
}

void fsAppSettings::Find_Flags(DWORD dw)
{
	m_stgs.WriteProfileInt (_T ("Find"), _T ("Flags"), dw);
}

UINT fsAppSettings::Find_GroupId()
{
	return m_stgs.GetProfileInt (_T ("Find"), _T ("GroupId"), -1);
}

void fsAppSettings::Find_GroupId(UINT n)
{
	m_stgs.WriteProfileInt (_T ("Find"), _T ("GroupId"), n);
}

void fsAppSettings::Find_TimeFrom(FILETIME &t)
{
	m_stgs.WriteProfileBinary (_T ("Find"), _T ("t1"),
		(LPBYTE) &t, sizeof (t));
}

FILETIME fsAppSettings::Find_TimeFrom()
{
	BYTE *pb;
	UINT sz;
	FILETIME t;
	ZeroMemory (&t, sizeof (t));

	if (m_stgs.GetProfileBinary (_T ("Find"), _T ("t1"), &pb, &sz))
	{
		if (sz == sizeof (t))
		{
			CopyMemory (&t, pb, sizeof (t));
			delete [] pb;
		}
	}

	return t;
}

void fsAppSettings::Find_TimeTo(FILETIME &t)
{
	m_stgs.WriteProfileBinary (_T ("Find"), _T ("t2"),
		(LPBYTE) &t, sizeof (t));
}

FILETIME fsAppSettings::Find_TimeTo()
{
	BYTE *pb;
	UINT sz;
	FILETIME t;
	ZeroMemory (&t, sizeof (t));

	if (m_stgs.GetProfileBinary (_T ("Find"), _T ("t2"), &pb, &sz))
	{
		if (sz == sizeof (t))
		{
			CopyMemory (&t, pb, sizeof (t));
			delete [] pb;
		}
	}

	return t;
}

UINT64 fsAppSettings::Find_FileSizeFrom()
{
	BYTE *pb;
	UINT sz;
	UINT64 u = 0;

	if (m_stgs.GetProfileBinary (_T ("Find"), _T ("s1"), &pb, &sz))
	{
		if (sz == sizeof (u))
		{
			CopyMemory (&u, pb, sizeof (u));
			delete [] pb;
		}
	}

	return u;
}

void fsAppSettings::Find_FileSizeFrom(UINT64 u)
{
	m_stgs.WriteProfileBinary (_T ("Find"), _T ("s1"),
		(LPBYTE) &u, sizeof (u));
}

void fsAppSettings::Find_FileSizeTo(UINT64 u)
{
	m_stgs.WriteProfileBinary (_T ("Find"), _T ("s2"),
		(LPBYTE) &u, sizeof (u));
}

UINT64 fsAppSettings::Find_FileSizeTo()
{
	BYTE *pb;
	UINT sz;
	UINT64 u = 0;

	if (m_stgs.GetProfileBinary (_T ("Find"), _T ("s2"), &pb, &sz))
	{
		if (sz == sizeof (u))
		{
			CopyMemory (&u, pb, sizeof (u));
			delete [] pb;
		}
	}

	return u;
}

//BOOL fsAppSettings::UseZipPreview()
//{
//	return m_stgs.GetProfileInt (_T ("Network"), _T ("UseZipPreview"), FALSE);
//}
//
//void fsAppSettings::UseZipPreview(BOOL b)
//{
//	m_stgs.WriteProfileInt (_T ("Network"), _T ("UseZipPreview"), b);
//}

BOOL fsAppSettings::MP_Mute()
{
	return m_stgs.GetProfileInt (_T ("MP"), _T ("Mute"), FALSE);
}

void fsAppSettings::MP_Mute(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("MP"), _T ("Mute"), b);
}

int fsAppSettings::MP_Volume()
{
	return m_stgs.GetProfileInt (_T ("MP"), _T ("Volume"), 50);
}

void fsAppSettings::MP_Volume(int i)
{
	m_stgs.WriteProfileInt (_T ("MP"), _T ("Volume"), i);
}

DWORD fsAppSettings::DownloadFlags()
{
	return m_stgs.GetProfileInt (_T ("Network"), _T ("Flags"),
		DPF_USEHIDDENATTRIB | DPF_DONTRESTARTIFNORESUME);
}

void fsAppSettings::DownloadFlags(DWORD dw)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("Flags"), dw);
}

BOOL fsAppSettings::NewDL_AutoStart()
{
	return m_stgs.GetProfileInt (_T ("NewDownload"), _T ("AutoStart"), TRUE);
}

void fsAppSettings::NewDL_AutoStart(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("NewDownload"), _T ("AutoStart"), b);
}

WORD fsAppSettings::RollBackSize()
{
	return (WORD)m_stgs.GetProfileInt (_T ("Network"), _T ("RollBackSize"), 3000);
}

void fsAppSettings::RollBackSize(WORD w)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("RollBackSize"), w);
}

BOOL fsAppSettings::CheckRecycleBinSize()
{
	return m_stgs.GetProfileInt (_T ("General"), _T ("CheckRBSize"), TRUE);
}

void fsAppSettings::CheckRecycleBinSize(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("General"), _T ("CheckRBSize"), b);
}

BOOL fsAppSettings::SM_KeepPasswords()
{
	return m_stgs.GetProfileInt (_T ("SiteManager"), _T ("KeepPasswords"), TRUE);
}

void fsAppSettings::SM_KeepPasswords(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("SiteManager"), _T ("KeepPasswords"), b);
}

BOOL fsAppSettings::SM_PwdsManualAddition()
{
	return m_stgs.GetProfileInt (_T ("SiteManager"), _T ("pma"), FALSE);
}

void fsAppSettings::SM_PwdsManualAddition(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("SiteManager"), _T ("pma"), b);
}

BOOL fsAppSettings::SM_DontSavePwdsToDisk()
{
	return m_stgs.GetProfileInt (_T ("SiteManager"), _T ("DontSavePwdsToDisk"), FALSE);
}

void fsAppSettings::SM_DontSavePwdsToDisk(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("SiteManager"), _T ("DontSavePwdsToDisk"), b);
}

BOOL fsAppSettings::FloatingWndsHideInFSMode()
{
	return m_stgs.GetProfileInt (_T ("General"), _T ("FltWndsHideInFSMode"), TRUE);
}

void fsAppSettings::FloatingWndsHideInFSMode(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("General"), _T ("FltWndsHideInFSMode"), b);
}

BOOL fsAppSettings::NewDL_GenerateNameAutomatically()
{
	return m_stgs.GetProfileInt (_T ("NewDownload"), _T ("GenerateNameAutomatically"), TRUE);
}

void fsAppSettings::NewDL_GenerateNameAutomatically(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("NewDownload"), _T ("GenerateNameAutomatically"), b);
}

void fsAppSettings::SaveStringList(LPCSTR pszSubKey, LPCSTR pszValue, CStringList &v)
{
	int lt = 0;
	int i = 0;
	for (i = 0; i < v.GetCount (); i++)
		lt += v.GetAt (v.FindIndex (i)).GetLength ();
	lt += v.GetCount ()+1;

	LPBYTE pb = new BYTE [lt];
	LPSTR pbp = (LPSTR)pb;

	for (i = 0; i < v.GetCount (); i++)
	{
		CString& str = v.GetAt (v.FindIndex (i));
		lstrcpy (pbp, str);
		pbp += str.GetLength ()+1;
	}

	*pbp = 0;
	m_stgs.WriteProfileBinary (pszSubKey, pszValue, pb, lt);

	delete[] pb; //???
}

BOOL fsAppSettings::LoadStringList(LPCSTR pszSubKey, LPCSTR pszValue, CStringList *v)
{
	LPBYTE pb = NULL;
	UINT lt = 0;

	v->RemoveAll ();

	if (FALSE == m_stgs.GetProfileBinary (pszSubKey, pszValue, &pb, &lt))
		return FALSE;
	if (pb == NULL || lt == 0)
		return FALSE;

	LPCSTR pbp = (LPCSTR)pb;

	while ((int)lt > 1)
	{
		v->AddTail (pbp);
		lt -= lstrlen (pbp)+1;
		pbp += lstrlen (pbp)+1;

	}

	delete [] pb;
	return TRUE;
}

BOOL fsAppSettings::FilesToDelete(CStringList &v)
{
	return LoadStringList ("FilesToDelete", "", &v);
}

void fsAppSettings::FilesToDelete_save(CStringList &v)
{
	SaveStringList ("FilesToDelete", "", v);
}

BOOL fsAppSettings::View_GCVButton()
{
	return m_stgs.GetProfileInt ("View", "GCVButton", TRUE);
}

void fsAppSettings::View_GCVButton(BOOL b)
{
	m_stgs.WriteProfileInt ("View", "GCVButton", b);
}

BOOL fsAppSettings::View_TUMChanged()
{
	return m_stgs.GetProfileInt ("View", "TUMChanged", TRUE);
}

void fsAppSettings::View_TUMChanged(BOOL b)
{
	m_stgs.WriteProfileInt ("View", "TUMChanged", b);
}

DWORD fsAppSettings::CreateBD_LastAtoZ()
{
	return (DWORD) m_stgs.GetProfileInt (_T ("Last"), _T ("CBD_AtoZ"), MAKELPARAM (0, 'Z' - 'A' - 1));
}

void fsAppSettings::CreateBD_LastAtoZ(DWORD dw)
{
	m_stgs.WriteProfileInt (_T ("Last"), _T ("CBD_AtoZ"), dw);
}

int fsAppSettings::WD_LastShutdownType()
{
	return m_stgs.GetProfileInt (_T ("Last"), _T ("WD_ShutdownType"), ST_SHUTDOWN);
}

void fsAppSettings::WD_LastShutdownType(int enType)
{
	m_stgs.WriteProfileInt (_T ("Last"), _T ("WD_ShutdownType"), enType);
}

BOOL fsAppSettings::WD_LastShutdownType_DontAsk()
{
	return m_stgs.GetProfileInt (_T ("Last"), _T ("WD_ShutdownType_DontAsk"), FALSE);
}

void fsAppSettings::WD_LastShutdownType_DontAsk(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Last"), _T ("WD_ShutdownType_DontAsk"), b);
}

BOOL fsAppSettings::DontSaveLogs()
{
	if (m_bDontSaveLogs == BOOL (-1))
		m_bDontSaveLogs = m_stgs.GetProfileInt (_T ("General"), _T ("DontSaveLogs"), TRUE);
	return m_bDontSaveLogs;
}

void fsAppSettings::DontSaveLogs(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("General"), _T ("DontSaveLogs"), m_bDontSaveLogs = b);
}

int fsAppSettings::Export_WhichHist()
{
	return m_stgs.GetProfileInt (_T ("Export"), _T ("WhichHist"), 0);
}

void fsAppSettings::Export_WhichHist(int i)
{
	m_stgs.WriteProfileInt (_T ("Export"), _T ("WhichHist"), i);
}

BOOL fsAppSettings::Export_Hist_CompletedOnly()
{
	return m_stgs.GetProfileInt (_T ("Export"), _T ("Hist_CompletedOnly"), TRUE);
}

void fsAppSettings::Export_Hist_CompletedOnly(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Export"), _T ("Hist_CompletedOnly"), b);
}

BOOL fsAppSettings::Export_Hist_Append()
{
	return m_stgs.GetProfileInt (_T ("Export"), _T ("Hist_Append"), TRUE);
}

void fsAppSettings::Export_Hist_Append(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Export"), _T ("Hist_Append"), b);
}

BOOL fsAppSettings::DownloadDialog_AutoClose()
{
	return m_stgs.GetProfileInt (_T ("View"), _T ("DldDlg_AutoClose"), TRUE);
}

void fsAppSettings::DownloadDialog_AutoClose(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("View"), _T ("DldDlg_AutoClose"), b);
}

BOOL fsAppSettings::DownloadDialog_Use()
{
	return m_stgs.GetProfileInt (_T ("View"), _T ("DldDlg_Use"), TRUE);
}

void fsAppSettings::DownloadDialog_Use(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("View"), _T ("DldDlg_Use"), b);
}

BOOL fsAppSettings::DownloadDialog_DontAskOnHide()
{
	return m_stgs.GetProfileInt (_T ("View"), _T ("DldDlg_DontAskOnHide"), FALSE);
}

void fsAppSettings::DownloadDialog_DontAskOnHide(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("View"), _T ("DldDlg_DontAskOnHide"), b);
}

int fsAppSettings::NumberOfDlCreatesByUser()
{
	return m_stgs.GetProfileInt (_T ("General"), _T ("NumberOfDlCBU"), 0);
}

void fsAppSettings::NumberOfDlCreatesByUser(int i)
{
	m_stgs.WriteProfileInt (_T ("General"), _T ("NumberOfDlCBU"), i);
}

void fsAppSettings::OnDlHasBeenCreatedByUser()
{
	NumberOfDlCreatesByUser (NumberOfDlCreatesByUser () + 1);
}

//UINT fsAppSettings::ConfTimeout_Hangup()
//{
//	return m_stgs.GetProfileInt ("Scheduler", "Hangup", 30);
//}
//
//void fsAppSettings::ConfTimeout_Hangup(UINT u)
//{
//	m_stgs.WriteProfileInt ("Scheduler", "Hangup", u);
//}

UINT fsAppSettings::ConfTimeout_Exit()
{
	return m_stgs.GetProfileInt ("Scheduler", "Exit", 30);
}

void fsAppSettings::ConfTimeout_Exit(UINT u)
{
	m_stgs.WriteProfileInt ("Scheduler", "Exit", u);
}

UINT fsAppSettings::ConfTimeout_Shutdown()
{
	return m_stgs.GetProfileInt ("Scheduler", "Shutdown", 30);
}

void fsAppSettings::ConfTimeout_Shutdown(UINT u)
{
	m_stgs.WriteProfileInt ("Scheduler", "Shutdown", u);
}

UINT fsAppSettings::ConfTimeout_LaunchDld()
{
	return m_stgs.GetProfileInt ("Scheduler", "LaunchDld", 30);
}

void fsAppSettings::ConfTimeout_LaunchDld(UINT u)
{
	m_stgs.WriteProfileInt ("Scheduler", "LaunchDld", u);
}

CString fsAppSettings::CreateBD_LastNumbers()
{
	return m_stgs.GetProfileString (_T ("Last_CBD"), _T ("Numbers"), "1-100");
}

void fsAppSettings::CreateBD_LastNumbers(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("Last_CBD"), _T ("Numbers"), psz);
}

BOOL fsAppSettings::WD_DisableAfterExec()
{
	return m_stgs.GetProfileInt (_T ("Last"), _T ("WD_DisableAfterExec"), TRUE);
}

void fsAppSettings::WD_DisableAfterExec(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Last"), _T ("WD_DisableAfterExec"), b);
}

BOOL fsAppSettings::IsArchivePackInstalled()
{
	return m_stgs.GetProfileInt ("", "apinstalled", FALSE);
}

BOOL fsAppSettings::DontShowInstallAP()
{
	return m_stgs.GetProfileInt ("View", "DontShowInstallAP", FALSE);
}

void fsAppSettings::DontShowInstallAP(BOOL b)
{
	m_stgs.WriteProfileInt ("View", "DontShowInstallAP", b);
}

CString fsAppSettings::Hash_LastAlgorithm()
{
	return m_stgs.GetProfileString ("Hash", "LastAlgorithm", "MD5");
}

void fsAppSettings::Hash_LastAlgorithm(LPCSTR psz)
{
	m_stgs.WriteProfileString ("Hash", "LastAlgorithm", psz);
}

BOOL fsAppSettings::View_DontShowHashCheckResultIfOK()
{
	return m_stgs.GetProfileInt (_T ("View"), _T ("DontShowHashCheckResultIfOK"), FALSE);
}

void fsAppSettings::View_DontShowHashCheckResultIfOK(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("View"), _T ("DontShowHashCheckResultIfOK"), b);
}

CString fsAppSettings::CreateBD_SaveAs_Template()
{
	return m_stgs.GetProfileString (_T ("Last_CBD"), _T ("SaveAsTemplate"), "");
}

void fsAppSettings::CreateBD_SaveAs_Template(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("Last_CBD"), _T ("SaveAsTemplate"), psz);
}

BOOL fsAppSettings::App_2_0_SchedulerFixPerformed()
{
	return m_stgs.GetProfileInt ("Scheduler", "sfp_2.0", FALSE);
}

void fsAppSettings::App_2_0_SchedulerFixPerformed(BOOL b)
{
	m_stgs.WriteProfileInt ("Scheduler", "sfp_2.0", b);
}

DWORD fsAppSettings::FileWriteCacheSize()
{
	if (m_dwWriteCacheSize == DWORD (-1))
		m_dwWriteCacheSize = m_stgs.GetProfileInt (_T ("General"), _T ("FileWriteCacheSize"), 0);
	return m_dwWriteCacheSize;
}

void fsAppSettings::FileWriteCacheSize(DWORD dw)
{
	m_dwWriteCacheSize = dw;
	m_stgs.WriteProfileInt (_T ("General"), _T ("FileWriteCacheSize"), dw);
}

CString fsAppSettings::View_LastDldMoveToFolder()
{
	return m_stgs.GetProfileString (_T ("View"), _T ("LastDldMoveToFolder"), "");
}

void fsAppSettings::View_LastDldMoveToFolder(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("View"), _T ("LastDldMoveToFolder"), psz);
}

DWORD fsAppSettings::DNPFlags()
{
	return m_stgs.GetProfileInt ("Network", "DNPFlags", 0);
}

void fsAppSettings::DNPFlags(DWORD dw)
{
	m_stgs.WriteProfileInt ("Network", "DNPFlags", dw);
}

WORD fsAppSettings::LowSpeed_Duration()
{
	return (WORD)m_stgs.GetProfileInt ("Network", "LowSpeed_Duration", 3);
}

void fsAppSettings::LowSpeed_Duration(WORD w)
{
	m_stgs.WriteProfileInt ("Network", "LowSpeed_Duration", w);
}

WORD fsAppSettings::LowSpeed_Factor()
{
	return (WORD)m_stgs.GetProfileInt ("Network", "LowSpeed_Factor", 3);
}

void fsAppSettings::LowSpeed_Factor(WORD w)
{
	m_stgs.WriteProfileInt ("Network", "LowSpeed_Factor", w);
}

void fsAppSettings::Scheduler_LastTask_save(fsSchedule *task)
{
	m_stgs.WriteProfileBinary ("Scheduler", "LastTask", (LPBYTE)task, sizeof (*task));

	switch (task->wts.enType)
	{
	case WTS_PROGRAM:
		Scheduler_LastTask_ProgName (task->wts.prog.pszName);
		Scheduler_LastTask_ProgArgs (task->wts.prog.pszArgs);
	break;
	}
}

void fsAppSettings::Scheduler_LastTask_read(fsSchedule *task)
{
	LPBYTE pb = NULL;
	UINT uSize = 0;

	if (FALSE == m_stgs.GetProfileBinary ("Scheduler", "LastTask", &pb, &uSize) ||
			uSize != sizeof (*task))
	{
		task->wts.enType = WTS_PROGRAM;

		CString strProg = Scheduler_LastTask_ProgName (),
				strArgs = Scheduler_LastTask_ProgArgs ();
		fsnew (task->wts.prog.pszName, char, strProg.GetLength () + 1);
		fsnew (task->wts.prog.pszArgs, char, strArgs.GetLength () + 1);
		lstrcpy (task->wts.prog.pszName, strProg);
		lstrcpy (task->wts.prog.pszArgs, strArgs);

		task->hts.enType = HTS_ONCE;
		task->hts.last.dwHighDateTime = task->hts.last.dwLowDateTime = UINT_MAX;
		task->dwFlags = SCHEDULE_ENABLED;

		SYSTEMTIME time;
		GetLocalTime(&time);

		if (++time.wHour > 23)
			time.wHour = 0;

		time.wMinute = time.wSecond = 0;

		SystemTimeToFileTime (&time, &task->hts.next);

		task->uWaitForConfirmation = 0;
	}
	else
	{
		CopyMemory (task, pb, sizeof (*task));

		task->wts.enType = WTS_PROGRAM;
		task->hts.last.dwHighDateTime = task->hts.last.dwLowDateTime = UINT_MAX;
		task->dwFlags = SCHEDULE_ENABLED;
		SYSTEMTIME time;
		GetLocalTime(&time);
		if (++time.wHour > 23)
			time.wHour = 0;
		time.wMinute = time.wSecond = 0;
		SystemTimeToFileTime (&time, &task->hts.next);
		task->uWaitForConfirmation = 0;

		switch (task->wts.enType)
		{
		case WTS_PROGRAM:
		{
			CString strProg = Scheduler_LastTask_ProgName (),
				strArgs = Scheduler_LastTask_ProgArgs ();
			fsnew (task->wts.prog.pszName, char, strProg.GetLength () + 1);
			fsnew (task->wts.prog.pszArgs, char, strArgs.GetLength () + 1);
			lstrcpy (task->wts.prog.pszName, strProg);
			lstrcpy (task->wts.prog.pszArgs, strArgs);
		}
		break;

		case WTS_STARTDOWNLOAD:
		case WTS_STOPDOWNLOAD:
			task->wts.dlds.pvIDs = NULL;
			task->wts.dlds.dwFlags = 0;
		break;
		}
	}

	if (pb)
		delete [] pb;
}

CString fsAppSettings::Scheduler_LastTask_ProgName()
{
	return m_stgs.GetProfileString (_T ("Scheduler"), _T ("LastTask_ProgName"), "");
}

void fsAppSettings::Scheduler_LastTask_ProgName(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("Scheduler"), _T ("LastTask_ProgName"), psz);
}

CString fsAppSettings::Scheduler_LastTask_ProgArgs()
{
	return m_stgs.GetProfileString (_T ("Scheduler"), _T ("LastTask_ProgArgs"), "");
}

void fsAppSettings::Scheduler_LastTask_ProgArgs(LPCSTR psz)
{
	m_stgs.WriteProfileString (_T ("Scheduler"), _T ("LastTask_ProgArgs"), psz);
}

vmsAppSettingsStore* fsAppSettings::get_SettingsStore()
{
	return &m_stgs;
}

//BOOL fsAppSettings::View_DropBoxIntro()
//{
//	return m_stgs.GetProfileInt ("View", "DropBoxIntro", TRUE);
//}
//
//void fsAppSettings::View_DropBoxIntro(BOOL b)
//{
//	m_stgs.WriteProfileInt ("View", "DropBoxIntro", b);
//}

BOOL fsAppSettings::Notif_DisableForBatchDownloads()
{
	return m_stgs.GetProfileInt (_T ("Notifications"), _T ("DisableForBatchDownloads"), FALSE);
}

void fsAppSettings::Notif_DisableForBatchDownloads(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Notifications"), _T ("DisableForBatchDownloads"), b);
}

BOOL fsAppSettings::Download_CheckIntegrityWhenDone()
{
	return m_stgs.GetProfileInt (_T ("Integrity"),"CheckWhenDone", TRUE);
}

void fsAppSettings::Download_CheckIntegrityWhenDone(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Integrity"),"CheckWhenDone", b);
}

int fsAppSettings::Download_IntegrityCheckFailedReaction()
{
	return m_stgs.GetProfileInt (_T ("Integrity"),"ICFR", 0);
}

void fsAppSettings::Download_IntegrityCheckFailedReaction(int i)
{
	m_stgs.WriteProfileInt (_T ("Integrity"),"ICFR", i);
}

BOOL fsAppSettings::View_SetOutputFolderAsDefForAllGrpsChecked()
{
	return m_stgs.GetProfileInt (_T ("View"), _T ("SetOutputFolderAsDefForAllGrpsChecked"), TRUE);
}

void fsAppSettings::View_SetOutputFolderAsDefForAllGrpsChecked(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("View"), _T ("SetOutputFolderAsDefForAllGrpsChecked"), b);
}

int fsAppSettings::View_DownloadsGroups_SelectedFilterId()
{
	return m_stgs.GetProfileInt (_T ("View"), _T ("DownloadsGroups_SelectedFilterId"), -2);
}

void fsAppSettings::View_DownloadsGroups_SelectedFilterId(int i)
{
	m_stgs.WriteProfileInt (_T ("View"), _T ("DownloadsGroups_SelectedFilterId"), i);
}

BOOL fsAppSettings::View_AskRemoveFromAutostartAtAppExit()
{
	return m_stgs.GetProfileInt (_T ("View"), _T ("AskRemoveFromAutostartAtAppExit"), TRUE);
}

void fsAppSettings::View_AskRemoveFromAutostartAtAppExit(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("View"), _T ("AskRemoveFromAutostartAtAppExit"), b);
}

vmsNewGroupSelectWay fsAppSettings::NewGrp_SelectWay()
{
	return (vmsNewGroupSelectWay) m_stgs.GetProfileInt (
		_T ("NewDownload"), _T ("GroupSW"), NGSW_CHOOSE_BY_EXT);
}

void fsAppSettings::NewGrp_SelectWay(vmsNewGroupSelectWay en)
{
	m_stgs.WriteProfileInt (_T ("NewDownload"), _T ("GroupSW"),
		en);
}

//void fsAppSettings::WriteTranslatedStringToRegistry(LPCSTR pszStringId, LPCSTR pszString)
//{
//	AfxGetApp ()->WriteProfileString ("View_Loc", pszStringId, pszString);
//}

BOOL fsAppSettings::View_NOMShown()
{
	return m_stgs.GetProfileInt ("View", "NOMShown", FALSE);
}

void fsAppSettings::View_NOMShown(BOOL b)
{
	m_stgs.WriteProfileInt ("View", "NOMShown", b);
}

BOOL fsAppSettings::PreventStandbyWhileDownloading()
{
	if (m_bPreventStandbyWhileDownloading == BOOL (-1))
		m_bPreventStandbyWhileDownloading = m_stgs.GetProfileInt ("General", "PreventStandbyWhileDownloading", TRUE);
	return m_bPreventStandbyWhileDownloading;
}

void fsAppSettings::PreventStandbyWhileDownloading(BOOL b)
{
	m_bPreventStandbyWhileDownloading = b;
	m_stgs.WriteProfileInt ("General", "PreventStandbyWhileDownloading", b);
}

void fsAppSettings::View_DontShowPauseAlldldsEnabled(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("View"), _T ("DontShowPauseAlldldsEnabled"), b);
}

BOOL fsAppSettings::View_DontShowPauseAlldldsEnabled()
{
	return m_stgs.GetProfileInt (_T ("View"), _T ("DontShowPauseAlldldsEnabled"), FALSE);
}

BOOL fsAppSettings::CheckIfDownloadWithSameUrlExists()
{
	return m_stgs.GetProfileInt (_T ("General"), _T ("CheckIfDownloadWithSameUrlExists"), TRUE);
}

void fsAppSettings::CheckIfDownloadWithSameUrlExists(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("General"), _T ("CheckIfDownloadWithSameUrlExists"), b);
}

int fsAppSettings::RecentDownloadsHistorySize()
{
	return m_stgs.GetProfileInt (_T ("General"), _T ("RecentDownloadsHistorySize"), 10);
}

void fsAppSettings::RecentDownloadsHistorySize(int i)
{
	m_stgs.WriteProfileInt (_T ("General"), _T ("RecentDownloadsHistorySize"), i);
}

DWORD fsAppSettings::DldsMgrPDTimeLimit()
{
	return m_stgs.GetProfileInt (_T ("Network"), _T ("DldsMgrPDTimeLimit"), 0);
}

void fsAppSettings::DldsMgrPDTimeLimit(DWORD dw)
{
	m_stgs.WriteProfileInt (_T ("Network"), _T ("DldsMgrPDTimeLimit"), dw);
}

void fsAppSettings::ApplySettingsToMutexes()
{
	if (IS_PORTABLE_MODE == FALSE)
		return;

	static HANDLE _hmxDisableBrMenu = NULL;
	//if (Monitor_IEMenu_Enable () == FALSE)
	//{
		if (_hmxDisableBrMenu == NULL)
			_hmxDisableBrMenu = CreateMutex (NULL, FALSE, "mx::fdm: brmenu_disable");
	//}
	//else if (_hmxDisableBrMenu)
	//{
	//	CloseHandle (_hmxDisableBrMenu);
	//	_hmxDisableBrMenu = NULL;
	//}

	static HANDLE _hmxDisableDlLink = NULL;
	//if (Monitor_IEMenu_DLThis () == FALSE)
	//{
		if (_hmxDisableDlLink == NULL)
			_hmxDisableDlLink = CreateMutex(NULL, FALSE, "mx::fdm: dllink_disable");
	//}
	//else if (_hmxDisableDlLink)
	//{
	//	CloseHandle (_hmxDisableDlLink);
	//	_hmxDisableDlLink = NULL;
	//}

	static HANDLE _hmxDisableDlAll = NULL;
	//if (Monitor_IEMenu_DLAll () == FALSE)
	//{
		if (_hmxDisableDlAll == NULL)
			_hmxDisableDlAll = CreateMutex (NULL, FALSE, "mx::fdm: dlall_disable");
	//}
	//else if (_hmxDisableDlAll)
	//{
	//	CloseHandle (_hmxDisableDlAll);
	//	_hmxDisableDlAll = NULL;
	//}

	static HANDLE _hmxDisableDlSelected = NULL;
	//if (Monitor_IEMenu_DLSelected () == FALSE)
	//{
		if (_hmxDisableDlSelected == NULL)
			_hmxDisableDlSelected = CreateMutex (NULL, FALSE, "mx::fdm: dlselected_disable");
	//}
	//else if (_hmxDisableDlSelected)
	//{
	//	CloseHandle (_hmxDisableDlSelected);
	//	_hmxDisableDlSelected = NULL;
	//}
}
//
//BOOL fsAppSettings::CheckIfDownloadIsMirror()
//{
//	return m_stgs.GetProfileInt (_T ("General"), _T ("CheckIfDownloadIsMirror"), FALSE);
//}
//
//void fsAppSettings::CheckIfDownloadIsMirror(BOOL b)
//{
//	m_stgs.WriteProfileInt (_T ("General"), _T ("CheckIfDownloadIsMirror"), b);
//}

BOOL fsAppSettings::Notif_UseOnDoneWnds()
{
	return m_stgs.GetProfileInt (_T ("Notifications"), _T ("UseOnDoneWnds"), TRUE);
}

void fsAppSettings::Notif_UseOnDoneWnds(BOOL b)
{
	m_stgs.WriteProfileInt (_T ("Notifications"), _T ("UseOnDoneWnds"), b);
}

int fsAppSettings::Notif_OnDoneWnds_Timeout()
{
	return m_stgs.GetProfileInt (_T ("Notifications"), _T ("OnDoneWnds_Timeout"), 0);
}

void fsAppSettings::Notif_OnDoneWnds_Timeout(int i)
{
	m_stgs.WriteProfileInt (_T ("Notifications"), _T ("OnDoneWnds_Timeout"), i);
}

UINT64 fsAppSettings::ConnectionBandwidth(bool bForDownload)
{
	return m_stgs.GetProfileUint64 (_T ("Network"),
		bForDownload ? _T ("ConnectionDownloadBandwidth") : _T ("ConnectionUploadBandwidth"), UINT64_MAX);
}

void fsAppSettings::ConnectionBandwidth(bool bForDownload, UINT64 uVal)
{
	m_stgs.WriteProfileUint64 (_T ("Network"),
		bForDownload ? _T ("ConnectionDownloadBandwidth") : _T ("ConnectionUploadBandwidth"), uVal);
}

void fsAppSettings::GetConnectionBandwidthValues (bool bForDownload, std::vector <UINT64> &v)
{
	v.clear ();
	LPBYTE pb = NULL; UINT uSize = 0;
	if (!m_stgs.GetProfileBinary (_T ("Network"),
			bForDownload ? _T ("ConnectionDownloadBandwidthValues") : _T ("ConnectionUploadBandwidthValues"), &pb, &uSize))
		return;
	UINT64 *pu = (UINT64*)pb;
	while (uSize >= sizeof (UINT64))
	{
		v.push_back (*pu++);
		uSize -= sizeof (UINT64);
	}
	delete [] pb;
}

void fsAppSettings::SetConnectionBandwidthValues (bool bForDownload, const std::vector <UINT64> &v)
{
	m_stgs.WriteProfileBinary (_T ("Network"),
		bForDownload ? _T ("ConnectionDownloadBandwidthValues") : _T ("ConnectionUploadBandwidthValues"), (LPBYTE)&v[0], v.size () * sizeof (UINT64));
}

BOOL fsAppSettings::SpecifyNetworkSpeedValueInBits(void)
{
	return m_stgs.GetProfileInt (_T ("View"), _T ("SpecifyNetworkSpeedValueInBits"), FALSE);
}

void fsAppSettings::SpecifyNetworkSpeedValueInBits(bool b)
{
	m_stgs.WriteProfileInt (_T ("View"), _T ("SpecifyNetworkSpeedValueInBits"), b);
}

//BOOL fsAppSettings::ActivateWebinterface()
//{
//	return m_stgs.GetProfileInt (_T ("View"), _T ("ShowFIW"), TRUE);
//}
//
//void fsAppSettings::ActivateWebinterface(BOOL b)
//{
//	m_stgs.WriteProfileInt (_T ("View"), _T ("ShowFIW"), b);
//}
