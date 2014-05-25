#pragma once

#ifndef __VERTEXNORMAL_H__
#define __VERTEXNORMAL_H__

// Library includes.
#include <d3dx9.h>

// Local includes.
#include "Vertex.h"

// Types

// Constants

// Prototypes.
class CVertexNormal : public CVertex
{
	// Member functions.
public:
	CVertexNormal();
	CVertexNormal(const D3DXVECTOR3& krVecPos, const D3DXVECTOR3& krVecNormal);
	~CVertexNormal();
	
	DWORD GetFVF() const;
	unsigned int GetSizeOf() const;

	void SetNormal(const D3DXVECTOR3& _krVecNormal);
	void SetNormal(const float _kfX, const float _kfY, const float _kfZ);
	void AddNormal(const D3DXVECTOR3& _krVecNormal);	// Adds the provided normal to the existing normal.
	void NormaliseNormal();	// Normal length = 1

	void operator=(const CVertexNormal& _rhs);

protected:

private:

	// Member variables.
public:

protected:
	D3DXVECTOR3 m_vecNormal;	// Orientation of the vertex; Should be of unit length.

private:
};

#endif	// __VERTEXNORMAL_H__