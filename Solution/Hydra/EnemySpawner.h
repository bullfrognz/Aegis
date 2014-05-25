//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   EnemySpawner.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_ENEMYSPAWNER_H__
#define __IGFEB11_IG500_ENEMYSPAWNER_H__


// Library Includes
#include <string>
#include <vector>


// Local Includes
#include "Macros.h"
#include "Array.h"


// Types


// Constants


// Prototypes
class CEnemy;
class CVector3;
class CD3DRenderer;
class CSpawnPool;
class CWaypoint;
class CPlayer;


class CEnemySpawner
{

	// Member Functions
public:


	 CEnemySpawner();
	~CEnemySpawner();


	void Process(float _fDeltaTick);
	void Draw(CD3DRenderer* _pRenderer);


	CSpawnPool* CreateSpawnPool(CD3DRenderer* _pRenderer,
								const char* _kcpEnemyType,
								const CWaypoint* _kpFirstWaypoint, 
								unsigned int _uiNumEnemies,
								float _fDelayBetweenSpawn,
								unsigned int _uiWaveNumber);


	CEnemy* SpawnEnemy(CD3DRenderer* _pRenderer,
					   const char* _kcpEnemyType,
					   const CWaypoint* _kpFirstWaypoint,
					   unsigned int _uiWaveNumber);


	// Inline Functions


	static inline std::vector<CEnemy*>& GetEnemyInstances();


protected:


	bool InitilaiseSpawnPools();


	void ProcessSpawnPools(float _fDeltaTick);
	void ProcessEnemies(float _fDeltaTick);


private:


	void Deinitialise();


	CEnemySpawner(const CEnemySpawner& _krEnemyManager);
	CEnemySpawner& operator = (const CEnemySpawner& _krEnemyManager);


	// Member Variables
protected:
	unsigned int m_uiWaveNumber;


private:


	std::vector<CSpawnPool*> m_arrSpawnPools;


	static std::vector<CEnemy*> s_vecEnemies;
	static unsigned int s_uiHighenemyAliveId;



	static unsigned int s_uiEnemyManagerReffCount;


};


#include "Inline/EnemySpawner.inl"


#endif //__IGFEB11_IG500_ENEMYSPAWNER_H__