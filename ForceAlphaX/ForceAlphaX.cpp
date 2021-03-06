// ForceAlphaX.cpp: 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "ForceAlphaX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define LIMITED
#pragma warning (disable : 4996)
//
//TODO:  如果此 DLL 相对于 MFC DLL 是动态链接的，
//		则从此 DLL 导出的任何调入
//		MFC 的函数必须将 AFX_MANAGE_STATE 宏添加到
//		该函数的最前面。
//
//		例如: 
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。  这意味着
//		它必须作为以下项中的第一个语句:
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CForceAlphaXApp

BEGIN_MESSAGE_MAP(CForceAlphaXApp, CWinApp)
END_MESSAGE_MAP()
struct On_RGB
{
	unsigned char RED;
	unsigned char GREEN;
	unsigned char BLUE;
	On_RGB(unsigned char r, unsigned g, unsigned char b) :RED(r), GREEN(g), BLUE(b)
	{
		return;
	}
};

// CForceAlphaXApp 构造

CForceAlphaXApp::CForceAlphaXApp()
{
	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CForceAlphaXApp 对象

CForceAlphaXApp theApp;


// CForceAlphaXApp 初始化
HMODULE GetSelfModuleHandle()
{
	MEMORY_BASIC_INFORMATION mbi;

	return ((::VirtualQuery(GetSelfModuleHandle, &mbi, sizeof(mbi)) != 0)
		? (HMODULE)mbi.AllocationBase : NULL);
}

list<HWND> All_Windows;
list<HWND> My_Windows;
BOOL CALLBACK Getted_Windows(HWND thehwnd, LPARAM thelpa)
{
	DWORD lpdwProcessId;
	GetWindowThreadProcessId(thehwnd, &lpdwProcessId);
	if (lpdwProcessId == thelpa)
	{
		All_Windows.push_back(thehwnd);
		//return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK GetAllEx(HWND thehwnd, LPARAM thelpa)
{
	All_Windows.push_back(thehwnd);
	return TRUE;
}
void is_My_Windows(HMODULE MyPcs);


_declspec (dllexport) BOOL __stdcall Window_Alpha(unsigned char byDw, HWND WinH)
{
	typedef BOOL(WINAPI *ColoredEx)(HWND, COLORREF, BYTE, DWORD);
	LONG lWindowStyle = ::GetWindowLong(WinH, GWL_EXSTYLE) | WS_EX_LAYERED;
	::SetWindowLong(WinH, GWL_EXSTYLE, lWindowStyle);
	ColoredEx P_Color = NULL;
	HINSTANCE hInst = LoadLibrary("User32.DLL");
	P_Color = (ColoredEx)GetProcAddress(hInst, "SetLayeredWindowAttributes");
	if (P_Color)P_Color(WinH, 0, byDw, 2);
	FreeLibrary(hInst);
	return TRUE;
}
HWND g_HWND = NULL;
BOOL CALLBACK EnumWindowsProcMy(HWND hwnd, LPARAM lParam)
{
	DWORD lpdwProcessId;
	GetWindowThreadProcessId(hwnd, &lpdwProcessId);
	if (lpdwProcessId == lParam)
	{
		All_Windows.push_back(hwnd);
		g_HWND = hwnd;
	}
	return TRUE;
}

_declspec (dllexport) BOOL __stdcall Window_Alpha(unsigned char byDw, HWND WinH,On_RGB FullColor)
{
	typedef BOOL(WINAPI *ColoredEx)(HWND, COLORREF, BYTE, DWORD);
	LONG lWindowStyle = ::GetWindowLong(WinH, GWL_EXSTYLE) | WS_EX_LAYERED;
	::SetWindowLong(WinH, GWL_EXSTYLE, lWindowStyle);
	ColoredEx P_Color = NULL;
	HINSTANCE hInst = LoadLibrary("User32.DLL");
	P_Color = (ColoredEx)GetProcAddress(hInst, "SetLayeredWindowAttributes");
	if (P_Color)P_Color(WinH, RGB(FullColor.RED, FullColor.GREEN, FullColor.BLUE), byDw, 1);
	FreeLibrary(hInst);
	return TRUE;
}

void is_My_Windows(HMODULE MyPcs);
_declspec (dllexport) BOOL __stdcall Handle_Alpha(unsigned char byDw, HANDLE WinH)
{
	g_HWND = NULL;
	All_Windows.clear();
	My_Windows.clear();
	auto alx = GetProcessId(WinH);
	EnumWindows(EnumWindowsProcMy, alx);
	is_My_Windows(GetSelfModuleHandle());
	if (!g_HWND)return FALSE;
	typedef BOOL(WINAPI *ColoredEx)(HWND, COLORREF, BYTE, DWORD);
	for (auto native_pcs = My_Windows.begin(); native_pcs != My_Windows.end(); native_pcs++)
	{
		LONG lWindowStyle = ::GetWindowLong(*native_pcs, GWL_EXSTYLE) | WS_EX_LAYERED;
		::SetWindowLong(*native_pcs, GWL_EXSTYLE, lWindowStyle);
		ColoredEx P_Color = NULL;
		HINSTANCE hInst = LoadLibrary("User32.DLL");
		P_Color = (ColoredEx)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		if (P_Color)P_Color(*native_pcs, 0, byDw, 2);
		FreeLibrary(hInst);
	}
	return TRUE;
}

_declspec (dllexport) BOOL __stdcall Handle_Alpha(unsigned char byDw, HANDLE WinH,On_RGB FullColor)
{
	g_HWND = NULL;
	All_Windows.clear();
	My_Windows.clear();
	auto alx = GetProcessId(WinH);
	EnumWindows(EnumWindowsProcMy, alx);
	is_My_Windows(GetSelfModuleHandle());
	if (!g_HWND)return FALSE;
	typedef BOOL(WINAPI *ColoredEx)(HWND, COLORREF, BYTE, DWORD);
	for (auto native_pcs = My_Windows.begin(); native_pcs != My_Windows.end(); native_pcs++)
	{
		LONG lWindowStyle = ::GetWindowLong(*native_pcs, GWL_EXSTYLE) | WS_EX_LAYERED;
		::SetWindowLong(*native_pcs, GWL_EXSTYLE, lWindowStyle);
		ColoredEx P_Color = NULL;
		HINSTANCE hInst = LoadLibrary("User32.DLL");
		P_Color = (ColoredEx)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		if (P_Color)P_Color(*native_pcs, RGB(FullColor.RED,FullColor.GREEN,FullColor.BLUE), byDw, 1);
		FreeLibrary(hInst);
	}
	return TRUE;
}

_declspec (dllexport) BOOL __stdcall On_Pcs_All(unsigned char byDw)
{
	All_Windows.clear();
	My_Windows.clear();
	EnumWindows(GetAllEx, 0);
	is_My_Windows(GetSelfModuleHandle());
	typedef BOOL(WINAPI *ColoredEx)(HWND, COLORREF, BYTE, DWORD);
	for (auto native_pcs = My_Windows.begin(); native_pcs != My_Windows.end(); native_pcs++)
	{
		LONG lWindowStyle = ::GetWindowLong(*native_pcs, GWL_EXSTYLE) | WS_EX_LAYERED;
		::SetWindowLong(*native_pcs, GWL_EXSTYLE, lWindowStyle);
		ColoredEx P_Color = NULL;
		HINSTANCE hInst = LoadLibrary("User32.DLL");
		P_Color = (ColoredEx)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		if (P_Color)P_Color(*native_pcs, 0, byDw, 2);
		FreeLibrary(hInst);
	}
	return TRUE;
}

_declspec (dllexport) BOOL __stdcall On_Res_All()
{
	All_Windows.clear();
	My_Windows.clear();
	EnumWindows(GetAllEx, 0);
	is_My_Windows(GetSelfModuleHandle());
	typedef BOOL(WINAPI *ColoredEx)(HWND, COLORREF, BYTE, DWORD);
	for (auto native_pcs = My_Windows.begin(); native_pcs != My_Windows.end(); native_pcs++)
	{
		LONG lWindowStyle = ::GetWindowLong(*native_pcs, GWL_EXSTYLE) | WS_EX_LAYERED;
		::SetWindowLong(*native_pcs, GWL_EXSTYLE, lWindowStyle);
		ColoredEx P_Color = NULL;
		HINSTANCE hInst = LoadLibrary("User32.DLL");
		P_Color = (ColoredEx)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		if (P_Color)P_Color(*native_pcs, 0, 255, 2);
		FreeLibrary(hInst);
	}
	return TRUE;
}


void is_My_Windows(HMODULE MyPcs)
{
	for (auto mx = All_Windows.begin(); mx != All_Windows.end(); mx++)
	{
		if (IsWindow(*mx))
		{
			My_Windows.push_back(*mx);
		}
	}
}

class Iniza
{
public:
	void X_THREADEX()
	{
		typedef BOOL(WINAPI *ColoredEx)(HWND, COLORREF, BYTE, DWORD);
		while (true)
		{
			for (auto native_pcs = My_Windows.begin(); native_pcs != My_Windows.end(); native_pcs++)
			{
				LONG lWindowStyle = ::GetWindowLong(*native_pcs, GWL_EXSTYLE) | WS_EX_LAYERED;
				::SetWindowLong(*native_pcs, GWL_EXSTYLE, lWindowStyle);
				ColoredEx P_Color = NULL;
				HINSTANCE hInst = LoadLibrary("User32.DLL");
				P_Color = (ColoredEx)GetProcAddress(hInst, "SetLayeredWindowAttributes");
				if (P_Color)P_Color(*native_pcs, 0, 200, 2);
				FreeLibrary(hInst);
			}
			::Sleep(10);
		}
	}

	stack <thread> Thr_MGRX;

	void Pcs_Stack()
	{
		All_Windows.clear();
		My_Windows.clear();
		EnumWindows(Getted_Windows, GetCurrentProcessId());
		is_My_Windows(GetSelfModuleHandle());
		Thr_MGRX.push(thread(&Iniza::X_THREADEX,this));
		Thr_MGRX.top().detach();
	}
};



BOOL CForceAlphaXApp::InitInstance()
{
#ifdef LIMITED
	auto tt = std::chrono::system_clock::to_time_t
	(std::chrono::system_clock::now());
	struct tm* ptm = localtime(&tt);
	if (((int)ptm->tm_year + 1900) >= 2019 && ((int)ptm->tm_mon + 1) > 6)
	{
		MessageBoxA(GetForegroundWindow(), "Out of date", "Sorfware Error", MB_OK);
		ExitProcess(-1);
	}
#endif
	All_Windows.clear();
	My_Windows.clear();
	EnumWindows(Getted_Windows, GetCurrentProcessId());
	is_My_Windows(GetSelfModuleHandle());
	typedef BOOL(WINAPI *ColoredEx)(HWND, COLORREF, BYTE, DWORD);
	for (auto native_pcs = My_Windows.begin(); native_pcs != My_Windows.end(); native_pcs++)
	{
		LONG lWindowStyle = ::GetWindowLong(*native_pcs, GWL_EXSTYLE) | WS_EX_LAYERED;
		::SetWindowLong(*native_pcs, GWL_EXSTYLE, lWindowStyle);
		ColoredEx P_Color = NULL;
		HINSTANCE hInst = LoadLibrary("User32.DLL");
		P_Color = (ColoredEx)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		if (P_Color)P_Color(*native_pcs, 0, 200, 2);
		FreeLibrary(hInst);
	}
	CWinApp::InitInstance();
	return TRUE;
}
