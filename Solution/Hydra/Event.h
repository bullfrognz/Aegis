//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Event.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_EVENT_H__
#define __IGFEB11_IG500_EVENT_H__


// Library Includes


// Local Includes


// Types


// Constants


// Prototypes


class CEvent
{

	// Member Functions
public:


	 CEvent(int _iSubject);
	~CEvent();


	// Inline Functions
	inline void SetData(void* _pData);


	inline unsigned int GetSubject() const;
	inline const void*  GetData()    const;


protected:


private:


	void Deinitialise();


	// Member Variables
protected:


	unsigned int m_uiSubject;


	void* m_pData;


private:


};

#include "Inline/Event.inl"

#endif //__IGFEB11_IG500_EVENT_H__