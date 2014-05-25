//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   XButtonTarget.h
//  Description :   Allows target to receive xbutton input.
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_XBUTTONTARGET_H__
#define __IGFEB11_IG500_XBUTTONTARGET_H__


// Library Includes


// Local Includes


// Types


// Constants


// Prototypes
enum EXInputButton;


class IXButtonTarget
{

	// Member Functions
public:


	         IXButtonTarget() {};
	virtual ~IXButtonTarget() {};


	virtual void HandleXButtonInput(EXInputButton _eXButton, bool _bDown = false) = 0;


	// Inline Functions


protected:


private:


	IXButtonTarget(const IXButtonTarget& _krXButtonTarget);
	IXButtonTarget& operator = (const IXButtonTarget& _krXButtonTarget);


	// Member Variables
protected:


private:


};


#endif //__IGFEB11_IG500_XBUTTONTARGET_H__