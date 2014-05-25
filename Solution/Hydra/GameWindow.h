//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   GameWindow.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_GAMEWINDOW_H__
#define __IGFEB11_IG500_GAMEWINDOW_H__


// Library Includes


// Local Includes
#include "Window.h"


// Types


// Constants


// Prototypes
class CINIParser;


class CGameWindow : public CWindow
{

	// Member Functions
public:


	         CGameWindow();
	virtual ~CGameWindow();


	virtual void ExecuteOneFrame();


	virtual LRESULT CALLBACK WindowProc(HWND _hWindow, UINT _uiMessage, WPARAM _wParam, LPARAM _lParam);


	static BOOL CALLBACK DlgProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);
	static BOOL CALLBACK CheatProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);
	static BOOL CALLBACK EnemyProc(HWND _hwnd, UINT _msg, WPARAM _wparam, LPARAM _lparam);
	

	// Inline Functions

protected:


	virtual void ExecuteMainSceneChange();
	virtual void ExecuteOverlaySceneChange();

	
private:
	void Deinitialise();


	CGameWindow(const CGameWindow& _krGameWindow);
	CGameWindow& operator = (const CGameWindow& _krGameWindow);


	// Member Variables
protected:


private:


	static bool s_bWireframe;
	static bool s_bDebugInfo;
	static unsigned int s_uiPlayerLives;
	static unsigned int s_uiPlayerGold;
	static unsigned int s_uiEnemySpawnNumber;
	static float s_fEnemySpawnRate;
		

};


#endif //__IGFEB11_IG500_GAMEWINDOW_H__