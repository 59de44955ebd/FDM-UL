/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#if !defined(AFX_FSAPPSETTINGS_H__33EC2FD8_44AF_484F_AC12_A498B479BD50__INCLUDED_)
#define AFX_FSAPPSETTINGS_H__33EC2FD8_44AF_484F_AC12_A498B479BD50__INCLUDED_

#include "vmsAppSettingsStore.h"
#include "DownloadProperties.h"
#include "fsDownloadsMgr.h"

//#include "fsWebPageDownloader.h"
#include "vmsTrafficUsageModeMgr.h"

#include "DownloadsWnd.h"
#if _MSC_VER > 1000
#pragma once
#endif

//enum vmsSpreadHelpRemind
//{
//	SHR_NEXTSTART,
//	SHR_IN3DAYS,
//	SHR_NEVER,
//	SHR_WAIT1STTIME,
//};

//enum vmsAutoUpdateType
//{
//	AUT_DLANDINST,
//	AUT_NOTIFYONLY,
//	AUT_TURNOFF,
//};


enum vmsNewGroupSelectWay
{
	NGSW_CHOOSE_BY_EXT,
	NGSW_USE_ALWAYS_SAME_GROUP,
	NGSW_USE_ALWAYS_SAME_GROUP_WITH_OUTFOLDER_AUTO_UPDATE,
};

class fsAppSettings
{

protected:
//	enum fsConnectionType
//	{
//		CT_MODEM_14_4,
//		CT_MODEM_28_8,
//		CT_MODEM_33_6,
//		CT_MODEM_56_ISDN,
//		CT_DUAL_ISDN,
//		CT_CABLE_DSL_256,
//		CT_CABLE_DSL_512,
//		CT_CABLE_DSL_768,
//		CT_CABLE_DSL_1M,
//		CT_CABLE_DSL_1_5M,
//		CT_CABLE_DSL_2M,
//		CT_LAN_10,
//		CT_UNKNOWN,
//	};
	struct fsTrafficUsageModeSettings
	{
		UINT uMaxConns;
		UINT uMaxConnsPS;
		UINT uMaxTasks;
		UINT uTrafficLimit;
		fsTrafficUsageModeSettings () {uMaxTasks = 3; uMaxConns = 3; uMaxConnsPS = 3; uTrafficLimit = UINT_MAX;}
	};
public:
	vmsAppSettingsStore* get_SettingsStore();

	void Notif_OnDoneWnds_Timeout (int i);
	int Notif_OnDoneWnds_Timeout();

	void Notif_UseOnDoneWnds (BOOL b);
	BOOL Notif_UseOnDoneWnds();

	void ApplySettingsToMutexes();
	void DldsMgrPDTimeLimit (DWORD dw);
	DWORD DldsMgrPDTimeLimit();

	void RecentDownloadsHistorySize (int i);
	int RecentDownloadsHistorySize();

	void CheckIfDownloadWithSameUrlExists (BOOL b);
	BOOL CheckIfDownloadWithSameUrlExists();

	BOOL View_DontShowPauseAlldldsEnabled();
	void View_DontShowPauseAlldldsEnabled (BOOL b);

	void PreventStandbyWhileDownloading (BOOL b);
	BOOL PreventStandbyWhileDownloading();

	void View_NOMShown (BOOL b);
	BOOL View_NOMShown();

//	void WriteTranslatedStringToRegistry (LPCSTR pszStringId, LPCSTR pszString);

	void NewGrp_SelectWay (vmsNewGroupSelectWay en);
	vmsNewGroupSelectWay NewGrp_SelectWay();

	void View_AskRemoveFromAutostartAtAppExit (BOOL b);
	BOOL View_AskRemoveFromAutostartAtAppExit();

	void View_DownloadsGroups_SelectedFilterId (int i);
	int View_DownloadsGroups_SelectedFilterId();
	void View_SetOutputFolderAsDefForAllGrpsChecked (BOOL b);
	BOOL View_SetOutputFolderAsDefForAllGrpsChecked();

	void Download_IntegrityCheckFailedReaction (int i);
	int Download_IntegrityCheckFailedReaction();
	void Download_CheckIntegrityWhenDone (BOOL b);
	BOOL Download_CheckIntegrityWhenDone();

	void Notif_DisableForBatchDownloads (BOOL b);
	BOOL Notif_DisableForBatchDownloads();

	void Scheduler_LastTask_ProgArgs (LPCSTR psz);
	CString Scheduler_LastTask_ProgArgs();
	void Scheduler_LastTask_ProgName (LPCSTR psz);
	CString Scheduler_LastTask_ProgName();
	void Scheduler_LastTask_read (fsSchedule* task);
	void Scheduler_LastTask_save (fsSchedule* task);

	void LowSpeed_Factor (WORD w);
	WORD LowSpeed_Factor();
	void LowSpeed_Duration (WORD w);
	WORD LowSpeed_Duration();
	void DNPFlags (DWORD dw);
	DWORD DNPFlags();

	void View_LastDldMoveToFolder (LPCSTR psz);
	CString View_LastDldMoveToFolder();

	void FileWriteCacheSize (DWORD dw);
	DWORD FileWriteCacheSize();

	void App_2_0_SchedulerFixPerformed (BOOL b);
	BOOL App_2_0_SchedulerFixPerformed();
	void CreateBD_SaveAs_Template (LPCSTR psz);
	CString CreateBD_SaveAs_Template();
	void View_DontShowHashCheckResultIfOK (BOOL b);
	BOOL View_DontShowHashCheckResultIfOK();
	void Hash_LastAlgorithm (LPCSTR psz);
	CString Hash_LastAlgorithm();
	void DontShowInstallAP (BOOL b);
	BOOL DontShowInstallAP();
	BOOL IsArchivePackInstalled();
	void WD_DisableAfterExec (BOOL b);
	BOOL WD_DisableAfterExec();

	void CreateBD_LastNumbers (LPCSTR psz);
	CString CreateBD_LastNumbers();

	void ConfTimeout_Exit (UINT u);
	UINT ConfTimeout_Exit();
	void ConfTimeout_Shutdown (UINT u);
	UINT ConfTimeout_Shutdown();
	void ConfTimeout_LaunchDld (UINT u);
	UINT ConfTimeout_LaunchDld();

	void OnDlHasBeenCreatedByUser();
	void NumberOfDlCreatesByUser (int i);
	int NumberOfDlCreatesByUser();

	void DownloadDialog_DontAskOnHide (BOOL b);
	BOOL DownloadDialog_DontAskOnHide();
	void DownloadDialog_Use (BOOL b);
	BOOL DownloadDialog_Use();
	void DownloadDialog_AutoClose (BOOL b);
	BOOL DownloadDialog_AutoClose();

	void Export_Hist_Append (BOOL b);
	BOOL Export_Hist_Append();
	void Export_Hist_CompletedOnly (BOOL b);
	BOOL Export_Hist_CompletedOnly();
	void Export_WhichHist (int i);
	int Export_WhichHist();
	void DontSaveLogs (BOOL b);
	BOOL DontSaveLogs();
	void WD_LastShutdownType_DontAsk (BOOL b);
	BOOL WD_LastShutdownType_DontAsk();
	void WD_LastShutdownType (int enType);
	int WD_LastShutdownType ();
	void CreateBD_LastAtoZ (DWORD dw);
	DWORD CreateBD_LastAtoZ ();

	void View_TUMChanged (BOOL b);
	BOOL View_TUMChanged();
	void View_GCVButton (BOOL b);
	BOOL View_GCVButton();

	void FilesToDelete_save (CStringList& v);
	BOOL FilesToDelete (CStringList& v);
	void NewDL_GenerateNameAutomatically (BOOL b);
	BOOL NewDL_GenerateNameAutomatically();

	void FloatingWndsHideInFSMode (BOOL b);
	BOOL FloatingWndsHideInFSMode();
	void SM_DontSavePwdsToDisk (BOOL b);
	BOOL SM_DontSavePwdsToDisk();
	void SM_PwdsManualAddition (BOOL b);
	BOOL SM_PwdsManualAddition();
	void SM_KeepPasswords (BOOL b);
	BOOL SM_KeepPasswords();

	void CheckRecycleBinSize (BOOL b);
	BOOL CheckRecycleBinSize();
	void RollBackSize (WORD w);
	WORD RollBackSize();

	void NewDL_AutoStart (BOOL b);
	BOOL NewDL_AutoStart();
	void DownloadFlags (DWORD dw);
	DWORD DownloadFlags();
	void MP_Volume (int i);
	int MP_Volume();
	void MP_Mute (BOOL b);
	BOOL MP_Mute();

	UINT64 Find_FileSizeTo();
	void Find_FileSizeTo (UINT64 u);
	void Find_FileSizeFrom (UINT64 u);
	UINT64 Find_FileSizeFrom();
	FILETIME Find_TimeTo();
	void Find_TimeTo (FILETIME &t);
	FILETIME Find_TimeFrom();
	void Find_TimeFrom (FILETIME &t);
	void Find_GroupId (UINT n);
	UINT Find_GroupId();
	void Find_Flags (DWORD dw);
	DWORD Find_Flags();
	CString Find_What();
	void Find_What (LPCSTR psz);

	void Deleted_BypassCompleted (BOOL b);
	BOOL Deleted_BypassCompleted();
	void Deleted_ConfirmDeletion (BOOL b);
	BOOL Deleted_ConfirmDeletion();
	void Deleted_MaxCount (UINT u);
	UINT Deleted_MaxCount();
	void Deleted_Bypass (BOOL b);
	BOOL Deleted_Bypass ();

	void View_DWWN (fsDLsWndWhatIsNow en);
	fsDLsWndWhatIsNow View_DWWN();
	void Export_Append (BOOL b);
	BOOL Export_Append();
	void Export_DontExpCompleted (BOOL b);
	BOOL Export_DontExpCompleted();
	void Export_WhichDlds (int i);
	int Export_WhichDlds();

	void Snd_Use (BOOL b);
	BOOL Snd_Use();
	void Snd_DownloadFailed (LPCSTR psz);
	CString Snd_DownloadFailed();

	void Snd_NoActiveDownloads (LPCSTR psz);
	CString Snd_NoActiveDownloads();
	void Snd_DownloadAdded (LPCSTR psz);
	CString Snd_DownloadAdded();
	void Snd_DownloadComplete (LPCSTR psz);
	CString Snd_DownloadComplete();

	UINT NewDL_GroupId ();
	void NewDL_GroupId (UINT n);
	CString NewDL_Group_old ();
	void NewDL_Group_old (LPCSTR psz);
	void View_FloatingInfoWindow (BOOL b);
	BOOL View_FloatingInfoWindow();

	void Notif_BalloonTimeout (DWORD dw);
	DWORD Notif_BalloonTimeout();
	void Notif_UseBalloon (BOOL b);
	BOOL Notif_UseBalloon();
	void Network_Br_SettingsSaved (BOOL b);
	BOOL Network_Br_SettingsSaved();
	void NewVerExists (BOOL b);
	BOOL NewVerExists();

	void View_SizesInBytes (BOOL b);
	BOOL View_SizesInBytes ();
	void Download_CreateExt (LPCSTR psz);
	CString Download_CreateExt();

	void DetLog (BOOL b);
	BOOL DetLog();
	void View_FloatingWindow(BOOL b);
	BOOL View_FloatingWindow();
	void DropBoxWndBlend (BYTE b);
	BYTE DropBoxWndBlend ();
	void DownloadsInfoWndBlend (BYTE b);
	BYTE DownloadsInfoWndBlend ();
	void TUMManage (fsTUMManage en);
	fsTUMManage TUMManage();
	void View_DldInfoCurTab (int i);
	int View_DldInfoCurTab ();
	void Last_Autostart (int i);
	int Last_Autostart();

	CString View_Language();
	void View_Language (LPCSTR pszLang);

	void View_SplitterRatio (LPCSTR pszName, float fRatio);
	float View_SplitterRatio (LPCSTR pszName);
	enum ReadWndPlacementAdjustment
	{
		RWPA_NONE,
		RWPA_FORCE_SWHIDE,
		RWPA_FORCE_SWHIDE_AND_KEEP_MINIMIZED_MAXIMIZED_STATE,
	};
	void View_ReadWndPlacement (CWnd* pWnd, LPCSTR pszName, ReadWndPlacementAdjustment enRWPA = RWPA_NONE);
	void View_SaveWndPlacement (CWnd* pWnd, LPCSTR pszName);
	void View_ReadWndSize(CWnd *pWnd, LPCSTR pszName);
	void View_SaveWndSize (CWnd* pWnd, LPCSTR pszName);
	void View_Statusbar (BOOL b);
	BOOL View_Statusbar ();
	void View_Toolbar (BOOL b);
	BOOL View_Toolbar();

	void View_SchedulerLog (BOOL b);
	BOOL View_SchedulerLog ();
	void View_DLInfo (BOOL b);
	BOOL View_DLInfo();
	void View_AllGroups (BOOL b);
	BOOL View_AllGroups();
	void View_SWBar (BOOL b);
	BOOL View_SWBar();

	void Prg_MinToTray (BOOL b);
	BOOL Prg_MinToTray();
	void Prg_CloseAsMinimize (BOOL b);
	BOOL Prg_CloseAsMinimize();
	void Prg_StartMinimized (BOOL b);
	BOOL Prg_StartMinimized();

	void CreateDld_IdOfLastGrpSelected (UINT n);
	UINT CreateDld_IdOfLastGrpSelected();
	void ActivePlugin (int i);
	int ActivePlugin();
	void NOW (int i);
	int NOW();
	void AutosaveInterval (UINT nVal);
	UINT AutosaveInterval ();
	BOOL AutoDelCompleted();
	void AutoDelCompleted (BOOL b);
	fsDeleteDownloadReaction DDR();
	void DDR (fsDeleteDownloadReaction en);
	void CurrentTUM (fsTUM i);
	fsTUM CurrentTUM();
	BOOL Get_TUM(vmsTrafficUsageModeRawSettings aTUM[3]);
	void Set_TUM (vmsTrafficUsageModeRawSettings aTUM [3]);
	void AdditionalExtension (LPCSTR pszExt);
	CString AdditionalExtension();
	void SizeChangeReaction (fsSizeChangeReaction val);
	fsSizeChangeReaction SizeChangeReaction();
	void AlreadyExistReaction (fsAlreadyExistReaction val);
	fsAlreadyExistReaction AlreadyExistReaction();
	void AccDeniedReaction (fsDownloadFileErrorProcessing val);
	fsDownloadFileErrorProcessing AccDeniedReaction();
	void NotFoundReaction (fsDownloadFileErrorProcessing val);
	fsDownloadFileErrorProcessing NotFoundReaction();

	void ASCIIExts (LPCSTR psz);
	CString ASCIIExts ();

	void UseCookie(BOOL b);
	BOOL UseCookie();

	// SOCKS5
	void UseSocksProxy (BOOL bUse);
	BOOL UseSocksProxy();
	void SocksProxy_Name (LPCSTR psz);
	CString SocksProxy_Name ();

	void FtpProxy_Password (LPCSTR psz);
	CString FtpProxy_Password ();
	void FtpProxy_UserName (LPCSTR psz);
	CString FtpProxy_UserName ();
	void FtpProxy_Name (LPCSTR psz);
	CString FtpProxy_Name ();

	void HttpsProxy_Password (LPCSTR psz);
	CString HttpsProxy_Password ();
	void HttpsProxy_UserName (LPCSTR psz);
	CString HttpsProxy_UserName ();
	void HttpsProxy_Name (LPCSTR psz);
	CString HttpsProxy_Name ();

	void HttpProxy_Password (LPCSTR psz);
	CString HttpProxy_Password ();
	void HttpProxy_UserName (LPCSTR psz);
	CString HttpProxy_UserName ();
	void HttpProxy_Name (LPCSTR psz);
	CString HttpProxy_Name ();

	void Timeout (UINT u);
	UINT Timeout();
	void ReserveDiskSpace (BOOL b);
	BOOL ReserveDiskSpace();
	void Agent (LPCSTR psz);
	CString Agent();
	void RestartSpeedLow (BOOL b);
	BOOL RestartSpeedLow();
	void IgnoreRestrictions (BOOL b);
	BOOL IgnoreRestrictions();
	void MaxAttempts (UINT u);
	UINT MaxAttempts ();
	void TrafficRestriction (UINT u);
	UINT TrafficRestriction();
	void MaxSections (UINT u);
	UINT MaxSections();
	void SectionMinSize (UINT u);
	UINT SectionMinSize();
	void RetriesTime (UINT u);
	UINT RetriesTime();
	void FtpTransferType (fsFtpTransferType enType);
	fsFtpTransferType FtpTransferType();
	void FtpFlags (DWORD dw);
	DWORD FtpFlags ();
	void UseHttp11 (BOOL b);
	BOOL UseHttp11();
	void Referer (LPCTSTR pszStr);
	CString Referer ();
	void UserPassword (LPCTSTR pszStr);
	CString UserPassword ();
	void UserName (LPCTSTR pszStr);
	CString UserName();

	void InternetAccessType (fsInternetAccessTypeEx enType);
	fsInternetAccessTypeEx InternetAccessType();

//	void ActivateWebinterface (BOOL b);
//	BOOL ActivateWebinterface();

	fsAppSettings();
	virtual ~fsAppSettings();

protected:
	vmsAppSettingsStore m_stgs;
	DWORD m_dwWriteCacheSize;
	DWORD m_dwNonUtf8NameFixed;
	BOOL m_bPreventStandbyWhileDownloading;
	BOOL m_bDontSaveLogs;
	BOOL LoadStringList(LPCSTR pszSubKey, LPCSTR pszValue, CStringList *v);
	void SaveStringList(LPCSTR pszSubKey, LPCSTR pszValue, CStringList &v);

public:
	UINT64 ConnectionBandwidth(bool bForDownload);
	void ConnectionBandwidth(bool bForDownload, UINT64 uVal);
	void GetConnectionBandwidthValues (bool bForDownload, std::vector <UINT64> &v);
	void SetConnectionBandwidthValues (bool bForDownload, const std::vector <UINT64> &v);
	BOOL SpecifyNetworkSpeedValueInBits(void);
	void SpecifyNetworkSpeedValueInBits(bool b);
};

#endif
