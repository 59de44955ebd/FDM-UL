/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "stdafx.h"

SCL_INITOBJECT (_T ("fdm"), 0);

fsAppSettings _App;
fsTrayIconMgr _TrayMgr;
fsDialogsMgr _DlgMgr;
fsClipboardMgr _ClipbrdMgr;
CToolBarEx _TBMgr;
fsAutorunMgr _AutorunMgr;

fsCmdHistoryMgr _LastUrlFiles;
fsCmdHistoryMgr _LastUrlPaths;
fsCmdHistoryMgr _LastBatchUrls;
fsCmdHistoryMgr _LastFolders;
fsCmdHistoryMgr _LastFind;

fsContextHelpMgr _CHMgr;
fsMFCLangMgr _LngMgr;
fsSitesMgr _SitesMgr;
fsSoundsMgr _Snds;

vmsSkinMgr _SkinMgr;
fsDownloadsMgr _DldsMgr;
vmsTheme _theme;
vmsDownloadsGroupsMgr _DldsGrps;
FILETIME _timeAppHasStarted;
fsPluginMgr _PluginMgr;
vmsFdmAppMgr _AppMgr;

vmsFdmWebInterfaceServer _fdmServer;
vmsHttpServer _httpServer(&_fdmServer);

DWORD _dwAppState = 0;

#ifdef _ATL_STATIC_REGISTRY
#include <statreg.h>
#endif

