//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	SurfaceManager.inl
//	Description	:	Definition of inline CSurfaceManager functions.
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// Library includes.
#include <cassert>

/**
*
* Creates a non-renderable texture.
*
* @author Jade Abbott
* @param _uiWidth Width of the render target surface.
* @param _uiHeight Height of the render target surface.
* @param _Format Format of the render target surface (e.g. D3DFMT_A8R8G8B8).
* @param _MemoryPool Which memory pool the surface is stored in.
* @return What the device returned.
*
*/
HRESULT
CSurfaceManager::CreateTexture(UINT _uiWidth, UINT _uiHeight, D3DFORMAT _Format, D3DPOOL _MemoryPool, IDirect3DTexture9** _ppOut)
{
	assert(m_pDevice);

	return m_pDevice->CreateTexture(_uiWidth,
									_uiHeight,
									1,
									0,
									_Format,
									_MemoryPool,
									_ppOut,
									NULL);
}

/**
*
* Deletes the surface matching the ID provided.
* Deleting nonexistent or already deleted surfaces is not allowed.
*
* @author Jade Abbott
* @param _uiID ID of the surface to be deleted.
*
*/
void
CSurfaceManager::DestroySurface(unsigned int _uiID)
{
	if (_uiID > m_uiNumSurfaces)
		return;

	if (m_arrpSurfaces)
	{
		if (m_arrpSurfaces[_uiID])
		{
			m_arrpSurfaces[_uiID]->Release();
			m_arrpSurfaces[_uiID] = 0;
		}
	}
}

/**
*
* Returns the surface matching the ID provided.
* Returns null pointer if surface requested does not exist.
*
* @author Jade Abbott
* @param _uiID ID of the surface to return.
* @return Pointer to the surface requested; Is null if surface doesn't exist.
*
*/
IDirect3DSurface9*
CSurfaceManager::GetSurface(unsigned int _uiID)
{
	assert(_uiID < m_uiNumSurfaces);
	assert(m_arrpSurfaces);	// Should exist if m_uiNumSurfaces is non-zero.
	return m_arrpSurfaces[_uiID];
}