//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   XInputTarget.h
//  Description :   --------------------------
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_XINPUTTARGET_H__
#define __IGFEB11_IG500_XINPUTTARGET_H__


// Library Includes


// Local Includes


// Types


// Constants


// Prototypes
enum EXInput;


class IXInputTarget
{

	// Member Functions
public:


	         IXInputTarget() {};
	virtual ~IXInputTarget() {};


	virtual void HandleControllerInput(EXInput _eButton, float _fValue = 0.0f) = 0;


	// Inline Functions


protected:


private:


	IXInputTarget(const IXInputTarget& _krXInputTarget);
	IXInputTarget& operator = (const IXInputTarget& _krXInputTarget);


	// Member Variables
protected:


private:


};


#endif //__IGFEB11_IG500_XINPUTTARGET_H__





























/*
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   XInputControllerTarget.h
//  Description :   --------------------------
//  Comments    :
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//

#pragma once

#ifndef __IGFEB11_IG300_XINPUTCONTROLLERTARGET_H__
#define __IGFEB11_IG300_XINPUTCONTROLLERTARGET_H__

// Library Includes

// Local Includes

// Types

// Constants

// Prototypes
class CXInputController;


class IXInputControllerTarget
{
	// Member Functions
public:
	         IXInputControllerTarget();
	virtual ~IXInputControllerTarget();

	virtual void HandleControllerInput(EXInput _eButton, float _fValue = 0.0f) = 0;

	// Inline Functions

protected:

private:

	// Member Variables
protected:

private:

};

#endif // __IGFEB11_IG300_XINPUTCONTROLLERTARGET_H__
*/