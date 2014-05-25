//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   EnemyManager.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Application.h"
#include "GameWindow.h"
#include "Enemy.h"
#include "SpawnPool.h"
#include "Waypoint.h"
#include "Vector3.h"


// This Include
#include "EnemySpawner.h"


// Static Variables
std::vector<CEnemy*> CEnemySpawner::s_vecEnemies;
unsigned int         CEnemySpawner::s_uiEnemyManagerReffCount = 0;
unsigned int         CEnemySpawner::s_uiHighenemyAliveId = 0;


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* EnemyManager class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CEnemySpawner::CEnemySpawner()
{
	//Increment number enemy manager reff count
	++ s_uiEnemyManagerReffCount;
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* EnemyManager class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CEnemySpawner::~CEnemySpawner()
{
	Deinitialise();


	//Decrement number enemy manager reff count
	-- s_uiEnemyManagerReffCount;

	
	//This was last enemy manager instance
	if (s_uiEnemyManagerReffCount == 0)
	{
		//Delete all enemy instances
		FW_DELETEVECTOR(CEnemy*, s_vecEnemies);
		s_uiHighenemyAliveId = 0;
	}
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
CEnemySpawner::Process(float _fDeltaTick)
{
	//Process spawn pools
	ProcessSpawnPools(_fDeltaTick);


	//Process enemy instances
	ProcessEnemies(_fDeltaTick);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Draws enemy instances
*
* @author Bryce Booth
* @param _pRenderer	Renderer for the window
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemySpawner::Draw(CD3DRenderer* _pRenderer)
{
	//Get array size
	unsigned int uiSize = static_cast<unsigned int>(s_vecEnemies.size());


	//Check size is not zero
	if (uiSize != 0)
	{
		//Loop through number of enemy instances
		for (unsigned int i = 0; i <= s_uiHighenemyAliveId; ++i)
		{
			//Check enemy alive
			if (s_vecEnemies[i]->IsAlive() == true)
			{
				//Renderer enemy
				s_vecEnemies[i]->Draw(_pRenderer);
			}
		}
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates spawn pool that spawns enemy instances over time.
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

CSpawnPool*
CEnemySpawner::CreateSpawnPool(CD3DRenderer* _pRenderer, const char* _kcpEnemyType, const CWaypoint* _kpFirstWaypoint,
							   unsigned int _uiNumEnemies, float _fDelayBetweenSpawn, unsigned int _uiWaveNumber)
{
	//Set default variables
	CSpawnPool* pSpawnPool = 0;
	unsigned int uiSize = static_cast<unsigned int>(m_arrSpawnPools.size());
	bool bSpawnPoolFound = false;


	//Loop through to max spawn pools
	for (unsigned int i = 0; i < uiSize; ++ i)
	{
		//Check spawn pool is active
		if (m_arrSpawnPools[i]->IsActive() == false)
		{
			//Start spawning of enemies
			m_arrSpawnPools[i]->StartSpawning(_pRenderer,
											  this,
											  _kcpEnemyType,
											  _kpFirstWaypoint,
											  _uiNumEnemies,
											  _fDelayBetweenSpawn,
											  _uiWaveNumber);


			//Set spawn instance
			pSpawnPool = m_arrSpawnPools[i];


			//Set spawn pool found to true
			bSpawnPoolFound = true;


			break;
		}
	}


	//Check if enemy could not be spawned
	if (bSpawnPoolFound == false)
	{
		//Instance new enemy
		CSpawnPool* pSpawnPool = new CSpawnPool();


		//Insert enemy instance into container
		m_arrSpawnPools.push_back(pSpawnPool);


		//Recursion
		return (CreateSpawnPool(_pRenderer, _kcpEnemyType, _kpFirstWaypoint, _uiNumEnemies, _fDelayBetweenSpawn, _uiWaveNumber));
	}
	else
	{
		//Return spawned enemy instance
		return (pSpawnPool);
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates spawn pool that spawns enemy instances over time.
*
* @author Bryce Booth
*
* @param _pRenderer				Renderer instance of window.
* @param _kcpEnemyType			Type of enemy to spawn.
* @param _kpFirstWaypoint		First waypoint that the enemies will spawn on.
*
*---------------------------------------------------------------------------------------------------------------------------*/

CEnemy*
CEnemySpawner::SpawnEnemy(CD3DRenderer* _pRenderer,
						  const char* _kcpEnemyType,
						  const CWaypoint* _kpFirstWaypoint,
						  unsigned int _uiWaveNumber)
{
	//Setup default variables
	CEnemy* pSpawnedEnemy = 0;
	unsigned int uiHighestEnemyAliveId = 0;
	bool bEnemySpawned = false;


	//Get enemy array size
	unsigned int uiArraySize = static_cast<unsigned int>(s_vecEnemies.size());


	//Loop through enemy container
	for (unsigned int i = 0; i < uiArraySize; ++ i)
	{
		if (s_vecEnemies[i]->IsAlive() == false)
		{
			//Change enemy type
			s_vecEnemies[i]->ChangeType(_pRenderer, _kcpEnemyType, _uiWaveNumber);


			//Set enemy position
			s_vecEnemies[i]->GetWorldMatrix().SetPosition(_kpFirstWaypoint->GetPosition());


			//Set enemy waypoiny
			s_vecEnemies[i]->SetWaypoint(_kpFirstWaypoint->GetNextWaypoint());


			//Revive enemy
			s_vecEnemies[i]->Revive();


			//Set spawned enemy instance
			pSpawnedEnemy = s_vecEnemies[i];


			//Set spawned to true
			bEnemySpawned = true;


			//Set current highest enemy alive id
			uiHighestEnemyAliveId = i;


			break;
		}
	}


	//Set current highest enemy alive id
	s_uiHighenemyAliveId = max(uiHighestEnemyAliveId, s_uiHighenemyAliveId);


	//Check if enemy could not be spawned
	if (bEnemySpawned == false)
	{
		//Instance new enemy
		CEnemy* pNewEnemy = new CEnemy();
		pNewEnemy->Initialise(_pRenderer);


		//Insert enemy instance into container
		s_vecEnemies.push_back(pNewEnemy);


		//Recursion
		return (SpawnEnemy(_pRenderer, _kcpEnemyType, _kpFirstWaypoint, _uiWaveNumber));
	}
	else
	{
		//Return spawned enemy instance
		return (pSpawnedEnemy);
	}
}








/********************************
            Protected
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Processes active spawn pools.
*
* @author Bryce Booth
* @param  _fDeltaTick	The time elasped since last process
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemySpawner::ProcessSpawnPools(float _fDeltaTick)
{
	//Set default variables
	CSpawnPool* pSpawnPool = 0;
	unsigned int uiSize = static_cast<unsigned int>(m_arrSpawnPools.size());


	//Loop through to max spawn pools
	for (unsigned int i = 0; i < uiSize; ++ i)
	{
		//Check spawn pool active
		if (m_arrSpawnPools[i]->IsActive() == true)
		{
			//Process spawn pool
			m_arrSpawnPools[i]->Process(_fDeltaTick);
		}
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Processes active enemy instances
*
* @author Bryce Booth
* @param  _fDeltaTick	The time elasped since last process
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEnemySpawner::ProcessEnemies(float _fDeltaTick)
{
	//Get array size
	unsigned int uiSize = static_cast<unsigned int>(s_vecEnemies.size());


	//Check size is not zero
	if (uiSize != 0)
	{
		//Set default variables
		unsigned int uiHighestEnemyAliveId = 0;


		//Loop through number of enemy instances
		for (unsigned int i = 0; i <= s_uiHighenemyAliveId; ++i)
		{
			//Check enemy alive
			if (s_vecEnemies[i]->IsAlive() == true)
			{
				s_vecEnemies[i]->Process(_fDeltaTick);


				uiHighestEnemyAliveId = i;
			}
		}


		//Set current highest enemy alive id
		s_uiHighenemyAliveId = min(s_uiHighenemyAliveId, uiHighestEnemyAliveId);
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
CEnemySpawner::Deinitialise()
{
	FW_DELETEVECTOR(CSpawnPool*, m_arrSpawnPools);
}