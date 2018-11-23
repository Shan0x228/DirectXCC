#pragma once

/*
*	DirectX ColorConverter - ���������, ������������� ����� � ������ DirectX.
*   DirectXCCApplication.h - ������ ���� ���������(�������� �������� �����).
*	�����: Shkolnik Prahramist (c) 2018.
*/

#include "APICore.h"
#include "UiRenderer.h"

// ���������� ������, ����������� ���� ����������.
class UiRenderer;
class DirectXCCApplication
{
// ������ �������� ��������� ����.
private:
	/*����������� �������������� ��������.*/
	HWND m_hMainWindowHandle{};											// ���������� ��������-���� ����������.

	HWND m_hCloseButtonHandle{};										// ���������� ������ �������� �������� ���� ����������.
	HWND m_hMinimizeButtonHandle{};										// ���������� ������ ������������ �������� ���� ����������.
	HWND m_hColorTextBoxHandle{};										// ���������� ���� ��� �����, RGB �������� �����.
	HWND m_hConvertButtonHandle{};										// ���������� ������ �������������� �����.

	HDC m_hWindowDC{};													// ���������� ������� ������� (Handle Device Context).
	RECT m_rWindowRect{};												// ������������� ����.

	const HRGN m_hSrcRgn{ CreateRectRgn(0, 0, 594, 279) };
	const HRGN m_hSrcRgn1{ CreateRectRgn(2, 2, 590, 275) };
	HRGN m_hAnimationRegion{};

	/*�������������� �������� ����.*/
	const std::wstring m_szApplicationTitle{L"DirectX CC"};				// ����� �������� �������� ���� � ��.
	const int m_nAppWidth{594}, m_nAppHeight{279};						// ������� �������� ����.

	// ������������ ��������������� ��������� ����������
	enum class UI_CTL_ID
	{
		CLOSE_BTN,
		MINIMIZE_BTN,
		TEXTBOX_BTN,
		CONV_BTN
	};

	UiRenderer* renderer{};												// ��������� �� ������ ������������ ���� ����������.
	friend class UiRenderer;											// ���������� �������������� ������.

// ������ �������� ��������� ������.
private:
	// bool RegisterNativeWindowObject() - ����� ������������ �������� ���� � ��.
	bool RegisterNativeWindowObject();

	// static LRESULT CALLBACK ApplicationProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) - ����������� ����� ��������� ������� ���������(��������� ��� �������������� ��������� � ������������ ����� ������).
	static LRESULT CALLBACK ApplicationProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) - ����� ��������� ������� ���������.
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// bool CreateNativeUiControls() - ����� ������� �������������� �������� ����������(����).
	bool CreateNativeUiControls();

// ������ �������� ������ ���������� ���������� �������� ����.
private:
	// void OnClose() - �����, ������������ ��� �������� �������� ����.
	void OnClose();

	// void OnCreate() - �����, ������������ ��� �������� �������� ����.
	void OnCreate();

	// void OnPaint() - �����, ������������ ��� ��������� �������� ����.
	void OnPaint();
	
	// void OnMove() - �����, ������������ ��� �������� �������� ����.
	void OnMove();

	// void OnLButtonDown() - �����, ������������ ��� ������� ��� � ������� �������� ����.
	void OnLButtonDown();

	// void OnUiClick() - ����� ���������� ��� ����� �� UI ���������.
	void OnUiClick(const int & nID);

	// void OnCloseButtonClick() - ����� ���������� ��� ����� �� ������ �������� ����.
	void OnCloseButtonClick();

	// void OnMinimizeButtonClick() - ����� ���������� ��� ����� �� ������ ������������ ����.
	void OnMinimizeButtonClick();

	// void OnConvertButtonClick() - ����� ���������� ��� ����� �� ������ ����������� ������.
	void OnConvertButtonClick();

// ������ �������� �������� ������ ������� ���� ����������.
public:
	// �����������.
	DirectXCCApplication();

	// int Run() - ����� ��������� ���� ��������� ��������� �������� ����.
	int Run();

	// HRESULT Invalidate() - ����� �������������� ������� ����.
	HRESULT Invalidate();

	// ����������.
	~DirectXCCApplication();
};