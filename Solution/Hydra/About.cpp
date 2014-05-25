//
//  Diploma of Interactive Gaming
//  Scene Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   About.cpp
//  Description :   for implementation file
//  Author      :   Jamie.Smith
//  Mail        :   Jamie.Smith@mediadesign.school.nz
//

// Library includes.

// Local Includes
#include "Macros.h"
#include "Application.h"
#include "GameWindow.h"
#include "D3DRenderer.h"
#include "SpriteManager.h"
#include "Camera.h"
#include "Viewport.h"
#include "SoundSystem.h"
#include "LightManager.h"
#include "InputManager.h"
#include "DeviceManager.h"
#include "XInputController.h"
#include "DirectInput.h"

// This Include
#include "About.h"

// Static Variables

// Static Function Prototypes


// Implementation

CAboutScene::CAboutScene()
: m_fResetTime(0.0f)
, m_fResetBackTime(0.0f)
, m_uiSelectedSprite(0)
, m_bLeftClick(false)
{

}

CAboutScene::~CAboutScene()
{
	Deinitialise();
}

bool
CAboutScene::InitialiseLights(CD3DRenderer *_pRenderer)
{
	m_uiLightDirectional = _pRenderer->GetLightManager().AddLight();

	_pRenderer->GetLightManager().UpdateParam(m_uiLightDirectional, DIRECTION, CVector3(0.5f, -0.3f, 1.0f));

	return(true);
}

bool
CAboutScene::InitialiseViewports(CD3DRenderer *_pRenderer)
{
	//empty
	return (true);
}

/**
*
* This function sets up all sprites
*
* @author Daniel Langsford
* @param 
* @return 
*
*/
bool
CAboutScene::InitialiseSprites(CD3DRenderer *_pRenderer)
{
	//Background
	m_uiBackGround = _pRenderer->GetSpriteManager().AddSprite (L"Assets/Sprites/About_BackGround.png");
	_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiBackGround);

	CVector3 vecPos;
	vecPos.x = 1280.0f / 2.0f;
	vecPos.y = 1024.0f / 2.0f;
	vecPos.z = 0.0f;

	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiBackGround);

	//Controlls
	m_uiGameControlls = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/ About_Controls.png");
	vecPos.y = 1024.0f * 0.3f;
	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiGameControlls);

	
	//Rules
	m_uiGameRules = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/About_Rules.png");
	vecPos.y = 1024.0f * 0.5f;
	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiGameRules);

	//Credits
	m_uiCredits = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/About_Credits.png");
	vecPos.y = 1024.0f * 0.7f;
	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiCredits);

	RECT SpriteRect = _pRenderer->GetSpriteManager().GetRect(m_uiGameControlls);
	SpriteRect.bottom = static_cast<LONG>(0.25f * SpriteRect.bottom);

	_pRenderer->GetSpriteManager().SetRect(&SpriteRect, m_uiGameControlls);
	_pRenderer->GetSpriteManager().SetRect(&SpriteRect, m_uiGameRules);
	_pRenderer->GetSpriteManager().SetRect(&SpriteRect, m_uiCredits);

	//Controls
	m_uiController = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/About_ViewControls.png");
	vecPos.x = 1280.0f / 2.0f;
	vecPos.y = 1024.0f / 2.0f;
	vecPos.z = 0.0f;
	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiController);
	_pRenderer->GetSpriteManager().SetVisible(false, m_uiController);
	
	//Keyboard controls
	m_uiKeyBoardControls = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/About_KeyboardControls.png");
	vecPos.x = 1280.0f / 2.0f;
	vecPos.y = 1024.0f / 2.0f;
	vecPos.z = 0.0f;
	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiKeyBoardControls);
	_pRenderer->GetSpriteManager().SetVisible(false, m_uiKeyBoardControls);

	//Credits
	m_uiViewCredits = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/About_ViewCredits.png");
	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiViewCredits);
	_pRenderer->GetSpriteManager().SetVisible(false, m_uiViewCredits);

	//Rules
	m_uiRules1 = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/About_Rules1.png");
	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiRules1);
	_pRenderer->GetSpriteManager().SetVisible(false, m_uiRules1);

	m_uiRules2 = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/About_Rules2.png");
	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiRules2);
	_pRenderer->GetSpriteManager().SetVisible(false, m_uiRules2);

	m_uiRules3 = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/About_Rules3.png");
	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiRules3);
	_pRenderer->GetSpriteManager().SetVisible(false, m_uiRules3);

	m_uiRules4 = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/About_Rules4.png");
	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiRules4);
	_pRenderer->GetSpriteManager().SetVisible(false, m_uiRules4);

	m_uiRules5 = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/About_Rules5.png");
	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiRules5);
	_pRenderer->GetSpriteManager().SetVisible(false, m_uiRules5);

	m_uiRules6 = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/About_Rules6.png");
	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiRules6);
	_pRenderer->GetSpriteManager().SetVisible(false, m_uiRules6);

	m_uiRules7 = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/About_Rules7.png");
	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiRules7);
	_pRenderer->GetSpriteManager().SetVisible(false, m_uiRules7);

	//Close
	m_uiQuit = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/About_Back.png");
	_pRenderer->GetSpriteManager().SetPosition(CVector3(42, 42, 0), m_uiQuit);
	_pRenderer->GetSpriteManager().SetVisible(true, m_uiQuit);

	return(true);
}

bool
CAboutScene::InitialiseScene(CD3DRenderer *_pRenderer, void *_pSceneData)
{
	m_eSceneState = STATE_MAIN;

	InitialiseSprites(_pRenderer);
	InitialiseViewports(_pRenderer);
	InitialiseLights(_pRenderer);

	InitPlayerInput();
	InitXInput();

	return(true);
}

void
CAboutScene::ProcessScene(float _fDeltaTick)
{	
	SpriteSelect();

	if(m_bLeftClick)
	{
		if(m_eSceneState == STATE_RULES)
		{
			RulesNextPage();
		}
		else if(m_eSceneState == STATE_CONTROLS)
		{
			ControlsNextPage();
		}
		m_bLeftClick = false;
	}	
}

void
CAboutScene::DrawScene(CD3DRenderer *_pRenderer)
{
	_pRenderer->GetLightManager().TurnOnLight(m_uiLightDirectional);

	_pRenderer->GetSpriteManager().Draw();
	
}


/**
*
* This function allows users to select sprites using the mouse
*
* @author Daniel Langsford
* @param 
* @return 
*
*/
void
CAboutScene::SpriteSelect()
{
	RECT SpriteBounds;
	CVector3 vecPos;
	float fWidth = 0;
	float fHeight = 0;
	
	HWND hWnd = CApplication::GetInstance().GetGameWindow().GetWindowHandle();

	const unsigned int kuiWindowWidth = CApplication::GetInstance().GetGameWindow().GetWindowWidth();
	const unsigned int kuiWindowHeight =  CApplication::GetInstance().GetGameWindow().GetWindowHeight();

	COORD MouseCords;
	MouseCords = CApplication::GetInstance().GetGameWindow().GetMosueCoords();
	CD3DRenderer* pRenderer = CApplication::GetInstance().GetGameWindow().GetRenderer();

	if(m_eSceneState == STATE_MAIN)
	{

		SpriteBounds = m_pRenderer->GetSpriteManager().GetRect(m_uiGameControlls);

		vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiGameControlls);

		fWidth =  static_cast<float>(SpriteBounds.right - SpriteBounds.left);
		fHeight =  static_cast<float>(SpriteBounds.bottom - SpriteBounds.top);
		fHeight *= 0.25f;

		fWidth = static_cast<float>((kuiWindowWidth / 1280.0f) * fWidth);
		fHeight = static_cast<float>((kuiWindowHeight / 1024.0f) * fHeight);
			
		SpriteBounds.left   =	static_cast<LONG>(vecPos.x - (fWidth / 2));
		SpriteBounds.right  =	static_cast<LONG>(vecPos.x + (fWidth / 2));
		SpriteBounds.top    =	static_cast<LONG>(vecPos.y - (fHeight / 2));
		SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + (fHeight / 2));
			
		if(MouseCords.X >= SpriteBounds.left  &&
		   MouseCords.X <= SpriteBounds.right &&
		   MouseCords.Y >= SpriteBounds.top   &&
		   MouseCords.Y <= SpriteBounds.bottom)
		{
			if(m_bLeftClick == true)
			{
				OpenControls();	
				m_bLeftClick = false;
			}
		}

		vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiCredits);

		SpriteBounds.left   =	static_cast<LONG>(vecPos.x - (fWidth / 2));
		SpriteBounds.right  =	static_cast<LONG>(vecPos.x + (fWidth / 2));
		SpriteBounds.top    =	static_cast<LONG>(vecPos.y - (fHeight / 2));
		SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + (fHeight / 2));
			
		if(MouseCords.X >= SpriteBounds.left  &&
		   MouseCords.X <= SpriteBounds.right &&
		   MouseCords.Y >= SpriteBounds.top   &&
		   MouseCords.Y <= SpriteBounds.bottom)
		{
			if(m_bLeftClick == true)
			{
				OpenCredits();	
				m_bLeftClick = false;
			}
		}

		vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiGameRules);

		SpriteBounds.left   =	static_cast<LONG>(vecPos.x - (fWidth / 2));
		SpriteBounds.right  =	static_cast<LONG>(vecPos.x + (fWidth / 2));
		SpriteBounds.top    =	static_cast<LONG>(vecPos.y - (fHeight / 2));
		SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + (fHeight / 2));
			
		if(MouseCords.X >= SpriteBounds.left  &&
		   MouseCords.X <= SpriteBounds.right &&
		   MouseCords.Y >= SpriteBounds.top   &&
		   MouseCords.Y <= SpriteBounds.bottom)
		{
			if(m_bLeftClick == true)
			{
				OpenRules();
				m_bLeftClick = false;
			}
		}
	}

	SpriteBounds = m_pRenderer->GetSpriteManager().GetRect(m_uiQuit);
	fWidth = static_cast<float>(SpriteBounds.right - SpriteBounds.left);
	fHeight = static_cast<float>(SpriteBounds.bottom - SpriteBounds.top);

	vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiQuit);

	SpriteBounds.left   =	static_cast<LONG>(vecPos.x - (fWidth / 2));
	SpriteBounds.right  =	static_cast<LONG>(vecPos.x + (fWidth / 2));
	SpriteBounds.top    =	static_cast<LONG>(vecPos.y - (fHeight / 2));
	SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + (fHeight / 2));
		
	if(MouseCords.X >= SpriteBounds.left  &&
	   MouseCords.X <= SpriteBounds.right &&
	   MouseCords.Y >= SpriteBounds.top   &&
	   MouseCords.Y <= SpriteBounds.bottom)
	{
		if(m_bLeftClick == true)
		{
			if(m_eSceneState == STATE_MAIN)
			{
				CApplication::GetInstance().GetGameWindow().GetCurrentMainScene().RecoverFromOverlayScene();
				CApplication::GetInstance().GetGameWindow().SetOverlayScene(OVERLAYSCENE_DELETE);
			}
			else
			{
				CloseAll();
			}

			m_bLeftClick = false;					
		}
	}
}

/**
*
* Handles the xinput 
*
* @author Jamie Smith
* @param _eXButton which button
* @param _bDown if the button is down or not 
*
*/ 
void
CAboutScene::HandleXButtonInput(EXInputButton _eXButton, bool _bDown)
{
	switch (_eXButton)
	{
		case XBUTTON_A:
		{
			if (_bDown)
			{
				m_bLeftClick = true;
				m_eSelectedSprite = static_cast<ESpriteSelection>(m_uiSelectedSprite);
			}

			break;
		}

		case XBUTTON_BACK:
		{
			if (_bDown)
			{
				CApplication::GetInstance().GetGameWindow().SetMainScene(SCENE_MAINMENU);				
			}
			break;
		}
	}
}

/**
*
* Handles the xinput Analog
*
* @author Jamie Smith
* @param _eXAnalog which button
* @param _fValue how much the Analog is pulled
*
*/ 
void
CAboutScene::HandleXAnalogInput(EXInputAnalog _eXAnalog, float _fValue)
{
	switch (_eXAnalog)
	{
		case XANALOG_LEFTX:
		{
			if (_fValue >= 0.8f)
			{
				++m_uiSelectedSprite;

				if(m_uiSelectedSprite > 3)
				{
					m_uiSelectedSprite = 0;
				}
			}
			else if (_fValue <= -0.8f)
			{
				--m_uiSelectedSprite;

				if(m_uiSelectedSprite < 0)
				{
					m_uiSelectedSprite = 3;
				}
			}
			break;
		}

		case XANALOG_LEFTY:
		{
			if (_fValue >= 0.8f)
			{
				m_uiSelectedSprite -= 2;

				if(m_uiSelectedSprite < 0)
				{
					m_uiSelectedSprite += 4;
				}
			}
			else if (_fValue <= -0.8f)
			{
				m_uiSelectedSprite += 2;

				if(m_uiSelectedSprite > 3)
				{
					m_uiSelectedSprite -= 4;
				}
			}
			break;
		}
	}
}

/**
*
* Handles the mouse input
*
* @author Jamie Smith
* @param _eDMouse which key state 
* @param _bDown if the key is down or not 
* @param _lValue the scroll value
*
*/
void
CAboutScene::HandleDMouseInput(EDInputMouse _eDMouse, bool _bDown, long _lValue)
{
	switch (_eDMouse)
	{
	case DMOUSE_LEFTCLICK:
		{
			m_bLeftClick = _bDown;
			break;
		}

	case DMOUSE_RIGHTCLICK:
		{
			m_bRightClick = _bDown;
			break;
		}
	case DMOUSE_WHEEL:
		{
			break;
		}
	}
}

/**
*
* This function handles input from the keyboard
*
* @author Jamie smith
* @param _iButton: which key it is
* @param _Down: if the key is down or up
* @return void
*
*/
void
CAboutScene::HandleDKeyboardInput(EDInputKeyboard _eDKebyoard, bool _bDown)
{
	switch (_eDKebyoard)
	{
	case DKEYBOARD_A:	//Fall through
	case DKEYBOARD_LEFTARROW:
		--m_uiSelectedSprite;

		if(m_uiSelectedSprite < 0)
		{
			m_uiSelectedSprite = 3;
		}
		break;

	case DKEYBOARD_D:	//Fall through
	case DKEYBOARD_RIGHTARROW:
		++m_uiSelectedSprite;

		if(m_uiSelectedSprite > 3)
		{
			m_uiSelectedSprite = 0;
		}
		break;


	case DKEYBOARD_S:	//Fall through
	case DKEYBOARD_DOWNARROW:
		m_uiSelectedSprite += 2;

		if(m_uiSelectedSprite > 3)
		{
			m_uiSelectedSprite -= 4;
		}
		break;

	case DKEYBOARD_W:	//Fall through
	case DKEYBOARD_UPARROW:
		m_uiSelectedSprite -= 2;

		if(m_uiSelectedSprite < 0)
		{
			m_uiSelectedSprite += 4;
		}
		break;


	case DKEYBOARD_ENTER: //Fall through
	case DKEYBOARD_SPACE:
		m_eSelectedSprite = static_cast<ESpriteSelection>(m_uiSelectedSprite);
		break;

	case DKEYBOARD_ESCAPE: //Fall through
	case DKEYBOARD_BACK:
		{
			CloseAll();
		}
		break;
	}
}

/**
*
* Sets if the controller is active or not
*
* @author Jamie smith
* @param _bActive: if the controller is active or not
* @return void
*
*/
void 
CAboutScene::SetControllerActive(bool _bActive)
{
	m_bControllerActive = _bActive;
}

/**
*
* Initialises the player input targets
*
* @author Jamie smith
* @return bool
*
*/
bool
CAboutScene::InitPlayerInput()
{
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_A, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_D, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_W, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_S, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_ENTER, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_SPACE, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_BACK, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_ESCAPE,this);

	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_UPARROW, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_DOWNARROW, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_RIGHTARROW, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_LEFTARROW, this);

	m_pInputManager->GetDirectInput().AddTarget(DMOUSE_LEFTCLICK, this);
	m_pInputManager->GetDirectInput().AddTarget(DMOUSE_RIGHTCLICK, this);
	m_pInputManager->GetDirectInput().AddTarget(DMOUSE_WHEEL, this);

	return(true);
}

/**
*
* Initialises the xinput targets
*
* @author Jamie smith
* @return bool
*
*/
bool
CAboutScene::InitXInput()
{
	m_pInputManager->GetXInputController().AddTarget(XBUTTON_A, this);
	m_pInputManager->GetXInputController().AddTarget(XBUTTON_BACK, this);
	m_pInputManager->GetXInputController().AddTarget(XANALOG_LEFTX, this);
	m_pInputManager->GetXInputController().AddTarget(XANALOG_LEFTY, this);


	return(true);
}



/**
*
* This function
*
* @author Daniel Langsford
* @param 
* @return 
*
*/
void
CAboutScene::OpenControls()
{
	m_eSceneState = STATE_CONTROLS;

	m_eCOntrolsPage = CONTROLS_XBOXCONTROLLER;

	m_pRenderer->GetSpriteManager().SetVisible(true, m_uiController);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiCredits);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiGameRules);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiGameControlls);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiBackGround);
}


/**
*
* This function
*
* @author Daniel Langsford
* @param 
* @return 
*
*/
void
CAboutScene::CloseControls()
{
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiController);
	m_pRenderer->GetSpriteManager().SetVisible(true, m_uiCredits);
	m_pRenderer->GetSpriteManager().SetVisible(true, m_uiGameRules);
	m_pRenderer->GetSpriteManager().SetVisible(true, m_uiGameControlls);
	m_pRenderer->GetSpriteManager().SetVisible(true, m_uiBackGround);
	
}



/**
*
* This function
*
* @author Daniel Langsford
* @param 
* @return 
*
*/
void
CAboutScene::CloseAll()
{
	m_eSceneState = STATE_MAIN;

	CloseControls();
	CloseCredits();
	CloseRules();
}



/**
*
* This function
*
* @author Daniel Langsford
* @param 
* @return 
*
*/
void
CAboutScene::OpenRules()
{
	m_eSceneState = STATE_RULES;
	m_eRulesPage = RULES_MAIN;

	m_pRenderer->GetSpriteManager().SetVisible(true, m_uiRules1);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiCredits);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiGameRules);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiGameControlls);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiBackGround);

}


/**
*
* This function
*
* @author Daniel Langsford
* @param 
* @return 
*
*/
void
CAboutScene::CloseRules()
{
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiRules1);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiRules2);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiRules3);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiRules4);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiRules5);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiRules6);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiRules7);
	m_pRenderer->GetSpriteManager().SetVisible(true, m_uiCredits);
	m_pRenderer->GetSpriteManager().SetVisible(true, m_uiGameRules);
	m_pRenderer->GetSpriteManager().SetVisible(true, m_uiGameControlls);
	m_pRenderer->GetSpriteManager().SetVisible(true, m_uiBackGround);

}



/**
*
* This function
*
* @author Daniel Langsford
* @param 
* @return 
*
*/
void
CAboutScene::OpenCredits()
{
	m_eSceneState = STATE_CREDITS;

	m_pRenderer->GetSpriteManager().SetVisible(true, m_uiViewCredits);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiCredits);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiGameRules);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiGameControlls);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiBackGround);

}


/**
*
* This function
*
* @author Daniel Langsford
* @param 
* @return 
*
*/
void
CAboutScene::CloseCredits()
{
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiViewCredits);
	m_pRenderer->GetSpriteManager().SetVisible(true, m_uiCredits);
	m_pRenderer->GetSpriteManager().SetVisible(true, m_uiGameRules);
	m_pRenderer->GetSpriteManager().SetVisible(true, m_uiGameControlls);
	m_pRenderer->GetSpriteManager().SetVisible(true, m_uiBackGround);
}


/**
*
* This function
*
* @author Daniel Langsford
* @param 
* @return 
*
*/
void
CAboutScene::RulesNextPage()
{
	switch(m_eRulesPage)
	{
	case RULES_MAIN:
		{
			m_eRulesPage = RULES_HUDINFO;
			
			m_pRenderer->GetSpriteManager().SetVisible(false, m_uiRules1);
			m_pRenderer->GetSpriteManager().SetVisible(true, m_uiRules2);						

			break;
		}
	case RULES_HUDINFO:
		{
			m_eRulesPage = RULES_LIVESINFO;
			
			m_pRenderer->GetSpriteManager().SetVisible(false, m_uiRules2);	
			m_pRenderer->GetSpriteManager().SetVisible(true, m_uiRules3);
			
			break;
		}
	case RULES_LIVESINFO:
		{
			m_eRulesPage = RULES_GOLDINFO;
			m_pRenderer->GetSpriteManager().SetVisible(false, m_uiRules3);
			m_pRenderer->GetSpriteManager().SetVisible(true, m_uiRules4);	
			break;
		}
	case RULES_GOLDINFO:
		{
			m_eRulesPage = RULES_WAVEINFO;
			m_pRenderer->GetSpriteManager().SetVisible(false, m_uiRules4);
			m_pRenderer->GetSpriteManager().SetVisible(true, m_uiRules5);	
			break;
		}
	case RULES_WAVEINFO:
		{
			m_eRulesPage = RULES_RADIALINFO;
			m_pRenderer->GetSpriteManager().SetVisible(false, m_uiRules5);
			m_pRenderer->GetSpriteManager().SetVisible(true, m_uiRules6);

			break;
		}
	case RULES_RADIALINFO:
		{
			m_eRulesPage = RULES_BUILDING;
			m_pRenderer->GetSpriteManager().SetVisible(false, m_uiRules6);
			m_pRenderer->GetSpriteManager().SetVisible(true, m_uiRules7);
			break;
		}

	case RULES_BUILDING:
		{
			CloseAll();
			break;
		}
	}
		
}



/**
*
* This function
*
* @author Daniel Langsford
* @param 
* @return 
*
*/
void
CAboutScene::ControlsNextPage()
{
	switch(m_eCOntrolsPage)
	{
	case CONTROLS_XBOXCONTROLLER:
		{
			m_eCOntrolsPage = CONTROLS_KEYBOARD;

			m_pRenderer->GetSpriteManager().SetVisible(false, m_uiController);
			m_pRenderer->GetSpriteManager().SetVisible(true, m_uiKeyBoardControls);
			break;
		}
	case CONTROLS_KEYBOARD:
		{
			m_pRenderer->GetSpriteManager().SetVisible(false, m_uiKeyBoardControls);
			CloseAll();
			break;
		}
	default: break;
	}
}

void
CAboutScene::Deinitialise()
{
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiGameControlls);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiBackGround);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiGameRules);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiCredits);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiBack);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiController);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiViewCredits);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiRules1);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiRules2);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiQuit);

}


