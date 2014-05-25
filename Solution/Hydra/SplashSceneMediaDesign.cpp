//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   SplashScene.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Macros.h"
#include "Application.h"
#include "Window.h"
#include "D3DRenderer.h"
#include "SpriteManager.h"
#include "Viewport.h"
#include "Camera.h"
#include "LightManager.h"
#include "Entity.h"
#include "Vector3.h"
#include "InputManager.h"
#include "DirectInput.h"
#include "XInputController.h"


// This Include
#include "SplashSceneMediaDesign.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* SplashScene class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CSplashScene::CSplashScene()
: m_fCountDown(0.0000001f)
, m_bFadeOut(0)
, m_fTimer(-1.0f)
{
	//Empty
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* SplashScene class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CSplashScene::~CSplashScene()
{
	Deinitialise();
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function initialisings the class instance before use.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CSplashScene::InitialiseScene(CD3DRenderer* _pRenderer, void* _pSceneData)
{
	InitialiseSprite();


	m_pInputManager->GetDirectInput().AddTarget(DMOUSE_LEFTCLICK, this);
	m_pInputManager->GetDirectInput().AddTarget(DMOUSE_RIGHTCLICK, this);


	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_ENTER, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_SPACE, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_ESCAPE, this);


	m_pInputManager->GetXInputController().AddTarget(XBUTTON_A, this);
	m_pInputManager->GetXInputController().AddTarget(XBUTTON_B, this);
	m_pInputManager->GetXInputController().AddTarget(XBUTTON_BACK, this);
	m_pInputManager->GetXInputController().AddTarget(XBUTTON_START, this);


	CApplication::GetInstance().GetGameWindow().HideCursor();
	CApplication::GetInstance().GetGameWindow().SetCursorStateLocked(true);


	return (true);
}

void
CSplashScene::ProcessScene(float _fDeltaTick)
{
	m_fTimer += _fDeltaTick;

	if(!m_bFadeOut)
	{
		if(m_fTimer >= 1)
		{
			//Fade in
			m_fCountDown += _fDeltaTick / 3;

			if(m_fCountDown >= 1)
			{
				m_bFadeOut = true;
			}
		}
	}
	else if(m_bFadeOut)
	{
		//Fade out
		m_fCountDown -= _fDeltaTick / 3;
	}

	Alpha();

	if(m_fCountDown <= 0)
	{
		Finish();
	}
}

void
CSplashScene::DrawScene(CD3DRenderer* _pRenderer)
{
	m_pRenderer->GetSpriteManager().Draw();
}

void
CSplashScene::Alpha()
{
	CD3DRenderer* pRenderer = CApplication::GetInstance().GetGameWindow().GetRenderer();

	unsigned int uiCurrentSpriteId = 0;

	//Set Alpha depending on display time remaining
	float fCurrentAlpha = 1.0f * m_fCountDown; //over time this goes to 0.0f

	const int kiAlphaMax = 255;

	unsigned char ucAlphaChannel = static_cast<char>(kiAlphaMax * fCurrentAlpha); //this will be between 0x00 and 0xff

	unsigned int uiRGB = 0x00FFFFFF; //Colour RGB

	unsigned int uiFinalColour = (ucAlphaChannel << 24) | uiRGB;

	pRenderer->GetSpriteManager().SetModulate(uiFinalColour, uiCurrentSpriteId);

}


void
CSplashScene::Finish()
{
	CWindow& rGameWindow = CApplication::GetInstance().GetGameWindow();


	CApplication::GetInstance().GetGameWindow().SetCursorStateLocked(false);


	//Set window startup scene
	rGameWindow.SetMainScene(SCENE_SPLASH_LOGO);
}

void
CSplashScene::HandleDMouseInput(EDInputMouse _eDMouse, bool _bDown, long _lValue)
{
	//Empty
}

void
CSplashScene::HandleDKeyboardInput(EDInputKeyboard _eDKebyoard, bool _bDown)
{
	switch (_eDKebyoard)
	{
	case DKEYBOARD_ENTER: //Fall through
	case DKEYBOARD_SPACE: //Fall through
	case DKEYBOARD_ESCAPE: 
		{
			if(_bDown)
			{
				Finish();
			}
		}
		break;
	}
}

void
CSplashScene::HandleXButtonInput(EXInputButton _eXButton, bool _bDown)
{
	switch (_eXButton)
	{
	case XBUTTON_A: //Fall through
	case XBUTTON_B: //Fall through
	case XBUTTON_BACK:  //Fall through
	case XBUTTON_START: 
		{
			if(_bDown)
			{
				Finish();
			}
		}
		break;
	}
}







/********************************
            Protected
*********************************/









/********************************
            Private
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Initialises the lights for the scene.
*
* @author Bryce Booth
* @param _pRenderer		Renderer of parent window.
* @return true			States that the lights were successfully setup.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CSplashScene::InitialiseLights(CD3DRenderer* _pRenderer)
{
	m_uiLightDirectional = _pRenderer->GetLightManager().AddLight();
	_pRenderer->GetLightManager().UpdateParam(m_uiLightDirectional, DIRECTION, CVector3(0.5f, -0.3f, 1.0f));


	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates and initialies a viewport and camera for the scene.
*
* @author Bryce Booth
* @param _pRenderer		Renderer of parent window.
* @return true			States that the viewport and camera were succesfully created.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CSplashScene::InitialiseViewports(CD3DRenderer* _pRenderer)
{
	const unsigned int kuiWindowWidth  = CApplication::GetInstance().GetGameWindow().GetClientWidth();
	const unsigned int kuiWindowHeight = CApplication::GetInstance().GetGameWindow().GetClientHeight();


	m_pViewport = new CViewport();
	m_pViewport->Initialise(0, 0, kuiWindowWidth, kuiWindowHeight, 0, _pRenderer);
	int iCamera = m_pViewport->CreateCamera(3.14159682f/3.0f, 0.1f, 1000.0f);
	m_pViewport->SetActiveCamera(m_pViewport->GetLastCreatedCamera());
	m_pViewport->GetCamera(iCamera)->GetWorldMatrix().SetPositionZ(-10);


	return (true);
}




bool
CSplashScene::InitialiseSprite()
{
	CWindow& rGameWindow = CApplication::GetInstance().GetGameWindow();
	const unsigned int kuiWindowWidth = rGameWindow.GetClientWidth();
	const unsigned int kuiWindowHeight = rGameWindow.GetClientHeight();

	m_uiSpriteMediaDesign = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SplashScreen.png");

	m_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiSpriteMediaDesign);	
	m_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiSpriteMediaDesign);

	return (true);
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* This function deinitialises the class instance by freeing memory and calling other necessary functions.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSplashScene::Deinitialise()
{
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiSpriteMediaDesign);
}