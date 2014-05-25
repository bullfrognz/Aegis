//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	SurfaceManager.cpp
//	Description	:	Definition of CSurfaceManager
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// This include.
#include "SurfaceManager.h"

// Local includes.
#include "Utility.h"

// Library includes.
#include <cassert>

CSurfaceManager::CSurfaceManager()
: m_pDevice(0)
, m_BBufferMsampleType(D3DMULTISAMPLE_NONE)
, m_BBufferMsampleQuality(0)
, m_arrpSurfaces(0)
, m_uiNumSurfaces(0)
{

}

CSurfaceManager::~CSurfaceManager()
{
	if (m_pDevice)
	{
		m_pDevice->Release();
	}

	for (unsigned int ui = 0; ui < m_uiNumSurfaces; ++ui)
	{
		if (m_arrpSurfaces[ui])
		{
			m_arrpSurfaces[ui]->Release();
		}
	}
	delete[] m_arrpSurfaces;
}

/**
*
* Initialises the surface manager.
*
* @author Jade Abbott
* @param _pDevice The rendering device (needed to create surfaces).
* @param _BBufferMsampleType The back buffer's multisample type.
* @param _BBufferMsampleQuality The back buffer's multisample quality.
* @return True if initialisation was successful.
*
*/
bool
CSurfaceManager::Initialise(IDirect3DDevice9* _pDevice, D3DMULTISAMPLE_TYPE _BBufferMsampleType, DWORD _BBufferMsampleQuality)
{
	assert(_pDevice);

	if (m_pDevice)
	{
		m_pDevice->Release();
	}

	m_pDevice = _pDevice;
	_pDevice->AddRef();

	m_BBufferMsampleType = _BBufferMsampleType;
	m_BBufferMsampleQuality = _BBufferMsampleQuality;

	return true;
}

/**
*
* Creates a stencil surface,
* and returns an ID that can be used to fetch the surface from this manager.
* The surface created is compatible with the back buffer.
*
* @author Jade Abbott
* @param _uiWidth Width of the stencil surface.
* @param _uiHeight Height of the stencil surface.
* @param _Format Format of the stencil surface (e.g. D3DFMT_D24S8)
* @param _bDiscard True will invalidate the stencil buffer after each frame.
* @return ID used on this surface manager to get the stencil surface.
*
*/
unsigned int
CSurfaceManager::CreateStencil(UINT _uiWidth, UINT _uiHeight, D3DFORMAT _Format, bool _bDiscard)
{
	assert(m_pDevice);

	unsigned int uiElement = GetFreeElement();
	if (uiElement != Utility::INVALID_ID)
	{
		if (FAILED(m_pDevice->CreateDepthStencilSurface(_uiWidth,
														_uiHeight,
														_Format,
														m_BBufferMsampleType,
														m_BBufferMsampleQuality,
														_bDiscard ? TRUE : FALSE,
														&m_arrpSurfaces[uiElement],
														NULL)))
		{
			return Utility::INVALID_ID;
		}
	}

	return uiElement;
}

/**
*
* Creates a render target that can be drawn to in place of the back buffer,
* and returns an ID that can be used to fetch the surface from this manager.
* The surface created is compatible with the default back buffer (multisampling anyway).
*
* @author Jade Abbott
* @param _uiWidth Width of the render target surface.
* @param _uiHeight Height of the render target surface.
* @param _Format Format of the render target surface (e.g. D3DFMT_A8R8G8B8)
* @param _bLockable True will allow the render target to be locked and accessed,
*					but the better method is to copy to and from another surface.
* @return ID used on this surface manager to get this render target.
*
*/
unsigned int
CSurfaceManager::CreateRenderTarget(UINT _uiWidth, UINT _uiHeight, D3DFORMAT _Format, bool _bLockable)
{
	assert(m_pDevice);

	unsigned int uiElement = GetFreeElement();
	if (uiElement != Utility::INVALID_ID)
	{
		if (FAILED(m_pDevice->CreateRenderTarget(_uiWidth,
												 _uiHeight,
												 _Format,
												 m_BBufferMsampleType,
												 m_BBufferMsampleQuality,
												 _bLockable ? TRUE : FALSE,
												 &m_arrpSurfaces[uiElement],
												 NULL)))
		{
			return Utility::INVALID_ID;
		}
	}

	return uiElement;
}

/**
*
* Creates a non-renderable surface (off-screen plain surface).
*
* @author Jade Abbott
* @param _uiWidth Width of the render target surface.
* @param _uiHeight Height of the render target surface.
* @param _Format Format of the render target surface (e.g. D3DFMT_A8R8G8B8).
* @param _MemoryPool Which memory pool the surface is stored in.
* @return ID used on this surface manager to get this plain surface.
*
*/
unsigned int
CSurfaceManager::CreatePlainSurface(UINT _uiWidth, UINT _uiHeight, D3DFORMAT _Format, D3DPOOL _MemoryPool)
{
	assert(m_pDevice);

	unsigned int uiElement = GetFreeElement();
	if (uiElement != Utility::INVALID_ID)
	{
		if (FAILED(m_pDevice->CreateOffscreenPlainSurface(_uiWidth,
														  _uiHeight,
														  _Format,
														  _MemoryPool,
														  &m_arrpSurfaces[uiElement],
														  NULL)))
		{
			return Utility::INVALID_ID;
		}
	}

	return uiElement;
}

/**
*
* Returns an iteration of m_arrpSurfaces that will point to a free element.
* Resizes array if necessary.
* Returns Utility::INVALID_ID if impossible to return free element.
*
* @author Jade Abbott
* @return Number to dereference m_arrpSurfaces with to get a free pointer.
*
*/
unsigned int
CSurfaceManager::GetFreeElement()
{
	for (unsigned int ui = 0; ui < m_uiNumSurfaces; ++ui)
	{
		if (!m_arrpSurfaces[ui])
			return ui;
	}

	IDirect3DSurface9** arrpNewSurfaces = new IDirect3DSurface9*[m_uiNumSurfaces + 1];
	if (!arrpNewSurfaces)
		return Utility::INVALID_ID;

	memcpy(arrpNewSurfaces, m_arrpSurfaces, sizeof(IDirect3DSurface9*) * m_uiNumSurfaces);
	arrpNewSurfaces[m_uiNumSurfaces] = 0;
	delete[] m_arrpSurfaces;
	m_arrpSurfaces = arrpNewSurfaces;
	++m_uiNumSurfaces;

	return m_uiNumSurfaces - 1;
}