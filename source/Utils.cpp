/*
  Free Download Manager Copyright (c) 2003-2014 FreeDownloadManager.ORG
*/

#include "StdAfx.h"
#include "Utils.h"
#include "MemHandleGuard.h"

bool ComErrToSysErrCode(HRESULT hr, DWORD& dwErr)
{
	if ((hr & 0xFFFF0000) == MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, 0))
	{
		dwErr = HRESULT_CODE(hr);
		return true;
	}
	if (hr == S_OK)
	{
		dwErr = HRESULT_CODE(hr);
		return true;
	}
	return false;
}

void FormatMessageByErrCode(CString& sMsg, DWORD dwErr, bool& bFailedToRetreive)
{
	LPVOID lpMsgBuf = 0;
	DWORD dwFlag = FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS;

	CMemHandleGuard mhgMemGuard(lpMsgBuf, bFailedToRetreive);

	if(::FormatMessage(dwFlag, NULL, dwErr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR) &lpMsgBuf, 0, NULL) == 0)
	{
		bFailedToRetreive = true;
		return;
	}

	sMsg = (LPCTSTR)lpMsgBuf;
}

void appendDiagnostics(CString&sMsg, const CString& sDiagnostics)
{
	CString sTmp;
	CString sFmt = LS (L_SYS_DIAGNOSTICS_FMT);
	sTmp.Format((LPCTSTR)sFmt, (LPCTSTR)sDiagnostics);
	sMsg += " ";
	sMsg += sTmp;
}

void putStrToBuffer(LPCTSTR tszStr, LPBYTE& pbtCurrentPos, LPBYTE pbtBuffer, DWORD dwBufferSizeSize, DWORD* pdwSizeReuiqred)
{
	int nLen = -1;
	UINT nBufferSize = 0;
	if (tszStr)
	{
		nLen = _tcslen(tszStr);
		nBufferSize = sizeof(TCHAR) * nLen;
	}

	if (pbtBuffer == NULL)
	{
		if (pdwSizeReuiqred)
		{
			*pdwSizeReuiqred += sizeof(nLen) + nBufferSize;
		}
		return;
	}

	CHECK_BUFFER_BOUNDS(dwBufferSizeSize, sizeof(nLen));
	CopyMemory(pbtCurrentPos, &nLen, sizeof(nLen));
	pbtCurrentPos += sizeof(nLen);

	if (tszStr)
	{
		CHECK_BUFFER_BOUNDS(dwBufferSizeSize, nBufferSize);
		CopyMemory(pbtCurrentPos, tszStr, nBufferSize);
		pbtCurrentPos += nBufferSize;
	}
}

bool getStrFromBuffer(LPTSTR* ptszStr, LPBYTE& pbtCurrentPos, LPBYTE pbtBuffer, DWORD dwBufferSizeSize)
{
	int nLen = 0;
	BOOLEAN_CHECK_BUFFER_BOUNDS(dwBufferSizeSize, sizeof(nLen));
	CopyMemory(&nLen, pbtCurrentPos, sizeof(nLen));
	pbtCurrentPos += sizeof(nLen);

	if (nLen < -1)
		return false;

	if (nLen == -1)
	{
		*ptszStr = 0;
		return true;
	}

	if ((UINT)nLen > 100000)
		return false;

	int nBufferSize = sizeof(TCHAR) * (nLen + 1);

	std::auto_ptr<TCHAR> aptszStrGuard( new TCHAR[nLen + 1] );
	LPTSTR tszTmp = aptszStrGuard.get();
	if (tszTmp == 0)
		return false;
	memset(tszTmp, 0, nBufferSize);

	BOOLEAN_CHECK_BUFFER_BOUNDS(dwBufferSizeSize, (sizeof(TCHAR) * nLen));
	CopyMemory(tszTmp, pbtCurrentPos, sizeof(TCHAR) * nLen);
	pbtCurrentPos += sizeof(TCHAR) * nLen;
	*ptszStr = aptszStrGuard.release();

	return true;
}

//##########################################################
//
//##########################################################
WCHAR *utf8ToUtf16(const char *utf8)
{
	int utf8len = strlen(utf8) + 1;
	int utf16len = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	WCHAR * utf16 = new WCHAR[utf16len + 1];
	MultiByteToWideChar(
		CP_UTF8,	// convert from UTF-8
		0,
		utf8,		// source UTF-8 string
		utf8len,	// total length of source UTF-8 string, in CHAR’s (= bytes), including end-of-string
		utf16,		// destination buffer
		utf16len	// size of destination buffer, in WCHAR’s
	);
	return utf16;
}

//##########################################################
//
//##########################################################
CString execCmd(const CHAR* cmd, LPDWORD lpExitCode)
{
	CString strResult;
	HANDLE hPipeRead, hPipeWrite;

	SECURITY_ATTRIBUTES saAttr = { sizeof(SECURITY_ATTRIBUTES) };
	saAttr.bInheritHandle = TRUE; // Pipe handles are inherited by child process.
	saAttr.lpSecurityDescriptor = NULL;

	// Create a pipe to get results from child's stdout.
	if (!CreatePipe(&hPipeRead, &hPipeWrite, &saAttr, 0))
		return strResult;

	STARTUPINFOA si = { sizeof(STARTUPINFOA) };
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	si.hStdOutput = hPipeWrite;
	si.hStdError = hPipeWrite;
	si.wShowWindow = SW_HIDE;

	PROCESS_INFORMATION pi = { 0 };

	BOOL fSuccess = CreateProcessA(NULL, (LPSTR)cmd, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	if (!fSuccess)
	{
		CloseHandle(hPipeWrite);
		CloseHandle(hPipeRead);
		return strResult;
	}

	bool bProcessEnded = false;
	for (; !bProcessEnded;)
	{
		// Give some timeslice (50 ms), so we won't waste 100% CPU.
		bProcessEnded = WaitForSingleObject(pi.hProcess, 50) == WAIT_OBJECT_0;

		// Even if process exited - we continue reading, if
		// there is some data available over pipe.
		for (;;)
		{
			char buf[1024];
			DWORD dwRead = 0;
			DWORD dwAvail = 0;

			if (!::PeekNamedPipe(hPipeRead, NULL, 0, NULL, &dwAvail, NULL))
				break;

			if (!dwAvail) // No data available, return
				break;

			if (!::ReadFile(hPipeRead, buf, min(sizeof(buf) - 1, dwAvail), &dwRead, NULL) || !dwRead)
				// Error, the child process might ended
				break;

			buf[dwRead] = 0;
			strResult += buf;
		}
	} //for

	GetExitCodeProcess(pi.hProcess, lpExitCode);

	CloseHandle(hPipeWrite);
	CloseHandle(hPipeRead);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	return strResult;
}
