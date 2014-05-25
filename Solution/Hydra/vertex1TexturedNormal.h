//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	Vertex1TexturedNormal.h
//	Description	:	Declaration of CVertex1TexturedNormal
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

#pragma once
#ifndef __VERTEX1TEXTUREDNORMAL_H__
#define __VERTEX1TEXTUREDNORMAL_H__

// Library includes.
#include <d3dx9.h>

// Local includes.
#include "VertexNormal.h"

// Types

// Constants

// Prototypes.
class CVertex1TexturedNormal : public CVertexNormal
{
	// Member functions.
public:
	CVertex1TexturedNormal();
	CVertex1TexturedNormal(const D3DXVECTOR3& krVecPos,
						   const D3DXVECTOR3& _krVecNormal,
						   float _fHorzU1, float _fVertV1);
	~CVertex1TexturedNormal();
	
	DWORD GetFVF() const;
	unsigned int GetSizeOf() const;

	// Texture.
	void SetTextureCoordinates(float _fHorzU1, float _fVertV1);
	void ScaleTextureCoordinates1(const float _kfScale);
	float GetTextureCoordHorzU1() const;
	float GetTextureCoordVertV1() const;

	void operator=(const CVertex1TexturedNormal& _rhs);

protected:

private:

	// Member variables.
public:

protected:
	float m_fU1;
	float m_fV1;

private:
};

#endif	// __VERTEX1TEXTUREDNORMAL_H__