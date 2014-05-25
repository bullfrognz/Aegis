//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   XTriggerTarget.h
//  Description :   Allows target to recieve x trigger input.
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_XTRIGGERTARGET_H__
#define __IGFEB11_IG500_XTRIGGERTARGET_H__


// Library Includes


// Local Includes


// Types


// Constants


// Prototypes
enum EXInputTrigger;


class IXTriggerTarget
{

	// Member Functions
public:


	         IXTriggerTarget() {};
	virtual ~IXTriggerTarget() {};


	virtual void HandleXTriggerInput(EXInputTrigger _eXTrigger, float _fValue = 0.0f) = 0;


	// Inline Functions


protected:


private:


	IXTriggerTarget(const IXTriggerTarget& _krXTriggerTarget);
	IXTriggerTarget& operator = (const IXTriggerTarget& _krXTriggerTarget);


	// Member Variables
protected:


private:


};


#endif //__IGFEB11_IG500_XTRIGGERTARGET_H__