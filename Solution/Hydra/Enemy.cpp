//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   Enemy.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "GameWindow.h"
#include "Scene.h"
#include "Macros.h"
#include "StrUtilities.h"
#include "D3DRenderer.h"
#include "INIParser.h"
#include "Event.h"
#include "Waypoint.h"
#include "Player.h"

#include "SoundSystem.h"
#include "Application.h"
#include "StaticObject.h"
#include "AnimatedObject.h"
#include "SpriteManager.h"
#include "DeviceManager.h"
#include "ParticleManager.h"
#include "ParticleInterface.h"
#include "vector3.h"
#include "Utility.h"


// This Include
#include "Enemy.h"


// Static Variables
CINIParser*  CEnemy::s_pEnemyIniParser  = 0;
unsigned int CEnemy::s_uiEnemyReffCount = 0;


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Enemy class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CEnemy::CEnemy()
: m_pRenderer(0)
, m_pIObjEnemy(0)
, m_uiSpriteHealthBar(0)
, m_kcpEnemyType(0)
, m_kpTargetWaypoint(0)
, m_uiBountyValue(0)
, m_fHealth(0)
, m_fHealthRegen(0)
, m_fDefaultHealth(0)
, m_fDefaultMovementVelocity(0)
, m_fToBeDefaultHealth(0)
, m_fToBeDefaultMovementVelocity(0)
, m_fLifeTimeElapsed(0)
, m_fCriticalColourTimer(0)
, m_fLastDistanceToWaypoint(0)
, m_bAlive(false)
, m_bFrostEffect(false)
{
	//Add reff
	++ s_uiEnemyReffCount;


	//Check if this is the first instance
	if (s_uiEnemyReffCount == 1)
	{
		//Load the tower ini parser
		LoadEnemyIniParser();
	}
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Enemy class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CEnemy::~CEnemy()
{
	Deinitialise();


	//Remove reff
	-- s_uiEnemyReffCount;


	//Check if this was the last instance
	if (s_uiEnemyReffCount == 0)
	{
		//Delete tower ini parser
		FW_DELETE(s_pEnemyIniParser);
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function initialises the class instance before use.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CEnemy::Initialise(CD3DRenderer* _pRenderer)
{
	//Set member variables
	m_pRenderer = _pRenderer;


	//Run initialsie functions
	IntiialiseHealthBar();


	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function runs process functions for the enemy class.
*
* @author Bryce Booth
* @param  _fDeltaTick	The time elasped since last process
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemy::Process(float _fDeltaTick)
{
	//Process enemy still alive
	ProcessAlive();

	//Check enemy is alive
	if (m_bAlive == true)
	{
		//Process waypoint
		ProcessTargetWaypoint();


		//Process health regen
		ProcessHealthRegen(_fDeltaTick);


		//Process poison effect
		ProcessPoisonEffect(_fDeltaTick);


		//Process frost effect
		ProcessFrostEffect(_fDeltaTick);


		//Process current target waypoint
		ProcessTargetWaypoint();	
	}


	//Process enemy still alive after effects
	ProcessAlive();


	//Process super class CEntity
	CEntity::Process(_fDeltaTick);


	//Process mesh object
	m_pIObjEnemy->Process(_fDeltaTick);


	//Process health bar
	ProcessHealthBar();


	//Increment life timer
	m_fLifeTimeElapsed += _fDeltaTick;


	//Process critical colour
	ProcessCriticalColour(_fDeltaTick);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will call on the renderer to draw meshes.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemy::Draw(CD3DRenderer* _pRenderer)
{
	//Draw mesh file
	m_pIObjEnemy->CopyPosition(this);
	m_pIObjEnemy->CopyOrientation(this);
	m_pIObjEnemy->Draw(_pRenderer, this);

	//Display the Frost Particles
	if(m_bFrostEffect)
	{
		for (int i = 0; i < 2; ++i)
		{
			float fXDirection = MathUtility::RandomNumber(-0.5f, 0.5f);
			float fYDirection = MathUtility::RandomNumber(-0.5f, 0.5f);
			float fZDirection = MathUtility::RandomNumber(-0.5f, 0.5f);
			CVector3 Vec(fXDirection, fYDirection, fZDirection);
			CVector3 ThisPos;
			float fXPos = MathUtility::RandomNumber(-0.1f, 0.1f);
			float fYPos = MathUtility::RandomNumber(-0.1f, 0.1f);
			float fZPos = MathUtility::RandomNumber(-0.1f, 0.1f);
			this->GetWorldMatrix().GetPosition(ThisPos);
			ThisPos.x += fXPos;
			ThisPos.y += fYPos;
			ThisPos.z += fZPos;
			m_pRenderer->GetParticleManager().GetParticleInterface().CreateFrost(ThisPos, Vec, 0.5f);
		}
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will change the enemies member variables to kill the enemy.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemy::Kill(bool _bHitLastWaypoint)
{
	if(m_bAlive == true)
	{
		//Set dead
		m_bAlive = false;


		if (_bHitLastWaypoint == false)
		{
			//Create death event
			CEvent EventDeath(EVENTSUBJECT_ENEMYDEATH);
			EventDeath.SetData(this);

			//Play death sound
			CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Enemy-Death.wav");


			//CApplication::GetInstance().GetGameWindow().GetCurrentMainScene().GetSoundSystem()->NewSound2DInstant("Assets/Sounds/Windows XP Ding.wav");

			
			//Send death event to targets
			SendEventToTargets(EventDeath);
		}

		for(int i = 0; i < 50; ++i)
		{
			float fXDirection = MathUtility::RandomNumber(-1.0f, 1.0f);
			float fYDirection = MathUtility::RandomNumber(-1.0f, 1.0f);
			float fZDirection = MathUtility::RandomNumber(-1.0f, 1.0f);
			CVector3 Vec(fXDirection, fYDirection, fZDirection);
			CVector3 ThisPos;
			this->GetWorldMatrix().GetPosition(ThisPos);
			m_pRenderer->GetParticleManager().GetParticleInterface().CreateFire(ThisPos, Vec, 0.75f);
		}

		//Turn off health bar
		m_pRenderer->GetSpriteManager().SetVisible(false, m_uiSpriteHealthBar);
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will revive the enemy by restoring default variables.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemy::Revive()
{
	//Restore enemy back to default
	RestoreDefaultVariables();


	//Set Alive
	m_bAlive = true;


	//Make health bar visiable
	m_pRenderer->GetSpriteManager().SetVisible(true, m_uiSpriteHealthBar);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will set the current waypoint that the enemy will be tracking.
*
* @author Bryce Booth
* @param  _kpWaypoint	Pointer to waypoint instance
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemy::SetWaypoint(const CWaypoint* _kpWaypoint)
{
	//Check waypoint instance valid
	if (_kpWaypoint)
	{
		//Set member variables
		m_kpTargetWaypoint = _kpWaypoint;
		

		//Get waypoint position
		CVector3 v3TargetPosition;
		v3TargetPosition = m_kpTargetWaypoint->GetPosition();


		//Look at position
		CEntity::LookAt(v3TargetPosition);
	}
	else
	{
		if(m_bAlive == true)
		{
			//Create hit last waypoint event
			CEvent EventHitLastWaypoint(EVENTSUBJECT_ENEMYLASTWAYPOINT);


			//Set event data
			EventHitLastWaypoint.SetData(this);
			

			//Send hit last waypoint event to targets
			SendEventToTargets(EventHitLastWaypoint);

			//Kill enemy
			Kill(true);
		}
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Changes the enemy to different enemy type.
*
* @author Bryce Booth
* @param _pRenderer		Renderer of the window
* @param _kcpEnemyType	Enemy type to be loaded from ini
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemy::ChangeType(CD3DRenderer* _pRenderer, const char* _kcpEnemyType, unsigned int _uiWaveNumber)
{
	//Clean up
	delete[] m_kcpEnemyType;
	m_kcpEnemyType = 0;


	//Set defailt variables
	char* cpEnemyMeshFile = 0;
	bool bMeshAnimated = false;

	
	//Set member variables
	m_pRenderer = _pRenderer;
	StrUtilities::Copy(_kcpEnemyType, m_kcpEnemyType);


	//Run initialsie functions
	InitialiseEnemyIniData(cpEnemyMeshFile, bMeshAnimated);
	InitialiseMesh(_pRenderer, cpEnemyMeshFile, bMeshAnimated);


	m_fToBeDefaultHealth = (m_fDefaultHealth + (((_uiWaveNumber * _uiWaveNumber) / 10) * m_fDefaultHealth));
	m_fToBeDefaultMovementVelocity = (m_fDefaultMovementVelocity + ((_uiWaveNumber / 100) * m_fDefaultMovementVelocity));


	//Delete variables
	delete[] cpEnemyMeshFile;
	cpEnemyMeshFile = 0;
}








/********************************
            Protected
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will load the enemy variables from the ini parser.
*
* @author Bryce Booth
* @param  _cprEnemyMeshFile		Returned file path of enemy mesh file (is freestore allocated, so it must be deleted).
* @return bool					States function execution succeeded or failed
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CEnemy::InitialiseEnemyIniData(char*& _cprEnemyMeshFile, bool& _brMeshFileAnimated)
{
	//Setup default variables
	std::string strEnemyMeshFile;
	bool bLoadedHealth			 = false;
	bool bLoadedMovementVelocity = false;
	bool bLoadedBountyValue		 = false;
	bool bLoadedMeshFile		 = false;
	bool bLoadedRadius			 = false;
	bool bLoadedLifeRegen		 = false;
	bool bLoadedMeshFileAnimated = false;


	//Load enemy ini data values
	bLoadedHealth			= s_pEnemyIniParser->GetValue(m_kcpEnemyType, "Health"			, m_fDefaultHealth);
	bLoadedRadius			= s_pEnemyIniParser->GetValue(m_kcpEnemyType, "Radius"			, CEntity::m_fRadius);
	bLoadedMovementVelocity = s_pEnemyIniParser->GetValue(m_kcpEnemyType, "MovementVelocity", m_fDefaultMovementVelocity);
	bLoadedBountyValue		= s_pEnemyIniParser->GetValue(m_kcpEnemyType, "BountyValue"		, m_uiBountyValue);
	bLoadedMeshFile			= s_pEnemyIniParser->GetValue(m_kcpEnemyType, "MeshFile"		, strEnemyMeshFile);
	bLoadedLifeRegen		= s_pEnemyIniParser->GetValue(m_kcpEnemyType, "HealthRegen"		, m_fHealthRegen);
	bLoadedMeshFileAnimated = s_pEnemyIniParser->GetValue(m_kcpEnemyType, "MeshFileAnimated", _brMeshFileAnimated);
	
	
	//Check all tower data exists
	LOG_FATALERROR(bLoadedHealth == false			, "Could not load enemy health.");
	LOG_FATALERROR(bLoadedMovementVelocity  == false, "Could not load enemy movement velocity.");
	LOG_FATALERROR(bLoadedBountyValue == false      , "Could not load enemy bounty value.");
	LOG_FATALERROR(bLoadedMeshFile == false		    , "Could not load enemy mesh file path.");
	LOG_FATALERROR(bLoadedLifeRegen == false	    , "Could not load enemy health regen value.");
	LOG_FATALERROR(bLoadedMeshFileAnimated == false , "Could not load enemy mesh file animated.");


	//Check ini data values are valid
	LOG_FATALERROR(m_fDefaultHealth <= 0			 , "The enemy health is invalid.");
	LOG_FATALERROR(CEntity::m_fRadius <= 0		     , "The enemy radius is invalid.");
	LOG_FATALERROR(m_fDefaultMovementVelocity <= 0.0f, "The enemy movement velocity is invalid.");


	//Copy string values
	StrUtilities::Copy(strEnemyMeshFile.c_str(), _cprEnemyMeshFile);


	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will create the mesh for the enemy.
*
* @author Bryce Booth
* @param _pRenderer			Renderer instance of the window.
* @param _kcpEnemyMeshFile	Enemy mesh file path.
* @param _uirMeshId			Returned mesh id of created mesh.
* return bool				States if function execution succeeded or failed
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CEnemy::InitialiseMesh(CD3DRenderer* _pRenderer, const char* _kcpEnemyMeshFile, bool _bMeshAnimated)
{
	FW_DELETE(m_pIObjEnemy);


	//Check if mesh is animated
	if (_bMeshAnimated == true)
	{
		//Instance animated object
		m_pIObjEnemy = new CAnimatedObject();
	}
	else
	{
		//Instance static object
		m_pIObjEnemy = new CStaticObject();
	}


	//Create tower name
	char* cpBuffer = new char[128];
	sprintf_s(cpBuffer, 128, "%s  %d", m_kcpEnemyType, s_uiEnemyReffCount);


	//Initialise instance object
	m_pIObjEnemy->Initialise(cpBuffer, _pRenderer, _kcpEnemyMeshFile);


	//Set pre draw and post draw call backs
	m_pIObjEnemy->SetPredrawCallback(&CEnemy::PreDraw);
	m_pIObjEnemy->SetPostdrawCallback(&CEnemy::PostDraw);


	//Delete variables
	delete[] cpBuffer;
	cpBuffer = 0;


	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* This function intiailises the health bar for the enemy
*
* @author Bryce Booth
* return bool			States if function execution succeeded or failed
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CEnemy::IntiialiseHealthBar()
{
	m_uiSpriteHealthBar = m_pRenderer->GetSpriteManager().AddSprite(L"Assets/Sprites/HealthBar.png");
	m_pRenderer->GetSpriteManager().SetObjectSpace(true, m_uiSpriteHealthBar);
	m_pRenderer->GetSpriteManager().SetVisible(false, m_uiSpriteHealthBar);


	return (true);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function calculates the health regeneration value for the enemy.
*
* @author Bryce Booth
* @param  _fDeltaTick	The time elasped since last process
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemy::ProcessHealthRegen(float _fDeltaTick)
{
	//Calculate health regen amount
	float fRegenAmount = m_fHealthRegen;
	fRegenAmount *= _fDeltaTick;


	//Add regen to health
	m_fHealth += fRegenAmount;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will process the poison effect aquired from projectiles.
*
* @author Bryce Booth
* @param  _fDeltaTick	The time elasped since last process
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemy::ProcessPoisonEffect(float _fDeltaTick)
{
	//Check poison timer not negitive
	if (m_fPoisonTimer > 0.0f)
	{
		//Decrement poison timer
		m_fPoisonTimer -= _fDeltaTick;


		//Calculate poison tick damage
		float fPoisonDamage = m_fPoisonTickDamage;
		fPoisonDamage *= _fDeltaTick;


		//Decrement health by poison tick damage
		m_fHealth -= fPoisonDamage;

		
		float fXDirection = MathUtility::RandomNumber(-1.0f, 1.0f);
		float fYDirection = MathUtility::RandomNumber(2.0f, 2.0f);
		float fZDirection = MathUtility::RandomNumber(-1.0f, 1.0f);
		CVector3 Vec(fXDirection, fYDirection, fZDirection);
		CVector3 ThisPos;
		float fXPos = MathUtility::RandomNumber(-0.1f, 0.1f);
		float fYPos = MathUtility::RandomNumber(-0.1f, 0.1f);
		float fZPos = MathUtility::RandomNumber(-0.1f, 0.1f);
		this->GetWorldMatrix().GetPosition(ThisPos);
		ThisPos.x += fXPos;
		ThisPos.y += fYPos;
		ThisPos.z += fZPos;
		m_pRenderer->GetParticleManager().GetParticleInterface().CreatePoison(ThisPos, Vec, 0.5f);	
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will checks the enemy's life state.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemy::ProcessAlive()
{
	//Check health equal or smaller then zero
	if (m_fHealth <= 0.0f)
	{
		//Kill the enemy
		Kill();
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will check if the enemy has reached the current target waypoint. A new waypoint will be set if it has.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemy::ProcessTargetWaypoint()
{
	if (m_kpTargetWaypoint)
	{
		const float kfDistanceToWaypoint = CEntity::GetSquaredDistanceTo(m_kpTargetWaypoint->GetPosition());


		//Check if enemy is intersecting with waypoint
		if (kfDistanceToWaypoint > m_fLastDistanceToWaypoint)
		{
			//Set next waypoint
			SetWaypoint(m_kpTargetWaypoint->GetNextWaypoint());

			
			if (m_kpTargetWaypoint)
			{
				m_fLastDistanceToWaypoint = CEntity::GetSquaredDistanceTo(m_kpTargetWaypoint->GetPosition());
			}
		}
		else
		{
			m_fLastDistanceToWaypoint = kfDistanceToWaypoint;
		}
	}
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will process the enemies health into a percent ratio and modify the health bar based on the result.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemy::ProcessHealthBar()
{
	//Get self position
	CVector3 v3Position;
	CEntity::m_mtxWorldMatrix.GetPosition(v3Position);

	//Increment health bar position
	v3Position.y += 1.5f;

	if( strcmp(m_kcpEnemyType, "Boss Enemy") == 0)
	{
		v3Position.y += 1.8f;
	}


	//Update new health bar position
	m_pRenderer->GetSpriteManager().SetPosition(v3Position, m_uiSpriteHealthBar);


	//Setup default variables
	RECT Drawbounds;
	ZeroMemory(&Drawbounds, sizeof(RECT));
	Drawbounds.bottom = 16;
	float fHealthWidth = 32;
	
	
	//Calculate enemy health in percentage
	float fPercentage = 1.0f - ((m_fHealth / m_fToBeDefaultHealth));

	
	//Calculate new health bar rect
	Drawbounds.left += static_cast<long>(fHealthWidth * fPercentage);
	Drawbounds.right = static_cast<long>(32 + fHealthWidth * fPercentage);


	//Update health bar rect
	m_pRenderer->GetSpriteManager().SetRect(&Drawbounds, m_uiSpriteHealthBar);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Processes the colour blending for towers that have critical striked.
*
* @author Bryce Booth
* _fDeltaTick	Time since last frame.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemy::ProcessCriticalColour(float _fDeltaTick)
{
	if (m_fCriticalColourTimer > 0.0f)
	{
		//Decrement timer
		m_fCriticalColourTimer -= _fDeltaTick;
	}
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will check if the enemy is affect by frost or poision. If the enemy is, then changes to the device
* manager will be made to show the effect visually.
*
* @author Bryce Booth
* @param _pRenderer	 The renderer for the window
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemy::PreDraw(void* _pEnemy, CD3DRenderer* _pRenderer)
{
	//Set default variables
	unsigned long ulTextureFactor = 0;
	float fEnemyPoisonTimer = 0.0f;
	float fEnemyFrostTimer = 0.0f;
	float fEnemyCriticalTimer = 0.0f;
	CEnemy* pEnemy = static_cast<CEnemy*>(_pEnemy);


	fEnemyPoisonTimer = pEnemy->GetPoisonTimer();
	fEnemyFrostTimer = pEnemy->GetFrostTimer();
	fEnemyCriticalTimer = pEnemy->GetCriticalColourTimer();


	//Check enemy has both frost and poison effects active
	if (fEnemyPoisonTimer > 0.0f && fEnemyFrostTimer > 0.0f)
	{
		ulTextureFactor = 0xFF207149;
	}
	else
	{
		//Check enemy has frost effect active
		if (fEnemyCriticalTimer > 0.0f)
		{
			ulTextureFactor = 0xFFFF0000;
		}
		else if (fEnemyFrostTimer > 0.0f)
		{
			ulTextureFactor = 0xFF0077FF;
		}
		//Check enemy has poison effect active
		else if (fEnemyPoisonTimer > 0.0f)
		{
			ulTextureFactor = 0xFF008800;
		}
	}


	//Check if there is a texture factor
	if (ulTextureFactor != 0)
	{
		//Set device states
		_pRenderer->GetDeviceManager().SetRenderState(D3DRS_TEXTUREFACTOR, ulTextureFactor);
		_pRenderer->GetDeviceManager().SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_ADD);
		_pRenderer->GetDeviceManager().SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);
		_pRenderer->GetDeviceManager().SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_TFACTOR);
	}
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will reset any device changes made within predraw.
*
* @author Bryce Booth
* @param _pRenderer	 The renderer for the window
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemy::PostDraw(void* _pEnemy, CD3DRenderer* _pRenderer)
{
	_pRenderer->GetDeviceManager().ResetTextureStageStates(0);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will change the enemy's movement velocity when the enemy is hit by a projectile that has the frost effect.
*
* @author Bryce Booth
* @param  _fFrostPenaltyRatio	The ratio to cut the enemy's movement velocity by.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemy::TurnOnFrostEffect(float _fFrostPenaltyRatio)
{
	//Reset movement velocity
	CEntity::m_v3MovementVelocity.z  = m_fDefaultMovementVelocity;


	//Scale movement velocity by penalty amount
	CEntity::m_v3MovementVelocity.z *= _fFrostPenaltyRatio;

	//Sets the frost particles to display 
	m_bFrostEffect = true;
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will restore the enemy's default movement velocity when the frost effect is removed.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemy::TurnOffFrostEffect()
{
	//Restore default movement velocity
	CEntity::m_v3MovementVelocity.z  = m_fDefaultMovementVelocity;

	//turns the frost particles off
	m_bFrostEffect = false;
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will run death visual effects for when the enemy dies.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemy::ExecuteDeathEffect()
{
	//Empty
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will resotre the enemy's member variables to default state.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemy::RestoreDefaultVariables()
{
	//Set new default variables
	//m_fDefaultMovementVelocity = m_fToBeDefaultMovementVelocity;
	//m_fDefaultHealth = m_fToBeDefaultHealth;


	//Reset life timer
	m_fLifeTimeElapsed = 0.0f;


	//Reset varaibles
	m_fCriticalColourTimer = 0.0f;


	//Restore default movement velocity
	CEntity::m_v3MovementVelocity.z  = m_fToBeDefaultMovementVelocity;


	//Restore default health
	m_fHealth = m_fToBeDefaultHealth;


	m_fLastDistanceToWaypoint = 100000.0f;


	//Reset effect target
	CEffectTarget::m_fPoisonTimer = 0.0f;
	CEffectTarget::m_fFrostTimer = 0.0f;
	CEffectTarget::m_fPoisonTickDamage = 0.0f;
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
CEnemy::Deinitialise()
{
	//Delete health bar
	m_pRenderer->GetSpriteManager().RemoveSprite(m_uiSpriteHealthBar);


	delete[] m_kcpEnemyType;
	m_kcpEnemyType = 0;

	FW_DELETE(m_pIObjEnemy);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will load the ini parser that contains all enemy related data.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemy::LoadEnemyIniParser()
{
	//Setup default variables
	bool bLoadSuccessful = false;


	//Instance ini parser
	s_pEnemyIniParser = new CINIParser();


	//Load tower ini file
	bLoadSuccessful = s_pEnemyIniParser->LoadINIFile("Ini Files/Enemy Data.ini");


	//Check ini parser file was loaded
	LOG_FATALERROR(bLoadSuccessful == false, "Could not load the enemy ini file");
}