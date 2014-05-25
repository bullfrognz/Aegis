//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   DeviceResetTarget.h
//  Description :  
//  Comments    :
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//

#pragma once

#ifndef __IGFEB11_IG500_DEVICERESETTARGET_H__
#define __IGFEB11_IG500_DEVICERESETTARGET_H__

// Library Includes
#include <vector>

// Local Includes

// Types

// Constants

// Prototypes


class CDeviceResetTarget
{
	// Member Functions
public:
	         CDeviceResetTarget();
	virtual ~CDeviceResetTarget();

	static void	ExecuteDeviceLostFix();
	static void ExecuteDeviceResetFix();

	// Inline Functions

protected:
	virtual void OnDeviceLost() = 0;
	virtual void OnDeviceReset() = 0;

private:

	// Member Variables
protected:

private:
	static std::vector<CDeviceResetTarget*> m_vecTargets;


};

#endif // __IGFEB11_IG500_DEVICERESETTARGET_H__