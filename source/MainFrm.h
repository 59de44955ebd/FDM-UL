/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#if !defined(AFX_MAINFRM_H__AC3FA611_4FF2_4779_82DF_504A2BF21D9A__INCLUDED_)
#define AFX_MAINFRM_H__AC3FA611_4FF2_4779_82DF_504A2BF21D9A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#include "AppStatusBar.h"
#include "ChildView.h"
#include "ToolBarEx.h"
#include "fsODMenu.h"

#pragma warning (push, 3)
#pragma warning (pop)

#define WM_SHOWTRAYMENU			(WM_APP+101)
#define WM_SHOWDOWNLOADDIALOG	(WM_APP+102)
#define WM_DOMODAL				(WM_APP+103)

#define ID_APP_EXIT_2	40000

class CMainFrame : public CFrameWnd
{
	friend class CFdmApp;

public:
	CMainFrame();

protected:
	DECLARE_DYNAMIC(CMainFrame)

public:

public:
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual void RecalcLayout(BOOL bNotify = TRUE);
	protected:
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	//}}AFX_VIRTUAL

public:
	BOOL m_bInited;

	static void ShowOnDownloadDoneBalloon (fsDownload* dld);
	void SetActivePlugin (int nIndex);

	void RebuidDownloadsList();

	static void ShowTimeoutBalloon (LPCSTR pszInfo, LPCSTR pszTitle, DWORD dwIcon = NIIF_INFO, BOOL bClear = FALSE);

	void ShowTrayMenu(BOOL bModeTray = TRUE);

	void SaveState(DWORD dwWhat);

	BOOL m_bCloseAsMinimize;
	BOOL m_bMinToTray;

	CImageList m_imgsMenu, m_dimgsMenu;

	CImageList m_imgsTool, m_dimgsTool;

	void RemovePluginMenu();
	void AddPluginMenuView(HMENU hMenuView, fsSetImage* pImages, int cImages, wgMenuViewItem *pItems, int cItems);
	void RemovePluginMenuView();

	void AddPluginMenu (HMENU hMenu, fsSetImage* pImages, int cImages);
	virtual ~CMainFrame();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CAppStatusBar  m_wndStatusBar;
	CChildView  m_wndView;
	BOOL m_bQueryForExit;

protected:
	void SaveAllData (DWORD dwWhat);
	afx_msg LRESULT OnDoModal (WPARAM, LPARAM lp);
	afx_msg LRESULT OnMyBalloonClosed (WPARAM, LPARAM);
	struct TimeoutBalloonInfo {
		CString strInfo;
		CString strTitle;
		DWORD dwIcon;
		BOOL bClear;
	};
	afx_msg LRESULT OnShowBalloon (WPARAM wp, LPARAM lp);

	class CFdmBalloon* m_pFdmBalloon;
	class CFdmBalloonContent* m_pFdmBalloonContent;
	enum FdmBalloonContentType {
		FBCT_UNKNOWN,
		FBCT_ON_DOWNLOAD_DONE,
	} m_enFdmBalloonContentType;
	void ShowFdmBalloon (CFdmBalloonContent*, FdmBalloonContentType);
	LONG m_cThreadsRunning;
	HANDLE m_hevShuttingDown;
	vmsCriticalSection m_csSaveAllData;
	static DWORD WINAPI _threadAutosave (LPVOID);
	int GetTumMenuPosition();

	UINT m_nShutdownMsg;
	afx_msg LRESULT OnPowerBroadCast (WPARAM, LPARAM);

	afx_msg void OnUpdateTotalSpeed (CCmdUI* pCmdUI);

	BOOL ImportListOfDownloads_FromDLInfoListFile(LPCSTR pszFile);
	BOOL ImportDownload (IXMLDOMNode* pNode, DLDS_LIST_REF v);

	BOOL ImportListOfDownloads_FromURLListFile (LPCSTR pszFile);

	afx_msg void OnTUMChanged();

	BOOL is_MouseInTray();

	afx_msg LRESULT OnSaveAllData (WPARAM, LPARAM);

	CReBar m_wndReBar;

	afx_msg LRESULT OnShowTrayMenu (WPARAM, LPARAM);
	void LoadToolImages();

	CString m_strTimeoutBallon_Msgs;

	void Balloon_ShowDLInfo(BOOL bCheckSettings = TRUE);
	BOOL m_bTrayMenuShowing;

	void ShowBalloon (LPCSTR pszInfo, LPCSTR pszTitle, BOOL bCheckSettings = TRUE, DWORD dwIcon = NIIF_INFO);
	void HideBalloon();
	BOOL m_bBalloonShowing;
	int m_balloonX, m_balloonY;

	void RemovePluginMenuView2();
	void AddPluginMenuView (HMENU hMenu, fsSetImage* pImages, int cImages);
	//afx_msg void OnUpdatePluginMenuView(CCmdUI *pCmdUI);

	wgMenuViewItem *m_pPluginMenuViewItems;
	int m_cPluginMenuViewItems;
	int m_cPluginMenuViewInserted;

	afx_msg void OnTBChange (NMHDR*, LRESULT* res);
	afx_msg void OnTBGetButtonInfo (NMHDR*, LRESULT* res);
	afx_msg void OnTBReset (NMHDR*, LRESULT* res);
	afx_msg void OnTBCustHelp (NMHDR*, LRESULT* res);
	afx_msg void OnTBEndDrag (NMHDR*, LRESULT* res);
	afx_msg void OnTBBeginDrag (NMHDR*, LRESULT* res);
	afx_msg void OnTBEndAdjust (NMHDR*, LRESULT* res);
	afx_msg void OnTBBeginAdjust (NMHDR*, LRESULT* res);
	afx_msg void OnTBQueryInsert (NMHDR*, LRESULT* res);
	afx_msg void OnTBQueryDelete (NMHDR*, LRESULT* res);

	virtual LRESULT WindowProc (UINT msg, WPARAM wp, LPARAM lp);
	static UINT m_umsgTaskBarCreated;

	void UpdateSettings();

	void SetMenuImages();

	void ApplyLanguageToMenu();
	void ApplyLanguage();

	//afx_msg void OnLngMenu (UINT id);

	//void BuildLngMenu();
	afx_msg void OnViewStatusbar();
	afx_msg void OnViewToolbar();

	afx_msg void OnAltPlusDigit (UINT nID);

	void OnUpdateSwitchTo (CCmdUI *pCmdUI);

	afx_msg void OnSwitchTo (UINT nID);

	void BuildSwitchToMenu();
	void UpdateTitle();

	void SaveSettings(DWORD dwWhat);
	void ReadSettings();
	void LoadMenuImages();
	fsODMenu m_odTrayMenu;
	fsODMenu m_odmenu;

	afx_msg LRESULT OnTrayMsg (WPARAM wp, LPARAM lp);

	int m_cMenuMainItemsAdded,
		m_cMenuViewItemsAdded;

	//{{AFX_MSG(CMainFrame)
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnClose();
	afx_msg void OnDlddefoptions();
	afx_msg void OnDldroptions();
	afx_msg void OnTumHeavy();
	afx_msg void OnUpdateTumHeavy(CCmdUI* pCmdUI);
	afx_msg void OnTumLight();
	afx_msg void OnUpdateTumLight(CCmdUI* pCmdUI);
	afx_msg void OnTumMedium();
	afx_msg void OnUpdateTumMedium(CCmdUI* pCmdUI);
	afx_msg void OnDldCreate();
	afx_msg void OnTaskCreateNew();
	afx_msg void OnNeedExit();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnAppExit();
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg void OnShowmainwindow();
	afx_msg void OnStartall();
	afx_msg void OnStopall();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnEndSession(BOOL bEnding);
	afx_msg void OnTurnoffwhendone();
	afx_msg void OnUpdateTurnoffwhendone(CCmdUI* pCmdUI);
	afx_msg void OnAddsite();
	afx_msg void OnViewSwbar();
	afx_msg void OnUpdateViewSwbar(CCmdUI* pCmdUI);
	afx_msg void OnNcRButtonUp(UINT nHitTest, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnQueryEndSession();
	afx_msg void OnInsert();

	afx_msg void OnActivateWebinterface();
	afx_msg void OnUpdateActivateWebinterface(CCmdUI* pCmdUI);

	//afx_msg void OnUpdateLngMenu (CCmdUI* pCmdUI);
	//afx_msg void OnDllangfiles();

	afx_msg void OnProceedFurherInitialization();
	afx_msg void OnAppAbout();
	afx_msg void OnExportlistofdownloads();
	afx_msg void OnImportlistofdownloads();
	afx_msg void OnExitwhendone();
	afx_msg void OnUpdateExitwhendone(CCmdUI* pCmdUI);
	afx_msg void OnFind();
	afx_msg void OnFindnext();
	afx_msg void OnUpdateFindnext(CCmdUI* pCmdUI);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDldCreatebatch();
	afx_msg void OnFileImportImportlistofdownloadsfromclipboard();
	afx_msg void OnOptionsSm();

	afx_msg void OnPausealldlds();
	afx_msg void OnUpdatePausealldlds(CCmdUI* pCmdUI);

	afx_msg void OnAppExit2();
	afx_msg void OnLoadatstartup();
	afx_msg void OnUpdateLoadatstartup(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	vmsCriticalSection m_csExit;
	bool m_bExitHandlerPerformed;

public:
	bool onExit(bool bQueryExit);

private:
	void UpdateTumToolbarState();
};

// { {AFX_INSERT_LOCATION}}

#endif
