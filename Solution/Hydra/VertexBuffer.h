//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	VertexBuffer.h
//	Description	:	Declaration of CVertexBuffer
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

#pragma once
#ifndef __HYDRA_VERTEXBUFFER_H__
#define __HYDRA_VERTEXBUFFER_H__

// Library includes.
#include <d3d9.h>

// Local includes.
#include "DeviceManager.h"

// Types.

// Constants.

// Prototypes.
struct TVertexBufferData
{
	void* m_pVertices;
	unsigned int m_uiVertexStride;
	void* m_pIndices;
	D3DFORMAT m_eIndexType;
	UINT m_uiNumVerts;
	UINT m_uiNumIndices;
	float m_fBoundingSphereRadius;
};

class CVertexBuffer
{
	// Member functions.
public:
	CVertexBuffer();
	~CVertexBuffer();

	bool Initialise(IDirect3DDevice9* _pDevice,
					DWORD _dwVertexFVF,
					D3DPRIMITIVETYPE _ePrimitiveType,
					unsigned int _uiTotalVerts,
					unsigned int _uiTotalIndices,
					unsigned int _uiStride,
					void* _pVertexData,
					D3DFORMAT _eIndexType,
					void* _pIndices,
					const D3DMATERIAL9& _krMaterial,
					bool _bDynamicVertices);

	void ReleaseFromLostDevice();
	bool InitialiseFromLostDevice(IDirect3DDevice9* _pDevice);

	void Render(CDeviceManager& _rDeviceManager, unsigned int _uiNumPrimitives = 0);

	unsigned int GetNumPrimitives() const;

	static unsigned int NumPrimitives(D3DPRIMITIVETYPE _ePrimitiveType, unsigned int _uiTotalIndicesOrVerts);

	const TVertexBufferData& GetVertexBufferData() const;

	void* GetDynamicVertices();
	void UpdateDynamicVertices(unsigned int _uiNumUpdated = 0);	// Updates device only when necessary.
	bool IsVerticesDynamic() const;

protected:

private:
	CVertexBuffer(const CVertexBuffer& _kr);
	CVertexBuffer& operator=(const CVertexBuffer& _kr);

	// Member variables.
public:

protected:
	IDirect3DVertexBuffer9* m_pVertexBuffer;
	IDirect3DIndexBuffer9* m_pIndexBuffer;

	TVertexBufferData m_MeshData;

	D3DMATERIAL9 m_Material;

	UINT m_uiNumPrimitives;

	DWORD m_dwFvf;

	D3DPRIMITIVETYPE m_ePrimitiveType;

	unsigned char m_ucFlags;

private:
};

#endif	// __HYDRA_VERTEXBUFFER_H__