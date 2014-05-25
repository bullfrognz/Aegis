//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	FogManager.cpp
//	Description	:	Definition of CFogManager
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//


// Library includes.
#include <cassert>

// Local includes.
#include "Utility.h"

// This include.
#include "FogManager.h"

#define FLG_FOGENABLED			Utility::B1
#define FLG_FOGTABLE_SUPPORTED	Utility::B2	/* Pixel fog */
#define FLG_FOGVERTEX_SUPPORTED	Utility::B3
#define FLG_FOGRANGE_SUPPORTED	Utility::B4
#define FLG_FOGRANGE			Utility::B5
#define FLG_WFOG_SUPPORTED		Utility::B6

CFogManager::CFogManager()
: m_pDeviceManager(0)
, m_ucFlags(0)
{

}

CFogManager::~CFogManager()
{

}

/**
*
* Initialises the fog manager.
*
* @author Jade Abbott
* @return True if initialisation was successful.
*
*/
bool
CFogManager::Initialise(CDeviceManager* _pDeviceManager, DWORD _dwRasterCaps)
{
	assert(_pDeviceManager);
	m_pDeviceManager = _pDeviceManager;

	// Fog support.
	if (_dwRasterCaps & D3DPRASTERCAPS_FOGVERTEX)	// Vertex fog supported...
		m_ucFlags = m_ucFlags | FLG_FOGVERTEX_SUPPORTED;

	if (_dwRasterCaps & D3DPRASTERCAPS_FOGTABLE)	// Pixel fog supported...
		m_ucFlags = m_ucFlags | FLG_FOGTABLE_SUPPORTED;

	if (_dwRasterCaps & D3DPRASTERCAPS_FOGRANGE)	// Ranged fog supported...
		m_ucFlags = m_ucFlags | FLG_FOGRANGE_SUPPORTED;

	if (_dwRasterCaps & D3DPRASTERCAPS_WFOG)	// W fog supported...
		m_ucFlags = m_ucFlags | FLG_WFOG_SUPPORTED;

	return true;
}

/**
*
* Returns true if vertex-based fog is supported.
*
* @author Jade Abbott
* @return True if vertex-based fog is supported.
*
*/
bool
CFogManager::IsVertexFogSupported() const
{
	return !!(m_ucFlags & FLG_FOGVERTEX_SUPPORTED);
}

/**
*
* Returns true if pixel-based fog is supported.
*
* @author Jade Abbott
* @return True if pixel-based fog is supported.
*
*/
bool
CFogManager::IsPixelFogSupported() const
{
	return !!(m_ucFlags & FLG_FOGTABLE_SUPPORTED);
}

/**
*
* Returns true if high quality fog is available.
*
* @author Jade Abbott
* @return True if high quality fog is available.
*
*/
bool
CFogManager::IsRangedFogSupported() const
{
	return !!(m_ucFlags & FLG_FOGRANGE_SUPPORTED);
}

/**
*
* Set the use of fog on or off.
*
* @author Jade Abbott
* @return void
*
*/
void
CFogManager::EnableFog(bool _bEnabled)
{
	assert(m_pDeviceManager);

	if (_bEnabled == !!(m_ucFlags & FLG_FOGENABLED))
		return;	// Already enabled/disabled.

	if (_bEnabled)
	{
		m_ucFlags = m_ucFlags | FLG_FOGENABLED;
		m_pDeviceManager->SetRenderState(D3DRS_FOGENABLE, TRUE);
	}
	else
	{
		m_ucFlags = m_ucFlags ^ FLG_FOGENABLED;
		m_pDeviceManager->SetRenderState(D3DRS_FOGENABLE, FALSE);
	}
}

/**
*
* Returns true if fog is enabled.
*
* @author Jade Abbott
* @return True if fog is enabled.
*
*/
bool
CFogManager::IsFogEnabled() const
{
	return !!(m_ucFlags & FLG_FOGENABLED);
}

/**
*
* Enable/disable the use of high quality fog.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CFogManager::EnableRangedFog(bool _bEnabled)
{
	assert(m_pDeviceManager);

	if (!(m_ucFlags & FLG_FOGRANGE_SUPPORTED) || _bEnabled == !!(m_ucFlags & FLG_FOGRANGE))	// Fog range is not supported; Already enabled/disabled...
		return;

	if (_bEnabled)
	{
		m_ucFlags = m_ucFlags | FLG_FOGRANGE;
		m_pDeviceManager->SetRenderState(D3DRS_RANGEFOGENABLE, TRUE);
	}
	else
	{
		m_ucFlags = m_ucFlags ^ FLG_FOGRANGE;
		m_pDeviceManager->SetRenderState(D3DRS_RANGEFOGENABLE, FALSE);
	}
}

/**
*
* Returns true if high quality fog is enabled.
*
* @author Jade Abbott
* @return True if high quality fog is enabled.
*
*/
bool
CFogManager::IsRangedFogEnabled() const
{
	return (!!(m_ucFlags & FLG_FOGRANGE));
}

/**
*
* Sets the method of vertex fog used.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CFogManager::SetVertexFogMode(D3DFOGMODE _eFogMode)
{
	assert(m_pDeviceManager);
	assert(_eFogMode != D3DFOG_FORCE_DWORD);

	if (!(m_ucFlags & FLG_FOGVERTEX_SUPPORTED))	// If not supported...
		return;

	m_pDeviceManager->SetRenderState(D3DRS_FOGVERTEXMODE, _eFogMode);
}

/**
*
* Sets the method of index/table/pixel fog used.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CFogManager::SetPixelFogMode(D3DFOGMODE _eFogMode)
{
	assert(m_pDeviceManager);
	assert(_eFogMode != D3DFOG_FORCE_DWORD);

	if (!(m_ucFlags & FLG_FOGTABLE_SUPPORTED))	// If not supported...
		return;

	m_pDeviceManager->SetRenderState(D3DRS_FOGTABLEMODE, _eFogMode);
}