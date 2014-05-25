//
//  Diploma of Interactive Gaming
//  Scene Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   RunThroughcamera.cpp
//  Description :   for implementation file
//  Author      :   Jamie.Smith
//  Mail        :   Jamie.Smith@mediadesign.school.nz
//

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

// Library includes.

// Local Includes
//#include "Scene.h"
#include "viewport.h" 
#include "D3Drenderer.h"
#include "window.h"
#include "Application.h"
#include "Window.h"
#include "utility.h"

// This Include
#include "RunThroughCamera.h" 

// Static Variables

// Static Function Prototypes

// Implementation
CRunThroughCamera::CRunThroughCamera()
: m_fFOV(0.0f)
, m_fNearClip(0.0f)
, m_fFarClip(0.0f)
, m_pPlaceHolder(0)
{
	// Empty.. 
}

CRunThroughCamera::~CRunThroughCamera()
{
	delete m_pPlaceHolder;
	m_pPlaceHolder = 0;
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
* @param _pPlayerInput a pointer to the playerinput class
* @param _pXInput a pointer to the XInput class
* @return valid Initialisatin true or false 
*
*/
bool CRunThroughCamera::Initialise(CViewport* _pViewport, float _fFOV, int _iHeight, int _iWidth,
							float _fNearClip, float _fFarClip, CD3DRenderer* _pRenderer, CEnemy* _pEntity)
{
	// store renderer
	m_pRenderer = _pRenderer;

	// set up the member variables 
	D3DXMatrixIdentity(&m_matProj);

	m_pPlaceHolder = _pEntity;

	m_fFOV = _fFOV;
	m_fNearClip = _fNearClip;
	m_fFarClip = _fFarClip;	

	// calculate the aspect ratio 
	float fAspect = static_cast<float>(_iWidth) / static_cast<float>(_iHeight); 

	// set up prospective matrix 
	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFOV, fAspect, m_fNearClip, m_fFarClip); 

	UpdateMatrix();

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
void CRunThroughCamera::Process(float _fDeltaTick) 
{
	UpdateMatrix();		

	m_pPlaceHolder->Process(_fDeltaTick);

	m_pPlaceHolder->GetWorldMatrix().GetPosition(m_vecPlaceHolderPos);
	this->GetWorldMatrix().SetPosition(m_vecPlaceHolderPos);
	this->CopyOrientation(m_pPlaceHolder);

	CEntity::Process(_fDeltaTick);
}






