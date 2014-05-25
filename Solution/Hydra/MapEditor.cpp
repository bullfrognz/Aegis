//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   MapEditor.cpp
//  Description :   Implementation of Map editor
//  Author      :   Daniel Langsford
//  Mail        :   daniel.langsford@mediadesign.school.nz
//

// Library Includes
#include <stdio.h>

// Local Includes
#include "resource.h"

#include "viewport.h"
#include "meshmanager.h"
#include "InputManager.h"
#include "logmanager.h"
#include "LogTarget.h"

#include "LogWindow.h"
#include "LogOutPut.h"
#include "Application.h"
#include "D3DRenderer.h"
#include "Window.h"

#include "StaticObject.h"
#include "Macros.h"
#include "Tower.h"
#include "mouse.h"
#include "player.h"

#include "vector2.h"
#include "utility.h"
#include "raycast.h"
#include "XInputcontroller.h"
#include "INIParser.h"

#include "GameCamera.h"

#include "SpriteManager.h"
#include "Application.h"
#include "XInputController.h"
#include "EnemySpawner.h"
#include "Camera.h"

#include <direct.h>

#include "Terrain.h"

#include "LightManager.h"


// This Include
#include "MapEditor.h"

// Static Variables
unsigned int
CMapEditor::s_uiGridWidth = 0;

unsigned int
CMapEditor::s_uiGridHeight = 0;

CINIParser*
CMapEditor::s_pParser = 0;

wchar_t*
CMapEditor::m_wcFileName = 0;

unsigned int
CMapEditor::m_uiNumWaypoints = 0;

bool 
CMapEditor::s_bQuitting = false;

// Implementation
	
CMapEditor::CMapEditor()
: m_uiFrameCount(0)
, m_uiCurrentFrameCount(0)
, m_uiSelectedTileX(0)
, m_uiSelectedTileY(0)
, m_fFrameTimer(0.0f)
, m_bPlacingWaypoints(0)
, m_fClickTimer(0.0f)
, m_fClickRefresh(0.5f)
, m_bClicked(false)
, m_bPlacable(false)
, m_bInitialise(false)
, m_bLeftClick(0)
, m_bRightClick(0)
, m_bSpriteSelected(0)
, m_bSave(0)
, m_bLoad(0)
, m_fScreenShotCameraHeight(0.0f)
, m_bTakeScreenShot(false)
, m_iFrameCounter(0)
, m_fResetTime(0.2f)
, m_fResetBackTime(0.2f)
, m_fTimer(0.0f)
, m_fBackTimer(0.0f)
, m_bTriggerUsed(false)
, m_bBackPressed(false)
, m_bPollControllerActive(true)
, m_bControllerActive(false)
{

}

CMapEditor::~CMapEditor()
{
	Deinitialise();
}

/**
*
* This function Initialises lights in the scene
*
* @author Daniel Langsford
* @param _pRenderer: Pointer to the renderer.
* @returns a bool representing function success 
*
*/
bool
CMapEditor::InitialiseLights(CD3DRenderer* _pRenderer)
{	
	assert(_pRenderer);

	m_uiLightDirectional = _pRenderer->GetLightManager().AddLight();

	return (true);
}

/**
*
* This function Initialises viewports in the scene
*
* @author Daniel Langsford
* @param _pRenderer: Pointer to the renderer.
* @returns a bool representing function success 
*
*/
bool
CMapEditor::InitialiseViewports(CD3DRenderer* _pRenderer)
{
	assert(_pRenderer);

	const unsigned int kuiWindowWidth = CApplication::GetInstance().GetGameWindow().GetClientWidth();
	const unsigned int kuiWindowHeight = CApplication::GetInstance().GetGameWindow().GetClientHeight();

	m_pViewport = new CViewport();

	m_pViewport->Initialise(kuiWindowWidth/2, kuiWindowHeight/2, kuiWindowWidth, kuiWindowHeight, 0, _pRenderer);

	m_pViewport->CreateGameCamera(3.14159682f/3.0f, 0.1f, 1000.0f, &m_pInputManager->GetDirectInput(), &m_pInputManager->GetXInputController(), m_pTerrain);
	m_pViewport->SetActiveCamera(m_pViewport->GetLastCreatedCamera());

	dynamic_cast<CGameCamera*>(m_pViewport->GetActiveCamera())->SetMouseScrollingEnabled(false);

	return (true);
}

/**
*
* This function Initialises the map editor grid in the scene
*
* @author Daniel Langsford
* @param _pRenderer Pointer to the renderer.
* @returns a bool representing function success 
*
*/
bool
CMapEditor::InitialiseGrid(CD3DRenderer* _pRenderer)
{
	m_pTerrain = new CTerrain;
	m_pTerrain->Initialise(_pRenderer, 2.0f, 1.0f, false);
	InitialiseBlankGrid();	
	
	return(true);
}

/**
*
* This function Initialises the map editor
*
* @author Daniel Langsford
* @param _pRenderer: Pointer to the renderer.
* @param _pSceneData: Any additional data needed for the scene.
* @returns a bool representing function success 
*
*/
bool
CMapEditor::InitialiseScene(CD3DRenderer* _pRenderer, void* _pSceneData)
{
	assert(_pRenderer);

	m_bControllerActive = false;
	
	CWindow& rGameWindow = CApplication::GetInstance().GetGameWindow();
	const unsigned int kuiClientWidth = rGameWindow.GetClientWidth();
	const unsigned int kuiClientHeight = rGameWindow.GetClientHeight();

	m_pInputManager->GetXInputController().SetDisabled(true);

	InitialiseGrid(_pRenderer);

	InitialiseSprites(_pRenderer);

	//Initialise XInput
	m_pInputManager->GetXInputController().AddTarget(XBUTTON_A, this);
	m_pInputManager->GetXInputController().AddTarget(XBUTTON_B, this);
	m_pInputManager->GetXInputController().AddTarget(XTRIGGER_RIGHT, this);
	m_pInputManager->GetXInputController().AddTarget(XTRIGGER_LEFT, this);
	m_pInputManager->GetXInputController().AddTarget(XBUTTON_BACK, this);
	//m_pXInput->AddIsActiveTarget(this);

		//Initialise Player Input
	m_pInputManager->GetDirectInput().AddTarget(DMOUSE_LEFTCLICK, this);
	m_pInputManager->GetDirectInput().AddTarget(DMOUSE_RIGHTCLICK, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_1, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_2, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_3, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_4, this);
	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_ENTER, this);

	//Initialise Logging
	m_pLogManager = new CLogManager;
	m_pLogManager->Initialise();

	LogBounds.top = 10;
	LogBounds.left = static_cast<LONG>(kuiClientWidth * 0.75f);
	LogBounds.right = kuiClientWidth;
	LogBounds.bottom = kuiClientHeight;

	//Set up log box
	m_LogWindow = &_pRenderer->GetLogWindow();
	m_uiFontId = m_LogWindow->CreateNewFont(8, 16, 1000, L"Aerial");
	m_uiLogBoxId = m_LogWindow->CreateNewLogBox(D3DCOLOR_XRGB(255,0,0), LogBounds, 0);
	
	m_SelectedTile = new CTile;

	m_eCurrentTileType = TILETYPE_WATER;

	if(s_bQuitting == true)
	{
		CApplication::GetInstance().GetGameWindow().SetMainScene(SCENE_MAINMENU);
		s_bQuitting = false;
	}
	

	return(true);
}


/**
*
* This function initialises all the sprites used in the scene
*
* @author Daniel Langsford
* @param _pRenderer: Pointer to the renderer.
* @returns a bool representing function success
*
*/
bool
CMapEditor::InitialiseSprites(CD3DRenderer* _pRenderer)
{
	CWindow& rGameWindow = CApplication::GetInstance().GetGameWindow();
	const unsigned int kuiWindowWidth = 1280;
	const unsigned int kuiWindowHeight = 1024;

	//Load water icons
	unsigned int uiPositionX = kuiWindowWidth / 2;
	unsigned int uiPositionY = kuiWindowHeight - 100;

	m_uiWaterIconID = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Icons/Icon_Water.png");
	assert(m_uiWaterIconID != -1);
	_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiWaterIconID);
	_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiWaterIconID);

	RECT SpriteRect = _pRenderer->GetSpriteManager().GetRect(m_uiWaterIconID);	

	float fWidth = static_cast<float>(SpriteRect.right - SpriteRect.left);
	float fHeight = static_cast<float>(SpriteRect.bottom - SpriteRect.top);

	CVector3 vecPos;
	vecPos = _pRenderer->GetSpriteManager().GetPosition(m_uiWaterIconID);
	vecPos.x = uiPositionX - (2.0f * fWidth);
	vecPos.y = static_cast<float>(uiPositionY);
	
	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiWaterIconID);

	//Load Path Icon.
	m_uiPathIconID = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Icons/Icon_Path.png");
	assert(m_uiPathIconID != -1);
	_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiPathIconID);
	_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiPathIconID);

	SpriteRect = _pRenderer->GetSpriteManager().GetRect(m_uiPathIconID);	

	fWidth = static_cast<float>(SpriteRect.right - SpriteRect.left);
	fHeight = static_cast<float>(SpriteRect.bottom - SpriteRect.top);

	vecPos = _pRenderer->GetSpriteManager().GetPosition(m_uiPathIconID);
	vecPos.x = uiPositionX - (1.0f * fWidth);
	vecPos.y = static_cast<float>(uiPositionY);

	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiPathIconID);

	//Load Raised tile icon.
	m_uiRaisedIconID = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Icons/Icon_Raised.png");
	assert(m_uiRaisedIconID != -1);
	_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiRaisedIconID);
	_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiRaisedIconID);

	SpriteRect = _pRenderer->GetSpriteManager().GetRect(m_uiRaisedIconID);	

	fWidth = static_cast<float>(SpriteRect.right - SpriteRect.left);
	fHeight = static_cast<float>(SpriteRect.bottom - SpriteRect.top);

	vecPos = _pRenderer->GetSpriteManager().GetPosition(m_uiRaisedIconID);
	vecPos.x = static_cast<float>(uiPositionX);
	vecPos.y = static_cast<float>(uiPositionY);

	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiRaisedIconID);

	//Load Waypoint tile icon.
	m_uiWaypointIconID = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Icons/Icon_Waypoint.png");
	assert(m_uiWaypointIconID != -1);
	_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiWaypointIconID);
	_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiWaypointIconID);

	SpriteRect = _pRenderer->GetSpriteManager().GetRect(m_uiWaypointIconID);	

	fWidth = static_cast<float>(SpriteRect.right - SpriteRect.left);
	fHeight = static_cast<float>(SpriteRect.bottom - SpriteRect.top);

	vecPos = _pRenderer->GetSpriteManager().GetPosition(m_uiWaypointIconID);
	vecPos.x = uiPositionX + fWidth;
	vecPos.y = static_cast<float>(uiPositionY);

	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiWaypointIconID);

	//File options icons
	m_uiFileOptions = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Icons/FileIcons.png");
	assert(m_uiFileOptions != -1);

	_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiFileOptions);
	
	SpriteRect = _pRenderer->GetSpriteManager().GetRect(m_uiFileOptions);
	fWidth = static_cast<float>(SpriteRect.right - SpriteRect.left);
	fHeight = static_cast<float>(SpriteRect.bottom - SpriteRect.top);

	SpriteRect.bottom = static_cast<LONG>(0.25f * fHeight);

	_pRenderer->GetSpriteManager().SetRect(&SpriteRect, m_uiFileOptions);

	_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiFileOptions);
	_pRenderer->GetSpriteManager().SetPosition(CVector3(10, 10, 0), m_uiFileOptions);

	//Selection Icon
	//This sprite is used to represent which icon is selected.
	m_uiIconSelectionID = _pRenderer->GetSpriteManager().AddSprite(L"Assets/Icons/IconSelection.png");
	assert(m_uiIconSelectionID != -1);

	_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiIconSelectionID);
	_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiIconSelectionID);

	vecPos = _pRenderer->GetSpriteManager().GetPosition(m_uiWaterIconID);

	_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiIconSelectionID);

	return(true);

}

/**
*
* This function processes everything in the scene
*
* @author Daniel Langsford
* @param _fDeltaTick: Time since last process call.
* @returns void
*
*/

void
CMapEditor::ProcessScene(float _fDeltaTick)
{
	m_fFrameTimer += _fDeltaTick;

	if(m_fFrameTimer >= 1.0f)
	{
		m_uiCurrentFrameCount = m_uiFrameCount;
		
		m_uiFrameCount = 0;
		m_fFrameTimer -= 1.0f;
	}

	if(m_bClicked)
	{
		m_fClickTimer += _fDeltaTick;
	}
	else
	{
		m_fClickTimer = 0.0f;
	}

	m_pTerrain->Process(_fDeltaTick);	
	m_LogWindow->Process(_fDeltaTick);

	SpriteSelect();
	m_pViewport->Process(_fDeltaTick);

	if(!m_bSpriteSelected)
	{
		ObjectSelect(_fDeltaTick);
	}

	if(m_bTakeScreenShot)
	{
		++m_iFrameCounter;
		m_pScreenShotViewPort->Process(_fDeltaTick);
	}
	
	if(m_iFrameCounter >= 4)
	{
		m_bTakeScreenShot = false;
		m_iFrameCounter = 0;
		delete[] m_wcFileName;
		m_wcFileName = 0;

		delete m_pScreenShotViewPort;
		m_pScreenShotViewPort = 0;
	}

	if(m_bTriggerUsed == true)
	{
		m_fTimer += _fDeltaTick;

		if(m_fTimer >= m_fResetTime)
		{
			m_bTriggerUsed = false;
			m_fTimer = 0.0f;
		}
	}

	ResetCursor();

}

/**
*
* This function draws everything in the scene
*
* @author Daniel Langsford
* @param _pRenderer: Pointer to the renderer
* @returns void. 
*
*/
void
CMapEditor::DrawScene(CD3DRenderer* _pRenderer)
{
	if(m_iFrameCounter == 2)
	{		
		_pRenderer->TakeScreenShot(CMapEditor::m_wcFileName);
	}
	else if(m_iFrameCounter >= 1)
	{
		_pRenderer->GetLightManager().TurnOnLight(m_uiLightDirectional);
		m_pTerrain->Draw();
	}
	else
	{
		++m_uiFrameCount;

		_pRenderer->GetLightManager().TurnOnLight(m_uiLightDirectional);
		
		if(m_bPlacingWaypoints == false)
		{
			m_pTerrain->Draw(m_SelectedTile);

			if(m_bPlacable == true)
			{
				_pRenderer->GetDeviceManager().SetRenderState(D3DRS_TEXTUREFACTOR, 0xFF008800);
				_pRenderer->GetDeviceManager().SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
				_pRenderer->GetDeviceManager().SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
				_pRenderer->GetDeviceManager().SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);
			}
			else
			{
				_pRenderer->GetDeviceManager().SetRenderState(D3DRS_TEXTUREFACTOR, 0x00CC0000);
				_pRenderer->GetDeviceManager().SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
				_pRenderer->GetDeviceManager().SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
				_pRenderer->GetDeviceManager().SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);
			}
			
			m_pTerrain->DrawTile(m_uiSelectedTileX, m_uiSelectedTileY);
			
			_pRenderer->GetDeviceManager().ResetTextureStageStates(0);

		}
		else
		{
			m_pTerrain->Draw();
		}
			
		m_pTerrain->GetWaypointManager().Draw(_pRenderer->GetDeviceManager());

		//Only draws debug info in debug mode
		#if _DEBUG
		DrawLogWindow();
		#endif

		_pRenderer->GetSpriteManager().Draw();
	}	
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Resets the cursor for the select map scene.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CMapEditor::ResetCursor()
{
	CApplication::GetInstance().GetGameWindow().ShowCursor();
}


/**
*
* This function draws all debug logging information.
*
* @author Daniel Langsford
* @returns void 
*
*/
void
CMapEditor::DrawLogWindow()
{
	COORD MousePos = CApplication::GetInstance().GetGameWindow().GetMosueCoords();
	
	CMapEditor::m_uiNumWaypoints = m_pTerrain->GetWaypointManager().GetNumWaypoints();

	m_LogWindow->EmptyBuffer();
	m_LogWindow->SetErrorMessagePosition(LogBounds);
	m_LogWindow->WriteToBuffer("FPS: %i", m_uiCurrentFrameCount);	
	m_pLogWindow->WriteToBuffer("Mouse Pos: (%i, %i)", MousePos.X, MousePos.Y); 
	m_pLogWindow->WriteToBuffer("Number of Waypoints: %i", CMapEditor::m_uiNumWaypoints);

	m_LogWindow->SetFont(m_uiFontId);
	m_LogWindow->PrintToScreen(m_uiLogBoxId);
}

/**
*
* This function detects when the mouse is on a sprite, and reacts accordingly.
*
* @author Daniel Langsford
* @returns void.
*
*/
void
CMapEditor::SpriteSelect()
{
	m_bSpriteSelected = false;

	HWND hWnd = CApplication::GetInstance().GetGameWindow().GetWindowHandle();

	const unsigned int kuiClientWidth = CApplication::GetInstance().GetGameWindow().GetClientWidth();
	const unsigned int kuiClientHeight =  CApplication::GetInstance().GetGameWindow().GetClientHeight();

	COORD MouseCords;
	MouseCords = CApplication::GetInstance().GetGameWindow().GetMosueCoords();
	CD3DRenderer* pRenderer = CApplication::GetInstance().GetGameWindow().GetRenderer();
	
	//Selection of water tile
	RECT SpriteBounds = pRenderer->GetSpriteManager().GetRect(m_uiWaterIconID);
	int iWidth = SpriteBounds.right - SpriteBounds.left;
	int iHeight = SpriteBounds.bottom - SpriteBounds.top;
	
	CVector3 vecPos = pRenderer->GetSpriteManager().GetPositionScaled(m_uiWaterIconID);
			
	SpriteBounds.left   =	static_cast<LONG>(vecPos.x);
	SpriteBounds.right  =	static_cast<LONG>(vecPos.x + iWidth);
	SpriteBounds.top    =	static_cast<LONG>(vecPos.y);
	SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + iHeight);

	if(MouseCords.X >= SpriteBounds.left &&
	   MouseCords.X <= SpriteBounds.right &&
	   MouseCords.Y >= SpriteBounds.top &&
	   MouseCords.Y <= SpriteBounds.bottom)
	{
		m_bSpriteSelected = true;
		if(m_bLeftClick)
		{
			vecPos = pRenderer->GetSpriteManager().GetPosition(m_uiWaterIconID);			
			pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiIconSelectionID);

			m_eCurrentTileType = TILETYPE_WATER;
			m_bPlacingWaypoints = false;
		}
	}

	//Selection of Path tile
	SpriteBounds = pRenderer->GetSpriteManager().GetRect(m_uiPathIconID);
	iWidth = SpriteBounds.right - SpriteBounds.left;
	iHeight = SpriteBounds.bottom - SpriteBounds.top;
		
	vecPos = pRenderer->GetSpriteManager().GetPositionScaled(m_uiPathIconID);
		
	SpriteBounds.left   =	static_cast<LONG>(vecPos.x);
	SpriteBounds.right  =	static_cast<LONG>(vecPos.x + iWidth);
	SpriteBounds.top    =	static_cast<LONG>(vecPos.y);
	SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + iHeight);

	if(MouseCords.X >= SpriteBounds.left &&
		MouseCords.X <= SpriteBounds.right &&
		MouseCords.Y >= SpriteBounds.top &&
		MouseCords.Y <= SpriteBounds.bottom)
	{
		m_bSpriteSelected = true;
		if(m_bLeftClick)
		{		
			vecPos = pRenderer->GetSpriteManager().GetPosition(m_uiPathIconID);			
			pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiIconSelectionID);

			m_eCurrentTileType = TILETYPE_PATH;
			m_bPlacingWaypoints = false;
		}
	}

	//Selection of Raised tile
	SpriteBounds = pRenderer->GetSpriteManager().GetRect(m_uiRaisedIconID);
	iWidth = SpriteBounds.right - SpriteBounds.left;
	iHeight = SpriteBounds.bottom - SpriteBounds.top;
		
	vecPos = pRenderer->GetSpriteManager().GetPositionScaled(m_uiRaisedIconID);
		
	SpriteBounds.left   =	static_cast<LONG>(vecPos.x);
	SpriteBounds.right  =	static_cast<LONG>(vecPos.x + iWidth);
	SpriteBounds.top    =	static_cast<LONG>(vecPos.y);
	SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + iHeight);

	if(MouseCords.X >= SpriteBounds.left &&
		MouseCords.X <= SpriteBounds.right &&
		MouseCords.Y >= SpriteBounds.top &&
		MouseCords.Y <= SpriteBounds.bottom)
	{
		m_bSpriteSelected = true;
		if(m_bLeftClick)
		{		
			vecPos = pRenderer->GetSpriteManager().GetPosition(m_uiRaisedIconID);			
			pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiIconSelectionID);

			m_eCurrentTileType = TILETYPE_RAISED;
			m_bPlacingWaypoints = false;
		}
	}

	//Selection of waypoints
	SpriteBounds = pRenderer->GetSpriteManager().GetRect(m_uiWaypointIconID);
	iWidth = SpriteBounds.right - SpriteBounds.left;
	iHeight = SpriteBounds.bottom - SpriteBounds.top;
		
	vecPos = pRenderer->GetSpriteManager().GetPositionScaled(m_uiWaypointIconID);
		
	SpriteBounds.left   =	static_cast<LONG>(vecPos.x);
	SpriteBounds.right  =	static_cast<LONG>(vecPos.x + iWidth);
	SpriteBounds.top    =	static_cast<LONG>(vecPos.y);
	SpriteBounds.bottom =	static_cast<LONG>(vecPos.y + iHeight);


	if(MouseCords.X >= SpriteBounds.left &&
		MouseCords.X <= SpriteBounds.right &&
		MouseCords.Y >= SpriteBounds.top &&
		MouseCords.Y <= SpriteBounds.bottom)
	{
		m_bSpriteSelected = true;
		if(m_bLeftClick)
		{	
			vecPos = pRenderer->GetSpriteManager().GetPosition(m_uiWaypointIconID);
			pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiIconSelectionID);
			m_bPlacingWaypoints = true;
		}
	}

	//Save selected
	SpriteBounds = pRenderer->GetSpriteManager().GetRect(m_uiFileOptions);
	CVector3 SpritePos;
	iWidth = SpriteBounds.right - SpriteBounds.left;
	iHeight = SpriteBounds.bottom - SpriteBounds.top;

	iWidth = static_cast<unsigned int>((kuiClientWidth / 1280.0f) * iWidth);
	iHeight =  static_cast<unsigned int>((kuiClientHeight / 1024.0f) * iHeight);

	vecPos = pRenderer->GetSpriteManager().GetPosition(m_uiFileOptions);

	SpritePos.x =  (kuiClientWidth / 1280.0f) * vecPos.x;
	SpritePos.y =  (kuiClientHeight / 1024.0f) * vecPos.y;
	
	SpriteBounds.left   =	static_cast<LONG>(SpritePos.x);
	SpriteBounds.right  =	static_cast<LONG>(SpritePos.x + iWidth / 4);
	SpriteBounds.top    =	static_cast<LONG>(SpritePos.y );
	SpriteBounds.bottom =	static_cast<LONG>(SpritePos.y  + iHeight / 4);

	if(MouseCords.X >= SpriteBounds.left  &&
	   MouseCords.X <= SpriteBounds.right &&
	   MouseCords.Y >= SpriteBounds.top   &&
	   MouseCords.Y <= SpriteBounds.bottom)
	{
		if(m_bLeftClick)
		{			
			m_bSpriteSelected = true;
			m_bSave = true;
			
			DialogBox(CApplication::GetInstance().GetInstanceHandle(),
						  MAKEINTRESOURCE(IDD_DIALOG2),
						  hWnd,
						  SaveProc);
			
			if(m_wcFileName)
			{
				TakeScreenShot();	
			}
		}
	}
	
	//Load selected
	SpriteBounds.left   =	static_cast<LONG>(SpritePos.x + iWidth / 4);
	SpriteBounds.right  =	static_cast<LONG>(SpritePos.x + iWidth / 2);
	SpriteBounds.top    =	static_cast<LONG>(SpritePos.y );
	SpriteBounds.bottom =	static_cast<LONG>(SpritePos.y + iHeight / 4);
	
	if(MouseCords.X >= SpriteBounds.left  &&
	   MouseCords.X <= SpriteBounds.right &&
	   MouseCords.Y >= SpriteBounds.top   &&
	   MouseCords.Y <= SpriteBounds.bottom)
	{
		if(m_bLeftClick)
		{			
			m_bSpriteSelected = true;
			m_bLoad = true;

			DialogBox(CApplication::GetInstance().GetInstanceHandle(),
					  MAKEINTRESOURCE(IDD_DIALOG3),
					  hWnd,
					  LoadProc);		
		}
	}

	SpriteBounds.left   =	static_cast<LONG>(SpritePos.x + iWidth / 2);
	SpriteBounds.right  =	static_cast<LONG>(SpritePos.x + iWidth / 2 + iWidth / 4);
	SpriteBounds.top    =	static_cast<LONG>(SpritePos.y);
	SpriteBounds.bottom =	static_cast<LONG>(SpritePos.y + iHeight / 4);

	//New map selected
	if(MouseCords.X >= SpriteBounds.left  &&
	   MouseCords.X <= SpriteBounds.right &&
	   MouseCords.Y >= SpriteBounds.top   &&
	   MouseCords.Y <= SpriteBounds.bottom)
	{
		m_bSpriteSelected = true;
		if(m_bLeftClick)
		{
			int iConfirm = MessageBox(hWnd, L"Are you sure you wish to create a new map?",
											L"Confirm Selection", MB_OKCANCEL);
			if(iConfirm == 1)
			{
				InitialiseBlankGrid();
			}
		}
	}

	SpriteBounds.left   =	static_cast<LONG>(SpritePos.x + iWidth / 2 + iWidth / 4);
	SpriteBounds.right  =	static_cast<LONG>(SpritePos.x + iWidth);
	SpriteBounds.top    =	static_cast<LONG>(SpritePos.y);
	SpriteBounds.bottom =	static_cast<LONG>(SpritePos.y + iHeight / 4);
	
	//Return to main menu
	if(MouseCords.X >= SpriteBounds.left  &&
	   MouseCords.X <= SpriteBounds.right &&
	   MouseCords.Y >= SpriteBounds.top   &&
	   MouseCords.Y <= SpriteBounds.bottom)
	{
		m_bSpriteSelected = true;
		if(m_bLeftClick)
		{
			int iConfirm = MessageBox(hWnd, L"Are you sure you wish to return to main menu? Unsaved progress will lost!",
											L"Confirm Exit", MB_OKCANCEL);
			if(iConfirm == 1)
			{
				CApplication::GetInstance().GetGameWindow().SetMainScene(SCENE_MAINMENU);
			}
		}
	}

}




/**
*
* This function detects collisions between the mouse and objects in the scene.
*
* @author Daniel Langsford
* @param _fDeltaTick: Time since last process call.
* @returns void
*
*/
void
CMapEditor::ObjectSelect(float _fDeltaTick)
{
	if (!m_pTerrain->GetGridWidth() || !m_pTerrain->GetGridHeight())
	{
		return;
	}

	CRayCast rayCast;
	rayCast.CastRay(m_pViewport, !m_bControllerActive);
	D3DXVECTOR3 vecNear;
	D3DXVECTOR3 vecFar;
	rayCast.Get3DPoints(vecNear, vecFar);

	if (MathUtility::IsLineGroundIntersecting(vecNear, vecFar, m_pTerrain->GetTowerHeightOffset()))
	{
		D3DXVECTOR3 vecIntersect;
		unsigned int uiX = 0;
		unsigned int uiY = 0;
		MathUtility::GetLineGroundIntersect(vecNear, vecFar, vecIntersect, 0.0f);
		const CTile& krTile = m_pTerrain->GetTile(vecIntersect, &uiX, &uiY);
		
		CTile& rTile = m_pTerrain->GetTile(uiX, uiY, true);
		
		*m_SelectedTile = rTile;
		m_uiSelectedTileX = uiX;
		m_uiSelectedTileY = uiY;
		
		//Tile Placement.
		if(m_bPlacingWaypoints == false)
		{
			ETileType TileType = rTile.GetTileType();

			switch(TileType)
			{
			case TILETYPE_BLANK:
				{
					m_bPlacable = true;
				
					if(m_bLeftClick)
					{
						rTile.SetTileType(m_eCurrentTileType);
					}
					break;
				}
			default:
				{
					m_bPlacable = false;
					if(m_bRightClick)
					{
						rTile.SetTileType(TILETYPE_BLANK);
					}
					break;
				}
			}
		}

		//Waypoint placement.
		else
		{		
			if(m_bLeftClick)
			{
				m_pTerrain->GetWaypointManager().WaypointCreation(WAYCRE_END, vecIntersect);
				m_uiNumWaypoints++;
				m_bLeftClick = false;
			}	
			if(m_bRightClick)
			{
				m_pTerrain->GetWaypointManager().WaypointCreation(WAYCRE_DELETE, vecIntersect);
				m_uiNumWaypoints--;
				m_bRightClick = false;
			}
			if(m_bClicked && m_fClickTimer >= 0.3f)
			{
				m_pTerrain->GetWaypointManager().WaypointCreation(WAYCRE_MOVE, vecIntersect);
			}
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
CMapEditor::HandleDMouseInput(EDInputMouse _eDMouse, bool _bDown, long _lValue)
{
	switch (_eDMouse)
	{
	case DMOUSE_LEFTCLICK:
		{
			m_bLeftClick =  _bDown;	
			m_bClicked = _bDown;	
			break;
		}
	case DMOUSE_RIGHTCLICK:
		{
			m_bRightClick = _bDown;	
			break;
		}
	}
}

/**
*
* This function handles input from the keyboard
*
* @author 
* @param _iButton:
* @param _Down:
* @return 
*
*/

void
CMapEditor::HandleDKeyboardInput(EDInputKeyboard _eDKebyoard, bool _bDown)
{
	switch (_eDKebyoard)
	{
	case DKEYBOARD_1:
		{
			CD3DRenderer* pRenderer = CApplication::GetInstance().GetGameWindow().GetRenderer();
			CVector3 vecPosition = pRenderer->GetSpriteManager().GetPosition(m_uiWaterIconID);
			pRenderer->GetSpriteManager().SetPosition(vecPosition, m_uiIconSelectionID);

			m_bPlacingWaypoints = false;
			m_eCurrentTileType = TILETYPE_WATER;
			break;
		}

	case DKEYBOARD_2:
		{
			CD3DRenderer* pRenderer = CApplication::GetInstance().GetGameWindow().GetRenderer();
			CVector3 vecPosition = pRenderer->GetSpriteManager().GetPosition(m_uiPathIconID);
			pRenderer->GetSpriteManager().SetPosition(vecPosition, m_uiIconSelectionID);

			m_bPlacingWaypoints = false;
			m_eCurrentTileType = TILETYPE_PATH;
			break;
		}

	case DKEYBOARD_3:
		{
			CD3DRenderer* pRenderer = CApplication::GetInstance().GetGameWindow().GetRenderer();
			CVector3 vecPosition = pRenderer->GetSpriteManager().GetPosition(m_uiRaisedIconID);
			pRenderer->GetSpriteManager().SetPosition(vecPosition, m_uiIconSelectionID);

			m_bPlacingWaypoints = false;
			m_eCurrentTileType = TILETYPE_RAISED;
			break;
		}

	case DKEYBOARD_4:
		{
			CD3DRenderer* pRenderer = CApplication::GetInstance().GetGameWindow().GetRenderer();
			CVector3 vecPosition = pRenderer->GetSpriteManager().GetPosition(m_uiWaypointIconID);
			pRenderer->GetSpriteManager().SetPosition(vecPosition, m_uiIconSelectionID);

			m_bPlacingWaypoints = true;
			break;
		}
	case DKEYBOARD_ENTER:
		{
			
		}
		break;
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
CMapEditor::HandleXButtonInput(EXInputButton _eXButton, bool _bDown)
{
	
}

/**
*
* Handles the xinput triggers
*
* @author Jamie Smith
* @param _eXTrigger which button
* @param _fValue how much the trigger is pulled
*
*/ 
void
CMapEditor::HandleXTriggerInput(EXInputTrigger _eXTrigger, float _fValue)
{

}

/**
*
* sets if the controller is active or not
*
* @author Jamie Smith
* @param _bActive if the controller is active or not
*
*/ 
void
CMapEditor::SetControllerActive(bool _bActive)
{
	
}


/**
*
* This function deletes any free store memory allocations.
*
* @author Daniel Langsford
* @param 
* @return 
*
*/
void
CMapEditor::Deinitialise()
{

	CD3DRenderer* pRenderer = CApplication::GetInstance().GetGameWindow().GetRenderer();
	pRenderer->GetSpriteManager().EraseAll();

	FW_DELETE(m_SelectedTile);
	FW_DELETE(m_pTerrain);
	FW_DELETE(m_pLogManager);
	FW_DELETE(m_pViewport);
}

/** 
*
* Calls save on the terrain
* 
* @author Jamie.Smith  
* @return void 
*
*/
void
CMapEditor::Save(const char* _kcFileName)
{
	m_pTerrain->GetWaypointManager().PostCreate();
	m_pTerrain->SaveMap(_kcFileName);
}

/** 
*
* Calls Load on the terrain
* 
* @author Jamie.Smith  
* @return bool
*
*/
bool
CMapEditor::Load(const char* _kcFileName)
{
	return(m_pTerrain->LoadMap(_kcFileName));
}

/** 
*
* Initialises a blank grid
* 
* @author Jamie.Smith  
* @return void 
*
*/
void
CMapEditor::InitialiseBlankGrid()
{
	s_uiGridWidth = 0;
	s_uiGridHeight = 0;

	m_uiSelectedTileX = 0;
	m_uiSelectedTileY = 0;

	HWND hWnd = CApplication::GetInstance().GetGameWindow().GetWindowHandle();
	
	while(s_uiGridWidth < 5 && s_uiGridHeight < 5 ||
		  s_uiGridWidth == 0 || s_uiGridHeight == 0)
	{
		DialogBox(CApplication::GetInstance().GetInstanceHandle(),
								  MAKEINTRESOURCE(IDD_DIALOG4),
								  hWnd,
								  InitialiseProc);

		if(s_uiGridWidth <= 5 && s_uiGridHeight <= 5)
		{
			MessageBox(NULL, L"Either Width or Height must be greater than five.", L"Error", MB_OK);
		}
		if(s_uiGridWidth <= 0 || s_uiGridHeight <= 0)
		{
			MessageBox(NULL, L"Width and Height must be greater than zero.", L"Error", MB_OK);
		}
	} 

	assert(s_uiGridWidth);
	assert(s_uiGridHeight);

	m_pTerrain->InitialiseBlankTerrain(s_uiGridWidth, s_uiGridHeight);
	m_uiSelectedTileX = 0;
	m_uiSelectedTileY = 0;	
}

/** 
*
* Gets if the player wants to save 
* 
* @author Jamie.Smith  
* @return bool 
*
*/
bool
CMapEditor::GetSave()
{
	return(m_bSave);
}

/** 
*
* Gets if the player wants to load
* 
* @author Jamie.Smith  
* @return bool 
*
*/
bool
CMapEditor::GetLoad()
{
	return(m_bLoad);
}

/**
*
* Takes a screen shot 
*
* @author Jamie Smith
*
*/ 
void
CMapEditor::TakeScreenShot()
{
	m_fScreenShotCameraHeight = 5.0f;
	unsigned int uiMaxSize = static_cast<unsigned int>((s_uiGridWidth > s_uiGridHeight ? s_uiGridWidth : s_uiGridHeight) * m_pTerrain->GetTileSpacing());

	m_pScreenShotViewPort = new CViewport();
	m_pScreenShotViewPort->Initialise(0, 0,
									  uiMaxSize, uiMaxSize,
									  1,
									  CApplication::GetInstance().GetGameWindow().GetRenderer());

	m_pScreenShotViewPort->CreateCamera(MathUtility::PI, 0.1f, 100.0f);
	m_pScreenShotViewPort->GetLastCreatedCamera()->GetWorldMatrix().SetPositionY(10.0f);
	m_pScreenShotViewPort->GetLastCreatedCamera()->RotateX(MathUtility::PI * -0.5f);
	m_pScreenShotViewPort->SetActiveCamera(m_pScreenShotViewPort->GetLastCreatedCamera());
	m_pScreenShotViewPort->GetActiveCamera()->SetMode(CAMERAMODE_ORTHOGONAL);

	m_bTakeScreenShot = true;
}

/**
*
* Initialises the stuff
*
* @author DANIEL LANGSFORD
*
*/ 
BOOL CALLBACK
CMapEditor::InitialiseProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	switch(_msg)
	{

	case WM_INITDIALOG:
		{
			CApplication::GetInstance().GetGameWindow().ShowCursor();
			CApplication::GetInstance().GetGameWindow().SetCursorStateLocked(true);
		}
	case WM_COMMAND:
		{
			switch (LOWORD(_wparam))
			{
			case IDC_CONTINUE:
				{
					//Get width
					HWND hEdit = GetDlgItem(_hwnd, IDC_EDIT1);
					wchar_t wcMsgTxt[20];
					GetWindowText(hEdit, wcMsgTxt, 19);
					s_uiGridWidth = static_cast<unsigned int>(_wtoi(wcMsgTxt));
					
					//Get height
					hEdit = GetDlgItem(_hwnd, IDC_EDIT2);
					GetWindowText(hEdit, wcMsgTxt, 19);
					s_uiGridHeight = static_cast<unsigned int>(_wtoi(wcMsgTxt));

					EndDialog(_hwnd, 0);

					CApplication::GetInstance().GetGameWindow().SetCursorStateLocked(false);

					break;
				}
			}
			break;
		}
	case WM_CLOSE:
		{
			s_uiGridWidth = 6;
			s_uiGridHeight = 6;

			s_bQuitting = true;

			EndDialog(_hwnd, 0);
					
			break;
		}
	default: break;

	}
	return(FALSE);
}

/**
*
* This function does the saving dialog box functionality
*
* @author Jamie Smith
* @param _hwnd The window handle
* @param _msg The window message
* @param _wparam The window WPARAM
* @param _lparam The window LPARAM
* @Return BOOL CALLBACK
*
*/
BOOL CALLBACK
CMapEditor::SaveProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	switch(_msg)
	{
	case WM_INITDIALOG:
		{
			if(CMapEditor::m_uiNumWaypoints < 2)
			{
				MessageBox(_hwnd, L"There must be 2 or more way points set", L"Error!", 0);
				EndDialog(_hwnd, 0);
			}			
		}
	case WM_COMMAND:
		{
			switch (LOWORD(_wparam))
			{
			case IDC_SAVE:
				{					
					s_pParser = new CINIParser();
			
					//------Set new Player gold.------------
					HWND hEdit = GetDlgItem(_hwnd, IDC_DIAL2EDIT1);
					wchar_t wcMsgTxt[20];
					GetWindowText(hEdit, wcMsgTxt, 19);

					char* kcGoldAmount = new char[20];

					size_t tempGold = 0;
					wcstombs_s(&tempGold, kcGoldAmount, (size_t)20, wcMsgTxt, (size_t)20);

					if(!(CMapEditor::CheckNumbers(kcGoldAmount)))
					{
						MessageBox(_hwnd, L"Invalid Entry, Gold must be a numerical value.", L"Error!", 0);
						break;
					}

					delete kcGoldAmount;

					int iGold = static_cast<int>(_wtoi(wcMsgTxt));

					if(iGold <= 20)
					{
						iGold = 20;
					}

					char GoldAmmount[20];
					_itoa_s(iGold, GoldAmmount, 20, 10);

					//---------------------------------------------------

					//-------Set new player lives.---------------
					hEdit = GetDlgItem(_hwnd, IDC_DIAL2EDIT2);
					GetWindowText(hEdit, wcMsgTxt, 19);

					char* kcLivesAmount = new char[20];

					size_t tempLives = 0;
					wcstombs_s(&tempLives, kcLivesAmount, (size_t)20, wcMsgTxt, (size_t)20);

					if(!(CMapEditor::CheckNumbers(kcLivesAmount)))
					{
						MessageBox(_hwnd, L"Invalid Entry, Lives must be a numerical value.", L"Error!", 0);
						break;
					}

					delete kcLivesAmount;

					int iLives = static_cast<int>(_wtoi(wcMsgTxt));

					if(iLives <= 0)
					{
						iLives = 1;
					}

					char LivesAmmount[20];
					_itoa_s(iLives, LivesAmmount, 20, 10);

					//----------------------------------------------------

					//-------Set the amount of waves---------------
					hEdit = GetDlgItem(_hwnd, IDC_DIAL2EDIT3);
					GetWindowText(hEdit, wcMsgTxt, 19);

					char* kcWaveAmount = new char[20];

					size_t tempWaves = 0;
					wcstombs_s(&tempWaves, kcWaveAmount, (size_t)20, wcMsgTxt, (size_t)20);

					if(!(CMapEditor::CheckNumbers(kcWaveAmount)))
					{
						MessageBox(_hwnd, L"Invalid Entry, Wave ammount must be a numerical value.", L"Error!", 0);
						break;
					}

					delete kcWaveAmount;

					int iWaveLength = static_cast<int>(_wtoi(wcMsgTxt));

					if(iWaveLength <= 0)
					{
						iWaveLength = 1;
					}

					char WaveNumber[20];
					_itoa_s(iWaveLength, WaveNumber, 20, 10);

					//----------------------------------------------------------

					//--------Save The Map----------------		

					OPENFILENAME File;
					ZeroMemory(&File, sizeof(OPENFILENAME));

					wchar_t wcFilePath[256];
					wcFilePath[0] = NULL;

					File.lStructSize = sizeof(OPENFILENAME);
					File.hwndOwner = _hwnd;
					File.lpstrFilter = L".Map";
					File.nFilterIndex = 1;
					File.lpstrFile = wcFilePath;
					File.nMaxFile = 256;
					File.lpstrDefExt = L"map";
					File.Flags = OFN_CREATEPROMPT | OFN_PATHMUSTEXIST |
								OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | 
								OFN_NOCHANGEDIR;
					File.lpstrInitialDir = L"Maps/";

					GetSaveFileName(&File);

					// Measure length of string.
					unsigned int uiStringLength = 0;
					while (File.lpstrFile[uiStringLength++]);					

					char* kcFileName = new char[uiStringLength];

					size_t temp = 0;
					wcstombs_s(&temp, kcFileName, uiStringLength, File.lpstrFile, uiStringLength);

					std::string strFileName = kcFileName;
					std::string strPicDest;

					remove(kcFileName);				
					
					size_t found;
					size_t End;
					size_t Length;

					found = strFileName.find_last_of("/\\");
					End = strFileName.find(".");

					Length = End - found;

					strFileName = (strFileName.substr(found+1, Length));

					delete[] m_wcFileName;
					m_wcFileName = 0;
				
					if(strFileName.length() != 0)
					{
						strPicDest = "Maps/";
						strPicDest.append(strFileName);
					
						m_wcFileName = new wchar_t[uiStringLength];
						mbstowcs_s(&temp, m_wcFileName, uiStringLength, strPicDest.c_str(), sizeof(wchar_t) * uiStringLength);
						
						strFileName.append("png");

						s_pParser->LoadINIFile(kcFileName);			
						s_pParser->AddValue("Meta Data", "MapPreviewFile", strFileName.c_str());
						s_pParser->AddValue("PlayerStats", "Gold", GoldAmmount);
						s_pParser->AddValue("PlayerStats", "Lives", LivesAmmount);
						s_pParser->AddValue("WaveNumber", "Wave", WaveNumber);
						s_pParser->SaveINIFile(kcFileName);

						CMapEditor::SaveEnemies(kcFileName, iWaveLength);

						CGameWindow& rWindow = dynamic_cast<CGameWindow&>(CApplication::GetInstance().GetGameWindow());
						dynamic_cast<CMapEditor*>(&rWindow.GetCurrentMainScene())->Save(kcFileName);						
					}

					EndDialog(_hwnd, 0);					
					
					FW_DELETE(s_pParser);
					delete[] kcFileName;
					kcFileName = 0;

					break;
				}
				break;			
			case IDCANCEL:
				{
					EndDialog(_hwnd, 0);
					return(false);
					break;
				}
			}
			break;
		}	
		break;

	case WM_CLOSE:
		{
			EndDialog(_hwnd, 0);
			break;
		}
	}


	return(FALSE);
}



/**
*
* This function does the loading dialog box functionality
*
* @author Jamie Smith
* @param _hwnd The window handle
* @param _msg The window message
* @param _wparam The window WPARAM
* @param _lparam The window LPARAM
* @Return BOOL CALLBACK
*
*/
BOOL CALLBACK
CMapEditor::LoadProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	switch(_msg)
	{
	case WM_INITDIALOG:
		{		
			s_pParser = new CINIParser();
			
			//--------Load The Map----------------
			OPENFILENAME File;
			ZeroMemory(&File, sizeof(OPENFILENAME));

			wchar_t wcFilePath[256];
			wcFilePath[0] = NULL;

			File.lStructSize = sizeof(OPENFILENAME);
			File.hwndOwner = _hwnd;
			File.lpstrFilter = L".Map";
			File.nFilterIndex = 1;
			File.lpstrFile = wcFilePath;
			File.nMaxFile = 256;
			File.lpstrDefExt = L"map";
			File.Flags = OFN_CREATEPROMPT | OFN_PATHMUSTEXIST |
						 OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY;
			File.lpstrInitialDir = L"Maps/";

			GetOpenFileName(&File);

			File.lpstrFilter;

			char* kcFileName = new char[256];

			size_t temp = 0;
			wcstombs_s(&temp, kcFileName, (size_t)256, File.lpstrFile, (size_t)256);


			CGameWindow& rWindow = dynamic_cast<CGameWindow&>(CApplication::GetInstance().GetGameWindow());
			
			//----------------------------------------
			std::string Temp = kcFileName;

			//Check if it is a valid map.
			if(Temp.length() != 0)
			{
				if(dynamic_cast<CMapEditor*>(&rWindow.GetCurrentMainScene())->Load(kcFileName))
				{
					s_pParser->LoadINIFile(kcFileName);
					s_pParser->GetValue("Terrain", "Height", s_uiGridHeight);
					s_pParser->GetValue("Terrain", "Width", s_uiGridWidth);
					s_pParser->SaveINIFile(kcFileName);
				}
				else
				{
					MessageBox(_hwnd, L"Map File Corrupt.", L"Error!", 0);	
					dynamic_cast<CMapEditor*>(&rWindow.GetCurrentMainScene())->InitialiseBlankGrid();
				}				
			}

			delete s_pParser;
			s_pParser = 0;

			delete kcFileName;
			kcFileName = 0;	
		
			EndDialog(_hwnd, 0);			
		}
		break;			
			

	case WM_CLOSE:
		{
			EndDialog(_hwnd, 0);
			break;
		}
	}


	return(FALSE);
}

/**
*
* checks if the input from the save is only numbers 
*
* @author Jamie Smith
* @param _kcInput the player input
*
*/ 
bool
CMapEditor::CheckNumbers(const char* _kcInput)
{
	int iLength = static_cast<int>(strlen(_kcInput));

	for(int i =0; i < iLength; i++)
	{
		if(_kcInput[i] < 48 || _kcInput[i] > 57)
		{
			return false;
		}
	}

	return(true);
}

void
CMapEditor::NextTile()
{
	bool bWaterSelect = false;
	CD3DRenderer* pRenderer = CApplication::GetInstance().GetGameWindow().GetRenderer();
	CVector3 vecPos;

	if(m_bPlacingWaypoints)
	{
		m_bPlacingWaypoints = false;
		m_eCurrentTileType = TILETYPE_WATER;

		vecPos = pRenderer->GetSpriteManager().GetPosition(m_uiWaterIconID);
		pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiIconSelectionID);	
		bWaterSelect = true;
	}

	if(bWaterSelect == false)
	{
		switch(m_eCurrentTileType)
		{
		case TILETYPE_WATER:
			{
				m_eCurrentTileType = TILETYPE_PATH;
				m_bPlacingWaypoints = false;

				vecPos = pRenderer->GetSpriteManager().GetPosition(m_uiPathIconID);
				pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiIconSelectionID);			

				break;
			}
		case TILETYPE_PATH:
			{
				m_eCurrentTileType = TILETYPE_RAISED;
				m_bPlacingWaypoints = false;

				vecPos = pRenderer->GetSpriteManager().GetPosition(m_uiRaisedIconID);
				pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiIconSelectionID);			

				break;
			}
		case TILETYPE_RAISED:
			{
				m_bPlacingWaypoints = true;

				vecPos = pRenderer->GetSpriteManager().GetPosition(m_uiWaypointIconID);
				pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiIconSelectionID);			

				break;
			}
		}
	}	
}

void
CMapEditor::LastTile()
{
	bool bWaterSelect = false;
	CD3DRenderer* pRenderer = CApplication::GetInstance().GetGameWindow().GetRenderer();
	CVector3 vecPos;

	if(m_bPlacingWaypoints)
	{
		m_bPlacingWaypoints = false;
		m_eCurrentTileType = TILETYPE_RAISED;

		vecPos = pRenderer->GetSpriteManager().GetPosition(m_uiRaisedIconID);
		pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiIconSelectionID);	
		bWaterSelect = true;
	}

	if(bWaterSelect == false)
	{
		switch(m_eCurrentTileType)
		{
		case TILETYPE_WATER:
			{
				m_bPlacingWaypoints = true;

				vecPos = pRenderer->GetSpriteManager().GetPosition(m_uiWaypointIconID);
				pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiIconSelectionID);						

				break;
			}
		case TILETYPE_PATH:
			{
				m_eCurrentTileType = TILETYPE_WATER;
				m_bPlacingWaypoints = false;

				vecPos = pRenderer->GetSpriteManager().GetPosition(m_uiWaterIconID);
				pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiIconSelectionID);			

				break;
			}
		case TILETYPE_RAISED:
			{
				m_eCurrentTileType = TILETYPE_PATH;
				m_bPlacingWaypoints = false;

				vecPos = pRenderer->GetSpriteManager().GetPosition(m_uiPathIconID);

				pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiIconSelectionID);			
				break;
			}
		}
	}
}

/**
*
* saves the enemies types spawn delay and number randomly between set numbers
*
* @author Jamie Smith
* @param _kcpFileName the file diestination
* @Param _uiNumOfWaves the number of waves
*
*/
void
CMapEditor::SaveEnemies(const char* _kcpFileName, unsigned int _uiNumOfWaves)
{
	s_pParser->LoadINIFile(_kcpFileName);			
	
	for(unsigned int i = 0; i < _uiNumOfWaves; ++i)
	{
		char Buffer[256];

		sprintf_s(Buffer, 256, "%s %i","Wave", i);
		std::string strBuffer = Buffer;		

		unsigned int uiEnemyType = MathUtility::RandomNumber(0, 2);
		switch(uiEnemyType)
		{
		case 0:
			{
				s_pParser->AddValue(strBuffer.c_str(), "EnemyType", "Fast Enemy");
				break;
			}
		case 1:
			{
				s_pParser->AddValue(strBuffer.c_str(), "EnemyType", "Medium Enemy");
				break;
			}
		case 2:
			{
				s_pParser->AddValue(strBuffer.c_str(), "EnemyType", "Heavy Enemy");
				break;
			}
		}		

		unsigned int uiNumberOfEnimies = MathUtility::RandomNumber(5, 20);
		char NumberOFEnemies[20];
		_itoa_s(uiNumberOfEnimies, NumberOFEnemies, 20, 10);
		s_pParser->AddValue(strBuffer.c_str(), "NumberOfEnemies ", NumberOFEnemies);

		float fSpawnDelay = MathUtility::RandomNumber(0.8f, 1.5f);
		char* SpawnDelay = new char[30];
		sprintf_s(SpawnDelay, 30, "%f", fSpawnDelay);
		s_pParser->AddValue(strBuffer.c_str(), "SpawnDelay  ", SpawnDelay);

		delete[] SpawnDelay;
		SpawnDelay = 0;
	}

	char BossBuffer[256];

	sprintf_s(BossBuffer, 256, "%s %i","Wave", _uiNumOfWaves);
	std::string strBossBuffer = BossBuffer;

	s_pParser->AddValue(strBossBuffer.c_str(), "EnemyType", "Boss Enemy");
	s_pParser->AddValue(strBossBuffer.c_str(), "NumberOfEnemies", "1");
	s_pParser->AddValue(strBossBuffer.c_str(), "SpawnDelay", "1");

	
	s_pParser->SaveINIFile(_kcpFileName);
}
