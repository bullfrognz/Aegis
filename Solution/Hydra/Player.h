//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Player.h
//  Description :  
//  Comments    :
//  Author      :   Jamie SMith
//  Mail        :   Jamie.Smith@mediadesign.school.nz
//
//  Editor Log:
//  - 
//

#pragma once

#ifndef __IGFEB11_PLAYER_H__
#define __IGFEB11_PLAYER_H__

// Library Includes

// Local Includes
#include "EventTarget.h"
#include <cassert>

// Types

// Constants

// Prototypes
class CINIParser;

class CPlayer : public CEventTarget
{
	// Member Functions
public:
	         CPlayer();
	virtual ~CPlayer();

	bool Initialise(const char* _kcFileName);

	void HandleRecievedEvent(const CEvent* _kpEventData);

	// Inline Functions
	inline void SetLives(int _i);
	inline void SetGold(unsigned int _ui);

	inline int GetLives() const;
	inline unsigned int GetGold() const;


protected:

	
private:

	// Member Variables
protected:
	int m_iLives;
	unsigned int m_uiGold;

private:

};

#include "Player.inl" 
#endif // 