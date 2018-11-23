#pragma once

/*
*  UiRenderer.h - графический модуль отрисовки GUI и элементов управления.
*	Автор: Shkolnik Prahramist (c) 2018.
*/

#include "APICore.h"
#include "DirectXCCApplication.h"

class DirectXCCApplication;
// Объявление класса, содержащего графическое ядро приложения.
class UiRenderer
{
// Секция содержит служебные поля Direct2D.
private:
	DirectXCCApplication* pApp{};
	ID2D1Factory* m_pD2D1Factory{};
	IDWriteFactory* m_pDWriteFactory{};

	ID2D1DCRenderTarget* m_pDCRT{};
	ID2D1SolidColorBrush* m_pSolidBrush{};
	IDWriteTextFormat* m_pTextFormat{};

	const D2D1_COLOR_F m_cWindowBackgroundColor{ 0.086f, 0.086f, 0.086f, 1.0f };

// Секция содержит служебные поля UIAnimation API.
public:
	// Animation components
	IUIAnimationManager*			m_pAnimationManager{};
	IUIAnimationTimer*				m_pAnimationTimer{};
	IUIAnimationTransitionLibrary*  m_pTransitionLibrary{};

	// Animated Variables
	IUIAnimationVariable*			m_pDeltaVariable{};

// Секция содержит служебные методы UIAnimation API.
private:
	// HRESULT InitializeAnimation() - метод инициализирует WAM.
	HRESULT InitializeAnimation();

	// HRESULT CreateAnimationVariables() - метод инициализирует ресурсы WAM.
	HRESULT CreateAnimationVariables();

	// void FreeUiAnimation() - метод высвобождает ресурсы WAM.
	void FreeUiAnimation();

// Секция содержит служебные методы.
private:
	// void InitD2D1() - метод инициализирует Direct2D.
	void InitD2D1();
	
	// void FreeD2D1() - метод высвобождает Direct2D.
	void FreeD2D1();

	// void CreateD2D1Resources() - метод инициализирует ресурсы для рисования.
	void CreateD2D1Resources();

	// void FreeD2D1Resources() - метод высвобождает ресурсы для рисования.
	void FreeD2D1Resources();

	// Очистка памяти Direct2D объекта.
	template<typename T>
	static void ReleaseComObj(T & obj)
	{
		if (obj != nullptr)
		{
			obj->Release();
		}
		obj = nullptr;
	}

// Секция содержит методы отрисовки GUI.
public:
	// void DrawWindowBackground() - метод рисует фон главного окна.
	void DrawWindowBackground();

	// void DrawWindowFrame() - метод рисует обводку главного окна.
	void DrawWindowFrame();

	// void DrawWindowTitleBar() - метод рисует заголовок главного окна.
	void DrawWindowTitleBar();

	// void DrawUiButtons(const int & nId, PDRAWITEMSTRUCT pDis) - метод рисует кнопку закрытия окна.
	void DrawUiButtons(const int & nId, PDRAWITEMSTRUCT pDis);

public:
	// Конструктор.
	UiRenderer(DirectXCCApplication * pApp);

	// void StartDrawing() - метод, подготавливающий ресурсы DirectX к рисованию.
	void StartDrawing();

	// TODO...
	void DeltaChanger();

	// void StopDrawing() - метод, останавливающий процесс рисования.
	void StopDrawing();

	// Деструктор.
	~UiRenderer();
};