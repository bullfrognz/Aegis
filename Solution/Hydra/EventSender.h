//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   EventSender.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_EVENTSENDER_H__
#define __IGFEB11_IG500_EVENTSENDER_H__


// Library Includes
#include <map>


// Local Includes
#include "EventTarget.h"


// Types


// Constants


// Prototypes
class CEvent;


template <typename EventEnumType>
class CEventSender
{

	// Member Functioens
public:


	CEventSender::CEventSender()
	{
	}


	virtual CEventSender::~CEventSender()
	{
	}


	// Inline Functions


protected:


	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* Sends the event to all targets attached to the event subject.
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/


	void
	CEventSender::SendEventToTargets(CEvent& _rEventData)
	{
		std::multimap<EEventSubject, CEventTarget*>& mmapEventTargets = CEventTarget::GetEventTargets();


		//Set default variables
		std::multimap<EEventSubject, CEventTarget*>::iterator iterEventTarget;
		std::pair< std::multimap<EEventSubject, CEventTarget*>::iterator ,
				   std::multimap<EEventSubject, CEventTarget*>::iterator > retEnumTypeGroup;


		//Get event subject
		EEventSubject eSubject = static_cast<EEventSubject>(_rEventData.GetSubject());


		//Find event enum type group within map
		retEnumTypeGroup = mmapEventTargets.equal_range(eSubject);


		//Check group has members
		if (retEnumTypeGroup.first != retEnumTypeGroup.second)
		{
			iterEventTarget = retEnumTypeGroup.first;

			
			//Loop through members within the group
			while (iterEventTarget != retEnumTypeGroup.second)
			{
				//Check event target was removed
				if ((*iterEventTarget).second == 0)
				{
					iterEventTarget = mmapEventTargets.erase(iterEventTarget);
				}
				else
				{
					//Send member the event data
					(*iterEventTarget).second->HandleRecievedEvent(&_rEventData);
					
					//Increment the iter
					++ iterEventTarget;
				}
			}
		}
	}


private:


	CEventSender(const CEventSender& _krEventSender);
	CEventSender& operator = (const CEventSender& _krEventSender);


	// Member Variables
protected:


private:


	


};


#endif //__IGFEB11_IG500_EVENTSENDER_H__