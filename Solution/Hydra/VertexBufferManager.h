//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	VertexBufferManager.h
//	Description	:	Declaration of CVertexBufferManager
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

#pragma once
#ifndef __VERTEXBUFFER_MANAGER_H__
#define __VERTEXBUFFER_MANAGER_H__

// Library includes.
#include <d3dx9.h>

// Local includes.
#include "DeviceResetTarget.h"
class CVertexBuffer;
class CDeviceManager;
enum EIndexType;

// Library includes.
struct IDirect3DDevice9;

class CVertexBufferManager : public CDeviceResetTarget
{
	// Member functions.
public:
	CVertexBufferManager();
	virtual ~CVertexBufferManager();

	bool Initialise(IDirect3DDevice9* _pDevice, CDeviceManager* _pDeviceManager);

	unsigned int CreateVertexBuffer(DWORD _dwVertexFVF,
									D3DPRIMITIVETYPE _ePrimitiveType,
									unsigned int _uiTotalVertices,
									unsigned int _uiTotalIndices,
									unsigned int _uiVertexStride,
									void* const _pVertices,
									void* const _pIndices,
									D3DFORMAT _eIndexType,
									const D3DMATERIAL9& _krMaterial,
									bool _bDynamicVertices);

	void DeleteVertexBuffer(unsigned int _uiID);

	inline CVertexBuffer* GetVertexBuffer(unsigned int _uiID);

	inline void Render(unsigned int _uiID, unsigned int _uiNumVerts = 0);
	inline void Render(CVertexBuffer& _rVertexBuffer, unsigned int _uiNumVerts = 0);

protected:
	unsigned int GetUnusedBufferIteration();

	virtual void OnDeviceLost();
	virtual void OnDeviceReset();

private:

	// Member variables.
public:

protected:
	IDirect3DDevice9* m_pDevice;
	CDeviceManager* m_pDeviceManager;

	CVertexBuffer** m_arrpVertexBuffers;
	unsigned int m_uiNumVertexBuffers;

private:
};

#include "VertexBufferManager.inl"

#endif	// __VERTEXBUFFER_MANAGER_H__