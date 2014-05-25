//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   EventTarget.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_EVENTTARGET_H__
#define __IGFEB11_IG500_EVENTTARGET_H__


// Library Includes
#include <map>


// Local Includes


// Types
enum EEventSubject
{
	EVENTSUBJECT_TOWERBUILD,
	EVENTSUBJECT_TOWERUPGRADE,
	EVENTSUBJECT_TOWERSELL,
	EVENTSUBJECT_TOWERDELETE,


	EVENTSUBJECT_ENEMYSPAWN,
	EVENTSUBJECT_ENEMYLASTWAYPOINT,
	EVENTSUBJECT_ENEMYDEATH,
	EVENTSUBJECT_ENEMYDELETE
};


// Constants


// Prototypes
class CEvent;


class CEventTarget
{

	// Member Functions
public:


	         CEventTarget();
	virtual ~CEventTarget();


	void Register(EEventSubject _eEventSubject);
	void Deregister(EEventSubject _eEventSubject);


	virtual void HandleRecievedEvent(const CEvent* _kpEventData) = 0;


	// Inline Functions
	static inline void ClearAllEvents();
	static inline std::multimap<EEventSubject, CEventTarget*>& GetEventTargets();


protected:


private:


	// Member Variables
protected:


private:


	static std::multimap<EEventSubject, CEventTarget*> m_mmapEventTargets;


};


#include "Inline/EventTarget.inl"


#endif //__IGFEB11_IG500_EVENTTARGET_H__