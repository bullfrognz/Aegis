//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   RunThroughCamera.h
//  Description :   for declaration file
//  Author      :   Jamie Smith
//  Mail        :   Jamie.Smith@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_RUNTHROUGHCAMERA_H__
#define __IGFEB11_RUNTHROUGHCAMERA_H__

// Library Includes

// Local Includes
#include "Utility.h"
#include "viewport.h"
#include "Vector3.h"
#include "entity.h"
#include "matrix.h"
#include "Camera.h"
#include "enemy.h"

// Types

// Constants

// Prototypes
class CViewport;
class CD3DRenderer;
class CCamera;

class CRunThroughCamera :  public CCamera
{
	// Member Functions
public:
	CRunThroughCamera();
	virtual ~CRunThroughCamera();

	virtual bool Initialise(CViewport* _pViewport, float _fFOV, int _iHeight, int _iWidth,
							float _fNearClip, float _fFarClip, CD3DRenderer* _pRenderer, CEnemy* _pEntity);


	virtual void Process(float _fDeltaTick); 


protected:

private:

	// Member Variables
public:
	
	CEnemy* m_pPlaceHolder;

protected:	

	float m_fFOV;
	float m_fNearClip;
	float m_fFarClip;
	float m_fMinCamHeight;
	float m_fMaxCamHeight;
	float m_fHeightY;

	CVector3 m_vecCameraPos;
	CVector3 m_vecPlaceHolderPos;

	CVector3 m_vecMaxAngle;
	CVector3 m_vecMinAngle;
	CVector3 m_vecCameraLook;

private:

};
 
#endif //__IGFEB11_GAMECAMERA_H__
