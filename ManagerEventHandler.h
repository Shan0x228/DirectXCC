// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved

#pragma once

#include "UIAnimationHelper.h"
#include "DirectXCCApplication.h"

// Event handler object for manager status changes
class DirectXCCApplication;
class CManagerEventHandler : public CUIAnimationManagerEventHandlerBase<CManagerEventHandler>
{
public:

    static HRESULT CreateInstance (DirectXCCApplication *pMainWindow, IUIAnimationManagerEventHandler **ppManagerEventHandler) throw()
    {
        CManagerEventHandler *pManagerEventHandler;
        HRESULT hr = CUIAnimationCallbackBase::CreateInstance(ppManagerEventHandler, &pManagerEventHandler);
        if (SUCCEEDED(hr))
        {
            pManagerEventHandler->m_pMainWindow = pMainWindow;
        }
        
        return hr;
    }

    // IUIAnimationManagerEventHandler
    IFACEMETHODIMP OnManagerStatusChanged(UI_ANIMATION_MANAGER_STATUS newStatus, UI_ANIMATION_MANAGER_STATUS previousStatus)
    {
        HRESULT hr = S_OK;

        if (newStatus == UI_ANIMATION_MANAGER_BUSY)
        {
			//hr = this->m_pMainWindow->Invalidate();
        }

        return hr;
    }

protected:
    CManagerEventHandler()
      : m_pMainWindow(nullptr)
    {
    }

	DirectXCCApplication *m_pMainWindow;
};
