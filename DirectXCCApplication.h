#pragma once

/*
*	DirectX ColorConverter - программа, преобразующая цвета в формат DirectX.
*   DirectXCCApplication.h - модуль ядра программы(содержит основной класс).
*	Автор: Shkolnik Prahramist (c) 2018.
*/

#include "APICore.h"
#include "UiRenderer.h"

// Объявление класса, содержащего ядро приложения.
class UiRenderer;
class DirectXCCApplication
{
// Секция содержит служебные поля.
private:
	/*Дескрипторы низкоуровневых объектов.*/
	HWND m_hMainWindowHandle{};											// Дескриптор главного-окна приложения.

	HWND m_hCloseButtonHandle{};										// Дескриптор кнопки закрытия главного окна приложения.
	HWND m_hMinimizeButtonHandle{};										// Дескриптор кнопки сворачивания главного окна приложения.
	HWND m_hColorTextBoxHandle{};										// Дескриптор поля для ввода, RGB значения цвета.
	HWND m_hConvertButtonHandle{};										// Дескриптор кнопки преобразования цвета.

	HDC m_hWindowDC{};													// Дескриптор девайса графики (Handle Device Context).
	RECT m_rWindowRect{};												// Прямоугольник окна.

	const HRGN m_hSrcRgn{ CreateRectRgn(0, 0, 594, 279) };
	const HRGN m_hSrcRgn1{ CreateRectRgn(2, 2, 590, 275) };
	HRGN m_hAnimationRegion{};

	/*Характеристики главного окна.*/
	const std::wstring m_szApplicationTitle{L"DirectX CC"};				// Текст названия главного окна в ОС.
	const int m_nAppWidth{594}, m_nAppHeight{279};						// Размеры главного окна.

	// Перечисления идентификаторов элементов управления
	enum class UI_CTL_ID
	{
		CLOSE_BTN,
		MINIMIZE_BTN,
		TEXTBOX_BTN,
		CONV_BTN
	};

	UiRenderer* renderer{};												// Указатель на объект графического ядра приложения.
	friend class UiRenderer;											// Объявление дружественного класса.

// Секция содержит служебные методы.
private:
	// bool RegisterNativeWindowObject() - метод регистрирует основное окно в ОС.
	bool RegisterNativeWindowObject();

	// static LRESULT CALLBACK ApplicationProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) - статический метод обработки оконных сообщений(необходим для преобразования сообщений в динамический метод класса).
	static LRESULT CALLBACK ApplicationProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) - метод обработки оконных сообщений.
	LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// bool CreateNativeUiControls() - метод создает низкоуровневые элементы управления(окна).
	bool CreateNativeUiControls();

// Секция содержит методы управления состоянием главного окна.
private:
	// void OnClose() - метод, вызывающийся при закрытии главного окна.
	void OnClose();

	// void OnCreate() - метод, вызывающийся при создании главного окна.
	void OnCreate();

	// void OnPaint() - метод, вызывающийся при рисовании главного окна.
	void OnPaint();
	
	// void OnMove() - метод, вызывающийся при движении главного окна.
	void OnMove();

	// void OnLButtonDown() - метод, вызывающийся при нажатии ЛКМ в области главного окна.
	void OnLButtonDown();

	// void OnUiClick() - метод вызывается при клике на UI компонент.
	void OnUiClick(const int & nID);

	// void OnCloseButtonClick() - метод вызывается при клике на кнопку закрытия окна.
	void OnCloseButtonClick();

	// void OnMinimizeButtonClick() - метод вызывается при клике на кнопку сворачивания окна.
	void OnMinimizeButtonClick();

	// void OnConvertButtonClick() - метод вызывается при клике на кнопку конвертации цветов.
	void OnConvertButtonClick();

// Секция содержит основные методы запуска окна приложения.
public:
	// Конструктор.
	DirectXCCApplication();

	// int Run() - метод запускает цикл обработки сообщений главного окна.
	int Run();

	// HRESULT Invalidate() - метод перерисовывает главное окно.
	HRESULT Invalidate();

	// Деструктор.
	~DirectXCCApplication();
};