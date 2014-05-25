//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   MouseInputTarget.h
//  Description :   --------------------------
//  Comments    :
//  Author      :   Jamie SMith
//  Mail        :   Jamie.Smith@mediadesign.school.nz
//
//  Editor Log:
//  - 
//

#pragma once

#ifndef __IGFEB11_MOUSEINPUTTARGET_H__
#define __IGFEB11_MOUSEINPUTTARGET_H__

// Library Includes

// Local Includes

// Types

// Constants

// Prototypes
class CMouse;
//class CDirectInput;
//class CPlayerInput;


class CMouseInputTarget
{
	// Member Functions
public:
	         CMouseInputTarget();
	virtual ~CMouseInputTarget();

	virtual void HandleMouseInput(int _iButton, bool _Down) = 0;

	// Inline Functions

protected:

private:

	// Member Variables
protected:

private:

};

#endif // 