//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   WaveManager.h
//  Description :   for declaration file
//  Author      :   Jamie Smith
//  Mail        :   Jamie.Smith@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_WAVEMANAGER_H__
#define __IGFEB11_WAVEMANAGER_H__

// Library Includes
#include <map>

// Local Includes
#include "IniParser.h"
#include "scene.h"

#include "XButtonTarget.h"
#include "DKeyboardTarget.h"

// Types

// Constants

// Prototypes
class CTerrain;
class CWave;
class CXInputController;
class CD3DRenderer;
class CDirectInput;

class CWaveManager : public IDKeyboardTarget
{
	// Member Functions
public:
	CWaveManager();
	virtual ~CWaveManager();

	bool Initialise(CD3DRenderer* _pRenderer, CTerrain* _pTerrain,
					char* _kcpFileName, CInputManager* _pInputManager, unsigned int _uiDifficulty);

	void Process(float _fDeltaTick, CTerrain* _pTerrain);

	void Draw(CD3DRenderer* _pRenderer);

	void CountTimers(float _fDeltaTick);

	bool CheckNewWave();

	CWave* GetCurrentWave();

	int GetCurrentWaveCount() const;

	void GetWaveSprites(unsigned int _uiWaveNumber);


protected:	
	void SpawnNewWave(CTerrain* _pTerrain);

private:

	virtual void HandleDKeyboardInput(EDInputKeyboard _eDKebyoard, bool _bDown = false);


	void InitialiseSprites(CD3DRenderer* _pRenderer);

	void SetCountDownSprites(int _iTimeRemaining);
	void DisableSprites();
	
	unsigned int GetSpriteID(int _iNumber);


	// Member Variables
public:

	unsigned int m_uiWaveAmount;

protected:
	std::map<unsigned int, CWave*> m_mapWaves;

	

	unsigned int m_uiCurrentWave;

	float m_fDifficulty;

	//Have the current wave sprites been selected already.
	bool m_bCurrentWaveSprites;

	CD3DRenderer* m_pRenderer;

	const float m_kfWaveDelay;
	float m_fWaveTimer;

	std::string m_strFileName;

	bool m_bController;

	bool m_bSpawnNextWave;

	bool m_bGameOver;

	//Timings for text display
	bool m_bDisplayText;
	float m_fTextTimer;
	float m_fTextDisplayTime;

	
	//Id numbers for in-game sprites
	int m_iSpriteOffSetX;
	int m_iSpriteOffSetY;

	unsigned int m_uiWave;
	unsigned int m_uiSprite0;
	unsigned int m_uiSprite1;
	unsigned int m_uiSprite2;
	unsigned int m_uiSprite3;
	unsigned int m_uiSprite4;
	unsigned int m_uiSprite5;
	unsigned int m_uiSprite6;
	unsigned int m_uiSprite7;
	unsigned int m_uiSprite8;
	unsigned int m_uiSprite9;
	unsigned int m_uiSpriteReserve;

	//Count down timer sprites
	unsigned int m_uiCountdown3;
	unsigned int m_uiCountdown2;
	unsigned int m_uiCountdown1;
	unsigned int m_uiEllipses;
	
	//Count down timer
	float m_fCountDownDisplayTime;
	float m_fCountDown;


	unsigned int m_uiFirstDigitID;
	unsigned int m_uiSecondDigitID;

private:

};

#endif //__IGFEB11_CAMERA_H__
