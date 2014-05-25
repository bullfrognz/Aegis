//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   EventTarget.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Macros.h"


// This Include
#include "EventTarget.h"


// Static Variables
std::multimap<EEventSubject, CEventTarget*> CEventTarget::m_mmapEventTargets;


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* EventTarget class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CEventTarget::CEventTarget()
{
	//Empty
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* EventTarget class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CEventTarget::~CEventTarget()
{
	//Empty
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Registers event target for chosen event.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEventTarget::Register(EEventSubject _eEventSubject)
{
	m_mmapEventTargets.insert( std::pair<EEventSubject, CEventTarget*>(_eEventSubject, this) );
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Registers event target for chosen event.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void 
CEventTarget::Deregister(EEventSubject _eEventSubject)
{
	//Set default variables
	std::multimap<EEventSubject, CEventTarget*>::iterator iterEventTarget;
	std::pair< std::multimap<EEventSubject, CEventTarget*>::iterator ,
			   std::multimap<EEventSubject, CEventTarget*>::iterator > retEventTargetsGroup;
	bool bTargetRemoved = false;


	//Find event enum type group within map
	retEventTargetsGroup = m_mmapEventTargets.equal_range(_eEventSubject);


	//Check group has members
	if (retEventTargetsGroup.first != retEventTargetsGroup.second)
	{
		//Loop through members within the group
		for (iterEventTarget = retEventTargetsGroup.first; iterEventTarget != retEventTargetsGroup.second; ++iterEventTarget)
		{
			//Check this is the target
			if ((*iterEventTarget).second == this)
			{
				//Set pointer to null for deletion in sendeventtotargets function
				(*iterEventTarget).second = 0;


				//Set target removed to true
				bTargetRemoved = true;


				break;
			}
		}
	}


	//Check target was found and removed
	//LOG_ERROR(bTargetRemoved == false, "The target does not belong to this event sender.");
}








/********************************
            Protected
*********************************/









/********************************
            Private
*********************************/