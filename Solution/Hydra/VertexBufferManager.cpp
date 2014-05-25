//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	VertexBufferManager.cpp
//	Description	:	Definition of CVertexBufferManager
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// This include.
#include "VertexBufferManager.h"

// Local includes.
#include "VertexBuffer.h"
#include "Utility.h"

// Library includes.
#include <d3dx9.h>
#include <cassert>

CVertexBufferManager::CVertexBufferManager()
: m_pDevice(0)
, m_pDeviceManager(0)
, m_arrpVertexBuffers(0)
, m_uiNumVertexBuffers(0)
{

}

CVertexBufferManager::~CVertexBufferManager()
{
	if (m_pDevice)
	{
		m_pDevice->Release();
	}

	for (unsigned int ui = 0; ui < m_uiNumVertexBuffers; ++ui)
	{
		delete m_arrpVertexBuffers[ui];	// Is the same as DeleteVertexBuffer(ui);
	}

	delete[] m_arrpVertexBuffers;
}

/**
*
* Initialises the vertex buffer manager.
* The vertex buffer manager is actually a manager of programatically built meshes.
* The reason for the name is to separate it from the "Mesh manager" which handles prebuilt meshes.
* This function must be called, and true returned, otherwise the vertex buffer manager is unusable.
*
* @author Jade Abbott
* @param _pDevice Interface to the GPU, which is required for creating vertex and index buffers.
* @param _pDeviceManager Used to handle most communication with the device.
*
*/
bool
CVertexBufferManager::Initialise(IDirect3DDevice9* _pDevice, CDeviceManager* _pDeviceManager)
{
	assert(_pDevice);
	assert(_pDeviceManager);

	if (m_pDevice)
	{
		m_pDevice->Release();
	}

	m_pDevice = _pDevice;
	m_pDevice->AddRef();

	m_pDeviceManager = _pDeviceManager;

	return true;
}

/**
*
* Handles creation of a vertex buffer.
* Returns an ID to get the vertex buffer out of this manager.
*
* @author Jade Abbott
* @param _dwVertexFVF The Flexible Vertex Format of the vertices used (e.g. D3DFVF_XYZ | D3DFVF_DIFFUSE).
* @param _ePrimitiveType The way the vertices are drawn, such as a line list or triangle strip.
* @param _uiTotalVertices The number of vertices in the vertex array.
* @param _uiTotalIndices The number of indices in the index array (set to zero if there are no indices).
* @param _uiVertexStride The size of each vertex.
* @param _pVertices Pointer to the first vertex in the array of vertices (this is kept, so do not delete afterwards).
* @param _pIndices Pointer to the first index in the array of indices (set to zero if there are no indices. Also, this is kept, so do not delete afterwards).
* @param _eIndexType The index format (e.g. D3DFMT_INDEX16 or D3DFMT_INDEX32).
* @param _krMaterial Const reference to the material used on the mesh (the original is copied by value).
* @param _bDynamicVertices True to make the vertices editable at runtime. Note that if an error occurs, the vertices will not be dynamic.
* @return ID used to get the vertex buffer from this manager. Is Utility::INVALID_ID if creation failed.
*
*/
unsigned int
CVertexBufferManager::CreateVertexBuffer(DWORD _dwVertexFVF,
										D3DPRIMITIVETYPE _ePrimitiveType,
										unsigned int _uiTotalVertices,
										unsigned int _uiTotalIndices,
										unsigned int _uiVertexStride,
										void* const _pVertices,
										void* const _pIndices,
										D3DFORMAT _eIndexType,
										const D3DMATERIAL9& _krMaterial,
										bool _bDynamicVertices)
{
	assert(m_pDevice);

	// Get an unused iteration of the array of pointers to vertex buffers...
	unsigned int uiIteration = GetUnusedBufferIteration();
	if (uiIteration == Utility::INVALID_ID)
	{
		delete[] _pVertices;
		delete[] _pIndices;
		return Utility::INVALID_ID;
	}

	CVertexBuffer* pVertexBuffer = new CVertexBuffer();
	if (!pVertexBuffer)
	{
		delete[] _pVertices;
		delete[] _pIndices;
		return Utility::INVALID_ID;
	}

	if (pVertexBuffer->Initialise(m_pDevice,
									_dwVertexFVF,
									_ePrimitiveType,
									_uiTotalVertices,
									_uiTotalIndices,
									_uiVertexStride,
									_pVertices,
									_eIndexType,
									_pIndices,
									_krMaterial,
									_bDynamicVertices))
	{
		//Add to CD3DRenderer's container of buffers.
		m_arrpVertexBuffers[uiIteration] = pVertexBuffer;
	}
	else	// Initialisation failed.
	{
		delete pVertexBuffer;	// Deletes the vertices and indices.
		return Utility::INVALID_ID;
	}

	return uiIteration;
}

/**
*
* Deletes the vertex buffer matching the provided ID.
*
* @author Jade Abbott
* @param _uiID The ID of the vertex buffer to delete.
* @return Void.
*
*/
void
CVertexBufferManager::DeleteVertexBuffer(unsigned int _uiID)
{
	if (_uiID == Utility::INVALID_ID)
		return;

	assert(_uiID < m_uiNumVertexBuffers);
	assert(m_arrpVertexBuffers);	// Should exist if m_uiNumMeshes is greater than zero (which allowed the above statement to pass).

	delete m_arrpVertexBuffers[_uiID];
	m_arrpVertexBuffers[_uiID] = 0;
}

/**
*
* Returns an unused iteration into the vertex buffer array.
* If no unused vertex buffer iteration is available, the array is resized first.
* If the array can't be resized, Utility::INVALID_ID is returned.
*
* @author Jade Abbott
* @return Iteration into m_arrpVertexBuffers that is unused.
*
*/
unsigned int
CVertexBufferManager::GetUnusedBufferIteration()
{
	// Find an unused buffer pointer in the array.
	for (unsigned int ui = 0; ui < m_uiNumVertexBuffers; ++ui)
	{
		if (!m_arrpVertexBuffers[ui])	// If unused...
			return ui;
	}

	// Else there are no unused pointers, so the array must be resized.
	CVertexBuffer** arrpVertexBuffers = new CVertexBuffer*[m_uiNumVertexBuffers + 1];
	if (!arrpVertexBuffers)
		return Utility::INVALID_ID;

	memcpy(arrpVertexBuffers, m_arrpVertexBuffers, sizeof(CVertexBuffer*) * m_uiNumVertexBuffers);
	arrpVertexBuffers[m_uiNumVertexBuffers] = 0;
	delete[] m_arrpVertexBuffers;
	m_arrpVertexBuffers = arrpVertexBuffers;
	++m_uiNumVertexBuffers;

	return m_uiNumVertexBuffers - 1;
}

/**
*
* @author Jade Abbott
*
*/
void
CVertexBufferManager::OnDeviceLost()
{
	for (unsigned int ui = 0; ui < m_uiNumVertexBuffers; ++ui)
	{
		if (m_arrpVertexBuffers[ui])
		{
			m_arrpVertexBuffers[ui]->ReleaseFromLostDevice();
		}
	}
}

/**
*
* @author Jade Abbott
*
*/
void
CVertexBufferManager::OnDeviceReset()
{
	assert(m_pDevice);

	for (unsigned int ui = 0; ui < m_uiNumVertexBuffers; ++ui)
	{
		if (m_arrpVertexBuffers[ui])
		{
			m_arrpVertexBuffers[ui]->InitialiseFromLostDevice(m_pDevice);
		}
	}
}