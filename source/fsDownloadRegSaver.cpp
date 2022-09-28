/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "FdmApp.h"
#include "fsDownloadRegSaver.h"
#include "DownloadsWnd.h"
#include "fsDownloadMgr.h"
#include "system.h"
#include "mfchelp.h"
#include "vmsLogger.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

fsDownloadRegSaver::fsDownloadRegSaver()
{
}

fsDownloadRegSaver::~fsDownloadRegSaver()
{
}

extern CFdmApp theApp;

fsDLLoadResult fsDownloadRegSaver::Load (vmsDownloadList& vDownloads, LPCSTR pszFileName, BOOL bDontLoadIfTooLarge, fsDLLoadFromType lt, BOOL bErrIfNotExists)
{
	LPBYTE pBuffer = NULL;
	HANDLE hFile = INVALID_HANDLE_VALUE;
	fsDLLoadFromType nlt = DLLFT_SAV;
	fsDLFileHdr hdr;
	vmsDownloadList tmp;

	fsString strFileName = theApp.m_strAppPath;
	strFileName += pszFileName;

	switch (lt)
	{
	case DLLFT_SAV:
		strFileName += ".sav";
		nlt = DLLFT_BAK;
		break;

	case DLLFT_BAK:
		strFileName += ".bak";
		nlt = DLLFT_SAV;
		break;
	}

	if (GetFileAttributes (strFileName) == UINT (-1))
	{
		if (nlt == DLLFT_SAV)
			return bErrIfNotExists == FALSE ? DLLR_SUCCEEDED : DLLR_FAILED;
		else
			return Load (vDownloads, pszFileName, bDontLoadIfTooLarge, nlt, bErrIfNotExists);
	}

	hFile = CreateFile (strFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
			OPEN_ALWAYS, 0, NULL);

	bErrIfNotExists = TRUE;

	if (hFile == INVALID_HANDLE_VALUE)
		goto _lErr;

	if (bDontLoadIfTooLarge && 5*1024*1024 < GetFileSize (hFile, NULL))
	{
		CloseHandle (hFile);
		return DLLR_TOOLARGESIZE;
	}

	DWORD dwFileSize;
	DWORD dw;
	WORD wVer;

	dwFileSize = GetFileSize (hFile, NULL);
	wVer = 0;

	if (FALSE == ReadFile (hFile, &hdr, sizeof (hdr), &dw, NULL) ||
			strnicmp (hdr.szSig, DLFILE_SIG, strlen (DLFILE_SIG)) )
	{
		goto _lErr;
	}
	else
	{
		dwFileSize -= dw;
		wVer = hdr.wVer;
		if (wVer > DLFILE_CURRENT_VERSION)
			goto _lErr;
	}

	vDownloads.DeleteAll();

	fsnew (pBuffer, BYTE, dwFileSize);

	if (!ReadFile (hFile, pBuffer, dwFileSize, &dw, NULL) || dw != dwFileSize)
		goto _lErr;
	CloseHandle (hFile);
	hFile = INVALID_HANDLE_VALUE;

	if (!tmp.loadFromStateBuffer(pBuffer, &dwFileSize, wVer))
		goto _lErr;

	vDownloads = tmp;

	//test
	if (pBuffer)
		delete[] pBuffer;

	return DLLR_SUCCEEDED;

_lErr:
	if (hFile != INVALID_HANDLE_VALUE)
		CloseHandle (hFile);

	if (pBuffer)
		delete [] pBuffer;

	if (lt != DLLFT_SAV)
		DeleteFile (strFileName);

	if (nlt == DLLFT_SAV)
		return DLLR_FAILED;

	return Load (vDownloads, pszFileName, bDontLoadIfTooLarge, nlt, bErrIfNotExists);
}

BOOL fsDownloadRegSaver::Save(vmsDownloadList& vDownloads, LPCSTR pszFileName)
{
	if (!vDownloads.isDirty())
		return TRUE;

	fsString strFileName = theApp.m_strAppPath;
	strFileName += pszFileName;
	strFileName += ".sav";

	fsString strFileNameBak = theApp.m_strAppPath;
	strFileNameBak += pszFileName;
	strFileNameBak += ".bak";

	HANDLE hFile = CreateFile (strFileNameBak, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_HIDDEN, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	DWORD dw;

	fsDLFileHdr hdr;
	if (FALSE == WriteFile (hFile, &hdr, sizeof (hdr), &dw, NULL))
	{
		CloseHandle (hFile);
		return FALSE;
	}

	DWORD dwSize = 0;
	LPBYTE pBuffer = NULL;

	try
	{
		vDownloads.getStateBuffer(0, &dwSize, false);
		fsnew (pBuffer, BYTE, dwSize);
		vDownloads.getStateBuffer(pBuffer, &dwSize, true);
	}
	catch (const std::exception& ex)
	{
		ASSERT (FALSE);
		vmsLogger::WriteLog("fsDownloadRegSaver::Save " + tstring(ex.what()));

		if (pBuffer)
			delete [] pBuffer;
		CloseHandle (hFile);
		return FALSE;
	}
	catch (...)
	{
		ASSERT (FALSE);
		vmsLogger::WriteLog("fsDownloadRegSaver::Save unknown exception");

		if (pBuffer)
			delete [] pBuffer;
		CloseHandle (hFile);
		return FALSE;
	}

	if (FALSE == WriteFile (hFile, pBuffer, dwSize, &dw, NULL))
	{
		if (pBuffer)
			delete [] pBuffer;
		CloseHandle (hFile);
		return FALSE;
	}

	if (pBuffer)
		delete [] pBuffer;

	BOOL bOK = FlushFileBuffers (hFile);
	BOOL bOK2 = CloseHandle (hFile);

	if (!bOK || !bOK2)
		return FALSE;

	if (GetFileAttributes (strFileName) != DWORD (-1))
	{
		SetFileAttributes (strFileName, FILE_ATTRIBUTE_HIDDEN);
		DeleteFile (strFileName);
	}

	bOK = MoveFile (strFileNameBak, strFileName);

	vDownloads.onStateSavedSuccessfully();

	return bOK;
}

bool fsDownloadRegSaver::IsStoringLogTurnedOn()
{
	return m_bDontSaveLogs != FALSE;
}
