#include "DirectXCCApplication.h"

// bool RegisterNativeWindowObject() - метод регистрирует основное окно в ОС.
bool DirectXCCApplication::RegisterNativeWindowObject()
{
	HRESULT hr = CoInitialize(NULL);
	if (!SUCCEEDED(hr))
		return false;

	WNDCLASSEX wc{ sizeof(WNDCLASSEX) };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = nullptr;//reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = nullptr;
	wc.lpfnWndProc = DirectXCCApplication::ApplicationProc;
	wc.lpszClassName = this->m_szApplicationTitle.c_str();
	wc.lpszMenuName = nullptr;
	wc.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wc))
		return false;

	if (this->m_hMainWindowHandle = CreateWindowEx(0,
		this->m_szApplicationTitle.c_str(),
		this->m_szApplicationTitle.c_str(),
		WS_CAPTION | WS_POPUP,
		(GetSystemMetrics(SM_CXSCREEN) - this->m_nAppWidth) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - this->m_nAppHeight) / 2,
		this->m_nAppWidth,
		this->m_nAppHeight,
		nullptr, nullptr, nullptr, this
	); !this->m_hMainWindowHandle)
		return false;

	this->renderer = new UiRenderer{ this };

	ShowWindow(this->m_hMainWindowHandle, SW_SHOW);
	UpdateWindow(this->m_hMainWindowHandle);

	return true;
}

// static LRESULT CALLBACK ApplicationProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) - статический метод обработки оконных сообщений(необходим для преобразования сообщений в динамический метод класса).
LRESULT DirectXCCApplication::ApplicationProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	DirectXCCApplication* pApp;
	if (uMsg == WM_NCCREATE)
	{
		pApp = static_cast<DirectXCCApplication*>(reinterpret_cast<CREATESTRUCT*>(lParam)->lpCreateParams);
		SetLastError(0);
		if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pApp)))
		{
			if (GetLastError() != 0)
				return false;
		}
	}
	else
	{
		pApp = reinterpret_cast<DirectXCCApplication*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	}

	if (pApp)
	{
		pApp->m_hMainWindowHandle = hWnd;
		return pApp->WindowProc(hWnd, uMsg, wParam, lParam);
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) - метод обработки оконных сообщений.
LRESULT DirectXCCApplication::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CREATE:
		{
			this->OnCreate();
		}
		break;

		case WM_PAINT:
		case WM_DISPLAYCHANGE:
		{
			PAINTSTRUCT ps{};
			BeginPaint(hWnd, &ps);
			this->m_hWindowDC = ps.hdc;

			this->OnPaint();

			EndPaint(hWnd, &ps);
		}
		return 0;

		case WM_TIMER:
		{
			this->Invalidate();
		}
		break;

		case WM_MOVE:
		{
			this->OnMove();
		}
		return 0;

		case WM_DRAWITEM:
		{
			this->renderer->DrawUiButtons(wParam, reinterpret_cast<PDRAWITEMSTRUCT>(lParam));
		}
		break;

		case WM_SETCURSOR:
		{
			HWND wind = reinterpret_cast<HWND>(wParam);
			if (wind == this->m_hCloseButtonHandle || wind == this->m_hMinimizeButtonHandle|| wind == this->m_hConvertButtonHandle)
			{
				SetCursor(LoadCursor(NULL, IDC_HAND));
				return(TRUE);
			}
		}
		break;

		case WM_NCCALCSIZE:
		{
			// Returning 0 from the message when wParam is TRUE removes the standard
			// frame, but keeps the window shadow.
			if (wParam == TRUE)
				SetWindowLong(hWnd, DWL_MSGRESULT, 0);
			return TRUE;
			return FALSE;
		}
		break;

		case WM_NCHITTEST:
		{
			// Returning HTCAPTION allows the user to move the window around by clicking 
			// anywhere.
			// Depending on the mouse coordinates passed in LPARAM, you may 
			// return other values to enable resizing.
			SetWindowLong(hWnd, DWL_MSGRESULT, HTCAPTION);
			return TRUE;
		}
		break;

		case WM_COMMAND:
		{
			this->OnUiClick(LOWORD(wParam));
		}
		break;

		case WM_LBUTTONDOWN:
		{
			this->OnLButtonDown();
		}
		break;

		case WM_DESTROY:
		{
			this->OnClose();
			PostQuitMessage(0);
		}
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

// bool CreateNativeUiControls() - метод создает низкоуровневые элементы управления(окна).
bool DirectXCCApplication::CreateNativeUiControls()
{
	if (this->m_hCloseButtonHandle = CreateWindow(
		L"BUTTON",
		L"X",
		WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
		564, 9, 16, 16, this->m_hMainWindowHandle,
		reinterpret_cast<HMENU>(DirectXCCApplication::UI_CTL_ID::CLOSE_BTN), nullptr, nullptr
	); !this->m_hCloseButtonHandle)
		return false;

	if (this->m_hMinimizeButtonHandle = CreateWindow(
		L"BUTTON",
		L"_",
		WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
		520, 9, 16, 16, this->m_hMainWindowHandle,
		reinterpret_cast<HMENU>(DirectXCCApplication::UI_CTL_ID::MINIMIZE_BTN), nullptr, nullptr
	); !this->m_hMinimizeButtonHandle)
		return false;

	if (this->m_hColorTextBoxHandle = CreateWindow(
		L"EDIT",
		L"",
		WS_VISIBLE | WS_CHILD,
		124, 102, 346, 21, this->m_hMainWindowHandle,
		reinterpret_cast<HMENU>(DirectXCCApplication::UI_CTL_ID::TEXTBOX_BTN), nullptr, nullptr
	); !this->m_hColorTextBoxHandle)
		return false;

	HFONT hFont = CreateFont(20, 0, 0, 0, FW_REGULAR, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, 0, DEFAULT_PITCH, L"Roboto");
	SendMessage(this->m_hColorTextBoxHandle, WM_SETFONT, reinterpret_cast<WPARAM>(hFont), TRUE);
	SendMessage(this->m_hColorTextBoxHandle, EM_SETMARGINS, EC_LEFTMARGIN | EC_RIGHTMARGIN, MAKELONG(5, 5));

	if (this->m_hConvertButtonHandle = CreateWindow(
		L"BUTTON",
		L"Convert!",
		WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
		124, 134, 346, 43, this->m_hMainWindowHandle,
		reinterpret_cast<HMENU>(DirectXCCApplication::UI_CTL_ID::CONV_BTN), nullptr, nullptr
	); !this->m_hConvertButtonHandle)
		return false;

	return true;
}

// Конструктор.
DirectXCCApplication::DirectXCCApplication()
{
	if (!this->RegisterNativeWindowObject())
		ExitProcess(EXIT_FAILURE);
}

// int Run() - метод запускает цикл обработки сообщений главного окна.
int DirectXCCApplication::Run()
{
	MSG msg{};
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return static_cast<int>(msg.wParam);
}

// HRESULT Invalidate() - метод перерисовывает главное окно.
HRESULT DirectXCCApplication::Invalidate()
{	
	HRESULT hr = InvalidateRgn(this->m_hMainWindowHandle, this->m_hAnimationRegion, false);; //bResult ? S_OK : E_FAIL;
	return hr;
}

// Деструктор.
DirectXCCApplication::~DirectXCCApplication()
{
	if (this->renderer != nullptr)
		delete this->renderer;
	this->renderer = nullptr;
}
