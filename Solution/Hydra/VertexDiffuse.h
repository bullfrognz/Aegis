//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	VertexDiffuse.h
//	Description	:	Declaration of CVertexDiffuse
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

#pragma once
#ifndef __VERTEXDIFFUSE_H__
#define __VERTEXDIFFUSE_H__

// Library includes.
#include <d3dx9.h>

// Local includes.
#include "Vertex.h"

class CVertexDiffuse : public CVertex
{
	// Member functions.
public:
	CVertexDiffuse();
	CVertexDiffuse(const D3DXVECTOR3& krVecPos, D3DCOLOR _Diffuse);
	~CVertexDiffuse();
	
	DWORD GetFVF() const;
	unsigned int GetSizeOf() const;

	void SetDiffuseColour(D3DCOLOR _Diffuse);

	void operator=(const CVertexDiffuse& _rhs);

protected:

private:

	// Member variables.
public:

protected:
	D3DCOLOR m_Diffuse;

private:
};

#endif	// __VERTEXDIFFUSE_H__