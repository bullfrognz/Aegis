//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Scene.h
//  Description :   
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __GAMEWINSCENE_H__
#define __GAMEWINSCENE_H__


// Library Includes
#include "D3DRenderer.h"
#include "Scene.h"

// Local Includes


// Types


// Constants


// Prototypes
class CD3DRenderer;
class CSoundSystem;
class CViewport;
class CPlayerInput;
class CXInputController;
class CLogWindow;


class CGameWinScene : public CScene
{

	// Member Functions
public:


	         CGameWinScene();
	virtual ~CGameWinScene();


	virtual bool InitialiseScene(CD3DRenderer* _pRenderer, void* _pSceneData = 0);
	virtual void ProcessScene(float _fDeltaTick);
	virtual void DrawScene(CD3DRenderer* _pRenderer);


	virtual void RecoverFromOverlayScene();


	// Inline Functions


protected:


	virtual bool InitialiseLights(CD3DRenderer* _pRenderer);
	virtual bool InitialiseViewports(CD3DRenderer* _pRenderer);


private:


	virtual bool InitialisePlayerInput();
	virtual bool InitialiseXInput();
	virtual bool InitialiseSoundSystem();
	virtual bool InitialiseLogManager();

	virtual void ProcessFPSCount(float _fDeltaTick);


	// Member Variables
protected:

private:

	unsigned int m_uiModulate;
	unsigned int m_uiSplashID;
	float m_fFadeTime;
	float m_fTotalTimeOpen;
	float m_fSolidTime;
	float m_fDelay;
};

#endif //__IGFEB11_IG500_Scene_H__