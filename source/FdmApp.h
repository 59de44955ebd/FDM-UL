/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#if !defined(AFX_FdmApp_H__0DFAE8B5_1F34_4956_8DFA_5AE79C242CB7__INCLUDED_)
#define AFX_FdmApp_H__0DFAE8B5_1F34_4956_8DFA_5AE79C242CB7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "../resource.h"
//#include "fdm.h"
#include "fsFDMCmdLineParser.h"

class CFdmApp : public CWinApp
{
public:
	CFdmApp();

	//{{AFX_VIRTUAL(CFdmApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

public:
	AFX_MODULE_STATE* GetModuleState();
	static void ScheduleExitProcess (DWORD dwSeconds);

	//void SaveSettings();

	CString m_strAppPath;

	BOOL Is_Starting();

	struct _inc_UrlToAdd {
		fsString strUrl;
		BOOL bForceSilent;
	};

	fs::list <_inc_UrlToAdd> m_vUrlsToAdd;
	~CFdmApp ();

	//{{AFX_MSG(CFdmApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	static DWORD WINAPI _threadExitProcess (LPVOID);

	BOOL m_bForceSilentSpecified;

	int m_nNoLngsErrReason;

	void CheckLocked();

	BOOL m_bStarting;

	BOOL CheckFdmStartedAlready(BOOL bSetForIfEx = TRUE);
	BOOL m_bEmbedding;
	BOOL InitLanguage();
};

//{{AFX_INSERT_LOCATION}}

#endif
