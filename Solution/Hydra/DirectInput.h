//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   DirectInput.h
//  Description :   Keeps track of mouse and keyboard states
//					and sends changed states to targets.
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_DIRECTINPUT_H__
#define __IGFEB11_IG500_DIRECTINPUT_H__


#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif


// Library Includes
#include <dinput.h>
#include <map>
#include <vector>


// Local Includes
#include "Vector2.h"


// Types
enum EDInputKeyboard
{
	DKEYBOARD_INVALID = -1,

	DKEYBOARD_A = DIK_A,
	DKEYBOARD_B = DIK_B,
	DKEYBOARD_C = DIK_C,
	DKEYBOARD_D = DIK_D,
	DKEYBOARD_E = DIK_E,
	DKEYBOARD_F = DIK_F,
	DKEYBOARD_G = DIK_C,
	DKEYBOARD_H = DIK_H,
	DKEYBOARD_I = DIK_I,
	DKEYBOARD_J = DIK_J,
	DKEYBOARD_K = DIK_K,
	DKEYBOARD_L = DIK_L,
	DKEYBOARD_M = DIK_M,
	DKEYBOARD_N = DIK_N,
	DKEYBOARD_O = DIK_O,
	DKEYBOARD_P = DIK_P,
	DKEYBOARD_Q = DIK_Q,
	DKEYBOARD_R = DIK_R,
	DKEYBOARD_S = DIK_S,
	DKEYBOARD_T = DIK_T,
	DKEYBOARD_U = DIK_U,
	DKEYBOARD_V = DIK_V,
	DKEYBOARD_W = DIK_W,
	DKEYBOARD_X = DIK_X,
	DKEYBOARD_Y = DIK_Y,
	DKEYBOARD_Z = DIK_Z,


	DKEYBOARD_UPARROW = DIK_UP,
	DKEYBOARD_DOWNARROW = DIK_DOWN,
	DKEYBOARD_LEFTARROW = DIK_LEFT,
	DKEYBOARD_RIGHTARROW = DIK_RIGHT,


	DKEYBOARD_0 = DIK_0,
	DKEYBOARD_1 = DIK_1,
	DKEYBOARD_2 = DIK_2,
	DKEYBOARD_3 = DIK_3,
	DKEYBOARD_4 = DIK_4,
	DKEYBOARD_5 = DIK_5,
	DKEYBOARD_6 = DIK_6,
	DKEYBOARD_7 = DIK_7,
	DKEYBOARD_8 = DIK_8,
	DKEYBOARD_9 = DIK_9,

	
	DKEYBOARD_F1 = DIK_F1,
	DKEYBOARD_F2 = DIK_F2,
	DKEYBOARD_F3 = DIK_F3,
	DKEYBOARD_F4 = DIK_F4,
	DKEYBOARD_F5 = DIK_F5,
	DKEYBOARD_F6 = DIK_F6,
	DKEYBOARD_F7 = DIK_F7,
	DKEYBOARD_F8 = DIK_F8,
	DKEYBOARD_F9 = DIK_F9,
	DKEYBOARD_F10 = DIK_F10,


	DKEYBOARD_ENTER = DIK_RETURN,
	DKEYBOARD_SPACE = DIK_SPACE,
	DKEYBOARD_ESCAPE = DIK_ESCAPE,
	DKEYBOARD_BACK = DIK_BACK,

	DKEYBOARD_MAX = 256
};


enum EDInputMouse
{
	DMOUSE_INVALID = -1,

	DMOUSE_LEFTCLICK,
	DMOUSE_RIGHTCLICK,
	DMOUSE_MIDDLECLICK,
	DMOUSE_WHEEL,

	DMOUSE_MAX
};


// Constants


// Prototypes
class IDMouseTarget;
class IDKeyboardTarget;


class CDirectInput
{

	// Member Functions
public:


	         CDirectInput();
	virtual ~CDirectInput();


	bool Initialise();
	void Process();


	void AddTarget(EDInputMouse _eDMouse, IDMouseTarget* _pTarget);
	void AddTarget(EDInputKeyboard _eDKeyboard, IDKeyboardTarget* _pTarget);


	void RemoveTarget(EDInputMouse _eDMouse, IDMouseTarget* _pTarget);
	void RemoveTarget(EDInputKeyboard _eDKeyboard, IDKeyboardTarget* _pTarget);


	// Inline Functions
	inline void SetDisabled(bool _bDisabled);


protected:


	bool UpdateMouse();
	bool UpdateKeyboard();


	void SaveCurrentState();


	void StoreCurrentStates();


	void DispatchMouseState();
	void DispatchKeyboardState();


	void SendInputToTargets(EDInputMouse _eDMouse);
	void SendInputToTargets(EDInputKeyboard _eDKeyboard);


private:


	bool InitialiseDInputInteface();
	bool InitialiseMouse();
	bool InitialiseKeyboard();


	void Deinitialise();


	CDirectInput(const CDirectInput& _krDirectInput);
	CDirectInput& operator = (const CDirectInput& _krDirectInput);


	// Member Variables
protected:


private:


	bool m_bKeyStates[DKEYBOARD_MAX];
	bool m_bPreviousKeyStates[DKEYBOARD_MAX];


	DIDEVCAPS m_tMouseCaps; 


	long m_lMouseState[DMOUSE_MAX];
	long m_lPreviousMouseState[DMOUSE_MAX];


	CVector2 m_v2MousePosition;


	IDirectInput8* m_d3dpDirectInput8;
	IDirectInputDevice8* m_d3dpKeyboard;
	IDirectInputDevice8* m_d3dpMouse;


	unsigned int m_uiWindowWidth;
	unsigned int m_uiWindowHeight;


	bool m_bDisabled;


	std::vector<IDMouseTarget*>    m_vecDMouseTargets[DMOUSE_MAX];
	std::vector<IDKeyboardTarget*> m_vecDKeyboardTargets[DKEYBOARD_MAX];


};


#include "DirectInput.inl"


#endif //__IGFEB11_IG500_DIRECTINPUT_H__




















































/*
//
//  Diploma of Interactive Gaming
//  Scene Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   directinput.h
//  Description :   for declaration file
//  Author      :   Jamie Smith
//  Mail        :   Jamie Smith@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_DIRECTINPUT_H__
#define __IGFEB11_DIRECTINPUT_H__

#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif

// Library Includes
#include <dinput.h> 

// Local Includes 
//#include "mouse.h"
#include "Vector2.h"

// Types

// Constants

// Prototypes
class CD3DRenderer; 

class CDirectInput
{
	// Member Functions
public:
	CDirectInput(); 
	virtual ~CDirectInput(); 

	virtual bool Initialise(HINSTANCE _hWindowInstance, HWND _hWindow);
	virtual bool InitialiseKeyboard();
	virtual bool InitialiseMouse();
	bool Update();	// Process.

	// For keyboard 
	inline bool IsKeyboardKeyPressed(unsigned int _uiKey); 

	// For mouse 
	void DrawCursor(CD3DRenderer* _pRenderer);

	inline const CVector2& GetMousePosition() const;
	inline bool IsMouseKeyPressed(unsigned int _uiKey);

	int GetChangeInZ();

protected:

private:

	// Member Variables
public:

protected:
	HWND m_hWnd; 
	DIDEVCAPS m_diMouseCaps; 
	DIMOUSESTATE m_diMouseState; 

	LPDIRECTINPUT8 m_pDInputInterface; 
	LPDIRECTINPUTDEVICE8 m_pInputKeyboard; 
	LPDIRECTINPUTDEVICE8 m_pInputMouse; 

	// For mouse 
		DIDEVCAPS m_diMouseCaps; 
	DIMOUSESTATE m_diMouseState; 
	CVector2 m_vecMousePos;
	DWORD m_pdwMouseInfo[5]; 

	unsigned int m_uiScreenWidth; 
	unsigned int m_uiScreenHeight; 

	// For keyboard 
	char m_cKeyBuffer[256]; 

private:

};

#include "directinput.inl" 
#endif //__IGFEB11_DIRECTINPUT_H__
*/