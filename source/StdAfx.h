/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#if !defined(AFX_STDAFX_H__3DEDF9D7_1A31_481A_8FBD_C2D53CEFE688__INCLUDED_)
#define AFX_STDAFX_H__3DEDF9D7_1A31_481A_8FBD_C2D53CEFE688__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN

//#define WINVER 0x501
//#define _WIN32_IE 0x501
//#define _WIN32_WINNT 0x500

//#define _WIN32_WINNT_WINXP                  0x0501 // Windows XP
//#define _WIN32_WINNT_WS03                   0x0502 // Windows Server 2003
//#define _WIN32_WINNT_WIN6                   0x0600 // Windows Vista
//#define _WIN32_WINNT_VISTA                  0x0600 // Windows Vista
//#define _WIN32_WINNT_WS08                   0x0600 // Windows Server 2008
//#define _WIN32_WINNT_LONGHORN               0x0600 // Windows Vista
//#define _WIN32_WINNT_WIN7                   0x0601 // Windows 7
//#define _WIN32_WINNT_WIN8                   0x0602 // Windows 8
//#define _WIN32_WINNT_WINBLUE                0x0603 // Windows 8.1
//#define _WIN32_WINNT_WINTHRESHOLD           0x0A00 // Windows 10
//#define _WIN32_WINNT_WIN10                  0x0A00 // Windows 10

#define WINVER 0x0601
#define _WIN32_WINNT 0x0601

#pragma warning(disable : 4995)
#pragma warning(disable : 4996)

#ifdef SCL_ENABLE
#pragma message ("============== WARNING: SCL_ENABLE is defined ==============")
#endif

#define _TB_SIZE_X	_SkinMgr.tbSizeX()
#define _TB_SIZE_Y	_SkinMgr.tbSizeY()
#define _TB_USE_ALPHA	_SkinMgr.tbUseAlpha()

#include <afxwin.h>
#include <afxext.h>
#include <afxdisp.h>
#include <afxdtctl.h>
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>
#endif

#include <intsafe.h>
#include <Ws2tcpip.h>
#include <Wspiapi.h>

#pragma warning (disable : 4192)
//#pragma warning (disable : 4146)
//#import "mshtml.tlb" rename("TranslateAccelerator", "mshtmlTranslateAccelerator")
#import "shdocvw.dll" rename("FindText", "shdocvwFindText")
#pragma warning (default : 4192)
//#pragma warning (default : 4146)

//#include "mshtmhst.h"
//_COM_SMARTPTR_TYPEDEF(IDocHostUIHandler, __uuidof(IDocHostUIHandler));
//_COM_SMARTPTR_TYPEDEF(ICustomDoc, __uuidof(ICustomDoc));
//
//#include "Mshtml.h"
//_COM_SMARTPTR_TYPEDEF(IHTMLDocument, __uuidof(IHTMLDocument));
//_COM_SMARTPTR_TYPEDEF(IHTMLDocument2, __uuidof(IHTMLDocument2));
//_COM_SMARTPTR_TYPEDEF(IHTMLElementCollection, __uuidof(IHTMLElementCollection));
//_COM_SMARTPTR_TYPEDEF(IHTMLFormElement, __uuidof(IHTMLFormElement));

#include <msxml.h>
_COM_SMARTPTR_TYPEDEF(IXMLDOMDocument, __uuidof(IXMLDOMDocument));
_COM_SMARTPTR_TYPEDEF(IXMLDOMNode, __uuidof(IXMLDOMNode));
_COM_SMARTPTR_TYPEDEF(IXMLDOMElement, __uuidof(IXMLDOMElement));
_COM_SMARTPTR_TYPEDEF(IXMLDOMNodeList, __uuidof(IXMLDOMNodeList));

//#define _ATL_APARTMENT_THREADED
//#include <atlbase.h>
//#include <atlcom.h>
//#include <atlsecurity.h>

class CFdmModule : public CComModule
{
public:
	LONG Unlock();
	LONG Lock();
	LPCTSTR FindOneOf(LPCTSTR p1, LPCTSTR p2);
	DWORD dwThreadID;
};
extern CFdmModule _Module;

#ifndef LONG_PTR
#define LONG_PTR		LONG
#define DWORD_PTR		DWORD
#endif

#define MY_MAX_PATH		10000

#include <assert.h>

#pragma warning (push, 3)
#include <vector>
#include <list>
#include <string>
#include <xlocale>
#include <algorithm>
#pragma warning (pop)

#include "tstring.h"

#define delta(a,b) (((a) > (b)) ? ((a)-(b)) : ((b)-(a)))

#include "vmsCriticalSection.h"
#include "vmsReaderWriterLock.h"
#include "vmsObject.h"

//{{AFX_INSERT_LOCATION}}

#include "vmsSourceCodeLogger.h"
#include "fsPluginMgr.h"
#include "../inetfile/inetfile.h"

//#include "vmsMediaConvertMgr.h"

#include "fsDownload.h"
#include "vmsPersistObject.h"

#include "vmsFdmAppMgr.h"
#include "fsAppSettings.h"
#include "common.h"
#include "system.h"
#include <limits.h>
#include "fsTrayIconMgr.h"
#include "fsDialogsMgr.h"
#include "fsClipboardMgr.h"
#include "ToolBarEx.h"
//#include "fsUpdateMgr.h"
#include "fsAutorunMgr.h"
#include "fsCmdHistoryMgr.h"
#include <exdispid.h>
#include <htmlhelp.h>
#include "fsContextHelpMgr.h"
#include "fsMFCLangMgr.h"
#include "fsSitesMgr.h"
#include "fsSoundsMgr.h"
#include "fsHistoriesMgr.h"
#include "vmsSkinMgr.h"
#include "vmsDownloadsGroupsMgr.h"
#include "fsDownloadsMgr.h"
#include "vmsTheme.h"
#include "fsPluginMgr.h"
//#include "zlib/zlib.h"
//#include "vmsZip.h"
//#include "vmsUnZip.h"

#include "vmsHttpServer.h"
#include "vmsFdmWebInterfaceServer.h"

#include "../resource.h"

#define SBMP(id) _SkinMgr.bmp (id)
#define SICO(id) _SkinMgr.icon (id)
#define SICOEX(id,cx,cy) _SkinMgr.icon(id,cx,cy)

extern fsAppSettings _App;
extern fsPluginMgr _PluginMgr;
extern fsTrayIconMgr _TrayMgr;
extern fsDialogsMgr _DlgMgr;
extern fsClipboardMgr _ClipbrdMgr;
extern CToolBarEx _TBMgr;
extern fsAutorunMgr _AutorunMgr;

extern fsCmdHistoryMgr _LastUrlFiles;
extern fsCmdHistoryMgr _LastUrlPaths;
extern fsCmdHistoryMgr _LastBatchUrls;
extern fsCmdHistoryMgr _LastFolders;
extern fsCmdHistoryMgr _LastFind;

extern fsContextHelpMgr _CHMgr;
extern fsMFCLangMgr _LngMgr;
extern fsSitesMgr _SitesMgr;
extern fsSoundsMgr _Snds;

extern vmsSkinMgr _SkinMgr;
extern fsDownloadsMgr _DldsMgr;
extern vmsTheme _theme;
extern vmsDownloadsGroupsMgr _DldsGrps;
extern FILETIME _timeAppHasStarted;
extern vmsFdmAppMgr _AppMgr;

extern vmsHttpServer _httpServer;

#define APPSTATE_PORTABLE_MODE					1
#define APPSTATE_PORTABLE_MODE_NOREG			2

extern DWORD _dwAppState;
//#ifndef _DEBUG
//#define IS_PORTABLE_MODE	((_dwAppState & APPSTATE_PORTABLE_MODE) != 0)
//#else
//#define IS_PORTABLE_MODE	FALSE
//#endif

#define IS_PORTABLE_MODE	TRUE

#include "lngphrases.h"

#define TRAY_ICON_NORMAL		0
#define TRAY_ICON_DOWNLOADING	1
#define TRAY_ICON_ERRORS		2
#define TRAY_ICON_UNKNOWN		3

#endif
