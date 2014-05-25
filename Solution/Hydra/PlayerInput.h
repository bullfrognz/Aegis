//
//  Diploma of Interactive Gaming
//  Scene Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   playerinput.h
//  Description :   PlayerInput declaration (header) file
//  Author      :   Jamie.Smith
//  Mail        :   Jamie.Smith@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_PLAYERINPUT_H__
#define __IGFEB11_PLAYERINPUT_H__

// Library Includes

// Local Includes
#include "defines.h"
#include "camera.h"
#include "gamescene.h"
#include "DirectInput.h"
#include "XInputController.h"

// Types

// Constants

// Prototypes
class CPlayerInputTarget;
class CVector2;
class CXInputController;

class CPlayerInput : public CXInputTarget
{
// Member Functions
public:
	CPlayerInput(); 
	~CPlayerInput(); 

	bool Initialise(HINSTANCE _hWindowInstance, HWND _hWindow, CXInputController* _pXInput); 
	void Process(float _fDeltaTick); 

	void SetKeyboardModifier(float _f); 
	void SetControllerModifier(float _f); 

	inline float GetKeyboardSpeedModifier() const;
	inline float GetControllerSpeedModifier() const;

	static int GetNumControllers();

	void DispatchKeyboardKeys();
	void DispatchMouseKeys();

	void AddDirectTarget(int _iButton, CPlayerInputTarget* _pTarget);
	void AddMouseTarget(int _iButton, CPlayerInputTarget* _pTarget);

	inline CDirectInput& GetDirectInput();

	void DisableInput(bool _bDisable);

	const CVector2& GetMousePos() const;

protected:
	virtual void HandleControllerInput(EXInputButton _eButton, float _fValue);

	virtual void SetControllerActive(bool _bActive);

	virtual void InitialiseXInputTarget(CXInputController* _pXInput);
	 

private:

// Member Variables
public:

protected:
	bool m_bKeys[255];
	bool m_bOldKeys[255];

	CDirectInput m_DInputDevice; 

	float m_fKeyboardSpeedModifier; 
	float m_fControllerSpeedModifier; 

	float m_fScroll;
	float m_fOldScroll;

	static int sm_iNumControlers; 

	std::multimap< int , CPlayerInputTarget* > m_pDirectTargets;

	bool m_bButtons[8];
	bool m_bOldButtons[8];

	std::multimap< int , CPlayerInputTarget* > m_pMouseTargets;

	int m_iScroll;

	bool m_bDisable;

	short m_sFrameSkip;

	CXInputController* m_pXInput;

	bool m_bController;

private:

};

#include "playerinput.inl" 
#endif // __IGFEB11_PLAYERINPUT_H__

