//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	FogManager.inl
//	Description	:	Definition of CFogManager
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

/**
*
* Sets the colour of the fog.
*
* @author Jade Abbott
* @return void
*
*/
void
CFogManager::SetFogColour(DWORD _dwColour)
{
	assert(m_pDeviceManager);
	m_pDeviceManager->SetRenderState(D3DRS_FOGCOLOR, _dwColour);
}

/**
*
* Sets the beginning of the fog.
*
* @author Jade Abbott
* @return void
*
*/
void
CFogManager::SetFogStart(float _fStart)
{
	assert(m_pDeviceManager);
	assert(_fStart >= 0.0f);
	m_pDeviceManager->SetRenderState(D3DRS_FOGSTART, *reinterpret_cast<DWORD*>(&_fStart));
}

/**
*
* Sets the end of the fog.
*
* @author Jade Abbott
* @return void
*
*/
void
CFogManager::SetFogEnd(float _fEnd)
{
	assert(m_pDeviceManager);
	assert(_fEnd >= 0.0f);
	m_pDeviceManager->SetRenderState(D3DRS_FOGEND, *reinterpret_cast<DWORD*>(&_fEnd));
}

/**
*
* Sets the density of the fog (how quickly the fog cuts off view).
*
* @author Jade Abbott
* @return void
*
*/
void
CFogManager::SetFogDensity(float _fDensity)
{
	assert(m_pDeviceManager);
	assert(_fDensity >= 0.0f);
	m_pDeviceManager->SetRenderState(D3DRS_FOGDENSITY, *reinterpret_cast<DWORD*>(&_fDensity));
}