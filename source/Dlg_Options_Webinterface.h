/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#if !defined(AFX_DLG_OPTIONS_GENERAL_MISC_H__16743713_76E4_49D8_9720_42A72A683929__INCLUDED_)
#define AFX_DLG_OPTIONS_GENERAL_MISC_H__16743713_76E4_49D8_9720_42A72A683929__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#include "Dlg_Options_Page.h"
#include "../resource.h"

class CDlg_Options_Webinterface : public CDlg_Options_Page
{

public:
	BOOL Apply();
	CString get_PageShortTitle();
	CString get_PageTitle();
	CDlg_Options_Webinterface(CWnd* pParent = NULL);

	//{{AFX_DATA(CDlg_Options_Webinterface)
	enum { IDD = IDD_WEBINTERFACE_DIALOG };
	//}}AFX_DATA

protected:
//	void ApplyLanguage();

	//{{AFX_MSG(CDlg_Options_Webinterface)
	virtual BOOL OnInitDialog();
	//afx_msg void OnDestroy();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif
