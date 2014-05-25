//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	Vertex1Textured.h
//	Description	:	Declaration of CVertex1Textured
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

#pragma once
#ifndef __VERTEX1TEXTURED_H__
#define __VERTEX1TEXTURED_H__

// Library includes.
#include <d3dx9.h>

// Local includes.
#include "Vertex.h"

// Types

// Constants

// Prototypes.
class CVertex1Textured : public CVertex
{
	// Member functions.
public:
	CVertex1Textured();
	CVertex1Textured(const D3DXVECTOR3& krVecPos, float _fHorzU, float _fVertV);
	~CVertex1Textured();
	
	DWORD GetFVF() const;
	unsigned int GetSizeOf() const;

	void SetTextureCoordinates(float _fHorzU, float _fHorzV);
	float GetTextureCoordHorzU() const;
	float GetTextureCoordVertV() const;

	void operator=(const CVertex1Textured& _rhs);

protected:

private:

	// Member variables.
public:

protected:
	float m_fU;
	float m_fV;

private:
};

#endif	// __VERTEX1TEXTURED_H__