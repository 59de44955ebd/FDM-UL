/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#if !defined(AFX_DLG_YTDLP_H__EF2ECB4B_4C91_4251_B43B_D948CDB7C7E4__INCLUDED_)
#define AFX_DLG_YTDLP_H__EF2ECB4B_4C91_4251_B43B_D948CDB7C7E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

class CDlg_YtDlp : public CDialog
{

public:
	CDlg_YtDlp(CWnd* pParent = NULL);

	//{{AFX_DATA(CDlg_YtDlp)
	enum { IDD = IDD_YTDLP };
	CComboBox	m_wndFormat;
	//}}AFX_DATA

	CStringArray m_formats;
	int m_selectedFormat;

	//{{AFX_VIRTUAL(CDlg_YtDlp)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//void ApplyLanguage(); //TODO

	//{{AFX_MSG(CDlg_YtDlp)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}

#endif
