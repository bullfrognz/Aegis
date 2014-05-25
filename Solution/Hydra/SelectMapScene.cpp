//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   SelectMapScene.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Macros.h"
#include "StrUtilities.h"
#include "Application.h"
#include "GameWindow.h"
#include "Window.h"
#include "D3DRenderer.h"
#include "MeshManager.h"
#include "GameCamera.h"
#include "SpriteManager.h"
#include "INIParser.h"
#include "SoundSystem.h"
#include "StaticObject.h"
#include "InputManager.h"
#include "GameSceneData.h"
#include "LogWindow.h"
#include "LightManager.h"
#include "Text.h"
#include "VertexBufferManager.h"
#include "Vertex1TexSCSP.h"
#include "Utility.h"
#include "DirectInput.h"
#include "XInputController.h"
#include "Defines.h"


// This Include
#include "SelectMapScene.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* SelectMapScene class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CSelectMapScene::CSelectMapScene()
: m_pTextMapPlayerGold(0)
, m_pTextMapPlayerLives(0)
, m_pINIMapFile(0)
, m_eScenePhase(SELMAPPHASE_SELECTMAP)
, m_eSelectedDifficulty(DIFFICULTY_INVALID)
, m_uiSelectedMap(0)
, m_uiPlayerStartGold(0)
, m_uiPlayerStartLives(0)
, m_uiLightDirectional(0)
, m_uiCurrentMapId(0)
, m_uiMapsReadFromId(0)
, m_uiMapSelectorPosition(0)
, m_uiVertexQuadID(Utility::INVALID_ID)
, m_uiSpriteBackground(0)
, m_uiSpriteMapContainer(0)
, m_uiSpriteMapPreviewer(0)
, m_uiSpriteSelectorBar(0)
, m_uiSpriteEasy(0)
, m_uiSpriteMedium(0)
, m_uiSpriteHard(0)
, m_fMapSwitchDelay(0)
, m_fMapSwitchTimer(0)
, m_fDifficultySwitchDelay(0)
, m_fDifficultySwitchTimer(0)
, m_bDoubleClick(false)
, m_bMouseClick(false)
, m_bNoMaps(false)
, m_bControllerActive(false)
, m_bIncrementMap(false)
, m_bDecrementMap(false)
, m_bIncrementDifficulty(false)
, m_bDecrementDifficulty(false)
{
	FW_FILLARRAY(m_pTextMapTitles, s_eMaxMapsToDisplay, 0);
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* SelectMapScene class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CSelectMapScene::~CSelectMapScene()
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
CSelectMapScene::InitialiseScene(CD3DRenderer* _pRenderer, void* _pSceneData)
{
	//Set member variables
	m_fMapSwitchDelay = 0.2f;
	m_fDifficultySwitchDelay = 0.2f;
	m_eScenePhase = SELMAPPHASE_SELECTMAP;
	m_pINIMapFile = new CINIParser();


	InitialisePlayerInputTarget();
	InitialiseXInputTarget();
	InitialiseMapText();
	InitialiseSprites();
	InitialiseMapPreviewer();


	ScanMapFiles();


	UpdateMapTitles();
	ReadSelectedMap();
	UpdatePlayerText();
	UpdateScrollArrows();
	UpdateMapPreviewer();
	UpdateDifficultyButtons();
	UpdateMapSelector();


	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Processes the scene.
*
* @author Bryce Booth
* @param _fDeltaTick	Time since last frame.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSelectMapScene::ProcessScene(float _fDeltaTick)
{
	//Increment timers
	m_fMapSwitchTimer += _fDeltaTick;
	m_fDifficultySwitchTimer += _fDeltaTick;


	if(m_pInputManager->GetXInputController().IsPluggedIn() == false)
	{
		if(m_eScenePhase == SELMAPPHASE_SELECTMAP && m_bNoMaps == false)
		{
			MouseSelect();	
		}
		else if(m_eScenePhase == SELMAPPHASE_SELDIFFICULTY && m_bNoMaps == false)
		{
			MouseSelectDifficulty();
		}
	}


	//Check scene phase is select map
	if (m_eScenePhase == SELMAPPHASE_SELECTMAP)
	{
		if (m_bIncrementMap == true)
		{
			IncrementMapSelection();
		}
		else if (m_bDecrementMap == true)
		{
			 DecrementMapSelection();
		}
	}
	//Check scene phase is select difficulty
	else if (m_eScenePhase == SELMAPPHASE_SELDIFFICULTY)
	{
		if (m_bIncrementDifficulty == true)
		{
			IncrementDifficultySelection();
		}
		else if (m_bDecrementDifficulty == true)
		{
			DecrementDifficultySelection();
		}
	}


	ResetCursor();
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Draws scenes text and models.
*
* @author Bryce Booth
* @param _pRenderer		Renderer of parent window.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSelectMapScene::DrawScene(CD3DRenderer* _pRenderer)
{
	//Turn on scene lights
	_pRenderer->GetLightManager().TurnOnLight(m_uiLightDirectional);

	
	//Tell sprite manager to draw.
	_pRenderer->GetSpriteManager().Draw();


	//Draw map previewer
	if (m_uiVertexQuadID != Utility::INVALID_ID)
	{
		CVertexBuffer* pBuffer = m_pRenderer->GetVertexBufferManager().GetVertexBuffer(m_uiVertexQuadID);
		assert(pBuffer);


		m_pRenderer->GetTextureManager().SetTexture(m_uiPreviewTextureId);
		pBuffer->Render(m_pRenderer->GetDeviceManager());
	}


	//Draw map text
	for (unsigned int i = 0; i < s_eMaxMapsToDisplay && i < m_vecMaps.size(); ++ i)
	{
		m_pTextMapTitles[i]->Draw(_pRenderer);
	}


	//Draw player map information text.
	m_pTextMapPlayerGold->Draw(_pRenderer);
	m_pTextMapPlayerLives->Draw(_pRenderer);


	#if _DEBUG

		DrawDebugInfo();

	#endif
}








/********************************
            Protected
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates lights for the scene.
*
* @author Bryce Booth
* @param _pRenderer		Renderer of parent window.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CSelectMapScene::InitialiseLights(CD3DRenderer* _pRenderer)
{
	m_uiLightDirectional = _pRenderer->GetLightManager().AddLight();
	_pRenderer->GetLightManager().UpdateParam(m_uiLightDirectional, DIRECTION, &D3DXVECTOR3(0.6f, -1.0f, 1.0f));


	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates and initialises viewport and camera for scene.
*
* @author Bryce Booth
* @param _pRenderer		Renderer of parent window.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CSelectMapScene::InitialiseViewports(CD3DRenderer* _pRenderer)
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
CSelectMapScene::HandleDMouseInput(EDInputMouse _eDMouse, bool _bDown, long _lValue)
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
				if(_lValue >= 120)
				{
					ScrollUp();
				}
				else if(_lValue <= -120)
				{
					ScrollDown();
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
CSelectMapScene::HandleDKeyboardInput(EDInputKeyboard _eDKebyoard, bool _bDown)
{
	if (_bDown)
	{
		switch (_eDKebyoard)
		{
		case DKEYBOARD_LEFTARROW:	//Fall through
		case DKEYBOARD_A:
			{
				m_bDecrementDifficulty = true;
			}
			break;

		case DKEYBOARD_RIGHTARROW:	//Fall through
		case DKEYBOARD_D:
			{
				m_bIncrementDifficulty = true;
			}
			break;

		case DKEYBOARD_W: //Fall through
		case DKEYBOARD_UPARROW:
			{
				m_bDecrementMap = true;
			}
			break;

		case DKEYBOARD_S: //Fall through
		case DKEYBOARD_DOWNARROW:
			{
				m_bIncrementMap = true;
			}
			break;

		case DKEYBOARD_ENTER: //Fall through
		case DKEYBOARD_SPACE:
			{
				if (m_eScenePhase == SELMAPPHASE_SELECTMAP)
				{
					SelectMap();
				}
				else if (m_eScenePhase == SELMAPPHASE_SELDIFFICULTY)
				{
					SelectDifficulty();
				}
			}
			break;

		case DKEYBOARD_ESCAPE: //Fall through
		case DKEYBOARD_BACK:
			{
				if (m_eScenePhase == SELMAPPHASE_SELECTMAP)
				{
					BackToMainMenu();
				}
				else if (m_eScenePhase == SELMAPPHASE_SELDIFFICULTY)
				{
					BackToSelectMap();
				}
			}
			break;
		}
	}
	else
	{
		switch (_eDKebyoard)
		{
		case DKEYBOARD_LEFTARROW:	//Fall through
		case DKEYBOARD_A:
			{
				m_bDecrementDifficulty = false;
			}
			break;

		case DKEYBOARD_RIGHTARROW:	//Fall through
		case DKEYBOARD_D:
			{
				m_bIncrementDifficulty = false;
			}
			break;

		case DKEYBOARD_W: //Fall through
		case DKEYBOARD_UPARROW:
			{
				m_bDecrementMap = false;
			}
			break;

		case DKEYBOARD_S: //Fall through
		case DKEYBOARD_DOWNARROW:
			{
				m_bIncrementMap = false;
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
CSelectMapScene::HandleXButtonInput(EXInputButton _eXButton, bool _bDown)
{
	if (_bDown)
	{
		switch (_eXButton)
		{
		case XBUTTON_A:
		{
			if (_bDown)
			{
				if (m_eScenePhase == SELMAPPHASE_SELECTMAP)
				{
					SelectMap();
				}
				else if (m_eScenePhase == SELMAPPHASE_SELDIFFICULTY)
				{
					SelectDifficulty();
				}
			}
			break;
		}


		case XBUTTON_B:
			{
				if (_bDown)
				{
					if (m_eScenePhase == SELMAPPHASE_SELECTMAP)
					{
						BackToMainMenu();
					}
					else if (m_eScenePhase == SELMAPPHASE_SELDIFFICULTY)
					{
						BackToSelectMap();
					}
				}
				break;
			}
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
CSelectMapScene::HandleXAnalogInput(EXInputAnalog _eXAnalog, float _fValue)
{
	switch (_eXAnalog)
	{
		case XANALOG_LEFTX:
		{
			if (_fValue >= 0.8f)
			{
				m_bIncrementDifficulty = true;
			}
			else if (_fValue <= -0.8f)
			{
				m_bDecrementDifficulty = true;
			}
			else
			{
				m_bIncrementDifficulty = false;
				m_bDecrementDifficulty = false;
			}
		}
		break;


		case XANALOG_LEFTY:
		{
			if (_fValue >= 0.8f)
			{
				m_bDecrementMap = true;
			}
			else if (_fValue <= -0.8f)
			{
				m_bIncrementMap = true;
			}
			else
			{
				m_bIncrementMap = false;
				m_bDecrementMap = false;
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
CSelectMapScene::InitialisePlayerInputTarget()
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
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_RIGHTARROW, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_LEFTARROW, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_ENTER, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_BACK, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_SPACE, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_ESCAPE, this);


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
CSelectMapScene::InitialiseXInputTarget()
{
	//Input controller
	m_pInputManager->GetXInputController().AddTarget(XBUTTON_BACK, this);
	m_pInputManager->GetXInputController().AddTarget(XBUTTON_A, this);
	m_pInputManager->GetXInputController().AddTarget(XBUTTON_B, this);
	m_pInputManager->GetXInputController().AddTarget(XANALOG_LEFTX, this);
	m_pInputManager->GetXInputController().AddTarget(XANALOG_LEFTY, this);


	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Instances and sets up the text for the maps.
*
* @author Bryce Booth
* @return true	The text were created and setup successfulluy.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CSelectMapScene::InitialiseMapText()
{
	//Get window width and height
	const float kfWindowWidth  = static_cast<float>(CApplication::GetInstance().GetGameWindow().GetClientWidth());
	const float kfWindowHeight = static_cast<float>(CApplication::GetInstance().GetGameWindow().GetClientHeight());


	//Caluclate current resolution ratios
	const float kfWidthRatio  = kfWindowWidth / 1280.0f;
	const float kfHeightRatio = kfWindowHeight / 1024.0f;


	//Get application base ratio
	const float kfBaseRatio = CApplication::GetInstance().GetBaseDimentionRatio();


	//Calculate font size
	const float kfFontSize = static_cast<float>(s_eMapTextFontSize) * kfBaseRatio;


	//Loop through number of maps to display
	for (unsigned int i = 0; i < s_eMaxMapsToDisplay; ++ i)
	{
		//Instand and initialise text
		m_pTextMapTitles[i] = new CText();
		m_pTextMapTitles[i]->Initialise(m_pRenderer);
		m_pTextMapTitles[i]->SetText("Warming Up");
		m_pTextMapTitles[i]->SetFontSize(static_cast<int>(kfFontSize));
		m_pTextMapTitles[i]->SetWeightHeavy(true);
	}


	//Instance and initialise player gold text
	m_pTextMapPlayerGold = new CText();
	m_pTextMapPlayerGold->Initialise(m_pRenderer);
	m_pTextMapPlayerGold->SetPosition(static_cast<int>(945.0f * kfWidthRatio), static_cast<int>(520.0f * kfHeightRatio));
	m_pTextMapPlayerGold->SetWeightHeavy(true);
	m_pTextMapPlayerGold->SetFontSize(static_cast<int>(kfFontSize));
	m_pTextMapPlayerGold->SetColour(s_ePlayerTextColour);


	//Instance and initialise player lives text
	m_pTextMapPlayerLives = new CText();
	m_pTextMapPlayerLives->Initialise(m_pRenderer);
	m_pTextMapPlayerLives->SetPosition(static_cast<int>(945.0f * kfWidthRatio), static_cast<int>(614.0f * kfHeightRatio));
	m_pTextMapPlayerLives->SetWeightHeavy(true);
	m_pTextMapPlayerLives->SetFontSize(static_cast<int>(kfFontSize));
	m_pTextMapPlayerLives->SetColour(s_ePlayerTextColour);


	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates the sprites and sets the sprites positions for the select map scene.
*
* @author Bryce Booth
* @return True	States that the scan was successful.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CSelectMapScene::InitialiseSprites()
{
	m_uiSpriteBackground = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SelectMap_Background.png");
	m_uiSpriteMapContainer = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SelectMap_MapContainer.png");
	m_uiSpriteMapPreviewer = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SelectMap_MapPreviewer.png");
	m_uiSpriteSelectorBar = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/SelectMap_SelectorBar.png");
	m_uiSpriteEasy = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/Selectmap_Easy.png");
	m_uiSpriteMedium = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/Selectmap_Medium.png");
	m_uiSpriteHard = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/Selectmap_Hard.png");

	m_uiSpriteArrowUp = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/MapSelect_ArrowUp.png");
	m_pRenderer->GetSpriteManager().SetPosition(CVector3(685.0f, 260.0f, 0.0f), m_uiSpriteArrowUp);

	m_uiSpriteArrowDown = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/MapSelect_ArrowDown.png");
	m_pRenderer->GetSpriteManager().SetPosition(CVector3(685.0f, 620.0f, 0.0f), m_uiSpriteArrowDown);

	m_pRenderer->GetSpriteManager().SetPosition(CVector3(1280.0f / 2.0f, 1024.0f / 2.0f, 0.0f), m_uiSpriteBackground);
	m_pRenderer->GetSpriteManager().SetPosition(CVector3(460.0f, 440.0f, 0.0f), m_uiSpriteMapContainer);
	m_pRenderer->GetSpriteManager().SetPosition(CVector3(945.0f, 348.0f, 0.0f), m_uiSpriteMapPreviewer);


	m_pRenderer->GetSpriteManager().SetPosition(CVector3(340.0f, 800.0f, 0.0f), m_uiSpriteEasy);
	m_pRenderer->GetSpriteManager().SetPosition(CVector3(640.0f, 800.0f, 0.0f), m_uiSpriteMedium);
	m_pRenderer->GetSpriteManager().SetPosition(CVector3(940.0f, 800.0f, 0.0f), m_uiSpriteHard);


	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Instances the map previwer object and updates the objects position.
*
* @author Bryce Booth
* @return True	States that the object was created successfully.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CSelectMapScene::InitialiseMapPreviewer()
{
	//Get window width and height
	const float kfWindowWidth  = static_cast<float>(CApplication::GetInstance().GetGameWindow().GetClientWidth());
	const float kfWindowHeight = static_cast<float>(CApplication::GetInstance().GetGameWindow().GetClientHeight());


	//Caluclate current resolution ratios
	const float kfWidthRatio  = kfWindowWidth / 1280.0f;
	const float kfHeightRatio = kfWindowHeight / 1024.0f;


	CVertex1TexSCSP* pVertices = new CVertex1TexSCSP[4];
	if (pVertices)
	{
		pVertices[0].SetTextureCoordinates(0.0f, 0.0f);
		pVertices[1].SetTextureCoordinates(1.0f, 0.0f);
		pVertices[2].SetTextureCoordinates(0.0f, 1.0f);
		pVertices[3].SetTextureCoordinates(1.0f, 1.0f);


		pVertices[0].SetPos( 820.0f * kfWidthRatio, 245.0f * kfHeightRatio);
		pVertices[1].SetPos(1075.0f * kfWidthRatio, 245.0f * kfHeightRatio);
		pVertices[2].SetPos( 820.0f * kfWidthRatio, 450.0f * kfHeightRatio);
		pVertices[3].SetPos(1075.0f * kfWidthRatio, 450.0f * kfHeightRatio);

		m_uiVertexQuadID = m_pRenderer->GetVertexBufferManager().CreateVertexBuffer(pVertices->GetFVF(),
																					D3DPT_TRIANGLESTRIP, 4, 0,
																					pVertices->GetSizeOf(), pVertices,
																					0, D3DFMT_UNKNOWN,
																					m_pRenderer->GetDeviceManager().GetDefaultMaterial(),
																					true);
	}

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
CSelectMapScene::ResetCursor()
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
* Scanes the map directory fora ll map files for the game.
*
* @author Bryce Booth
* @return True	States that the scan was successful.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSelectMapScene::ScanMapFiles()
{
	//Set default variables
	WIN32_FIND_DATA w32FileData;
	HANDLE hHandle   = 0;
	char* cpFileName = 0;
	wchar_t* wcpMapsSearch = new wchar_t[256];


	//Compile map directory string
	swprintf_s(wcpMapsSearch, 256, L"%s/*.map", Defines::GetWMapDirectory());


	//Scan map directory
	hHandle = FindFirstFile(wcpMapsSearch, &w32FileData);

	if (hHandle != INVALID_HANDLE_VALUE)
	{
		hHandle = FindFirstFile(wcpMapsSearch, &w32FileData);


		//Loop through data
		do
		{
			//Convert file name
			StrUtilities::ConvertToChar(w32FileData.cFileName, cpFileName);


			//Add map to maps vector
			m_vecMaps.push_back(cpFileName);
		}
		while(FindNextFile(hHandle, &w32FileData));
	}
	else
	{
		char* cpBuffer = new char[32];
		sprintf_s(cpBuffer, 32, "No maps are available.");


		m_vecMaps.push_back(cpBuffer);


		m_bNoMaps = true;
	}


	//Close handle
	FindClose(hHandle);


	//Delete map folder string
	FW_ADELETE(wcpMapsSearch);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Increments the current map selection.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void 
CSelectMapScene::IncrementMapSelection()
{
	//Check if timer is larger then delay
	if (m_fMapSwitchTimer > m_fMapSwitchDelay)
	{
		//Check if not at last map
		if (m_uiCurrentMapId + 1 != static_cast<unsigned int>(m_vecMaps.size()))
		{
			if (m_uiMapSelectorPosition == s_eMaxMapsToDisplay - 1)
			{
				m_uiMapsReadFromId += 1;


				UpdateMapTitles();
			}


			if (m_uiMapSelectorPosition < s_eMaxMapsToDisplay - 1)
			{
				++ m_uiMapSelectorPosition;


				UpdateMapSelector();
			}


			m_uiCurrentMapId += 1;
			

			ReadSelectedMap();
			UpdateMapTitles();
			UpdateScrollArrows();


			//Reset map switch timer
			m_fMapSwitchTimer = 0.0f;


			//Play sound
			CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");
		}
	}
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Decrements the current map selection.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSelectMapScene::DecrementMapSelection()
{
	//Check if timer is larger then delay
	if (m_fMapSwitchTimer > m_fMapSwitchDelay)
	{
		//Check if not at last map
		if (m_uiCurrentMapId != 0)
		{
			if (m_uiMapSelectorPosition == 0 && m_uiMapsReadFromId != 0)
			{
				m_uiMapsReadFromId -= 1;


				UpdateMapTitles();
			}


			if (m_uiMapSelectorPosition != 0)
			{
				-- m_uiMapSelectorPosition;


				UpdateMapSelector();
			}


			m_uiCurrentMapId -= 1;
			

			ReadSelectedMap();
			UpdateMapTitles();
			UpdateScrollArrows();


			//Reset map switch timer
			m_fMapSwitchTimer = 0.0f;


			//Play sound
			CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");
		}
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Increments the current difficulty selection.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSelectMapScene::IncrementDifficultySelection()
{
	if (m_fDifficultySwitchTimer > m_fDifficultySwitchDelay)
	{
		if (m_eSelectedDifficulty == DIFFICULTY_EASY || m_eSelectedDifficulty == DIFFICULTY_MEDIUM)
		{
			if (m_eSelectedDifficulty == DIFFICULTY_EASY)
			{
				m_eSelectedDifficulty = DIFFICULTY_MEDIUM;
			}
			else if (m_eSelectedDifficulty == DIFFICULTY_MEDIUM)
			{
				m_eSelectedDifficulty = DIFFICULTY_HARD;
			}

			//Play sound
			CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");


			m_fDifficultySwitchTimer = 0.0f;


			UpdateDifficultyButtons();
		}
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Decrements the current difficulty selection.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSelectMapScene::DecrementDifficultySelection()
{	
	if (m_fDifficultySwitchTimer > m_fDifficultySwitchDelay)
	{
		if (m_eSelectedDifficulty == DIFFICULTY_MEDIUM || m_eSelectedDifficulty == DIFFICULTY_HARD)
		{
			if (m_eSelectedDifficulty == DIFFICULTY_MEDIUM)
			{
				m_eSelectedDifficulty = DIFFICULTY_EASY;
			}
			else if (m_eSelectedDifficulty == DIFFICULTY_HARD)
			{
				m_eSelectedDifficulty = DIFFICULTY_MEDIUM;
			}


			//Play sound
			CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");
	

			m_fDifficultySwitchTimer = 0.0f;


			UpdateDifficultyButtons();
		}
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Selects the current map and switches to the select difficulty phase.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSelectMapScene::SelectMap()
{
	if (m_bNoMaps == false)
	{
		m_pRenderer->GetSpriteManager().SetModulate(0xFFAAAAAA, m_uiSpriteMapContainer);
		m_eScenePhase = SELMAPPHASE_SELDIFFICULTY;
		UpdateMapTitles();


		m_eSelectedDifficulty = DIFFICULTY_MEDIUM;
		UpdateDifficultyButtons();


		CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Select.wav");
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Selects the current difficulty and starts the game.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSelectMapScene::SelectDifficulty()
{
	char* cpBuffer = new char[1024];
	sprintf_s(cpBuffer, 1024, "%s/%s", Defines::GetMapDirectory(), m_vecMaps[m_uiCurrentMapId]);


	CGameSceneData* pGameSceneData = new CGameSceneData();


	pGameSceneData->SetMapFile(cpBuffer);
	pGameSceneData->SetPlayerStartGold(m_uiPlayerStartGold);
	pGameSceneData->SetPlayerStartLives(m_uiPlayerStartLives);
	pGameSceneData->SetDifficulty(m_eSelectedDifficulty);


	CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Select.wav");


	CApplication::GetInstance().GetGameWindow().SetMainScene(SCENE_GAME, pGameSceneData);
	CApplication::GetInstance().GetGameWindow().SetOverlayScene(OVERLAYSCENE_DELETE);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the select map scene back to the main menu scene.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSelectMapScene::BackToMainMenu()
{
	CApplication::GetInstance().GetGameWindow().GetCurrentMainScene().RecoverFromOverlayScene();


	CApplication::GetInstance().GetGameWindow().SetOverlayScene(OVERLAYSCENE_DELETE);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the current scene phase back to select map from select difficulty.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSelectMapScene::BackToSelectMap()
{
	m_pRenderer->GetSpriteManager().SetModulate(0xFFFFFFFF, m_uiSpriteMapContainer);
	m_eScenePhase = SELMAPPHASE_SELECTMAP;


	m_eSelectedDifficulty = DIFFICULTY_INVALID;


	UpdateMapTitles();
	UpdateScrollArrows();
	UpdateDifficultyButtons();
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Updates the text of the map titles based on which map to start reading from.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSelectMapScene::UpdateMapTitles()
{
	//Get window dimentions
	const float kfWindowCenterX = static_cast<float>(CApplication::GetInstance().GetGameWindow().GetClientWidth())  / 2.0f;
	const float kfWindowCenterY = static_cast<float>(CApplication::GetInstance().GetGameWindow().GetClientHeight()) / 2.0f;


	//Get application base ratio
	const float kfBaseRatio = CApplication::GetInstance().GetBaseDimentionRatio();


	//Calculate text position X 
	float fTextPositionX = kfWindowCenterX;
	fTextPositionX += static_cast<float>(s_eMapsTextOffsetX) * kfBaseRatio;


	//Calculate text position Y
	float fTextPositionY = kfWindowCenterY;
	fTextPositionY += static_cast<float>(s_eMapsTextOffsetY) * kfBaseRatio;


	//Calculate map text margin
	const float kfTextMapMargin = static_cast<float>(s_eMapsTextMapMargin) * kfBaseRatio;


	//Get number of maps
	unsigned int uiMapsSize   = static_cast<unsigned int>(m_vecMaps.size());


	for (unsigned int i = 0; i < s_eMaxMapsToDisplay && i < m_vecMaps.size(); ++ i)
	{
		m_pTextMapTitles[i]->SetText(m_vecMaps[m_uiMapsReadFromId + i]);
		m_pTextMapTitles[i]->SetPositionX(static_cast<int>(fTextPositionX));
		m_pTextMapTitles[i]->SetPositionY(static_cast<int>(fTextPositionY) + (static_cast<int>(kfTextMapMargin) * i));


		if (m_eScenePhase == SELMAPPHASE_SELDIFFICULTY)
		{
			if (i != m_uiMapSelectorPosition)
			{
				m_pTextMapTitles[i]->SetColour(0xFF444444);
			}
		}
		else if (i == m_uiMapSelectorPosition)
		{
			m_pTextMapTitles[i]->SetColour(m_eMapsTextHoverColour);
		}
		else
		{
			m_pTextMapTitles[i]->SetColour(s_eMapsTextIdleColour);
		}
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Updates the player gold and lives text for the current selected map.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSelectMapScene::UpdatePlayerText()
{
	//Default varaibles
	char cBuffer[128];


	//Set gold
	sprintf_s(cBuffer, 128, "%i", m_uiPlayerStartGold);
	m_pTextMapPlayerGold->SetText(cBuffer);


	//Set lives
	sprintf_s(cBuffer, 128, "%i", m_uiPlayerStartLives);
	m_pTextMapPlayerLives->SetText(cBuffer);
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the current scene phase back to select map from select difficulty.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSelectMapScene::UpdateScrollArrows()
{
	if (m_uiMapsReadFromId > 0)
	{
		m_pRenderer->GetSpriteManager().SetVisible(true, m_uiSpriteArrowUp);
	}
	else
	{
		m_pRenderer->GetSpriteManager().SetVisible(false, m_uiSpriteArrowUp);
	}


	if (m_uiMapsReadFromId + s_eMaxMapsToDisplay == static_cast<int>(m_vecMaps.size()) ||
		static_cast<int>(m_vecMaps.size()) < s_eMaxMapsToDisplay)
	{
		m_pRenderer->GetSpriteManager().SetVisible(false, m_uiSpriteArrowDown);
	}
	else
	{
		m_pRenderer->GetSpriteManager().SetVisible(true, m_uiSpriteArrowDown);
	}
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the current scene phase back to select map from select difficulty.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSelectMapScene::UpdateMapPreviewer()
{
	wchar_t* wcpFile = 0;

	StrUtilities::ConvertToWChar(m_strMapPreviewFile.c_str(), wcpFile);


	m_uiPreviewTextureId = m_pRenderer->GetTextureManager().LoadTextureFile(wcpFile);


	delete[] wcpFile;
	wcpFile = 0;
}





/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the current scene phase back to select map from select difficulty.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSelectMapScene::UpdateDifficultyButtons()
{
	m_pRenderer->GetSpriteManager().SetModulate(s_eDifficultyIdleColour, m_uiSpriteEasy);
	m_pRenderer->GetSpriteManager().SetModulate(s_eDifficultyIdleColour, m_uiSpriteMedium);
	m_pRenderer->GetSpriteManager().SetModulate(s_eDifficultyIdleColour, m_uiSpriteHard);


	switch (m_eSelectedDifficulty)
	{
	case DIFFICULTY_EASY:
		m_pRenderer->GetSpriteManager().SetModulate(s_eDifficultyHoverColour, m_uiSpriteEasy);
		break;

	case DIFFICULTY_MEDIUM:
		m_pRenderer->GetSpriteManager().SetModulate(s_eDifficultyHoverColour, m_uiSpriteMedium);
		break;

	case DIFFICULTY_HARD:
		m_pRenderer->GetSpriteManager().SetModulate(s_eDifficultyHoverColour, m_uiSpriteHard);
		break;
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the current scene phase back to select map from select difficulty.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSelectMapScene::UpdateMapSelector()
{
	m_pRenderer->GetSpriteManager().SetPosition(
		CVector3(457.0f, 260.0f + (m_uiMapSelectorPosition * s_eMapsTextMapMargin), 0.0f),
		m_uiSpriteSelectorBar);
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Reads details out of the currently selected map
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSelectMapScene::ReadSelectedMap()
{
	if (m_bNoMaps == false)
	{
		//Setup default varaibles
		char cMapFileExtension[256];
		bool bLoadedMapFile = false;
		bool bLoadedPlayerGold = false;
		bool bLoadedPlayerLives = false;
		bool bLoadedMapPreview = false;


		//Compile map directory string
		sprintf_s(cMapFileExtension, 256, "%s/%s", Defines::GetMapDirectory(), m_vecMaps[m_uiCurrentMapId]);


		bLoadedMapFile = m_pINIMapFile->LoadINIFile(cMapFileExtension); 


		LOG_FATALERROR(bLoadedMapFile == false, "Map file not found!");


		bLoadedPlayerGold  = m_pINIMapFile->GetValue("PlayerStats", "Gold" , m_uiPlayerStartGold);
		bLoadedPlayerLives = m_pINIMapFile->GetValue("PlayerStats", "Lives", m_uiPlayerStartLives);
		bLoadedMapPreview  = m_pINIMapFile->GetValue("Meta Data", "MapPreviewFile", m_strMapPreviewFile);


		LOG_ERROR(bLoadedPlayerGold  == false, "Map file is missing player gold!");
		LOG_ERROR(bLoadedPlayerLives == false, "Map file is missing player lives!");
		LOG_ERROR(bLoadedMapPreview == false, "Map file is missing the preview screen shot!");


		char cBuffer[512];
		sprintf_s(cBuffer, 512, "%s/%s", Defines::GetMapDirectory(), m_strMapPreviewFile.c_str());


		m_strMapPreviewFile = cBuffer;


		UpdateMapPreviewer();
		UpdatePlayerText();
		UpdateScrollArrows();
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
CSelectMapScene::Deinitialise()
{
	FW_DELETEARRAY(m_pTextMapTitles, s_eMaxMapsToDisplay);
	FW_DELETE(m_pTextMapPlayerGold);
	FW_DELETE(m_pTextMapPlayerLives);
	FW_DELETEVECTOR(char*, m_vecMaps);
	FW_DELETE(m_pINIMapFile);


	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiSpriteBackground);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiSpriteMapContainer);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiSpriteMapPreviewer);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiSpriteSelectorBar);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiSpriteEasy);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiSpriteMedium);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiSpriteHard);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiSpriteArrowUp);
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiSpriteArrowDown);


	m_pRenderer->GetVertexBufferManager().DeleteVertexBuffer(m_uiVertexQuadID);
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Draws debug information about the scene to the window.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSelectMapScene::DrawDebugInfo()
{
	if (m_pLogWindow)
	{
		
		COORD MousePos = CApplication::GetInstance().GetGameWindow().GetMosueCoords();
			
		m_pLogWindow->EmptyBuffer();
		m_pLogWindow->SetErrorMessagePosition(m_rctLogBounds);
		m_pLogWindow->WriteToBuffer("Mouse X: %i", MousePos.X);
		m_pLogWindow->WriteToBuffer("Mouse Y: %i", MousePos.Y);
		m_pLogWindow->WriteToBuffer("Map Selector Position: %i", m_uiMapSelectorPosition); 
		m_pLogWindow->WriteToBuffer("Current Map Id: %i", m_uiCurrentMapId);
		m_pLogWindow->WriteToBuffer("Read From Id: %i", m_uiMapsReadFromId);
		m_pLogWindow->WriteToBuffer("");
		m_pLogWindow->WriteToBuffer("Map Gold: %i", m_uiPlayerStartGold); 
		m_pLogWindow->WriteToBuffer("Map Lives: %i", m_uiPlayerStartLives);
		m_pLogWindow->WriteToBuffer("Difficulty: %i", m_eSelectedDifficulty);
		//m_pLogWindow->WriteToBuffer("Map Preview: %s", m_uiPlayerStartLives);
		m_pLogWindow->WriteToBuffer("");
		m_pLogWindow->WriteToBuffer("FPS: %i", m_uiFramesPerSecond);
		m_pLogWindow->WriteToBuffer("");
		
	 

		m_pLogWindow->SetFont(m_uiFontId);
		m_pLogWindow->PrintToScreen(m_uiLogBoxId);
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
CSelectMapScene::MouseSelect()
{
	RECT SpriteBounds;
	CVector3 vecPos;
	int iWidth = 0;
	int iHeight = 0;

	const unsigned int kuiWindowWidth = CApplication::GetInstance().GetGameWindow().GetWindowWidth();
	const unsigned int kuiWindowHeight =  CApplication::GetInstance().GetGameWindow().GetWindowHeight();
	
	COORD MouseCords;
	MouseCords = CApplication::GetInstance().GetGameWindow().GetMosueCoords();
	
	//Up Arrow	
	SpriteBounds = m_pRenderer->GetSpriteManager().GetRect(m_uiSpriteArrowUp);

	vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiSpriteArrowUp);

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
			DecrementMapSelection();		
		}
	}

	//Down Arrow
	SpriteBounds = m_pRenderer->GetSpriteManager().GetRect(m_uiSpriteArrowDown);

	vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiSpriteArrowDown);

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
			IncrementMapSelection();		
		}
	}

	for(unsigned int i = 0; i < s_eMaxMapsToDisplay; ++i)
	{
		int iTemp = i;

		RECT TextBounds = m_pTextMapTitles[i]->GetRect();

		if(MouseCords.X >= TextBounds.left  &&
		   MouseCords.X <= TextBounds.right &&
		   MouseCords.Y >= TextBounds.top   &&
		   MouseCords.Y <= TextBounds.bottom)
		{
			if(m_bMouseClick == true)
			{
				m_uiMapSelectorPosition = i;
				m_uiCurrentMapId = m_uiMapsReadFromId + i;

				ReadSelectedMap();
				UpdateMapTitles();


				//Reset map switch timer
				m_fMapSwitchTimer = 0.0f;


				//Play sound
				CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");
				
				

				UpdateMapSelector();	

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
CSelectMapScene::DoubleClicked()
{	
	COORD MouseCords;
	MouseCords = CApplication::GetInstance().GetGameWindow().GetMosueCoords();

	for(unsigned int i = 0; i < s_eMaxMapsToDisplay; ++i)
	{
		RECT TextBounds = m_pTextMapTitles[i]->GetRect();

		if(MouseCords.X >= TextBounds.left  &&
		   MouseCords.X <= TextBounds.right &&
		   MouseCords.Y >= TextBounds.top   &&
		   MouseCords.Y <= TextBounds.bottom)
		{
			m_uiCurrentMapId = m_uiMapsReadFromId + i;

			ReadSelectedMap();
			UpdateMapTitles();


			//Reset map switch timer
			m_fMapSwitchTimer = 0.0f;


			//Play sound
			CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");
			
			m_uiMapSelectorPosition = i;

			UpdateMapSelector();	

			SelectMap();
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
CSelectMapScene::MouseSelectDifficulty()
{
	RECT SpriteBounds;
	CVector3 vecPos;
	int iWidth = 0;
	int iHeight = 0;

	COORD MouseCords;
	MouseCords = CApplication::GetInstance().GetGameWindow().GetMosueCoords();

	//Selected easy option
	SpriteBounds = m_pRenderer->GetSpriteManager().GetRect(m_uiSpriteEasy);

	vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiSpriteEasy);

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
		if(m_eSelectedDifficulty != DIFFICULTY_EASY)
		{
			m_eSelectedDifficulty = DIFFICULTY_EASY;

			CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");

			m_fDifficultySwitchTimer = 0.0f;
		}

			UpdateDifficultyButtons();
		if(m_bMouseClick == true)
		{
			SelectDifficulty();
		}
	}

	//Selected medium option
	SpriteBounds = m_pRenderer->GetSpriteManager().GetRect(m_uiSpriteMedium);

	vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiSpriteMedium);

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
		if(m_eSelectedDifficulty != DIFFICULTY_MEDIUM)
		{
			m_eSelectedDifficulty = DIFFICULTY_MEDIUM;

			CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");

			m_fDifficultySwitchTimer = 0.0f;

			UpdateDifficultyButtons();
		}

		if(m_bMouseClick == true)
		{
			SelectDifficulty();
		}
	}

	//Selected Hard option
	SpriteBounds = m_pRenderer->GetSpriteManager().GetRect(m_uiSpriteHard);

	vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiSpriteHard);

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
		if(m_eSelectedDifficulty != DIFFICULTY_HARD)
		{
			m_eSelectedDifficulty = DIFFICULTY_HARD;

			CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");

			m_fDifficultySwitchTimer = 0.0f;

			UpdateDifficultyButtons();
		}

		if(m_bMouseClick == true)
		{
			SelectDifficulty();
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
CSelectMapScene::ScrollUp()
{
	if(m_uiMapsReadFromId == 0)
	{
		DecrementMapSelection();
	}
	else if (m_uiCurrentMapId > 0)
	{
		if (m_uiMapsReadFromId <= s_eMaxMapsToDisplay)
		{
			m_uiCurrentMapId -= m_uiMapsReadFromId;
			m_uiMapsReadFromId = 0;
		}
		else
		{
			m_uiMapsReadFromId -= s_eMaxMapsToDisplay;
			m_uiCurrentMapId -= s_eMaxMapsToDisplay;
		}

		
		ReadSelectedMap();
		UpdateMapTitles();
		UpdateScrollArrows();
		UpdateMapSelector();


		//Play sound
		CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");
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
CSelectMapScene::ScrollDown()
{
	/*
	if (m_uiMapsReadFromId + s_eMaxMapsToDisplay >= m_vecMaps.size())
	{
		IncrementMapSelection();
	}
	else
	{
		if (m_uiCurrentMapId + s_eMaxMapsToDisplay >= m_vecMaps.size())
		{
			m_uiCurrentMapId   = (static_cast<int>(m_vecMaps.size()) - s_eMaxMapsToDisplay) - m_uiMapsReadFromId;
			m_uiMapsReadFromId = static_cast<int>(m_vecMaps.size()) - s_eMaxMapsToDisplay;
		}


		ReadSelectedMap();
		UpdateMapTitles();
		UpdateScrollArrows();
		UpdateMapSelector();


		//Play sound
		CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Menu-Change.wav");
	}
	*/
}


void
CSelectMapScene::SetDoubleClick(bool _bDoubleClick)
{
	m_bDoubleClick = _bDoubleClick;
}