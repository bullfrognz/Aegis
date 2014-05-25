//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	VertexScreenSpace.h
//	Description	:	Declaration of CVertex1TexSCSP
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

#pragma once
#ifndef __VERTEX1TEXTURESCREENSPACE_H__
#define __VERTEX1TEXTURESCREENSPACE_H__

// Library includes.
#include <d3dx9.h>

// Local includes.
#include "Vertex.h"

// Types

// Constants

// Prototypes.
class CVertex1TexSCSP : public CVertex
{
	// Member functions.
public:
	CVertex1TexSCSP();
	CVertex1TexSCSP(const D3DXVECTOR3& krVecPos, float _fU, float _fV);
	~CVertex1TexSCSP();
	
	DWORD GetFVF() const;
	unsigned int GetSizeOf() const;

	void SetTextureCoordinates(float _fHorzU, float _fVertV);
	float GetTextureCoordHorzU() const;
	float GetTextureCoordVertV() const;

	void SetPos(float _fX, float _fY);

	void operator=(const CVertex1TexSCSP& _rhs);

protected:

private:

	// Member variables.
public:

protected:
	float m_fRHW;
	float m_fU;
	float m_fV;

private:
};

#endif	// __VERTEX1TEXTURESCREENSPACE_H__