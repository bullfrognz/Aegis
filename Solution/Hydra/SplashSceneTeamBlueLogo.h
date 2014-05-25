//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   SplashScene.h
//  Description :   Splash scene that appears as the 
//					game starts.
//
//  Author      :   Jamie Smith
//  Mail        :   Jamie Smith@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_SPLASHSCENETEAMBLUE_H__
#define __IGFEB11_IG500_SPLASHSCENETEAMBLUE_H__


// Library Includes


// Local Includes
#include "Scene.h"
#include "DMouseTarget.h"
#include "DKeyboardTarget.h"
#include "XButtonTarget.h"


// Types


// Constants


// Prototypes
class CEntity;


class CSplashSceneTeamBlue : public CScene, public IDMouseTarget, public IDKeyboardTarget, public IXButtonTarget
{

	// Member Functions
public:


	         CSplashSceneTeamBlue();
	virtual ~CSplashSceneTeamBlue();


	virtual bool InitialiseScene(CD3DRenderer* _pRenderer, void* _pSceneData = 0);
	virtual void ProcessScene(float _fDeltaTick) ;
	virtual void DrawScene(CD3DRenderer* _pRenderer);


	// Inline Functions


protected:


	void Alpha();


	void Finish();


	virtual void HandleDMouseInput(EDInputMouse _eDMouse, bool _bDown, long _lValue);
	virtual void HandleDKeyboardInput(EDInputKeyboard _eDKebyoard, bool _bDown = false);
	virtual void HandleXButtonInput(EXInputButton _eXButton, bool _bDown = false);


private:


	virtual bool InitialiseLights(CD3DRenderer* _pRenderer);
	virtual bool InitialiseViewports(CD3DRenderer* _pRenderer);
	bool InitialiseSprite();


	void Deinitialise();


	CSplashSceneTeamBlue(const CSplashSceneTeamBlue& _krSplashScene);
	CSplashSceneTeamBlue& operator = (const CSplashSceneTeamBlue& _krSplashScene);


	// Member Variables
protected:


	unsigned int m_uiLightDirectional;
	unsigned int m_uiTeamBlueLogo;

	float m_fCountDown;
	float m_fTimer;

	bool m_bFadeOut;

private:


};


#endif //__IGFEB11_IG500_SPLASHSCENE_H__