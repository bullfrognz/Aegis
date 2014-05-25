//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	RadialMenu.inl
//	Description	:	Definition of inline CRadialMenu functions.
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// Library includes.
#include <cassert>

// Local includes.
#include "Utility.h"
#include "D3DRenderer.h"
#include "SurfaceManager.h"


/**
*
* Returns an editable pointer to the button's data.
* The point of this function is to set the information regarding each button.
*
* @author Jade Abbott
* @param _ucButton The button whose pointer will be obtained.
* @param _ppOut Will contain the address of the pointer.
* @return Pointer for the button data.
*
*/
TRadialMenuButtonData&
CRadialMenu::GetButtonData(unsigned char _ucButton)
{
	assert(m_arrButtonData);
	assert(_ucButton < m_ucNumButtons);
	return m_arrButtonData[_ucButton];
}

float
CRadialMenu::GetDrawPositionX() const
{
	return m_fDrawPositionX;
}

float
CRadialMenu::GetDrawPositionY() const
{
	return m_fDrawPositionY;
}

bool
CRadialMenu::CreateRenderTarget()
{
	assert(m_pRenderer);

	CSurfaceManager& rSurfaceManager = m_pRenderer->GetSurfaceManager();

	if (m_uiRenderTargetID != Utility::INVALID_ID)
	{
		rSurfaceManager.DestroySurface(m_uiRenderTargetID);
	}

	m_uiRenderTargetID = m_pRenderer->GetSurfaceManager().CreateRenderTarget(m_uiDiameter, m_uiDiameter, D3DFMT_A8R8G8B8, false);

	return m_uiRenderTargetID != Utility::INVALID_ID;
}