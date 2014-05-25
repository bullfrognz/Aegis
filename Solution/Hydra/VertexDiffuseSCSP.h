//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	VertexDiffuseSCSP.h
//	Description	:	Declaration of CVertexDiffuseSCSP (Screen Space)
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

#pragma once
#ifndef __VERTEXDIFFUSESCREENSPACE_H__
#define __VERTEXDIFFUSESCREENSPACE_H__

// Library includes.
#include <d3dx9.h>

// Local includes.
#include "Vertex.h"

// Types

// Constants

// Prototypes.
class CVertexDiffuseSCSP : public CVertex
{
	// Member functions.
public:
	CVertexDiffuseSCSP();
	CVertexDiffuseSCSP(const D3DXVECTOR3& krVecPos, D3DCOLOR _dwDiffuse);
	~CVertexDiffuseSCSP();
	
	DWORD GetFVF() const;
	unsigned int GetSizeOf() const;

	void SetPos(float _fX, float _fY);
	void SetDiffuse(D3DCOLOR _dwDiffuse);

	void operator=(const CVertexDiffuseSCSP& _rhs);

protected:

private:

	// Member variables.
public:

protected:
	float m_fRHW;
	D3DCOLOR m_dwDiffuse;

private:
};

#endif	// __VERTEXDIFFUSESCREENSPACE_H__