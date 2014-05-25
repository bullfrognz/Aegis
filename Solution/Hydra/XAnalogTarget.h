//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   XAnalogTarget.h
//  Description :   Allows target to receive xanalog input.
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_XANALOGTARGET_H__
#define __IGFEB11_IG500_XANALOGTARGET_H__


// Library Includes


// Local Includes


// Types


// Constants


// Prototypes
enum EXInputAnalog;


class IXAnalogTarget
{

	// Member Functions
public:


	         IXAnalogTarget() {};
	virtual ~IXAnalogTarget() {};


	virtual void HandleXAnalogInput(EXInputAnalog _eXAnalog, float _fValue = 0.0f) = 0;


	// Inline Functions


protected:


private:


	IXAnalogTarget(const IXAnalogTarget& _krXAnalogTarget);
	IXAnalogTarget& operator = (const IXAnalogTarget& _krXAnalogTarget);


	// Member Variables
protected:


private:


};


#endif //__IGFEB11_IG500_XANALOGUETARGET_H__