/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#if !defined(AFX_VMSFDMWEBINTERFACESERVER_H__B258E06E_3C7B_4F7C_BAA1_A448FDCE8D18__INCLUDED_)
#define AFX_VMSFDMWEBINTERFACESERVER_H__B258E06E_3C7B_4F7C_BAA1_A448FDCE8D18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#include "vmsHttpResourceContainer.h"

class vmsFdmWebInterfaceServer : public vmsHttpResourceContainer
{
public:

	virtual BOOL ProcessRequest (vmsHttpRequest &request, vmsHttpResponse &response);

	vmsFdmWebInterfaceServer();
	virtual ~vmsFdmWebInterfaceServer();

protected:
	BOOL RequestCreateNewDownload (LPCSTR pszRes, vmsHttpResponse &response);
	std::string m_strAddDownloadRes_ok = "Your request has been procceded successfully.";
	std::string m_strAddDownloadRes_err = "An error occured while trying to process this request.";
};

#endif
