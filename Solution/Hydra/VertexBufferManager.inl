//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	VertexBufferManager.inl
//	Description	:	Definition of inline CVertexBufferManager functions.
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// Local includes.
#include "VertexBuffer.h"
#include "Utility.h"

// Library includes.
#include <cassert>

/**
*
* Returns the vertex buffer requested.
*
* @author Jade Abbott
* @param _uiID ID of the vertex buffer.
* @return Vertex buffer that matches the provided ID.
*
*/
CVertexBuffer*
CVertexBufferManager::GetVertexBuffer(unsigned int _uiID)
{
	assert(_uiID < m_uiNumVertexBuffers);
	assert(m_arrpVertexBuffers[_uiID]);
	return m_arrpVertexBuffers[_uiID];
}

/**
*
* Renders the vertex buffer requested.
* Can also limit the number of vertices rendered to the provided amount (optional parameter).
*
* @author Jade Abbott
* @param _uiID ID of the vertex buffer.
* @return _uiNumVerts Optional parameter to set the number of vertices to be drawn.
*
*/
void
CVertexBufferManager::Render(unsigned int _uiID, unsigned int _uiNumVerts)
{
	assert(m_pDeviceManager);
	
	if (_uiID == Utility::INVALID_ID)
		return;

	assert(m_arrpVertexBuffers[_uiID]);

	m_arrpVertexBuffers[_uiID]->Render(*m_pDeviceManager, _uiNumVerts);
}

/**
*
* Overloaded function to render a vertex buffer, when the vertex buffer is already in hand.
*
* @author Jade Abbott
* @param _rVertexBuffer Reference to the vertex buffer to draw.
* @return _uiNumVerts Optional parameter to set the number of vertices to be drawn.
*
*/
void
CVertexBufferManager::Render(CVertexBuffer& _rVertexBuffer, unsigned int _uiNumVerts)
{
	assert(m_pDeviceManager);

	_rVertexBuffer.Render(*m_pDeviceManager, _uiNumVerts);
}