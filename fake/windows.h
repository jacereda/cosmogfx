#define ZeroMemory(Destination, Length) memset((Destination), 0, (Length))
/* #define HDC uint64_t */
/* #define HGLRC uint64_t */

#define WNDCLASS struct NtWndClass

#define MSG struct NtMsg

#define LOWORD(l) ((WORD)(((DWORD_PTR)(l)) & 0xffff))
#define HIWORD(l) ((WORD)((((DWORD_PTR)(l)) >> 16) & 0xffff))
#define CALLBACK

#define __MSABI_LONG(x) x

#define WINUSERAPI
#define WINAPI
#define WINGDIAPI

#define MAKEINTRESOURCE(i) ((LPWSTR)((ULONG_PTR)((WORD)(i))))

#define MAPVK_VK_TO_VSC_EX (4)

#define CS_OWNDC 0x0020

#define CP_UTF8 65001

#define PFD_MAIN_PLANE 0
#define PFD_TYPE_RGBA 0
#define PFD_DOUBLEBUFFER 0x00000001
#define PFD_DRAW_TO_WINDOW 0x00000004
#define PFD_SUPPORT_OPENGL 0x00000020

#define DIB_RGB_COLORS 0
#define BI_RGB 0
#define IDC_ARROW MAKEINTRESOURCE(32512)
#define GWL_STYLE (-16)

#define WM_PAINT 0x000F
#define WM_SETCURSOR 0x0020
#define WM_MOUSEMOVE 0x0200
#define WM_SIZE 0x0005
#define WM_CLOSE 0x0010
#define WM_KEYDOWN 0x0100
#define WM_KEYUP 0x0101
#define WM_SYSKEYDOWN 0x0104
#define WM_SYSKEYUP 0x0105
#define WM_LBUTTONDOWN 0x0201
#define WM_LBUTTONUP 0x0202
#define WM_MBUTTONDOWN 0x0207
#define WM_MBUTTONUP 0x0208
#define WM_MOUSEWHEEL 0x020A
#define WM_RBUTTONDOWN 0x0204
#define WM_RBUTTONUP 0x0205
#define WM_CHAR 0x0102

#define WS_CLIPSIBLINGS __MSABI_LONG(0x04000000)
#define WS_CLIPCHILDREN __MSABI_LONG(0x02000000)
#define WS_POPUP __MSABI_LONG(0x80000000)
#define WS_OVERLAPPED __MSABI_LONG(0x00000000)
#define WS_CAPTION __MSABI_LONG(0x00C00000)
#define WS_SYSMENU __MSABI_LONG(0x00080000)
#define WS_MINIMIZEBOX __MSABI_LONG(0x00020000)
#define WS_MAXIMIZEBOX __MSABI_LONG(0x00010000)
#define WS_THICKFRAME __MSABI_LONG(0x00040000)
#define WS_EX_APPWINDOW __MSABI_LONG(0x00040000)

#define SW_SHOWNORMAL 1
#define SW_SHOWMAXIMIZED 3

#define SWP_NOSIZE 0x0001
#define SWP_NOMOVE 0x0002
#define SWP_NOZORDER 0x0004
#define SWP_FRAMECHANGED 0x0020
#define SWP_SHOWWINDOW 0x0040

#define HWND_TOPMOST ((HWND)-1)

#define PM_REMOVE 0x0001

#define HANDLE_WM_CLOSE(hwnd, wParam, lParam, fn) ((fn)(hwnd), (LRESULT)0)
#define HANDLE_WM_KEYDOWN(hwnd, wParam, lParam, fn)                     \
	((fn)((hwnd), (UINT)(wParam), TRUE, (int)(short)LOWORD(lParam), \
	     (UINT)HIWORD(lParam)),                                     \
	    (LRESULT)0)
#define HANDLE_WM_KEYUP(hwnd, wParam, lParam, fn)                        \
	((fn)((hwnd), (UINT)(wParam), FALSE, (int)(short)LOWORD(lParam), \
	     (UINT)HIWORD(lParam)),                                      \
	    (LRESULT)0)
#define HANDLE_WM_CHAR(hwnd, wParam, lParam, fn) \
	((fn)((hwnd), (TCHAR)(wParam), (int)(short)LOWORD(lParam)), (LRESULT)0)

#define HANDLE_WM_SIZE(hwnd, wParam, lParam, fn)                  \
	((fn)((hwnd), (UINT)(wParam), (int)(short)LOWORD(lParam), \
	     (int)(short)HIWORD(lParam)),                         \
	    (LRESULT)0)

#define HANDLE_WM_SYSKEYDOWN(hwnd, wParam, lParam, fn)                  \
	((fn)((hwnd), (UINT)(wParam), TRUE, (int)(short)LOWORD(lParam), \
	     (UINT)HIWORD(lParam)),                                     \
	    (LRESULT)0)
#define HANDLE_WM_SYSKEYUP(hwnd, wParam, lParam, fn)                     \
	((fn)((hwnd), (UINT)(wParam), FALSE, (int)(short)LOWORD(lParam), \
	     (UINT)HIWORD(lParam)),                                      \
	    (LRESULT)0)
#define HANDLE_WM_SYSCHAR(hwnd, wParam, lParam, fn) \
	((fn)((hwnd), (TCHAR)(wParam), (int)(short)LOWORD(lParam)), (LRESULT)0)
#define HANDLE_WM_MOUSEMOVE(hwnd, wParam, lParam, fn)                         \
	((fn)((hwnd), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), \
	     (UINT)(wParam)),                                                 \
	    (LRESULT)0)
#define HANDLE_WM_LBUTTONDOWN(hwnd, wParam, lParam, fn)   \
	((fn)((hwnd), FALSE, (int)(short)LOWORD(lParam),  \
	     (int)(short)HIWORD(lParam), (UINT)(wParam)), \
	    (LRESULT)0)
#define HANDLE_WM_LBUTTONUP(hwnd, wParam, lParam, fn)                         \
	((fn)((hwnd), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), \
	     (UINT)(wParam)),                                                 \
	    (LRESULT)0)
#define HANDLE_WM_MBUTTONDOWN(hwnd, wParam, lParam, fn)   \
	((fn)((hwnd), FALSE, (int)(short)LOWORD(lParam),  \
	     (int)(short)HIWORD(lParam), (UINT)(wParam)), \
	    (LRESULT)0)
#define HANDLE_WM_MBUTTONUP(hwnd, wParam, lParam, fn)                         \
	((fn)((hwnd), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), \
	     (UINT)(wParam)),                                                 \
	    (LRESULT)0)
#define HANDLE_WM_RBUTTONDOWN(hwnd, wParam, lParam, fn)   \
	((fn)((hwnd), FALSE, (int)(short)LOWORD(lParam),  \
	     (int)(short)HIWORD(lParam), (UINT)(wParam)), \
	    (LRESULT)0)
#define HANDLE_WM_RBUTTONUP(hwnd, wParam, lParam, fn)                         \
	((fn)((hwnd), (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam), \
	     (UINT)(wParam)),                                                 \
	    (LRESULT)0)
#define HANDLE_WM_SETCURSOR(hwnd, wParam, lParam, fn)         \
	(LRESULT)(DWORD)(WINBOOL)(fn)((hwnd), (HWND)(wParam), \
	    (UINT)LOWORD(lParam), (UINT)HIWORD(lParam))
#define HANDLE_WM_PAINT(hwnd, wParam, lParam, fn) ((fn)(hwnd), (LRESULT)0)

typedef LRESULT(CALLBACK *WNDPROC)(HWND, UINT, WPARAM, LPARAM);

typedef uint32_t __LONG32;

typedef struct _ICONINFO {
	WINBOOL fIcon;
	DWORD	xHotspot;
	DWORD	yHotspot;
	HBITMAP hbmMask;
	HBITMAP hbmColor;
} ICONINFO;
typedef ICONINFO *PICONINFO;

typedef __LONG32 FXPT16DOT16, *LPFXPT16DOT16;
typedef __LONG32 FXPT2DOT30, *LPFXPT2DOT30;

typedef struct tagCIEXYZ {
	FXPT2DOT30 ciexyzX;
	FXPT2DOT30 ciexyzY;
	FXPT2DOT30 ciexyzZ;
} CIEXYZ;

typedef struct tagICEXYZTRIPLE {
	CIEXYZ ciexyzRed;
	CIEXYZ ciexyzGreen;
	CIEXYZ ciexyzBlue;
} CIEXYZTRIPLE;

typedef struct {
	DWORD	     bV5Size;
	LONG	     bV5Width;
	LONG	     bV5Height;
	WORD	     bV5Planes;
	WORD	     bV5BitCount;
	DWORD	     bV5Compression;
	DWORD	     bV5SizeImage;
	LONG	     bV5XPelsPerMeter;
	LONG	     bV5YPelsPerMeter;
	DWORD	     bV5ClrUsed;
	DWORD	     bV5ClrImportant;
	DWORD	     bV5RedMask;
	DWORD	     bV5GreenMask;
	DWORD	     bV5BlueMask;
	DWORD	     bV5AlphaMask;
	DWORD	     bV5CSType;
	CIEXYZTRIPLE bV5Endpoints;
	DWORD	     bV5GammaRed;
	DWORD	     bV5GammaGreen;
	DWORD	     bV5GammaBlue;
	DWORD	     bV5Intent;
	DWORD	     bV5ProfileData;
	DWORD	     bV5ProfileSize;
	DWORD	     bV5Reserved;
} BITMAPV5HEADER, *LPBITMAPV5HEADER, *PBITMAPV5HEADER;

typedef struct tagBITMAPINFOHEADER {
	DWORD biSize;
	LONG  biWidth;
	LONG  biHeight;
	WORD  biPlanes;
	WORD  biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG  biXPelsPerMeter;
	LONG  biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
} BITMAPINFOHEADER, *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;

typedef struct tagRGBQUAD {
	BYTE rgbBlue;
	BYTE rgbGreen;
	BYTE rgbRed;
	BYTE rgbReserved;
} RGBQUAD;

typedef struct tagBITMAPINFO {
	BITMAPINFOHEADER bmiHeader;
	RGBQUAD		 bmiColors[1];
} BITMAPINFO, *LPBITMAPINFO, *PBITMAPINFO;

typedef struct tagPIXELFORMATDESCRIPTOR {
	WORD  nSize;
	WORD  nVersion;
	DWORD dwFlags;
	BYTE  iPixelType;
	BYTE  cColorBits;
	BYTE  cRedBits;
	BYTE  cRedShift;
	BYTE  cGreenBits;
	BYTE  cGreenShift;
	BYTE  cBlueBits;
	BYTE  cBlueShift;
	BYTE  cAlphaBits;
	BYTE  cAlphaShift;
	BYTE  cAccumBits;
	BYTE  cAccumRedBits;
	BYTE  cAccumGreenBits;
	BYTE  cAccumBlueBits;
	BYTE  cAccumAlphaBits;
	BYTE  cDepthBits;
	BYTE  cStencilBits;
	BYTE  cAuxBuffers;
	BYTE  iLayerType;
	BYTE  bReserved;
	DWORD dwLayerMask;
	DWORD dwVisibleMask;
	DWORD dwDamageMask;
} PIXELFORMATDESCRIPTOR, *PPIXELFORMATDESCRIPTOR, *LPPIXELFORMATDESCRIPTOR;

typedef struct tagPOINT {
	LONG x;
	LONG y;
} POINT, *PPOINT;

typedef struct tagRECT {
	LONG left;
	LONG top;
	LONG right;
	LONG bottom;
} RECT, *PRECT, *NPRECT, *LPRECT;

/* typedef struct tagMSG { */
/* 	HWND   hwnd; */
/* 	UINT   message; */
/* 	WPARAM wParam; */
/* 	LPARAM lParam; */
/* 	DWORD  time; */
/* 	POINT  pt; */
/* } MSG, *PMSG, *NPMSG, *LPMSG; */

typedef struct tagWNDCLASSEXA {
	UINT	  cbSize;
	UINT	  style;
	WNDPROC	  lpfnWndProc;
	int	  cbClsExtra;
	int	  cbWndExtra;
	HINSTANCE hInstance;
	HICON	  hIcon;
	HCURSOR	  hCursor;
	HBRUSH	  hbrBackground;
	LPCSTR	  lpszMenuName;
	LPCSTR	  lpszClassName;
	HICON	  hIconSm;
} WNDCLASSEXA, *PWNDCLASSEXA, *NPWNDCLASSEXA, *LPWNDCLASSEXA;

WINUSERAPI int WINAPI MultiByteToWideChar(UINT CodePage, DWORD dwFlags,
    LPCCH lpMultiByteStr, int cbMultiByte, LPWSTR lpWideCharStr,
    int cchWideChar);

WINUSERAPI WINBOOL WINAPI DestroyIcon(HICON hIcon);

WINUSERAPI HICON WINAPI CreateIconIndirect(PICONINFO piconinfo);

// WINUSERAPI LONG WINAPI SetWindowLongA(HWND hWnd, int nIndex, LONG dwNewLong);
WINUSERAPI LONG WINAPI SetWindowLong(HWND hWnd, int nIndex, LONG dwNewLong);

WINUSERAPI HDC WINAPI GetDC(HWND hWnd);
WINUSERAPI int WINAPI ReleaseDC(HWND hWnd, HDC hDC);

HMODULE LoadLibraryA(LPCSTR lpLibFileName);
/* WINUSERAPI HCURSOR WINAPI LoadCursorW( */
/*     HINSTANCE hInstance, LPCWSTR lpCursorName); */

int32_t PeekMessage(struct NtMsg *lpMsg, int64_t hWnd, uint32_t wMsgFilterMin,
    uint32_t wMsgFilterMax, uint32_t);

// WINUSERAPI WINBOOL WINAPI PeekMessageW(LPMSG lpMsg, HWND hWnd,
//    UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg);
// WINUSERAPI LRESULT WINAPI DispatchMessageW(CONST MSG *lpMsg);
WINUSERAPI WINBOOL WINAPI InvalidateRect(
    HWND hWnd, CONST RECT *lpRect, WINBOOL bErase);
WINUSERAPI WINBOOL WINAPI UpdateWindow(HWND hWnd);
WINUSERAPI WINBOOL WINAPI AdjustWindowRect(
    LPRECT lpRect, DWORD dwStyle, WINBOOL bMenu);
WINUSERAPI UINT WINAPI MapVirtualKeyEx(UINT uCode, UINT uMapType, HKL dwhkl);
WINUSERAPI HKL WINAPI  GetKeyboardLayout(DWORD idThread);

WINGDIAPI HBITMAP WINAPI CreateBitmap(
    int nWidth, int nHeight, UINT nPlanes, UINT nBitCount, CONST VOID *lpBits);
WINGDIAPI HBITMAP WINAPI CreateDIBSection(HDC hdc, CONST BITMAPINFO *lpbmi,
    UINT usage, VOID **ppvBits, HANDLE hSection, DWORD offset);
WINGDIAPI HRGN WINAPI	 CreateRectRgn(int x1, int y1, int x2, int y2);
WINGDIAPI WINBOOL WINAPI SwapBuffers(HDC);
WINGDIAPI WINBOOL WINAPI SetPixelFormat(
    HDC hdc, int format, CONST PIXELFORMATDESCRIPTOR *ppfd);
WINGDIAPI int WINAPI ChoosePixelFormat(
    HDC hdc, CONST PIXELFORMATDESCRIPTOR *ppfd);

#define VK_LBUTTON 0x01
#define VK_RBUTTON 0x02
#define VK_CANCEL 0x03
#define VK_MBUTTON 0x04
#define VK_XBUTTON1 0x05
#define VK_XBUTTON2 0x06
#define VK_BACK 0x08
#define VK_TAB 0x09
#define VK_CLEAR 0x0C
#define VK_RETURN 0x0D
#define VK_SHIFT 0x10
#define VK_CONTROL 0x11
#define VK_MENU 0x12
#define VK_PAUSE 0x13
#define VK_CAPITAL 0x14
#define VK_KANA 0x15
#define VK_HANGEUL 0x15
#define VK_HANGUL 0x15
#define VK_JUNJA 0x17
#define VK_FINAL 0x18
#define VK_HANJA 0x19
#define VK_KANJI 0x19
#define VK_ESCAPE 0x1B
#define VK_CONVERT 0x1C
#define VK_NONCONVERT 0x1D
#define VK_ACCEPT 0x1E
#define VK_MODECHANGE 0x1F
#define VK_SPACE 0x20
#define VK_PRIOR 0x21
#define VK_NEXT 0x22
#define VK_END 0x23
#define VK_HOME 0x24
#define VK_LEFT 0x25
#define VK_UP 0x26
#define VK_RIGHT 0x27
#define VK_DOWN 0x28
#define VK_SELECT 0x29
#define VK_PRINT 0x2A
#define VK_EXECUTE 0x2B
#define VK_SNAPSHOT 0x2C
#define VK_INSERT 0x2D
#define VK_DELETE 0x2E
#define VK_HELP 0x2F

#define VK_LWIN 0x5B
#define VK_RWIN 0x5C
#define VK_APPS 0x5D
#define VK_SLEEP 0x5F
#define VK_NUMPAD0 0x60
#define VK_NUMPAD1 0x61
#define VK_NUMPAD2 0x62
#define VK_NUMPAD3 0x63
#define VK_NUMPAD4 0x64
#define VK_NUMPAD5 0x65
#define VK_NUMPAD6 0x66
#define VK_NUMPAD7 0x67
#define VK_NUMPAD8 0x68
#define VK_NUMPAD9 0x69
#define VK_MULTIPLY 0x6A
#define VK_ADD 0x6B
#define VK_SEPARATOR 0x6C
#define VK_SUBTRACT 0x6D
#define VK_DECIMAL 0x6E
#define VK_DIVIDE 0x6F
#define VK_F1 0x70
#define VK_F2 0x71
#define VK_F3 0x72
#define VK_F4 0x73
#define VK_F5 0x74
#define VK_F6 0x75
#define VK_F7 0x76
#define VK_F8 0x77
#define VK_F9 0x78
#define VK_F10 0x79
#define VK_F11 0x7A
#define VK_F12 0x7B
#define VK_F13 0x7C
#define VK_F14 0x7D
#define VK_F15 0x7E
#define VK_F16 0x7F
#define VK_F17 0x80
#define VK_F18 0x81
#define VK_F19 0x82
#define VK_F20 0x83
#define VK_F21 0x84
#define VK_F22 0x85
#define VK_F23 0x86
#define VK_F24 0x87
#define VK_NUMLOCK 0x90
#define VK_SCROLL 0x91
#define VK_OEM_NEC_EQUAL 0x92
#define VK_OEM_FJ_JISHO 0x92
#define VK_OEM_FJ_MASSHOU 0x93
#define VK_OEM_FJ_TOUROKU 0x94
#define VK_OEM_FJ_LOYA 0x95
#define VK_OEM_FJ_ROYA 0x96
#define VK_LSHIFT 0xA0
#define VK_RSHIFT 0xA1
#define VK_LCONTROL 0xA2
#define VK_RCONTROL 0xA3
#define VK_LMENU 0xA4
#define VK_RMENU 0xA5
#define VK_BROWSER_BACK 0xA6
#define VK_BROWSER_FORWARD 0xA7
#define VK_BROWSER_REFRESH 0xA8
#define VK_BROWSER_STOP 0xA9
#define VK_BROWSER_SEARCH 0xAA
#define VK_BROWSER_FAVORITES 0xAB
#define VK_BROWSER_HOME 0xAC
#define VK_VOLUME_MUTE 0xAD
#define VK_VOLUME_DOWN 0xAE
#define VK_VOLUME_UP 0xAF
#define VK_MEDIA_NEXT_TRACK 0xB0
#define VK_MEDIA_PREV_TRACK 0xB1
#define VK_MEDIA_STOP 0xB2
#define VK_MEDIA_PLAY_PAUSE 0xB3
#define VK_LAUNCH_MAIL 0xB4
#define VK_LAUNCH_MEDIA_SELECT 0xB5
#define VK_LAUNCH_APP1 0xB6
#define VK_LAUNCH_APP2 0xB7
#define VK_OEM_1 0xBA
#define VK_OEM_PLUS 0xBB
#define VK_OEM_COMMA 0xBC
#define VK_OEM_MINUS 0xBD
#define VK_OEM_PERIOD 0xBE
#define VK_OEM_2 0xBF
#define VK_OEM_3 0xC0
#define VK_OEM_4 0xDB
#define VK_OEM_5 0xDC
#define VK_OEM_6 0xDD
#define VK_OEM_7 0xDE
#define VK_OEM_8 0xDF
#define VK_OEM_AX 0xE1
#define VK_OEM_102 0xE2
#define VK_ICO_HELP 0xE3
#define VK_ICO_00 0xE4
#define VK_PROCESSKEY 0xE5
#define VK_ICO_CLEAR 0xE6
#define VK_PACKET 0xE7
#define VK_OEM_RESET 0xE9
#define VK_OEM_JUMP 0xEA
#define VK_OEM_PA1 0xEB
#define VK_OEM_PA2 0xEC
#define VK_OEM_PA3 0xED
#define VK_OEM_WSCTRL 0xEE
#define VK_OEM_CUSEL 0xEF
#define VK_OEM_ATTN 0xF0
#define VK_OEM_FINISH 0xF1
#define VK_OEM_COPY 0xF2
#define VK_OEM_AUTO 0xF3
#define VK_OEM_ENLW 0xF4
#define VK_OEM_BACKTAB 0xF5
#define VK_ATTN 0xF6
#define VK_CRSEL 0xF7
#define VK_EXSEL 0xF8
#define VK_EREOF 0xF9
#define VK_PLAY 0xFA
#define VK_ZOOM 0xFB
#define VK_NONAME 0xFC
#define VK_PA1 0xFD
#define VK_OEM_CLEAR 0xFE

typedef struct _DWM_BLURBEHIND {
	DWORD dwFlags;
	BOOL  fEnable;
	HRGN  hRgnBlur;
	BOOL  fTransitionOnMaximized;
} DWM_BLURBEHIND, *PDWM_BLURBEHIND;

#define DWM_BB_ENABLE 0x00000001
#define DWM_BB_BLURREGION 0x00000002
