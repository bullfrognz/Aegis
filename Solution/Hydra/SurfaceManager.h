//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	SurfaceManager.h
//	Description	:	Declaration of CSurfaceManager
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

#pragma once
#ifndef __SURFACEMANAGER_H__
#define __SURFACEMANAGER_H__

// Library includes.
#include <d3dx9.h>

class CSurfaceManager
{
	// Member functions.
public:
	CSurfaceManager();
	~CSurfaceManager();

	bool Initialise(IDirect3DDevice9* _pDevice, D3DMULTISAMPLE_TYPE _BBufferMsampleType, DWORD _BBufferMsampleQuality);

	unsigned int CreateStencil(UINT _uiWidth, UINT _uiHeight, D3DFORMAT _Format, bool _bDiscard = false);
	unsigned int CreateRenderTarget(UINT _uiWidth, UINT _uiHeight, D3DFORMAT _Format, bool _bLockable = false);
	unsigned int CreatePlainSurface(UINT _uiWidth, UINT _uiHeight, D3DFORMAT _Format, D3DPOOL _MemoryPool);
	inline HRESULT CreateTexture(UINT _uiWidth, UINT _uiHeight, D3DFORMAT _Format, D3DPOOL _MemoryPool, IDirect3DTexture9** _ppOut);
	inline void DestroySurface(unsigned int _uiID);
	inline IDirect3DSurface9* GetSurface(unsigned int _uiID);

protected:
	unsigned int GetFreeElement();

private:

	// Member data.
public:

protected:
	IDirect3DDevice9* m_pDevice;

	D3DMULTISAMPLE_TYPE m_BBufferMsampleType;
	DWORD m_BBufferMsampleQuality;
	
	IDirect3DSurface9** m_arrpSurfaces;
	unsigned int m_uiNumSurfaces;

private:
};

#include "SurfaceManager.inl"

#endif	// __SURFACEMANAGER_H__