//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	VertexSCSP.h
//	Description	:	Declaration of CVertexSCSP (Screen Space)
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

#pragma once
#ifndef __VERTEXSCREENSPACE_H__
#define __VERTEXSCREENSPACE_H__

// Library includes.
#include <d3dx9.h>

// Local includes.
#include "Vertex.h"

// Types

// Constants

// Prototypes.
class CVertexSCSP : public CVertex
{
	// Member functions.
public:
	CVertexSCSP();
	CVertexSCSP(const D3DXVECTOR3& krVecPos);
	~CVertexSCSP();
	
	DWORD GetFVF() const;
	unsigned int GetSizeOf() const;

	void SetPos(float _fX, float _fY);

	void operator=(const CVertexSCSP& _rhs);

protected:

private:

	// Member variables.
public:

protected:
	float m_fRHW;

private:
};

#endif	// __VERTEXSCREENSPACE_H__