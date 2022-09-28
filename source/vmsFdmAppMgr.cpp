/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "vmsFdmAppMgr.h"
#include "FdmApp.h"
#include "MyMessageBox.h"

vmsFdmAppMgr::vmsFdmAppMgr()
{
}

vmsFdmAppMgr::~vmsFdmAppMgr()
{
}

LPCSTR vmsFdmAppMgr::getBuildNumberAsString()
{
	static std::string str;
	if (!str.empty ())
		return str.c_str ();
	str = getVersion ()->m_appVersion.size () > 2 ? getVersion ()->m_appVersion [2].toString () : "???";
	return str.c_str ();
}

int vmsFdmAppMgr::getBuildNumber()
{
	return getVersion ()->m_appVersion.size () > 2 ? getVersion ()->m_appVersion [2].dwVal : -1;
}

const vmsBinaryFileVersionInfo* vmsFdmAppMgr::getVersion()
{
	static vmsBinaryFileVersionInfo bfvi;
	if (bfvi.m_appVersion.size () == 0)
	{
		TCHAR tsz [MAX_PATH];
		GetModuleFileName (NULL, tsz, MAX_PATH);
		bfvi.Retrieve (tsz);
	}
	return &bfvi;
}

LPCSTR vmsFdmAppMgr::getAppVersionedName()
{
	static std::string str;
	if (str.empty ())
	{
		str = getAppName ();
		str += ' ';
		str += getVersion ()->m_tstrProductVersion;
	}
	return str.c_str ();
}

LPCSTR vmsFdmAppMgr::getAppAgentName()
{
	static std::string str;
	if (str.empty ())
	{
		str = "FDM ";
		char sz [100];
		str += itoa (getVersion ()->m_appVersion [0].dwVal, sz, 10);
		str += ".x";
	}
	return str.c_str ();
}

LPCSTR vmsFdmAppMgr::getAppName()
{
	return getVersion ()->m_tstrProductName.c_str ();
}

LPCSTR vmsFdmAppMgr::getAppAgentNameUf()
{
	static std::string str;
	if (str.empty ())
	{
		str = "Free Download Manager ";
		char sz [100];
		str += itoa (getVersion ()->m_appVersion [0].dwVal, sz, 10);
		str += ".x";
	}
	return str.c_str ();
}

//LPCSTR vmsFdmAppMgr::getAppBtAgentName()
//{
//	static std::string str;
//	if (str.empty ())
//	{
//		str = "FDM/";
//		char sz [100];
//		str += itoa (getVersion ()->m_appVersion [0].dwVal, sz, 10);
//		str += '.';
//		str += itoa (getVersion ()->m_appVersion [1].dwVal, sz, 10);
//		str += '(';
//		str += itoa (getVersion ()->m_appVersion [2].dwVal, sz, 10);
//		str += ')';
//	}
//	return str.c_str ();
//}
