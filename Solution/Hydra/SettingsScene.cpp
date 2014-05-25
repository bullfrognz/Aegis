//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   SettingsScene.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <vector>


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
#include "SettingsSceneData.h"
#include "DirectInput.h"
#include "XInputController.h"
#include "GameScene.h"
#include "Hud.h"
#include "RadialMenu.h"


// This Include
#include "SettingsScene.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* SettingsScene class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CSettingsScene::CSettingsScene()
: m_uiSettingsLogo(0)
, m_uiResolutionTitle(0)
, m_uiResolutionArrowLeft(0)
, m_uiResolutionArrowRight(0)
, m_uiModeTitle(0)
, m_uiModeArrowLeft(0)
, m_uiModeArrowRight(0)
, m_uiMultisamplingTitle(0)
, m_uiMultisamplingArrowLeft(0)
, m_uiMultisamplingArrowRight(0)
, m_uiVolumeTitle(0)
, m_uiVolumeArrowLeft(0)
, m_uiVolumeArrowRight(0)
, m_uiSaveTitle(0)
, m_uiBackTitle(0)
, m_eCurrentOption(SETTINGSOPTION_RESOLUTION)
, m_fChangeSectionDelay(0)
, m_fChangeSectionTimer(0)
, m_fChangeValueDelay(0)
, m_fChangeValueTimer(0)
, m_uiResolutionMode(0)
, m_bWindowMode(0)
, m_uiMultiSampleType(0)
, m_fVolume(0)
, m_bMouseClick(false)
, m_bSpriteSelected(false)
, m_bIncrementValue(false)
, m_bDecrementValue(false)
, m_bIncrementSection(false)
, m_bDecrementSection(false)
{
	//Empty
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* SettingsScene class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CSettingsScene::~CSettingsScene()
{
	Deinitialise();
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* This function initialisings the class instance before use.
*
* @author Bryce Booth
* @param _pRenderer		Renderer for the window
* @param _pSceneData	Pointer to a container of data for the scene.
* @return true			Inditates the class initialised successfully.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CSettingsScene::InitialiseScene(CD3DRenderer* _pRenderer, void* _pSceneData)
{
	assert(_pSceneData);

	//Member variables
	m_pSettingsSceneData = reinterpret_cast<CSettingsSceneData*>(_pSceneData);
	m_fChangeSectionDelay = 0.2f;
	m_fChangeValueDelay = 0.2f;
	bool bFullscreen = CApplication::GetInstance().GetGameWindow().IsFullscreen();

	//Run initialise functions
	FW_VALIDATE(InitialisePlayerInputTarget(), "Settings scene player input target initialise failed.");
	FW_VALIDATE(InitialiseXInputTarget(), "Settings scene x input target initialise failed.");
	FW_VALIDATE(InitialiseSprites(_pRenderer), "Settings scene sprites initialise failed.");
	FW_VALIDATE(InitialiseSpritePositons(_pRenderer), "Settings scene sprites position initialise failed.");
	FW_VALIDATE(InitialiseResolutions(_pRenderer), "Settings scene resolution initialise failed.");
	FW_VALIDATE(InitialiseModeTypes(), "Settings scene mode types initialise failed.");
	FW_VALIDATE(InitialiseMultiSamplingTypes(_pRenderer, bFullscreen), "Settings scene multisampling types initialise failed.");
	FW_VALIDATE(InitialiseVolumeTypes(), "Settings scene volume levels initialise failed.");
	FW_VALIDATE(InitialiseText(_pRenderer), "Settings scene text initialise failed.");

	//Execute aditional functions
	UpdateSectionSprites();
	UpdateSectionText();


	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Processes the class instance for the current frame.
*
* @author Bryce Booth
* @param  _fDeltaTick	The time elasped since last process
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSettingsScene::ProcessScene(float _fDeltaTick)
{
	//Incrment timers
	m_fChangeSectionTimer += _fDeltaTick;
	m_fChangeValueTimer += _fDeltaTick;

	if (m_pInputManager->GetXInputController().IsPluggedIn() == false)
	{
		SpriteSelection();


		if(!m_bSpriteSelected)
		{
			TextSelection();
		}
	}


	if (m_bIncrementValue == true)
	{
		IncrementSectionValue();
	}
	else if (m_bDecrementValue == true)
	{
		DecrementSectionValue();
	}


	if (m_bIncrementSection == true)
	{
		IncrementCurrentSection();
	}
	else if (m_bDecrementSection == true)
	{
		DecrementCurrentSection();
	}


	ResetCursor();
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Calls draw for the current scene.
*
* @author Bryce Booth
* @param _pRenderer	Renderer for the window
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSettingsScene::DrawScene(CD3DRenderer* _pRenderer)
{
	m_TextResolution.Draw(_pRenderer);
	m_TextMode.Draw(_pRenderer);
	m_TextMultiSample.Draw(_pRenderer);
	m_TextVolume.Draw(_pRenderer);
}








/********************************
            Protected
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Initialises the lights for the scene
*
* @author Bryce Booth
* @param _pRenderer		Renderer for the window
* @return true			Light successfully setup.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CSettingsScene::InitialiseLights(CD3DRenderer* _pRenderer)
{
	//Ask light manager to add light
	m_uiLightDirectional = _pRenderer->GetLightManager().AddLight();


	//Update light position
	_pRenderer->GetLightManager().UpdateParam(m_uiLightDirectional, DIRECTION, CVector3(0.5f, -0.3f, 1.0f));


	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Create viewport for scene.
*
* @author Bryce Booth
* @param _pRenderer		Renderer for the window
* @return true			Viewport successfully setup.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CSettingsScene::InitialiseViewports(CD3DRenderer* _pRenderer)
{
	//Empty



	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Handles the direct input messages for the scene.
*
* @author Bryce Booth
* @param _eDMouse	Which button on the mouse was triggered.
* @param _bDown		If the button is down.
* @param _fValue	The value of the button, if any.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSettingsScene::HandleDMouseInput(EDInputMouse _eDMouse, bool _bDown, long _lValue)
{
	switch (_eDMouse)
	{
	case DMOUSE_LEFTCLICK:
		{
			m_bMouseClick = _bDown;
			break;
		}


	case DMOUSE_WHEEL:
		{
			if(_lValue > -120)
			{
				IncrementSectionValue();
			}
			 else if(_lValue < 120)
			{
				DecrementSectionValue();
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
CSettingsScene::HandleDKeyboardInput(EDInputKeyboard _eDKebyoard, bool _bDown)
{
	if (_bDown)
	{
		switch (_eDKebyoard)
		{
		case DKEYBOARD_A:	//Fall through
		case DKEYBOARD_LEFTARROW:
			{
				m_bDecrementValue = true;
			}
			break;

		case DKEYBOARD_D:	//Fall through
		case DKEYBOARD_RIGHTARROW:
			{
				m_bIncrementValue = true;
			}
			break;

		case DKEYBOARD_S:	//Fall through
		case DKEYBOARD_DOWNARROW:
			{
				m_bIncrementSection = true;
			}
			break;

		case DKEYBOARD_W:	//Fall through
		case DKEYBOARD_UPARROW:
			{
				m_bDecrementSection = true;
			}
			break;

		case DKEYBOARD_ENTER: //Fall through
		case DKEYBOARD_SPACE:
			{
				if (m_eCurrentOption == SETTINGSOPTION_SAVE)
				{
					ExecuteSaveSettings();
				}
				else if (m_eCurrentOption == SETTINGSOPTION_BACK)
				{
					ReturnToBeforeScene();
				}
			}
			break;

		case DKEYBOARD_ESCAPE: //Fall through
		case DKEYBOARD_BACK:
			{
				ReturnToBeforeScene();
			}
			break;
		}
	}
	else
	{
		switch (_eDKebyoard)
		{
		case DKEYBOARD_A:	//Fall through
		case DKEYBOARD_LEFTARROW:
			{
				m_bDecrementValue = false;
			}
			break;

		case DKEYBOARD_D:	//Fall through
		case DKEYBOARD_RIGHTARROW:
			{
				m_bIncrementValue = false;
			}
			break;

		case DKEYBOARD_S:	//Fall through
		case DKEYBOARD_DOWNARROW:
			{
				m_bIncrementSection = false;
			}
			break;

		case DKEYBOARD_W:	//Fall through
		case DKEYBOARD_UPARROW:
			{
				m_bDecrementSection = false;
			}
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
CSettingsScene::HandleXAnalogInput(EXInputAnalog _eXAnalog, float _fValue)
{
	switch (_eXAnalog)
	{
		case XANALOG_LEFTX:
		{
			if (_fValue >= 0.8f)
			{
				IncrementSectionValue();
			}
			else if (_fValue <= -0.8f)
			{
				DecrementSectionValue();
			}
			break;
		}


		case XANALOG_LEFTY:
		{
			if (_fValue >= 0.8f && m_fChangeSectionTimer > m_fChangeSectionDelay)
			{
				DecrementCurrentSection();


				m_fChangeSectionTimer = 0;
			}
			else if (_fValue <= -0.8f && m_fChangeSectionTimer > m_fChangeSectionDelay)
			{
				IncrementCurrentSection();


				m_fChangeSectionTimer = 0;
			}
			break;
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
CSettingsScene::HandleXButtonInput(EXInputButton _eXButton, bool _bDown)
{
	if (_bDown)
	{
		switch (_eXButton)
		{
			case XBUTTON_A:
			{
				if (_bDown)
				{
					if (m_eCurrentOption == SETTINGSOPTION_SAVE)
					{
						ExecuteSaveSettings();
					}
					else if (m_eCurrentOption == SETTINGSOPTION_BACK)
					{
						ReturnToBeforeScene();
					}
				}
				break;
			}


		case XBUTTON_B:
			{
				if (_bDown)
				{
					ReturnToBeforeScene();
				}
				break;
			}
		}
	}
}







/********************************
            Private
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Configures direct input for which commands the scene is looking for.
*
* @author Bryce Booth
* @return true	States the configuration was successful 
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CSettingsScene::InitialisePlayerInputTarget()
{
	//Ask for a, d, w, s and return keys
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


	//Initialise Mouse controls
	m_pInputManager->GetDirectInput().AddTarget(DMOUSE_LEFTCLICK, this);
	m_pInputManager->GetDirectInput().AddTarget(DMOUSE_RIGHTCLICK, this);
	m_pInputManager->GetDirectInput().AddTarget(DMOUSE_WHEEL, this);


	//Return successful
	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Configures the xinput controller for which commands the scene is looking for.
*
* @author Bryce Booth
* @return true	States the configuration was successful 
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CSettingsScene::InitialiseXInputTarget()
{
	m_pInputManager->GetXInputController().AddTarget(XBUTTON_A, this);
	m_pInputManager->GetXInputController().AddTarget(XBUTTON_B, this);
	m_pInputManager->GetXInputController().AddTarget(XANALOG_LEFTX, this);
	m_pInputManager->GetXInputController().AddTarget(XANALOG_LEFTY, this);


	//Return successful
	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates sprites for the scene.
*
* @author Bryce Booth
* @param _pRenderer	Renderer for the window
* @return true	States the configuration was successful 
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CSettingsScene::InitialiseSprites(CD3DRenderer* _pRenderer)
{	
	//Settings
	m_uiSettingsBackground = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SettingsMenu_Background.png");
	m_uiSettingsLogo       = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SettingsMenu_Logo.png");


	//Resolution
	m_uiResolutionTitle      = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SettingsMenu_Resolution.png");
	m_uiResolutionArrowLeft  = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SettingsMenu_ArrowLeft.png");
	m_uiResolutionArrowRight = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SettingsMenu_ArrowRight.png");


	//Mode
	m_uiModeTitle      = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SettingsMenu_Mode.png");
	m_uiModeArrowLeft  = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SettingsMenu_ArrowLeft.png");
	m_uiModeArrowRight = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SettingsMenu_ArrowRight.png");


	//Multisampling
	m_uiMultisamplingTitle      = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SettingsMenu_MultiSampling.png");
	m_uiMultisamplingArrowLeft  = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SettingsMenu_ArrowLeft.png");
	m_uiMultisamplingArrowRight = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SettingsMenu_ArrowRight.png");


	//Volume
	m_uiVolumeTitle      = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SettingsMenu_Volume.png");
	m_uiVolumeArrowLeft  = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SettingsMenu_ArrowLeft.png");
	m_uiVolumeArrowRight = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SettingsMenu_ArrowRight.png");


	//Settings
	m_uiSaveTitle = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SettingsMenu_Save.png");
	m_uiBackTitle = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SettingsMenu_Back.png");


	//Return successful
	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Configures the sprite's positions.
*
* @author Bryce Booth
* @param _pRenderer	Renderer for the window
* @return true	States the configuration was successful 
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CSettingsScene::InitialiseSpritePositons(CD3DRenderer* _pRenderer)
{
	//Get application base width and height
	const float kfBaseWidth  = CApplication::GetInstance().GetBaseWidth();
	const float kfBaseHeight = CApplication::GetInstance().GetBaseHeight();


	//Calculate half width and height
	const float kfHalfBaseWidth  = kfBaseWidth  / 2.0f;
	const float kfHalfBaseHeight = kfBaseHeight / 2.0f;


	//Convert to float
	const float kfLeftArrowX  = static_cast<float>(s_uiLeftArrowMarginX);
	const float kfRightArrowX = static_cast<float>(s_uiRightArrowMartinX);


	//Default varaibles
	const float kfSectionX = 250;


	//Settings
	_pRenderer->GetSpriteManager().SetPosition(CVector3(kfHalfBaseWidth, kfHalfBaseHeight, 0.0f), m_uiSettingsBackground);
	_pRenderer->GetSpriteManager().SetPosition(CVector3(kfHalfBaseWidth, 180.0f, 0.0f), m_uiSettingsLogo);


	//Resolution
	_pRenderer->GetSpriteManager().SetPosition(CVector3(kfSectionX, 300.0f, 0.0f), m_uiResolutionTitle);
	_pRenderer->GetSpriteManager().SetPosition(CVector3(kfLeftArrowX, 300.0f, 0.0f), m_uiResolutionArrowLeft);
	_pRenderer->GetSpriteManager().SetPosition(CVector3(kfRightArrowX, 300.0f, 0.0f), m_uiResolutionArrowRight);


	//Mode
	_pRenderer->GetSpriteManager().SetPosition(CVector3(kfSectionX, 400.0f, 0.0f), m_uiModeTitle);
	_pRenderer->GetSpriteManager().SetPosition(CVector3(kfLeftArrowX, 400.0f, 0.0f), m_uiModeArrowLeft);
	_pRenderer->GetSpriteManager().SetPosition(CVector3(kfRightArrowX, 400.0f, 0.0f), m_uiModeArrowRight);


	//Multisampling
	_pRenderer->GetSpriteManager().SetPosition(CVector3(kfSectionX, 500.0f, 0.0f), m_uiMultisamplingTitle);
	_pRenderer->GetSpriteManager().SetPosition(CVector3(kfLeftArrowX, 500.0f, 0.0f), m_uiMultisamplingArrowLeft);
	_pRenderer->GetSpriteManager().SetPosition(CVector3(kfRightArrowX, 500.0f, 0.0f), m_uiMultisamplingArrowRight);


	//Volume
	_pRenderer->GetSpriteManager().SetPosition(CVector3(kfSectionX, 600.0f, 0.0f), m_uiVolumeTitle);
	_pRenderer->GetSpriteManager().SetPosition(CVector3(kfLeftArrowX, 600.0f, 0.0f), m_uiVolumeArrowLeft);
	_pRenderer->GetSpriteManager().SetPosition(CVector3(kfRightArrowX, 600.0f, 0.0f), m_uiVolumeArrowRight);


	//Save
	_pRenderer->GetSpriteManager().SetPosition(CVector3(850.0f, 720.0f, 0.0f), m_uiSaveTitle);
	_pRenderer->GetSpriteManager().SetPosition(CVector3(850.0f, 810.0f, 0.0f), m_uiBackTitle);
	
	
	//Return successful
	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Adds all supported resolutions of the computer into container.
*
* @author Bryce Booth
* @param _pRenderer	Renderer for the window
* @return true	States the configuration was successful 
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CSettingsScene::InitialiseResolutions(CD3DRenderer* _pRenderer)
{
	//Default varaibles
	char* cpBuffer = 0;


	//Get window variables
	unsigned int uiWindowWidth  = CApplication::GetInstance().GetGameWindow().GetWindowWidth();
	unsigned int uiWindowHeight = CApplication::GetInstance().GetGameWindow().GetWindowHeight();
	bool bFullscreen            = CApplication::GetInstance().GetGameWindow().IsFullscreen();


	//Get renderer refresh rate
	unsigned int uiRefreshRate = _pRenderer->GetPresentParameters().FullScreen_RefreshRateInHz;


	//Get supported display modes
	_pRenderer->GetSupportedDisplayModes(m_vecDisplayModes);


	//Loop through number of modes
	for (unsigned int i = 0; i < static_cast<unsigned int>(m_vecDisplayModes.size()); ++i)
	{
		//Instance char array
		cpBuffer = new char[256];


		//Create resolution text
		sprintf_s(cpBuffer, 256, "%d x %d %dHz", m_vecDisplayModes[i].Width, m_vecDisplayModes[i].Height, m_vecDisplayModes[i].RefreshRate);


		//Insert resolition into map
		m_mapResolutionTypes.insert( std::pair<unsigned int, char*>(i, cpBuffer) );


		//Check if mode resolution is current window resolution
		if (uiWindowWidth == m_vecDisplayModes[i].Width && uiWindowHeight == m_vecDisplayModes[i].Height)
		{
			//Check if fullscreen
			if (bFullscreen == true)
			{
				//Check if refresh rate is the same
				if (m_vecDisplayModes[i].RefreshRate == uiRefreshRate)
				{
					//Set current resolution
					m_uiResolutionMode = i;
				}
			}
			else
			{
				//Set current resolution
				m_uiResolutionMode = i;
			}
		}
	}


	//Return successful
	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Initialises the mode types and sets the current mode
*
* @author Bryce Booth
* @return true		States the configuration was successful 
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CSettingsScene::InitialiseModeTypes()
{
	//Get window is fullscreen
	bool bFullscreen = CApplication::GetInstance().GetGameWindow().IsFullscreen();


	//Insert modes
	m_mapModeTypes.insert( std::pair<bool, char*>(true, "Window    ") );
	m_mapModeTypes.insert( std::pair<bool, char*>(false, "Fullscreen") );


	//Check if windowed
	if (bFullscreen == false)
	{
		//Set windowed
		m_bWindowMode = true;
	}
	else
	{
		//Set fullscreen
		m_bWindowMode = false;
	}
	

	//Return successful
	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Finds all support multisampling levels and adds them to container.
*
* @author Bryce Booth
* @param _pRenderer		Renderer for the window.
* @param _bFullscreen	If the window is fullscreen.
* @return true	States the configuration was successful .
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CSettingsScene::InitialiseMultiSamplingTypes(CD3DRenderer* _pRenderer, bool _bFullscreen)
{
	//Clean previous multisample types
	FW_DELETEMAP(unsigned int, char*, m_mapMultiSampleTypes);


	//Default variables
	std::vector<D3DMULTISAMPLE_TYPE> vecMultisamplingTypes;
	char* cpBuffer = 0;


	//Get supported multisample types
	_pRenderer->GetSupportedMultiSamplingTypes(vecMultisamplingTypes, _bFullscreen);


	//Loop through all multisample types
	for(unsigned int i = 0; i < static_cast<unsigned int>(vecMultisamplingTypes.size()); ++ i)
	{
		//Create buffer
		cpBuffer = new char[128];


		//Create text
		sprintf_s(cpBuffer, 128, "%d", vecMultisamplingTypes[i]);

	
		//Insert data into container
		m_mapMultiSampleTypes.insert( std::pair<unsigned int, char*>(vecMultisamplingTypes[i], cpBuffer) );
	}


	//Get current multisample type
	m_uiMultiSampleType = static_cast<unsigned int>(_pRenderer->GetPresentParameters().MultiSampleType);


	//Return successful
	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Adds a list of sound volume values to container.
*
* @author Bryce Booth
* @return true	States the configuration was successful .
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CSettingsScene::InitialiseVolumeTypes()
{
	//Insert 0-100% values
	m_mapVolumeTypes.insert( std::pair<float, char*>(0.0f, "0% ") );
	m_mapVolumeTypes.insert( std::pair<float, char*>(0.1f, "10% ") );
	m_mapVolumeTypes.insert( std::pair<float, char*>(0.2f, "20% ") );
	m_mapVolumeTypes.insert( std::pair<float, char*>(0.3f, "30% ") );
	m_mapVolumeTypes.insert( std::pair<float, char*>(0.4f, "40% ") );
	m_mapVolumeTypes.insert( std::pair<float, char*>(0.5f, "50% ") );
	m_mapVolumeTypes.insert( std::pair<float, char*>(0.6f, "60% ") );
	m_mapVolumeTypes.insert( std::pair<float, char*>(0.7f, "70% ") );
	m_mapVolumeTypes.insert( std::pair<float, char*>(0.8f, "80% ") );
	m_mapVolumeTypes.insert( std::pair<float, char*>(0.9f, "90% ") );
	m_mapVolumeTypes.insert( std::pair<float, char*>(1.0f, "100%") );


	//Get current volume
	m_fVolume = CSoundSystem::GetInstance()->GetVolume();


	//Check volume out of range
	if (m_fVolume > 1.0f || m_fVolume < 0.0f)
	{
		//Set default volume
		m_fVolume = 1.0f;
		CSoundSystem::GetInstance()->GlobalVolume(m_fVolume);
	}


	//Return successful
	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Configures setting's text positions on screen.
*
* @author Bryce Booth
*
* @param _pRenderer		Renderer for the window.
*
* @return true			States the configuration was successful .
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CSettingsScene::InitialiseText(CD3DRenderer* _pRenderer)
{
	//Get window width and height
	const float kfWindowWidth  = static_cast<float>(CApplication::GetInstance().GetGameWindow().GetClientWidth());
	const float kfWindowHeight = static_cast<float>(CApplication::GetInstance().GetGameWindow().GetClientHeight());


	//Caluclate current resolution ratios
	const float kfWidthRatio  = kfWindowWidth / 1280.0f;
	const float kfHeightRatio = kfWindowHeight / 1024.0f;


	//Default varaibles
	const float kfFontSize = 35.0f;


	//Get base ratio
	const float kfBaseRatio = CApplication::GetInstance().GetBaseDimentionRatio();


	//Resolution
	m_TextResolution.Initialise(_pRenderer);
	m_TextResolution.SetPositionX(static_cast<int>(735.0f * kfWidthRatio));
	m_TextResolution.SetPositionY(static_cast<int>(278.0f * kfHeightRatio));
	m_TextResolution.SetFontSize(static_cast<int>(kfFontSize * kfBaseRatio));
	m_TextResolution.SetWeightHeavy(true);
	//m_TextResolution.SetFormat(DT_CENTER | DT_TOP);



	//Mode
	m_TextMode.Initialise(_pRenderer);
	m_TextMode.SetPositionX(static_cast<int>(680.0f * kfWidthRatio));
	m_TextMode.SetPositionY(static_cast<int>(380.0f * kfHeightRatio));
	m_TextMode.SetFontSize(static_cast<int>(kfFontSize * kfBaseRatio));
	m_TextMode.SetWeightHeavy(true);
	m_TextMode.SetFormat(DT_CENTER | DT_TOP);



	//Multisampling
	m_TextMultiSample.Initialise(_pRenderer);
	m_TextMultiSample.SetPositionX(static_cast<int>(825.0f * kfWidthRatio));
	m_TextMultiSample.SetPositionY(static_cast<int>(481.0f * kfHeightRatio));
	m_TextMultiSample.SetFontSize(static_cast<int>(kfFontSize * kfBaseRatio));
	m_TextMultiSample.SetWeightHeavy(true);
	m_TextMultiSample.SetFormat(DT_VCENTER | DT_CENTER);



	//Volume
	m_TextVolume.Initialise(_pRenderer);
	m_TextVolume.SetPositionX(static_cast<int>(785.0f * kfWidthRatio));
	m_TextVolume.SetPositionY(static_cast<int>(581.0f * kfHeightRatio));
	m_TextVolume.SetFontSize(static_cast<int>(kfFontSize * kfBaseRatio));
	m_TextVolume.SetWeightHeavy(true);
	m_TextVolume.SetFormat(DT_VCENTER | DT_CENTER);


	//Return successful
	return (true);
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Resets the cursor for the settings scene.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSettingsScene::ResetCursor()
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
* Incrments the current selection group on the menu.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSettingsScene::IncrementCurrentSection()
{
	//Check if timer is higher then delay
	if (m_fChangeValueTimer > m_fChangeValueDelay)
	{
		//Set next selection
		switch (m_eCurrentOption)
		{
		case SETTINGSOPTION_RESOLUTION:
			m_eCurrentOption = SETTINGSOPTION_MODE;
			break;


		case SETTINGSOPTION_MODE:
			m_eCurrentOption = SETTINGSOPTION_MULTISAMPLING;
			break;


		case SETTINGSOPTION_MULTISAMPLING:
			m_eCurrentOption = SETTINGSOPTION_VOLUME;
			break;


		case SETTINGSOPTION_VOLUME:
			m_eCurrentOption = SETTINGSOPTION_SAVE;
			break;


		case SETTINGSOPTION_SAVE:
			m_eCurrentOption = SETTINGSOPTION_BACK;
			break;


		case SETTINGSOPTION_BACK:
			m_eCurrentOption = SETTINGSOPTION_RESOLUTION;
			break;
		}


		//Updates sprites and text
		UpdateSectionSprites();
		UpdateSectionText();


		//Play change selection sound
		CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");


		//Reset change value timer
		m_fChangeValueTimer = 0.0f;
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Decrments the current selection group on the menu.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSettingsScene::DecrementCurrentSection()
{
	//Check if timer is higher then delay
	if (m_fChangeValueTimer > m_fChangeValueDelay)
	{
		//Set next selection
		switch (m_eCurrentOption)
		{
		case SETTINGSOPTION_RESOLUTION:
			m_eCurrentOption = SETTINGSOPTION_BACK;
			break;


		case SETTINGSOPTION_MODE:
			m_eCurrentOption = SETTINGSOPTION_RESOLUTION;
			break;


		case SETTINGSOPTION_MULTISAMPLING:
			m_eCurrentOption = SETTINGSOPTION_MODE;
			break;


		case SETTINGSOPTION_VOLUME:
			m_eCurrentOption = SETTINGSOPTION_MULTISAMPLING;
			break;


		case SETTINGSOPTION_SAVE:
			m_eCurrentOption = SETTINGSOPTION_VOLUME;
			break;


		case SETTINGSOPTION_BACK:
			m_eCurrentOption = SETTINGSOPTION_SAVE;
		}


		//Updates sprites and text
		UpdateSectionSprites();
		UpdateSectionText();


		//Play change selection sound
		CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");


		//Reset change value timer
		m_fChangeValueTimer = 0.0f;
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Increments the current value of selection.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSettingsScene::IncrementSectionValue()
{
	//Check if timer is higher then delay
	if (m_fChangeValueTimer > m_fChangeValueDelay)
	{
		//Increment option on current selection
		switch (m_eCurrentOption)
		{
		case SETTINGSOPTION_RESOLUTION:
			{
				std::map<unsigned int, char*>::iterator iterSectionData;
				iterSectionData = m_mapResolutionTypes.find(m_uiResolutionMode);
				++ iterSectionData;


				if (iterSectionData == m_mapResolutionTypes.end())
				{
					iterSectionData = m_mapResolutionTypes.begin();
				}
				m_uiResolutionMode = (*iterSectionData).first;
				break;
			}


		case SETTINGSOPTION_MODE:
			{
				std::map<bool, char*>::iterator iterSectionData;
				iterSectionData = m_mapModeTypes.find(m_bWindowMode);
				++ iterSectionData;


				if (iterSectionData == m_mapModeTypes.end())
				{
					iterSectionData = m_mapModeTypes.begin();
				}
				m_bWindowMode = (*iterSectionData).first;


				InitialiseMultiSamplingTypes(m_pRenderer, !m_bWindowMode);
				break;
			}


		case SETTINGSOPTION_MULTISAMPLING:
			{
				std::map<unsigned int, char*>::iterator iterSectionData;
				iterSectionData = m_mapMultiSampleTypes.find(m_uiMultiSampleType);
				++ iterSectionData;


				if (iterSectionData == m_mapMultiSampleTypes.end())
				{
					iterSectionData = m_mapMultiSampleTypes.begin();
				}
				m_uiMultiSampleType = (*iterSectionData).first;
				break;
			}


		case SETTINGSOPTION_VOLUME:
			{
				std::map<float, char*>::iterator iterSectionData;
				iterSectionData = m_mapVolumeTypes.find(m_fVolume);
				++ iterSectionData;


				if (iterSectionData == m_mapVolumeTypes.end())
				{
					iterSectionData = m_mapVolumeTypes.begin();
				}
				m_fVolume = (*iterSectionData).first;
			break;
			}


		case SETTINGSOPTION_SAVE:
			//Empty
			break;
		}


		//Update text
		UpdateSectionText();


		//Play change value sound
		CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");


		//Reset change value timer
		m_fChangeValueTimer = 0.0f;
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Decrements the current value of selection.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSettingsScene::DecrementSectionValue()
{
	//Check if timer is higher then delay
	if (m_fChangeValueTimer > m_fChangeValueDelay)
	{
		//Decrement option on current selection
		switch (m_eCurrentOption)
		{
		case SETTINGSOPTION_RESOLUTION:
			{
				std::map<unsigned int, char*>::iterator iterSectionData;
				iterSectionData = m_mapResolutionTypes.find(m_uiResolutionMode);


				if (iterSectionData == m_mapResolutionTypes.begin())
				{
					iterSectionData = m_mapResolutionTypes.end();
				}

				-- iterSectionData;

				m_uiResolutionMode = (*iterSectionData).first;
				break;
			}


		case SETTINGSOPTION_MODE:
			{
				std::map<bool, char*>::iterator iterSectionData;
				iterSectionData = m_mapModeTypes.find(m_bWindowMode);
				

				if (iterSectionData == m_mapModeTypes.begin())
				{
					iterSectionData = m_mapModeTypes.end();
				}

				-- iterSectionData;

				m_bWindowMode = (*iterSectionData).first;


				InitialiseMultiSamplingTypes(m_pRenderer, !m_bWindowMode);
				break;
			}


		case SETTINGSOPTION_MULTISAMPLING:
			{
				std::map<unsigned int, char*>::iterator iterSectionData;
				iterSectionData = m_mapMultiSampleTypes.find(m_uiMultiSampleType);


				if (iterSectionData == m_mapMultiSampleTypes.begin())
				{
					iterSectionData = m_mapMultiSampleTypes.end();
				}

				-- iterSectionData;

				m_uiMultiSampleType = (*iterSectionData).first;
				break;
			}


		case SETTINGSOPTION_VOLUME:
			{
				std::map<float, char*>::iterator iterSectionData;
				iterSectionData = m_mapVolumeTypes.find(m_fVolume);


				if (iterSectionData == m_mapVolumeTypes.begin())
				{
					iterSectionData = m_mapVolumeTypes.end();
				}

				-- iterSectionData;

				m_fVolume = (*iterSectionData).first;
				break;
			}


		case SETTINGSOPTION_SAVE:
			//Empty
			break;
		}


		//Update text
		UpdateSectionText();


		//Play change value sound
		CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");

		
		//Reset change value timer
		m_fChangeValueTimer = 0.0f;
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Updates the text of the settings to match each current selection groups value.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSettingsScene::UpdateSectionText()
{
	//Resolution
	std::map<unsigned int, char*>::iterator iterResolution;
	iterResolution = m_mapResolutionTypes.find(m_uiResolutionMode);
	m_TextResolution.SetText((*iterResolution).second);


	//Mode
	std::map<bool, char*>::iterator iterMode;
	iterMode = m_mapModeTypes.find(m_bWindowMode);
	m_TextMode.SetText((*iterMode).second);


	//Multisampling
	std::map<unsigned int, char*>::iterator iterMultisampling;
	iterMultisampling = m_mapMultiSampleTypes.find(m_uiMultiSampleType);
	m_TextMultiSample.SetText((*iterMultisampling).second);


	//Volume
	std::map<float, char*>::iterator iterVolume;
	iterVolume = m_mapVolumeTypes.find(m_fVolume);
	m_TextVolume.SetText((*iterVolume).second);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Updates sprites.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSettingsScene::UpdateSectionSprites()
{
	ShadeAllSections();
	HighlightCurrentSection();
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Shades all selection group's sprites.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSettingsScene::ShadeAllSections()
{
	//Resolution
	m_TextResolution.SetColour(s_iTextShadeColour);
	m_pRenderer->GetSpriteManager().SetModulate(s_iSpriteShadeColour, m_uiResolutionArrowLeft);
	m_pRenderer->GetSpriteManager().SetModulate(s_iSpriteShadeColour, m_uiResolutionArrowRight);


	//Mode
	m_TextMode.SetColour(s_iTextShadeColour);
	m_pRenderer->GetSpriteManager().SetModulate(s_iSpriteShadeColour, m_uiModeArrowLeft);
	m_pRenderer->GetSpriteManager().SetModulate(s_iSpriteShadeColour, m_uiModeArrowRight);


	//Multisampling
	m_TextMultiSample.SetColour(s_iTextShadeColour);
	m_pRenderer->GetSpriteManager().SetModulate(s_iSpriteShadeColour, m_uiMultisamplingArrowLeft);
	m_pRenderer->GetSpriteManager().SetModulate(s_iSpriteShadeColour, m_uiMultisamplingArrowRight);


	//Volume
	m_TextVolume.SetColour(s_iTextShadeColour);
	m_pRenderer->GetSpriteManager().SetModulate(s_iSpriteShadeColour, m_uiVolumeArrowLeft);
	m_pRenderer->GetSpriteManager().SetModulate(s_iSpriteShadeColour, m_uiVolumeArrowRight);


	//Save
	m_pRenderer->GetSpriteManager().SetModulate(s_iSpriteShadeColour, m_uiSaveTitle);
	m_pRenderer->GetSpriteManager().SetModulate(s_iSpriteShadeColour, m_uiBackTitle);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Heights the current selection that the user is on.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSettingsScene::HighlightCurrentSection()
{
	//Highlight the current selection
	switch (m_eCurrentOption)
	{
	case SETTINGSOPTION_RESOLUTION:
		m_TextResolution.SetColour(s_iTextHoverColour);
		m_pRenderer->GetSpriteManager().SetModulate(s_iSpriteHoverColour, m_uiResolutionArrowLeft);
		m_pRenderer->GetSpriteManager().SetModulate(s_iSpriteHoverColour, m_uiResolutionArrowRight);
		break;


	case SETTINGSOPTION_MODE:
		m_TextMode.SetColour(s_iTextHoverColour);
		m_pRenderer->GetSpriteManager().SetModulate(s_iSpriteHoverColour, m_uiModeArrowLeft);
		m_pRenderer->GetSpriteManager().SetModulate(s_iSpriteHoverColour, m_uiModeArrowRight);
		break;


	case SETTINGSOPTION_MULTISAMPLING:
		m_TextMultiSample.SetColour(s_iTextHoverColour);
		m_pRenderer->GetSpriteManager().SetModulate(s_iSpriteHoverColour, m_uiMultisamplingArrowLeft);
		m_pRenderer->GetSpriteManager().SetModulate(s_iSpriteHoverColour, m_uiMultisamplingArrowRight);
		break;


	case SETTINGSOPTION_VOLUME:
		m_TextVolume.SetColour(s_iTextHoverColour);
		m_pRenderer->GetSpriteManager().SetModulate(s_iSpriteHoverColour, m_uiVolumeArrowLeft);
		m_pRenderer->GetSpriteManager().SetModulate(s_iSpriteHoverColour, m_uiVolumeArrowRight);
		break;


	case SETTINGSOPTION_SAVE:
		m_pRenderer->GetSpriteManager().SetModulate(s_iSpriteHoverColour, m_uiSaveTitle);
		break;


	case SETTINGSOPTION_BACK:
		m_pRenderer->GetSpriteManager().SetModulate(s_iSpriteHoverColour, m_uiBackTitle);
		break;
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the settings for the window and renderer for the settings that the user has chosen.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSettingsScene::ExecuteSaveSettings()
{
	//Get varaibles
	const unsigned int kuiNewWidth  = m_vecDisplayModes[m_uiResolutionMode].Width;
	const unsigned int kuiNewHeight = m_vecDisplayModes[m_uiResolutionMode].Height;
	const unsigned int kuiRefreshRate = m_vecDisplayModes[m_uiResolutionMode].RefreshRate;


	//Set resolution and window mode
	CWindow& rWindow = CApplication::GetInstance().GetGameWindow();
	rWindow.ResizeWindow(kuiNewWidth, kuiNewHeight, kuiRefreshRate, !m_bWindowMode);


	//Set multisampling
	m_pRenderer->SetMultisampleType(static_cast<D3DMULTISAMPLE_TYPE>(m_uiMultiSampleType), !m_bWindowMode);


	//Force device to reset to apply new settings
	m_pRenderer->GetDeviceManager().ScheduleDeviceReset();

	
	//Change volume of sound system
	CSoundSystem::GetInstance()->GlobalVolume(m_fVolume);


	//Change back to previous scene
	ReturnToBeforeScene(kuiNewWidth, kuiNewHeight);


	//Play save settings sound
	CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Select.wav");
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the scene that is set within the given settings scene data.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSettingsScene::ReturnToBeforeScene(unsigned int _uiScreenWidth, unsigned int _uiScreenHeight)
{
	if (m_pSettingsSceneData->GetSceneTypeMainScene() == true)
	{
		CApplication::GetInstance().GetGameWindow().GetCurrentMainScene().RecoverFromOverlayScene();
		CApplication::GetInstance().GetGameWindow().SetOverlayScene(OVERLAYSCENE_DELETE);
	}
	else
	{
		CWindow& rWindow = CApplication::GetInstance().GetGameWindow();
		rWindow.SetOverlayScene(static_cast<EOverlayScene>(m_pSettingsSceneData->GetSceneTypeId()));

		if (_uiScreenWidth && _uiScreenHeight)
		{
			// Adjust HUD and Radial Menu scaling.
			CGameScene& rGameScene = *dynamic_cast<CGameScene*>(&rWindow.GetCurrentMainScene());
			rGameScene.GetHud()->OnResolutionChange(_uiScreenWidth, _uiScreenHeight);
			rGameScene.GetRadialMenu()->OnResolutionChange(min(_uiScreenWidth, _uiScreenHeight - static_cast<unsigned int>(rGameScene.GetHud()->GetUsedScreenHeight())),
															_uiScreenWidth * 0.5f,
															(_uiScreenHeight - rGameScene.GetHud()->GetUsedScreenHeight()) * 0.5f);
		}
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* 
*
* @author Daniel Lansford
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSettingsScene::SpriteSelection()
{
	RECT SpriteBounds;
	CVector3 vecPos;
	int iWidth = 0;
	int iHeight = 0;
	
	m_bSpriteSelected = false;

	HWND hWnd = CApplication::GetInstance().GetGameWindow().GetWindowHandle();

	const unsigned int kuiWindowWidth = CApplication::GetInstance().GetGameWindow().GetWindowWidth();
	const unsigned int kuiWindowHeight =  CApplication::GetInstance().GetGameWindow().GetWindowHeight();

	COORD MouseCords;
	MouseCords = CApplication::GetInstance().GetGameWindow().GetMosueCoords();
	CD3DRenderer* pRenderer = CApplication::GetInstance().GetGameWindow().GetRenderer();

	//Increment Resolution
	SpriteBounds = m_pRenderer->GetSpriteManager().GetRect(m_uiResolutionArrowRight);

	vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiResolutionArrowRight);

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
		if(m_bMouseClick == true)
		{
			m_eCurrentOption = SETTINGSOPTION_RESOLUTION;
			IncrementSectionValue();
			m_bSpriteSelected = true;

			//Updates sprites and text
			UpdateSectionSprites();
			UpdateSectionText();			
		}
	}

	//Decrement Resolution
	vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiResolutionArrowLeft);

	SpriteBounds.left   =	static_cast<LONG>(vecPos.x - (iWidth / 2));
	SpriteBounds.right  =	static_cast<LONG>(vecPos.x + (iWidth / 2));
	SpriteBounds.top    =	static_cast<LONG>(vecPos.y - (iHeight / 2));
	SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + (iHeight / 2));
		
	if(MouseCords.X >= SpriteBounds.left  &&
	   MouseCords.X <= SpriteBounds.right &&
	   MouseCords.Y >= SpriteBounds.top   &&
	   MouseCords.Y <= SpriteBounds.bottom)
	{
		if(m_bMouseClick == true)
		{
			m_eCurrentOption = SETTINGSOPTION_RESOLUTION;
			DecrementSectionValue();
			m_bSpriteSelected = true;

			//Updates sprites and text
			UpdateSectionSprites();
			UpdateSectionText();			
		}
	}

	//Increment Mode
	vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiModeArrowRight);

	SpriteBounds.left   =	static_cast<LONG>(vecPos.x - (iWidth / 2));
	SpriteBounds.right  =	static_cast<LONG>(vecPos.x + (iWidth / 2));
	SpriteBounds.top    =	static_cast<LONG>(vecPos.y - (iHeight / 2));
	SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + (iHeight / 2));
		
	if(MouseCords.X >= SpriteBounds.left  &&
	   MouseCords.X <= SpriteBounds.right &&
	   MouseCords.Y >= SpriteBounds.top   &&
	   MouseCords.Y <= SpriteBounds.bottom)
	{
		if(m_bMouseClick == true)
		{
			m_eCurrentOption = SETTINGSOPTION_MODE;
			IncrementSectionValue();
			m_bSpriteSelected = true;

			//Updates sprites and text
			UpdateSectionSprites();
			UpdateSectionText();			
		}
	}

	//Decrement Mode
	vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiModeArrowLeft);

	SpriteBounds.left   =	static_cast<LONG>(vecPos.x - (iWidth / 2));
	SpriteBounds.right  =	static_cast<LONG>(vecPos.x + (iWidth / 2));
	SpriteBounds.top    =	static_cast<LONG>(vecPos.y - (iHeight / 2));
	SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + (iHeight / 2));
		
	if(MouseCords.X >= SpriteBounds.left  &&
	   MouseCords.X <= SpriteBounds.right &&
	   MouseCords.Y >= SpriteBounds.top   &&
	   MouseCords.Y <= SpriteBounds.bottom)
	{
		if(m_bMouseClick == true)
		{
			m_eCurrentOption = SETTINGSOPTION_MODE;
			DecrementSectionValue();
			m_bSpriteSelected = true;

			//Updates sprites and text
			UpdateSectionSprites();
			UpdateSectionText();			
		}
	}

	//Increment MultiSampling
	vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiMultisamplingArrowRight);

	SpriteBounds.left   =	static_cast<LONG>(vecPos.x - (iWidth / 2));
	SpriteBounds.right  =	static_cast<LONG>(vecPos.x + (iWidth / 2));
	SpriteBounds.top    =	static_cast<LONG>(vecPos.y - (iHeight / 2));
	SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + (iHeight / 2));
		
	if(MouseCords.X >= SpriteBounds.left  &&
	   MouseCords.X <= SpriteBounds.right &&
	   MouseCords.Y >= SpriteBounds.top   &&
	   MouseCords.Y <= SpriteBounds.bottom)
	{
		if(m_bMouseClick == true)
		{
			m_eCurrentOption = SETTINGSOPTION_MULTISAMPLING;
			IncrementSectionValue();
			m_bSpriteSelected = true;

			//Updates sprites and text
			UpdateSectionSprites();
			UpdateSectionText();			
		}
	}

	//Decrement MultiSampling
	vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiMultisamplingArrowLeft);

	SpriteBounds.left   =	static_cast<LONG>(vecPos.x - (iWidth / 2));
	SpriteBounds.right  =	static_cast<LONG>(vecPos.x + (iWidth / 2));
	SpriteBounds.top    =	static_cast<LONG>(vecPos.y - (iHeight / 2));
	SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + (iHeight / 2));
		
	if(MouseCords.X >= SpriteBounds.left  &&
	   MouseCords.X <= SpriteBounds.right &&
	   MouseCords.Y >= SpriteBounds.top   &&
	   MouseCords.Y <= SpriteBounds.bottom)
	{
		if(m_bMouseClick == true)
		{
			m_eCurrentOption = SETTINGSOPTION_MULTISAMPLING;
			DecrementSectionValue();
			m_bSpriteSelected = true;

			//Updates sprites and text
			UpdateSectionSprites();
			UpdateSectionText();			
		}
	}

	//Increment Volume
	vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiVolumeArrowRight);

	SpriteBounds.left   =	static_cast<LONG>(vecPos.x - (iWidth / 2));
	SpriteBounds.right  =	static_cast<LONG>(vecPos.x + (iWidth / 2));
	SpriteBounds.top    =	static_cast<LONG>(vecPos.y - (iHeight / 2));
	SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + (iHeight / 2));
		
	if(MouseCords.X >= SpriteBounds.left  &&
	   MouseCords.X <= SpriteBounds.right &&
	   MouseCords.Y >= SpriteBounds.top   &&
	   MouseCords.Y <= SpriteBounds.bottom)
	{
		if(m_bMouseClick == true)
		{
			m_eCurrentOption = SETTINGSOPTION_VOLUME;
			IncrementSectionValue();
			m_bSpriteSelected = true;

			//Updates sprites and text
			UpdateSectionSprites();
			UpdateSectionText();			
		}
	}

	//Decrement Volume
	vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiVolumeArrowLeft);

	SpriteBounds.left   =	static_cast<LONG>(vecPos.x - (iWidth / 2));
	SpriteBounds.right  =	static_cast<LONG>(vecPos.x + (iWidth / 2));
	SpriteBounds.top    =	static_cast<LONG>(vecPos.y - (iHeight / 2));
	SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + (iHeight / 2));
		
	if(MouseCords.X >= SpriteBounds.left  &&
	   MouseCords.X <= SpriteBounds.right &&
	   MouseCords.Y >= SpriteBounds.top   &&
	   MouseCords.Y <= SpriteBounds.bottom)
	{
		if(m_bMouseClick == true)
		{
			m_eCurrentOption = SETTINGSOPTION_VOLUME;
			DecrementSectionValue();
			m_bSpriteSelected = true;

			//Updates sprites and text
			UpdateSectionSprites();
			UpdateSectionText();			
		}
	}


	//Selection of save
	SpriteBounds = m_pRenderer->GetSpriteManager().GetRect(m_uiSaveTitle);
	vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiSaveTitle);

	iWidth =  SpriteBounds.right - SpriteBounds.left;
	iHeight =  SpriteBounds.bottom - SpriteBounds.top;

	SpriteBounds.left   =	static_cast<LONG>(vecPos.x - iWidth / 2);
	SpriteBounds.right  =	static_cast<LONG>(vecPos.x + iWidth / 2);
	SpriteBounds.top    =	static_cast<LONG>(vecPos.y - iHeight / 2);
	SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + iHeight / 2);
		
	if(MouseCords.X >= SpriteBounds.left  &&
	   MouseCords.X <= SpriteBounds.right &&
	   MouseCords.Y >= SpriteBounds.top   &&
	   MouseCords.Y <= SpriteBounds.bottom)
	{
		if(m_eCurrentOption != SETTINGSOPTION_SAVE)
		{
			m_eCurrentOption = SETTINGSOPTION_SAVE;

			//Updates sprites and text
			UpdateSectionSprites();
			UpdateSectionText();


			//Play change selection sound
			CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");


			//Reset change value timer
			m_fChangeValueTimer = 0.0f;
		}
		else
		{
			if(m_bMouseClick == true)
			{
				if (m_eCurrentOption == SETTINGSOPTION_SAVE)
				{
					ExecuteSaveSettings();
				}
				else if (m_eCurrentOption == SETTINGSOPTION_BACK)
				{
					ReturnToBeforeScene();
				}
			}
		}
	}

	//Selection of Back
	SpriteBounds = m_pRenderer->GetSpriteManager().GetRect(m_uiBackTitle);
	vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiBackTitle);

	iWidth =  SpriteBounds.right - SpriteBounds.left;
	iHeight =  SpriteBounds.bottom - SpriteBounds.top;

	SpriteBounds.left   =	static_cast<LONG>(vecPos.x - iWidth / 2);
	SpriteBounds.right  =	static_cast<LONG>(vecPos.x + iWidth / 2);
	SpriteBounds.top    =	static_cast<LONG>(vecPos.y - iHeight / 2);
	SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + iHeight / 2);
		
	if(MouseCords.X >= SpriteBounds.left  &&
	   MouseCords.X <= SpriteBounds.right &&
	   MouseCords.Y >= SpriteBounds.top   &&
	   MouseCords.Y <= SpriteBounds.bottom)
	{
		if(m_eCurrentOption != SETTINGSOPTION_BACK)
		{
			m_eCurrentOption = SETTINGSOPTION_BACK;

			//Updates sprites and text
			UpdateSectionSprites();
			UpdateSectionText();

			//Play change selection sound
			CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");

			//Reset change value timer
			m_fChangeValueTimer = 0.0f;
		}
		else
		{
			if(m_bMouseClick == true)
			{
				ReturnToBeforeScene();
				m_bMouseClick = false;
			}
		}
	}

	
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* 
*
* @author Daniel Lansford
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSettingsScene::TextSelection()
{
	HWND hWnd = CApplication::GetInstance().GetGameWindow().GetWindowHandle();

	const unsigned int kuiWindowWidth = CApplication::GetInstance().GetGameWindow().GetWindowWidth();
	const unsigned int kuiWindowHeight =  CApplication::GetInstance().GetGameWindow().GetWindowHeight();

	COORD MouseCords;
	MouseCords = CApplication::GetInstance().GetGameWindow().GetMosueCoords();
	CD3DRenderer* pRenderer = CApplication::GetInstance().GetGameWindow().GetRenderer();
	
	////Selection of Resolution
	RECT TextBounds = m_TextResolution.GetRect();
			
	if(MouseCords.X >= TextBounds.left &&
	   MouseCords.X <= TextBounds.right &&
	   MouseCords.Y >= TextBounds.top &&
	   MouseCords.Y <= TextBounds.bottom)
	{
		if(m_bMouseClick == true)
		{
			m_eCurrentOption = SETTINGSOPTION_RESOLUTION;
			//Updates sprites and text
			UpdateSectionSprites();
			UpdateSectionText();

			//Play change selection sound
			CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");

			//Reset change value timer
			m_fChangeValueTimer = 0.0f;
		}
	}

	//Selection of Windowed / Full screen mode
	TextBounds = m_TextMode.GetRect();
		
	if(MouseCords.X >= TextBounds.left &&
	   MouseCords.X <= TextBounds.right &&
	   MouseCords.Y >= TextBounds.top &&
	   MouseCords.Y <= TextBounds.bottom)
	{
		if(m_bMouseClick == true)
		{
			m_eCurrentOption = SETTINGSOPTION_MODE;
			//Updates sprites and text
			UpdateSectionSprites();
			UpdateSectionText();

			//Play change selection sound
			CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");

			//Reset change value timer
			m_fChangeValueTimer = 0.0f;
		}
	}

	//Selection of multisampling
	TextBounds = m_TextMultiSample.GetRect();
		
	if(MouseCords.X >= TextBounds.left &&
	   MouseCords.X <= TextBounds.right &&
	   MouseCords.Y >= TextBounds.top &&
	   MouseCords.Y <= TextBounds.bottom)
	{
		if(m_bMouseClick == true)
		{
			m_eCurrentOption = SETTINGSOPTION_MULTISAMPLING;
			//Updates sprites and text
			UpdateSectionSprites();
			UpdateSectionText();

			//Play change selection sound
			CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");

			//Reset change value timer
			m_fChangeValueTimer = 0.0f;
		}
	}

	//Selection of volume controls
	TextBounds = m_TextVolume.GetRect();
		
	if(MouseCords.X >= TextBounds.left &&
	   MouseCords.X <= TextBounds.right &&
	   MouseCords.Y >= TextBounds.top &&
	   MouseCords.Y <= TextBounds.bottom)
	{
		if(m_bMouseClick == true)
		{
			m_eCurrentOption = SETTINGSOPTION_VOLUME;
			//Updates sprites and text
			UpdateSectionSprites();
			UpdateSectionText();

			//Play change selection sound
			CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");

			//Reset change value timer
			m_fChangeValueTimer = 0.0f;
		}
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* This function deinitialises the class instance by freeing memory and calling other necessary functions.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSettingsScene::Deinitialise()
{
	//Clean maps
	FW_DELETEMAP(unsigned int, char*, m_mapResolutionTypes);
	FW_DELETEMAP(unsigned int, char*, m_mapMultiSampleTypes);
	FW_DELETE(m_pSettingsSceneData);


	//Remove sprites
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiSettingsBackground);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiSettingsLogo);

	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiResolutionTitle);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiResolutionArrowLeft);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiResolutionArrowRight);

	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiModeTitle);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiModeArrowLeft);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiModeArrowRight);

	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiMultisamplingTitle);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiMultisamplingArrowLeft);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiMultisamplingArrowRight);

	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiVolumeTitle);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiVolumeArrowLeft);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiVolumeArrowRight);

	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiSaveTitle);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiBackTitle);

	m_pRenderer->GetLightManager().RemoveLight(m_uiLightDirectional);
}