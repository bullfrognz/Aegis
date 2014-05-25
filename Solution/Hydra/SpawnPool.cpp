//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   SpawnPool.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "EnemySpawner.h"
#include "StrUtilities.h"


// This Include
#include "SpawnPool.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* SpawnPool class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CSpawnPool::CSpawnPool()
: m_pEnemySpawner(0)
, m_pRenderer(0)
, m_kcpEnemyType(0)
, m_kpFirstWaypoint(0)
, m_uiSpawnNumEnemies(0)
, m_fDelayBtweenSpawn(0)
, m_uiNumSpawnedEnemies(0)
, m_fDelaySpawnTimeElapsed(0)
, m_bActive(false)
{
	//Empty
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* SpawnPool class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CSpawnPool::~CSpawnPool()
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
CSpawnPool::Initialise(CEnemySpawner* _pEnemySpawner)
{
	//Set member variables
	m_pEnemySpawner = _pEnemySpawner;


	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function processes the class instance for the current frame.
*
* @author Bryce Booth
* @param  _fDeltaTick	The time elasped since last process
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSpawnPool::Process(float _fDeltaTick)
{
	//Check if currently active
	LOG_FATALERROR(m_bActive == false, "The spawn pool is not active.");


	//Increment spawn time elapsed
	m_fDelaySpawnTimeElapsed += _fDeltaTick;


	if (m_fDelaySpawnTimeElapsed > m_fDelayBtweenSpawn)
	{
		//Tell enemy spawner to spawn a new enemy
		m_pEnemySpawner->SpawnEnemy(m_pRenderer, m_kcpEnemyType, m_kpFirstWaypoint, m_uiWaveNumber);


		//Incrmeent number of spawned enemies
		++ m_uiNumSpawnedEnemies;


		//Decrement time elapsed
		m_fDelaySpawnTimeElapsed -= m_fDelayBtweenSpawn;
	}


	//Check if the maxium number of enemies to spawn is hit
	if (m_uiNumSpawnedEnemies >= m_uiSpawnNumEnemies)
	{
		//Deactivate
		m_bActive = false;
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Starts spawning of selected amount of type of enemies. 
*
* @author Bryce Booth
*
* @param _pRenderer				Renderer instance of window.
* @param _kcpEnemyType			Type of enemy to spawn.
* @param _kpFirstWaypoint		First waypoint that the enemies will spawn on.
* @param _uiNumEnemies			The number of enemies to spawn.
* @param _fDelayBetweenSpawn	Delay between each enemy spawning.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CSpawnPool::StartSpawning(CD3DRenderer* _pRenderer,
						  CEnemySpawner* _pEnemySpawner,
					      const char* _kcpEnemyType,
					      const CWaypoint* _kpFirstWaypoint,
					      unsigned int _uiSpawnNumEnemies,
					      float _fDelayBetweenSpawn,
						  unsigned int _uiWaveNumber)
{
	delete[] m_kcpEnemyType;
	m_kcpEnemyType = 0;


	//Check if currently active
	LOG_FATALERROR(m_bActive == true, "The spawn pool is already active.");
	

	//Set member variables
	m_pRenderer = _pRenderer;
	m_pEnemySpawner = _pEnemySpawner;
	StrUtilities::Copy(_kcpEnemyType, m_kcpEnemyType);
	m_kpFirstWaypoint = _kpFirstWaypoint;
	m_uiSpawnNumEnemies = _uiSpawnNumEnemies;
	m_fDelayBtweenSpawn = _fDelayBetweenSpawn;
	m_uiWaveNumber = _uiWaveNumber;

	m_uiNumSpawnedEnemies = 0;
	m_fDelaySpawnTimeElapsed = 0;


	//Activate
	m_bActive = true;
}







/********************************
            Protected
*********************************/







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
CSpawnPool::Deinitialise()
{
	delete[] m_kcpEnemyType;
	m_kcpEnemyType = 0;
}