//
//  Diploma of Interactive Gaming
//  Scene Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Mouse.h
//  Description :   Mouse declaration (header) file
//  Author      :   Jamie.Smith
//  Mail        :   Jamie.Smith@mediadesign.school.nz
//

#pragma once

#ifndef __IGFEB11_MOUSE_H__
#define __IGFEB11_MOUSE_H__

// Library Includes

// Local Includes
#include "Defines.h"
#include "directinput.h"

//#include "Scene.h"

// Types

// Constants

// Prototypes
class CDirectInput; 
class CVector2;
class CMouseInputTarget;
//class CXInputController; 

class CMouse
{
// Member Functions
public:
	CMouse(); 
	~CMouse(); 

	bool Initialise(); 
	void Process(float _fDeltaTick); 

	//void UpdateMouseState(DIMOUSESTATE* _pMouseState);

	CVector2 GetMouseCoOrds();

	void AddDirectTarget(int _iButton, CMouseInputTarget* _pTarget);

	void SendButtonStateToTargets(int _iButton, bool _Down);

	void CheckMouseState(DIMOUSESTATE* _pMouseState);

protected:
	bool IsButtonPressed(int _iButton, DIMOUSESTATE* _pMouseState);

private:

// Member Variables
public:

protected:
	DIMOUSESTATE m_diMouseState;

	bool m_bButtons[8];
	bool m_bOldButtons[8];

	std::multimap< int , CMouseInputTarget* > m_pMouseTargets;

private:

};


#endif // 

