#include "UiRenderer.h"
#include "ManagerEventHandler.h"

// HRESULT InitializeAnimation() - метод инициализирует WAM.
HRESULT UiRenderer::InitializeAnimation()
{
	// Create Animation Manager
	HRESULT hr = CoCreateInstance(CLSID_UIAnimationManager, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pAnimationManager));

	if (SUCCEEDED(hr))
	{
		// Create Animation Timer
		hr = CoCreateInstance(CLSID_UIAnimationTimer, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pAnimationTimer));

		if (SUCCEEDED(hr))
		{
			// Create Animation Transition Library
			hr = CoCreateInstance(CLSID_UIAnimationTransitionLibrary, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pTransitionLibrary));

			if (SUCCEEDED(hr))
			{
				// Create and set the ManagerEventHandler to start updating when animations are scheduled
				IUIAnimationManagerEventHandler *pManagerEventHandler;
				hr = CManagerEventHandler::CreateInstance(this->pApp, &pManagerEventHandler);

				if (SUCCEEDED(hr))
				{
					hr = m_pAnimationManager->SetManagerEventHandler(pManagerEventHandler);
					pManagerEventHandler->Release();
				}
			}
		}
	}

	return hr;
}

// HRESULT CreateAnimationVariables() - метод инициализирует ресурсы WAM.
HRESULT UiRenderer::CreateAnimationVariables()
{
	HRESULT hr = m_pAnimationManager->CreateAnimationVariable(0, &this->m_pDeltaVariable);
	if (SUCCEEDED(hr))
	{
		hr = this->m_pDeltaVariable->SetLowerBound(0);
		if (SUCCEEDED(hr))
		{
			hr = this->m_pDeltaVariable->SetUpperBound(255);
		}
	}

	return hr;
}

// TODO...
void UiRenderer::DeltaChanger()
{
	const UI_ANIMATION_SECONDS DURATION = 2;
	const DOUBLE ACCELERATION_RATIO = 0.5;
	const DOUBLE DECELERATION_RATIO = 0.5;

	// Create a storyboard
	IUIAnimationStoryboard* pStoryboard{};
	HRESULT hr = m_pAnimationManager->CreateStoryboard(&pStoryboard);

	if (SUCCEEDED(hr))
	{
		IUIAnimationTransition *pTransitionDeltaValue;
		double tmp_val{};
		this->m_pDeltaVariable->GetValue(&tmp_val);
		if (tmp_val == 255)
			hr = m_pTransitionLibrary->CreateAccelerateDecelerateTransition(DURATION, 0, ACCELERATION_RATIO, DECELERATION_RATIO, &pTransitionDeltaValue);
		else
			hr = m_pTransitionLibrary->CreateAccelerateDecelerateTransition(DURATION, 255, ACCELERATION_RATIO, DECELERATION_RATIO, &pTransitionDeltaValue);

		// Create transitions for the RGB animation variables

		if (SUCCEEDED(hr))
		{
			// Add transitions to the storyboard
			hr = pStoryboard->AddTransition(this->m_pDeltaVariable, pTransitionDeltaValue);

			if (SUCCEEDED(hr))
			{
				// Get the current time and schedule the storyboard for play

				UI_ANIMATION_SECONDS secondsNow;
				hr = m_pAnimationTimer->GetTime(&secondsNow);

				if (SUCCEEDED(hr))
				{
					hr = pStoryboard->Schedule(secondsNow);
				}
			}
		}
		pTransitionDeltaValue->Release();
	}
	pStoryboard->Release();
}
