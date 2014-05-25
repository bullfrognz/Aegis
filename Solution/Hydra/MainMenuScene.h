//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   MainMenuScene.h
//  Description :   Scene for the player to select a category
//					to enter.
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_MAINMENUSCENE_H__
#define __IGFEB11_IG500_MAINMENUSCENE_H__


// Library Includes


// Local Includes
#include "Scene.h"

#include "XButtonTarget.h"
#include "XAnalogTarget.h"
#include "Vector3.h"
#include "DMouseTarget.h"
#include "DKeyboardTarget.h"


// Types
enum EMenuCogSelection
{
	MENUCOGSEL_INVALID = -1,

	MENUCOGSEL_MIN,

	MENUCOGSEL_PLAYGAME,
	MENUCOGSEL_OPTIONS,
	MENUCOGSEL_MAPEDITOR,
	MENUCOGSEL_ABOUT,
	MENUCOGSEL_QUIT,

	MENUCOGSEL_MAX
};


// Constants


// Prototypes
class CViewport;
class CPlayerInput;
class CMouse;
class CXInputController;
class CObject;


class CMainMenuScene : public CScene, public IDMouseTarget, public IDKeyboardTarget, public IXButtonTarget, public IXAnalogTarget
{

	// Member Functions
public:


	         CMainMenuScene();
	virtual ~CMainMenuScene();


	virtual void ProcessScene(float _fDeltaTick);
	virtual void DrawScene(CD3DRenderer* _pRenderer);


	virtual void RecoverFromOverlayScene();


	// Inline Functions


protected:


	virtual bool InitialiseLights(CD3DRenderer* _pRenderer);
	virtual bool InitialiseViewports(CD3DRenderer* _pRenderer);
	virtual bool InitialiseScene(CD3DRenderer* _pRenderer, void* _pSceneData = 0);
	bool InitialiseGameTitle(CD3DRenderer* _pRenderer);
	bool InitialiseMenuCog(CD3DRenderer* _pRenderer);
	bool InitiliseSprites(CD3DRenderer* _pRenderer);


	void ResetCursor();


	void DisplayMenutitle();
	void HideMenuTitle();


	void DisplayMenuCog();
	void HideMenuCog();
	void RotateMenuCogRight();
	void RotateMenuCogLeft();
	void MouseSelection();


	void ExecuteMenuCogSelection();


	virtual void HandleDMouseInput(EDInputMouse _eDMouse, bool _bDown, long _lValue);
	virtual void HandleDKeyboardInput(EDInputKeyboard _eDKebyoard, bool _bDown = false);
	virtual void HandleXButtonInput(EXInputButton _eXButton, bool _bDown = false);
	virtual void HandleXAnalogInput(EXInputAnalog _eXAnalog, float _fValue = 0.0f);

	
private:


	bool InitialisePlayerInputTarget();
	bool InitialiseXInputTarget();


	void Deinitialise();


	CMainMenuScene(const CMainMenuScene& _krMainMenuScene);
	CMainMenuScene& operator = (const CMainMenuScene& _krMainMenuScene);


	// Member Variables
protected:


private:


	CVector3 m_v3MenuCogStartPosition;
	CVector3 m_v3MenuCogEndPosition;


	CObject* m_pAObjGameTitle;
	CObject* m_pSObjMenuCog;


	int m_iMenuCogSelection;


	unsigned int m_uiLightDirectional;
	unsigned int m_uiMenuSelectionId;
	unsigned int m_uiNextOptionIconId;
	unsigned int m_uiLastOptionIconId;


	unsigned int m_uiNumMenuOptions;


	float m_fMenuCogLerpDuration;
	float m_fMenuCogRotateDuration;
	float m_fTitleAnimationTimer;


	bool m_bLAnalogActive;
	bool m_bRAnalogActive;
	bool m_bLeftClick;
	bool m_bActive;


};


#endif //__IGFEB11_IG500_SELECTMAPSCENE_H__