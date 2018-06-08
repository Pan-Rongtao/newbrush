#include "system/Platform.h"

#if NEWBRUSH_SDK_TARGET_PLATFORM == PLATFORM_WIN32
#include "Window_Win32.h"
#include "core/Exception.h"
#include "system/WindowEvent.h"

using nb::System::String;
using nb::System::WindowEvent;
using nb::System::Window;
using nb::System::Window_Win32;
#define WINDOW_CLASS_NAME	"Newbrush Class"

bool Window_Win32::m_bPressed = false;
Window_Win32::Window_Win32(Window *pV)
: NativeWindow(pV)
{
	m_Instance = ::GetModuleHandle(NULL);

	WNDCLASSA windowClass = {0};
	windowClass.style			= 0;
	windowClass.cbClsExtra		= 0;
	windowClass.cbWndExtra		= 0;
	windowClass.lpszMenuName	= 0;
	windowClass.hInstance		= m_Instance;
	windowClass.lpszClassName	= WINDOW_CLASS_NAME;
	windowClass.lpfnWndProc		= Window_Win32::WndProc;
	windowClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	windowClass.hCursor			= LoadCursor(NULL, IDC_ARROW);
	windowClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
//	windowClass.hIconSm			= 0;

	if(::RegisterClassA(&windowClass) == 0)
	{
		int err = GetLastError();
		if(err != 1410)	//class is already registed
		{
			char info[80] = {0};
			sprintf_s(info, "RegisterClass window class fail. error code[%d]", err);
			NB_THROW_EXCEPTION(info);
		}
	}

	RECT rcClient = {0, 0, 800, 480};
	AdjustWindowRect(&rcClient, WS_TILEDWINDOW, false);

	int width = rcClient.right - rcClient.left;
	int height = rcClient.bottom - rcClient.top;
	int x = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
	int y = (GetSystemMetrics(SM_CYSCREEN) - height ) / 2;
	m_Hwnd = ::CreateWindowA(windowClass.lpszClassName, "", WS_TILEDWINDOW, x, y, width, height, NULL, NULL, m_Instance, NULL);
	::ShowWindow(m_Hwnd, SW_SHOWNORMAL);
	::UpdateWindow(m_Hwnd);

	m_mapInternals.insert(std::make_pair((long)m_Hwnd, m_pW));
}

Window_Win32::~Window_Win32()
{
	::DestroyWindow(m_Hwnd);
	if(::UnregisterClassA(WINDOW_CLASS_NAME, m_Instance) == 0)
	{
		int err = GetLastError();
		char info[80] = {0};
		sprintf_s(info, "UnregisterClass window class fail. error code[%d]", err);
		NB_THROW_EXCEPTION(info);
	}
}

void Window_Win32::SetCaption(const nb::System::String &caption)
{
	::SetWindowTextA(m_Hwnd, caption.ToAscii().GetData());
}

nb::System::RectI Window_Win32::GetRect() const
{
	RECT rcWindow;
	RECT rcClient;
	::GetWindowRect(m_Hwnd, &rcWindow);
	::GetClientRect(m_Hwnd, &rcClient);
	return nb::System::RectI(rcWindow.left, rcWindow.top, rcClient.right -  rcClient.left, rcClient.bottom - rcClient.top);
}

void Window_Win32::SetRect(const nb::System::RectI &rect)
{
	RECT rc = {rect.GetX(), rect.GetTop(), rect.GetRight(), rect.GetBottom()};
	AdjustWindowRect(&rc, WS_TILEDWINDOW, false);
	::MoveWindow(m_Hwnd, rect.GetX(), rect.GetY(), rc.right - rc.left, rc.bottom - rc.top, true);
}

nb::System::String Window_Win32::GetCaption() const
{
	char arr[100] = {0};
	GetWindowTextA(m_Hwnd, arr, 100);
	return arr;
}

long Window_Win32::GetWindowHandle()
{
	return (long)m_Hwnd;
}

void Window_Win32::Pending()
{
	MSG msg = {0};
	if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
}

LRESULT CALLBACK Window_Win32::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if(msg == WM_DESTROY || msg == WM_CLOSE || msg == WM_QUIT || msg == WM_SIZE || 
		msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP || msg == WM_LBUTTONDBLCLK || msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP || msg == WM_MOUSEMOVE ||
		msg == WM_KEYDOWN || msg == WM_KEYUP || msg == WM_SYSKEYDOWN || msg == WM_SYSKEYUP)
	{			
		std::map<long, Window *>::const_iterator iter = m_mapInternals.find((long)hwnd);
		Window *pWindow = iter == m_mapInternals.end() ? NULL : iter->second;

		switch(msg)
		{
		case WM_DESTROY:
			if(pWindow)
			{
				NativeWindow::OnPrimaryAction(pWindow, WindowEvent::PrimaryAction_Destroy);
			}
			break;
		case WM_CLOSE:
		case WM_QUIT:
			{
				::PostQuitMessage(0);
			}
			break;
		case WM_SIZE:
			{
				if(pWindow)
				{
					NativeWindow::OnResize(pWindow, LOWORD(lParam), HIWORD(lParam));
				}
			}
			break;
		case WM_LBUTTONDOWN:
//		case WM_RBUTTONDOWN:
			{
				m_bPressed = true;
				::SetCapture(hwnd);
				if(pWindow)
				{
					NativeWindow::OnPointerAction(pWindow, WindowEvent::PointerAction_Down, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				}
			}
			break;
		case WM_MOUSEMOVE:
			{
				if(pWindow && m_bPressed)
				{
					NativeWindow::OnPointerAction(pWindow, WindowEvent::PointerAction_Move, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				}
			}
			break;
		case WM_LBUTTONUP:
//		case WM_RBUTTONUP:
			{
				m_bPressed = false;
				::ReleaseCapture();
				if(pWindow)
				{
					int x = GET_X_LPARAM(lParam);
					int y = GET_Y_LPARAM(lParam);
					NativeWindow::OnPointerAction(pWindow, WindowEvent::PointerAction_Up, x, y);

					RECT rcClient;
					::GetClientRect(hwnd, &rcClient);
					if(x >= 0 && x <= (rcClient.right -  rcClient.left) && y >= 0 && y <= (rcClient.bottom - rcClient.top))
						NativeWindow::OnPointerAction(pWindow, WindowEvent::PointerAction_Click, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				}
			}
			break;
		case WM_KEYDOWN:
		case WM_KEYUP:
			{
				if(pWindow)
				{
					if(wParam == VK_ESCAPE)
					{
						NativeWindow::OnKeyAction(pWindow, msg == WM_KEYDOWN ?  WindowEvent::KeyAction_Down : WindowEvent::KeyAction_Up, 
							WindowEvent::VKey_Esc, 0);
					}
					else if(wParam >= VK_F1 && wParam <= VK_F12)
					{
						NativeWindow::OnKeyAction(pWindow, msg == WM_KEYDOWN ?  WindowEvent::KeyAction_Down : WindowEvent::KeyAction_Up, 
							(WindowEvent::KeyCode)(wParam - VK_F1 + WindowEvent::VKey_F1), 0);
					}
					else if(wParam == VK_SPACE)
					{
						NativeWindow::OnKeyAction(pWindow, msg == WM_KEYDOWN ?  WindowEvent::KeyAction_Down : WindowEvent::KeyAction_Up, 
							WindowEvent::VKey_Space, 0);
					}
					else if((wParam >= '0' && wParam <= '9') || (wParam >= 'A' && wParam <= 'Z'))
					{
						NativeWindow::OnKeyAction(pWindow, msg == WM_KEYDOWN ? 
							WindowEvent::KeyAction_Down : WindowEvent::KeyAction_Up, 
							(WindowEvent::KeyCode)wParam, 0);
					}
					else if(wParam >= VK_LEFT && wParam <= VK_DOWN)
					{
						NativeWindow::OnKeyAction(pWindow, msg == WM_KEYDOWN ?  WindowEvent::KeyAction_Down : WindowEvent::KeyAction_Up, 
							(WindowEvent::KeyCode)(wParam - VK_LEFT + WindowEvent::VKey_Left), 0);
					}
				}

			}
			break;
		case WM_SYSKEYDOWN:		//F10只有systemkey，且F10会影响其他key建
		case WM_SYSKEYUP:
			{
				if(pWindow)
				{
					if(wParam == VK_F10)
					{
						NativeWindow::OnKeyAction(pWindow, msg == WM_SYSKEYDOWN ?  WindowEvent::KeyAction_Down : WindowEvent::KeyAction_Up, 
							WindowEvent::VKey_F10, 0);

						//F10在win32中会让窗口消息进入空闲状态，此时不会再接收到F1-F12按键，除非再按一次F10来取消这种状态
						//而直接return 0不return ::DefWindowProc(hwnd, msg, wParam, lParam);可防止这种事情发生。
						return 0;
					}
				}
			}
			break;		
		default:
			break;
		}
	}

	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

#endif
