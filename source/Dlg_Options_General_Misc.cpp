/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "stdafx.h"
#include "Dlg_Options_General_Misc.h"
#include "ShedulerWnd.h"
#include "MainFrm.h"
#include "vmsFileUtil.h"

extern CShedulerWnd *_pwndScheduler;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDlg_Options_General_Misc::CDlg_Options_General_Misc(CWnd* pParent )
	: CDlg_Options_Page(CDlg_Options_General_Misc::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg_Options_General_Misc)
	//}}AFX_DATA_INIT

	m_bExitToutChanged = m_bShutdownToutChanged = false;
	m_bDTAEChanged = false;
}

void CDlg_Options_General_Misc::DoDataExchange(CDataExchange* pDX)
{
	CDlg_Options_Page::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg_Options_General_Misc)
	DDX_Control(pDX, IDC_SHUTDOWN_TOUT, m_wndShutdownTout);
	DDX_Control(pDX, IDC_LAUNCHDLD_TOUT, m_wndLaunchDldTout);
	DDX_Control(pDX, IDC_EXIT_TOUT, m_wndExitTout);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg_Options_General_Misc, CDlg_Options_Page)
	//{{AFX_MSG_MAP(CDlg_Options_General_Misc)
	ON_CBN_SELCHANGE(IDC_EXIT_TOUT, OnSelchangeExitTout)
	ON_CBN_SELCHANGE(IDC_SHUTDOWN_TOUT, OnSelchangeShutdownTout)
	ON_CBN_SELCHANGE(IDC_LAUNCHDLD_TOUT, OnSelchangeLaunchdldTout)
	ON_BN_CLICKED(IDC_DISABLEWDTASKAFTEREXEC, OnDisablewdtaskafterexec)
	ON_BN_CLICKED(IDC_CHOOSEYTDLPPATH, OnChooseYtDlp)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlg_Options_General_Misc::OnInitDialog()
{
	CDlg_Options_Page::OnInitDialog();

	CComboBox* pboxes [] = {
		&m_wndExitTout, &m_wndShutdownTout, &m_wndLaunchDldTout
	};

	for (UINT i = 0; i < sizeof (pboxes) / sizeof (CComboBox*); i++)
	{
		pboxes [i]->AddString (LS (L_DONTASKFORCONF));

		UINT aSecs [] = {
			5, 15, 30, 60
		};
		for (UINT j = 0; j < sizeof (aSecs) / sizeof (UINT); j++)
		{
			CString str;
			str.Format (LS (L_N_SECONDS), aSecs [j]);
			pboxes [i]->AddString (str);
		}

		pboxes [i]->AddString (LS (L_DISABLECONFTIMEOUT));

		UINT uTimeout;
		switch (i)
		{
			case 0: uTimeout = _App.ConfTimeout_Exit (); break;
			case 1: uTimeout = _App.ConfTimeout_Shutdown (); break;
			case 2: uTimeout = _App.ConfTimeout_LaunchDld (); break;
			default: ASSERT (FALSE); uTimeout = 0; break;
		}

		SelectToutItem (pboxes [i], uTimeout);
	}

	CheckDlgButton (IDC_ASKFORST, _App.WD_LastShutdownType_DontAsk () ? BST_UNCHECKED : BST_CHECKED);
	CheckDlgButton (IDC_DISABLEWDTASKAFTEREXEC, _App.WD_DisableAfterExec () ? BST_CHECKED : BST_UNCHECKED);

	CSpinButtonCtrl *pSpin = (CSpinButtonCtrl*) GetDlgItem (IDC_AUTOSAVESPIN);
	pSpin->SetRange (1, UD_MAXVAL);
	SetDlgItemInt (IDC_AUTOSAVE, _App.AutosaveInterval () / 60 / 1000, FALSE);

	GetDlgItem(IDC_YTDLPPATH)->SetWindowText(_App.YtDlp_Path());

	ApplyLanguage ();

	return TRUE;
}

CString CDlg_Options_General_Misc::get_PageTitle()
{
	return LS (L_MISC);
}

CString CDlg_Options_General_Misc::get_PageShortTitle()
{
	return LS (L_MISC);
}

BOOL CDlg_Options_General_Misc::Apply()
{
	_App.WD_LastShutdownType_DontAsk (IsDlgButtonChecked (IDC_ASKFORST) == BST_UNCHECKED);
	_App.ConfTimeout_Exit (GetTimeoutForToutItem (&m_wndExitTout));
	_App.ConfTimeout_Shutdown (GetTimeoutForToutItem (&m_wndShutdownTout));
	_App.ConfTimeout_LaunchDld (GetTimeoutForToutItem (&m_wndLaunchDldTout));

	int pos = -1;

	if (m_bExitToutChanged)
	{
		pos = -1;
		_pwndScheduler->ExitWhenDone (&pos);
		if (pos != -1)
		{
			m_bExitToutChanged = false;
			_pwndScheduler->GetMgr ()->GetTask (pos)->uWaitForConfirmation = _App.ConfTimeout_Exit ();
			_pwndScheduler->GetMgr ()->setDirtyFlagForTask(pos);
		}
	}

	fsShutdownType enType = (fsShutdownType) _App.WD_LastShutdownType ();
	if (m_bShutdownToutChanged)
	{
		pos = -1;
		_pwndScheduler->TurnoffWhenDone (enType, &pos);
		if (pos != -1)
		{
			m_bShutdownToutChanged = false;
			_pwndScheduler->GetMgr ()->GetTask (pos)->uWaitForConfirmation = _App.ConfTimeout_Shutdown ();
			_pwndScheduler->GetMgr ()->setDirtyFlagForTask(pos);
		}
	}

	if (m_bDTAEChanged)
	{
		m_bDTAEChanged = false;
		BOOL bDis = IsDlgButtonChecked (IDC_DISABLEWDTASKAFTEREXEC) == BST_CHECKED;

		_App.WD_DisableAfterExec (bDis);

		_pwndScheduler->ExitWhenDone (&pos);
		if (pos != -1)
		{
			if (bDis)
				_pwndScheduler->GetMgr ()->GetTask (pos)->dwFlags |= SCHEDULE_AUTODIS;
			else
				_pwndScheduler->GetMgr ()->GetTask (pos)->dwFlags &= ~SCHEDULE_AUTODIS;
			_pwndScheduler->GetMgr ()->setDirtyFlagForTask(pos);
		}

		_pwndScheduler->TurnoffWhenDone (enType, &pos);
		if (pos != -1)
		{
			if (bDis)
				_pwndScheduler->GetMgr ()->GetTask (pos)->dwFlags |= SCHEDULE_AUTODIS;
			else
				_pwndScheduler->GetMgr ()->GetTask (pos)->dwFlags &= ~SCHEDULE_AUTODIS;
			_pwndScheduler->GetMgr ()->setDirtyFlagForTask(pos);
		}
	}

	UINT nVal;

	nVal = GetDlgItemInt (IDC_AUTOSAVE, NULL, FALSE);
	if (nVal == 0)
	{
		CString str; str.Format (LS (L_ENTERGREATER), 0);
		MessageBox (str, LS (L_INPERR), MB_ICONEXCLAMATION);
		CEdit *pE = (CEdit*) GetDlgItem (IDC_AUTOSAVE);
		pE->SetSel (0, -1);
		pE->SetFocus ();
		return FALSE;
	}

	_App.AutosaveInterval (nVal * 60 * 1000);

	CString strYtDlpPath;
	GetDlgItemText(IDC_YTDLPPATH, strYtDlpPath);

	_App.YtDlp_Path(strYtDlpPath);
	if (!strYtDlpPath.IsEmpty() && vmsFileUtil::FileExists(strYtDlpPath))
	{
		strcpy_s(_App.m_szYtDlpPath, sizeof _App.m_szYtDlpPath, strYtDlpPath);
		_App.m_bHasYtDlp = TRUE;
	}
	else
	{
		const char *other_dirs[] = { ".", NULL };
		_App.m_bHasYtDlp = PathFindOnPath(_App.m_szYtDlpPath, other_dirs);
		if (_App.m_bHasYtDlp)
			_App.YtDlp_Path(_App.m_szYtDlpPath);
	}

	return TRUE;
}

void CDlg_Options_General_Misc::ApplyLanguage()
{
	fsDlgLngInfo lnginfo [] =  {
		fsDlgLngInfo (IDC__TOUTSFORCONFS, L_TOUTSFORCONFS),
		fsDlgLngInfo (IDC__EXIT, L_EXIT),
		fsDlgLngInfo (IDC__SHUTDOWN, L_SHUTDOWN),
		fsDlgLngInfo (IDC__LAUNCHDLD, L_LAUNCHDLD),
		fsDlgLngInfo (IDC_ASKFORST, L_ASKFORST),
		fsDlgLngInfo (IDC_DISABLEWDTASKAFTEREXEC, L_DISABLEWHENDONEAFTEREXEC),
		fsDlgLngInfo (IDC__AUTOSAVE, L_AUTOSAVE),
	};

	_LngMgr.ApplyLanguage (this, lnginfo, sizeof (lnginfo) / sizeof (fsDlgLngInfo), 0);
}

void CDlg_Options_General_Misc::SelectToutItem(CComboBox *pbox, UINT uTimeout)
{
	switch (uTimeout) {
	case 0: pbox->SetCurSel (0); break;
	case 5: pbox->SetCurSel (1); break;
	case 15: pbox->SetCurSel (2); break;
	default:
	case 30: pbox->SetCurSel (3); break;
	case 60: pbox->SetCurSel (4); break;
	case UINT_MAX: pbox->SetCurSel (5); break;
	}
}

UINT CDlg_Options_General_Misc::GetTimeoutForToutItem(CComboBox *pbox)
{
	switch (pbox->GetCurSel ()){
	case 0:	return 0;
	case 1: return 5;
	case 2: return 15;
	case CB_ERR:
	default:
	case 3: return 30;
	case 4: return 60;
	case 5: return UINT_MAX;
	}
}

void CDlg_Options_General_Misc::OnSelchangeExitTout()
{
	m_bExitToutChanged = true;
}

void CDlg_Options_General_Misc::OnSelchangeShutdownTout()
{
	m_bShutdownToutChanged = true;
}

void CDlg_Options_General_Misc::OnSelchangeLaunchdldTout()
{
}

void CDlg_Options_General_Misc::OnDisablewdtaskafterexec()
{
	m_bDTAEChanged = true;
}

void CDlg_Options_General_Misc::OnDestroy()
{
	CDlg_Options_Page::OnDestroy();
}

void CDlg_Options_General_Misc::OnChooseYtDlp()
{
	CFileDialog dlg(TRUE, "exe", NULL, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, "yt-dlp.exe|*.exe", this); // OFN_NOCHANGEDIR
	if (_DlgMgr.DoModal(&dlg) != IDOK)
		return;
	GetDlgItem(IDC_YTDLPPATH)->SetWindowText(dlg.GetPathName());
}
