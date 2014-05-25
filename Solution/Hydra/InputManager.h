//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   InputManager.h
//  Description :   Manages direct input and xinput.
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_INPUTMANAGER_H__
#define __IGFEB11_IG500_INPUTMANAGER_H__


// Library Includes


// Local Includes


// Types


// Constants


// Prototypes
class CXInputController;
class CDirectInput;


class CInputManager
{

	// Member Functions
public:


	 CInputManager();
	~CInputManager();


	bool Initialise();
	void Process(float _fDeltaTick);


	void DisableInput();
	void EnableInput();


	// Inline Functions
	inline CXInputController& GetXInputController();
	inline CDirectInput&	  GetDirectInput();


protected:


private:


	void Deinitialise();


	CInputManager(const CInputManager& _krInputManager);
	CInputManager& operator = (const CInputManager& _krInputManager);


	// Member Variables
protected:


private:


	CXInputController* m_pXInputController;
	CDirectInput*	   m_pDirectInput;


};


#include "InputManager.inl"


#endif //__IGFEB11_IG500_INPUTMANAGER_H__