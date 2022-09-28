/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "vmsInternetSession.h"
#include "inetutil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

vmsInternetSession::vmsInternetSession()
{

}

vmsInternetSession::~vmsInternetSession()
{

}

fsInternetResult vmsInternetSession::Create(LPCSTR pszAgent, fsInternetAccessTypeEx enAT, LPCSTR pszProxyName, fsNetworkProtocol enProtocol)
{
	return fsInternetSession::Create (pszAgent, (fsInternetAccessType)enAT, pszProxyName);
}
