from ctypes import windll, create_string_buffer, cast, byref, Structure
from ctypes.wintypes import LPCWSTR, LPARAM, DWORD, LPVOID, HWND, UINT

user32 = windll.user32
user32.FindWindowW.argtypes = (LPCWSTR , LPCWSTR)
user32.FindWindowW.restype = HWND
user32.SendMessageW.argtypes = (HWND, UINT, LPVOID, LPVOID)

WM_COPYDATA = 74

class COPYDATASTRUCT(Structure):
    _fields_ = [
        ('dwData', LPARAM),
        ('cbData', DWORD),
        ('lpData', LPVOID)
    ]

if __name__ == "__main__":

    # Must be bytes, FDM-UL expects string as char*, not WCHAR*
    DOWNLOAD_URL = b'https://github.com/59de44955ebd/FDM-UL/releases/download/v1.1/FDM-UL.zip'

    hwnd = user32.FindWindowW('FDM-UL Main Window', None)
    if hwnd:

        ds = COPYDATASTRUCT()
        ds.dwData =	1  # add silently, now "Add download" dialog
        ds.cbData =	len(DOWNLOAD_URL) + 1
        ds.lpData =	cast(create_string_buffer(DOWNLOAD_URL), LPVOID)
        user32.SendMessageW(hwnd, WM_COPYDATA, 0, byref(ds))

    else:
        print('ERROR: No running instance of FDM-UL found!')
