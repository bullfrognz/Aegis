//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   MainMenuScene.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Macros.h"
#include "Application.h"
#include "GameWindow.h"
#include "Utility.h"


#include "D3DRenderer.h"
#include "LightManager.h"
#include "Viewport.h"
#include "Camera.h"


#include "MeshManager.h"
#include "AnimatedObject.h"
#include "StaticObject.h"
#include "SoundSystem.h"

#include "InputManager.h"

#include "Vector3.h"
#include "SpriteManager.h"
#include "DeviceManager.h"


#include "SettingsSceneData.h"
#include "XInputController.h"
#include "DirectInput.h"
#include "AnimatedMesh.h"


// This Include
#include "MainMenuScene.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* MainMenuScene class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CMainMenuScene::CMainMenuScene()
: m_pAObjGameTitle(0)
, m_pSObjMenuCog(0)
, m_iMenuCogSelection(MENUCOGSEL_INVALID)
, m_uiNumMenuOptions(0)
, m_bLAnalogActive(0)
, m_bRAnalogActive(0)
, m_fTitleAnimationTimer(1.75f)
, m_bLeftClick(false)
, m_bActive(true)

{
	//Empty
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* MainMenuScene class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CMainMenuScene::~CMainMenuScene()
{
	Deinitialise();
}










/*---------------------------------------------------------------------------------------------------------------------------
*
* Processes the scene for the current frame.
*
* @author Bryce Booth
* @param _fDeltaTick	Time since last frame.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMainMenuScene::ProcessScene(float _fDeltaTick)
{
	if (m_fTitleAnimationTimer >= 0.0f)
	{
		m_pRenderer->GetMeshManager().Process(_fDeltaTick);


		m_fTitleAnimationTimer -= _fDeltaTick;
	}


	m_pAObjGameTitle->Process(_fDeltaTick);
	m_pSObjMenuCog->Process(_fDeltaTick);


	if(m_bActive)
	{
		MouseSelection();
	}


	if (m_bLAnalogActive == true)
	{
		RotateMenuCogLeft();
	}
	else if (m_bRAnalogActive == true)
	{
		RotateMenuCogRight();
	}


	ResetCursor();
}




/*---------------------------------------------------------------------------------------------------------------------------
*
* Draws the scenes' objects.
*
* @author Bryce Booth
* @param _pRenderer		Renderer of the parent window.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMainMenuScene::DrawScene(CD3DRenderer* _pRenderer)
{
	m_pViewport->Draw(_pRenderer);


	_pRenderer->GetLightManager().TurnOnLight(m_uiLightDirectional);


	m_pAObjGameTitle->Draw(_pRenderer);

	m_pSObjMenuCog->Draw(_pRenderer);

	_pRenderer->GetSpriteManager().Draw();
}




/*---------------------------------------------------------------------------------------------------------------------------
*
* Runs functionality to recover from overlay scenes.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMainMenuScene::RecoverFromOverlayScene()
{
	m_pRenderer->GetMeshManager().GetAnimatedMesh(m_pAObjGameTitle->GetMeshId())->GetAnimationController()->SetTrackPosition(0, 0);


	//Display menu cog
	DisplayMenuCog();
	DisplayMenutitle();


	//Re-enable input
	m_pInputManager->EnableInput();


	//Set active to true
	m_bActive = true;



	//Show mouse arrows
	m_pRenderer->GetSpriteManager().SetVisible(true, m_uiNextOptionIconId);
	m_pRenderer->GetSpriteManager().SetVisible(true, m_uiLastOptionIconId);
}











/********************************
            Protected
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
CMainMenuScene::InitialiseLights(CD3DRenderer* _pRenderer)
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
CMainMenuScene::InitialiseViewports(CD3DRenderer* _pRenderer)
{
	const unsigned int kuiWindowWidth  = CApplication::GetInstance().GetGameWindow().GetClientWidth();
	const unsigned int kuiWindowHeight = CApplication::GetInstance().GetGameWindow().GetClientHeight();


	m_pViewport = new CViewport();
	m_pViewport->Initialise(0, 0, kuiWindowWidth, kuiWindowHeight, 0, _pRenderer);
	int iCamera = m_pViewport->CreateCamera(3.14159682f/3.0f, 0.1f, 1000.0f);
	m_pViewport->SetActiveCamera(m_pViewport->GetLastCreatedCamera());
	m_pViewport->GetCamera(iCamera)->GetWorldMatrix().SetPositionZ(-10);


	m_pViewport->GetActiveCamera()->GetSkyBox()->SetAngularVelocityY(0.01f);


	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Runs other initialises functions specific to this scene and sets member variables.
*
* @author Bryce Booth
* @param _pRenderer		Renderer of parent window.
* @param _pSceneData	Data container for scene.
* @return true			States that the scene successfully was setup.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CMainMenuScene::InitialiseScene(CD3DRenderer* _pRenderer, void* _pSceneData)
{
	//Run initialise functions
	InitialiseGameTitle(_pRenderer);
	InitialiseMenuCog(_pRenderer);
	InitialisePlayerInputTarget();
	InitiliseSprites(_pRenderer);
	InitialiseXInputTarget();


	CApplication::GetInstance().GetGameWindow().CenterCursor();


	ResetCursor();


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
CMainMenuScene::InitialiseGameTitle(CD3DRenderer* _pRenderer)
{
	m_pAObjGameTitle = new CAnimatedObject();
	m_pAObjGameTitle->Initialise("Hello", _pRenderer, "Assets/Mesh/Menu_GameTitle.x");


	m_pAObjGameTitle->GetWorldMatrix().SetPositionY(13);
	m_pAObjGameTitle->GetWorldMatrix().SetPositionZ(18);


	DisplayMenutitle();


	m_pRenderer->GetMeshManager().GetAnimatedMesh(m_pAObjGameTitle->GetMeshId())->GetAnimationController()->SetTrackPosition(0, 0);


	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates and sets default parameters for the menu cog.
*
* @author Bryce Booth
* @param _pRenderer		Renderer of parent window.
* @return true			States that the menu cog was successfully created.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CMainMenuScene::InitialiseMenuCog(CD3DRenderer* _pRenderer)
{
	m_pSObjMenuCog = new CStaticObject();
	m_pSObjMenuCog->Initialise("Test Object", _pRenderer, "Assets\\Mesh\\MainMenu_BigCog.x");
	

	m_iMenuCogSelection = MENUCOGSEL_PLAYGAME;
	m_uiNumMenuOptions  = MENUCOGSEL_MAX - 1;


	m_v3MenuCogStartPosition.Set(0, -20, 0);
	m_v3MenuCogEndPosition.Set(0, -10, 0);


	m_fMenuCogLerpDuration = 2.0f;
	m_fMenuCogRotateDuration = 0.3f;


	DisplayMenuCog();


	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates and sets sprite positions for the mouse arrows that are used for the mouse to rotate the menu cog.
*
* @author Daniel Lansford
* @param _pRenderer		Renderer of parent window.
* @return true			States that the mouse arrows were successfully created.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CMainMenuScene::InitiliseSprites(CD3DRenderer* _pRenderer)
{	
	assert(_pRenderer);

	const unsigned int kuiWindowWidth = 1280;
	const unsigned int kuiWindowHeight = 1024;

	//OptionSelection;
	m_uiMenuSelectionId = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/MainMenu_Selection.png");
	_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiMenuSelectionId);
	_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiMenuSelectionId);

	RECT SpriteRect = _pRenderer->GetSpriteManager().GetRect(m_uiMenuSelectionId);	
	
	float fWidth = static_cast<float>(SpriteRect.right - SpriteRect.left);
	fWidth *= 0.75f;
	float fHeight = static_cast<float>(SpriteRect.bottom - SpriteRect.top);
	fHeight *= 0.25f;

	SpriteRect.right = static_cast<LONG>(fWidth);
	SpriteRect.bottom = static_cast<LONG>(fHeight);

	_pRenderer->GetSpriteManager().SetRect(&SpriteRect, m_uiMenuSelectionId);
	_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiMenuSelectionId);

	CVector3 vecPos;
	vecPos.x = static_cast<float>(kuiWindowWidth / 2 - fWidth / 2);
	vecPos.y = static_cast<float>(kuiWindowHeight * 0.75f);

	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiMenuSelectionId);

	//Next option icon
	m_uiNextOptionIconId = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SettingsMenu_ArrowRight.png");
	_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiNextOptionIconId);
	_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiNextOptionIconId);

	vecPos;
	vecPos.x = static_cast<float>(kuiWindowWidth * 0.8f);
	vecPos.y = static_cast<float>(kuiWindowHeight * 0.8f);

	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiNextOptionIconId);

	//Previous option icon
	m_uiLastOptionIconId = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SettingsMenu_ArrowLeft.png");
	_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiLastOptionIconId);
	_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiLastOptionIconId);

	vecPos;
	vecPos.x = static_cast<float>(kuiWindowWidth) * 0.1f;
	vecPos.y = static_cast<float>(kuiWindowHeight) * 0.8f;

	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiLastOptionIconId);



	return(true);
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Resets the cursor for the main menu scene.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMainMenuScene::ResetCursor()
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
* Displays the menu title.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMainMenuScene::DisplayMenutitle()
{	
	m_fTitleAnimationTimer = 1.75f;


	m_pAObjGameTitle->SetVisible(true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Hides the menu title.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMainMenuScene::HideMenuTitle()
{
	m_pAObjGameTitle->SetVisible(false);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets parameters for the menu cog to display.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMainMenuScene::DisplayMenuCog()
{
	m_pSObjMenuCog->GetWorldMatrix().SetPosition(m_v3MenuCogStartPosition);
	m_pSObjMenuCog->LerpPosition(m_v3MenuCogEndPosition, m_fMenuCogLerpDuration);
	m_pSObjMenuCog->LerpRotation(MathUtility::PI * 4, m_fMenuCogLerpDuration, AXIS_Z);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets parameters for the menu cog to hide.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMainMenuScene::HideMenuCog()
{
	m_pSObjMenuCog->GetWorldMatrix().SetPosition(m_v3MenuCogEndPosition);
	m_pSObjMenuCog->LerpPosition(m_v3MenuCogStartPosition, m_fMenuCogLerpDuration);
	m_pSObjMenuCog->LerpRotation(MathUtility::PI * 4, m_fMenuCogLerpDuration, AXIS_Z);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* Rotates the menu cog right.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMainMenuScene::RotateMenuCogRight()
{
	bool bLerping = m_pSObjMenuCog->IsLerpingInProgress();


	if (bLerping == false)
	{
		m_pSObjMenuCog->LerpRotation(-MathUtility::PI * 2.0f / m_uiNumMenuOptions, m_fMenuCogRotateDuration, AXIS_Z);

		CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");

		
		++ m_iMenuCogSelection;


		if (m_iMenuCogSelection == MENUCOGSEL_MAX)
		{
			m_iMenuCogSelection = MENUCOGSEL_PLAYGAME;
		}
	}
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* Rotates the menu cog left.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMainMenuScene::RotateMenuCogLeft()
{
	bool bLerping = m_pSObjMenuCog->IsLerpingInProgress();


	if (bLerping == false)
	{
		m_pSObjMenuCog->LerpRotation(MathUtility::PI * 2.0f / m_uiNumMenuOptions, m_fMenuCogRotateDuration, AXIS_Z);

		CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");

		-- m_iMenuCogSelection;


		if (m_iMenuCogSelection == MENUCOGSEL_MIN)
		{
			m_iMenuCogSelection = MENUCOGSEL_QUIT;
		}
	}
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* Calculates the mouse position and checks if the mouse has click on the menu cog option or the menu cog rotate sprites
*
* @author Daniel Lansford
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMainMenuScene::MouseSelection()
{
	CWindow& rGameWindow = CApplication::GetInstance().GetGameWindow();
	unsigned int kuiWindowWidth = rGameWindow.GetClientWidth();
	unsigned int kuiWindowHeight = rGameWindow.GetClientHeight();

	COORD MouseCords;
	MouseCords = CApplication::GetInstance().GetGameWindow().GetMosueCoords();
	CD3DRenderer* pRenderer = CApplication::GetInstance().GetGameWindow().GetRenderer();
	
	
	RECT SpriteBounds = pRenderer->GetSpriteManager().GetRect(m_uiMenuSelectionId);

	float fWidth = static_cast<float>(SpriteBounds.right - SpriteBounds.left);
	fWidth *= 0.75f;
	float fHeight = static_cast<float>(SpriteBounds.bottom - SpriteBounds.top);
	fHeight *= 0.25f;

	fWidth =((kuiWindowWidth / 1280.0f) * fWidth);
	fHeight =  ((kuiWindowHeight / 1024.0f) * fWidth);

	SpriteBounds.right = static_cast<LONG>(fWidth);
	SpriteBounds.bottom = static_cast<LONG>(fHeight);

	CVector3 vecPos = pRenderer->GetSpriteManager().GetPositionScaled(m_uiMenuSelectionId);

	//Select option
	SpriteBounds.left   =	static_cast<LONG>(vecPos.x);
	SpriteBounds.right  =	static_cast<LONG>(vecPos.x + fWidth);
	SpriteBounds.top    =	static_cast<LONG>(vecPos.y);
	SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + fHeight);

	if(MouseCords.X >= SpriteBounds.left &&
	   MouseCords.X <= SpriteBounds.right &&
	   MouseCords.Y >= SpriteBounds.top &&
	   MouseCords.Y <= SpriteBounds.bottom)
	{
		if(m_bLeftClick)
		{
			ExecuteMenuCogSelection();
		}
	}

	//Next option
	SpriteBounds = pRenderer->GetSpriteManager().GetRect(m_uiNextOptionIconId);
	int iWidth = SpriteBounds.right - SpriteBounds.left;
	int iHeight = SpriteBounds.bottom - SpriteBounds.top;

	iWidth = static_cast<unsigned int>((kuiWindowWidth / 1280.0f) * iWidth);
	iHeight =  static_cast<unsigned int>((kuiWindowHeight / 1024.0f) * iHeight);

	vecPos = pRenderer->GetSpriteManager().GetPositionScaled(m_uiNextOptionIconId);
	
	SpriteBounds.left   =	static_cast<LONG>(vecPos.x);
	SpriteBounds.right  =	static_cast<LONG>(vecPos.x + iWidth);
	SpriteBounds.top    =	static_cast<LONG>(vecPos.y);
	SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + iHeight);

	if(MouseCords.X >= SpriteBounds.left &&
	   MouseCords.X <= SpriteBounds.right &&
	   MouseCords.Y >= SpriteBounds.top &&
	   MouseCords.Y <= SpriteBounds.bottom)
	{
		if(m_bLeftClick)
		{
			RotateMenuCogRight();
		}

	}

	//Previous option
	SpriteBounds = pRenderer->GetSpriteManager().GetRect(m_uiLastOptionIconId);
	iWidth = SpriteBounds.right - SpriteBounds.left;
	iHeight = SpriteBounds.bottom - SpriteBounds.top;

	iWidth = static_cast<unsigned int>((kuiWindowWidth / 1280.0f) * iWidth);
	iHeight =  static_cast<unsigned int>((kuiWindowHeight / 1024.0f) * iHeight);

	vecPos = pRenderer->GetSpriteManager().GetPositionScaled(m_uiLastOptionIconId);
	
	SpriteBounds.left   =	static_cast<LONG>(vecPos.x);
	SpriteBounds.right  =	static_cast<LONG>(vecPos.x + iWidth);
	SpriteBounds.top    =	static_cast<LONG>(vecPos.y);
	SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + iHeight);

	if(MouseCords.X >= SpriteBounds.left &&
	   MouseCords.X <= SpriteBounds.right &&
	   MouseCords.Y >= SpriteBounds.top &&
	   MouseCords.Y <= SpriteBounds.bottom)
	{
		if(m_bLeftClick)
		{
			RotateMenuCogLeft();
		}

	}

}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Runs functionality to execute the current menu cog selection.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMainMenuScene::ExecuteMenuCogSelection()
{
	CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Select.wav");

	switch (m_iMenuCogSelection)
	{
	case MENUCOGSEL_PLAYGAME:
		{
			HideMenuCog();
			HideMenuTitle();
			m_pRenderer->GetSpriteManager().SetVisible(false, m_uiNextOptionIconId);
			m_pRenderer->GetSpriteManager().SetVisible(false, m_uiLastOptionIconId);

			m_bActive = false;

			m_pInputManager->DisableInput();
			

			CApplication::GetInstance().GetGameWindow().SetOverlayScene(OVERLAYSCENE_SELECTMAP);
		}
		break;

	case MENUCOGSEL_OPTIONS:
		{
			HideMenuCog();
			HideMenuTitle();
			m_pRenderer->GetSpriteManager().SetVisible(false, m_uiNextOptionIconId);
			m_pRenderer->GetSpriteManager().SetVisible(false, m_uiLastOptionIconId);

			m_bActive = false;

			m_pInputManager->DisableInput();


			CSettingsSceneData* pSettingsSceneData = new CSettingsSceneData;
			pSettingsSceneData->SetSceneTypeId(SCENE_MAINMENU);
			pSettingsSceneData->SetSceneTypeMainScene(true);
			

			CApplication::GetInstance().GetGameWindow().SetOverlayScene(OVERLAYSCENE_SETTINGS, pSettingsSceneData);
		}
		break;

	case MENUCOGSEL_MAPEDITOR:
		{
			//Map editor must be run in windowed mode.
			CWindow& rGameWindow = CApplication::GetInstance().GetGameWindow();
			const unsigned int kuiWindowWidth = rGameWindow.GetWindowWidth();
			const unsigned int kuiWindowHeight = rGameWindow.GetWindowHeight();

			CApplication::GetInstance().GetGameWindow().ResizeWindow(kuiWindowWidth,
																	 kuiWindowHeight,
																	 0,
																	 false);

			m_pRenderer->GetDeviceManager().ScheduleDeviceReset();

			CApplication::GetInstance().GetGameWindow().SetMainScene(SCENE_MAPEDITOR);
		}
		break;

	case MENUCOGSEL_ABOUT:
		{
			HideMenuCog();
			HideMenuTitle();
			m_pRenderer->GetSpriteManager().SetVisible(false, m_uiNextOptionIconId);
			m_pRenderer->GetSpriteManager().SetVisible(false, m_uiLastOptionIconId);

			m_bActive = false;

			m_pInputManager->DisableInput();

			CApplication::GetInstance().GetGameWindow().SetOverlayScene(OVERLAYSCENE_ABOUT);
			m_bActive = false;
		}

		break;

	case MENUCOGSEL_QUIT:
		CApplication::GetInstance().Quit();
		break;
	}


	m_bLeftClick = false;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Handles the direct input messages for the scene.
*
* @author Bryce Booth
* @param _eDMouse	Which button on the mouse was triggered
* @param _bDown		If the button is down.
* @param _fValue	The value of the button, if any.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMainMenuScene::HandleDMouseInput(EDInputMouse _eDMouse, bool _bDown, long _lValue)
{
	switch (_eDMouse)
	{
	case DMOUSE_LEFTCLICK:
		{		
			m_bLeftClick = _bDown;

			break;
		}

	case DMOUSE_WHEEL:
		{
			if(_lValue >= 120)
			{
				RotateMenuCogLeft();
			}
			else if (_lValue <=  -120)
			{
				RotateMenuCogRight();
			}
			break;
		}
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Handles the direct input keyboard messages for the scene.
*
* @author Bryce Booth
* @param _eDMouse	Which button on the keyboard was triggered.
* @param _bDown		If the button is down.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMainMenuScene::HandleDKeyboardInput(EDInputKeyboard _eDKebyoard, bool _bDown)
{
	//Key was down
	if (_bDown)
	{
		switch (_eDKebyoard)
		{
			case DKEYBOARD_A:
			case DKEYBOARD_LEFTARROW:
				{
					m_bLAnalogActive = true;
					break;
				}

			case DKEYBOARD_D:
			case DKEYBOARD_RIGHTARROW:
				{
					m_bRAnalogActive = true;
					break;
				}
			case DKEYBOARD_ENTER:
			case DKEYBOARD_SPACE:
				{
					ExecuteMenuCogSelection();
					break;
				}
		}
	}
	//Key was released
	else
	{
		switch (_eDKebyoard)
		{
			case DKEYBOARD_A:
			case DKEYBOARD_LEFTARROW:
				{
					m_bLAnalogActive = false;
					break;
				}

			case DKEYBOARD_D:
			case DKEYBOARD_RIGHTARROW:
				{
					m_bRAnalogActive = false;
					break;
				}
		}
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Handles button messages from the controller. 
*
* @author Bryce Booth
* @param _eXButton	The button that has been triggered.
* @param _bDown		If the button was down.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMainMenuScene::HandleXButtonInput(EXInputButton _eXButton, bool _bDown)
{
	switch (_eXButton)
	{
	case XBUTTON_A:
		if (_bDown)
		{
			ExecuteMenuCogSelection();
		}
		break;
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
CMainMenuScene::HandleXAnalogInput(EXInputAnalog _eXAnalog, float _fValue)
{
	switch (_eXAnalog)
	{
	case XANALOG_LEFTX:
		{
			if (_fValue >= 0.8f)
			{
				m_bRAnalogActive = true;
			}
			else if (_fValue <= -0.8f)
			{
				m_bLAnalogActive = true;
			}
			else
			{
				m_bRAnalogActive = false;
				m_bLAnalogActive = false;
			}
		}
		break;
	}
}










/********************************
            Private
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Tells input manager which mouse and keyboard buttons the scene wants.
*
* @author Bryce Booth
* @return true	Input manager was succcessfully configured.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CMainMenuScene::InitialisePlayerInputTarget()
{
	//Mouse
	m_pInputManager->GetDirectInput().AddTarget(DMOUSE_LEFTCLICK, this);
	m_pInputManager->GetDirectInput().AddTarget(DMOUSE_WHEEL, this);


	//Keybaord
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_LEFTARROW, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_RIGHTARROW, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_SPACE, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_A, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_D, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_ENTER, this);


	return (true);
}



/*---------------------------------------------------------------------------------------------------------------------------
*
* Tells input manager which conntroller messages the scene wants.
*
* @author Bryce Booth
* @return true	Input manager was succcessfully configured.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CMainMenuScene::InitialiseXInputTarget()
{
	//XInput Controller
	m_pInputManager->GetXInputController().AddTarget(XBUTTON_A, this);
	m_pInputManager->GetXInputController().AddTarget(XANALOG_LEFTX, this);
	m_pInputManager->GetXInputController().AddTarget(XANALOG_LEFTY, this);


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
CMainMenuScene::Deinitialise()
{
	m_pRenderer->GetSpriteManager().EraseAll();

	FW_DELETE(m_pAObjGameTitle);
	FW_DELETE(m_pSObjMenuCog);


	m_pRenderer->GetLightManager().RemoveLight(m_uiLightDirectional);
}