//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	VertexBuffer.cpp
//	Description	:	Definition of CVertexBuffer
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// Library includes.
#include <cassert>

// Local includes.
#include "Vertex.h"
#include "Utility.h"

// This include.
#include "VertexBuffer.h"

#define FLG_DYNAMIC_VERTICES Utility::B1
#define FLG_UPDATE_VERTICES Utility::B2

CVertexBuffer::CVertexBuffer()
: m_pVertexBuffer(0)
, m_pIndexBuffer(0)
, m_uiNumPrimitives(0)
, m_dwFvf(0)
, m_ePrimitiveType(D3DPT_POINTLIST)
, m_ucFlags(0)
{
	ZeroMemory(&m_MeshData, sizeof(TVertexBufferData));
	ZeroMemory(&m_Material, sizeof(D3DMATERIAL9));
}

CVertexBuffer::~CVertexBuffer()
{
	if (m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = 0;
	}

	if (m_pIndexBuffer)
	{
		m_pIndexBuffer->Release();
		m_pIndexBuffer = 0;
	}

	delete[] reinterpret_cast<CVertex*>(m_MeshData.m_pVertices);	// Heap corruption error if attempting to delete void*
	delete[] m_MeshData.m_pIndices;
}

/**
*
* Initialises this vertex buffer.
*
* @author Jade Abbott
* @param _pDevice Required to create the vertex and index buffers on the graphics card.
* @param _dwVertexFVF The Flexible Vertex Format of the vertices used (e.g. D3DFVF_XYZ | D3DFVF_DIFFUSE).
* @param _ePrimitiveType The way the vertices are drawn, such as a line list or triangle strip.
* @param _uiTotalVertices The number of vertices in the vertex array.
* @param _uiTotalIndices The number of indices in the index array (set to zero if there are no indices).
* @param _uiStride The size of each vertex.
* @param _pVertexData Pointer to the first vertex in the array of vertices (this is kept, so do not delete afterwards).
* @param _eIndexType The index format (e.g. D3DFMT_INDEX16 or D3DFMT_INDEX32).
* @param _pIndexData Pointer to the first index in the array of indices (set to zero if there are no indices. Also, this is kept, so do not delete afterwards).
* @param _krMaterial Const reference to the material used on the mesh (the original is copied by value).
* @param _bDynamicVertices True to make the vertices editable at runtime. Note that if an error occurs, the vertices will not be dynamic.
* @return True if initialisation was successful.
*
*/
bool
CVertexBuffer::Initialise(IDirect3DDevice9* _pDevice,
						DWORD _dwVertexFVF,
						D3DPRIMITIVETYPE _ePrimitiveType,
						unsigned int _uiTotalVerts,
						unsigned int _uiTotalIndices,
						unsigned int _uiStride,
						void* _pVertexData,
						D3DFORMAT _eIndexType,
						void* _pIndices,
						const D3DMATERIAL9& _krMaterial,
						bool _bDynamicVertices)
{
	assert(_pDevice);
	assert(_ePrimitiveType == D3DPT_POINTLIST ? _eIndexType == D3DFMT_UNKNOWN : true);	// Pointlists can not be used with indices.
	assert(_uiTotalVerts);

	HRESULT hr = 0;

	m_dwFvf = _dwVertexFVF;
	m_MeshData.m_pVertices = _pVertexData;
	m_MeshData.m_uiVertexStride = _uiStride;
	m_MeshData.m_pIndices = _pIndices;
	m_MeshData.m_eIndexType = _eIndexType;
	m_MeshData.m_uiNumVerts = _uiTotalVerts;
	m_MeshData.m_uiNumIndices = _uiTotalIndices;
	MathUtility::CalculateBoundingSphere(m_MeshData.m_fBoundingSphereRadius, _pVertexData, _uiStride, _uiTotalVerts);
	m_Material = _krMaterial;
	m_ePrimitiveType = _ePrimitiveType;

	// Find number of primitives.
	m_uiNumPrimitives = NumPrimitives(_ePrimitiveType, _uiTotalIndices ? _uiTotalIndices : _uiTotalVerts);
	
	// Create index buffer if required.
	if (_uiTotalIndices > 0)
	{
		assert(!m_pIndexBuffer);
		
		unsigned int uiIndexNumBytes = 0;
		
		if (_eIndexType == D3DFMT_INDEX16)
		{
			uiIndexNumBytes = 2;
		}
		else if (_eIndexType == D3DFMT_INDEX32)
		{
			uiIndexNumBytes = 4;
		}
		else	// D3DFMT_UNKNOWN.
		{
			assert(false);
			return false;
		}

		// Create index buffer.
		hr = _pDevice->CreateIndexBuffer(_uiTotalIndices * uiIndexNumBytes, D3DUSAGE_WRITEONLY, _eIndexType, D3DPOOL_DEFAULT, &m_pIndexBuffer, NULL);

		if (SUCCEEDED(hr))	// If index buffer was created successfully...
		{
			void* pTempIndexAccess = 0;

			// Populate index buffer with provided array of indices.
			hr = m_pIndexBuffer->Lock(0, _uiTotalIndices * uiIndexNumBytes, &pTempIndexAccess, 0);

			if (SUCCEEDED(hr))	// If locking was successful...
			{
				memcpy(pTempIndexAccess, _pIndices, _uiTotalIndices * uiIndexNumBytes);	// Copy the indices over.

				m_pIndexBuffer->Unlock();
			}
			else
			{
				assert(false);

				return false;
			}
		}
		else
		{
			assert(false);

			return false;
		}
	}

	// Create vertex buffer.
	if (_bDynamicVertices)
	{
		hr = _pDevice->CreateVertexBuffer(_uiTotalVerts * _uiStride, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, _dwVertexFVF, D3DPOOL_DEFAULT, &m_pVertexBuffer, 0);

		if (SUCCEEDED(hr))
		{
			m_ucFlags = m_ucFlags | FLG_DYNAMIC_VERTICES;
		}
		else
		{
			if (m_pVertexBuffer)
			{
				m_pVertexBuffer->Release();
			}

			_bDynamicVertices = false;
		}
	}

	if (!_bDynamicVertices)	// Done separately from if statement above incase statement above changes type from dynamic to non-dynamic.
	{
		assert(!m_pVertexBuffer);
		hr = _pDevice->CreateVertexBuffer(_uiTotalVerts * _uiStride, D3DUSAGE_WRITEONLY, _dwVertexFVF, D3DPOOL_MANAGED, &m_pVertexBuffer, 0);
	}

	if (SUCCEEDED(hr))
	{
		void* pTempVertexAccess = 0;

		hr = m_pVertexBuffer->Lock(0, _uiTotalVerts * _uiStride, &pTempVertexAccess, 0);

		if (SUCCEEDED(hr))
		{
			memcpy(pTempVertexAccess, _pVertexData, _uiTotalVerts * _uiStride);

			m_pVertexBuffer->Unlock();
		}
		else
		{
			assert(false);

			return false;
		}
	}
	else
	{
		assert(false);

		return false;
	}

	return true;
}

/**
*
* @author Jade Abbott
*
*/
void
CVertexBuffer::ReleaseFromLostDevice()
{
	if (m_pVertexBuffer)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = 0;
	}
	
	if (m_pIndexBuffer)
	{
		m_pIndexBuffer->Release();
		m_pIndexBuffer = 0;
	}
}

/**
*
* Restores this vertex buffer when the device is lost.
*
* @author Jade Abbott
* @param _pDevice Required to restart the vertex and index buffers.
* @return True if recovery was successful.
*
*/
bool
CVertexBuffer::InitialiseFromLostDevice(IDirect3DDevice9* _pDevice)
{
	assert(_pDevice);
	HRESULT hr = 0;

	assert(!m_pIndexBuffer);
	assert(!m_pVertexBuffer);
	
	// Create index buffer if required.
	if (m_MeshData.m_uiNumIndices > 0)
	{
		unsigned int uiIndexNumBytes = 0;
		
		if (m_MeshData.m_eIndexType == D3DFMT_INDEX16)
		{
			uiIndexNumBytes = 2;
		}
		else if (m_MeshData.m_eIndexType == D3DFMT_INDEX32)
		{
			uiIndexNumBytes = 4;
		}
		else	// D3DFMT_UNKNOWN.
		{
			assert(false);
			return false;
		}

		// Create index buffer.
		hr = _pDevice->CreateIndexBuffer(m_MeshData.m_uiNumIndices * uiIndexNumBytes, D3DUSAGE_WRITEONLY, m_MeshData.m_eIndexType, D3DPOOL_DEFAULT, &m_pIndexBuffer, NULL);

		if (SUCCEEDED(hr))	// If index buffer was created successfully...
		{
			void* pTempIndexAccess = 0;

			// Populate index buffer with provided array of indices.
			hr = m_pIndexBuffer->Lock(0, m_MeshData.m_uiNumIndices * uiIndexNumBytes, &pTempIndexAccess, 0);

			if (SUCCEEDED(hr))	// If locking was successful...
			{
				memcpy(pTempIndexAccess, m_MeshData.m_pIndices, m_MeshData.m_uiNumIndices * uiIndexNumBytes);	// Copy the indices over.

				m_pIndexBuffer->Unlock();
			}
			else
			{
				assert(false);
				return false;
			}
		}
		else
		{
			assert(false);
			return false;
		}
	}

	// Create vertex buffer.
	if (m_ucFlags & FLG_DYNAMIC_VERTICES)
	{
		hr = _pDevice->CreateVertexBuffer(m_MeshData.m_uiNumVerts * m_MeshData.m_uiVertexStride, D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY, m_dwFvf, D3DPOOL_DEFAULT, &m_pVertexBuffer, 0);

		if (FAILED(hr))
		{
			if (m_pVertexBuffer)
			{
				m_pVertexBuffer->Release();
				m_pVertexBuffer = 0;
			}

			m_ucFlags = m_ucFlags ^ FLG_DYNAMIC_VERTICES;
		}
	}

	if (!(m_ucFlags & FLG_DYNAMIC_VERTICES))	// Done separately from if statement above incase statement above changes type from dynamic to non-dynamic.
	{
		assert(!m_pVertexBuffer);
		hr = _pDevice->CreateVertexBuffer(m_MeshData.m_uiNumVerts * m_MeshData.m_uiVertexStride, D3DUSAGE_WRITEONLY, m_dwFvf, D3DPOOL_MANAGED, &m_pVertexBuffer, 0);
	}

	if (SUCCEEDED(hr))
	{
		void* pTempVertexAccess = 0;

		hr = m_pVertexBuffer->Lock(0, m_MeshData.m_uiNumVerts * m_MeshData.m_uiVertexStride, &pTempVertexAccess, 0);

		if (SUCCEEDED(hr))
		{
			memcpy(pTempVertexAccess, m_MeshData.m_pVertices, m_MeshData.m_uiNumVerts * m_MeshData.m_uiVertexStride);

			m_pVertexBuffer->Unlock();
		}
		else
		{
			assert(false);

			return false;
		}
	}
	else
	{
		assert(false);

		return false;
	}

	return true;
}

/**
*
* Renders the mesh.
*
* @author Jade Abbott
* @param _rDeviceManager The device that will be used to render with.
* @param _uiNumVerts The number of vertices to render; Zero will render all vertices.
* @return Void.
*
*/
void
CVertexBuffer::Render(CDeviceManager& _rDeviceManager, unsigned int _uiNumVerts)
{
	assert(m_pVertexBuffer);
	assert(_uiNumVerts <= m_MeshData.m_uiNumVerts);

	// If index buffer: Set indices on device.
	if (m_pIndexBuffer)
		_rDeviceManager.SetIndices(m_pIndexBuffer);
	
	// Set stream source on device.
	_rDeviceManager.SetStreamSource(m_pVertexBuffer, m_MeshData.m_uiVertexStride);

	// Set FVF on device.
	_rDeviceManager.SetFVF(m_dwFvf);

	// Set material on device.
	_rDeviceManager.SetMaterial(&m_Material);

	// Update vertices if required (dynamic buffers).
	if (m_ucFlags & FLG_UPDATE_VERTICES)
	{
		assert(m_ucFlags & FLG_DYNAMIC_VERTICES);

		m_ucFlags = (m_ucFlags | FLG_UPDATE_VERTICES) ^ FLG_UPDATE_VERTICES;	// Vertices will be updated (if possible).

		// Upload vertex data to device.
		void* pTempVertexAccess = 0;
		HRESULT hr = m_pVertexBuffer->Lock(0, (_uiNumVerts ? _uiNumVerts : m_MeshData.m_uiNumVerts) * m_MeshData.m_uiVertexStride, &pTempVertexAccess, D3DLOCK_DISCARD);

		if (SUCCEEDED(hr))
		{
			memcpy(pTempVertexAccess, m_MeshData.m_pVertices, (_uiNumVerts ? _uiNumVerts : m_MeshData.m_uiNumVerts) * m_MeshData.m_uiVertexStride);
			m_pVertexBuffer->Unlock();
		}
	}
	
	if (m_pIndexBuffer)	// If indices exist...
	{
		assert(m_ePrimitiveType != D3DPT_POINTLIST);
		_rDeviceManager.DrawIndexedPrimitive(m_ePrimitiveType, _uiNumVerts ? _uiNumVerts : m_MeshData.m_uiNumVerts, m_uiNumPrimitives);
	}
	else	// No indices...
	{
		_rDeviceManager.DrawPrimitive(m_ePrimitiveType, _uiNumVerts ? NumPrimitives(m_ePrimitiveType, _uiNumVerts) : m_uiNumPrimitives);
	}
}

/**
*
* Returns the number of primitives this mesh will render (number of individual (but visible) faces).
*
* @author Jade Abbott
* @return Number of primitives this mesh will draw.
*
*/
unsigned int
CVertexBuffer::GetNumPrimitives() const
{
	assert(m_uiNumPrimitives > 0);
	return m_uiNumPrimitives;
}

/**
*
* Returns the number of primitives for a provided primitive type and vertex/index count.
*
* @author Jade Abbott
* @param _ePrimitiveType The primitive type (line list, triangle strip, point list, etc).
* @param _uiTotalIndicesOrVerts For an indexed mesh, provide the number of indices, otherwise provide the number of vertices.
* @return Number of primitives for a provided primitive type and vertex/index count.
*
*/
unsigned int
CVertexBuffer::NumPrimitives(D3DPRIMITIVETYPE _ePrimitiveType, unsigned int _uiTotalIndicesOrVerts)
{
	switch (_ePrimitiveType)
	{
	case D3DPT_POINTLIST:
		return _uiTotalIndicesOrVerts;
		break;

	case D3DPT_LINELIST:
		return _uiTotalIndicesOrVerts / 2;
		break;

	case D3DPT_LINESTRIP:
		return _uiTotalIndicesOrVerts - 1;
		break;

	case D3DPT_TRIANGLELIST:
		return _uiTotalIndicesOrVerts / 3;
		break;

	case D3DPT_TRIANGLESTRIP:	// Fall through.
	case D3DPT_TRIANGLEFAN:
		return _uiTotalIndicesOrVerts - 2;
		break;

	default:
		assert(false);
		return 0;
		break;
	}
}

/**
*
* Provides access to the meshes data, but is uneditable.
*
* @author Jade Abbott
* @return Const reference to this meshes data.
*
*/
const TVertexBufferData&
CVertexBuffer::GetVertexBufferData() const
{
	return m_MeshData;
}

/**
*
* Returns a pointer to the RAM copy of this vertex buffer's vertices.
* Is only allowed if the vertices are dynamic.
*
* @author Jade Abbott
* @return Void pointer to the RAM copy of the vertices for this mesh.
*
*/
void*
CVertexBuffer::GetDynamicVertices()
{
	assert(m_ucFlags & FLG_DYNAMIC_VERTICES);

	return m_MeshData.m_pVertices;
}

/**
*
* Updates the vertices on the device using the vertices on RAM.
*
* @author Jade Abbott
* @param If zero, the entire buffer will be updated; If non-zero, that many vertices (from the front) will be updated.
* @return Void.
*
*/
void
CVertexBuffer::UpdateDynamicVertices(unsigned int _uiNumUpdated)
{
	assert(m_ucFlags & FLG_DYNAMIC_VERTICES);	// Should not be called if vertices are not dynamic.
	assert(_uiNumUpdated <= m_MeshData.m_uiNumVerts);

	if (_uiNumUpdated)	// If a non-zero value was provided...
	{
		// Upload vertex data to device.
		void* pTempVertexAccess = 0;
		HRESULT hr = m_pVertexBuffer->Lock(0, _uiNumUpdated * m_MeshData.m_uiVertexStride, &pTempVertexAccess, D3DLOCK_DISCARD);

		if (SUCCEEDED(hr))
		{
			memcpy(pTempVertexAccess, m_MeshData.m_pVertices, _uiNumUpdated * m_MeshData.m_uiVertexStride);

			m_pVertexBuffer->Unlock();
		}
	}
	else
	{
		m_ucFlags = m_ucFlags | FLG_UPDATE_VERTICES;
	}
}

/**
*
* Returns true if this meshes vertices are dynamic (can be edited at runtime).
*
* @author Jade Abbott
* @return True if this meshes vertices are dynamic (can be edited at runtime).
*
*/
bool
CVertexBuffer::IsVerticesDynamic() const
{
	return !!(m_ucFlags & FLG_DYNAMIC_VERTICES);
}