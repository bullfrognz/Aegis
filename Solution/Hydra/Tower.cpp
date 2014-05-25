//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   Tower.cpp
//d
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <string>
#include <cmath>


// Local Includes
#include "Macros.h"
#include "IniParser.h"
#include "Event.h"
#include "EnemySpawner.h"
#include "Enemy.h"
#include "D3DRenderer.h"
#include "MeshManager.h"
#include "StrUtilities.h"
#include "EventSender.h"
#include "Projectile.h"
#include "StaticObject.h"
#include "AnimatedObject.h"
#include "SoundSystem.h"

#include "ParticleManager.h"
#include "ParticleInterface.h"
#include "vector3.h"
#include "Utility.h"


// This Include
#include "Tower.h"


// Static Variables
CINIParser*  CTower::s_pTowerIniParser  = 0;
unsigned int CTower::s_uiTowerReffCount = 0;
bool         CTower::s_bShadowsEnabled  = false;


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Tower class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CTower::CTower()
: m_pRenderer(0)
, m_kcpTowerType(0)
, m_cpSndFire(0)
, m_ppTargetEnemy(0)
, m_pObjTracker(0)
, m_uiMaxTargets(0)
, m_uiMaxActiveTargetId(0)
, m_uiBuildCost(0)
, m_uiTowerEmitterType(0)
, m_fRange(0)
, m_fFireRate(0)
, m_fFireTimer(0)
, m_fEmitterTime(0)
, m_pWeapon(0)
{
	//Add reff
	++ s_uiTowerReffCount;


	//Check if this is the first instance
	if (s_uiTowerReffCount == 1)
	{
		//Load the tower ini parser
		LoadTowerIniParser();
	}
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Tower class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CTower::~CTower()
{
	Deinitialise();


	//Remove reff
	-- s_uiTowerReffCount;


	//Check if this was the last instance
	if (s_uiTowerReffCount == 0)
	{
		//Delete tower ini parser
		FW_DELETE(s_pTowerIniParser);
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function initialisings the class instance before use.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CTower::Initialise(CD3DRenderer* _pRenderer, const char* _kcpTowerType)
{
	//Set defailt variables
	char* cpMeshFile = 0;
	char* cpTrackerMeshFile = 0;
	TWeaponData tWeaponData;
	TProjectileData tProjectileData;
	m_pRenderer = _pRenderer;
	CEntity::m_fRadius = 1.0f;
	bool bMeshAnimated = false;


	//Set member variables
	StrUtilities::Copy(_kcpTowerType, m_kcpTowerType);


	//Run intiailise functions
	InitialiseTowerIniData(cpMeshFile, bMeshAnimated, cpTrackerMeshFile);
	InitialiseTowerEmitterIni();
	IntiailiseObject(_pRenderer, cpMeshFile, bMeshAnimated);
	InitialiseTracker(_pRenderer, cpTrackerMeshFile);
	InitialiseMaxTargets();
	InitialiseProjectileIniData(tProjectileData);
	InitialiseProjectileEffectIniData(tProjectileData);
	InitialiseWeaponIniData(_pRenderer, tWeaponData);
	InitialiseWeapon(_pRenderer, tWeaponData, tProjectileData);


	//Delete variables
	FW_ADELETE(cpMeshFile);
	FW_ADELETE(cpTrackerMeshFile);


	//Register for events
	CEventTarget::Register(EVENTSUBJECT_ENEMYDEATH);
	CEventTarget::Register(EVENTSUBJECT_ENEMYLASTWAYPOINT);


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
CTower::Process(float _fDeltaTick)
{
	//Check object tracker valid
	if (m_pObjTracker)
	{
		//Process tracker
		ProcessTracker(_fDeltaTick);
	}


	//Process weapon
	m_pWeapon->Process(_fDeltaTick);


	//Set default varuiables
	unsigned int uiHighestActiveTargetId = 0;
	bool bAttackedEnemy = false;


	//Increment fire timer
	m_fFireTimer += _fDeltaTick;


	//Loop trough max target id
	for (unsigned int i = 0; i <= m_uiMaxActiveTargetId; ++i)
	{
		//Process target
		ProcessTargetEnemyStatus(i);
	

		//Check tower target valid
		if (m_ppTargetEnemy[i])
		{
			//Check tower is ready to fire
			if (m_fFireTimer > m_fFireRate)
			{
				//Attack target
				FireWeaponAtEnemy(m_ppTargetEnemy[i]);


				//Set attacked enemy to true
				bAttackedEnemy = true;
			}

			
			//Remember the current highest active enemy id
			uiHighestActiveTargetId = i;
		}


		//Check index equals max active target id
		//Check index smaller then max targets
		if (i == m_uiMaxActiveTargetId && i < m_uiMaxTargets - 1)
		{
			//Check index does not have a target
			if (m_ppTargetEnemy[i + 1] == 0) 
			{
				//Find new target for index
				ProcessTargetEnemyStatus(i + 1);
			}
		}
	}


	//Set current max active target id
	m_uiMaxActiveTargetId = min(uiHighestActiveTargetId, m_uiMaxActiveTargetId);


	//Check tower had attacked an enemy
	if (bAttackedEnemy == true)
	{
		//Reset fire timer
		m_fFireTimer = 0;


		if (m_cpSndFire)
		{
			CSoundSystem::GetInstance()->NewSound2DInstant(m_cpSndFire);
		}
	}


	//Process derived class CEntity
	CEntity::Process(_fDeltaTick);


	//Process tower mesh
	m_pObjTower->Process(_fDeltaTick);


	//Check tower has frost emitter
	if (m_uiTowerEmitterType & TOWEREMITTER_FROST)
	{
		//Default variables
		CVector3 v3SelfPosition;
		CEntity::m_mtxWorldMatrix.GetPosition(v3SelfPosition);


		//Generate random direction
		CVector3 v3Direction(MathUtility::RandomNumber(-1.5f, 1.5f),
							 MathUtility::RandomNumber(-1.5f, 1.5f),
							 MathUtility::RandomNumber(-1.5f, 1.5f));


		//Calcualte emit position
		v3SelfPosition += m_v3EmitterOffset;


		//Draw particles
		m_pRenderer->GetParticleManager().GetParticleInterface().CreateFrostTower(v3SelfPosition, v3Direction, m_fEmitterTime);
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will call on the renderer to draw meshes.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CTower::Draw(CD3DRenderer* _pRenderer)
{
	//Draw tower object
	m_pObjTower->CopyPosition(this);
	m_pObjTower->CopyOrientation(this);
	m_pObjTower->Draw(_pRenderer);


	//Check object tracker valid
	if (m_pObjTracker)
	{
		m_pObjTracker->Draw(_pRenderer);
	}


	//Draw weapon
	m_pWeapon->Draw(_pRenderer);
}










/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will handle incomine events from event senders.
*
* @author Bryce Booth
* @param _kpEventData	Container for received event data
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CTower::HandleRecievedEvent(const CEvent* _kpEventData)
{
	int iEventDataSubject = _kpEventData->GetSubject();


	switch (iEventDataSubject)
	{
		case EVENTSUBJECT_ENEMYDEATH:
			{
				const CEnemy* kpEnemy = reinterpret_cast<const CEnemy*>(_kpEventData->GetData());


				if (IsEnemyTargeted(kpEnemy) == true)
				{
					RemoveTargetEnemy(kpEnemy);
				}
			}
			break;


		case EVENTSUBJECT_ENEMYLASTWAYPOINT:
			{
				const CEnemy* kpEnemy = reinterpret_cast<const CEnemy*>(_kpEventData->GetData());


				if (IsEnemyTargeted(kpEnemy) == true)
				{
					RemoveTargetEnemy(kpEnemy);
				}
			}
			break;


		default:
			break;
	}
}








/********************************
            Protected
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will retrieve data from the tower ini parser file for the tower.
*
* @author Bryce Booth
* @param _cprMeshFile			The file for the tower mesh
* @param _cprTrackerMeshFile	The file for the tower tracker mesh
* @return bool					States function execution succeeded or failed
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CTower::InitialiseTowerIniData(char*& _cprMeshFile, bool& _brMeshAnimated, char*& _cprTrackerMeshFile)
{
	//Setup default variables
	std::string strMeshFile;
	std::string strUpgradeToType1;
	std::string strUpgradeToType2;
	std::string strUpgradeToType3;
	std::string strWeaponType;
	std::string strTrackerMeshFile;
	std::string strSndFire;
	bool bLoadedRange		    = false;
	bool bLoadedFireRate	    = false;
	bool bLoadedTowerMeshFile   = false;
	bool bLoadedUpgradeToType   = false;
	bool bLoadedMaxTargets	    = false;
	bool bLoadedTrackerMeshFile = false;
	bool bLoadedTrackerOffset   = false;
	bool bLoadedWeaponOffset    = false;
	bool bLoadedMeshIfAnimated  = false;
	bool bLoadedBuildCost		= false;
	bool bLoadedSndFire			= false;


	//Load tower data from ini parser
	bLoadedRange		   = s_pTowerIniParser->GetValue(m_kcpTowerType, "Range"				, m_fRange);
	bLoadedFireRate		   = s_pTowerIniParser->GetValue(m_kcpTowerType, "FireRate"				, m_fFireRate);
	bLoadedTowerMeshFile   = s_pTowerIniParser->GetValue(m_kcpTowerType, "TowerMeshFile"		, strMeshFile);
	bLoadedUpgradeToType   = s_pTowerIniParser->GetValue(m_kcpTowerType, "UpgradeToType1"		, strUpgradeToType1);
	bLoadedUpgradeToType   = s_pTowerIniParser->GetValue(m_kcpTowerType, "UpgradeToType2"		, strUpgradeToType2);
	bLoadedUpgradeToType   = s_pTowerIniParser->GetValue(m_kcpTowerType, "UpgradeToType3"		, strUpgradeToType3);
	bLoadedMaxTargets	   = s_pTowerIniParser->GetValue(m_kcpTowerType, "MaxTargets"			, m_uiMaxTargets);
	bLoadedTrackerMeshFile = s_pTowerIniParser->GetValue(m_kcpTowerType, "TrackerMeshFile"		, strTrackerMeshFile);
	bLoadedTrackerOffset   = s_pTowerIniParser->GetValue(m_kcpTowerType, "TrackerMeshOffset"	, m_v3TrackerOffset);
	bLoadedWeaponOffset    = s_pTowerIniParser->GetValue(m_kcpTowerType, "WeaponOffset"			, m_v3WeaponOffset);
	bLoadedMeshIfAnimated  = s_pTowerIniParser->GetValue(m_kcpTowerType, "TowerMeshFileAnimated", _brMeshAnimated);
	bLoadedBuildCost       = s_pTowerIniParser->GetValue(m_kcpTowerType, "Value"				, m_uiBuildCost);
	bLoadedSndFire         = s_pTowerIniParser->GetValue(m_kcpTowerType, "SndFireProjectile"	, strSndFire);
	
	
	//Check tower data loaded successfully
	LOG_FATALERROR(bLoadedRange == false	     , "Could not load tower range.");
	LOG_FATALERROR(bLoadedFireRate == false		 , "Could not load tower fire rate.");
	LOG_FATALERROR(bLoadedTowerMeshFile == false , "Could not load tower mesh file.");
	LOG_FATALERROR(bLoadedMaxTargets == false	 , "Could not load tower max targets.");
	LOG_FATALERROR(bLoadedWeaponOffset == false	 , "Could not load weapon offset.");
	LOG_FATALERROR(bLoadedMeshIfAnimated == false, "Could not load if mesh animated.");
	LOG_FATALERROR(bLoadedTrackerMeshFile == true && bLoadedTrackerOffset == false, "Missing tracker mesh offset.");


	//Check tower data is valid
	LOG_FATALERROR(m_fRange <= 0	  , "The tower range is invalid.");
	LOG_FATALERROR(m_fFireRate <= 0	  , "The tower fire rate is invalid.");
	LOG_FATALERROR(m_uiMaxTargets == 0, "The tower max targets is invalid.");


	//Copy string values
	StrUtilities::Copy(strMeshFile.c_str()       , _cprMeshFile);
	StrUtilities::Copy(strTrackerMeshFile.c_str(), _cprTrackerMeshFile);
	StrUtilities::Copy(strSndFire.c_str(), m_cpSndFire);


	if (strUpgradeToType1.length() > 0)
	{
		char* cpBuffer = 0;
		StrUtilities::Copy(strUpgradeToType1.c_str(), cpBuffer);
		m_vecUpgradeTowerTypes.push_back(cpBuffer);

	}


	if (strUpgradeToType2.length() > 0)
	{
		char* cpBuffer = 0;
		StrUtilities::Copy(strUpgradeToType2.c_str(), cpBuffer);
		m_vecUpgradeTowerTypes.push_back(cpBuffer);
	}


	if (strUpgradeToType3.length() > 0)
	{
		char* cpBuffer = 0;
		StrUtilities::Copy(strUpgradeToType3.c_str(), cpBuffer);
		m_vecUpgradeTowerTypes.push_back(cpBuffer);
	}


	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will load the emitter type that the tower has if any.
*
* @author Bryce Booth
* @return bool		States function execution succeeded or failed
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CTower::InitialiseTowerEmitterIni()
{
	//Default variables
	bool bLoadedEmitterType	  = false;
	bool bLoadedEmitterOffset = false;
	bool bLoadedEmitterTime   = false;


	//Load tower data from ini parser
	bLoadedEmitterType	 = s_pTowerIniParser->GetValue(m_kcpTowerType, "EmitterType"  , m_uiTowerEmitterType);
	bLoadedEmitterOffset = s_pTowerIniParser->GetValue(m_kcpTowerType, "EmitterOffset", m_v3EmitterOffset);
	bLoadedEmitterTime   = s_pTowerIniParser->GetValue(m_kcpTowerType, "EmitterTime", m_fEmitterTime);


	//Check if tower has emitter
	if (bLoadedEmitterType != TOWEREMITTER_NONE)
	{
		//Check emitter time valid
		LOG_FATALERROR(bLoadedEmitterTime == false, "Could not loaded emitter time.");
	}


	return (true);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will create a mesh for the tower object and initialise the tower object.
*
* @author Bryce Booth
* @param _pRenderer			    The renderer for the window
* @param _kcpTrackerMeshFile	The file for the tower object mesh
* @return bool					States function execution succeeded or failed
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CTower::IntiailiseObject(CD3DRenderer* _pRenderer, char* _cpMeshFile, bool _bMeshAnimated)
{
	//Check if mesh is animated
	if (_bMeshAnimated == true)
	{
		//Instance animated object
		m_pObjTower = new CAnimatedObject();
	}
	else
	{
		//Instance static object
		m_pObjTower = new CStaticObject();
	}


	//Create tower name
	//TODO
	//Mismatched alloc/ dealloc
	char* cpBuffer = new char[128];
	sprintf_s(cpBuffer, 128, "%s %d", m_kcpTowerType, s_uiTowerReffCount);


	//Initialise instance object
	m_pObjTower->Initialise(cpBuffer, _pRenderer, _cpMeshFile);


	//Delete variables
	FW_ADELETE(cpBuffer);


	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will create a mesh for the tower tracker object and initialise the tracker object.
*
* @author Bryce Booth
* @param _pRenderer			    The renderer for the window
* @param _kcpTrackerMeshFile	The file for the tower tracker mesh
* @return bool					States function execution succeeded or failed
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CTower::InitialiseTracker(CD3DRenderer* _pRenderer, const char* _kcpTrackerMeshFile)
{
	//Check tracker mesh exists for this tower
	if (_kcpTrackerMeshFile && strlen(_kcpTrackerMeshFile) > 0)
	{
		//Convert string to wchar
		wchar_t* wcpTrackerMeshFile = 0;
		StrUtilities::ConvertToWChar(_kcpTrackerMeshFile, wcpTrackerMeshFile);


		//Load mesh file
		unsigned int uiMeshId = _pRenderer->GetMeshManager().CreateNewMesh(wcpTrackerMeshFile);


		//Create object name
		char cBuffer[128];
		sprintf_s(cBuffer, 128, "%s Tracker %d", m_kcpTowerType, s_uiTowerReffCount);


		//Instance object
		m_pObjTracker = new CStaticObject();


		//Initialise object
		m_pObjTracker->Initialise(cBuffer, _pRenderer, uiMeshId);
		

		//Delete converted string
		delete[] wcpTrackerMeshFile;
		wcpTrackerMeshFile = 0;
	}


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
CTower::InitialiseMaxTargets()
{
	//Instance enemy pointers
	m_ppTargetEnemy = new CEnemy*[m_uiMaxTargets];


	//Clean memory
	FW_FILLARRAY(m_ppTargetEnemy, m_uiMaxTargets, 0);


	return (true);
}










/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will load ini data for the tower projectiles.
*
* @author Bryce Booth
* _trProjectileData		Container for the projectile data
* @return bool			States function execution succeeded or failed
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool 
CTower::InitialiseProjectileIniData(TProjectileData& _trProjectileData)
{
	//Setup default variables
	std::string strMeshFile;
	std::string strSndHit;
	bool bLoadedRadius			 = false;
	bool bLoadedMovementVelocity = false;
	bool bLoadedMeshFile		 = false;
	bool bLoadedIfAnimatedMesh   = false;
	bool bLoadedAngularVelocity  = false;
	bool bLoadedSndProjectileHit = false;
	bool bLoadedEmitterType = false;


	//Load projectile ini data
	bLoadedRadius           = s_pTowerIniParser->GetValue(m_kcpTowerType, "Radius"		      , _trProjectileData.m_fRadius);
	bLoadedMovementVelocity = s_pTowerIniParser->GetValue(m_kcpTowerType, "MovementVelocity"  , _trProjectileData.m_fMovementVelocity);
	bLoadedMeshFile         = s_pTowerIniParser->GetValue(m_kcpTowerType, "ProjectileMeshFile", strMeshFile);
	bLoadedIfAnimatedMesh   = s_pTowerIniParser->GetValue(m_kcpTowerType, "ProjectileMeshFileAnimated", _trProjectileData.m_bAnimatedMesh);
	bLoadedAngularVelocity  = s_pTowerIniParser->GetValue(m_kcpTowerType, "AngularVelocity", _trProjectileData.m_v3AngularVelocity);
	bLoadedSndProjectileHit = s_pTowerIniParser->GetValue(m_kcpTowerType, "SndProjectileHit", strSndHit);
	bLoadedEmitterType      = s_pTowerIniParser->GetValue(m_kcpTowerType, "ProjectileEmitterType", _trProjectileData.m_uiEmitterType);
	
	
	//Check projectile data exists
	LOG_FATALERROR(bLoadedRadius == false		   , "Could not load projectile radius.");
	LOG_FATALERROR(bLoadedMovementVelocity == false, "Could not load projectile movement velocity.");
	LOG_FATALERROR(bLoadedMeshFile == false		   , "Could not load projectile mesh file.");
	LOG_FATALERROR(bLoadedIfAnimatedMesh == false  , "Could not load projectile mesh file animated.");


	//Check ini data values are valid
	LOG_FATALERROR(_trProjectileData.m_fRadius <= 0.0f , "The projectile radius is invalid");
	LOG_ERROR(_trProjectileData.m_fMovementVelocity < CProjectile::GetMinMovementVelocity(), "The projectile movement velocity is too low.");
	LOG_ERROR(_trProjectileData.m_fMovementVelocity > CProjectile::GetMaxMovementVelocity(), "The projectile movement velocity is too high.");


	//Copy string values
	StrUtilities::Copy(strMeshFile.c_str(), _trProjectileData.m_kcpMeshFile);
	StrUtilities::Copy(strSndHit.c_str(), _trProjectileData.m_cpSndHit);


	return (true);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will load ini data for the projectile effects.
*
* @author Bryce Booth
* _trProjectileData		Container for the projectile data
* @return bool			States function execution succeeded or failed
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool 
CTower::InitialiseProjectileEffectIniData(TProjectileData& _trProjectileData)
{
	//Setup default variables
	bool bLoadedEffects           = false;
	bool bLoadedPoisonTickDamage  = false;
	bool bLoadedPoisonLength      = false;
	bool bLoadedFrostPenaltyRatio = false;
	bool bLoadedFrostLength       = false;
	bool bLoadedAreaOfEffect      = false;


	//Load projectile effect ini data
	bLoadedEffects			 = s_pTowerIniParser->GetValue(m_kcpTowerType, "Effects"	      , _trProjectileData.m_uiEffects);
	bLoadedPoisonTickDamage  = s_pTowerIniParser->GetValue(m_kcpTowerType, "PoisonTickDamage" , _trProjectileData.m_fPoisonTickDamage);
	bLoadedPoisonLength      = s_pTowerIniParser->GetValue(m_kcpTowerType, "PoisonLength"     , _trProjectileData.m_fPoisonLength);
	bLoadedFrostPenaltyRatio = s_pTowerIniParser->GetValue(m_kcpTowerType, "FrostPenaltyRatio", _trProjectileData.m_fFrostPenaltyRatio);
	bLoadedFrostLength		 = s_pTowerIniParser->GetValue(m_kcpTowerType, "FrostLength"	  , _trProjectileData.m_fFrostLength);
	bLoadedAreaOfEffect      = s_pTowerIniParser->GetValue(m_kcpTowerType, "AreaOfEffect"	  , _trProjectileData.m_fAreaOfEffect);
	
	
	//Check projectiles has poison effect
	if (_trProjectileData.m_uiEffects & EFFECTTYPE_POISON)
	{
		//Check poison effect data loaded successfully
		LOG_FATALERROR(bLoadedPoisonTickDamage == false, "Could not load projectile effect posion tick damage.");
		LOG_FATALERROR(bLoadedPoisonTickDamage == false, "Could not load projectile effect posion length.");


		//Check poison data is valid
		LOG_FATALERROR(_trProjectileData.m_fPoisonTickDamage <= 0.0f, "The projectile effect poison tick damage is invalid.");
		LOG_FATALERROR(_trProjectileData.m_fPoisonLength     <= 0.0f, "The projectile effect poison length is invalid.");
	}


	//Check projectiles has frost effect
	if (_trProjectileData.m_uiEffects & EFFECTTYPE_FROST)
	{
		//Check frost effect data loaded successfully
		LOG_FATALERROR(bLoadedFrostPenaltyRatio == false, "Could not load projectile effect frost penalty ratio.");
		LOG_FATALERROR(bLoadedFrostLength == false	    , "Could not load projectile effect frost length.");


		//Check frost data is valid
		LOG_FATALERROR(_trProjectileData.m_fFrostPenaltyRatio <= 0.0f, "The projectile effect frost penalty ratio is invalid.");
		LOG_FATALERROR(_trProjectileData.m_fFrostLength       <= 0.0f, "The projectile effect frost length is invalid.");
	}


	return (true);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will load ini data for the tower weapon.
*
* @author Bryce Booth
* _trProjectileData		Container for the weapon data
* @return bool			States function execution succeeded or failed
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool 
CTower::InitialiseWeaponIniData(CD3DRenderer* _pRenderer, TWeaponData& _trWeaponData)
{
	//Setup default variables
	bool bLoadedMinDamage	       = false;
	bool bLoadedMaxDamage	       = false;
	bool bLoadedCriticalRating     = false;
	bool bLoadedCriticalMultiplier = false;


	//Load weapon ini data
	bLoadedMinDamage	      = s_pTowerIniParser->GetValue(m_kcpTowerType, "MinDamage"	        , _trWeaponData.m_fMinDamage);
	bLoadedMaxDamage	      = s_pTowerIniParser->GetValue(m_kcpTowerType, "MaxDamage"	        , _trWeaponData.m_fMaxDamage);
	bLoadedCriticalRating     = s_pTowerIniParser->GetValue(m_kcpTowerType, "CriticalRating"    , _trWeaponData.m_uiCritialRating);
	bLoadedCriticalMultiplier = s_pTowerIniParser->GetValue(m_kcpTowerType, "CriticalMultiplier", _trWeaponData.m_fCriticalMultiplier);
	
	
	//Check weapon data loaded successfully
	LOG_FATALERROR(bLoadedMinDamage == false     , "Could not load weapon min damage.");
	LOG_FATALERROR(bLoadedMaxDamage == false     , "Could not load weapon max damage.");
	LOG_FATALERROR(bLoadedCriticalRating == false, "Could not load weapon critical rating.");


	//Check weapon data is valid
	LOG_FATALERROR(_trWeaponData.m_fMinDamage <= 0.0f, "The weapon min damage is invalid.");
	LOG_FATALERROR(_trWeaponData.m_fMaxDamage <= 0.0f, "The weapon max damage is invalid.");
	LOG_FATALERROR(_trWeaponData.m_fMinDamage > _trWeaponData.m_fMaxDamage , "The weapon min damage cannot be more then weapon max damage.");
	LOG_FATALERROR(_trWeaponData.m_uiCritialRating < 0.0f, "The weapon critical rating cannot be lower then 0.");
	LOG_FATALERROR(_trWeaponData.m_uiCritialRating > 100.0f, "The weapon critical rating cannot be higher then 100.");


	return (true);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will calculate the maxium projectiles that the tower can use and initialise the tower weapon instance.
*
* @author Bryce Booth
* @param _pRenderer		The renderer for the window
* _trProjectileData		Container for the weapon data
* _trProjectileData		Container for the projectile data
* @return bool			States function execution succeeded or failed
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool 
CTower::InitialiseWeapon(CD3DRenderer* _pRenderer, TWeaponData& _trWeaponData, TProjectileData& _trProjectileData)
{
	//Get the maxium projectile life
	float fMaxProjectileLife = CProjectile::GetMaxiumLifeSpan();


	//Calculate the maxium number of projectiles
	//that can be active at one time for this weapon
	float fMaxProjectiles = 1.0f;
	fMaxProjectiles *= fMaxProjectileLife;
	fMaxProjectiles /= m_fFireRate;
	fMaxProjectiles *= m_uiMaxTargets;


	//Get final number of projectiles
	_trWeaponData.m_uiMaxProjectiles =  static_cast<unsigned int>(ceil(fMaxProjectiles));


	//Instance weapon class
	m_pWeapon = new CWeapon();


	//Initialise weapon
	m_pWeapon->Initialise(_pRenderer, _trWeaponData, _trProjectileData);


	return (true);
}










/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will update the tracker objects direction towards the towers main target in 2d space.
*
* @author Bryce Booth
* @param  _fDeltaTick	The time elasped since last process
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CTower::ProcessTracker(float _fDeltaTick)
{
	//Get tower position
	CVector3 v3Position;


	CEntity::m_mtxWorldMatrix.GetPosition(v3Position);


	m_pObjTracker->GetWorldMatrix().SetPosition(v3Position);
	m_pObjTracker->GetWorldMatrix().TranslatePosition(m_v3TrackerOffset);
	m_pObjTracker->GetWorldMatrix().GetPosition(v3Position);


	m_pObjTracker->Process(_fDeltaTick);


	if (m_ppTargetEnemy[0])
	{
		CVector3 v3TargetPosition;
		m_ppTargetEnemy[0]->GetWorldMatrix().GetPosition(v3TargetPosition);

		v3TargetPosition.y = v3Position.y;


		m_pObjTracker->LookAt(v3TargetPosition);
	}
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will check the target status within the given index and run functionality based on the target state.
*
* @author Bryce Booth
* _uiTargetIndex	Index for the target enemy container
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CTower::ProcessTargetEnemyStatus(unsigned int _uiTargetIndex)
{
	//Check tower has target
	if (m_ppTargetEnemy[_uiTargetIndex] == 0)
	{
		//Find new target
		FindNewTargetEnemy(_uiTargetIndex);
	}
	else
	{
		//Check target is within range of tower
		bool bWithinRange = IsEnemyWithinTowerRange(m_ppTargetEnemy[_uiTargetIndex]);
 
	
		if (bWithinRange == false)
		{
			//Remove current target
			RemoveTargetEnemy(m_ppTargetEnemy[_uiTargetIndex]);


			//Find new target
			FindNewTargetEnemy(_uiTargetIndex);
		}
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will update the weapon emit position and call on the weapon to fire at given enemy.
*
* @author Bryce Booth
* _pEnemy	Enemy instance that the weapon will fire at
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CTower::FireWeaponAtEnemy(CEnemy* _pEnemy)
{
	//Set default variables
	CVector3 v3WeaponEmitPosition;
	CVector3 v3TranslationX;
	CVector3 v3TranslationY;
	CVector3 v3TranslationZ;


	//Get tower position
	if (m_pObjTracker)
	{
		//Get tracker object position
		m_pObjTracker->GetWorldMatrix().GetPosition(v3WeaponEmitPosition);


		//Get track object orientation
		m_pObjTracker->GetWorldMatrix().GetOrientationX(v3TranslationX);
		m_pObjTracker->GetWorldMatrix().GetOrientationY(v3TranslationY);
		m_pObjTracker->GetWorldMatrix().GetOrientationZ(v3TranslationZ);


		//Calculate offset
		v3TranslationX *= m_v3WeaponOffset.x;
		v3TranslationY *= m_v3WeaponOffset.y;
		v3TranslationZ *= m_v3WeaponOffset.z;


		//Add up weapon emit position
		v3WeaponEmitPosition += v3TranslationX;
		v3WeaponEmitPosition += v3TranslationY;
		v3WeaponEmitPosition += v3TranslationZ;
	}
	else
	{
		//Get self positon
		CEntity::m_mtxWorldMatrix.GetPosition(v3WeaponEmitPosition);


		//Get self orientation
		CEntity::m_mtxWorldMatrix.GetOrientationX(v3TranslationX);
		CEntity::m_mtxWorldMatrix.GetOrientationY(v3TranslationY);
		CEntity::m_mtxWorldMatrix.GetOrientationZ(v3TranslationZ);


		//Calculate weapon offset
		v3TranslationX *= m_v3WeaponOffset.x;
		v3TranslationY *= m_v3WeaponOffset.y;
		v3TranslationZ *= m_v3WeaponOffset.z;


		//Add up weapon emit position
		v3WeaponEmitPosition += v3TranslationX;
		v3WeaponEmitPosition += v3TranslationY;
		v3WeaponEmitPosition += v3TranslationZ;
	}


	//Fire weapon
	m_pWeapon->Fire(v3WeaponEmitPosition, _pEnemy);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will scan through all enemies for the first enemy to be within the tower range to be set as the new target
* for the given index.
*
* @author Bryce Booth
* _uiTargetIndex	Index for the target enemy container
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CTower::FindNewTargetEnemy(unsigned int _uiTargetIndex)
{
	//Set default variables
	CEnemy* pEnemy = 0;
	CEnemy* pOldestEnemy = 0;
	CEnemy* pLowestHealthEnemy = 0;
	unsigned int uiNumEnemiesLowestHealth = 0;
	bool bAlreadyTargeted = false;
	bool bWithinRange     = false;


	//Get enemy instances
	std::vector<CEnemy*>& vecEnemyInstances = CEnemySpawner::GetEnemyInstances();
	unsigned int uiNumEnemyInstances = static_cast<unsigned int>(vecEnemyInstances.size());


	//Loop through number active enemy instances
	for (unsigned int i = 0; i < uiNumEnemyInstances; ++ i)
	{
		//Set enemy
		pEnemy = vecEnemyInstances[i];


		//Check enemy is alive
		if (vecEnemyInstances[i]->IsAlive() == true)
		{
			//Check enemy is within tower range
			bWithinRange = IsEnemyWithinTowerRange(pEnemy);


			if (bWithinRange == true)
			{
				//Check enemy is current being targeted
				bAlreadyTargeted = IsEnemyTargeted(pEnemy);

				
				if (bAlreadyTargeted == false)
				{
					if (pOldestEnemy == 0)
					{
						pOldestEnemy = pEnemy;
						pLowestHealthEnemy = pEnemy;
					}
					else
					{
						if (pEnemy->GetLifeTimeElapsed() > pOldestEnemy->GetLifeTimeElapsed())
						{
							pOldestEnemy = pEnemy;
						}


						if (pEnemy->GetHealth() < pLowestHealthEnemy->GetHealth())
						{
							-- uiNumEnemiesLowestHealth;


							pLowestHealthEnemy = pEnemy;
						}
					}
				}
			}
		}
	}


	//Check enemy was found
	if (pLowestHealthEnemy && uiNumEnemiesLowestHealth > 0)
	{
		//Set enemy as target enemy
		AddNewTargetEnemy(pLowestHealthEnemy);
	}
	else if (pOldestEnemy)
	{
		//Set enemy as target enemy
		AddNewTargetEnemy(pOldestEnemy);
	}
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will check an enemy to see whether it is within the tower range.
*
* @author Bryce Booth
* @param _pEnemy	The enemy instance to check 
* @return bool		States enemy is within tower range or not
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CTower::IsEnemyWithinTowerRange(CEnemy* _pEnemy)
{
	//Set default varaibles
	float fSquaredDistanceTowerEnemy = CEntity::GetSquaredDistanceTo(_pEnemy);
	float fSqauredTowerRange  = m_fRange * m_fRange;
	float fSqauredEnemyRadius = _pEnemy->GetSquaredRadius();


	//Check enemy within tower range
	if (fSquaredDistanceTowerEnemy < fSqauredEnemyRadius + fSqauredTowerRange)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will added a new enemy target to the towers enemy targets container by finding a free spot 
* within the container.
*
* @author Bryce Booth
* @param _pEnemy	The enemy instance to add to the tower targets container 
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CTower::AddNewTargetEnemy(CEnemy* _pEnemy)
{
	//Loop through max number targets
	for (unsigned int i = 0; i < m_uiMaxTargets; ++i)
	{
		//Check target enemy is remove target enemy
		if (m_ppTargetEnemy[i] == 0)
		{
			//Set enemy as target enemy
			m_ppTargetEnemy[i] = _pEnemy;


			//Check current id larger then max target enemy id
			m_uiMaxActiveTargetId = max(i, m_uiMaxActiveTargetId);


			break;
		}
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will search the tower's target enemy container to see if the tower is currently targeting the enemy.
*
* @author Bryce Booth
* @param _kpEnemy	The enemy instance to check for
* @return bool		Returns if the enemy is currenly a target or not of the tower
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CTower::IsEnemyTargeted(const CEnemy* _kpEnemy)
{
	//Set default variables
	bool bTargeted = false;


	//Loop through max number targets
	for (unsigned int i = 0; i < m_uiMaxTargets; ++i)
	{
		//Check target enemy is remove target enemy
		if (m_ppTargetEnemy[i] == _kpEnemy)
		{
			bTargeted = true;


			break;
		}
	}


	return (bTargeted);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will remove an enemy instance from the tower's current targets container
*
* @author Bryce Booth
* @param _kpEnemy	The enemy instance to look for and remove
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CTower::RemoveTargetEnemy(const CEnemy* _kpEnemy)
{
	//Loop through max number targets
	for (unsigned int i = 0; i < m_uiMaxTargets; ++i)
	{
		//Check target enemy is remove target enemy
		if (m_ppTargetEnemy[i] == _kpEnemy)
		{
			//Remove enemy target
			m_ppTargetEnemy[i] = 0;
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
CTower::Deinitialise()
{
	CEventTarget::Deregister(EVENTSUBJECT_ENEMYDEATH);
	CEventTarget::Deregister(EVENTSUBJECT_ENEMYLASTWAYPOINT);

	FW_ADELETE(m_kcpTowerType);

	FW_DELETE(m_pWeapon);
	FW_ADELETE(m_ppTargetEnemy);
	FW_DELETE(m_pObjTracker);
	FW_DELETE(m_pObjTower);
	FW_ADELETE(m_cpSndFire);

	FW_DELETEVECTOR(char*, m_vecUpgradeTowerTypes);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CTower::LoadTowerIniParser()
{
	//Setup default variables
	bool bLoadSuccessful = false;


	//Instance ini parser
	s_pTowerIniParser = new CINIParser();


	//Load tower ini file
	bLoadSuccessful = s_pTowerIniParser->LoadINIFile("Ini Files/Tower Data.ini");


	//Check ini parser file was loaded
	LOG_FATALERROR(bLoadSuccessful == false, "Could not load the tower ini file");
}