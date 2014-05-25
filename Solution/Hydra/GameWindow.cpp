//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   GameWindow.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <string>

// Local Includes
#include "Macros.h"
#include "Application.h"
#include "D3DRenderer.h"
#include "Clock.h"
#include "Scene.h"
#include "player.h"
#include "GameScene.h"
#include "SettingsScene.h"
#include "SoundSystem.h"

#include "SelectMapScene.h"
#include "MainMenuScene.h"
#include "MapEditor.h"
#include "INIParser.h"
#include "Terrain.h"
#include "Waypoint.h"
#include "EnemySpawner.h"
#include "WaveManager.h"
#include "Wave.h"
#include "PauseScene.h"
#include "Enemy.h"
#include "LightManager.h"
#include "GameSceneData.h"
#include "DeviceManager.h"
#include "SpriteManager.h"
#include "About.h"
#include "GameWinScene.h"
#include "SplashSceneMediaDesign.h"
#include "SplashSceneTeamBlueLogo.h"

#include "resource.h"

// This Include
#include "GameWindow.h"


// Static Variables
bool
CGameWindow::s_bWireframe = false;

bool
CGameWindow::s_bDebugInfo = true;

unsigned int
CGameWindow::s_uiPlayerLives = 0;

unsigned int
CGameWindow::s_uiPlayerGold = 0;

unsigned int
CGameWindow::s_uiEnemySpawnNumber = 0;

float
CGameWindow::s_fEnemySpawnRate = 0;



// Implementation

//Prototypes

BOOL CALLBACK
TestProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* GameWindow class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CGameWindow::CGameWindow()
{
	//Empty
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* GameWindow class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CGameWindow::~CGameWindow()
{
	Deinitialise();
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* Runs functionality for the window to process for this frame.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CGameWindow::ExecuteOneFrame()
{
	//Check renderering device ready
	bool bDeviceReady = m_pRenderer->IsDeviceReady();


	//Check window is displaying
	if (bDeviceReady == true)
	{
		//Check if scene was set to change
		if (m_eChangeToMainScene != SCENE_INVALID)
		{
			//Run scene change function
			ExecuteMainSceneChange();
		}


		//Check if scene was set to change
		if (m_eChangeToOverlayScene != OVERLAYSCENE_INVALID)
		{
			//Run scene change function
			ExecuteOverlaySceneChange();
		}


		//Check scene exists
		if (m_pMainScene != 0)
		{
			//Process clock
			m_pClock->Process();


			//Get delta tick
			float fDeltaTick = fDeltaTick = static_cast<float>(m_pClock->GetDeltaTick());


			//Process current scene
			m_pMainScene->Process(fDeltaTick);


			//Start device renderering
			m_pRenderer->StartRendering(true, true, false);


			//Draw current scene
			m_pRenderer->GetLightManager().CreateDarkness();
			m_pMainScene->Draw(m_pRenderer);


			//Check overlay scene exists
			if (m_eOverlayScene != OVERLAYSCENE_INVALID)
			{
				//Process overlay scene
				m_pOverlayScene->Process(fDeltaTick);


				//Draw overlay scene
				m_pRenderer->GetLightManager().CreateDarkness();
				m_pOverlayScene->Draw(m_pRenderer);
			}


			//End device renderering
			m_pRenderer->EndRendering();
		}
	}
	else
	{
		m_pRenderer->GetDeviceManager().ExecuteResetDevice();
		TurnOnCursorClip();
	}
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* Handles window messages.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

LRESULT CALLBACK
CGameWindow::WindowProc(HWND _hWindow, UINT _uiMessage, WPARAM _wParam, LPARAM _lParam)
{
	switch (_uiMessage)
	{
		case WM_KILLFOCUS:
			TurnOffCursorClip();
			m_bFocused = false;
			break;

		case WM_SETFOCUS:
			TurnOnCursorClip();
			m_bFocused = true;
			break;

		case WM_SETCURSOR:
			SetCursor(LoadCursor( NULL , IDC_ARROW ));
			break;

		case WM_MOUSEMOVE:
			m_crdMousePosition.X = static_cast<short>(LOWORD(_lParam));
			m_crdMousePosition.Y = static_cast<short>(HIWORD(_lParam));
			break;

		case WM_LBUTTONUP:
			//m_pMessageManager->SendMsgToTargets(true, _wParam, _lParam);
			break;

		case WM_RBUTTONDOWN:
			//m_pMessageManager->SendMsgToTargets(true, _wParam, _lParam);
			break;

		case WM_RBUTTONUP:
			//m_pMessageManager->SendMsgToTargets(true, _wParam, _lParam);
			break;

		case WM_LBUTTONDBLCLK:
			{
				CGameWindow& rWindow = dynamic_cast<CGameWindow&>(CApplication::GetInstance().GetGameWindow());

				if(rWindow.GetOverlaySceneType() == OVERLAYSCENE_SELECTMAP)
				{
					CSelectMapScene& MapSelect = reinterpret_cast<CSelectMapScene&>(rWindow.GetCurrentOverlayScene());
					MapSelect.DoubleClicked();
				}
				break;
			}
		
		case WM_KEYDOWN:
		{
			switch (LOWORD (_wParam))
			{
			case VK_F1:
				{
					//#if _DEBUG

					CGameWindow& rWindow = dynamic_cast<CGameWindow&>(CApplication::GetInstance().GetGameWindow());
					ShowCursor();

					if(rWindow.GetCurrentMainSceneType() == SCENE_GAME)
					{
						DialogBox(CApplication::GetInstance().GetInstanceHandle(),
							MAKEINTRESOURCE(IDD_DIALOG1),
							NULL,
							DlgProc);	
					}

					//#endif

					break;
				}


			case VK_OEM_3: //Tilde key '~'										
				{
					CGameWindow& rWindow = dynamic_cast<CGameWindow&>(CApplication::GetInstance().GetGameWindow());

					if(rWindow.GetCurrentMainSceneType() == SCENE_GAME)
					{
						DialogBox(CApplication::GetInstance().GetInstanceHandle(),
								  MAKEINTRESOURCE(IDD_DIALOG5),
								  NULL,
								  CheatProc);
					}
					break;
				}
			}
		}
		
		case WM_KEYUP:
			//m_pMessageManager->SendMsgToTargets(false, _wParam, _lParam);
			break;

		case WM_DESTROY:
			CApplication::GetInstance().Quit();
			break;	

		default:
			return (DefWindowProc(_hWindow, _uiMessage, _wParam, _lParam));
			break;
	}

	return (FALSE);
}

BOOL CALLBACK
CGameWindow::DlgProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	CGameWindow& rWindow = dynamic_cast<CGameWindow&>(CApplication::GetInstance().GetGameWindow());
	CGameScene& rGameScene = dynamic_cast<CGameScene&>(rWindow.GetCurrentMainScene());
	
	switch(_msg)
	{

	case WM_INITDIALOG:
		{
			//Add enemy types to combo box
			HWND hEdit;
			std::wstring newOption; 
			wchar_t* wcpNewOption;
			hEdit = GetDlgItem(_hwnd, IDC_ENEMYTYPE);

			newOption = L"Fast Enemy";
			wcpNewOption = const_cast<wchar_t*>(newOption.c_str());			
			SendMessage(hEdit, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(wcpNewOption));

			newOption = L"Medium Enemy";
			wcpNewOption = const_cast<wchar_t*>(newOption.c_str());
			SendMessage(hEdit, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(wcpNewOption));

			newOption = L"Heavy Enemy";
			wcpNewOption = const_cast<wchar_t*>(newOption.c_str());
			SendMessage(hEdit, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(wcpNewOption));

			newOption = L"Boss Enemy";
			wcpNewOption = const_cast<wchar_t*>(newOption.c_str());
			SendMessage(hEdit, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(wcpNewOption));
						
				
			if(s_bWireframe == true)
			{
				CheckDlgButton(_hwnd, IDC_CHECK2, BST_CHECKED);
			}
			if(s_bDebugInfo == true)
			{
				CheckDlgButton(_hwnd, IDC_CHECK1, BST_CHECKED);
			}

			wchar_t wcValue[256];
			unsigned int uiValue = 0;

			//Get Player gold value.
			hEdit = GetDlgItem(_hwnd, IDC_EDIT1);
			uiValue = rGameScene.GetPlayer()->GetGold();
			swprintf_s(wcValue, 19, L"%i", uiValue);
			
			SetWindowText(hEdit, wcValue);

			//Get player lives.
			hEdit = GetDlgItem(_hwnd, IDC_EDIT2);
			uiValue = rGameScene.GetPlayer()->GetLives();
			swprintf_s(wcValue, 19, L"%i", uiValue);
			
			SetWindowText(hEdit, wcValue);

			CApplication::GetInstance().GetGameWindow().ShowCursor();
			
			break;
		}

	case WM_COMMAND:
		{
			switch (LOWORD(_wparam))
			{
			case IDC_OK:
				{
					EndDialog(_hwnd, 0);
					CGameWindow& rWindow = dynamic_cast<CGameWindow&>(CApplication::GetInstance().GetGameWindow());

					//Set Wireframe mode.
					if(s_bWireframe == true)
					{
						rWindow.GetRenderer()->GetDeviceManager().SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
					}
					else
					{
						rWindow.GetRenderer()->GetDeviceManager().SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
					}

					//Show debug information.
					if(s_bDebugInfo == true && rWindow.GetCurrentMainSceneType() == SCENE_GAME)
					{
						CGameScene& rGameScene = dynamic_cast<CGameScene&>(rWindow.GetCurrentMainScene());
						rGameScene.SetShowDebugInfo(true);						
					}
					else if(s_bDebugInfo == false && rWindow.GetCurrentMainSceneType() == SCENE_GAME)
					{
						CGameScene& rGameScene = dynamic_cast<CGameScene&>(rWindow.GetCurrentMainScene());
						rGameScene.SetShowDebugInfo(false);		
					}	

					if(rWindow.GetCurrentMainSceneType() == SCENE_GAME)
					{
						//Set new Player gold.
						HWND hEdit = GetDlgItem(_hwnd, IDC_EDIT1);
						wchar_t wcMsgTxt[20];
						GetWindowText(hEdit, wcMsgTxt, 19);

						s_uiPlayerGold = static_cast<unsigned int>(_wtoi(wcMsgTxt));
						CGameScene& rGameScene = dynamic_cast<CGameScene&>(rWindow.GetCurrentMainScene());
						rGameScene.GetPlayer()->SetGold(s_uiPlayerGold);

						//Set new player lives.
						hEdit = GetDlgItem(_hwnd, IDC_EDIT2);
						GetWindowText(hEdit, wcMsgTxt, 19);

						s_uiPlayerLives = static_cast<unsigned int>(_wtoi(wcMsgTxt));
						rGameScene.GetPlayer()->SetLives(s_uiPlayerLives);

						/*----------------*
						 * ENEMY SPAWNING *
						 *----------------*/
						hEdit = GetDlgItem(_hwnd, IDC_EDIT7);
						GetWindowText(hEdit, wcMsgTxt, 19);

						s_uiEnemySpawnNumber = static_cast<unsigned int>(_wtoi(wcMsgTxt));

						hEdit = GetDlgItem(_hwnd, IDC_EDIT3);
						GetWindowText(hEdit, wcMsgTxt, 19);

						s_fEnemySpawnRate =  static_cast<float>(_wtof(wcMsgTxt));

						hEdit = GetDlgItem(_hwnd, IDC_ENEMYTYPE);
						int iSelectedIndex = static_cast<int>(SendMessage(hEdit, CB_GETCURSEL, 0, 0));
						wchar_t wcpEnemyType[256];
						for(int i = 0; i < 256; i++)
						{
							wcpEnemyType[i] = 0;
						}

						SendMessage(hEdit, CB_GETLBTEXT, iSelectedIndex, reinterpret_cast<LPARAM>(&wcpEnemyType));

						char cpEnemyType[256];
						size_t iLength = wcslen(wcpEnemyType);
						size_t iTemp = 0;


						if(iLength > 5)
						{

							wcstombs_s(&iTemp, cpEnemyType, sizeof(char*) * iLength,  wcpEnemyType, sizeof(wchar_t) * iLength);

							s_uiEnemySpawnNumber < 0 ?  s_uiEnemySpawnNumber = 0 : 0;
							s_fEnemySpawnRate < 0 ?  s_uiEnemySpawnNumber = 0 : 0;

							rGameScene.GetWaveManager()->GetCurrentWave()->GetEnemySpawner()->CreateSpawnPool( rWindow.GetRenderer(),
																		   cpEnemyType,
																		   rGameScene.GetTerrain()->GetWaypointManager().GetWaypoint(0),
																		   s_uiEnemySpawnNumber,
																		   s_fEnemySpawnRate, 1); 
						}
					}
					CApplication::GetInstance().GetGameWindow().HideCursor();
				}
				break;

			case IDC_BUTTON3:
				{					
					CApplication::GetInstance().GetGameWindow().GetRenderer()->GetSpriteManager().EraseAll();
					CApplication::GetInstance().GetGameWindow().SetMainScene(SCENE_MAINMENU, 0);
					CApplication::GetInstance().GetGameWindow().HideCursor();
					EndDialog(_hwnd, 0);	
					break;
				}

			case IDC_ENEMYVALUES:
				{
					DialogBox(CApplication::GetInstance().GetInstanceHandle(),
								  MAKEINTRESOURCE(IDD_DIALOG6),
								  NULL,
								  EnemyProc);
					break;
				}

			case IDC_CHECK1:
				{
					if(s_bDebugInfo == true)
					{
						s_bDebugInfo = false;
					}
					else
					{
						s_bDebugInfo = true;
					}

					break;
				}
			
			case IDC_CHECK2:
				{
					if(s_bWireframe == false)
					{
						s_bWireframe = true;
					}
					else
					{
						s_bWireframe = false;
					}
					break;
				}	
			case IDC_RESET:
				{
					CGameWindow& rWindow = dynamic_cast<CGameWindow&>(CApplication::GetInstance().GetGameWindow());
					CGameScene& rGameScene = dynamic_cast<CGameScene&>(rWindow.GetCurrentMainScene());					
					CGameSceneData* SceneData = new CGameSceneData;
					*SceneData = rGameScene.GetData();
					void* pData = reinterpret_cast<void*>(SceneData); 
							
					CApplication::GetInstance().GetGameWindow().GetRenderer()->GetSpriteManager().EraseAll();
					CApplication::GetInstance().GetGameWindow().SetMainScene(SCENE_GAME, pData);
					CApplication::GetInstance().GetGameWindow().HideCursor();
					EndDialog(_hwnd, 0);
					break;
				}

			
			case IDC_CANCEL:
				{
					CApplication::GetInstance().GetGameWindow().HideCursor();
					EndDialog(_hwnd, 0);
					break;
				}
			}
			break;
		}	

	case WM_CLOSE:
		{
			CApplication::GetInstance().GetGameWindow().HideCursor();
			EndDialog(_hwnd, 0);
			break;
		}
	}

	return(FALSE);
}

BOOL CALLBACK
CGameWindow::CheatProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	wchar_t wcMsgTxt[256];
	std::wstring strGold;
	std::wstring strLives;

	CGameWindow& rWindow = dynamic_cast<CGameWindow&>(CApplication::GetInstance().GetGameWindow());
	CGameScene& rGameScene = dynamic_cast<CGameScene&>(rWindow.GetCurrentMainScene());

	//Gold	
	strGold = L"Thug Lyf";

	//Win

	//Infinite Lives
	strLives = L"Lumberjack";
	
	switch(_msg)
	{
	case WM_INITDIALOG:
		{
			CApplication::GetInstance().GetGameWindow().ShowCursor();
			break;
		}

	case WM_CLOSE:
		{		
			CApplication::GetInstance().GetGameWindow().HideCursor();
			EndDialog(_hwnd, 0);
			break;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(_wparam))
			{
			case IDC_CHEATOK:
				{
					HWND hEdit = GetDlgItem(_hwnd, IDC_EDIT1);
					GetWindowText(hEdit, wcMsgTxt, 256);
					std::wstring strMessage = wcMsgTxt;

					if(strMessage == strLives)
					{		
						rGameScene.GetPlayer()->SetLives(9999999);	
					}
					if(strMessage == strGold)
					{		
						rGameScene.GetPlayer()->SetGold(9999999);	
					}

					CApplication::GetInstance().GetGameWindow().HideCursor();
					EndDialog(_hwnd, 0);
					break;			
				}
			case IDC_CHEATCANCEL:
				{
					CApplication::GetInstance().GetGameWindow().HideCursor();
					EndDialog(_hwnd, 0);
					break;		
				}
			}
		}
	}	
	
	return(false);
}

BOOL CALLBACK
CGameWindow::EnemyProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam)
{
	switch(_msg)
	{
	case WM_CLOSE:
		{	
			break;
		}

	case WM_COMMAND:
		{
			switch (LOWORD(_wparam))
			{
			case IDC_BUTTON12:
				{
					HWND hEdit;
					hEdit = GetDlgItem(_hwnd, IDC_HEALTH);

					wchar_t wcMsgTxt[20];
					GetWindowText(hEdit, wcMsgTxt, 19);
					//Get new health modifier
					int iHealth = static_cast<unsigned int>(_wtoi(wcMsgTxt));			

					//Get new velocity modifier
					hEdit = GetDlgItem(_hwnd, IDC_SPEED);
					GetWindowText(hEdit, wcMsgTxt, 19);
					int iVelocity = static_cast<unsigned int>(_wtoi(wcMsgTxt));

					std::vector<CEnemy*>& vecEnemyInstances = CEnemySpawner::GetEnemyInstances();
					unsigned int uiNumEnemyInstances = static_cast<unsigned int>(vecEnemyInstances.size());

					for(unsigned int i = 0; i < uiNumEnemyInstances; ++i)
					{
						vecEnemyInstances[i]->SetDefaultHealth(vecEnemyInstances[i]->GetDefaultHealth() + (iHealth * vecEnemyInstances[i]->GetDefaultHealth()));
						vecEnemyInstances[i]->SetDefaultMovementVelocity(vecEnemyInstances[i]->GetDefaultMovementVelocity() + (iVelocity * vecEnemyInstances[i]->GetDefaultMovementVelocity()));
					}

					EndDialog(_hwnd, 0);
						
				}
				break;
			}

	default: break;
		}

	}

	return(false);

}
	
/********************************
            Protected
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Changes the main scene.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CGameWindow::ExecuteMainSceneChange()
{
	//Delete current scene
	FW_DELETE(m_pMainScene);


	//Instance new scene
	switch (m_eChangeToMainScene)
	{
		case SCENE_SPLASH_MEDIA:
			m_pMainScene = new CSplashScene();
			break;

		case SCENE_SPLASH_LOGO:
			m_pMainScene = new CSplashSceneTeamBlue();
			break;

		case SCENE_MAINMENU:
			m_pMainScene = new CMainMenuScene();
			break;

		case SCENE_GAME:
			m_pMainScene = new CGameScene();
			break;

		case SCENE_MAPEDITOR:
			m_pMainScene = new CMapEditor();
			break;

		default:
			LOG_FATALERROR(false, "Unknown scene.");
			break;
	}


	//Set current scene;
	m_eMainScene = m_eChangeToMainScene;


	m_eChangeToMainScene = SCENE_INVALID;

	//Run scene initialise function
	m_pMainScene->Initialise(m_pRenderer, m_pChangeToMainSceneData);


	//Clean up	
	m_pChangeToMainSceneData = 0;
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* Changes the overlay scene.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CGameWindow::ExecuteOverlaySceneChange()
{
	//Delete current scene
	FW_DELETE(m_pOverlayScene);


	//Instance new scene
	switch (m_eChangeToOverlayScene)
	{
		case OVERLAYSCENE_GAMEPAUSEMENU:
			m_pOverlayScene = new CPauseScene();
			break;

		case OVERLAYSCENE_SETTINGS:
			m_pOverlayScene = new CSettingsScene();
			break;

		case OVERLAYSCENE_SELECTMAP:
			m_pOverlayScene = new CSelectMapScene();
			break;

		case OVERLAYSCENE_GAMEWIN:
			m_pOverlayScene = new CGameWinScene();
			break;

		case OVERLAYSCENE_DELETE:
			m_eOverlayScene = OVERLAYSCENE_INVALID;
			m_eChangeToOverlayScene = OVERLAYSCENE_INVALID;
			m_pChangeToOverlaySceneData = 0;
			return ;

		case OVERLAYSCENE_ABOUT:
			m_pOverlayScene = new CAboutScene();
			break;


		default:
			LOG_FATALERROR(false, "Unknown overlay scene");
			break;
	}


	//Set current scene;
	m_eOverlayScene = m_eChangeToOverlayScene;


	//Run scene initialise function
	m_pOverlayScene->Initialise(m_pRenderer, m_pChangeToOverlaySceneData);


	//Clean up
	m_eChangeToOverlayScene = OVERLAYSCENE_INVALID;
	m_pChangeToOverlaySceneData = 0;
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
CGameWindow::Deinitialise()
{
	//Empty
}