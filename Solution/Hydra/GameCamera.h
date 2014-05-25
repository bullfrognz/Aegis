//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   GameCamera.h
//  Description :   for declaration file
//  Author      :   Jamie Smith
//  Mail        :   Jamie.Smith@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_GAMECAMERA_H__
#define __IGFEB11_GAMECAMERA_H__

// Library Includes

// Local Includes
#include "Utility.h"
#include "viewport.h"
#include "Vector3.h"
#include "entity.h"
#include "XButtonTarget.h"
#include "XAnalogTarget.h"
#include "matrix.h"
#include "Camera.h"
#include "terrain.h"
#include "DMouseTarget.h"
#include "DKeyboardTarget.h"

// Types

// Constants

// Prototypes
class CViewport;
class CD3DRenderer;
class CXInputController;
class CCamera;

class CGameCamera : public IDMouseTarget, public IDKeyboardTarget, public IXButtonTarget, public IXAnalogTarget, public CCamera
{
	// Member Functions
public:
	CGameCamera();
	virtual ~CGameCamera();

	virtual bool Initialise(CViewport* _pViewport, float _fFOV, int _iHeight, int _iWidth,
							float _fNearClip, float _fFarClip, CD3DRenderer* _pRenderer,
							CDirectInput* _pDirectInput, CXInputController* _pXInput, 
							CTerrain* _pTerrain);

	virtual inline float GetNearPlane() const; 
	virtual inline float GetFarPlane() const; 

	virtual void Process(float _fDeltaTick); 

	void CheckTimers(float _fDeltaTick);

	void ProcessMousePosition();
	void ProcessDirectInputMovement(float _fDeltaTick);
	void ProcessXInputMovement(float _fDeltaTick);

	void InitPlaceHolder();
	void InitLookAtEntity();

	virtual inline D3DXMATRIX* GetViewMatrix(); 
	virtual inline D3DXMATRIX* GetProjMatrix();  

	virtual void HandleXButtonInput(EXInputButton _eXButton, bool _bDown = false);
	virtual void HandleXAnalogInput(EXInputAnalog _eXAnalog, float _fValue = 0.0f);
	virtual void HandleDMouseInput(EDInputMouse _eDMouse, bool _bDown, long _lValue);
	virtual void HandleDKeyboardInput(EDInputKeyboard _eDKebyoard, bool _bDown = false);

	void CheckCamera();

	void Rotate(float _fRadians);

	void SnapToOrigin();

	void DisableCameraControls(bool _DisableCameraControls);

	CEntity* GetPlaceHolder();

	void SetMouseScrollingEnabled(bool _bEnabled);

	void DisableController(bool _bDisable);


protected:

private:
	virtual void InitialiseDirectTarget(CDirectInput* _pDirectInput);
	virtual void InitialiseMouseTarget(CDirectInput* _pDirectInput);
	virtual void InitialiseXInputTarget(CXInputController* _pXInput);

	// Member Variables
public:
	
	CEntity* m_pLookAtEntity;
	CEntity* m_pPlaceHolder;

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

	float m_fDirection;

	int m_iMapHeight;
	int m_iMapWidth;

	int m_iCameraBounds;

	float m_fAnalogRightX;
	float m_fAnalogRightY;

	float m_fAnalogLeftX;
	float m_fAnalogLeftY;

	bool m_bRotateLeft;
	bool m_bRotateRight;

	bool m_bMoveForward;
	bool m_bMoveBack;
	bool m_bMoveLeft;
	bool m_bMoveRight;

	bool m_bMoveUp;
	bool m_bMoveDown;

	bool m_bMouseScrolling;

	CXInputController* m_pXInput;

	static bool s_bDisableCameraControls;

private:
	const float m_kfMovementVelocity;
	const float m_kfRotationVelocity;

	const int k_iScroll;

};

#include "GameCamera.inl" 
#endif //__IGFEB11_GAMECAMERA_H__
