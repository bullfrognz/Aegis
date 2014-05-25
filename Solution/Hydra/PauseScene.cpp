//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   PauseScene.cpp
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
#include "Camera.h"
#include "Viewport.h"
#include "SoundSystem.h"
#include "LightManager.h"
#include "DirectInput.h"
#include "InputManager.h"
#include "SettingsSceneData.h"
#include "XInputController.h"


// This Include
#include "PauseScene.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* PauseScene class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CPauseScene::CPauseScene()
: m_eCurrentButton(BUTTON_CONTINUE)
, m_uiLightDirectional(0)
, m_uiContinue(0)
, m_uiSettings(0)
, m_uiQuit(0)
, m_fSelectChangeDelay(0)
, m_fSelectChangeTimer(0)
, m_bMouseClick(false)
{
	//Empty
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* PauseScene class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CPauseScene::~CPauseScene()
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
CPauseScene::InitialiseScene(CD3DRenderer* _pRenderer, void* _pSceneData)
{
	//Set member variables
	m_fSelectChangeDelay = 0.2f;


	//Run initialise functions
	InitialisePlayerInputTarget();
	InitialiseXInputTarget();
	InitialiseSprites(_pRenderer);

	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CPauseScene::ProcessScene(float _fDeltaTick)
{
	m_fSelectChangeTimer += _fDeltaTick;


	if (m_pInputManager->GetXInputController().IsPluggedIn() == false)
	{
		MouseSelection();
	}


	ResetCursor();
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CPauseScene::DrawScene(CD3DRenderer* _pRenderer)
{
	//Empty
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CPauseScene::HandleDMouseInput(EDInputMouse _eDMouse, bool _bDown, long _lValue)
{
	switch (_eDMouse)
	{
	case DMOUSE_LEFTCLICK:
		{
			m_bMouseClick = _bDown;
			break;
		}
	}
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CPauseScene::HandleDKeyboardInput(EDInputKeyboard _eDKebyoard, bool _bDown)
{
	if (_bDown == true)
	{
		switch(_eDKebyoard)
		{
		case DKEYBOARD_S: //Fall through
		case DKEYBOARD_DOWNARROW:
			{
				IncrementButton();
				break;
			}
		case DKEYBOARD_W: //Fall through
		case DKEYBOARD_UPARROW:
			{
				DecrementButton();
				break;
			}
		case DKEYBOARD_ENTER: //Fall through
		case DKEYBOARD_SPACE:
			{
				ExecuteSelect();
				break;
			}

		case DKEYBOARD_ESCAPE:
			{
				m_eCurrentButton = BUTTON_CONTINUE;
				ExecuteSelect();
				break;
			}
		}
	}
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CPauseScene::HandleXButtonInput(EXInputButton _eXButton, bool _bDown)
{
	switch (_eXButton)
	{
	case XBUTTON_A:
		{
			if (_bDown)
			{
				ExecuteSelect();
			}
			break;
		}


	case XBUTTON_START: //Fall through
	case XBUTTON_B:
		{
			if (_bDown)
			{
				m_eCurrentButton = BUTTON_CONTINUE;
				ExecuteSelect();
			}
			break;
		}
	}
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CPauseScene::HandleXAnalogInput(EXInputAnalog _eXAnalog, float _fValue)
{
	switch (_eXAnalog)
	{
		case XANALOG_LEFTX:
		{
			if (_fValue >= 0.8f)
			{
			}
			else if (_fValue <= -0.8f)
			{
			}
			break;
		}

		case XANALOG_LEFTY:
		{
			if (_fValue >= 0.8f)
			{
				DecrementButton();
			}
			else if (_fValue <= -0.8f)
			{
				IncrementButton();
			}
			break;
		}
	}
}








/********************************
            Protected
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CPauseScene::InitialiseLights(CD3DRenderer* _pRenderer)
{
	m_uiLightDirectional = _pRenderer->GetLightManager().AddLight();
	_pRenderer->GetLightManager().UpdateParam(m_uiLightDirectional, DIRECTION, CVector3(0.5f, -0.3f, 1.0f));


	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CPauseScene::InitialiseViewports(CD3DRenderer* _pRenderer)
{
	//Empty


	return (true);
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CPauseScene::InitialisePlayerInputTarget()
{
	//Mouse
	m_pInputManager->GetDirectInput().AddTarget(DMOUSE_LEFTCLICK, this);
	m_pInputManager->GetDirectInput().AddTarget(DMOUSE_RIGHTCLICK, this);
	m_pInputManager->GetDirectInput().AddTarget(DMOUSE_WHEEL, this);


	//Keyboard
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_A, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_D, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_W, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_S, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_UPARROW, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_DOWNARROW, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_LEFTARROW, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_RIGHTARROW, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_ESCAPE, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_ENTER, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_SPACE, this);


	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CPauseScene::InitialiseXInputTarget()
{
	m_pInputManager->GetXInputController().AddTarget(XBUTTON_START, this);
	m_pInputManager->GetXInputController().AddTarget(XBUTTON_A, this);
	m_pInputManager->GetXInputController().AddTarget(XBUTTON_B, this);
	m_pInputManager->GetXInputController().AddTarget(XANALOG_LEFTX, this);
	m_pInputManager->GetXInputController().AddTarget(XANALOG_LEFTY, this);
	//m_pXInput->AddIsActiveTarget(this);


	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CPauseScene::InitialiseSprites(CD3DRenderer* _pRenderer)
{
	//Settings
	m_uiContinue = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/PauseMenu_Continue.png");
	m_uiSettings = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/PauseMenu_Settings.png");
	m_uiQuit     = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/PauseMenu_Quit.png");


	_pRenderer->GetSpriteManager().SetPosition(CVector3(1280.0f / 2.0f, 1024.0f / 2.0f - 100.0f, 0.0f), m_uiContinue);
	_pRenderer->GetSpriteManager().SetPosition(CVector3(1280.0f / 2.0f, 1024.0f / 2.0f + 050.0f, 0.0f), m_uiSettings);
	_pRenderer->GetSpriteManager().SetPosition(CVector3(1280.0f / 2.0f, 1024.0f / 2.0f + 200.0f, 0.0f), m_uiQuit);


	UpdateSprites();


	return (true);
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Resets the cursor for the select map scene.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CPauseScene::ResetCursor()
{
	if (m_pInputManager->GetXInputController().IsPluggedIn())
	{
		CApplication::GetInstance().GetGameWindow().HideCursor();
	}
	else
	{
		CApplication::GetInstance().GetGameWindow().ShowCursor();
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void 
CPauseScene::UpdateSprites()
{
	switch (m_eCurrentButton)
	{
	case BUTTON_CONTINUE:
		m_pRenderer->GetSpriteManager().SetModulate(s_uiHoverSpriteColour, m_uiContinue);
		m_pRenderer->GetSpriteManager().SetModulate(s_uiIdleSpriteColour, m_uiSettings);
		m_pRenderer->GetSpriteManager().SetModulate(s_uiIdleSpriteColour, m_uiQuit);
		break;


	case BUTTON_SETTINGS:
		m_pRenderer->GetSpriteManager().SetModulate(s_uiIdleSpriteColour, m_uiContinue);
		m_pRenderer->GetSpriteManager().SetModulate(s_uiHoverSpriteColour, m_uiSettings);
		m_pRenderer->GetSpriteManager().SetModulate(s_uiIdleSpriteColour, m_uiQuit);
		break;


	case BUTTON_QUIT:
		m_pRenderer->GetSpriteManager().SetModulate(s_uiIdleSpriteColour, m_uiContinue);
		m_pRenderer->GetSpriteManager().SetModulate(s_uiIdleSpriteColour, m_uiSettings);
		m_pRenderer->GetSpriteManager().SetModulate(s_uiHoverSpriteColour, m_uiQuit);
		break;
	}
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CPauseScene::IncrementButton()
{
	if (m_fSelectChangeTimer > m_fSelectChangeDelay)
	{
		switch (m_eCurrentButton)
		{
		case BUTTON_CONTINUE:
			m_eCurrentButton = BUTTON_SETTINGS;
			break;

		case BUTTON_SETTINGS:
			m_eCurrentButton = BUTTON_QUIT;
			break;

		case BUTTON_QUIT:
			break;
		}


		UpdateSprites();


		m_fSelectChangeTimer = 0.0f;


		CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");
	}
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CPauseScene::DecrementButton()
{
	if (m_fSelectChangeTimer > m_fSelectChangeDelay)
	{
		switch (m_eCurrentButton)
		{
		case BUTTON_CONTINUE:
			break;

		case BUTTON_SETTINGS:
			m_eCurrentButton = BUTTON_CONTINUE;
			break;

		case BUTTON_QUIT:
			m_eCurrentButton = BUTTON_SETTINGS;
			break;
		}


		UpdateSprites();


		m_fSelectChangeTimer = 0.0f;


		CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");
	}
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CPauseScene::ExecuteSelect()
{
	switch (m_eCurrentButton)
	{
	case BUTTON_CONTINUE:
		CApplication::GetInstance().GetGameWindow().GetCurrentMainScene().RecoverFromOverlayScene();
		CApplication::GetInstance().GetGameWindow().SetOverlayScene(OVERLAYSCENE_DELETE);
		break;

	case BUTTON_SETTINGS:
		{
			CSettingsSceneData* pSettingsSceneData = new CSettingsSceneData;
			pSettingsSceneData->SetSceneTypeId(OVERLAYSCENE_GAMEPAUSEMENU);
			pSettingsSceneData->SetSceneTypeMainScene(false);


			CApplication::GetInstance().GetGameWindow().SetOverlayScene(OVERLAYSCENE_SETTINGS, pSettingsSceneData);
		}
		break;

	case BUTTON_QUIT:
		CApplication::GetInstance().GetGameWindow().SetMainScene(SCENE_MAINMENU);
		CApplication::GetInstance().GetGameWindow().SetOverlayScene(OVERLAYSCENE_DELETE);
		break;
	}


	CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Select.wav");
}









void
CPauseScene::MouseSelection()
{
	RECT SpriteBounds;
	CVector3 vecPos;
	int iWidth = 0;
	int iHeight = 0;
	
	HWND hWnd = CApplication::GetInstance().GetGameWindow().GetWindowHandle();

	const unsigned int kuiWindowWidth = CApplication::GetInstance().GetGameWindow().GetWindowWidth();
	const unsigned int kuiWindowHeight =  CApplication::GetInstance().GetGameWindow().GetWindowHeight();

	COORD MouseCords;
	MouseCords = CApplication::GetInstance().GetGameWindow().GetMosueCoords();
	CD3DRenderer* pRenderer = CApplication::GetInstance().GetGameWindow().GetRenderer();

	//Continue
	SpriteBounds = m_pRenderer->GetSpriteManager().GetRect(m_uiContinue);

	vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiContinue);

	iWidth =  SpriteBounds.right - SpriteBounds.left;
	iHeight =  SpriteBounds.bottom - SpriteBounds.top;

	SpriteBounds.left   =	static_cast<LONG>(vecPos.x - (iWidth / 2));
	SpriteBounds.right  =	static_cast<LONG>(vecPos.x + (iWidth / 2));
	SpriteBounds.top    =	static_cast<LONG>(vecPos.y - (iHeight / 2));
	SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + (iHeight / 2));
		
	if(MouseCords.X >= SpriteBounds.left  &&
	   MouseCords.X <= SpriteBounds.right &&
	   MouseCords.Y >= SpriteBounds.top   &&
	   MouseCords.Y <= SpriteBounds.bottom)
	{		
		if(m_eCurrentButton != BUTTON_CONTINUE)
		{
			m_eCurrentButton = BUTTON_CONTINUE;
			UpdateSprites();

			m_fSelectChangeTimer = 0.0f;

			CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");
		}

		if(m_bMouseClick == true)
		{		
			ExecuteSelect();		
		}
			
	}

	//Settings
	SpriteBounds = m_pRenderer->GetSpriteManager().GetRect(m_uiSettings);

	vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiSettings);

	iWidth =  SpriteBounds.right - SpriteBounds.left;
	iHeight =  SpriteBounds.bottom - SpriteBounds.top;

	SpriteBounds.left   =	static_cast<LONG>(vecPos.x - (iWidth / 2));
	SpriteBounds.right  =	static_cast<LONG>(vecPos.x + (iWidth / 2));
	SpriteBounds.top    =	static_cast<LONG>(vecPos.y - (iHeight / 2));
	SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + (iHeight / 2));
		
	if(MouseCords.X >= SpriteBounds.left  &&
	   MouseCords.X <= SpriteBounds.right &&
	   MouseCords.Y >= SpriteBounds.top   &&
	   MouseCords.Y <= SpriteBounds.bottom)
	{		
		if(m_eCurrentButton != BUTTON_SETTINGS)
		{
			m_eCurrentButton = BUTTON_SETTINGS;
			UpdateSprites();

			m_fSelectChangeTimer = 0.0f;

			CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");
		}

		if(m_bMouseClick == true)
		{
			ExecuteSelect();		
		}		
	}

	//Quit
	SpriteBounds = m_pRenderer->GetSpriteManager().GetRect(m_uiQuit);

	vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiQuit);

	iWidth =  SpriteBounds.right - SpriteBounds.left;
	iHeight =  SpriteBounds.bottom - SpriteBounds.top;

	SpriteBounds.left   =	static_cast<LONG>(vecPos.x - (iWidth / 2));
	SpriteBounds.right  =	static_cast<LONG>(vecPos.x + (iWidth / 2));
	SpriteBounds.top    =	static_cast<LONG>(vecPos.y - (iHeight / 2));
	SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + (iHeight / 2));
		
	if(MouseCords.X >= SpriteBounds.left  &&
	   MouseCords.X <= SpriteBounds.right &&
	   MouseCords.Y >= SpriteBounds.top   &&
	   MouseCords.Y <= SpriteBounds.bottom)
	{	
		if(m_eCurrentButton != BUTTON_QUIT)
		{
			m_eCurrentButton = BUTTON_QUIT;
			UpdateSprites();

			m_fSelectChangeTimer = 0.0f;

			CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");
		}

		if(m_bMouseClick == true)
		{
			ExecuteSelect();		
		}	
	}
}

/********************************
            Private
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function deinitialises the class instance by freeing memory and calling other necessary functions.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CPauseScene::Deinitialise()
{
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiContinue);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiSettings);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiQuit);
}