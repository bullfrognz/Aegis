//
//  Diploma of Interactive Gaming
//  Scene Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :	Mouse.cpp
//  Description :   Mouse implementation (source) file
//  Author      :   Jamie.Smith 
//  Mail        :   Jamie.Smith @mediadesign.school.nz 
//

// Library Includes

// Local Includes
#include "vector2.h"
#include "Mouse.h"
#include "playerinput.h"
#include "MouseINputTarget.h"

// This Include

// Static Variables

// Static Function Prototypes

// Implementation

/** 
*
* Class Constructor 
*
*/ 
CMouse::CMouse() 
{
	for(int i = 0; i < 8; ++i)
	{
		m_bOldButtons[i] = 0;
	}

	for(int i = 0; i < 8; ++i)
	{
		m_bButtons[i] = 0;
	}
}

/** 
*
* Class Destructor 
*
*/ 
CMouse::~CMouse()
{
	
}

/**
*
* Initialises the mouse
*
* @author Jamie.Smith  
* @return bool
*
*/
bool 
CMouse::Initialise()
{
	return(true);
}

/**
*
* Processes the mouse
*
* @author Jamie.Smith  
* @param _fDeltaTick the delta tick
* @return void 
*
*/
void
CMouse::Process(float _fDeltaTick)
{
	//Empty. For future use?
}

/**
*
* Checks if the buttons are pressed then sends them to the targets
*
* @author Jamie.Smith  
* @param _pMouseState the buffer in wich the mouse info is held
* @return void 
*
*/
void
CMouse::CheckMouseState(DIMOUSESTATE* _pMouseState)
{
	for(int i = 0; i< 8; ++i)
	{
		m_bButtons[i] = IsButtonPressed(i, _pMouseState);

		if(m_bButtons[i] != m_bOldButtons[i])
		{
			SendButtonStateToTargets(i, m_bButtons[i]);
			m_bOldButtons[i] = m_bButtons[i];
		}		
	}
}

/**
*
* adds the button and which target wants to receive it to a map 
*
* @author Jamie.Smith  
* @param _iButton the button value 
* @param _pTarget the target
* @return void 
*
*/ 
void
CMouse::AddDirectTarget(int _iButton, CMouseInputTarget* _pTarget)
{
	m_pMouseTargets.insert( std::pair< int , CMouseInputTarget* >( _iButton , _pTarget ) );
}  

/**
*
* Sends the buttons state to its required target
*
* @author Jamie.Smith  
* @param _iButton the key value 
* @param _Down wiether or not the key was pushed down or up
* @return void 
*
*/
void 
CMouse::SendButtonStateToTargets(int _iButton, bool _Down)
{
	std::multimap< int , CMouseInputTarget* >::iterator iterTarget;
	std::pair< std::multimap< int , CMouseInputTarget* >::iterator,
		       std::multimap< int , CMouseInputTarget* >::iterator > ret;

	ret = m_pMouseTargets.equal_range(_iButton);

	if (ret.first != ret.second)
	{
		for (iterTarget = ret.first; iterTarget != ret.second; ++iterTarget)
		{
			(*iterTarget).second->HandleMouseInput( _iButton , _Down );
		}
	}
}

/**
*
* Returns the mouse coordaniates
*
* @author Jamie.Smith  
* @return Cvector2
*
*/
CVector2
CMouse::GetMouseCoOrds()
{
	CVector2 Temp;

	Temp.x = static_cast<float>(m_diMouseState.lX);
	Temp.y = static_cast<float>(m_diMouseState.lY);

	return(Temp);
}

/**
*
* Checks if the buttons are pressed
*
* @author Jamie.Smith  
* @param _iButton the key value 
* @param _pMouseState the buffer in wich the mouse info is held
* @return bool 
*
*/
bool
CMouse::IsButtonPressed(int _iButton, DIMOUSESTATE* _pMouseState)
{
	if(_pMouseState->rgbButtons[_iButton] & 0x80)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}
