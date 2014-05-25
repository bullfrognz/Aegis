//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   GameScene.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_GAMESCENE_H__
#define __IGFEB11_IG500_GAMESCENE_H__


// Library Includes
#include <windows.h>
#include <d3dx9.h>


// Local Includes
#include "Scene.h"

#include "XButtonTarget.h"
#include "XAnalogTarget.h"
#include "strUtilities.h"
#include "vector2.h"
#include "DMouseTarget.h"
#include "DKeyboardTarget.h"


// Types
enum EDifficulty
{
	DIFFICULTY_INVALID = -1,

	DIFFICULTY_EASY = 1,
	DIFFICULTY_MEDIUM,
	DIFFICULTY_HARD,

	DIFFICULTY_MAX
};


// Constants


// Prototypes
class CD3DRenderer;
class CViewport;
class CLogManager;
class CStaticObject;
class CPlayerInput;
class CPlayer;
class CTower;
class CEnemySpawner;
class CTerrain;
class CXInputController;
class CLogWindow;
class CAnimatedMesh;
class CAnimatedObject;
class CRadialMenu;
class CHud;
class CWaveManager;
class CGameSceneData;
class CVector2;
class CParticleManager;
class CTile;


class CGameScene : public CScene, public IDMouseTarget, public IDKeyboardTarget, public IXButtonTarget, public IXAnalogTarget
{
	// Member Functions
public:


	         CGameScene();
	virtual ~CGameScene();

	virtual bool InitialiseScene(CD3DRenderer* _pRenderer, void* _pSceneData);
	virtual void ProcessScene(float _fDeltaTick);
	virtual void DrawScene(CD3DRenderer* _pRenderer);


	virtual void RecoverFromOverlayScene();


	void ExecuteGameOver(bool _bWon);


	// Inline Functions
	inline void SetShowDebugInfo(bool _bShow);
	inline CPlayer* GetPlayer();
	inline CWaveManager* GetWaveManager();
	inline CTerrain* GetTerrain();
	CGameSceneData& GetData();
	inline CRadialMenu* GetRadialMenu();
	inline CHud* GetHud();

	void GameOver(bool _bVictory);

protected:

	virtual bool InitialiseLights(CD3DRenderer* _pRenderer);
	virtual bool InitialiseViewports(CD3DRenderer* _pRenderer);

	void ResetCursor();
	
	virtual void ObjectSelect(bool _bClicked);


	virtual void HandleDMouseInput(EDInputMouse _eDMouse, bool _bDown, long _lValue);
	virtual void HandleDKeyboardInput(EDInputKeyboard _eDKebyoard, bool _bDown = false);
	virtual void HandleXButtonInput(EXInputButton _eXButton, bool _bDown = false);
	virtual void HandleXAnalogInput(EXInputAnalog _eXAnalog, float _fValue = 0.0f);
	void SetControllerActive(bool _bActive);
	

	static void BuildTower(void* _pGameSceneInstance, unsigned char _ucButton);

	static void UpgradeTower(void* _pGameSceneInstance, unsigned char _ucButton);

	static void SellTower(void* _pGameSceneInstance, unsigned char _ucButton);

	void DrawDebugInfo();
	void DrawTiles();


private:
	bool InitialiseSprites();
	bool InitialisePlayerInputTarget();
	bool InitialiseXInputTarget();
	bool IntiialisePlayer(unsigned int _uiStartGold, unsigned int _uiStartLives);
	bool InitialiseTerrain(CD3DRenderer* _pRenderer, const char* _kcpMapFile);
	bool InitialiseWaveManager(CD3DRenderer* _pRenderer, CTerrain* _pTerrain, CGameSceneData* _pGameSceneData);
	bool InitialiseRadialMenu(CD3DRenderer* _pRenderer, unsigned int _uiWindowWidth, unsigned int _uiMaxHeight);
	bool InitialiseHud(CD3DRenderer* _pRenderer, unsigned int _uiWindowWidth, unsigned int _uiWindowHeight, const char* _pkcMapFile);

	void CheckMouseActive();

	void MouseSelection();


	void OpenPauseMenu();

	void Deinitialise();


	CGameScene(const CGameScene& _krGameScene);
	CGameScene& operator = (const CGameScene& _krGameScene);


	// Member Variables
protected:





private:

	CGameSceneData* m_pGameData;

	bool m_bUseMousePos;
	bool m_bSkipLeftClick;

	//Scene lights
	unsigned int m_uiLightDirectional;
 
	CTerrain*				m_pTerrain;
	CPlayer*				m_pPlayer;
	CRadialMenu*			m_pRadialMenu;
	CHud*					m_pHud;
	CWaveManager*   		m_pWaveManager;
	CParticleManager*		m_pPartManager;
	

	unsigned int m_uiPointerId;

	//Currently selected tile
	static unsigned int m_uiSelectedTileX;
	static unsigned int m_uiSelectedTileY;
	static const CTile* m_pSelectedTile;

	unsigned int m_uiVictoryScreenId;

	float m_PlaceTimer;

	float m_fAnalogLeftX;
	float m_fAnalogLeftY;


	bool m_bCollision;
	bool m_bController;
	bool m_bShowDebugInfo;
	bool m_bLeftClick;
	bool m_bRightClick;
	bool m_bPaused;

	bool m_bRadMenuOpen;

	bool m_bRadMenu360;	// True if the Radial Menu Process() was handled by the Xbox 360 controller.

	CVector2 m_vecPreviousMousePos;

	unsigned int m_uiCrosshairId;
	unsigned int m_uiPauseId;

	unsigned int m_uiStartWaypoint;
	unsigned int m_uiEndWaypoint;

	COORD m_MouseCoords;

	bool m_bGameOver;
};


#include "Inline/GameScene.inl"


#endif //__IGFEB11_IG500_GAMESCENE_H__