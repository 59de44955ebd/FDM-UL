/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "FdmApp.h"
#include "vmsDownloadMgrEx.h"
#include "vmsLogger.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

vmsDownloadMgrEx::vmsDownloadMgrEx()
{
	m_pMgr = NULL;
}

vmsDownloadMgrEx::~vmsDownloadMgrEx()
{
	DetachDownloadMgr ();
}

void vmsDownloadMgrEx::DetachDownloadMgr ()
{
	vmsPersistObject *pObj = NULL;
	if (m_pMgr)
		pObj = m_pMgr;
	//else if (m_spBtMgr)
	//	pObj = m_spBtMgr;
	//else if (m_pTpMgr)
	//	pObj = m_pTpMgr;
	getPersistObjectChildren ()->removePersistObject (pObj);
	SAFE_DELETE (m_pMgr);
	//m_spBtMgr = NULL;
	//SAFE_DELETE (m_pTpMgr);
}

void vmsDownloadMgrEx::Attach(fsDownloadMgr *pMgr)
{
	DetachDownloadMgr ();
	m_pMgr = pMgr;
	getPersistObjectChildren ()->addPersistObject (m_pMgr);
}

//void vmsDownloadMgrEx::Attach(vmsBtDownloadManager *pBtMgr)
//{
//	DetachDownloadMgr ();
//	m_spBtMgr = pBtMgr;
//	getPersistObjectChildren ()->addPersistObject (m_spBtMgr);
//}
//
//void vmsDownloadMgrEx::Attach(vmsTpDownloadMgr *pTpMgr)
//{
//	DetachDownloadMgr ();
//	m_pTpMgr = pTpMgr;
//	getPersistObjectChildren ()->addPersistObject (m_pTpMgr);
//}

fsDownloadMgr* vmsDownloadMgrEx::GetDownloadMgr()
{
	return m_pMgr;
}

//vmsBtDownloadManager* vmsDownloadMgrEx::GetBtDownloadMgr()
//{
//	return m_spBtMgr;
//}
//
//vmsTpDownloadMgr* vmsDownloadMgrEx::GetTpDownloadMgr()
//{
//	return m_pTpMgr;
//}

fsString vmsDownloadMgrEx::get_OutputFilePathName()
{
	return m_pMgr->GetDP ()->pszFileName;
}

float vmsDownloadMgrEx::GetPercentDone()
{
	return m_pMgr->GetDownloader ()->GetPercentDone ();
}

BOOL vmsDownloadMgrEx::IsLaunchWhenDone()
{
	return m_pMgr->GetDP ()->dwFlags & DPF_STARTWHENDONE;
}

fsResumeSupportType vmsDownloadMgrEx::IsResumeSupported()
{
	return m_pMgr->GetDownloader ()->IsResumeSupported ();
}

BOOL vmsDownloadMgrEx::IsDone()
{
	return m_pMgr->IsDone ();
}

BOOL vmsDownloadMgrEx::IsRunning()
{
	return m_pMgr->IsRunning ();
}

BOOL vmsDownloadMgrEx::IsFileInitializedOnDisk()
{
	if (m_pMgr)
		return m_pMgr->IsFileInit ();
	else
		return TRUE;
}

void vmsDownloadMgrEx::set_LaunchWhenDone(BOOL b)
{
	if (b)
		m_pMgr->GetDP ()->dwFlags |= DPF_STARTWHENDONE;
	else
		m_pMgr->GetDP ()->dwFlags &= ~DPF_STARTWHENDONE;

	m_pMgr->setDirty();
}

fsString vmsDownloadMgrEx::get_URL(BOOL bInclAuth)
{
	return m_pMgr->GetDownloader ()->get_URL (bInclAuth);
}

int vmsDownloadMgrEx::GetNumberOfSections()
{
	return m_pMgr->GetDownloader ()->GetNumberOfSections ();
}

UINT64 vmsDownloadMgrEx::GetLDFileSize()
{
	return m_pMgr->GetDownloader ()->GetLDFileSize ();
}

UINT64 vmsDownloadMgrEx::GetDownloadedBytesCount()
{
	return m_pMgr->GetDownloader ()->GetDownloadedBytesCount ();
}

BOOL vmsDownloadMgrEx::IsDownloading()
{
	return m_pMgr->GetDownloader ()->IsDownloading ();
}

UINT64 vmsDownloadMgrEx::GetSSFileSize()
{
	return m_pMgr->GetDownloader ()->GetSSFileSize ();
}

void vmsDownloadMgrEx::GetSectionInfo(int nIndex, vmsSectionInfo *sect, BOOL bNoCacheAccounting)
{
	fsSection s;
	m_pMgr->GetDownloader ()->GetSectionInfo (nIndex, &s, bNoCacheAccounting);
	sect->uDStart = s.uDStart;
	sect->uDCurrent = s.uDCurrent;
	sect->uDEnd = s.uDEnd;
}

int vmsDownloadMgrEx::GetDownloadingSectionCount()
{
	return m_pMgr->GetDownloader ()->GetDownloadingSectionCount ();
}

void vmsDownloadMgrEx::CreateOneMoreSection()
{
	m_pMgr->CreateOneMoreSection ();
}

void vmsDownloadMgrEx::StopSection()
{
	m_pMgr->StopSection ();
}

UINT64 vmsDownloadMgrEx::GetBytesLeft()
{
	return m_pMgr->GetDownloader ()->GetBytesLeft ();
}

UINT vmsDownloadMgrEx::GetSpeed()
{
	return m_pMgr->GetDownloader ()->GetSpeed ();
}

BOOL vmsDownloadMgrEx::MoveToFolder(LPCSTR pszPath)
{
	return m_pMgr->MoveToFolder (pszPath);
}

BOOL vmsDownloadMgrEx::IsStoppedByUser()
{
	return m_pMgr->GetDownloader ()->IsStoppedByUser ();
}

BOOL vmsDownloadMgrEx::IsCantStart()
{
	return m_pMgr->IsCantStart ();
}

fsInternetResult vmsDownloadMgrEx::RestartDownloading()
{
	return m_pMgr->RestartDownloading ();
}

BOOL vmsDownloadMgrEx::IsDescriptionFileShouldBeGenerated()
{
	return m_pMgr->GetDP ()->dwFlags & DPF_GENERATEDESCFILE;
}

fsInternetResult vmsDownloadMgrEx::StartDownloading()
{
	return m_pMgr->StartDownloading ();
}

void vmsDownloadMgrEx::StopDownloading()
{
	m_pMgr->StopDownloading ();
}

void vmsDownloadMgrEx::LimitTraffic(UINT uLimit)
{
	m_pMgr->GetDownloader ()->LimitTraffic (uLimit);
}

UINT vmsDownloadMgrEx::GetTrafficLimit()
{
	return m_pMgr->GetDownloader ()->GetTrafficLimit ();
}

void vmsDownloadMgrEx::UseDetailedLog(BOOL b)
{
	m_pMgr->GetDownloader ()->UseDetailedLog (b);
}

BOOL vmsDownloadMgrEx::DeleteFile()
{
	return m_pMgr->DeleteFile ();
}

BOOL vmsDownloadMgrEx::IsDontConfirmLaunchWhenDone()
{
	return m_pMgr->GetDP ()->dwFlags & DPF_STARTWHENDONE_NOCONF;
}

fsInternetResult vmsDownloadMgrEx::SetToRestartState()
{
	return m_pMgr->SetToRestartState ();
}

int vmsDownloadMgrEx::GetConnectionCount()
{
	return m_pMgr->GetDownloader ()->GetRunningSectionCount ();
}

BOOL vmsDownloadMgrEx::LoadState(LPBYTE lpBuffer, LPDWORD lpdwSize, WORD wVer)
{
#define CHECK_BOUNDS(need) if (need < 0 || need > int(*lpdwSize) - (pB - LPBYTE (lpBuffer))) return FALSE;
	LPBYTE pB = LPBYTE (lpBuffer);

	BYTE bBitTorrent = FALSE, bTransportProtocol = FALSE;
	DWORD dwMgrStateSize = *lpdwSize;
	DWORD dwConsumed = 0;

	BOOL bOk;

	if (wVer > 9)
	{
		CHECK_BOUNDS (sizeof (BYTE));
		const int nMgr = *lpBuffer++;
		bBitTorrent = (nMgr == 1);
		if (wVer > 13) bTransportProtocol = (nMgr == 2);
		dwConsumed++;
		dwMgrStateSize--;
	}

	//if (bTransportProtocol)
	//{
	//	Attach (new vmsTpDownloadMgr);
	//	bOk = m_pTpMgr->LoadState (lpBuffer, &dwMgrStateSize, wVer);
	//}
	//else if (bBitTorrent)
	//{
	//	vmsBtDownloadManagerPtr spMgr; spMgr.CreateInstance ();
	//	Attach (spMgr);
	//	bOk = m_spBtMgr->LoadState (lpBuffer, &dwMgrStateSize, wVer);
	//}
	//else
	//{
		Attach (new fsDownloadMgr);
		bOk = m_pMgr->LoadState (lpBuffer, &dwMgrStateSize, wVer);
	//}

	if (bOk == FALSE)
		return FALSE;

	dwConsumed += dwMgrStateSize;
	*lpdwSize = dwConsumed;

	return TRUE;
}

//BOOL vmsDownloadMgrEx::IsBittorrent()
//{
//	return m_spBtMgr != NULL;
//}
//
//BOOL vmsDownloadMgrEx::IsTp()
//{
//	return m_pTpMgr != NULL;
//}

void vmsDownloadMgrEx::GetSplittedSectionsList(std::vector <vmsSectionInfo> &v)
{
	try
	{
		std::vector <vmsSectionInfo> vBtSects;
		//if (m_spBtMgr)
		//	m_spBtMgr->GetSectionsInfo (vBtSects);

		v.clear ();
		size_t num = GetNumberOfSections ();
		vmsSectionInfo *sectLast = NULL;

		for (size_t i = 0; i < num; i++)
		{
			vmsSectionInfo sect;
	/*		if (m_spBtMgr)
				sect = vBtSects [i];
			else*/
				GetSectionInfo (i, &sect);
			if (sectLast != NULL &&
				(sectLast->uDCurrent == sect.uDStart || sectLast->uDCurrent+1 == sect.uDStart))
			{
				sectLast->uDEnd = sect.uDEnd;
				sectLast->uDCurrent = sect.uDCurrent;
			}
			else
			{
				v.push_back (sect);

				std::vector <vmsSectionInfo>::iterator itLastSect = v.end () - 1;
				sectLast = &(*itLastSect);

			}
		}
	}
	catch (const std::exception& ex)
	{
		ASSERT (FALSE);
		vmsLogger::WriteLog("vmsDownloadMgrEx::GetSplittedSectionsList " + tstring(ex.what()));
		v.clear ();
	}
	catch (...)
	{
		ASSERT (FALSE);
		vmsLogger::WriteLog("vmsDownloadMgrEx::GetSplittedSectionsList unknown exception");
		v.clear ();
	}
}

BOOL vmsDownloadMgrEx::IsReservingDiskSpace()
{
	return (m_pMgr->get_State () & DS_RESERVINGSPACE) != 0;
}

int vmsDownloadMgrEx::get_ReservingDiskSpaceProgress()
{
	return m_pMgr->get_ReservingDiskSpaceProgress ();
}

void vmsDownloadMgrEx::Do_OpenFolder()
{
	if (m_pMgr && m_pMgr->IsFileInit () == FALSE)
	{
		ShellExecute (NULL, "explore", get_OutputFilePathName (), NULL, NULL, SW_SHOW);
	}
	else
	{
		CString strFileName = get_OutputFilePathName ();

		//if (m_spBtMgr && m_spBtMgr->get_FileCount () > 1)
		//	strFileName += m_spBtMgr->get_RootFolderName ();

		if (GetFileAttributes (strFileName) == DWORD (-1))
		{
			char szPath [MY_MAX_PATH];

			fsGetPath (strFileName, szPath);
			ShellExecute (NULL, "explore", szPath, NULL, NULL, SW_SHOW);
		}
		else
		{
			CString strCmd;
			strCmd.Format ("/select,\"%s\"", strFileName.GetString());
				ShellExecute (NULL, "open", "explorer.exe", strCmd.GetString(), NULL, SW_SHOW);
		}
	}
}

UINT64 vmsDownloadMgrEx::getSpeed(bool bOfDownload)
{
	vmsDownloaderWithNetworkUsageAdjustment *pObj = getDownloaderWithNetworkUsageAdjustmentObject ();
	return pObj ? pObj->getSpeed (bOfDownload) : 0;
}

void vmsDownloadMgrEx::setSpeedLimit(bool bOfDownload, UINT64 uLimit)
{
	vmsDownloaderWithNetworkUsageAdjustment *pObj = getDownloaderWithNetworkUsageAdjustmentObject ();
	if (pObj)
		pObj->setSpeedLimit (bOfDownload, uLimit);
}

vmsDownloaderWithNetworkUsageAdjustment* vmsDownloadMgrEx::getDownloaderWithNetworkUsageAdjustmentObject(void)
{
	if (m_pMgr)
		return m_pMgr;
	//if (m_spBtMgr)
	//	return m_spBtMgr;
	return NULL;
}

UINT64 vmsDownloadMgrEx::getSpeedLimit(bool bOfDownload)
{
	vmsDownloaderWithNetworkUsageAdjustment *pObj = getDownloaderWithNetworkUsageAdjustmentObject ();
	return pObj ? pObj->getSpeedLimit (bOfDownload) : UINT64_MAX;
}

bool vmsDownloadMgrEx::isResumeSupported(bool bOfDownload)
{
	vmsDownloaderWithNetworkUsageAdjustment *pObj = getDownloaderWithNetworkUsageAdjustmentObject ();
	return pObj ? pObj->isResumeSupported (bOfDownload) : true;
}

bool vmsDownloadMgrEx::isIgnoreAllSpeedLimits(bool bOfDownload)
{
	vmsDownloaderWithNetworkUsageAdjustment *pObj = getDownloaderWithNetworkUsageAdjustmentObject ();
	return pObj ? pObj->isIgnoreAllSpeedLimits (bOfDownload) : false;
}

UINT64 vmsDownloadMgrEx::getInternalSpeedLimit(bool bOfDownload)
{
	vmsDownloaderWithNetworkUsageAdjustment *pObj = getDownloaderWithNetworkUsageAdjustmentObject ();
	return pObj ? pObj->getInternalSpeedLimit (bOfDownload) : _UI64_MAX;
}

bool vmsDownloadMgrEx::isRequiresTraffic(bool bForDownload)
{
	vmsDownloaderWithNetworkUsageAdjustment *pObj = getDownloaderWithNetworkUsageAdjustmentObject ();
	return pObj ? pObj->isRequiresTraffic (bForDownload) : false;
}

bool vmsDownloadMgrEx::isSpeedCanBeLimitedBySomeInternalReasons (bool bForDownload)
{
	vmsDownloaderWithNetworkUsageAdjustment *pObj = getDownloaderWithNetworkUsageAdjustmentObject ();
	return pObj ? pObj->isSpeedCanBeLimitedBySomeInternalReasons (bForDownload) : false;
}

bool vmsDownloadMgrEx::isInternetTraffic (bool bForDownload)
{
	vmsDownloaderWithNetworkUsageAdjustment *pObj = getDownloaderWithNetworkUsageAdjustmentObject ();
	return pObj ? pObj->isInternetTraffic (bForDownload) : true;
}
