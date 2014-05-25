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
#include "application.h"
#include "window.h"
#include "Scene.h"
#include "InputManager.h"
#include "viewport.h" 
#include "D3Drenderer.h"
#include "window.h"
#include "InputManager.h"
#include "XInputController.h"
#include "Application.h"
#include "Window.h"
#include "utility.h"
#include "SoundSystem.h"
#include "DirectInput.h"

#include "StaticObject.h"

// This Include
#include "GameCamera.h" 

// Static Variables
bool
CGameCamera::s_bDisableCameraControls = false;

// Static Function Prototypes

// Implementation
CGameCamera::CGameCamera()
: m_fFOV(0.0f)
, m_fNearClip(0.0f)
, m_fFarClip(0.0f)
, k_iScroll(3)
, m_fMinCamHeight(2)
, m_fMaxCamHeight(45)
, m_pLookAtEntity(0)
, m_fDirection(0)
, m_fAnalogRightX(0)
, m_pPlaceHolder(0)
, m_fAnalogRightY(0)
, m_fAnalogLeftX(0)
, m_fAnalogLeftY(0)
, m_bRotateLeft(false)
, m_bRotateRight(false)
, m_bMoveForward(false)
, m_bMoveBack(false)
, m_bMoveLeft(false)
, m_bMoveRight(false)
, m_bMoveUp(false)
, m_bMoveDown(false)
, m_bMouseScrolling(true)
, m_kfMovementVelocity(12.5f)
, m_kfRotationVelocity(2.0f)
, m_iCameraBounds(17)
{
	// Empty.. 
}

CGameCamera::~CGameCamera()
{
	delete m_pPlaceHolder;
	m_pPlaceHolder = 0;

	delete m_pLookAtEntity;
	m_pLookAtEntity = 0;
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
bool CGameCamera::Initialise(CViewport* _pViewport, float _fFOV, int _iHeight, int _iWidth,
							float _fNearClip, float _fFarClip, CD3DRenderer* _pRenderer,
							CDirectInput* _pDirectInput, CXInputController* _pXInput, CTerrain* _pTerrain)
{
	// store renderer
	m_pRenderer = _pRenderer;

	// set up the member variables 
	D3DXMatrixIdentity(&m_matProj);

	InitPlaceHolder();
	InitLookAtEntity();

	m_fFOV = _fFOV;
	m_fNearClip = _fNearClip;
	m_fFarClip = _fFarClip;

	InitialiseDirectTarget(_pDirectInput);
	InitialiseMouseTarget(_pDirectInput);
	InitialiseXInputTarget(_pXInput);	

	// calculate the aspect ratio 
	float fAspect = static_cast<float>(_iWidth) / static_cast<float>(_iHeight); 

	// set up prospective matrix 
	D3DXMatrixPerspectiveFovLH(&m_matProj, m_fFOV, fAspect, m_fNearClip, m_fFarClip); 

	UpdateMatrix();

	m_iMapHeight = _pTerrain->GetGridHeight();
	m_iMapWidth = _pTerrain->GetGridWidth();

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
void CGameCamera::Process(float _fDeltaTick) 
{
	//Reset movement velocity
	m_pPlaceHolder->SetMovementVelocityX(0);
	m_pPlaceHolder->SetMovementVelocityY(0);
	m_pPlaceHolder->SetMovementVelocityZ(0);


	UpdateMatrix();


	if(s_bDisableCameraControls == false)
	{	
		bool bControllerActive = CApplication::GetInstance().GetGameWindow().GetCurrentMainScene().GetInputManager().GetXInputController().IsPluggedIn();
		bool bControllerDisabled = CApplication::GetInstance().GetGameWindow().GetCurrentMainScene().GetInputManager().GetXInputController().IsDisabled();
		
		if (bControllerActive && bControllerDisabled == false)
		{
			ProcessXInputMovement(_fDeltaTick);
		}
		else
		{
			if (m_bMouseScrolling)
			{
				ProcessMousePosition();
			}
			ProcessDirectInputMovement(_fDeltaTick);
		}

		CheckCamera();


		m_pPlaceHolder->Process(_fDeltaTick);


		float LookAtXDir = m_pPlaceHolder->GetWorldMatrix()._31; 
		float LookAtZDir = m_pPlaceHolder->GetWorldMatrix()._33;
		float PlaceHolderXPos = m_pPlaceHolder->GetWorldMatrix().GetPositionX();
		float PlaceHolderZPos = m_pPlaceHolder->GetWorldMatrix().GetPositionZ();

		float LookAtXPos = PlaceHolderXPos + (LookAtXDir * 10);
		float LookAtZPos = PlaceHolderZPos + (LookAtZDir * 10);

		m_pLookAtEntity->GetWorldMatrix().SetPosition(LookAtXPos, 0.0f, LookAtZPos);

		m_pPlaceHolder->GetWorldMatrix().GetPosition(m_vecPlaceHolderPos);
		this->GetWorldMatrix().SetPosition(m_vecPlaceHolderPos);

		CEntity::Process(_fDeltaTick);

		CSoundSystem::GetInstance()->SetLissenPos(m_vecCameraPos.x,
												  m_vecCameraPos.y,
												  m_vecCameraPos.z,
												  m_vecCameraLook.x,
												  m_vecCameraLook.y,
												  m_vecCameraLook.z);
	}

	CCamera::CalculateFrustum(m_pRenderer);


	CVector3 v3SelfPosition;
	m_mtxWorldMatrix.GetPosition(v3SelfPosition);

	m_pSkyBox->GetWorldMatrix().SetPosition(v3SelfPosition);
}

/** 
*
* Sets up which keys it wishes to check the changes of
* 
* @author Jamie.Smith  
* @Param1 _pPlayerInput the pointer to player input
* @return void
*
*/
void
CGameCamera::InitialiseDirectTarget(CDirectInput* _pDirectInput)
{
	_pDirectInput->AddTarget(DKEYBOARD_UPARROW, this);
	_pDirectInput->AddTarget(DKEYBOARD_DOWNARROW, this);
	_pDirectInput->AddTarget(DKEYBOARD_LEFTARROW, this);
	_pDirectInput->AddTarget(DKEYBOARD_RIGHTARROW, this);


	_pDirectInput->AddTarget(DKEYBOARD_W, this);
	_pDirectInput->AddTarget(DKEYBOARD_A, this);
	_pDirectInput->AddTarget(DKEYBOARD_S, this);
	_pDirectInput->AddTarget(DKEYBOARD_D, this);
	_pDirectInput->AddTarget(DKEYBOARD_R, this);
	_pDirectInput->AddTarget(DKEYBOARD_F, this);
	_pDirectInput->AddTarget(DKEYBOARD_Q, this);
	_pDirectInput->AddTarget(DKEYBOARD_E, this);
	_pDirectInput->AddTarget(DKEYBOARD_SPACE, this);
}

/** 
*
* Sets up which mouse buttons it wishes to check the changes of
* 
* @author Jamie.Smith  
* @Param1 _pPlayerInput the pointer to player input
* @return void
*
*/
void
CGameCamera::InitialiseMouseTarget(CDirectInput* _pDirectInput)
{
	_pDirectInput->AddTarget(DMOUSE_WHEEL, this);
}

/** 
*
* Handles the input of the XBox 360 controller
* 
* @author Jamie.Smith  
* @Param1 _eButton the button which has been pushed
* @Param2 _fValue the amount the button has been pushed
* @return void
*
*/

void
CGameCamera::HandleXButtonInput(EXInputButton _eXButton, bool _bDown)
{
	if (s_bDisableCameraControls == false)
	{
		switch(_eXButton)
		{
		case XBUTTON_Y:
			{
				SnapToOrigin();
			}
			break;

		case XBUTTON_BUMPERLEFT:
			break;

		case XBUTTON_BUMPERRIGHT:
			break;
		}
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Handles analog messages from the controller.
*
* @author Bryce Booth
* @param _eXAnalog	The analog that has been triggered.
* @param _fValue	The value of the trigger.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CGameCamera::HandleXAnalogInput(EXInputAnalog _eXAnalog, float _fValue)
{
	if (s_bDisableCameraControls == false)
	{
		switch (_eXAnalog)
		{
			case XANALOG_LEFTX:
				{
					if (_fValue > 0.25f)
					{
						m_bMoveRight = true;
					}
					else if (_fValue < -0.25f)
					{
						m_bMoveLeft = true;
					}
					else
					{
						m_bMoveLeft = false;
						m_bMoveRight = false;
					}


					m_fAnalogLeftX = _fValue;
				}
				break;

			case XANALOG_LEFTY:
				{
					if (_fValue > 0.25f)
					{
						m_bMoveForward = true;
					}
					else if (_fValue < -0.25f)
					{
						m_bMoveBack = true;
					}
					else
					{
						m_bMoveForward = false;
						m_bMoveBack = false;
					}


					m_fAnalogLeftY = _fValue;
				}
				break;

			case XANALOG_RIGHTX:
				{
					if (_fValue > 0.25f)
					{
						m_bRotateLeft = true;
					}
					else if (_fValue < -0.25f)
					{
						m_bRotateRight = true;
					}
					else
					{
						m_bRotateLeft = false;
						m_bRotateRight = false;
					}


					m_fAnalogRightX = _fValue;
				}
				break;

			case XANALOG_RIGHTY:
				{
					if (_fValue > 0.25f)
					{
						m_bMoveUp = true;
					}
					else if (_fValue < -0.25f)
					{
						m_bMoveDown = true;
					}
					else
					{
						m_bMoveUp = false;
						m_bMoveDown = false;
					}


					m_fAnalogRightY = _fValue;
				}
				break;
		}
	}
}


/** 
*
* Sets up which Xbox controller buttons it wishes to check the changes of
* 
* @author Jamie.Smith  
* @Param1 _pPlayerInput the pointer to player input
* @return void
*
*/
void 
CGameCamera::InitialiseXInputTarget(CXInputController* _pXInput)
{
	_pXInput->AddTarget(XBUTTON_A, this);
	_pXInput->AddTarget(XBUTTON_B, this);
	_pXInput->AddTarget(XBUTTON_X, this);
	_pXInput->AddTarget(XBUTTON_Y, this);
	_pXInput->AddTarget(XANALOG_LEFTX, this);
	_pXInput->AddTarget(XANALOG_LEFTY, this);
	_pXInput->AddTarget(XANALOG_RIGHTX, this);
	_pXInput->AddTarget(XANALOG_RIGHTY, this);
	_pXInput->AddTarget(XBUTTON_BUMPERLEFT, this);
	_pXInput->AddTarget(XBUTTON_BUMPERRIGHT, this);
	_pXInput->AddTarget(XBUTTON_START, this);
}

/** 
*
* Handles the input of the mouse
* 
* @author Jamie.Smith
* @Param1 _eButton the button which has been pushed
* @Param2 _fValue the amount the button has been pushed
* @return void
*
*/
void
CGameCamera::HandleDMouseInput(EDInputMouse _eDMouse, bool _bDown, long _lValue)
{
	m_pPlaceHolder->GetWorldMatrix()._42 += (_lValue / 120) * -4.0f;
}



/*---------------------------------------------------------------------------------------------------------------------------
*
* Handles the keyboard input messages
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CGameCamera::HandleDKeyboardInput(EDInputKeyboard _eDKebyoard, bool _bDown)
{
	if (s_bDisableCameraControls == false)
	{
		switch (_eDKebyoard)
		{
		case DKEYBOARD_UPARROW: //Fall through
		case DKEYBOARD_W:
			m_bMoveForward = _bDown;
			break;
		
		case DKEYBOARD_LEFTARROW: //Fall through
		case DKEYBOARD_A:
			m_bMoveLeft = _bDown;
			break;

		case DKEYBOARD_DOWNARROW: //Fall through
		case DKEYBOARD_S:
			m_bMoveBack = _bDown;
			break;
		
		case DKEYBOARD_RIGHTARROW: //Fall through
		case DKEYBOARD_D:
			m_bMoveRight = _bDown;
			break;

		case DKEYBOARD_Q:
			m_bRotateRight = _bDown;
			break;

		case DKEYBOARD_E:
			m_bRotateLeft = _bDown;
			break;

		case DKEYBOARD_R:
			m_bMoveUp = _bDown;
			break;

		case DKEYBOARD_F:
			m_bMoveDown = _bDown;
			break;

		case DKEYBOARD_SPACE:
			SnapToOrigin();
			break;
		}
	}
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Processes the mouse position, and moves camera if the mouse cursor is within range of border.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CGameCamera::ProcessMousePosition()
{
	const int kiClientWidth  = CApplication::GetInstance().GetGameWindow().GetClientWidth();
	const int kiClientHeight = CApplication::GetInstance().GetGameWindow().GetClientHeight();
	COORD& crdrMousePosition   = CApplication::GetInstance().GetGameWindow().GetMosueCoords();

	int iPaddingX = static_cast<int>(kiClientWidth * 0.025f);
	int iPaddingY = static_cast<int>(kiClientHeight * 0.025f);


	if (crdrMousePosition.X < iPaddingX)
	{
		m_pPlaceHolder->SetMovementVelocityX(-m_kfMovementVelocity * 1.25f);
	}
	else if  (crdrMousePosition.X > kiClientWidth - iPaddingX)
	{
		m_pPlaceHolder->SetMovementVelocityX(m_kfMovementVelocity * 1.25f);
	}


	if (crdrMousePosition.Y < iPaddingY)
	{
		m_pPlaceHolder->SetMovementVelocityZ(m_kfMovementVelocity * 1.25f);
	}
	else if  (crdrMousePosition.Y > kiClientHeight - iPaddingY)
	{
		m_pPlaceHolder->SetMovementVelocityZ(-m_kfMovementVelocity * 1.25f);
	}
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Processes movement for the camera based of direct input.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CGameCamera::ProcessDirectInputMovement(float _fDeltaTick)
{
	//Movement forward & back
	if (m_bMoveForward && !m_bMoveBack)
	{
		m_pPlaceHolder->SetMovementVelocityZ(m_kfMovementVelocity);
	}
	else if (!m_bMoveForward && m_bMoveBack)
	{
		m_pPlaceHolder->SetMovementVelocityZ(-m_kfMovementVelocity);
	}


	//Movement left & right
	if (m_bMoveLeft && !m_bMoveRight)
	{
		m_pPlaceHolder->SetMovementVelocityX(-m_kfMovementVelocity);
	}
	else if (!m_bMoveLeft && m_bMoveRight)
	{
		m_pPlaceHolder->SetMovementVelocityX(m_kfMovementVelocity);
	}


	//Rotate left & right
	if (m_bRotateLeft && !m_bRotateRight)
	{
		Rotate(m_kfRotationVelocity * _fDeltaTick);
	}
	else if (!m_bRotateLeft && m_bRotateRight)
	{
		Rotate(m_kfRotationVelocity * _fDeltaTick * -1.0f);
	}


	//Move up & down
	if (m_bMoveUp && !m_bMoveDown)
	{
		m_pPlaceHolder->SetMovementVelocityY(m_kfMovementVelocity);
	}
	else if (!m_bMoveUp && m_bMoveDown)
	{
		m_pPlaceHolder->SetMovementVelocityY(-m_kfMovementVelocity);
	}
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Processes movement for the camera based of x input.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CGameCamera::ProcessXInputMovement(float _fDeltaTick)
{
	//Movement forward & back & left & right
	if (m_bMoveForward || m_bMoveBack || m_bMoveRight || m_bMoveLeft)
	{
		m_pPlaceHolder->SetMovementVelocityZ(m_kfMovementVelocity * m_fAnalogLeftY);
		m_pPlaceHolder->SetMovementVelocityX(m_kfMovementVelocity * m_fAnalogLeftX);
	}


	//Rotate left & right && Move up & down
	if (m_bRotateLeft || m_bRotateRight || m_bMoveUp || m_bMoveDown)
	{
		Rotate(-m_kfRotationVelocity * m_fAnalogRightX * _fDeltaTick);
		m_pPlaceHolder->SetMovementVelocityY(-m_kfMovementVelocity * m_fAnalogRightY);
	}
}

/** 
*
* Checks whether the camera is within its bounds
* 
* @author Jamie.Smith  
* @return void
*
*/
void
CGameCamera::CheckCamera()
{
	if(m_pPlaceHolder->GetWorldMatrix()._42 <= m_fMinCamHeight)
	{
		m_pPlaceHolder->GetWorldMatrix()._42 = m_fMinCamHeight;
	}

	if(m_pPlaceHolder->GetWorldMatrix()._42 >= m_fMaxCamHeight)
	{
		m_pPlaceHolder->GetWorldMatrix()._42 = m_fMaxCamHeight;
	}

	if(m_pPlaceHolder->GetWorldMatrix()._41 >= m_iMapWidth + m_iCameraBounds)
	{			
		m_pPlaceHolder->GetWorldMatrix()._41 = static_cast<float>(m_iMapWidth + m_iCameraBounds);
	}
	else if(m_pPlaceHolder->GetWorldMatrix()._41 <= ((m_iMapWidth * -1) - m_iCameraBounds))
	{		
		m_pPlaceHolder->GetWorldMatrix()._41 = static_cast<float>((m_iMapWidth * -1) - m_iCameraBounds);
	}
	if(m_pPlaceHolder->GetWorldMatrix()._43 >= m_iMapHeight + m_iCameraBounds)
	{			
		m_pPlaceHolder->GetWorldMatrix()._43 = static_cast<float>(m_iMapHeight + m_iCameraBounds);
	}
	else if(m_pPlaceHolder->GetWorldMatrix()._43 <= ((m_iMapHeight * -1) - m_iCameraBounds))
	{			
		m_pPlaceHolder->GetWorldMatrix()._43 = static_cast<float>((m_iMapHeight * -1) - m_iCameraBounds);
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CGameCamera::Rotate(float _fRadians)
{
	//Default varaibles
	CVector3 v3LookAtPosition;
	CVector3 v3PlaceHolderPosition;
	float fNewPositionX = 0.0f;
	float fNewPositionY = 0.0f;


	//Get positions
	m_pLookAtEntity->GetWorldMatrix().GetPosition(v3LookAtPosition);
	m_pPlaceHolder->GetWorldMatrix().GetPosition(v3PlaceHolderPosition);


	//Rotate place holder
	m_pPlaceHolder->RotateY(_fRadians);


	//Calculate new position
	MathUtility::PointRotation(v3LookAtPosition.x,
							   v3LookAtPosition.z,
							   v3PlaceHolderPosition.x,
							   v3PlaceHolderPosition.z,								
							   _fRadians,
							   fNewPositionX,
							   fNewPositionY);


	//Set place holder position
	m_pPlaceHolder->GetWorldMatrix().SetPositionX(fNewPositionX);
	m_pPlaceHolder->GetWorldMatrix().SetPositionZ(fNewPositionY);		
}

/** 
*
* initialises the PlaceHolder Entity
* 
* @author Jamie.Smith  
* @return void
*
*/
void
CGameCamera::InitPlaceHolder()
{
	CVector3 v3Position(0.0f, 10.0f, -10.0f);

	m_pPlaceHolder = new CEntity();
	m_pPlaceHolder->Initialise("CameraPlaceHolder");
	m_pPlaceHolder->GetWorldMatrix().SetPosition(v3Position);	
}

/** 
*
* initialises the LookAt Entity
* 
* @author Jamie.Smith  
* @return void
*
*/
void
CGameCamera::InitLookAtEntity()
{	
	CVector3 v3Position(0.0f, 0.0f, 0.0f);

	m_pLookAtEntity = new CEntity();
	m_pLookAtEntity->Initialise("CameraLookAtHolder");
	m_pLookAtEntity->GetWorldMatrix().SetPosition(v3Position);
	this->SetTrackingEntity(m_pLookAtEntity);
}

/** 
*
* Snaps the camera back to the original position
* 
* @author Jamie.Smith
* @return void
*
*/
void
CGameCamera::SnapToOrigin()
{
	delete m_pPlaceHolder;
	m_pPlaceHolder = 0;

	delete m_pLookAtEntity;
	m_pLookAtEntity = 0;

	InitPlaceHolder();
	InitLookAtEntity();
}

void
CGameCamera::DisableCameraControls(bool _bDisableCameraControls)
{
	if (m_pPlaceHolder && _bDisableCameraControls == true)
	{
		m_pPlaceHolder->SetMovementVelocityX(0);
		m_pPlaceHolder->SetMovementVelocityY(0);
		m_pPlaceHolder->SetMovementVelocityZ(0);


		m_bRotateLeft = false;
		m_bRotateRight = false;

		m_bMoveForward = false;
		m_bMoveBack = false;
		m_bMoveLeft = false;
		m_bMoveRight = false;

		m_bMoveUp = false;
		m_bMoveDown = false;
	}


	CGameCamera::s_bDisableCameraControls = _bDisableCameraControls;
}


CEntity*
CGameCamera::GetPlaceHolder()
{
	return (m_pPlaceHolder);
}


void
CGameCamera::SetMouseScrollingEnabled(bool _bEnabled)
{
	m_bMouseScrolling = _bEnabled;
}

void 
DisableController(bool _bDisable)
{
	//m_pXInput-
}

