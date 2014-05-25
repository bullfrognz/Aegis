//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   DMouseTarget.h
//  Description :   Allows target to receive mouse input.
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_DMOUSETARGET_H__
#define __IGFEB11_IG500_DMOUSETARGET_H__


// Library Includes


// Local Includes


// Types


// Constants


// Prototypes
enum EDInputMouse;


class IDMouseTarget
{

	// Member Functions
public:


	         IDMouseTarget() {};
	virtual ~IDMouseTarget() {};


	virtual void HandleDMouseInput(EDInputMouse _eDMouse, bool _bDown, long _lValue) = 0;


	// Inline Functions


protected:


private:


	IDMouseTarget(const IDMouseTarget& _krMouseTarget);
	IDMouseTarget& operator = (const IDMouseTarget& _krMouseTarget);


	// Member Variables
protected:


private:


};


#endif //__IGFEB11_IG500_DMOUSETARGET_H__