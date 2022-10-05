#ifndef __LNGPHRASES_H_
#define __LNGPHRASES_H_

enum LangPhrase
{
	L_SAVEALL,
	L_CUT,
	L_COPY,
	L_PASTE,
	L_LIGHT,
	L_MEDIUM,
	L_HEAVY,
	L_DLDR_OPTIONS,
	L_ABOUT,
	L_EXIT,
	L_FILE,
	L_VIEW,
	L_OPTIONS,
	L_TOOLS,
	L_HELP,
	L_TOOLBAR,
	L_STATUSBAR,
	L_DLDDEFOPT,
	L_PRGGENSET,
	L_TURNOFFWD,
	L_SWITCHTO,
	L_TUM,
	L_DOWNLOADS,
	L_SCHEDULER,
	L_SITESMGR,
	L_NEWDLD,
	L_STARTDLDS,
	L_STOPDLDS,
	L_SCHEDULEDLDS,
	L_NEWTASK,
	L_TASKPROP,
	L_STOP,
	L_ADDSITE,
	L_SITEPROP,
	L_DLGROUPS,
	L_DLINFO,
	L_SCHEDULERLOG,
	L_NEWDL,
	L_DELETEDLD,
	L_LAUNCHFILE,
	L_OPENFOLDER,
	L_AUTOSTARTDLD,
	L_DLDPROP,
	L_ENABLETASK,
	L_DISABLETASK,
	L_DELETETASK,
	L_DOWNLOAD,
	L_DELETESITE,
	L_TEMPENTRY,
	L_SITES,
	L_SHOWMAINWND,
	L_STARTALLDLDS,
	L_STOPALLDLDS,
	L_CANCEL,
	L_ALLGROUPS,
	L_FILTERS,
	L_COMPLETED,
	L_INPROGRESS,
	L_SCHEDULED,
	L_STOPPED,
	L_OTHER,
	L_CREATEGRP,
	L_DELGRP,
	L_DELETEALLDLDS,
	L_DELSUCCDLDS,
	L_OPENGRPFOLDER,
	L_GRPPROP,
	L_GRPNAME,
	L_GRPFOLDER,
	L_GRPEXTS,
	L_GRPDEFPRIOR,
	L_LOW,
	L_ENTERGRPNAME,
	L_INPERR,
	L_ENTERFLRNAME,
	L_CHOOSEGRPFLDR,
	L_ENTERGRPNAMEHERE,
	L_FOLDERINWHICH,
	L_BROWSEFOR,
	L_GRPFILESEXTS,
	L_DONTACCEPTCHANGES,
	L_ACCEPTCHANGES,
	L_ERRLOADGRPS,
	L_ERR,
	L_AREYOUSURE,
	L_THISDELGRPDLDS,
	L_CONFIRMATION,
	L_FILENAME,
	L_SIZE,
	L_DOWNLOADED,
	L_TIMELEFT,
	L_SECTIONS,
	L_SPEED,
	L_COMMENT,
	L_LOG,
	L_PROGRESS,
	L_TIME,
	L_DATE,
	L_INFORMATION,
	L_CLEAR,
	L_AUTOSCROLL,
	L_UNKNETERR,
	L_INVLOGIN,
	L_INVPWD,
	L_SUCCESS,
	L_CANTCONNECT,
	L_NOTFOUND,
	L_CONNWASLOST,
	L_NOTRESPONSE,
	L_NOTRESOLVED,
	L_NORESUME,
	L_PROXYLOGINREQ,
	L_EXTERR,
	L_BADREQ,
	L_UNKSERVERR,
	L_CONNABORTED,
	L_BADURL,
	L_NOINETCONN,
	L_HTTPNOTSUPP,
	L_UNKERR,
	L_LIMITREACHED,
	L_TOTALLIMITREACHED,
	L_PAUSESECS,
	L_SECTION,
	L_STARTED,
	L_DONE,
	L_DLDCOMPLETED,
	L_CONNECTING,
	L_CONNSUCC,
	L_REDIRECTING,
	L_REDIRSUCC,
	L_STARTINGDLD,
	L_DLDSTOPPED,
	L_NEWSECTION,
	L_CANCELED,
	L_RESTARTINGDLD,
	L_OPENINGFILE,
	L_FILENAMETOOLONG,
	L_FILEALREXISTSRENAMING,
	L_RENAMINGTO,
	L_WASDELETED,
	L_REWRITINGIT,
	L_RESUMINGDLD,
	L_ALREXISTS,
	L_FAILEDTOOPEN,
	L_FILESIZEWASCHANGED,
	L_ADJFORNEWSIZE,
	L_CANTREWRITE,
	L_WILLBERENAMED,
	L_CANTRENAMEBACK,
	L_CONNECT,
	L_AUTHORIZATION,
	L_USER,
	L_PASSWORD,
	L_GROUP,
	L_SAVETO,
	L_SAVEAS,
	L_START,
	L_AUTOMATICALLY,
	L_MANUALLY,
	L_SCHEDULE,
	L_ADVANCED,
	L_ADDROFFILE,
	L_USERHERE,
	L_PWDHERE,
	L_LOGINHERE,
	L_GROUPHERE,
	L_DLDFOLDERHERE,
	L_SAVEASHERE,
	L_DLDSHORTDESC,
	L_STARTNOWHERE,
	L_MANUALLYSTARTHERE,
	L_SCHEDULESTARTHERE,
	L_SETTIMEHERE,
	L_ADVANCEDHERE,
	L_CHECKURL,
	L_ENTERUSER,
	L_CHOOSEOUTFOLDER,
	L_GENERAL,
	L_GENERALINFO,
	L_SAVEDAS,
	L_SAVEDASHERE,
	L_CANTCHANGEFILENAME,
	L_CANTRENAME,
	L_FILENOTFOUND,
	L_PATHNOTFOUND,
	L_BADEXE,
	L_FILEINUSE,
	L_ACCDENIED,
	L_DEVNOTREADY,
	L_DISKFULL,
	L_BADFILENAME,
	L_LOGINREQ,
	L_CONNECTION,
	L_NETWORK,
	L_ERRS,
	L_PAUSEBETWEEN,
	L_MAXATTEMPTS,
	L_TIMEOUTINSEC,
	L_MINSIZE,
	L_MAXCOUNT,
	L_NETUSAGERESTR,
	L_LIMITTRAFF,
	L_IGNOREALLRESTR,
	L_B,
	L_KB,
	L_MB,
	L_S,
	L_ENTERGREATER,
	L_ENTERDIM,
	L_PAUSEBETWEENHERE,
	L_MAXATTEMPTSHERE,
	L_TIMEOUTHERE,
	L_MINSECTSIZEHERE,
	L_MAXSECTHERE,
	L_TRAFFLIMITHERE,
	L_IGNOREALLHERE,
	L_DIMHERE,
	L_PROTOCOL,
	L_IDAS,
	L_REFERER,
	L_USEHTTP11,
	L_USECOOKIE,
	L_USEPASSIVEMODE,
	L_TRANSFERMODE,
	L_BINARY,
	L_ASCIIFOR,
	L_IDASHERE,
	L_REFERERHERE,
	L_USEHTTP11HERE,
	L_USECOOKIEHERE,
	L_USEPASSIVEMODEHERE,
	L_BINARYHERE,
	L_ASCIIHERE,
	L_ASCIIFORHERE,
	L_PROXY,
	L_GETFROM,
	L_FROMMANUALLY,
	L_FROMDONTUSE,
	L_SETTINGS,
	L_ADDR,
	L_PORT,
	L_ENTERPROXY,
	L_ENTERPROXYPORT,
	L_FROMMANUALHERE,
	L_FROMDONTUSEHERE,
	L_PROTOCOLHERE,
	L_PROXYADDRHERE,
	L_PROXYPORTHERE,
	L_PROXYLOGINHERE,
	L_MISC,
	L_LOCALFILE,
	L_IFEXISTS,
	L_RESERVESPACE,
	L_ADDEXT,
	L_INETSERV,
	L_DONTRESTARTIFNORESUME,
	L_IFSIZECHANGED,
	L_STOPONERRS,
	L_ASK,
	L_REWRITE,
	L_RENAME,
	L_RESUME,
	L_RESTART,
	L_ADJUST,
	L_ENTEREXT,
	L_IFEXISTSHERE,
	L_RESERVESPACEHERE,
	L_ADDEXTHERE,
	L_DONTRESTARTHERE,
	L_IFSIZECHANGEDHERE,
	L_FILENOTFOUNDHERE,
	L_ACCDENIEDHERE,
	L_MAXCOUNTOFCONNS,
	L_MAXCOUNTOFCONNSPERSERV,
	L_TUR,
	L_MAXCONNSHERE,
	L_ALLDLDS,
	L_LISTOFDLDS,
	L_AUTOSAVE,
	L_MIN,
	L_WHENDEL,
	L_AUTODEL,
	L_DONTDELFILE,
	L_DELFILE,
	L_STARTUP,
	L_AUTOSTART,
	L_STARTMINIMIZED,
	L_SYSTEM,
	L_MINTOTRAY,
	L_CLOSEASMINIMIZE,
	L_WTS,
	L_HTS,
	L_NEXTSTART,
	L_LASTSTART,
	L_CANTLOADSCHEDULERLOG,
	L_STARTIT,
	L_CHANGINGTUM,
	L_CHANGETUMTO,
	L_SHUTDOWN,
	L_RESTARTCOMP,
	L_LOGOFF,
	L_ONCE,
	L_SUN,
	L_MON,
	L_TUE,
	L_WED,
	L_THU,
	L_FRI,
	L_SAT,
	L_ONDAYS,
	L_EVERY,
	L_DAYS,
	L_HOURS,
	L_ATSTARTUP,
	L_WHENNOACTIVEDLDS,
	L_WHENSPEEDLESS,
	L_WHENALLDLDSINERR,
	L_NEVER,
	L_UNKNOWN,
	L_LAUNCHEDSUCC,
	L_OUTOFMEMORY,
	L_CANTLAUNCH,
	L_SCHEDULERESTOEXIT,
	L_PRGNAME,
	L_ARGS,
	L_SHUTDOWNTYPE,
	L_FORCEAPPS,
	L_LAUNCHPRG,
	L_CHANGETUM,
	L_EXITFROM,
	L_SHUTDOWNCOMP,
	L_DLDSTOSTART,
	L_DLDSTOSTOP,
	L_APPS,
	L_ALLFILES,
	L_AVAILON2000,
	L_ENTERPRGNAME,
	L_ENTERDLDS,
	L_SETTUMHERE,
	L_SELDLDSHERE,
	L_ALLDLDSHERE,
	L_TOSELHERE,
	L_TOUNSELHERE,
	L_PROGNAMEHERE,
	L_CHOOSEPROGHERE,
	L_ARGSHERE,
	L_TYPEHERE,
	L_FORCEEXITHERE,
	L_WTSHERE,
	L_INCERTAINDAYS,
	L_SUNDAY,
	L_MONDAY,
	L_TUESDAY,
	L_WEDNESDAY,
	L_THURSDAY,
	L_FRIDAY,
	L_SATURDAY,
	L_ONEVENT,
	L_DURING,
	L_LOWSPEED,
	L_MIN_SMALL,
	L_B_MINUTES,
	L_B_HOURS,
	L_B_DAYS,
	L_WHENSPEEDSMALL,
	L_WHENALLDLDSINERRSTATE,
	L_ENTERDAYS,
	L_STARTTIMEHERE,
	L_TIMEHERE,
	L_ONCEHERE,
	L_DATEHERE,
	L_DAILYHERE,
	L_SUNHERE,
	L_MONHERE,
	L_TUEHERE,
	L_WEDHERE,
	L_THUHERE,
	L_FRIHERE,
	L_SATHERE,
	L_ONEVERYHERE,
	L_EVERYDIMHERE,
	L_ONEVENTHERE,
	L_EVENTHERE,
	L_DURINGHERE,
	L_LOWSPEEDHERE,
	L_CONFIRMREQ,
	L_WAITFORCONFIRM,
	L_SECS,
	L_USECONFIRMHERE,
	L_WAITFORCONFIRMHERE,
	L_SITENAME,
	L_CONNS,
	L_LOGIN,
	L_GROUP2,
	L_MAXSITECONNS,
	L_USEDEFGRP,
	L_USESITEFTPPASSIVE,
	L_ENTERSITE,
	L_SITEALREXISTS,
	L_MAXCONNSMUST,
	L_ENTERGRP,
	L_SITEHERE,
	L_MAXCONNSHERE2,
	L_USEDEFGRPHERE,
	L_ASKUSER,
	L_DONTASKAGAIN,
	L_WRITEERR,
	L_FILEEXISTSWHATTODO,
	L_DONTASKAGAINHERE,
	L_REWRITEHERE,
	L_RENAMEHERE,
	L_RESUMEHERE,
	L_STOPHERE,
	L_YES,
	L_NO,
	L_DOWNLOAD2,
	L_WBDELETED,
	L_LOGINREQENTERLOGIN,
	L_LOGINTO,
	L_SENDLOGIN,
	L_DONTCONNECTTOSERV,
	L_SIZECHANGEDWTD,
	L_RESTARTHERE,
	L_ADJUSTHERE,
	L_PLEASEWAIT,
	L_DOWNLOADING,
	L_CREATEDLDS,
	L_SELECTCONTENT,
	L_UNSELECTCONTENT,
	L_LISTOFDLDSHERE,
	L_SELFOLDERHERE,
	L_UNSELFOLDERHERE,
	L_ABOUT2,
	L_STARTDL,
	L_STOPDL,
	L_SCHEDULEDL,
	L_DELETE,
	L_FILES,
	L_SAVEDIN,
	L_EXPORTSETTINGS,
	L_NORESUMERESTARTING,
	L_ERROPENURL,
	L_DETECTACTIVITY,
	L_DECBYLEVEL,
	L_SETTOLIGHT,
	L_VALIDFOR,
	L_VALIDFORSUBDOMAINS,
	L_VALIDHTTPHERE,
	L_VALIDHTTPSHERE,
	L_VALIDFTPHERE,
	L_VALIDSUBDOMAINSHERE,
	L_ENTERATLEAST1PROTOCOL,
	L_MAXDLDS,
	L_RESTARTDL,
	L_ADDONEMORESECT,
	L_DELSECTION,
	L_SHESTOPPED,
	L_QUERYSIZE,
	L_QUERINGSIZE,
	L_QUERYSIZEHERE,
	L_YESTOALL,
	L_NOTOALL,
	L_DETAILEDLOG,
	L_BROWSERRESTARTREQ,
	L_LISTOFTASKS,
	L_LISTOFSITES,
	L_DELETINGDLDS,
	L_CREATEBATCHDLD,
	L_DLGFROM,
	L_DLGTO,
	L_DLGSTEP,
	L_DLGWILDBYTES,
	L_SEERESULTS,
	L_DLGSAMPLE,
	L_FROMHERE,
	L_TOHERE,
	L_STEPHERE,
	L_WILDBYTESHERE,
	L_SEERESULTSHERE,
	L_TOMBGTFROM,
	L_USEBDS,
	L_CREATEEXT,
	L_CREATEEXTHERE,
	L_SHOWSIZESINBYTES,
	L_DISAFTEREXEC,
	L_DELAFTEREXEC,
	L_DISSCHEDHERE,
	L_DELSCHEDHERE,
	L_FILEAUTO,
	L_FILEAUTOHERE,
	L_QUERYBATCHSIZEHERE,
	L_DLDALREXISTS,
	L_LAUNCH,
	L_LAUNCHHERE,
	L_VERSION,
	L_STARTING,
	L_ACTIVEDLDS,
	L_THEREARENOACTDLDS,
	L_NOTIFICATIONS,
	L_USEBALLOONS,
	L_TIMEOUT,
	L_WAITING,
	L_ENTERMIRRURL,
	L_FILESIZEEXCEEDS2GB,
	L_NEWDOWNLOAD,
	L_GROUPBYEXT,
	L_CUSTOMIZE,
	L_USESOUNDS,
	L_CUSTOMIZESOUNDS,
	L_SETSOUND,
	L_REMOVE,
	L_TEST,
	L_SNDEVENTSHERE,
	L_DLADDEDHERE,
	L_DLCOMPLETEDHERE,
	L_DLFAILEDHERE,
	L_SETSOUNDHERE,
	L_REMOVESOUNDHERE,
	L_TESTSOUNDHERE,
	L_EVENT,
	L_SOUND,
	L_NOSOUND,
	L_DOWNLOADADDED,
	L_DOWNLOADCOMPLETE,
	L_DOWNLOADFAILED,
	L_SOUNDFILES,
	L_FAILED,
	L_CLEARHISTORY,
	L_IMPORT,
	L_EXPORT,
	L_IMPORTLISTOFDLDS,
	L_EXPORTLISTOFDLDS,
	L_CANTOPENFILE,
	L_EXPALLDLDS,
	L_EXPDLDSINLIST,
	L_EXPSELDLDS,
	L_DONTEXPCOMPLDLDS,
	L_APPENDIFFILEEXISTS,
	L_INVALIDGROUPNAME,
	L_EXITWHENDONE,
	L_ADDED,
	L_DELETED,
	L_PROPERTIES,
	L_CLEARDELETED,
	L_DONTUSEDELETED,
	L_MAXDELETED,
	L_DOWNLOADS_,
	L_BYPASSCOMPLETED,
	L_CONFIRMDLDELETION,
	L_DELETEDPROPERTIES,
	L_DONTUSEDELETEDHERE,
	L_MAXDELETEDHERE,
	L_MAXDELETEDVALHERE,
	L_BYPASSCOMPLETEDHERE,
	L_CONFIRMDLDDELETIONHERE,
	L_RESTORE,
	L_RESTORINGDLDS,
	L_CLEARHISTORY2,
	L_FIND,
	L_FINDNEXT,
	L_FINDWHAT,
	L_SEARCHIN,
	L_LOCFILENAME,
	L_FINDWHATHERE,
	L_SEARCHIN_FILENAMEHERE,
	L_SEARCHIN_URLHERE,
	L_SEARCHIN_COMMENTHERE,
	L_SEARCHIN_LOCALFILENAMEHERE,
	L_SEARCHADVANCEDHERE,
	L_FINDWHERE,
	L_FINDINLISTOFDLDS,
	L_SETTIME,
	L_FINDINDELETED,
	L_FINDUSESIZE,
	L_MAXIMAL,
	L_MINIMAL,
	L_FINDLISTOFDLDSHERE,
	L_FINDDELETEDHERE,
	L_FINDUSESIZEHERE,
	L_FINDMINSIZEHERE,
	L_FINDMAXSIZEHERE,
	L_FINDINGROUP,
	L_FINDINGROUPHERE,
	L_SEARCHISPERFORMED,
	L_THEREISNOITEMS,
	L_THEREISNOMOREITEMS,
	L_FINDDONE,
	L_PAUSE,
	L_FILTER,
	L_USEHIDDENATTRIB,
	L_APPENDCOMMENT,
	L_STARTDLDAUTOMATICALLY,
	L_ADD,
	L_USEROLLBACK,
	L_ROLLBACKSIZE,
	L_BYTES,
	L_USEROLLBACKHERE,
	L_ROLLBACKSIZEHERE,
	L_RBTOOLARGE,
	L_DONTCHECKAGAIN,
	L_DOUBTFULRANGESRESPONSE,
	L_COPYTOCB,
	L_NOACTIVEDOWNLOADS,
	L_NOACTIVEDOWNLOADSSNDHERE,
	L_IMPORTURLSFROMCLIPBOARD,
	L_PASSWORDS,
	L_OPTIONS_SM,
	L_SAVEPASSWORD,
	L_SAVEPASSWORD_0,
	L_SAVEPASSWORD_1,
	L_DONTSUGGESTTOSAVEPWDS,
	L_USESMTOSTOREPWDS,
	L_ASKMETOSAVEPWDS,
	L_DONTASKMETOSAVEPWDS,
	L_DELPWDSBEFOREEXIT,
	L_DELETEALLPWDS,
	L_NEWSTYLE,
	L_OLDSTYLE,
	L_INVALIDDIRNAME,
	L_WASSCHEDULEDTOLAUNCH,
	L_DOYOUWANTTOLAUNCHIT,
	L_LAUNCHWHENDONE,
	L_USEBDS2,
	L_HIBERNATE,
	L_STANDBY,
	L_SAVEFILE,
	L_OPENFILE,
	L_SAVEFILEANDOPENIT,
	L_DLDTYPE,
	L_DONTSHOWTHISWINDOWAGAIN,
	L_HIDE,
	L_TUMCHANGED,
	L_TUMCHANGED_TOP,
	L_TUM_HEAVY_DESC,
	L_TUM_MEDIUM_DESC,
	L_TUM_LIGHT_DESC,
	L_RENAMEATRESTARTALSO,
	L_URLLISTFILES,
	L_DLINFOLISTFILES,
	L_EXPORTOPTIONS,
	L_RETRDATEFROMSERVER,
	L_RETRDATEFROMSERVER_HERE,
	L_GENERATEDESCFILE,
	L_GENERATEDESCFILE_HERE,
	L_THISFILEWASDLDEDFROM,
	L_DONTRETRFILEDATEFROMSERV,
	L_DONTRETRFILEDATEFROMSERV_HERE,
	L_DONTSAVELOGS,
	L_SAVEDINFILE,
	L_FILESIZE,
	L_RESUMESUPPORT,
	L_CLOSEWINDOWWHENDONE,
	L_OPEN,
	L_YESIWANTTOSEE,
	L_NOIDONTWANTTOSEE,
	L_YESBUTNOFORTHISDLD,
	L_DLDWBDELETEDFROMDISK,
	L_CHOOSEGROUP,
	L_SETGRPROOTFOLDER,
	L_SELECTGRPSROOTFLDR,
	L_PAUSEALLDOWNLOADS,
	L_SHOWDLDDLG,
	L_TOUTSFORCONFS,
	L_LAUNCHDLD,
	L_ASKFORST,
	L_DONTASKFORCONF,
	L_N_SECONDS,
	L_DISABLECONFTIMEOUT,
	L_TYPE,
	L_IGNORE,
	L_SETOFNUMBERS,
	L_ASSIGN,
	L_SETOFNUMBERS_HERE,
	L_ASSIGNSETOFNUMBERS_HERE,
	L_SINGLENUMBER,
	L_NUMBER,
	L_ASSIGNSETOFNUMBERS,
	L_SYNTAXERROR,
	L_DISABLEWHENDONEAFTEREXEC,
	L_MOVEUP,
	L_MOVEDOWN,
	L_MOVEDLDUP,
	L_MOVEDLDDOWN,
	L_CHECKFILEINTEGRITY,
	L_CHECKINTEGRITY_INFOMSG,
	L_ALGORITHM,
	L_CHECKSUM,
	L_PASTEFROMCLIPBOARD,
	L_CHECK,
	L_CALCULATINGCHECKSUM,
	L_CFI_SUCCEEDED,
	L_CFI_FAILED,
	L_CFI_RESULTMSG_OK,
	L_CFI_RESULTMSG_ERR,
	L_CFI_NEVERSHOWIFOK,
	L_FILESIZESARENOTEQUAL,
	L_DLG_SAVE_AS_TEMPLATE,
	L_INVALID_SAVE_AS_TEMPLATE,
	L_WHENDONE,
	L_WHENDONE_2,
	L_WHATISTHIS,
	L_CLOSE,
	L_USEWRITECACHE,
	L_MOVEDLDFILETOFOLDER,
	L_SPEEDISTOOLOW,
	L_RESTARTATLOWSPEED,
	L_RESTARTATLOWSPEED_HERE,
	L_DOYOUWANTTOSEEDLPROGRESSWNDAGAIN,
	L_MOVETOP,
	L_MOVEBOTTOM,
	L_PLACEDLDATTOP,
	L_PLACEDLDATTOPHERE,
	L_ENABLE,
	L_DISABLE,
	L_SWITCH,
	L_RAD_INVERT_HERE,
	L_DISABLENOTIFICATIONSFORBATCHDLDS,
	L_INTEGRITY,
	L_PERFORMINTEGRITYCHECK,
	L_PERFORMINTEGRITYCHECKWHENDONE_HERE,
	L_IFCHECKFAILED,
	L_CHECKSUMOFTHISFILE,
	L_DONOTHING,
	L_ICFR_HERE,
	L_PERFORMINGINTEGRITYCHECK,
	L_INTEGRITYCHECKSUCCEEDED,
	L_INTEGRITYCHECKFAILED,
	L_SPECIFYINTEGRITYALGORITHM,
	L_VALIDCHECKSUM,
	L_RESULTCHECKSUM,
	L_MACROSES,
	L_SERVER_MACROS_DESC,
	L_PATHONSERVER_MACROS_DESC,
	L_YEAR_MACROS_DESC,
	L_MONTH_MACROS_DESC,
	L_DAY_MACROS_DESC,
	L_DATE_MACROS_DESC,
	L_SCHEDULE_START,
	L_SCHEDULE_STOP,
	L_SCHEDULE_DLDSTART,
	L_SCHEDULE_DLDSTOP,
	L_TASKS,
	L_PARENT_GROUP,
	L_SETASDEFFORALLGROUPS,
	L_OKTOSETFOLDERASDEFFORGRP,
	L_DELDEADDLDS,
	L_FOLDER,
	L_TO,
	L_NAME,
	L_METALINK_DETECTED,
	L_BT_TRACKER_ANNOUNCE,
	L_GRANTBANDWIDTHFORDLD,
	L_INVFILENAME,
	L_INVFOLDERNAME,
	L_DLDSHOWPROGRESSDLG,
	L_ALWAYSUSETHISGRP,
	L_ALWAYSUSESAMEGRPANDAUTOUPDATEOUTFOLDER,
	L_PREP_FILES_ONDISK,
	L_STATE,
	L_PREP_FILES_ONDISK_SHORT,
	L_GRPFORNEWDLD,
	L_UPLOAD_SPEED,
	L_AREYOUSURE_WILLSTARTFROM0,
	L_TOTAL_SPEED_SBTEXT,
	L_UPLOAD,
	L_CONSIDER_DLD_AS_MAL_IF_MIN_0,
	L_CONSIDER_DLD_AS_MAL_IF_MIN_1,
	L_STARTDRIVELETTER,
	L_ALLGRPSFLDRSWBCHANGEDTOTHISFLDR,
	L_SETDEFDLDFLDR,
	L_PREVENT_STANDBY_WHILE_DLDING,
	L_SOURCE,
	L_SAVE,
	L_PAUSEALLDLDSMODE_ON_MSG,
	L_CHECKDLDWITHSAMEURLEXISTS,
	L_BTDLD_DEFSTGS,
	L_RESTARTCOMPLDLDS,
	L_TIME_LIMIT,
	L_HR,
	L_LIMITSTARTDLDSTIME,
	L_ALLOWSTARTONLYFROM,
	L_ESSENTIAL,
	L_USE_ONDONE_WNDS,
	L_SET_TIMEOUT_FOR_ONDONE_WNDS,
	L_ERROR,
	L_SHOWTIPS,
	L_NODLDSTOEXPORT,
	L_AFTERSILENTCREATION,
	L_PERC_DOWNLOADED_INTOTAL,
	L_LEFT_TO_DOWNLOAD_AT,
	L_PATHTOPROFILE,
	L_SYS_DIAGNOSTICS_FMT,
	L_ERROR_LOADING_DOWNLOADS__CANCEL_TO_EXIT,
	L_ELREQ_APPLYSETTINGS,
	L_DETERMINE_AUTOMATICALLY,
	L_CHOOSE__GOESDLG,
	L_CONNECTION_SPEED,
	L_STGS_FOR_TUMS,
	L_PERCOFCONNSPEED,
	L_MANAGE_AUTOMATICALLY,
	L_SETTO,
	L_CONNECTIONSPEEDINFO_MSG,
	L_DOWNLOADSPEED,
	L_MEASURE_AGAIN,
	L_SPECIFY_VALUE,
	L_VALUE_MUSTBE_SOME_NUMBER_GREATER_OR_EQUAL_TO_ZERO,
	L_SPECIFY_IN_BITS_INSTEAD_OF_BYTES,
	L_WEBINTERFACE
};

#endif