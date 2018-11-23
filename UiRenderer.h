#pragma once

/*
*  UiRenderer.h - ����������� ������ ��������� GUI � ��������� ����������.
*	�����: Shkolnik Prahramist (c) 2018.
*/

#include "APICore.h"
#include "DirectXCCApplication.h"

class DirectXCCApplication;
// ���������� ������, ����������� ����������� ���� ����������.
class UiRenderer
{
// ������ �������� ��������� ���� Direct2D.
private:
	DirectXCCApplication* pApp{};
	ID2D1Factory* m_pD2D1Factory{};
	IDWriteFactory* m_pDWriteFactory{};

	ID2D1DCRenderTarget* m_pDCRT{};
	ID2D1SolidColorBrush* m_pSolidBrush{};
	IDWriteTextFormat* m_pTextFormat{};

	const D2D1_COLOR_F m_cWindowBackgroundColor{ 0.086f, 0.086f, 0.086f, 1.0f };

// ������ �������� ��������� ���� UIAnimation API.
public:
	// Animation components
	IUIAnimationManager*			m_pAnimationManager{};
	IUIAnimationTimer*				m_pAnimationTimer{};
	IUIAnimationTransitionLibrary*  m_pTransitionLibrary{};

	// Animated Variables
	IUIAnimationVariable*			m_pDeltaVariable{};

// ������ �������� ��������� ������ UIAnimation API.
private:
	// HRESULT InitializeAnimation() - ����� �������������� WAM.
	HRESULT InitializeAnimation();

	// HRESULT CreateAnimationVariables() - ����� �������������� ������� WAM.
	HRESULT CreateAnimationVariables();

	// void FreeUiAnimation() - ����� ������������ ������� WAM.
	void FreeUiAnimation();

// ������ �������� ��������� ������.
private:
	// void InitD2D1() - ����� �������������� Direct2D.
	void InitD2D1();
	
	// void FreeD2D1() - ����� ������������ Direct2D.
	void FreeD2D1();

	// void CreateD2D1Resources() - ����� �������������� ������� ��� ���������.
	void CreateD2D1Resources();

	// void FreeD2D1Resources() - ����� ������������ ������� ��� ���������.
	void FreeD2D1Resources();

	// ������� ������ Direct2D �������.
	template<typename T>
	static void ReleaseComObj(T & obj)
	{
		if (obj != nullptr)
		{
			obj->Release();
		}
		obj = nullptr;
	}

// ������ �������� ������ ��������� GUI.
public:
	// void DrawWindowBackground() - ����� ������ ��� �������� ����.
	void DrawWindowBackground();

	// void DrawWindowFrame() - ����� ������ ������� �������� ����.
	void DrawWindowFrame();

	// void DrawWindowTitleBar() - ����� ������ ��������� �������� ����.
	void DrawWindowTitleBar();

	// void DrawUiButtons(const int & nId, PDRAWITEMSTRUCT pDis) - ����� ������ ������ �������� ����.
	void DrawUiButtons(const int & nId, PDRAWITEMSTRUCT pDis);

public:
	// �����������.
	UiRenderer(DirectXCCApplication * pApp);

	// void StartDrawing() - �����, ���������������� ������� DirectX � ���������.
	void StartDrawing();

	// TODO...
	void DeltaChanger();

	// void StopDrawing() - �����, ��������������� ������� ���������.
	void StopDrawing();

	// ����������.
	~UiRenderer();
};