//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   -
//  Description :   -
//  Author      :   Daniel Langsford
//  Mail        :   daniel.langsford@mediadesign.school.nz
//
#pragma once

#ifndef __IGFEB11_IG500_MAPEDITOR_H__
#define __IGFEB11_IG500_MAPEDITOR_H__

// Library Includes
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

// Local Includes
#include "Scene.h"

#include "XButtonTarget.h"
#include "XTriggerTarget.h"
#include "Terrain.h"
#include "player.h"
#include "DMouseTarget.h"
#include "DKeyboardTarget.h"

// Types


// Constants

// Prototypes
class CTerrain;
class CEnemySpawner;

class CMapEditor : public CScene, public IDMouseTarget, public IDKeyboardTarget, public IXButtonTarget, public IXTriggerTarget
{
// Member Functions
public:

	         CMapEditor();
	virtual ~CMapEditor();

	virtual bool InitialiseLights(CD3DRenderer* _pRenderer);
	virtual bool InitialiseViewports(CD3DRenderer* _pRenderer);
	bool InitialiseGrid(CD3DRenderer* _pRenderer);
	bool InitialiseSprites(CD3DRenderer* _pRenderer);
	void InitialiseBlankGrid();
	
	
	virtual bool InitialiseScene(CD3DRenderer* _pRenderer, void* _pSceneData);

	virtual void ProcessScene(float _fDeltaTick);
	
	virtual void DrawScene(CD3DRenderer* _pRenderer);

	void ResetCursor();

	void DrawLogWindow();
	
	void TileSelection();
	void SpriteSelect();
	virtual void ObjectSelect(float _fDeltaTick);
	
	void TakeScreenShot();
	

	virtual void HandleDMouseInput(EDInputMouse _eDMouse, bool _bDown, long _lValue);
	virtual void HandleDKeyboardInput(EDInputKeyboard _eDKebyoard, bool _bDown = false);
	virtual void HandleXButtonInput(EXInputButton _eXButton, bool _bDown = false);
	virtual void HandleXTriggerInput(EXInputTrigger _eXTrigger, float _fValue = 0.0f);
	void SetControllerActive(bool _bActive);

	void NextTile();
	void LastTile();

	void Deinitialise();

	void Save(const char* _kcFileName);
	bool Load(const char* _kcFileName);

	bool GetSave();
	bool GetLoad();

	

protected:

	static BOOL CALLBACK
	InitialiseProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);

	static BOOL CALLBACK SaveProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);
	
	static BOOL CALLBACK LoadProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);

	static void SaveEnemies(const char* _kcpFileName, unsigned int _uiNumOfWaves);


private:

// Member Variables
public:

protected:

private:
	static CINIParser* s_pParser; 

	static wchar_t* m_wcFileName;

	static bool CheckNumbers(const char* _kcInput);
	
	static bool s_bQuitting;

	bool m_bInitialise;

	bool m_bLeftClick;
	bool m_bRightClick;
	bool m_bSave;
	bool m_bLoad;

	bool m_bPlacable;

	bool m_bPlacingWaypoints;

	bool m_bSpriteSelected;

	bool m_bTakeScreenShot;

	RECT LogBounds;

	CEnemySpawner* m_pEnemySpawner;

	CViewport* m_pScreenShotViewPort;

	unsigned int m_uiLightDirectional;

	static unsigned int s_uiGridWidth;
	static unsigned int s_uiGridHeight;

	float m_fScreenShotCameraHeight;

	ETileType m_eCurrentTileType;

	CTerrain* m_pTerrain;

	//Frame rate stuff.
	unsigned int m_uiFrameCount;
	unsigned int m_uiCurrentFrameCount;
	float m_fFrameTimer;

	//Logging stuff
	unsigned int m_uiLogBoxId;
	unsigned int m_uiFontId;

	CLogManager* m_pLogManager;
	CLogWindow* m_LogWindow;

	//Selected tile
	CTile* m_SelectedTile;
	unsigned int m_uiSelectedTileX;
	unsigned int m_uiSelectedTileY;

	//Timings for object selection
	bool m_bClicked;
	float m_fClickTimer;
	float m_fClickRefresh;

	unsigned int m_uiFileOptions;
	unsigned int m_uiWaterIconID;
	unsigned int m_uiPathIconID;
	unsigned int m_uiRaisedIconID;
	unsigned int m_uiWaypointIconID;
	unsigned int m_uiIconSelectionID;

	//Number of waypoints
	static unsigned int m_uiNumWaypoints;

	unsigned int m_uiIconID;

	int m_iFrameCounter;

	//Timing for icon selection
	bool m_bTriggerUsed;
	float m_fTimer;
	const float m_fResetTime;

	bool m_bBackPressed;
	float m_fBackTimer;
	const float m_fResetBackTime;

	bool m_bControllerActive;
	bool m_bPollControllerActive;

	//Start and End sprites
	unsigned int m_uiStartIcon;
	unsigned int m_uiEndIcon;
	

};

#endif // __IGFEB11_MODULE_TEMPLATE_H__
