//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   camera.h
//  Description :   for declaration file
//  Author      :   Jamie Smith
//  Mail        :   Jamie.Smith@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_CAMERA_H__
#define __IGFEB11_CAMERA_H__

// Library Includes

// Local Includes
#include "Utility.h"
#include "viewport.h"
#include "Vector3.h"
#include "entity.h"
#include "matrix.h"
#include "Planes.h"

// Types
typedef enum TECameraMode
{
	INVALID_CAMERAMODE,
	CAMERAMODE_ORTHOGONAL,
	CAMERAMODE_PERSPECTIVE,
	MAX_CAMERAMODE

} ECameraMode;

// Constants

// Prototypes
class CViewport;
class CD3DRenderer;
class CObject;

class CCamera : public CEntity
{
	// Member Functions
public:
	CCamera();
	virtual ~CCamera();

	virtual bool Initialise(CViewport* _pViewport, float _fFOV, int _iHeight, int _iWidth,
							float _fNearClip, float _fFarClip, CD3DRenderer* _pRenderer); 

	virtual inline float GetNearPlane() const; 
	virtual inline float GetFarPlane() const; 

	virtual void Process(float _fDeltaTick); 


	virtual void Draw(CD3DRenderer* _pRenderer);


	virtual inline D3DXMATRIX* GetViewMatrix(); 
	virtual inline D3DXMATRIX* GetProjMatrix(); 

	virtual inline void SetProjMatrix(CMatrix* _ProjMat); 

	virtual void SetMode(ECameraMode _eMode);

	virtual void ResetMatrices();

	void Reset3DMatrices(); 
	void Reset2DMatrices(); 

	virtual void UpdateMatrix();  

	int GetCameraID();

	static bool IsInFrustum(const CVector3& _rkVec3Pos, float _fRadius);

	inline CObject* GetSkyBox();

protected:

	void CalculateFrustum(CD3DRenderer* _pRenderer);

private:

	// Member Variables
public:

protected:
	CD3DRenderer* m_pRenderer;

	CObject* m_pSkyBox;

	ECameraMode m_eCameraMode;

	CViewport* m_pViewport;

	float m_fFOV;
	float m_fNearClip;
	float m_fFarClip;

	CMatrix m_matView; 
	CMatrix m_matProj; 

	static int s_iCameraID;

	static CPlane m_plnFrustumPlane[PLANE_MAX];

private:

};

#include "camera.inl" 
#endif //__IGFEB11_CAMERA_H__
