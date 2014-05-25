#pragma once

#ifndef __VERTEX2TEXTUREDNORMAL_H__
#define __VERTEX2TEXTUREDNORMAL_H__

// Library includes.
#include <d3dx9.h>

// Local includes.
#include "Vertex1TexturedNormal.h"

// Types

// Constants

// Prototypes.
class CVertex2TexturedNormal : public CVertex1TexturedNormal
{
	// Member functions.
public:
	CVertex2TexturedNormal();
	CVertex2TexturedNormal(const D3DXVECTOR3& krVecPos,
						   const D3DXVECTOR3& _krVecNormal,
						   float _fHorzU1, float _fVertV1,
						   float _fHorzU2, float _fVertV2);
	~CVertex2TexturedNormal();
	
	DWORD GetFVF() const;
	unsigned int GetSizeOf() const;

	// Texture.
	void SetTextureCoordinates(float _fHorzU1, float _fVertV1, float _fHorzU2, float _fVertV2);
	void SetTextureCoordinates(float _fHorzU2, float _fVertV2);
	void ScaleTextureCoordinates2(const float _kfScale);
	float GetTextureCoordHorzU2() const;
	float GetTextureCoordVertV2() const;

	void operator=(const CVertex2TexturedNormal& _rhs);

protected:

private:

	// Member variables.
public:

protected:
	float m_fU2;
	float m_fV2;

private:
};

#endif	// __VERTEX2TEXTUREDNORMAL_H__