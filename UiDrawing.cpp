#include "UiRenderer.h"

// void DrawWindowBackground() - метод рисует фон главного окна.
void UiRenderer::DrawWindowBackground()
{
	/*this->m_pSolidBrush->SetColor(this->m_cWindowBackgroundColor);
	this->m_pDCRT->FillRectangle(
		D2D1::RectF(0.0f, 0.0f, static_cast<FLOAT>(this->pApp->m_nAppWidth), static_cast<FLOAT>(this->pApp->m_nAppHeight)),
		this->m_pSolidBrush);*/
}

// void DrawWindowFrame() - метод рисует обводку главного окна.
void UiRenderer::DrawWindowFrame()
{
	// Get the RGB animation variable values
	DOUBLE DeltaValue{};
	this->m_pDeltaVariable->GetValue(&DeltaValue);

	this->m_pSolidBrush->SetColor(D2D1::ColorF(0.705f, 0.0f, static_cast<FLOAT>(DeltaValue) / 255.0f, 1.0f));
	this->m_pDCRT->DrawRectangle(D2D1::RectF(1.0f, 1.0f, static_cast<FLOAT>(this->pApp->m_nAppWidth) - 1.0f, static_cast<FLOAT>(this->pApp->m_nAppHeight) - 1.0f), this->m_pSolidBrush, 2.0f);
}

// void DrawWindowTitleBar() - метод рисует заголовок главного окна.
void UiRenderer::DrawWindowTitleBar()
{
	this->m_pDWriteFactory->CreateTextFormat(
		L"Roboto",
		nullptr,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		20.0f,
		L"",
		&this->m_pTextFormat
	);

	this->m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));
	this->m_pDCRT->DrawText(this->pApp->m_szApplicationTitle.c_str(), this->pApp->m_szApplicationTitle.length(), this->m_pTextFormat, D2D1::RectF(20.0f, 6.0f, 150.0f, 30.0f), this->m_pSolidBrush);

	this->ReleaseComObj(this->m_pTextFormat);
}

// void DrawUiButtons(const int & nId, PDRAWITEMSTRUCT pDis) - метод рисует кнопку закрытия окна.
void UiRenderer::DrawUiButtons(const int & nId, PDRAWITEMSTRUCT pDis)
{
	this->m_pDCRT->BindDC(pDis->hDC, &pDis->rcItem);
	this->m_pDCRT->BeginDraw();
	this->m_pDCRT->Clear(this->m_cWindowBackgroundColor);

	switch (nId)
	{
		case static_cast<int>(DirectXCCApplication::UI_CTL_ID::CLOSE_BTN):
		{
			this->m_pSolidBrush->SetColor(this->m_cWindowBackgroundColor);
			this->m_pDCRT->FillRectangle(D2D1::RectF(0.0f, 0.0f, static_cast<FLOAT>(pDis->rcItem.right), static_cast<FLOAT>(pDis->rcItem.bottom)), this->m_pSolidBrush);

			if (pDis->itemState & ODS_SELECTED)
				this->m_pSolidBrush->SetColor(D2D1::ColorF(0.721f, 0.721f, 0.721f, 1.0f));
			else
				this->m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));

			this->m_pDCRT->DrawLine(D2D1::Point2F(0.0f, 0.0f), D2D1::Point2F(16.0f, 16.0f), this->m_pSolidBrush, 2.0f);
			this->m_pDCRT->DrawLine(D2D1::Point2F(16.0f, 0.0f), D2D1::Point2F(0.0f, 16.0f), this->m_pSolidBrush, 2.0f);
		}
		break;
	
		case static_cast<int>(DirectXCCApplication::UI_CTL_ID::MINIMIZE_BTN):
		{
			//this->m_pDCRT_T->BindDC(pDis->hDC, &pDis->rcItem);
			//this->m_pDCRT_T->BeginDraw();
			//this->m_pDCRT_T->Clear(this->m_cWindowBackgroundColor);

			this->m_pSolidBrush->SetColor(this->m_cWindowBackgroundColor);
			this->m_pDCRT->FillRectangle(D2D1::RectF(0.0f, 0.0f, static_cast<FLOAT>(pDis->rcItem.right), static_cast<FLOAT>(pDis->rcItem.bottom)), this->m_pSolidBrush);

			if (pDis->itemState & ODS_SELECTED)
				this->m_pSolidBrush->SetColor(D2D1::ColorF(0.721f, 0.721f, 0.721f, 1.0f));
			else
				this->m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));

			this->m_pDCRT->DrawLine(D2D1::Point2F(0.0f, 15.0f), D2D1::Point2F(16.0f, 15.0f), this->m_pSolidBrush, 2.0f);

			this->m_pDCRT->EndDraw();
		}
		break;

		case static_cast<int>(DirectXCCApplication::UI_CTL_ID::CONV_BTN):
		{
			if (pDis->itemState & ODS_SELECTED)
				this->m_pSolidBrush->SetColor(D2D1::ColorF(0.070f, 0.482f, 0.894f, 1.0f));
			else
				this->m_pSolidBrush->SetColor(D2D1::ColorF(0.0f, 0.501f, 1.0f, 1.0f));

			this->m_pDCRT->FillRectangle(D2D1::RectF(0.0f, 0.0f, static_cast<FLOAT>(pDis->rcItem.right), static_cast<FLOAT>(pDis->rcItem.bottom)), this->m_pSolidBrush);

			this->m_pDWriteFactory->CreateTextFormat(
				L"Roboto",
				nullptr,
				DWRITE_FONT_WEIGHT_LIGHT,
				DWRITE_FONT_STYLE_NORMAL,
				DWRITE_FONT_STRETCH_NORMAL,
				21.0f,
				L"",
				&this->m_pTextFormat
			);

			this->m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
			this->m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

			if (pDis->itemState & ODS_SELECTED)
				this->m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::WhiteSmoke));
			else
				this->m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::White));

			this->m_pDCRT->DrawText(L"Convert!", 9, this->m_pTextFormat, D2D1::RectF(0.0f, 0.0f, static_cast<FLOAT>(pDis->rcItem.right), static_cast<FLOAT>(pDis->rcItem.bottom)), this->m_pSolidBrush);

			this->ReleaseComObj(this->m_pTextFormat);
		}
		break;
	}

	this->m_pDCRT->EndDraw();
}