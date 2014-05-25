//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   PauseScene.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_PAUSESCENE_H__
#define __IGFEB11_IG500_PAUSESCENE_H__


// Library Includes
#include <d3dx9.h>


// Local Includes
#include "Scene.h"

#include "XButtonTarget.h"
#include "XAnalogTarget.h"
#include "DMouseTarget.h"
#include "DKeyboardTarget.h"


// Types
enum ECurrentButton
{
	BUTTON_INVALID,

	BUTTON_CONTINUE,
	BUTTON_SETTINGS,
	BUTTON_QUIT,

	BUTTON_MAX
};


// Constants


// Prototypes
class CD3DRenderer;


class CPauseScene : public CScene, public IDMouseTarget, public IDKeyboardTarget, public IXButtonTarget, public IXAnalogTarget
{

	// Member Functions
public:


	         CPauseScene();
	virtual ~CPauseScene();


	virtual bool InitialiseScene(CD3DRenderer* _pRenderer, void* _pSceneData = 0);
	virtual void ProcessScene(float _fDeltaTick);
	virtual void DrawScene(CD3DRenderer* _pRenderer);


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
	bool InitialiseSprites(CD3DRenderer* _pRenderer);

	void ResetCursor();

	void MouseSelection();

	void UpdateSprites();


	void IncrementButton();
	void DecrementButton();


	void ExecuteSelect();


	void Deinitialise();


	CPauseScene(const CPauseScene& _krPauseScene);
	CPauseScene& operator = (const CPauseScene& _krPauseScene);


	// Member Variables
protected:


private:


	static enum
	{
		s_uiIdleSpriteColour  = 0xAAAAAAAA,
		s_uiHoverSpriteColour = 0xFFFFFFFF
	};


	ECurrentButton m_eCurrentButton;

	bool m_bMouseClick;
	
	//Lights
	unsigned int m_uiLightDirectional;


	//Settings
	unsigned int m_uiContinue;
	unsigned int m_uiSettings;
	unsigned int m_uiQuit;


	float m_fSelectChangeDelay;
	float m_fSelectChangeTimer;



};


#endif //__IGFEB11_IG500_PAUSESCENE_H__