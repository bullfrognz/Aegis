//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
// (c) 2011 Media Design School
//
//  File Name   :   RayCast.cpp
//  Description :   Template for implementation of CClogmanager files
//  Author      :   Daniel Langsford
//  Mail        :   daniel.langsford@mediadesign.school.nz
//

#include "Macros.h"
#include "Application.h"
#include "Viewport.h"
#include "Window.h"
#include "Camera.h"
#include "GameCamera.h"
#include "utility.h"

#include "RayCast.h" 

/**
*
* This function creates a ray from the near plane of the frustum to the far plane,
* depending on mouse position.
*
* @author Daniel Langsford
* @param _pViewPort: The viewport to be used. 
* @param _bUseMouseCoords: Determines whether mouse coordinates will be used,
* if false, the middle of the screen will be used
*
* @returns a 3D vector, specifying the direction of the new ray.
*
*/
D3DXVECTOR3
CRayCast::CastRay(CViewport* _pViewPort, bool _bUseMouseCoords)
{
	D3DXVECTOR3 vecNear;
	D3DXVECTOR3 vecFar;
	D3DMATRIX matView;

	float fWidth = static_cast<float>(CApplication::GetInstance().GetGameWindow().GetClientWidth());
	float fHeight = static_cast<float>(CApplication::GetInstance().GetGameWindow().GetClientHeight());

	float fX = 0;
	float fY = 0;

	if(_bUseMouseCoords == true)
	{
		COORD MousePos = CApplication::GetInstance().GetGameWindow().GetMosueCoords();
		fX = static_cast<float>(MousePos.X);
		fY = static_cast<float>(MousePos.Y);
	}
	else
	{
		fX = fWidth / 2;
		fY = fHeight / 2;

	}
	
	float fFar = _pViewPort->GetActiveCamera()->GetFarPlane();
	float fNear = _pViewPort->GetActiveCamera()->GetNearPlane();

	float fFOV = _pViewPort->GetFOV();

	matView = *(_pViewPort->GetActiveCamera()->GetViewMatrix());


	//Normalises the coordinates taken in;
	//new coordinates will be between -1 and 1 on the x and y axis.
	NormaliseCoords(fWidth, fHeight, fX, fY);

	// Mouse X and Y are now scalars beween -1.0f and 1.0f.

	//Converts the input coordinates into 3D points.
	Create3DPoints(fX, fY, fFOV, fNear, fFar, fWidth / fHeight,
				   m_vecNearPoint, m_vecFarPoint);

	//Converts the new 3D points into world space.
	ConvertToWorldSpace(m_vecNearPoint, m_vecFarPoint, matView);

	//Returns the newly created ray.
	return m_vecFarPoint - m_vecNearPoint;
}

/**
*
* This function normalises the coordinates of the mouse, to within a range of negative one to positive one
*
* @author Daniel Langsford
* @param _fScreenWidth: Width of the screen
* @param _fScreenWidth: Height of the screen
* @return void
*
*/
void
CRayCast::NormaliseCoords(float _fScreenWidth, float _fScreenHeight,
						 float& _fX, float& _fY)
{
	_fX = ((_fX + _fX) / _fScreenWidth) - 1.0f;
	_fY = ((_fY + _fY) / _fScreenHeight) - 1.0f;

	//LOG_FATALERROR(_fX > 1 || _fX < -1, "Mouse X outside of normalised range");
	//LOG_FATALERROR(_fY > 1 || _fY < -1, "Mouse Y outside of normalised range");

}

/**
*
* This function creates two 3D points on the near and far plane of the frustum.
*
* @author Daniel Langsford
* @param _fX: X Coordinate of the mouse.
* @param _fY: Y Coordinate of the mouse.
* @param _fFOV: Field of view in the viewport
* @param _fNear: Distance to near plane of frustum.
* @param _fFar: Distance to far plane of frustum.
* @param _fAspectRatio: Aspect ratio of the screen (width / height)
* @param _vecNearPoint: Point on the near plane of the frustum to be populated.
* @param _vecFarPoint: Point on the far plane of the frustum to be populated.
*
* @return void
*
*/
void
CRayCast::Create3DPoints(float _fX, float _fY, float _fFOV,
						 float _fNear, float _fFar, float _fAspectRatio,
						 D3DXVECTOR3& _vecNearPoint, D3DXVECTOR3& _vecFarPoint)
{
	const float kfTangent = tanf(_fFOV * 0.5f);
	float fRatioX = kfTangent * (_fX * _fAspectRatio);
	float fRatioY = -kfTangent * _fY;

	_vecNearPoint.x = _fNear * fRatioX;
	_vecNearPoint.y = _fNear * fRatioY;
	_vecNearPoint.z = _fNear;

	_vecFarPoint.x = _fFar * fRatioX;
	_vecFarPoint.y = _fFar * fRatioY;
	_vecFarPoint.z = _fFar;
}

/**
*
* This function converts the new near and far points into world coordinates
*
* @author Daniel Langsford
* @param _vecNearPoint: The near point, which will be converted to world space coordinates.
* @param _vecFarPoint: The far point, which will be converted to world space coordinates.
* @param _rkmatView: The view matrix, taken from the viewport.
* @return void.
*
*/
void
CRayCast::ConvertToWorldSpace(D3DXVECTOR3& _vecNearPoint, D3DXVECTOR3& _vecFarPoint,
							const D3DXMATRIX& _rkmatView)
{
	float fDeterminant = D3DXMatrixDeterminant(&_rkmatView);
	D3DXMATRIX matInverseView;

	D3DXMatrixInverse(&matInverseView, &fDeterminant, &_rkmatView);

	D3DXVECTOR4 vecNearResult;
	D3DXVECTOR4 vecFarResult;
	
	D3DXVec3Transform(&vecNearResult, &_vecNearPoint, &matInverseView);
	D3DXVec3Transform(&vecFarResult, &_vecFarPoint, &matInverseView);

	_vecNearPoint.x = vecNearResult.x;
	_vecNearPoint.y = vecNearResult.y;
	_vecNearPoint.z = vecNearResult.z;

	_vecFarPoint.x = vecFarResult.x;
	_vecFarPoint.y = vecFarResult.y;
	_vecFarPoint.z = vecFarResult.z;

	// Remember vectors for future reference.
	m_vecNearPoint = _vecNearPoint;
	m_vecFarPoint = _vecFarPoint;
}

/**
*
* This function populates and returns the near and far points of the ray.
*
* @author Daniel Langsford
* @param _vecNearPoint: Near point to be populated.
* @param _vecFarPoint: Far point to be populated.
*
* @return void.
*
*/
void
CRayCast::Get3DPoints(D3DXVECTOR3& _vecNearPoint, D3DXVECTOR3& _vecFarPoint) const
{
	_vecNearPoint = m_vecNearPoint;
	_vecFarPoint = m_vecFarPoint;
}

	