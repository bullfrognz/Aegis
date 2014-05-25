//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   SelectMapScene.h
//  Description :   Graphical inferface for the player to select a map
//					and a difficulty for the game.
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_SELECTMAPSCENE_H__
#define __IGFEB11_IG500_SELECTMAPSCENE_H__


// Library Includes
#include <vector>


// Local Includes
#include "Scene.h"

#include "XButtonTarget.h"
#include "XAnalogTarget.h"
#include "DMouseTarget.h"
#include "DKeyboardTarget.h"
#include "GameScene.h"


// Types
enum ESelectMapPhase
{
	SELMAPPHASE_INVALID = -1,

	SELMAPPHASE_SELECTMAP,
	SELMAPPHASE_SELDIFFICULTY,

	SELMAPPHASE_MAX
};


// Constants


// Prototypes
class CXInputController;
class CObject;
class CText;
class CINIParser;


class CSelectMapScene : public CScene, public IDMouseTarget, public IDKeyboardTarget, public IXButtonTarget, public IXAnalogTarget
{

	// Member Functions
public:


	 CSelectMapScene();
	~CSelectMapScene();


	virtual bool InitialiseScene(CD3DRenderer* _pRenderer, void* _pSceneData = 0);
	virtual void ProcessScene(float _fDeltaTick);
	virtual void DrawScene(CD3DRenderer* _pRenderer);

	void DoubleClicked();

	void SetDoubleClick(bool _bDoubleClick);



	// Inline Functions


protected:


	virtual bool InitialiseLights(CD3DRenderer* _pRenderer);
	virtual bool InitialiseViewports(CD3DRenderer* _pRenderer);


	virtual void HandleDMouseInput(EDInputMouse _eDMouse, bool _bDown, long _lValue);
	virtual void HandleDKeyboardInput(EDInputKeyboard _eDKebyoard, bool _bDown = false);
	virtual void HandleXButtonInput(EXInputButton _eXButton, bool _bDown = false);
	virtual void HandleXAnalogInput(EXInputAnalog _eXAnalog, float _fValue = 0.0f);


private:

	bool InitialisePlayerInputTarget();
	bool InitialiseXInputTarget();
	bool InitialiseMapText();
	bool InitialiseSprites();
	bool InitialiseMapPreviewer();

	void ResetCursor();
	
	void ScanMapFiles();

	void IncrementMapSelection();
	void DecrementMapSelection();


	void IncrementDifficultySelection();
	void DecrementDifficultySelection();


	void SelectMap();
	void SelectDifficulty();


	void BackToMainMenu();
	void BackToSelectMap();


	void UpdateMapTitles();
	void UpdatePlayerText();
	void UpdateScrollArrows();
	void UpdateMapPreviewer();
	void UpdateDifficultyButtons();
	void UpdateMapSelector();


	void ReadSelectedMap();

	void MouseSelect();
	void MouseSelectDifficulty();
	
	void Deinitialise();
	void DrawDebugInfo();

	void ScrollUp();
	void ScrollDown();

	CSelectMapScene(const CSelectMapScene& _krSelectMapScene);
	CSelectMapScene& operator = (const CSelectMapScene& _krSelectMapScene);


	// Member Variables
protected:


private:

	
	static enum
	{
		s_eMapTextFontSize = 30,


		s_eMaxMapsToDisplay = 8,


		s_eMapsTextOffsetX = -390,
		s_eMapsTextOffsetY = -269,
		s_eMapsTextMapMargin   = 50,
		s_eMapsTextIdleColour  = 0xFFDDDDDD,
		m_eMapsTextHoverColour = 0xFFffffff,


		s_ePlayerGoldTextOffsetX = 200,
		s_ePlayerGoldTextOffsetY = -10,
		s_ePlayerLivesTextOffsetX = 170,
		s_ePlayerLivesTextOffsetY = 68,
		s_ePlayerTextFontSize = 25,
		s_ePlayerTextColour = 0xFFf7ff19,


		s_eDifficultyTextFontSize = 45,
		s_eDifficultyIdleColour = 0xFF555555,
		s_eDifficultyHoverColour = 0xFFFFFFFF,
	};


	CText* m_pTextMapTitles[s_eMaxMapsToDisplay];
	CText* m_pTextMapPlayerGold;
	CText* m_pTextMapPlayerLives;
	CINIParser* m_pINIMapFile;


	ESelectMapPhase m_eScenePhase;
	EDifficulty  m_eSelectedDifficulty;

	
	unsigned int m_uiSelectedMap;
	unsigned int m_uiPlayerStartGold;
	unsigned int m_uiPlayerStartLives;


	unsigned int m_uiLightDirectional;
	unsigned int m_uiCurrentMapId;
	unsigned int m_uiMapsReadFromId;
	unsigned int m_uiMapSelectorPosition;

	unsigned int m_uiVertexQuadID;
	unsigned int m_uiPreviewTextureId;


	//Sprites
	unsigned int m_uiSpriteBackground;
	unsigned int m_uiSpriteMapContainer;
	unsigned int m_uiSpriteMapPreviewer;
	unsigned int m_uiSpriteSelectorBar;
	unsigned int m_uiSpriteEasy;
	unsigned int m_uiSpriteMedium;
	unsigned int m_uiSpriteHard;

	unsigned int m_uiSpriteArrowUp;
	unsigned int m_uiSpriteArrowDown;


	float m_fMapSwitchDelay;
	float m_fMapSwitchTimer;
	float m_fDifficultySwitchDelay;
	float m_fDifficultySwitchTimer;


	bool m_bNoMaps;


	bool m_bIncrementMap;
	bool m_bDecrementMap;
	bool m_bIncrementDifficulty;
	bool m_bDecrementDifficulty;


	bool m_bMouseClick;
	bool m_bDoubleClick;
	bool m_bControllerActive;


	std::string m_strMapPreviewFile;


	std::vector<char*> m_vecMaps;


};


#endif //__IGFEB11_IG500_SELECTMAPSCENE_H__