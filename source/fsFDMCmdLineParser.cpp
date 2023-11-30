/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "FdmApp.h"
#include "fsFDMCmdLineParser.h"
#include "vmsAppMutex.h"
//#include "vmsFdmUtils.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

fsFDMCmdLineParser::fsFDMCmdLineParser()
	//:
	//m_bRunAsElevatedTasksProcessor (false),
	//m_bInstallIeIntegration (false)
{
	m_bAnotherFDMStarted = FALSE;
	m_bForceSilent = FALSE;
	//m_bNeedExit = false;
	//m_bNeedRegisterServer = m_bNeedUnregisterServer = false;
}

fsFDMCmdLineParser::~fsFDMCmdLineParser()
{
}

void fsFDMCmdLineParser::Parse(PerformTasksOfType enPTT)
{
	extern vmsAppMutex _appMutex;
	m_bAnotherFDMStarted = _appMutex.isAnotherInstanceStartedAlready ();

	HWND hWnd = NULL;
	if (m_bAnotherFDMStarted)
		hWnd = FindWindow(MY_CLASSNAME, NULL);

	if (FALSE == m_parser.Parse ())
		return;

	m_bForceSilent = FALSE;

	CFdmApp* app = (CFdmApp*) AfxGetApp ();

	for (int i = 0; i < m_parser.Get_ParameterCount (); i++)
	{
		LPCSTR pszParam = m_parser.Get_Parameter (i);
		LPCSTR pszValue = m_parser.Get_ParameterValue (i);

		if (strcmp (pszParam, "?") == 0 && enPTT == Normal)
		{
			MessageBox (0,
				"fdm.exe [-fs] [-fn=...] [-url=]url1 [-fn=...] [-url=]url2 ...\n\n"
				"-fs - force silent mode.\n"
				"-fn - use this filename (silent mode only)"
				//"If url contains spaces it should be in quotes.\n\n"
				//"Example:\n"
				//"fdm.exe -fs \"https://site.com/read me.txt\"",
				,"Command line usage", 0);
		}
		else if (stricmp (pszParam, "fs") == 0)
		{
			m_bForceSilent = TRUE;
		}
		else if ((stricmp (pszParam, "URL") == 0 || *pszParam == 0) && enPTT == Normal)
		{
			fsURL url;
			BOOL bUrl = IR_SUCCESS == url.Crack (pszValue) && pszValue [1] != ':';
			if (bUrl == FALSE)
				continue;

			if (m_bAnotherFDMStarted && hWnd)
			{
				//IWGUrlReceiver* pAdd = NULL;
				//CoCreateInstance (CLSID_WGUrlReceiver, NULL, CLSCTX_ALL,
				//	IID_IWGUrlReceiver, (void**) &pAdd);

				//if (pAdd)
				//{
				//	CComBSTR _url = pszValue;
				//	pAdd->put_Url (_url);
				//	if (m_bForceSilent)
				//		pAdd->put_ForceSilent (TRUE);
				//	pAdd->AddDownload ();
				//	pAdd->Release ();
				//}

				CHAR _url[L_MAX_URL_LENGTH];
				strcpy(_url, pszValue);
				if (i > 0 && stricmp(m_parser.Get_Parameter(i - 1), "fn") == 0)
				{
					strcat(_url, " ");
					strcat(_url, m_parser.Get_ParameterValue(i - 1));
				}

				COPYDATASTRUCT ds;

				// ORG
				ds.dwData = m_bForceSilent ? 1 : 0;
				//ds.cbData = strlen(pszValue);
				//ds.lpData = (void *)pszValue;

				//NEW
				ds.cbData = strlen(_url);
				ds.lpData = (void *)_url;

				SendMessage(hWnd, WM_COPYDATA, (WPARAM)(HWND)0, (LPARAM)&ds);
			}
			else
			{
				CFdmApp::_inc_UrlToAdd _url;
				_url.strUrl = pszValue;
				_url.bForceSilent = m_bForceSilent;

				if (i > 0 && stricmp(m_parser.Get_Parameter(i - 1), "fn") == 0)
				{
					_url.strFilename = m_parser.Get_ParameterValue(i - 1);
					_url.bForceFilename = TRUE;
				}
				//else
				//{
				//	_url.bForceFilename = FALSE;
				//}

				app->m_vUrlsToAdd.add (_url);
			}
		}
	}
}

BOOL fsFDMCmdLineParser::is_ForceSilentSpecified()
{
	return m_bForceSilent;
}

void fsFDMCmdLineParser::ReadIntVector(LPCTSTR ptsz, std::vector <int>& v)
{
	if (!ptsz)
		return;

	while (*ptsz)
	{
		tstring tstr;
		while (_istdigit (*ptsz))
			tstr += *ptsz++;
		if (!tstr.empty ())
			v.push_back (_ttoi (tstr.c_str ()));
		if (*ptsz++ != ',')
			return;
	}
}
