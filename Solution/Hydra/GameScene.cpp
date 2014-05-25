//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
// 
//  (c) 2011 Media Design School
//
//  File Name :   GameScene.cpp
//
//  Author    :   Team Blue
//  Mail      :   
//


// Library Includes


// Local Includes
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
#include "EnemySpawner.h"
#include "mouse.h"
#include "player.h"

#include "utility.h"
#include "raycast.h"
#include "XInputcontroller.h"
#include "INIParser.h"
#include "AnimatedObject.h"
#include "GameCamera.h"
#include "Terrain.h"
#include "RadialMenu.h"
#include "Hud.h"
#include "WaveManager.h"
#include "HudDataManager.h"
#include "GameSceneData.h"
#include "LightManager.h"
#include "SpriteManager.h"
#include "ParticleManager.h"
#include "ParticleInterface.h"
#include "Wave.h"
#include "Tile.h"


// This Include
#include "GameScene.h"


// Static Variables
unsigned int
CGameScene::m_uiSelectedTileX(0);

unsigned int
CGameScene::m_uiSelectedTileY(0);


const CTile*
CGameScene::m_pSelectedTile(0);

// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* GameScene class constructor
*
* @author Team Blue
*
*---------------------------------------------------------------------------------------------------------------------------*/

CGameScene::CGameScene()
: m_uiLightDirectional(0)
, m_pTerrain(0)
, m_pPlayer(0)
, m_pRadialMenu(0)
, m_pHud(0)
, m_uiPointerId(0)
, m_PlaceTimer(0)
, m_pGameData(0)
, m_uiVictoryScreenId(0)
, m_uiPauseId(0)
, m_fAnalogLeftX(0)
, m_fAnalogLeftY(0)
, m_bCollision(true)
, m_bUseMousePos(true)
, m_bController(false)
, m_bShowDebugInfo(false)
, m_bLeftClick(false)
, m_bRightClick(false)
, m_bRadMenu360(false)
, m_bPaused(false)
, m_bGameOver(false)
, m_bSkipLeftClick(false)
{
	CEventTarget::ClearAllEvents();
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* GameScene class deconstructor
*
* @author Team Blue
*
*---------------------------------------------------------------------------------------------------------------------------*/

CGameScene::~CGameScene()
{
	Deinitialise();
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* This function initialises the scene
*
* @author Team Blue
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CGameScene::InitialiseScene(CD3DRenderer* _pRenderer, void* _pSceneData)
{
	LOG_FATALERROR(_pSceneData == 0, "The game scene data was not recieved.");	

	CGameSceneData* pGameSceneData = reinterpret_cast<CGameSceneData*>(_pSceneData);
	
	m_pGameData = pGameSceneData;

	LOG_FATALERROR(strlen(pGameSceneData->GetMapFile()) == 0, "The game scene data map file is invalid.");
	LOG_FATALERROR(pGameSceneData->GetPlayerStartGold() == 0, "The game scene data start gold is invalid.");
	LOG_FATALERROR(pGameSceneData->GetPlayerStartLives() == 0, "The game scene data start lives is invalid.");

	m_bShowDebugInfo = true;

	CWindow& rGameWindow = CApplication::GetInstance().GetGameWindow();
	const unsigned int kuiWindowWidth = rGameWindow.GetClientWidth();
	const unsigned int kuiWindowHeight = rGameWindow.GetClientHeight();

	InitialisePlayerInputTarget();
	InitialiseXInputTarget();
	IntiialisePlayer(pGameSceneData->GetPlayerStartGold(), pGameSceneData->GetPlayerStartLives());
	InitialiseTerrain(_pRenderer, pGameSceneData->GetMapFile());
	InitialiseWaveManager(_pRenderer, m_pTerrain, pGameSceneData);
	InitialiseHud(_pRenderer, kuiWindowWidth, kuiWindowHeight, pGameSceneData->GetMapFile());	// Must be done after InitialiseTerrain(), InitialisePlayer(), and InitialiseWaveManager(), but before InitialiseRadialMenu().
	InitialiseRadialMenu(_pRenderer, kuiWindowWidth, kuiWindowHeight - static_cast<unsigned int>(m_pHud->GetUsedScreenHeight()));	// Must be done after InitialiseHud().

	// Initialise singleton data manager.
	CHudDataManager* pDataManager = CHudDataManager::GetInstance();
	if (pDataManager)
		pDataManager->Initialise(_pRenderer->GetTextureManager());

	//Initialise sprites
	InitialiseSprites();
	
	int iWidth = CApplication::GetInstance().GetGameWindow().GetClientWidth();
	int iHeight = CApplication::GetInstance().GetGameWindow().GetClientHeight();

	m_MouseCoords.X = static_cast<short>((1280.0f / static_cast<float>((iWidth)) * (iWidth / 2)));
	m_MouseCoords.Y = static_cast<short>((1024.0f / static_cast<float>((iHeight)) * (iHeight / 2)));

	

	return (true);
}

/*---------------------------------------------------------------------------------------------------------------------------
*
* This function Processes the scene
*
* @author Team Blue
*
*---------------------------------------------------------------------------------------------------------------------------*/
void
CGameScene::ProcessScene(float _fDeltaTick)
{
	if (m_bPaused == false && m_bGameOver == false)
	{
		m_pRenderer->GetMeshManager().Process(_fDeltaTick);

		CheckMouseActive();
		

		m_pWaveManager->Process(_fDeltaTick, m_pTerrain);

		m_pTerrain->Process(_fDeltaTick);

		m_pRenderer->GetParticleManager().Process(_fDeltaTick);

		if (m_pRadialMenu)
		{
			CGameCamera* pGameCamera = dynamic_cast<CGameCamera*>(m_pViewport->GetActiveCamera());

			if (m_pRadialMenu->IsOpen())
			{
				m_bRadMenuOpen = true;
				pGameCamera->DisableCameraControls(true);

				if (m_pPlayer)
					m_pRadialMenu->AutoDisableButtons(m_pPlayer->GetGold());

				if (!m_pInputManager->GetXInputController().IsPluggedIn())
				{
					m_bRadMenu360 = false;
					COORD mousePos = CApplication::GetInstance().GetGameWindow().GetMosueCoords();
					m_pRadialMenu->Process(mousePos.X, mousePos.Y);
				}

			}
			else
			{
				m_bRadMenuOpen = false;
				pGameCamera->DisableCameraControls(false);
				m_pRenderer->GetSpriteManager().SetVisible(true, m_uiCrosshairId);
			}
		}

		if (m_pRadialMenu ? !m_pRadialMenu->IsOpen() : true)	// Only do ray casting if the Radial Menu is not open.
			ObjectSelect(false);	// Ray casting without selecting anything.


		MouseSelection();

		ResetCursor();
	}
}

/*---------------------------------------------------------------------------------------------------------------------------
*
* This function draws the objects
*
* @author Team Blue
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CGameScene::DrawScene(CD3DRenderer* _pRenderer)
{
	_pRenderer->GetLightManager().TurnOnLight(m_uiLightDirectional);

	m_pViewport->Draw(_pRenderer);

	m_pWaveManager->Draw(_pRenderer);	

	DrawTiles();
	
	_pRenderer->GetSpriteManager().DrawWorld();
	
	//////////////////////////////
	// Alpha draw calls.

	_pRenderer->GetParticleManager().Draw(&reinterpret_cast<D3DXVECTOR3&>(m_pViewport->GetActiveCamera()->GetWorldMatrix_s().GetPosition(CVector3())));

	//////////////////////////////
	// Heads Up Display draw calls (if not in the hud, place draw call above this).

	if (m_pHud && !m_bGameOver)
	{
		m_pHud->Draw();

		if (m_pTerrain)
			m_pHud->DrawTowerMarkers(m_pTerrain->GetTowers(), m_pTerrain->GetNumTowers());

		m_pHud->DrawEnemyMarkers();
	}

	#if _DEBUG

	if(m_bShowDebugInfo && !m_bGameOver)
		DrawDebugInfo();

	#endif

	if (m_pRadialMenu && !m_bGameOver)
		if (m_pRadialMenu->IsOpen())
			m_pRadialMenu->Draw();	

	_pRenderer->GetSpriteManager().DrawScreen();

	CWave::SetHasNotBeenDrawn();
}

void
CGameScene::RecoverFromOverlayScene()
{
	m_pInputManager->EnableInput();


	m_bPaused = false;

	if (m_pInputManager->GetXInputController().IsPluggedIn() == false)
	{
		m_bSkipLeftClick = true;
	}

	m_bLeftClick = false;
	static_cast<CGameCamera*>(m_pViewport->GetActiveCamera())->DisableCameraControls(false);
}


void
CGameScene::ExecuteGameOver(bool _bWon)
{
	if (!m_bGameOver)
	{
		static_cast<CGameCamera*>(m_pViewport->GetActiveCamera())->DisableCameraControls(true);
		m_bGameOver = true;
		m_bPaused = true;


		bool* bWon = new bool;
		*bWon = _bWon;


		CApplication::GetInstance().GetGameWindow().SetOverlayScene(OVERLAYSCENE_GAMEWIN, bWon);

		m_pInputManager->GetXInputController().SetRumbleLeft(XRUMBLELVL_4, 5.0f);
		m_pInputManager->GetXInputController().SetRumbleRight(XRUMBLELVL_4, 5.0f);
	}
}




/********************************
            Protected
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function Initialises the lights
*
* @author Team Blue
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CGameScene::InitialiseLights(CD3DRenderer* _pRenderer)
{
	//Create default light
	m_uiLightDirectional = _pRenderer->GetLightManager().AddLight();


	return (true);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function initialises the viewports
*
* @author Team Blue
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CGameScene::InitialiseViewports(CD3DRenderer* _pRenderer)
{
	const unsigned int kuiWindowWidth = CApplication::GetInstance().GetGameWindow().GetClientWidth();
	const unsigned int kuiWindowHeight = CApplication::GetInstance().GetGameWindow().GetClientHeight();


	m_pViewport = new CViewport();
	m_pViewport->Initialise(0, 0, kuiWindowWidth, kuiWindowHeight, 0, _pRenderer);
	m_pViewport->CreateGameCamera(3.14159682f/3.0f, 0.1f, 1000.0f, &m_pInputManager->GetDirectInput(), &m_pInputManager->GetXInputController(), m_pTerrain);
	m_pViewport->SetActiveCamera(m_pViewport->GetLastCreatedCamera());


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
CGameScene::ResetCursor()
{
	if (m_bGameOver == false && m_bPaused == false)
	{
		CApplication::GetInstance().GetGameWindow().HideCursor();
	}
}






/**
*
* This function checks for collision between and platforms on the level.
*
* @author Daniel Langsford
*
*/
void
CGameScene::ObjectSelect(bool _bClicked)
{
	if (!m_pTerrain->GetGridWidth() || !m_pTerrain->GetGridHeight())
	{
		return;
	}

	CVector3 vecPosition;

	CRayCast rayCast;
	rayCast.CastRay(m_pViewport, (m_pInputManager->GetXInputController().IsPluggedIn() == false));
	D3DXVECTOR3 vecNear;
	D3DXVECTOR3 vecFar;
	rayCast.Get3DPoints(vecNear, vecFar);

	if (MathUtility::IsLineGroundIntersecting(vecNear, vecFar, m_pTerrain->GetTowerHeightOffset()))
	{
		D3DXVECTOR3 vecIntersect;
		unsigned int uiX = 0;
		unsigned int uiY = 0;

		MathUtility::GetLineGroundIntersect(vecNear, vecFar, vecIntersect, m_pTerrain->GetTowerHeightOffset());
		const CTile& rTile = m_pTerrain->GetTile(vecIntersect, &uiX, &uiY);
		m_uiSelectedTileX = uiX;
		m_uiSelectedTileY = uiY;
		
		static unsigned int s_uiTowerID = Utility::INVALID_ID;

		m_pSelectedTile = &rTile;

		if(rTile.GetTileType() == TILETYPE_RAISED && rTile.GetObjectID() == Utility::INVALID_ID)
		{
			m_bCollision = true;

			if(_bClicked)
			{
				//Open Radial Menu.
				if (m_pRadialMenu)
				{
					if (!m_pRadialMenu->IsOpen())
					{
						unsigned int uiNumTowers = CHudDataManager::GetInstance()->GetNumChildren(HUDGRP_TOWER);
						if (uiNumTowers > 3)	// 3 starter towers offered.
							uiNumTowers = 3;

						if (uiNumTowers)
						{
							if (m_bSkipLeftClick == false)
							{
								if (m_pRadialMenu->Open(uiNumTowers < 3 ? uiNumTowers : 3))	// Maximum 3 towers displayed.
								{
									m_uiSelectedTileX = uiX;
									m_uiSelectedTileY = uiY;

									//Populate options.
									for (unsigned int ui = 0; ui < uiNumTowers; ++ui)
									{
										TRadialMenuButtonData* pData = &m_pRadialMenu->GetButtonData(ui);
										pData->m_pStaticMemberFunction = &CGameScene::BuildTower;
										pData->m_pInstanceMemberData = this;
										pData->m_pkReferenceData = &CHudDataManager::GetInstance()->GetData(HUDGRP_TOWER, ui);
									}
								}
							}
							else
							{
								m_bSkipLeftClick = false;
							}
						}
					}
				}
			}
		}
		else if(rTile.GetTileType() == TILETYPE_RAISED && rTile.GetObjectType() == TILEOBJ_TOWER)
		{
			if(_bClicked)
			{
				if (m_pRadialMenu)
				{
					if (!m_pRadialMenu->IsOpen())
					{
						if (m_bSkipLeftClick == false)
						{
							s_uiTowerID = Utility::INVALID_ID;

							// Get tower.
							CTower& rTower = m_pTerrain->GetTower(rTile.GetObjectID());
							std::vector<char*>& rVecTowerUpgrades = rTower.GetTowerUpgradeTypes();

							unsigned int uiNumTowers = static_cast<unsigned int>(rVecTowerUpgrades.size());


							if (m_pRadialMenu->Open(uiNumTowers + 1))	// + 1 for the "sell" option.
							{
								m_uiSelectedTileX = uiX;
								m_uiSelectedTileY = uiY;

								CHudDataManager& rHudDataManager = *CHudDataManager::GetInstance();

								//Populate options
								for (unsigned int ui = 0; ui < uiNumTowers; ++ui)
								{
									TRadialMenuButtonData* pData = &m_pRadialMenu->GetButtonData(ui);
									pData->m_pStaticMemberFunction = &CGameScene::UpgradeTower;
									pData->m_pkReferenceData = rHudDataManager.GetData(HUDGRP_TOWER, rVecTowerUpgrades[ui]);
									pData->m_pInstanceMemberData = this;					
								}

								// "Sell" button.
								TRadialMenuButtonData* pData = &m_pRadialMenu->GetButtonData(uiNumTowers);
								pData->m_bNoDisable = true;	// Prevent this button from ever being disabled.
								pData->m_pStaticMemberFunction = &CGameScene::SellTower;
								pData->m_pInstanceMemberData = this;
								if (rHudDataManager.GetNumChildren(HUDGRP_MISC) > 0)
								{
									pData->m_pkReferenceData = &rHudDataManager.GetData(HUDGRP_MISC, unsigned int(0));
									unsigned int uiOriginalValue = rHudDataManager.GetData(HUDGRP_TOWER, rTower.GetTowerType())->m_uiValue;
									rHudDataManager.SetValue(HUDGRP_MISC, 0, static_cast<unsigned int>(uiOriginalValue * 0.8f));
								}
							}
						}
					}
				}
			}
		}
		else
		{
			m_bCollision = false;
			m_bSkipLeftClick = false;
		}

		if (m_pHud)
		{
			if (m_pRadialMenu ? !m_pRadialMenu->IsOpen() : true)	// If the radial menu is not open...
			{
				unsigned int uiID = rTile.GetObjectType() == TILEOBJ_TOWER ? rTile.GetObjectID() : Utility::INVALID_ID;
				
				if (s_uiTowerID != uiID)
				{
					s_uiTowerID = uiID;

					CTower* pTower = s_uiTowerID == Utility::INVALID_ID ? 0 : &m_pTerrain->GetTower(s_uiTowerID);

					m_pHud->SetExtendedInfo(pTower);
					m_pHud->SetSelectionData(!pTower ? 0 : CHudDataManager::GetInstance()->GetData(HUDGRP_TOWER, pTower->GetTowerType()));
				}
			}
		}
	}
}

/*---------------------------------------------------------------------------------------------------------------------------
*
* Draws the debug info
*
* @author Daniel langsford
*
*---------------------------------------------------------------------------------------------------------------------------*/
void
CGameScene::DrawDebugInfo()
{
	if (m_pLogWindow)
	{
		
		COORD MousePos = CApplication::GetInstance().GetGameWindow().GetMosueCoords();
			
		m_pLogWindow->EmptyBuffer();
		m_pLogWindow->SetErrorMessagePosition(m_rctLogBounds);
		m_pLogWindow->WriteToBuffer("Mouse Pos : (%i, %i)", MousePos.X, MousePos.Y); 
		m_pLogWindow->WriteToBuffer("FPS: %i", m_uiFramesPerSecond);
		m_pLogWindow->WriteToBuffer("");
		m_pLogWindow->WriteToBuffer("Wave Count: %i", m_pWaveManager->GetCurrentWaveCount());
		
		
		CVector3 LookAtPosition;
		CCamera* ActiveCamera = m_pViewport->GetActiveCamera();
		dynamic_cast<CGameCamera*>(ActiveCamera)->m_pLookAtEntity->GetWorldMatrix().GetPosition(LookAtPosition);

		m_pLogWindow->WriteToBuffer("LookAt X : %f", LookAtPosition.x);
		m_pLogWindow->WriteToBuffer("LookAt y : %f", LookAtPosition.y);
		m_pLogWindow->WriteToBuffer("LookAt z : %f", LookAtPosition.z);
		m_pLogWindow->WriteToBuffer("");

		CVector3 PlaceHolder;
		dynamic_cast<CGameCamera*>(ActiveCamera)->m_pPlaceHolder->GetWorldMatrix().GetPosition(PlaceHolder);

		m_pLogWindow->WriteToBuffer("Camera X : %f", PlaceHolder.x);
		m_pLogWindow->WriteToBuffer("Camera y : %f", PlaceHolder.y);
		m_pLogWindow->WriteToBuffer("Camera z : %f", PlaceHolder.z);
		m_pLogWindow->WriteToBuffer("");
		
		
	 
		if(m_bCollision == true)
		{
			m_pLogWindow->WriteToBuffer("Ray / Tile Collision!");
		}
		else
		{
			m_pLogWindow->WriteToBuffer("No collision detected!");
		}
		

		m_pLogWindow->SetFont(m_uiFontId);
		m_pLogWindow->PrintToScreen(m_uiLogBoxId);
	}
}

void
CGameScene::HandleDMouseInput(EDInputMouse _eDMouse, bool _bDown, long _lValue)
{
	switch (_eDMouse)
	{
	case DMOUSE_LEFTCLICK:
		{
			m_bLeftClick = _bDown;
			m_bUseMousePos = true;

			if(m_bLeftClick)
			{
				if(m_pRadialMenu->IsOpen())
				{
					m_pRadialMenu->ExecuteButton();
				}
				else
				{
					ObjectSelect(true);	// Ray casting with click effect.
				}
			}

			break;
		}


	case DMOUSE_RIGHTCLICK:
		{
			m_bRightClick = _bDown;

			if (_bDown && m_pRadialMenu)
			{
				if (m_pRadialMenu->IsOpen())
				{
					m_pRadialMenu->Close();
				}
			}

			break;
		}
	}
}

void
CGameScene::HandleDKeyboardInput(EDInputKeyboard _eDKebyoard, bool _bDown)
{
	switch (_eDKebyoard)
	{
	case DKEYBOARD_ESCAPE:
		{
			if (_bDown)
			{
				if (m_pRadialMenu->IsOpen())
				{
					m_pRadialMenu->Close();
				}
				else
				{
					OpenPauseMenu();
				}
			}
			break;
		}
	}
}


void
CGameScene::HandleXButtonInput(EXInputButton _eXButton, bool _bDown)
{
	switch (_eXButton)
	{

	case XBUTTON_B:
		{
			m_bRightClick = _bDown;

			// Close Radial Menu if it is open.
			if (_bDown && m_pRadialMenu)
			{
				if (m_pRadialMenu->IsOpen())
				{
					m_pRadialMenu->Close();
				}
			}
		}
		break;


	case XBUTTON_A:
		{
			if(_bDown)
			{
				m_pRenderer->GetSpriteManager().SetVisible(false, m_uiCrosshairId);
				m_bLeftClick = true;

				if(m_pRadialMenu->IsOpen())
				{
					m_pRadialMenu->ExecuteButton();
				}
				else
				{
					ObjectSelect(true);	// Ray casting with click.
				}
			}
			else
			{
				m_bLeftClick = false;
			}
		}
		break;


	case XBUTTON_START:
		{
			if(_bDown)
			{
				OpenPauseMenu();
			}
		}
		break;
		
	}
}


void
CGameScene::HandleXAnalogInput(EXInputAnalog _eXAnalog, float _fValue)
{
	switch (_eXAnalog)
	{
	case XANALOG_LEFTX: // Fall through
		{
			m_fAnalogLeftX = _fValue > 0.3 || _fValue < -0.3 ? _fValue : 0;
		}
		break;

	case XANALOG_LEFTY:
		{
			m_fAnalogLeftY = _fValue > 0.3 || _fValue < -0.3 ? _fValue : 0;
		}
		break;
	}

	if(_fValue > 0.3f || _fValue < -0.3f)
	{
		m_bUseMousePos = false;
		m_pRenderer->GetSpriteManager().SetPosition(CVector3(m_MouseCoords.X, m_MouseCoords.Y, 0), m_uiCrosshairId);
	}

	if(_fValue > 0.3f)
	{
		if(m_pRadialMenu->IsOpen())
		{
			SetCursorPos(static_cast<int>(m_pRadialMenu->GetDrawPositionX()), static_cast<int>(m_pRadialMenu->GetDrawPositionY()));						
		}						
	}

	if (m_pRadialMenu)
	{
		if (m_pRadialMenu->IsOpen())
		{
			static bool s_bLeftInCentre = true;	// To remember the old state.

			if (m_fAnalogLeftX || m_fAnalogLeftY)
			{
				s_bLeftInCentre = false;
				m_bRadMenu360 = true;	// Handled the Radial Menu using the Xbox 360 controller;


				float fAngle = MathUtility::AngleFromDeltaPos(m_fAnalogLeftX, m_fAnalogLeftY);


				m_pRadialMenu->Process(&fAngle);
			}
			else
			{
				if (!s_bLeftInCentre)
				{
					s_bLeftInCentre = true;
					m_bRadMenu360 = true;
					m_pRadialMenu->Process(0);
				}
			}
		}
	}
}


void
CGameScene::SetControllerActive(bool _bActive)
{
	m_bController = _bActive;
}

void
CGameScene::BuildTower(void* _pGameSceneInstance, unsigned char _ucButton)
{
	assert(_pGameSceneInstance);
	CGameScene& rGameScene = *reinterpret_cast<CGameScene*>(_pGameSceneInstance);

	// Build tower
	TRadialMenuButtonData& rButton = rGameScene.m_pRadialMenu->GetButtonData(_ucButton);

	if (rButton.m_pkReferenceData)
	{		
		if(rGameScene.m_pPlayer->GetGold() >= rButton.m_pkReferenceData->m_uiValue)
		{
			rGameScene.m_pTerrain->AddTower(m_uiSelectedTileX, m_uiSelectedTileY, rButton.m_pkReferenceData->m_pcSectionHeader);	
			rGameScene.m_pPlayer->SetGold(rGameScene.m_pPlayer->GetGold() - rButton.m_pkReferenceData->m_uiValue);
		}
	}

	rGameScene.m_pRadialMenu->Close();
}

void
CGameScene::UpgradeTower(void* _pGameSceneInstance, unsigned char _ucButton)
{
	assert(_pGameSceneInstance);
	CGameScene& rGameScene = *reinterpret_cast<CGameScene*>(_pGameSceneInstance);

	//Create a new, upgraded tower	
	TRadialMenuButtonData& rButton = rGameScene.m_pRadialMenu->GetButtonData(_ucButton);

	if (rButton.m_pkReferenceData)
	{		
		if(rGameScene.m_pPlayer->GetGold() >= rButton.m_pkReferenceData->m_uiValue)
		{
			//Remove current tower
			rGameScene.m_pTerrain->DestroyTower(m_uiSelectedTileX, m_uiSelectedTileY);

			rGameScene.m_pTerrain->AddTower(m_uiSelectedTileX, m_uiSelectedTileY, rButton.m_pkReferenceData->m_pcSectionHeader);	
			rGameScene.m_pPlayer->SetGold(rGameScene.m_pPlayer->GetGold() - rButton.m_pkReferenceData->m_uiValue);
		}
	}

	//Close menu
	rGameScene.m_pRadialMenu->Close();
}

void
CGameScene::SellTower(void* _pGameSceneInstance, unsigned char _ucButton)
{
	assert(_pGameSceneInstance);
	CGameScene& rGameScene = *reinterpret_cast<CGameScene*>(_pGameSceneInstance);

	//Remove current tower
	rGameScene.m_pTerrain->DestroyTower(m_uiSelectedTileX, m_uiSelectedTileY);

	//Return eighty percent of tower value to the player.
	TRadialMenuButtonData& rButton = rGameScene.m_pRadialMenu->GetButtonData(_ucButton);

	unsigned int uiValue = rButton.m_pkReferenceData ? rButton.m_pkReferenceData->m_uiValue : 30;
	rGameScene.m_pPlayer->SetGold(rGameScene.m_pPlayer->GetGold() + uiValue);

	//Close menu
	rGameScene.m_pRadialMenu->Close();
}



bool
CGameScene::InitialiseSprites()
{
	CWindow& rGameWindow = CApplication::GetInstance().GetGameWindow();
	const unsigned int kuiWindowWidth = 1280;
	const unsigned int kuiWindowHeight = 1024;

	//Load crosshair icons
	unsigned int uiPositionX = kuiWindowWidth / 2;
	unsigned int uiPositionY = kuiWindowHeight / 2;

	m_uiCrosshairId = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Cursor_Crosshair.png");
	assert(m_uiCrosshairId != -1);
	m_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiCrosshairId);
	m_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiCrosshairId);

	CVector3 vecPos;
	vecPos.x = static_cast<float>(uiPositionX);
	vecPos.y = static_cast<float>(uiPositionY);
	vecPos.z = 0.0f;
		
	m_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiCrosshairId);

	RECT SpriteRect = m_pRenderer->GetSpriteManager().GetRect(m_uiCrosshairId);
	int iWidth = SpriteRect.right - SpriteRect.left;
	int iHeight = SpriteRect.bottom - SpriteRect.top;

	float fX = static_cast<float>(iWidth/2);
	float fY = static_cast<float>(iHeight/2);

	m_pRenderer->GetSpriteManager().SetCenter(&CVector3(fX, fY, 0.0f), m_uiCrosshairId);

	//Load pause button
	m_uiPauseId = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/Game_Pause.png");
	
	m_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiPauseId);
	m_pRenderer->GetSpriteManager().SetVisible(true, m_uiPauseId);

	m_pRenderer->GetSpriteManager().SetPosition(CVector3(50, 50, 0), m_uiPauseId);

	//First waypoint
	m_uiStartWaypoint = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/Game_startWaypoint.png");
	
	m_pRenderer->GetSpriteManager().SetObjectSpace(true, m_uiStartWaypoint);
	
	vecPos = m_pTerrain->GetWaypointManager().GetWaypoint(0)->GetPosition();
	vecPos.y += 1.0f;

	m_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiStartWaypoint);

	//End waypoint
	m_uiEndWaypoint = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/Game_EndWaypoint.png");
	
	m_pRenderer->GetSpriteManager().SetObjectSpace(true, m_uiEndWaypoint);

	int iLastWaypoint = m_pTerrain->GetWaypointManager().GetNumWaypoints();
	iLastWaypoint -= 1;
	
	vecPos = m_pTerrain->GetWaypointManager().GetWaypoint(iLastWaypoint)->GetPosition();
	vecPos.y += 1.0f;

	m_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiEndWaypoint);

	
	return(true);

}

bool
CGameScene::InitialisePlayerInputTarget()
{
	//Mouse
	m_pInputManager->GetDirectInput().AddTarget(DMOUSE_LEFTCLICK, this);
	m_pInputManager->GetDirectInput().AddTarget(DMOUSE_RIGHTCLICK, this);
	m_pInputManager->GetDirectInput().AddTarget(DMOUSE_WHEEL, this);


	m_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_ESCAPE, this);


	return (true);
}

bool
CGameScene::InitialiseXInputTarget()
{
	//XInput Controller
	m_pInputManager->GetXInputController().AddTarget(XBUTTON_A, this);
	m_pInputManager->GetXInputController().AddTarget(XBUTTON_B, this);
	m_pInputManager->GetXInputController().AddTarget(XANALOG_LEFTY, this);
	m_pInputManager->GetXInputController().AddTarget(XANALOG_LEFTX, this);
	m_pInputManager->GetXInputController().AddTarget(XBUTTON_START, this);


	return (true);
}

bool
CGameScene::IntiialisePlayer(unsigned int _uiStartGold, unsigned int _uiStartLives)
{
	bool bSuccess = false;


	m_pPlayer = new CPlayer;
	bSuccess = m_pPlayer->Initialise("Maps/Cool Map.map");
	m_pPlayer->SetGold(_uiStartGold);
	m_pPlayer->SetLives(_uiStartLives);


	return (true);
}

bool
CGameScene::InitialiseTerrain(CD3DRenderer* _pRenderer, const char* _kcpMapFile)
{
	m_pTerrain = new CTerrain();
	m_pTerrain->Initialise(_pRenderer, 2.0f, 1.0f, true);
	m_pTerrain->LoadMap(_kcpMapFile);

	return (true);
}

bool
CGameScene::InitialiseWaveManager(CD3DRenderer* _pRenderer, CTerrain* _pTerrain, CGameSceneData* _pGameSceneData)
{
	m_pWaveManager = new CWaveManager();
	m_pWaveManager->Initialise(_pRenderer, _pTerrain, _pGameSceneData->GetMapFile(), m_pInputManager, static_cast<unsigned int>(_pGameSceneData->GetDifficulty()));

	return(true);
}

bool
CGameScene::InitialiseRadialMenu(CD3DRenderer* _pRenderer, unsigned int _uiWindowWidth, unsigned int _uiWindowHeight)
{
	m_pRadialMenu = new CRadialMenu();
	if (m_pRadialMenu)
	{
		m_pRadialMenu->Initialise(_pRenderer,
								  m_pHud,
								  min(_uiWindowWidth, _uiWindowHeight),	// Maximum diameter allowed.
								  50,		// Maximum lines used to represent the inner circle.
								  5.0f,
								  0.3f,	// 30% of the radial menu will be the centre circle.
								  _uiWindowWidth * 0.5f,	// X position where the Radial Menu will appear.
								  _uiWindowHeight * 0.5f);	// Y position where the Radial Menu will appear.
	}
	
	return !!m_pRadialMenu;
}

bool
CGameScene::InitialiseHud(CD3DRenderer* _pRenderer, unsigned int _uiWindowWidth, unsigned int _uiWindowHeight, const char* _pkcMapFile)
{
	assert(m_pPlayer);

	m_pHud = new CHud();
	if (m_pHud)
	{
		bool bLoaded = false;

		if (_pkcMapFile)
		{
			CINIParser parser;
			if (parser.LoadINIFile(_pkcMapFile))
			{
				std::wstring string;
				parser.GetValue("Meta Data", "MapPreviewFile", string);
				string = std::wstring(L"Maps\\") + string;
				m_pHud->Initialise(_pRenderer, m_pPlayer, m_pWaveManager, _uiWindowWidth, _uiWindowHeight, string.c_str());
				bLoaded = true;
			}
		}

		if (!bLoaded)
		{
			m_pHud->Initialise(_pRenderer, m_pPlayer, m_pWaveManager, _uiWindowWidth, _uiWindowHeight, 0);
		}

		if (m_pTerrain)
		{
			m_pHud->InitialiseTerrain(*m_pTerrain);
		}
		else
		{
			assert(false);
		}
	}

	return !!m_pHud;
}

CGameSceneData&
CGameScene::GetData()
{
	return(*m_pGameData);
}



void
CGameScene::DrawTiles()
{
	if (m_pSelectedTile && m_pSelectedTile->GetObjectType() == TILEOBJ_TOWER)
	{
		//Draw terrain excluding selected tile and towers
		m_pTerrain->Draw(m_pSelectedTile, false);


		//Draw towers excluding select tower
		m_pTerrain->DrawTowers(m_pSelectedTile->GetObjectID());


		//Set render states
		m_pRenderer->GetDeviceManager().SetRenderState(D3DRS_TEXTUREFACTOR, 0xFFAAAAFF);
		m_pRenderer->GetDeviceManager().SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
		m_pRenderer->GetDeviceManager().SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
		m_pRenderer->GetDeviceManager().SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);


		m_pTerrain->DrawTile(m_uiSelectedTileX, m_uiSelectedTileY);
		m_pTerrain->DrawTower(m_pSelectedTile->GetObjectID());


		m_pRenderer->GetDeviceManager().ResetTextureStageStates(0);
	}
	else if (m_pSelectedTile && m_pSelectedTile->GetObjectType() == TILEOBJ_NONE)
	{
		//Draw terrain excluding selected tile and towers
		m_pTerrain->Draw(m_pSelectedTile, true);


		if (m_pSelectedTile->GetTileType() == TILETYPE_RAISED)
		{
			//Set render states
			m_pRenderer->GetDeviceManager().SetRenderState(D3DRS_TEXTUREFACTOR, 0xFF00AA00);
			m_pRenderer->GetDeviceManager().SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
			m_pRenderer->GetDeviceManager().SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
			m_pRenderer->GetDeviceManager().SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);
		}
		else
		{
			//Set render states
			m_pRenderer->GetDeviceManager().SetRenderState(D3DRS_TEXTUREFACTOR, 0xFFAA0000);
			m_pRenderer->GetDeviceManager().SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
			m_pRenderer->GetDeviceManager().SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
			m_pRenderer->GetDeviceManager().SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);
		}


		m_pTerrain->DrawTile(m_uiSelectedTileX, m_uiSelectedTileY);


		m_pRenderer->GetDeviceManager().ResetTextureStageStates(0);
	}
	else
	{
		m_pTerrain->Draw();
	}
}



/********************************
            Private
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* 
*
* @author Team Blue
*
*---------------------------------------------------------------------------------------------------------------------------*/


void
CGameScene::GameOver(bool _bVictory)
{	
	if(_bVictory)
	{
		m_pRenderer->GetSpriteManager().SetVisible(true, m_uiVictoryScreenId);	
	}
	else
	{

	}
}

void
CGameScene::OpenPauseMenu()
{
	CApplication::GetInstance().GetGameWindow().SetOverlayScene(OVERLAYSCENE_GAMEPAUSEMENU);
	m_pInputManager->DisableInput();
	m_bPaused = true;

	if(m_pRadialMenu->IsOpen())
	{
		m_pRadialMenu->Close();
	}

	static_cast<CGameCamera*>(m_pViewport->GetActiveCamera())->DisableCameraControls(true);
}


void
CGameScene::CheckMouseActive()
{	
	if (m_pInputManager->GetXInputController().IsPluggedIn() == false)
	{
		COORD MousePos = CApplication::GetInstance().GetGameWindow().GetMosueCoords();

		int iWidth = CApplication::GetInstance().GetGameWindow().GetClientWidth();
		int iHeight = CApplication::GetInstance().GetGameWindow().GetClientHeight();

		MousePos.X = static_cast<short>((1280.0f / static_cast<float>(iWidth)) * MousePos.X);
		MousePos.Y = static_cast<short>((1024.0f / static_cast<float>(iHeight)) * MousePos.Y);

		if(MousePos.X != m_vecPreviousMousePos.x || MousePos.Y != m_vecPreviousMousePos.y)
		{
			m_bUseMousePos = true;
			m_pRenderer->GetSpriteManager().SetPosition(CVector3(MousePos.X, MousePos.Y, 0), m_uiCrosshairId);
		}

		m_vecPreviousMousePos.x = MousePos.X;
		m_vecPreviousMousePos.y = MousePos.Y;
	}
}


void
CGameScene::MouseSelection()
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
	SpriteBounds = m_pRenderer->GetSpriteManager().GetRect(m_uiPauseId);

	vecPos = m_pRenderer->GetSpriteManager().GetPositionScaled(m_uiPauseId);

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
		if(m_bLeftClick == true)
		{		
			OpenPauseMenu();		
		}			
	}
}
void
CGameScene::Deinitialise()
{
	m_pRenderer->GetSpriteManager().EraseAll();

//	FW_DELETE(m_pEnemySpawner);
	FW_DELETE(m_pPlayer);
	FW_DELETE(m_pTerrain);
	FW_DELETE(m_pRadialMenu);
	FW_DELETE(m_pHud);
	FW_DELETE(m_pWaveManager);
	FW_DELETE(m_pGameData);

	m_pRenderer->GetParticleManager().DeleteAllParticles();

	// Delete singleton data manager.
	CHudDataManager::DestroyInstance();
}