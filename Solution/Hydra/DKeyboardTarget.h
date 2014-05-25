//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   DKeyboardTarget.h
//  Description :   Allows target to recieve keyboard events.
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_DKEYBOARDTARGET_H__
#define __IGFEB11_IG500_DKEYBOARDTARGET_H__


// Library Includes


// Local Includes


// Types


// Constants


// Prototypes
enum EDInputKeyboard;


class IDKeyboardTarget
{

	// Member Functions
public:


	         IDKeyboardTarget() {};
	virtual ~IDKeyboardTarget() {};


	virtual void HandleDKeyboardInput(EDInputKeyboard _eDKebyoard, bool _bDown = false) = 0;


	// Inline Functions


protected:


private:


	IDKeyboardTarget(const IDKeyboardTarget& _krKeyboardTarge);
	IDKeyboardTarget& operator = (const IDKeyboardTarget& _krKeyboardTarge);


	// Member Variables
protected:


private:


};


#endif //__IGFEB11_IG500_DKEYBOARDTARGET_H__