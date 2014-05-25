//
//  Diploma of Interactive Gaming
//  Scene Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   wave.cpp
//  Description :   for implementation file
//  Author      :   Jamie.Smith
//  Mail        :   Jamie.Smith@mediadesign.school.nz
//

// Library includes.
#include <string>

// Local Includes
#include "enemy.h"
#include "application.h"
#include "window.h"

// This Include
#include "wave.h"

// Static Variables
int 
CWave::s_iRefCount = 0;

CEnemySpawner*
CWave::m_pEnemySpawner = 0;

bool
CWave::s_bHasProcessed = false;

bool 
CWave::s_bHasDrawn = false;

// Static Function Prototypes

// Implementation

CWave::CWave()
: m_fDifficulty(0)
{
	s_iRefCount++;

	if(s_iRefCount == 1)
	{
		m_pEnemySpawner = new CEnemySpawner();
	}
}

CWave::~CWave()
{
	s_iRefCount--;

	if(s_iRefCount == 0)
	{
		delete m_pEnemySpawner;
		m_pEnemySpawner = 0;
	}
}

/** 
*
* Initialises the wave
* 
* @author Jamie.Smith  
* @Param _pRenderer a pointer to the renderer
* @Param _pTerrain a pointer to the Terrain
* @Param _kcpFileName a pointer to the the file destination of the map
* @Param _uiWaveID the waves id
* @Param _uiDifficulty the difficulty
* @return bool
*
*/
bool 
CWave::Initialise(CD3DRenderer* _pRenderer, CTerrain* _pTerrain,
				  unsigned int _uiWaveID, const char* _kcpFileName,
				  float _fDifficulty)
{
	std::string EnemyType;

	m_fDifficulty = _fDifficulty;

	char Buffer[256];

	sprintf_s(Buffer, 256, "%s %i","Wave", _uiWaveID);

	std::string strBuffer = Buffer;

	CINIParser* pINIParser = new CINIParser();
	pINIParser->LoadINIFile(_kcpFileName);
	pINIParser->GetValue(strBuffer.c_str(), "EnemyType", EnemyType);
	pINIParser->GetValue(strBuffer.c_str(), "NumberOfEnemies", m_uiNumberOfEnemies);
	pINIParser->GetValue(strBuffer.c_str(), "SpawnDelay", SpawnDelay);
	delete pINIParser;
	pINIParser = 0;
	
	m_pEnemySpawner->CreateSpawnPool(_pRenderer, EnemyType.c_str(), 
									_pTerrain->GetWaypointManager().GetWaypoint(0),
									m_uiNumberOfEnemies, SpawnDelay, _uiWaveID);	

	return(true);
}

/** 
*
* Processes the Wave
* 
* @author Jamie.Smith  
* @Param _fDeltaTick the delta of the clock
* @return void
*
*/
void 
CWave::Process(float _fDeltaTick)
{
	if(s_bHasProcessed == false)
	{
		m_pEnemySpawner->Process(_fDeltaTick);
		s_bHasProcessed = true;
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
CWave::Draw(CD3DRenderer* _pRenderer)
{
	if(s_bHasDrawn == false)
	{
		m_pEnemySpawner->Draw(_pRenderer);
		s_bHasProcessed = false;
		s_bHasDrawn = true;
	}
}		

/** 
*
* Checks if the wave is over
* 
* @author Jamie.Smith  
* @return bool
*
*/
bool
CWave::CheckIsWaveOver()
{
	std::vector<CEnemy*>& vecEnemyInstances = CEnemySpawner::GetEnemyInstances();
	unsigned int uiNumEnemyInstances = static_cast<unsigned int>(vecEnemyInstances.size());

	if(uiNumEnemyInstances <= 0)
	{
		return(false);
	}

	for(unsigned int i = 0; i < uiNumEnemyInstances; ++i)
	{
		if(vecEnemyInstances[i]->IsAlive())
		{
			return(false);
		}		
	}

	return(true);
}

/** 
*
* returns the enemye spawner
* 
* @author Jamie.Smith  
* @return CEnemySpawner*
*
*/
CEnemySpawner* 
CWave::GetEnemySpawner()
{
	return(m_pEnemySpawner);
}

/** 
*
* sets has not been drawn
* 
* @author ???
* @return void
*
*/
void
CWave::SetHasNotBeenDrawn()
{
	s_bHasDrawn = false;
}
		