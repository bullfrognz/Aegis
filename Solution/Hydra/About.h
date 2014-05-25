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
//  Author      :   jamie smith
//  Mail        :   jamie.smith@mediadesign.school.nz
//
#pragma once

#ifndef __IGFEB11_IG500_ABOUT_H__
#define __IGFEB11_IG500_ABOUT_H__

// Library Includes


// Local Includes
#include "Scene.h"

#include "XButtonTarget.h"
#include "XAnalogTarget.h"
#include "DMouseTarget.h"
#include "DKeyboardTarget.h"


// Types
enum ESpriteSelection
{
	SPRITE_INVALID = -1,
	SPRITE_GAMECONTROLLS,
	SPRITE_GAMERULES,
	SPRITE_CREDITS,
	SPRITE_BACK,
	SPRITE_MAX
};

enum ESceneState
{
	STATE_INVALID = -1,
	STATE_MAIN,
	STATE_CONTROLS,
	STATE_RULES,
	STATE_CREDITS,
	STATE_MAX
};

enum ERulesPage
{
	RULES_INVALID,

	RULES_MAIN,
	RULES_HUDINFO,
	RULES_LIVESINFO,
	RULES_GOLDINFO,
	RULES_WAVEINFO,
	RULES_RADIALINFO,
	RULES_BUILDING,
	
	RULES_MAX
};

enum EControls
{
	CONTROLS_INVALID,

	CONTROLS_XBOXCONTROLLER,
	CONTROLS_KEYBOARD,

	CONTROLS_MAX
};


// Constants

// Prototypes

class CAboutScene : public CScene, public IDMouseTarget, public IDKeyboardTarget, public IXButtonTarget, public IXAnalogTarget
{
// Member Functions
public:
	         CAboutScene();
	virtual ~CAboutScene();

	virtual bool InitialiseLights(CD3DRenderer* _pRenderer);
	virtual bool InitialiseViewports(CD3DRenderer* _pRenderer);
	bool InitialiseSprites(CD3DRenderer* _pRenderer);
	
	virtual bool InitialiseScene(CD3DRenderer* _pRenderer, void* _pSceneData);

	virtual void ProcessScene(float _fDeltaTick);
	
	virtual void DrawScene(CD3DRenderer* _pRenderer);
	
	void SpriteSelect();
		

	virtual void HandleDMouseInput(EDInputMouse _eDMouse, bool _bDown, long _lValue);
	virtual void HandleDKeyboardInput(EDInputKeyboard _eDKebyoard, bool _bDown = false);
	virtual void HandleXButtonInput(EXInputButton _eXButton, bool _bDown = false);
	virtual void HandleXAnalogInput(EXInputAnalog _eXAnalog, float _fValue = 0.0f);


	void SetControllerActive(bool _bActive);

	void OpenControls();
	void CloseControls();

	void OpenCredits();
	void CloseCredits();

	void OpenRules();
	void CloseRules();

	void CloseAll();

	void RulesNextPage();

	void ControlsNextPage();

	void Deinitialise();



protected:


private:
	bool InitPlayerInput();
	bool InitXInput();

// Member Variables
public:

protected:

private:
	static CINIParser* s_pParser; 

	bool m_bLeftClick;
	bool m_bRightClick;

	bool m_bSpriteSelected;

	ESceneState m_eSceneState;

	ERulesPage m_eRulesPage;

	EControls m_eCOntrolsPage;

	ESpriteSelection m_eSelectedSprite;
	unsigned int m_uiSelectedSprite;

	unsigned int m_uiLightDirectional;

	//Timing for icon selection
	bool m_bTriggerUsed;
	float m_fTimer;
	const float m_fResetTime;

	bool m_bBackPressed;
	float m_fBackTimer;
	const float m_fResetBackTime;

	bool m_bControllerActive;
	bool m_bPollControllerActive;

	//Sprties

	//Background
	unsigned int m_uiBackGround;

	//Controlls
	unsigned int m_uiGameControlls;

	//Rules
	unsigned int m_uiGameRules;

	//Credits
	unsigned int m_uiCredits;

	//Back 
	unsigned int m_uiBack;

	//Controller 
	unsigned int m_uiController;

	//Keyboard
	unsigned int m_uiKeyBoardControls;

	//Credits screen
	unsigned int m_uiViewCredits;

	//Rules
	unsigned int m_uiRules1;
	unsigned int m_uiRules2;
	unsigned int m_uiRules3;
	unsigned int m_uiRules4;
	unsigned int m_uiRules5;
	unsigned int m_uiRules6;
	unsigned int m_uiRules7;

	//Close
	unsigned int m_uiQuit;


};

#endif // __IGFEB11_MODULE_TEMPLATE_H__
