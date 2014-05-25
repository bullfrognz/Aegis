//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Wave.h
//  Description :   wave declaration file
//  Author      :   Jamie Smith
//  Mail        :   Jamie.Smith@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_WAVE_H__
#define __IGFEB11_WAVE_H__

// Library Includes

// Local Includes
#include "iniParser.h"
#include "EnemySpawner.h"
#include "Terrain.h"

// Types

// Constants

// Prototypes
class CEnemy;

class CWave
{
	// Member Functions
public:
	CWave();
	virtual ~CWave();

	bool Initialise(CD3DRenderer* _pRenderer, CTerrain* _pTerrain,
					unsigned int _uiWaveID, const char* _kcpFileName,
					float _fDifficulty);

	void Process(float _fDeltaTick);

	void Draw(CD3DRenderer* _pRenderer);

	bool CheckIsWaveOver();

	CEnemySpawner* GetEnemySpawner();

	static void SetHasNotBeenDrawn();

	protected:

private:

	// Member Variables
public:

protected:
	unsigned int m_uiNumberOfEnemies;

	float SpawnDelay;

	float m_fDifficulty;


private:
	static CEnemySpawner* m_pEnemySpawner;
	static int s_iRefCount;
	static bool s_bHasProcessed;	
	static bool s_bHasDrawn;

};

#endif //__IGFEB11_CAMERA_H__
