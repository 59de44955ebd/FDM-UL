/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "FdmApp.h"
#include "Dlg_YtDlp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlg_YtDlp::CDlg_YtDlp(CWnd* pParent )
	: CDialog(CDlg_YtDlp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_YtDlp)
	//}}AFX_DATA_INIT
}

void CDlg_YtDlp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_YtDlp)
	DDX_Control(pDX, IDC_FORMAT, m_wndFormat);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_YtDlp, CDialog)
	//{{AFX_MSG_MAP(CDlg_YtDlp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlg_YtDlp::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_wndFormat.Clear();
	for (int i = 0; i < m_formats.GetSize(); i++)
		m_wndFormat.AddString(m_formats.GetAt(i));
	m_wndFormat.SetCurSel(0);

	return TRUE;
}

void CDlg_YtDlp::OnOK()
{
	m_selectedFormat = m_wndFormat.GetCurSel ();
	CDialog::OnOK();
}
