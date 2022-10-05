/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "StdAfx.h"

#include "vmsFdmWebInterfaceServer.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CDownloadsWnd* _pwndDownloads;

vmsFdmWebInterfaceServer::vmsFdmWebInterfaceServer()
{
}

vmsFdmWebInterfaceServer::~vmsFdmWebInterfaceServer()
{
}

BOOL vmsFdmWebInterfaceServer::ProcessRequest(vmsHttpRequest &request, vmsHttpResponse &response)
{
	if (lstrcmpi (request.get_RequestType (), "GET"))
		return FALSE;

	if (_App.Webinterface_UsePwd())
	{
		CString strU = _App.Webinterface_Login();
		CString strP = _App.Webinterface_Password();
		if (strU.IsEmpty () == FALSE && lstrcmp (request.get_Auth (), strU + ":" + strP))
		{
			response.set_ResponseCode ("401 Authorization Required");
			return FALSE;
		}
	}

	LPCSTR pszRes = request.get_ResourcePath ();

	if (strncmp (pszRes, "/adddownload.req?", lstrlen ("/adddownload.req?")) == 0)
		return RequestCreateNewDownload (pszRes, response);

	response.set_ResponseCode ("404 Not Found");
	return FALSE;
}

BOOL vmsFdmWebInterfaceServer::RequestCreateNewDownload(LPCSTR pszRes, vmsHttpResponse &response)
{
	CString strUrl;
	pszRes += lstrlen ("/adddownload.req?");
	if (strnicmp (pszRes, "URL=", 4))
	{
		response.set_Body (m_strAddDownloadRes_err.c_str (), m_strAddDownloadRes_err.length ());
		return FALSE;
	}
	pszRes += 4;

	while (*pszRes)
	{
		char c;
		if (*pszRes == '%')
		{
			pszRes++;
			char sz [3];
			sz [0] = *pszRes++;
			if (*pszRes == 0)
				return FALSE;
			sz [1] = *pszRes++;
			sz [2] = 0;
			int i;
			sscanf (sz, "%x", &i);
			c = (char)i;
		}
		else
		{
			c = *pszRes++;
			if (c == '+')
				c = ' ';
		}

		strUrl += c;
	}

	CString str;
	int i = 0;
	for (i = 0; i < strUrl.GetLength () - 1;)
	{
		if (strUrl [i] == '&' && strUrl [i+1] == '#')
		{
			int k = i + 2;
			CString str2;
			bool bHex = false;
			if (k < strUrl.GetLength ())
				bHex = strUrl [k] == 'x';
			if (bHex)
				k++;
			while (isdigit (strUrl [k]))
				str2 += strUrl [k++];
			if (str2.IsEmpty () == FALSE &&
				 (strUrl [k] == ';' || strUrl.GetLength () == k))
			{
				i = ++k;
				wchar_t wsz [2];
				if (bHex)
				{
					int j;
					sscanf (str2, "%x", &j);
					wsz [0] = (wchar_t)j;
				}
				else
				{
					wsz [0] = (wchar_t)atoi (str2);
				}
				wsz [1] = 0;
				char sz [2];
				WideCharToMultiByte (CP_ACP, 0, wsz, -1, sz, 1, NULL, NULL);
				sz [1] = 0;
				str += sz;
				continue;
			}

		}

		str += strUrl [i++];
	}
	if (i == strUrl.GetLength () - 1)
		str += strUrl [i];
	strUrl = str;

	//UINT CDownloadsWnd::CreateDownload(LPCSTR pszStartUrl, BOOL bReqTopMostDialog, LPCSTR pszComment, LPCSTR pszReferer,
	//	  BOOL bSilent, DWORD dwForceAutoLaunch, BOOL *pbAutoStart, vmsDWCD_AdditionalParameters* pParams, UINT* pRes)
	UINT nID = _pwndDownloads->CreateDownload(strUrl.GetString(), FALSE, NULL, NULL, TRUE);

	BOOL bAdded = nID != UINT_MAX;
	if (bAdded == FALSE)
		response.set_Body (m_strAddDownloadRes_err.c_str (), m_strAddDownloadRes_err.length ());
	else
		response.set_Body (m_strAddDownloadRes_ok.c_str (), m_strAddDownloadRes_ok.length ());

	return TRUE;
}

