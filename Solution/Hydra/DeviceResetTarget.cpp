//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   DeviceResetTarget.cpp
//  Description :  
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes

// This Include
#include "DeviceResetTarget.h"

// Static Variables

// Static Function Prototypes
std::vector<CDeviceResetTarget*> CDeviceResetTarget::m_vecTargets;

// Implementation

CDeviceResetTarget::CDeviceResetTarget()
{
	m_vecTargets.push_back(this);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Removes self from device resetting.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CDeviceResetTarget::~CDeviceResetTarget()
{
	std::vector<CDeviceResetTarget*>::iterator iterTarget;
	iterTarget = m_vecTargets.begin();
		
	for (iterTarget; iterTarget != m_vecTargets.end(); ++iterTarget)
	{
		if ((*iterTarget) == this)
		{
			m_vecTargets.erase(iterTarget);

			break;
		}
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Tells all device reset targets that the device was lost.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/


void
CDeviceResetTarget::ExecuteDeviceLostFix()
{
	std::vector<CDeviceResetTarget*>::iterator iterTarget;
	iterTarget = m_vecTargets.begin();
		
	for (iterTarget; iterTarget != m_vecTargets.end(); ++iterTarget)
	{
		(*iterTarget)->OnDeviceLost();
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Tells all device reset targets that the device has been reset.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDeviceResetTarget::ExecuteDeviceResetFix()
{
	std::vector<CDeviceResetTarget*>::iterator iterTarget;
	iterTarget = m_vecTargets.begin();
		
	for (iterTarget; iterTarget != m_vecTargets.end(); ++iterTarget)
	{
		(*iterTarget)->OnDeviceReset();
	}
}