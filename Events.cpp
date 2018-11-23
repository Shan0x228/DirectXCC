#include "DirectXCCApplication.h"

// void OnClose() - метод, вызывающийся при закрытии главного окна.
void DirectXCCApplication::OnClose()
{
}

// void OnCreate() - метод, вызывающийся при создании главного окна.
void DirectXCCApplication::OnCreate()
{
	if (!this->CreateNativeUiControls())
		SendMessage(this->m_hMainWindowHandle, WM_DESTROY, 0, 0);

	this->m_hAnimationRegion = CreateRectRgn(0, 0, 0, 0);
	CombineRgn(this->m_hAnimationRegion, this->m_hSrcRgn, this->m_hSrcRgn1, RGN_XOR);

	SetTimer(this->m_hMainWindowHandle, 1, 1, nullptr);

	GetClientRect(this->m_hMainWindowHandle, &this->m_rWindowRect);

	MARGINS pMargins{ 0, 0, 0, 1 };
	DwmExtendFrameIntoClientArea(this->m_hMainWindowHandle, &pMargins);

	// Force the system to recalculate NC area (making it send WM_NCCALCSIZE).
	SetWindowPos(this->m_hMainWindowHandle, nullptr, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_FRAMECHANGED);
}

// void OnPaint() - метод, вызывающийся при рисовании главного окна.
void DirectXCCApplication::OnPaint()
{
	// Update the animation manager with the current time
	UI_ANIMATION_SECONDS secondsNow;
	HRESULT hr = this->renderer->m_pAnimationTimer->GetTime(&secondsNow);
	if (SUCCEEDED(hr))
	{
		hr = this->renderer->m_pAnimationManager->Update(secondsNow);
		if (SUCCEEDED(hr))
		{
			// Read the values of the animation variables and draw the client area
			this->renderer->StartDrawing();
			this->renderer->DrawWindowFrame();
			this->renderer->DrawWindowTitleBar();
			this->renderer->StopDrawing();

			if (SUCCEEDED(hr))
			{
				// Continue redrawing the client area as long as there are animations scheduled
				UI_ANIMATION_MANAGER_STATUS status;
				hr = this->renderer->m_pAnimationManager->GetStatus(&status);

				if (SUCCEEDED(hr))
				{
					if (status == UI_ANIMATION_MANAGER_BUSY)
					{
						//this->Invalidate();
					}
					else
						this->renderer->DeltaChanger();
				}
			}
		}
	}
}

// void OnMove() - метод, вызывающийся при движении главного окна.
void DirectXCCApplication::OnMove()
{
}

// void OnLButtonDown() - метод, вызывающийся при нажатии ЛКМ в области главного окна.
void DirectXCCApplication::OnLButtonDown()
{
	ReleaseCapture();
	SendMessage(this->m_hMainWindowHandle, WM_SYSCOMMAND, 61458, 0);
}

// void OnUiClick() - метод, вызывается при клике на UI компонент.
void DirectXCCApplication::OnUiClick(const int & nID)
{
	switch (nID)
	{
		case static_cast<int>(DirectXCCApplication::UI_CTL_ID::CLOSE_BTN):
		{
			this->OnCloseButtonClick();
		}
		break;

		case static_cast<int>(DirectXCCApplication::UI_CTL_ID::MINIMIZE_BTN):
		{
			this->OnMinimizeButtonClick();
		}
		break;

		case static_cast<int>(DirectXCCApplication::UI_CTL_ID::CONV_BTN):
		{
			this->OnConvertButtonClick();
		}
		break;
	}
}
