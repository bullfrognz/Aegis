//
//  Diploma of Interactive Gaming
//  Scene Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   camera.cpp
//  Description :   for implementation file
//  Author      :   Jamie.Smith
//  Mail        :   Jamie.Smith@mediadesign.school.nz
//

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

// Library includes.
#include <dinput.h> 

// Local Includes
//#include "Scene.h"
#include "viewport.h" 
#include "D3Drenderer.h"
#include "window.h"
#include "Application.h"
#include "Window.h"
#include "utility.h"
#include "StaticObject.h"

// This Include
#include "camera.h" 

// Static Variables
 int CCamera::s_iCameraID = -1;

CPlane CCamera::m_plnFrustumPlane[PLANE_MAX];

// Static Function Prototypes

// Implementation
CCamera::CCamera()
: m_fFOV(0.0f)
, m_fNearClip(0.0f)
, m_fFarClip(0.0f)
, m_pSkyBox(0)
{
	++s_iCameraID;
}

CCamera::~CCamera()
{
	--s_iCameraID;

	delete m_pSkyBox;
	m_pSkyBox = 0;
}


/**
*
* Initalise the camera 
*
* @author Jamie Smith
* @param _pViewport pointer to the viewport 
* @param _fFOV float for Feild of View 
* @param _fNearClip the near clipping value 
* @param _fFarClip the far clipping value 
* @return valid Initialisatin true or false 
*
*/
bool CCamera::Initialise(CViewport* _pViewport, float _fFOV, int _iHeight, int _iWidth,
							float _fNearClip, float _fFarClip, CD3DRenderer* _pRenderer)
{
	// store renderer
	m_pRenderer = _pRenderer;

	// set up the member variables 
	D3DXMatrixIdentity(&m_matProj);

	m_pViewport = _pViewport;

	m_fFOV = _fFOV;
	m_fNearClip = _fNearClip;
	m_fFarClip = _fFarClip;	

	// calculate the aspect ratio 
	float fAspect = static_cast<float>(_iWidth) / static_cast<float>(_iHeight); 

	// set up prospective matrix 
	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFOV, fAspect, m_fNearClip, m_fFarClip); 

	UpdateMatrix();

	m_pSkyBox = new CStaticObject();
	m_pSkyBox->Initialise("Sky Box", _pRenderer, "Assets/Mesh/SkyBox.x");

	return (true);
}

/**
*
* Process the camera controlls 
*
* @author Jamie Smith
* @param _fDeltaTick time elapsed 
*
*/ 
void CCamera::Process(float _fDeltaTick) 
{
	UpdateMatrix();	

	CEntity::Process(_fDeltaTick);

	CalculateFrustum(m_pRenderer);


	CVector3 v3SelfPosition;
	m_mtxWorldMatrix.GetPosition(v3SelfPosition);

	m_pSkyBox->GetWorldMatrix().SetPosition(v3SelfPosition);

	m_pSkyBox->Process(_fDeltaTick);
}

void
CCamera::Draw(CD3DRenderer* _pRenderer)
{
	_pRenderer->GetDeviceManager().SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pSkyBox->Draw(_pRenderer);
	_pRenderer->GetDeviceManager().SetRenderState(D3DRS_LIGHTING, TRUE);
}


/** 
*
* Updates the renderer with any new view or projection matrix
* 
* @author Jamie.Smith  
* @return void 
*
*/
void 
CCamera::UpdateMatrix()
{
	float fDeterminate = D3DXMatrixDeterminant(&(CEntity::m_mtxWorldMatrix));

	D3DXMatrixInverse(&m_matView, &fDeterminate, &(CEntity::m_mtxWorldMatrix));

	// send the matrices up to the pipe line
	m_pRenderer->SetViewMatrix(&m_matView);
	m_pRenderer->SetProjectionMatrix(&m_matProj);
}

/** 
*
* Returns the cameras ID
* 
* @author Jamie.Smith  
* @return int
*
*/
int		
CCamera::GetCameraID()
{
	return(s_iCameraID);
}

/** 
*
* Sets the view mode for the camera
* 
* @author Jamie.Smith  
* @return void
*
*/
void 
CCamera::SetMode(ECameraMode _eMode)
{
	m_eCameraMode = _eMode;

	ResetMatrices();
}

/** 
*
* Resets the matricies for the camera mode
* 
* @author Jamie.Smith  
* @return void
*
*/
void 
CCamera::ResetMatrices()
{
	switch(m_eCameraMode)
	{
		case CAMERAMODE_PERSPECTIVE:
		{
			Reset3DMatrices();
		}
		break;
		case CAMERAMODE_ORTHOGONAL:
		{
			Reset2DMatrices();
		}
		break;
		default:
		{
			
		}
		break;
	}
}

/** 
*
* Resets the 3d matrices
* 
* @author Jamie.Smith  
* @return void
*
*/
void 
CCamera::Reset3DMatrices()
{
	// calculate the aspect ratio 
	float fAspect = static_cast<float>(m_pViewport->GetWidth()) / static_cast<float>(m_pViewport->GetHeight()); 

	// set up prospective matrix 
	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFOV, fAspect, m_fNearClip, m_fFarClip); 

	UpdateMatrix();
}

/** 
*
* Resets the 2d matrices
* 
* @author Jamie.Smith  
* @return void
*
*/
void 
CCamera::Reset2DMatrices()
{
	// setup 2d viewing plane 
	D3DXMatrixOrthoLH(&m_matProj, static_cast<float>(m_pViewport->GetWidth()), static_cast<float>(m_pViewport->GetHeight()), m_fNearClip, m_fFarClip); 

	UpdateMatrix();
}

/** 
*
* Callucaltes whats if the vector position is within the frustum
* 
* @author Jamie.Smith  
* @Param _rkVec3Pos the vector position
* @Param _fRadius the radius of the object
* @return bool
*
*/
bool
CCamera::IsInFrustum(const CVector3& _rkVec3Pos, float _fRadius)
{
	for(int i = 0; i < PLANE_MAX; ++ i)
	{
		float fDistanceFromPlane = _rkVec3Pos.Dot(m_plnFrustumPlane[i].m_VectorNormal) + m_plnFrustumPlane[i].m_fDistance;

		if(fDistanceFromPlane < (-_fRadius))
		{
			return (false);
		}
	}
	return (true);
}

/** 
*
* Callucaltes the frustum
* 
* @author Jamie.Smith  
* @Param _pRenderer a pointer to the renderer
* @return void
*
*/
void
CCamera::CalculateFrustum(CD3DRenderer* _pRenderer)
{
	const CMatrix* kmtxpProjection = _pRenderer->GetDeviceManager().GetProjectionMatrix();
	const CMatrix* kmtxpView       = _pRenderer->GetDeviceManager().GetViewMatrix();


	CMatrix mtxViewProjection;
	D3DXMatrixMultiply(&mtxViewProjection, kmtxpView, kmtxpProjection);


	m_plnFrustumPlane[PLANE_LEFT].m_VectorNormal.x = -(mtxViewProjection._14 + mtxViewProjection._11);
	m_plnFrustumPlane[PLANE_LEFT].m_VectorNormal.y = -(mtxViewProjection._24 + mtxViewProjection._21);
	m_plnFrustumPlane[PLANE_LEFT].m_VectorNormal.z = -(mtxViewProjection._34 + mtxViewProjection._31);
	m_plnFrustumPlane[PLANE_LEFT].m_fDistance = -(mtxViewProjection._44 + mtxViewProjection._41);

	m_plnFrustumPlane[PLANE_RIGHT].m_VectorNormal.x = -(mtxViewProjection._14 - mtxViewProjection._11);
	m_plnFrustumPlane[PLANE_RIGHT].m_VectorNormal.y = -(mtxViewProjection._24 - mtxViewProjection._21);
	m_plnFrustumPlane[PLANE_RIGHT].m_VectorNormal.z = -(mtxViewProjection._34 - mtxViewProjection._31);
	m_plnFrustumPlane[PLANE_RIGHT].m_fDistance = -(mtxViewProjection._44 - mtxViewProjection._41);

	m_plnFrustumPlane[PLANE_TOP].m_VectorNormal.x = -(mtxViewProjection._14 - mtxViewProjection._12);
	m_plnFrustumPlane[PLANE_TOP].m_VectorNormal.y = -(mtxViewProjection._24 - mtxViewProjection._22);
	m_plnFrustumPlane[PLANE_TOP].m_VectorNormal.z = -(mtxViewProjection._34 - mtxViewProjection._32);
	m_plnFrustumPlane[PLANE_TOP].m_fDistance = -(mtxViewProjection._44 - mtxViewProjection._42);

	m_plnFrustumPlane[PLANE_BOTTOM].m_VectorNormal.x = -(mtxViewProjection._14 + mtxViewProjection._12);
	m_plnFrustumPlane[PLANE_BOTTOM].m_VectorNormal.y = -(mtxViewProjection._24 + mtxViewProjection._22);
	m_plnFrustumPlane[PLANE_BOTTOM].m_VectorNormal.z = -(mtxViewProjection._34 + mtxViewProjection._32);
	m_plnFrustumPlane[PLANE_BOTTOM].m_fDistance = -(mtxViewProjection._44 + mtxViewProjection._42);

	m_plnFrustumPlane[PLANE_NEAR].m_VectorNormal.x = -(mtxViewProjection._13);
	m_plnFrustumPlane[PLANE_NEAR].m_VectorNormal.y = -(mtxViewProjection._23);
	m_plnFrustumPlane[PLANE_NEAR].m_VectorNormal.z = -(mtxViewProjection._33);
	m_plnFrustumPlane[PLANE_NEAR].m_fDistance = -(mtxViewProjection._43);

	m_plnFrustumPlane[PLANE_FAR].m_VectorNormal.x = -(mtxViewProjection._14 - mtxViewProjection._13);
	m_plnFrustumPlane[PLANE_FAR].m_VectorNormal.y = -(mtxViewProjection._24 - mtxViewProjection._23);
	m_plnFrustumPlane[PLANE_FAR].m_VectorNormal.z = -(mtxViewProjection._34 - mtxViewProjection._33);
	m_plnFrustumPlane[PLANE_FAR].m_fDistance = -(mtxViewProjection._44 - mtxViewProjection._43);

	for(int i = 0; i < PLANE_MAX; ++ i)
	{
		m_plnFrustumPlane[i].m_VectorNormal.x *= -1.0f;
		m_plnFrustumPlane[i].m_VectorNormal.y *= -1.0f;
		m_plnFrustumPlane[i].m_VectorNormal.z *= -1.0f;
		m_plnFrustumPlane[i].m_fDistance *= -1.0f;

		float fDenom = 1.0f / D3DXVec3Length(&m_plnFrustumPlane[i].m_VectorNormal);

		m_plnFrustumPlane[i].m_VectorNormal.x *= fDenom;
		m_plnFrustumPlane[i].m_VectorNormal.y *= fDenom;
		m_plnFrustumPlane[i].m_VectorNormal.z *= fDenom;
		m_plnFrustumPlane[i].m_fDistance *= fDenom;
	}
}