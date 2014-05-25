//
//  Diploma of Interactive Gaming
//  Scene Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   WaveManager.cpp
//  Description :   for implementation file
//  Author      :   Jamie.Smith
//  Mail        :   Jamie.Smith@mediadesign.school.nz
//

// Library includes.
#include <string>

// Local Includes
#include "wave.h"
#include "Terrain.h"
#include "Application.h"
#include "InputManager.h"
#include "D3DRenderer.h"
#include "SpriteManager.h"
#include "SoundSystem.h"
#include "DirectInput.h"
#include "XInputController.h"
#include "GameScene.h"

// This Include
#include "waveManager.h"

// Static Variables

// Static Function Prototypes


// Implementation

CWaveManager::CWaveManager()
: m_kfWaveDelay(3.0f)
, m_uiCurrentWave(0)
, m_uiWaveAmount(0)
, m_iSpriteOffSetX(0)
, m_iSpriteOffSetY(0)
, m_fTextTimer(3.0f)
, m_fTextDisplayTime(3.0f)
, m_fWaveTimer(10.0f)
, m_uiFirstDigitID(0)
, m_uiSecondDigitID(0)
, m_fCountDownDisplayTime(1)
, m_fCountDown(1)
, m_bSpawnNextWave(false)
, m_bDisplayText(false)
, m_bCurrentWaveSprites(false)
, m_fDifficulty(0)
, m_bGameOver(0)
{
}

CWaveManager::~CWaveManager()
{
	FW_DELETEMAP(unsigned int, CWave*, m_mapWaves);
}

/** 
*
* Initialises the wavemanager
* 
* @author Jamie.Smith  
* @Param _pRenderer a pointer to the renderer
* @Param _pTerrain a pointer to the Terrain
* @Param _kcpFileName a pointer to the the file destination of the map
* @Param _pInputManager a pointer to the Input manager
* @Param _uiDifficulty the difficulty
* @return bool
*
*/
bool
CWaveManager::Initialise(CD3DRenderer* _pRenderer, CTerrain* _pTerrain,
						 char* _kcpFileName, CInputManager* _pInputManager,
						 unsigned int _uiDifficulty)
{
	m_strFileName = _kcpFileName;
	
	m_pRenderer = _pRenderer;

	m_fDifficulty = static_cast<float>(_uiDifficulty) / 2.0f;

	CINIParser* _pParser = new CINIParser();
	_pParser->LoadINIFile(_kcpFileName);
	_pParser->GetValue("WaveNumber", "Wave", m_uiWaveAmount);
	delete _pParser;
	_pParser = 0;	

	InitialiseSprites(m_pRenderer);

	SpawnNewWave(_pTerrain);

	_pInputManager->GetDirectInput().AddTarget(DKEYBOARD_T , this);
	
	return(true);
}

/** 
*
* Processes the WaveManager
* 
* @author Jamie.Smith  
* @Param _fDeltaTick the delta of the clock
* @Param _pTerrain a pointer to the Terrain
* @return bool
*
*/
void
CWaveManager::Process(float _fDeltaTick, CTerrain* _pTerrain)
{
	if(m_bGameOver)
	{
		m_pRenderer->GetSpriteManager().EraseAll();

		static_cast<CGameScene&>(CApplication::GetInstance().GetGameWindow().GetCurrentMainScene()).ExecuteGameOver(true);
	}
	else
	{
		if(CheckNewWave() || m_bSpawnNextWave)
		{
			SpawnNewWave(_pTerrain);
		}	

		if(m_fWaveTimer <= 0)
		{
			m_mapWaves[m_uiCurrentWave]->Process(_fDeltaTick);
		}	

		CountTimers(_fDeltaTick);

		if(m_bDisplayText == true)
		{
			if(m_fWaveTimer < m_fTextTimer + 1.0f)
			{
				m_pRenderer->GetSpriteManager().SetVisible(true, m_uiWave);

				if(m_bCurrentWaveSprites == false)
				{
					GetWaveSprites(m_uiCurrentWave + 1);
					m_bCurrentWaveSprites = true;
				}

				m_fTextTimer -= _fDeltaTick;

				float fScalar = m_fTextTimer;
				if(fScalar > 1)
				{
					fScalar = 1;
				}

				float fCurrentAlpha = 1.0f * fScalar; //over time this goes to 0.0f

				const int kiAlphaMax = 255;

				unsigned char ucAlphaChannel = static_cast<unsigned char>(kiAlphaMax * fCurrentAlpha); //this will be between 0x00 and 0xff

				unsigned int uiRGB = 0x00FFFFFF; //Colour RGB

				unsigned int uiFinalColour = (ucAlphaChannel << 24) | uiRGB;	

				CApplication::GetInstance().GetGameWindow().GetRenderer()->GetSpriteManager().SetModulate(uiFinalColour, m_uiWave);
				CApplication::GetInstance().GetGameWindow().GetRenderer()->GetSpriteManager().SetModulate(uiFinalColour, m_uiSpriteReserve);
				CApplication::GetInstance().GetGameWindow().GetRenderer()->GetSpriteManager().SetModulate(uiFinalColour, m_uiFirstDigitID);
				CApplication::GetInstance().GetGameWindow().GetRenderer()->GetSpriteManager().SetModulate(uiFinalColour, m_uiSecondDigitID);
				
				//Countdown sprites

				//Will truncate float to int value. This is intentional.
				SetCountDownSprites(static_cast<int>(m_fTextTimer));

				m_fCountDown -= _fDeltaTick;
				if(m_fCountDown <= 0.0f)
				{
					m_fCountDown = m_fCountDownDisplayTime;

				}

				if(m_fTextTimer <= 0.0f)
				{
					m_bDisplayText = false;
					m_fTextTimer = m_fTextDisplayTime;
					DisableSprites();
				}		
			}
		}
	}
}

/** 
*
* Draws the WaveManager
* 
* @author Jamie.Smith  
* @Param _pRenderer a pointer to the Renderer
* @return void
*
*/
void
CWaveManager::Draw(CD3DRenderer* _pRenderer)
{
	if(m_fWaveTimer <= 0)
	{
		m_mapWaves[m_uiCurrentWave]->Draw(_pRenderer);
	}
	
}

/** 
*
* counts down the timers
* 
* @author Jamie.Smith  
* @Param _fDeltaTick a the delta of the clock
* @return void
*
*/
void
CWaveManager::CountTimers(float _fDeltaTick)
{
	m_fWaveTimer -= _fDeltaTick;
}

/** 
*
* Checks if a new wave needs to be spawned
* 
* @author Jamie.Smith
* @return bool
*
*/
bool
CWaveManager::CheckNewWave()
{
	if(m_fWaveTimer <= (m_kfWaveDelay * -1))
	{
		if(m_mapWaves[m_uiCurrentWave]->CheckIsWaveOver())
		{
			++m_uiCurrentWave;
			m_fWaveTimer = m_kfWaveDelay;

			if(m_uiCurrentWave > m_uiWaveAmount)
			{
				m_bGameOver = true;
			}

			return(true);
		}
	}
	return(false);
}

/** 
*
* Returns the current wave
* 
* @author Jamie.Smith  
* @return CWave
*
*/
CWave*
CWaveManager::GetCurrentWave()
{
	std::map<unsigned int, CWave*>::iterator iter;
	iter = m_mapWaves.find(m_uiCurrentWave);

	return iter != m_mapWaves.end() ? iter->second : 0;
}

/** 
*
* Returns the current wave number
* 
* @author Jamie.Smith  
* @return int
*
*/
int
CWaveManager::GetCurrentWaveCount() const
{
	return(m_uiCurrentWave);
}


void
CWaveManager::HandleDKeyboardInput(EDInputKeyboard _eDKebyoard, bool _bDown)
{
#if _DEBUG
	switch (_eDKebyoard)
	{
	case DKEYBOARD_T:
		if (_bDown)
		{
			++ m_uiCurrentWave;
			m_bSpawnNextWave = true;
		}
		break;
	}
#endif
}


/** 
*
* Initialises the sprites
* 
* @author Daniel langsford 
* @Param _pRenderer a pointer to the renderer
* @return void
*
**/
void
CWaveManager::InitialiseSprites(CD3DRenderer* _pRenderer)
{
	CWindow& rGameWindow = CApplication::GetInstance().GetGameWindow();
	const unsigned int kuiWindowWidth = 1280;
	const unsigned int kuiWindowHeight = 1024;	

	CD3DRenderer* m_pRenderer = CApplication::GetInstance().GetGameWindow().GetRenderer();

	m_uiWave = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/Game_Wave.png");
	assert(m_uiWave != -1);
	m_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiWave);
	m_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiWave);

	RECT SpriteRect = m_pRenderer->GetSpriteManager().GetRect(m_uiWave);
	int iWidth = SpriteRect.right - SpriteRect.left;		

	m_iSpriteOffSetY = kuiWindowHeight / 4;
	
	CVector3 vecPos(static_cast<float>(kuiWindowWidth / 2 - (iWidth * 1.5f) / 2),
					static_cast<float>(m_iSpriteOffSetY), 0.0f);

	m_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiWave);
	
	//Wave number 0
	m_uiSprite0 = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/Game_Wave0.png");
	assert(m_uiSprite0 != -1);
	m_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiSprite0);
	m_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiSprite0);
	vecPos.x +=  iWidth;
	m_iSpriteOffSetX = static_cast<int>(vecPos.x);
	m_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiSprite0);

	//Wave number 1
	m_uiSprite1 = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/Game_Wave1.png");
	assert(m_uiSprite1 != -1);
	m_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiSprite1);
	m_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiSprite1);
	m_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiSprite1);

	//Wave number 2
	m_uiSprite2 = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/Game_Wave2.png");
	assert(m_uiSprite2 != -1);
	m_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiSprite2);
	m_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiSprite2);
	m_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiSprite2);

	//Wave number 3
	m_uiSprite3 = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/Game_Wave3.png");
	assert(m_uiSprite3 != -1);
	m_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiSprite3);
	m_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiSprite3);
	m_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiSprite3);

	//Wave number 4
	m_uiSprite4 = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/Game_Wave4.png");
	assert(m_uiSprite4 != -1);
	m_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiSprite4);
	m_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiSprite4);
	m_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiSprite4);

	//Wave number 5
	m_uiSprite5 = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/Game_Wave5.png");
	assert(m_uiSprite5 != -1);
	m_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiSprite5);
	m_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiSprite5);
	m_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiSprite5);

	//Wave number 6
	m_uiSprite6 = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/Game_Wave6.png");
	assert(m_uiSprite6 != -1);
	m_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiSprite6);
	m_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiSprite6);
	m_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiSprite6);

	//Wave number 7
	m_uiSprite7 = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/Game_Wave7.png");
	assert(m_uiSprite7 != -1);
	m_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiSprite7);
	m_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiSprite7);
	m_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiSprite7);

	//Wave number 8
	m_uiSprite8 = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/Game_Wave8.png");
	assert(m_uiSprite8 != -1);
	m_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiSprite8);
	m_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiSprite8);
	m_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiSprite8);
		
	//Wave number 9
	m_uiSprite9 = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/Game_Wave9.png");
	assert(m_uiSprite9 != -1);
	m_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiSprite9);
	m_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiSprite9);
	m_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiSprite9);

	const int kiOffSetX = 40;
	const int kiOffSetY = 128;

	//Wave countdown sprite 3
	m_uiCountdown3 = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/Game_Wave3.png");
	assert(m_uiCountdown3 != -1);
	m_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiCountdown3);
	m_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiCountdown3);
	vecPos.x = static_cast<float>(kuiWindowWidth / 2 - kiOffSetX);
	vecPos.y += kiOffSetY;
	m_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiCountdown3);

	//Wave countdown sprite 2
	m_uiCountdown2 = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/Game_Wave2.png");
	assert(m_uiCountdown2 != -1);
	m_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiCountdown2);
	m_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiCountdown2);
	vecPos.x = static_cast<float>(kuiWindowWidth / 2 - kiOffSetX);
	m_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiCountdown2);

	//Wave countdown sprite 1
	m_uiCountdown1 = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/Game_Wave1.png");
	assert(m_uiCountdown1 != -1);
	m_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiCountdown1);
	m_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiCountdown1);
	vecPos.x = static_cast<float>(kuiWindowWidth / 2 - kiOffSetX);
	m_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiCountdown1);

	//Ellipses sprite
	m_uiEllipses = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/Wave Ellipses.png");
	assert(m_uiCountdown3 != -1);
	m_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiEllipses);
	m_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), m_uiEllipses);
	vecPos.x += 16;
	
	m_pRenderer->GetSpriteManager().SetPosition(vecPos, m_uiEllipses);

	DisableSprites();	
}

void
CWaveManager::SpawnNewWave(CTerrain* _pTerrain)
{
	DisableSprites();	

	CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Game-NewWave.wav");

	m_mapWaves[m_uiCurrentWave] = new CWave();
	m_mapWaves[m_uiCurrentWave]->Initialise(CApplication::GetInstance().GetGameWindow().GetRenderer(),
											_pTerrain, m_uiCurrentWave, m_strFileName.c_str(), m_fDifficulty);

	m_bDisplayText = true;
	m_bSpawnNextWave = false;
	m_bCurrentWaveSprites = false;
}

void
CWaveManager::GetWaveSprites(unsigned int _uiWaveNumber)
{	
	int iFirstDigit;
	int iSecondDigit;
	const int kiSpriteWidth = 42;

	unsigned int iFirstId;
	unsigned int iSecondId;

	iFirstDigit = static_cast<int>(_uiWaveNumber / 10);
	
	int iTruncation = _uiWaveNumber / 10;
	iTruncation *= 10;

	if(iTruncation < 1)
	{
		iSecondDigit = _uiWaveNumber;
	}
	else
	{
		iSecondDigit = _uiWaveNumber%iTruncation;
	}

	iFirstId = GetSpriteID(iFirstDigit);
	iSecondId =  GetSpriteID(iSecondDigit);

	if(iFirstId == iSecondId)
	{
		iSecondId = m_pRenderer->GetSpriteManager().Duplicate(iFirstId);
		m_uiSpriteReserve = iSecondId;
	}
	
	m_pRenderer->GetSpriteManager().SetVisible(true, m_uiWave);

	//Draw first digit
	m_pRenderer->GetSpriteManager().SetPosition(CVector3(m_iSpriteOffSetX, m_iSpriteOffSetY, 0),
											   iFirstId);

	m_pRenderer->GetSpriteManager().SetVisible(true, iFirstId);

	//Draw second digit
	m_pRenderer->GetSpriteManager().SetCenter(&CVector3(0,0,0), iSecondId);
	m_pRenderer->GetSpriteManager().SetPosition(CVector3(m_iSpriteOffSetX + kiSpriteWidth, m_iSpriteOffSetY, 0),
											    iSecondId);

	m_pRenderer->GetSpriteManager().SetVisible(true, iSecondId);

	m_uiFirstDigitID = iFirstId;
	m_uiSecondDigitID = iSecondId;

	
}

unsigned int
CWaveManager::GetSpriteID(int _iNumber)
{
	switch(_iNumber)
	{
	case 0:
		{
			return(m_uiSprite0);
			break;
		}
	case 1:
		{
			return(m_uiSprite1);
			break;
		}
	case 2:
		{
			return(m_uiSprite2);
			break;
		}
	case 3:
		{
			return(m_uiSprite3);
			break;
		}
	case 4:
		{
			return(m_uiSprite4);
			break;
		}
	case 5:
		{
			return(m_uiSprite5);
			break;
		}
	case 6:
		{
			return(m_uiSprite6);
			break;
		}
	case 7:
		{
			return(m_uiSprite6);
			break;
		}
	case 8:
		{
			return(m_uiSprite8);
			break;
		}
	case 9:
		{
			return(m_uiSprite9);
			break;
		}

	default:
		{
			return(-1);
			break;
		}
	}
}

void 
CWaveManager::DisableSprites()
{	
	//Set sprites to false
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiWave);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiSprite0);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiSprite1);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiSprite2);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiSprite3);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiSprite4);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiSprite5);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiSprite6);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiSprite7);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiSprite8);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiSprite9);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiSpriteReserve);

	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiFirstDigitID);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiSecondDigitID);

	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiCountdown3);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiCountdown2);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiCountdown1);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiEllipses);

	//Reset any colour blending
	m_pRenderer->GetSpriteManager().SetModulate(0xffffffff , m_uiWave);
	m_pRenderer->GetSpriteManager().SetModulate(0xffffffff , m_uiSprite0);
	m_pRenderer->GetSpriteManager().SetModulate(0xffffffff , m_uiSprite1);
	m_pRenderer->GetSpriteManager().SetModulate(0xffffffff , m_uiSprite2);
	m_pRenderer->GetSpriteManager().SetModulate(0xffffffff , m_uiSprite3);
	m_pRenderer->GetSpriteManager().SetModulate(0xffffffff , m_uiSprite4);
	m_pRenderer->GetSpriteManager().SetModulate(0xffffffff , m_uiSprite5);
	m_pRenderer->GetSpriteManager().SetModulate(0xffffffff , m_uiSprite6);
	m_pRenderer->GetSpriteManager().SetModulate(0xffffffff , m_uiSprite7);
	m_pRenderer->GetSpriteManager().SetModulate(0xffffffff , m_uiSprite8);
	m_pRenderer->GetSpriteManager().SetModulate(0xffffffff , m_uiSprite9);
	m_pRenderer->GetSpriteManager().SetModulate(0xffffffff , m_uiSpriteReserve);

	m_pRenderer->GetSpriteManager().SetModulate(0xffffffff , m_uiFirstDigitID);
	m_pRenderer->GetSpriteManager().SetModulate(0xffffffff , m_uiSecondDigitID);

	m_pRenderer->GetSpriteManager().SetModulate(0xffffffff , m_uiCountdown3);
	m_pRenderer->GetSpriteManager().SetModulate(0xffffffff , m_uiCountdown2);
	m_pRenderer->GetSpriteManager().SetModulate(0xffffffff , m_uiCountdown1);
	m_pRenderer->GetSpriteManager().SetModulate(0xffffffff , m_uiEllipses);

}



void
CWaveManager::SetCountDownSprites(int _iTimeRemaining)
{
	CD3DRenderer* pRenderer = CApplication::GetInstance().GetGameWindow().GetRenderer();

	unsigned int uiCurrentSpriteId = 0;

	//Set Alpha depending on display time remaining
	float fCurrentAlpha = 1.0f * m_fCountDown; //over time this goes to 0.0f

	const int kiAlphaMax = 255;

	unsigned char ucAlphaChannel = static_cast<char>(kiAlphaMax * fCurrentAlpha); //this will be between 0x00 and 0xff

	unsigned int uiRGB = 0x00FFFFFF; //Colour RGB

	unsigned int uiFinalColour = (ucAlphaChannel << 24) | uiRGB;


	switch(_iTimeRemaining)
	{
	case 2:
		{
			uiCurrentSpriteId = m_uiCountdown3;
			pRenderer->GetSpriteManager().SetVisible(true, m_uiCountdown3);
			pRenderer->GetSpriteManager().SetVisible(false, m_uiCountdown2);
			pRenderer->GetSpriteManager().SetVisible(false, m_uiCountdown1);
			break;
		}
	case 1:
		{
			uiCurrentSpriteId = m_uiCountdown2;
			pRenderer->GetSpriteManager().SetVisible(true, m_uiCountdown2);
			pRenderer->GetSpriteManager().SetVisible(false, m_uiCountdown3);
			pRenderer->GetSpriteManager().SetVisible(false, m_uiCountdown1);
			break;
		}
	case 0:
		{
			uiCurrentSpriteId = m_uiCountdown1;
			pRenderer->GetSpriteManager().SetVisible(true, m_uiCountdown1);
			pRenderer->GetSpriteManager().SetVisible(false, m_uiCountdown3);
			pRenderer->GetSpriteManager().SetVisible(false, m_uiCountdown2);
			break;
		}
	default:
		{
			break;
		}
	}

	pRenderer->GetSpriteManager().SetModulate(uiFinalColour, uiCurrentSpriteId);
	pRenderer->GetSpriteManager().SetModulate(uiFinalColour, m_uiEllipses);
	pRenderer->GetSpriteManager().SetVisible(true, m_uiEllipses);

}