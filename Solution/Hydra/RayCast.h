//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
// (c) 2011 Media Design School
//
//  File Name   :   LogFile.h
//  Description :   Template for declaration of CLogfile files
//  Author      :   Daniel Langsford
//  Mail        :   daniel.langsford@mediadesign.school.nz
//
#pragma once

#ifndef __IGFEB11_IG500_RAYCAST_H__
#define __IGFEB11_IG500_RAYCAST_H__

// Library Includes
#include <d3d9.h>
#include <d3dx9.h>
#include <math.h>

// Local Includes

// Types

// Constants

// Prototypes
class CViewport;

class CRayCast
{
// Member Functions
public:
	
	D3DXVECTOR3 CastRay(CViewport* _pViewPort, bool _bUseMouseCoords);

	static void NormaliseCoords(float _fScreenWidth, float _fScreenHeight,
								float& _fX, float& _fY);

	void Create3DPoints(float _fX, float _fY, float _fFOV,
						float _fNear, float _fFar, float _fAspectRatio,
						D3DXVECTOR3& _vecNearPoint, D3DXVECTOR3& _vecFarPoint);

	void ConvertToWorldSpace(D3DXVECTOR3& _vecNearPoint, D3DXVECTOR3& _vecFarPoint,
						 const D3DXMATRIX& _rkmatView);

	void Get3DPoints(D3DXVECTOR3& _vecNearPoint, D3DXVECTOR3& _vecFarPoint) const;

		
protected:

private:

// Member Variables
public:

protected:

private:
	D3DXVECTOR3 m_vecNearPoint;
	D3DXVECTOR3 m_vecFarPoint;

};

#endif // __IGFEB11_MODULE_TEMPLATE_H__
