//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   SpawnPool.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_SPAWNPOOL_H__
#define __IGFEB11_IG500_SPAWNPOOL_H__


// Library Includes


// Local Includes
#include "Macros.h"
#include "Vector3.h"


// Types


// Constants


// Prototypes
class CEnemySpawner;
class CD3DRenderer;
class CWaypoint;


class CSpawnPool
{

	// Member Functions
public:


	 CSpawnPool();
	~CSpawnPool();


	bool Initialise(CEnemySpawner* _pEnemySpawner);
	void Process(float _fDeltaTick);


	void StartSpawning(CD3DRenderer* _pRenderer,
					   CEnemySpawner* _pEnemySpawner,
					   const char* _kcpEnemyType,
					   const CWaypoint* _kpFirstWaypoint,
					   unsigned int _uiSpawnNumEnemies,
					   float _fDelayBetweenSpawn,
					   unsigned int _uiWaveNumber);


	// Inline Functions
	inline bool IsActive() const;


protected:


private:


	void Deinitialise();


	CSpawnPool(const CSpawnPool& _krSpawnPool);
	CSpawnPool& operator = (const CSpawnPool& _krSpawnPool);


	// Member Variables
protected:


private:
	

	CD3DRenderer*    m_pRenderer;
	CEnemySpawner*   m_pEnemySpawner;
	const char*      m_kcpEnemyType;
	const CWaypoint* m_kpFirstWaypoint;
	unsigned int     m_uiSpawnNumEnemies;
	float            m_fDelayBtweenSpawn;

	unsigned int m_uiWaveNumber;


	unsigned int m_uiNumSpawnedEnemies;
	float	     m_fDelaySpawnTimeElapsed;

	bool m_bActive;
};


#include "Inline/SpawnPool.inl"


#endif //__IGFEB11_IG500_SPAWNPOOL_H__