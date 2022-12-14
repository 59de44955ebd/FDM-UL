/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#if !defined(AFX_SCHEDULE_WTSPAGE_H__C7737538_D613_4BC4_AF3E_A98D89CE3CBA__INCLUDED_)
#define AFX_SCHEDULE_WTSPAGE_H__C7737538_D613_4BC4_AF3E_A98D89CE3CBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

class CSchedule_WTSPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CSchedule_WTSPage)

public:
	struct fsSchedule* m_task;	
	CSchedule_WTSPage();
	~CSchedule_WTSPage();

	//{{AFX_DATA(CSchedule_WTSPage)
	enum { IDD = IDD_SCHEDULE_WHATTOSTART };
	CListCtrl	m_wndUnselDlds;
	CListCtrl	m_wndSelDlds;
	CComboBox	m_wndTUM;
	CButton	m_btnToUnsel;
	CButton	m_btnToSel;
	CComboBox	m_wndShutdownType;
	CButton	m_btnChoose;
	CComboBox	m_wndWTS;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(CSchedule_WTSPage)
	public:
	virtual BOOL OnApply();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    
	//}}AFX_VIRTUAL

protected:
	void PrepareCHMgr(CPoint point);
	void ApplyLanguage();
		
	BOOL ApplyStartStopDownloads();
	void FreeSchedule();
	
	BOOL ApplyProg();
	
	void UpdateEnabled ();
	
	void BuildDownloadsList();
	int m_iWTS;	
	
	void ShowGroup (int iGrp, BOOL bShow = TRUE, BOOL bEnabled = TRUE);
	
	//{{AFX_MSG(CSchedule_WTSPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeWts();
	afx_msg void OnChangeProgname();
	afx_msg void OnChangeArguments();
	afx_msg void OnChoosename();
	afx_msg void OnClickUnseldlds(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickSeldlds(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTosel();
	afx_msg void OnTounsel();
	afx_msg void OnSelchangeTum();
	afx_msg void OnSelchangeShutdowntype();
	afx_msg void OnForceexit();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnWhatisthis();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}

#endif 
