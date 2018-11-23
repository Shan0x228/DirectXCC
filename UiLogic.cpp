#include "DirectXCCApplication.h"

// void OnCloseButtonClick() - метод вызывается при клике на кнопку закрытия окна.
void DirectXCCApplication::OnCloseButtonClick()
{
	SendMessage(this->m_hMainWindowHandle, WM_DESTROY, 0, 0);
}

// void OnMinimizeButtonClick() - метод вызывается при клике на кнопку сворачивания окна.
void DirectXCCApplication::OnMinimizeButtonClick()
{
	SendMessage(this->m_hMainWindowHandle, WM_SYSCOMMAND, SC_MINIMIZE, 0);
}

// void OnConvertButtonClick() - метод вызывается при клике на кнопку конвертации цветов.
void DirectXCCApplication::OnConvertButtonClick()
{
	using namespace std;

	int R{}, G{}, B{};

	wstring text{};
	text.resize(64);

	GetWindowText(this->m_hColorTextBoxHandle, &text[0], 64);

	text.erase(remove(begin(text), end(text), 0), end(text));
	text.erase(remove(begin(text), end(text), ' '), end(text));
	text.erase(remove(begin(text), end(text), 'r'), end(text));
	text.erase(remove(begin(text), end(text), 'g'), end(text));
	text.erase(remove(begin(text), end(text), 'b'), end(text));
	text.erase(remove(begin(text), end(text), '('), end(text));
	text.erase(remove(begin(text), end(text), ')'), end(text));

	int rPos = text.find(',', 0);
	if (rPos == wstring::npos)
	{
		SetWindowText(this->m_hColorTextBoxHandle, L"Invalid data!");
		return;
	}

	int gPos = text.find(',', rPos + 1);
	if (gPos == wstring::npos)
	{
		SetWindowText(this->m_hColorTextBoxHandle, L"Invalid data!");
		return;
	}

	R = _wtoi(text.substr(0, rPos).c_str());
	G = _wtoi(text.substr(rPos + 1, gPos).c_str());
	B = _wtoi(text.substr(gPos + 1, wstring::npos).c_str());

	FLOAT fR = static_cast<FLOAT>(R) / 255.0f;
	FLOAT fG = static_cast<FLOAT>(G) / 255.0f;
	FLOAT fB = static_cast<FLOAT>(B) / 255.0f;

	text = to_wstring(fR) + L"f, " + to_wstring(fG) + L"f, " + to_wstring(fB) + L"f";

	SetWindowText(this->m_hColorTextBoxHandle, text.c_str());
}
