//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   PlayerInputTarget.h
//  Description :   --------------------------
//  Comments    :
//  Author      :   Jamie SMith
//  Mail        :   Jamie.Smith@mediadesign.school.nz
//
//  Editor Log:
//  - 
//

#pragma once

#ifndef __IGFEB11_PLAYERINPUTTARGET_H__
#define __IGFEB11_PLAYERINPUTTARGET_H__

// Library Includes

// Local Includes

// Types

// Constants

// Prototypes
class CDirectInput;
class CPlayerInput;


class CPlayerInputTarget
{
	// Member Functions
public:
	         CPlayerInputTarget();
	virtual ~CPlayerInputTarget();

	virtual void HandleDirectInput(int _iButton, bool _Down) = 0;
	virtual void HandleMouseInput(int _iButton, bool _Down, float _fScroll) = 0; 


	// Inline Functions

protected:

private:

	// Member Variables
protected:

private:

};

#endif // 