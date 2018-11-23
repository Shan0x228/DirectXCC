#include "UiRenderer.h"

// void InitD2D1() - метод инициализирует Direct2D.
void UiRenderer::InitD2D1()
{
	HRESULT hr{};
	
	if (hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &this->m_pD2D1Factory); !SUCCEEDED(hr))
		ExitProcess(EXIT_FAILURE);

	if (hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_pDWriteFactory), reinterpret_cast<IUnknown **>(&m_pDWriteFactory)); !SUCCEEDED(hr))
		ExitProcess(EXIT_FAILURE);
}

// void FreeD2D1() - метод высвобождает Direct2D.
void UiRenderer::FreeD2D1()
{
	this->FreeD2D1Resources();
	this->ReleaseComObj(this->m_pDWriteFactory);
	this->ReleaseComObj(this->m_pD2D1Factory);
}

// void CreateD2D1Resources() - метод инициализирует ресурсы для рисования.
void UiRenderer::CreateD2D1Resources()
{
	HRESULT hr{};

	D2D1_SIZE_U size = D2D1::SizeU(
		this->pApp->m_nAppWidth,
		this->pApp->m_nAppHeight
	);

	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(
			DXGI_FORMAT_B8G8R8A8_UNORM,
			D2D1_ALPHA_MODE_PREMULTIPLIED),
		0,
		0,
		D2D1_RENDER_TARGET_USAGE_NONE,
		D2D1_FEATURE_LEVEL_DEFAULT
	);

	if (hr = this->m_pD2D1Factory->CreateDCRenderTarget(&props, &this->m_pDCRT); !SUCCEEDED(hr))
		ExitProcess(EXIT_FAILURE);

	if (hr = this->m_pDCRT->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &this->m_pSolidBrush); !SUCCEEDED(hr))
		ExitProcess(EXIT_FAILURE);
}

// void FreeD2D1Resources() - метод высвобождает ресурсы для рисования.
void UiRenderer::FreeD2D1Resources()
{
	this->ReleaseComObj(this->m_pSolidBrush);
	this->ReleaseComObj(this->m_pTextFormat);
	this->ReleaseComObj(this->m_pDCRT);
}

// Конструктор.
UiRenderer::UiRenderer(DirectXCCApplication * pApp)
	: pApp(pApp)
{
	InitD2D1();
	CreateD2D1Resources();
	this->InitializeAnimation();
	this->CreateAnimationVariables();
}

// void StartDrawing() - метод, подготавливающий ресурсы DirectX к рисованию.
void UiRenderer::StartDrawing()
{
	this->m_pDCRT->BindDC(this->pApp->m_hWindowDC, &this->pApp->m_rWindowRect);
	this->m_pDCRT->BeginDraw();
	this->m_pDCRT->Clear(this->m_cWindowBackgroundColor);
}

// void StopDrawing() - метод, останавливающий процесс рисования.
void UiRenderer::StopDrawing()
{
	this->m_pDCRT->EndDraw();
}

// void FreeUiAnimation() - метод высвобождает ресурсы WAM
void UiRenderer::FreeUiAnimation()
{
	// Animated Variables
	this->ReleaseComObj(m_pDeltaVariable);

	// Animation
	this->ReleaseComObj(m_pAnimationManager);
	this->ReleaseComObj(m_pAnimationTimer);
	this->ReleaseComObj(m_pTransitionLibrary);
}

// Деструктор.
UiRenderer::~UiRenderer()
{
	this->FreeUiAnimation();
	this->FreeD2D1();
}
