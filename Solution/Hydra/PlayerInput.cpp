//
//  Diploma of Interactive Gaming
//  Scene Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   playerinput.cpp
//  Description :   PlayerInput implementation (source) file
//  Author      :   Jamie.Smith 
//  Mail        :   Jamie.Smith @mediadesign.school.nz 
//

// Library Includes

// Local Includes
//#include "Scene.h" 
#include "viewport.h" 
#include "directinput.h" 
#include "macros.h"

// This Include
#include "playerinput.h"

// Static Variables
int CPlayerInput::sm_iNumControlers = 0;

// Static Function Prototypes

// Implementation

/** 
*
* Class Constructor 
*
*/ 
CPlayerInput::CPlayerInput() 
: m_fKeyboardSpeedModifier(13.3f) 
, m_fControllerSpeedModifier(3.9f)
, m_fScroll(0)
, m_fOldScroll(0)
, m_iScroll(3)
, m_bDisable(0)
, m_sFrameSkip(5)
, m_bController(0)
{
	for(int i  = 0; i < 255; ++i)
	{
		m_bKeys[i] = 0;
		m_bOldKeys[i] = 0;
	}

	for(int i = 0; i < 8; ++i)
	{
		m_bButtons[i] = 0;
		m_bOldButtons[i] = 0;
	}
}

/** 
*
* Class Destructor 
*
*/ 
CPlayerInput::~CPlayerInput()
{

}

/** 
*
* Initialise the Player input class 
* 
* @author Jamie.Smith  
* @return Initialisation status true or false 
*
*/ 
bool
CPlayerInput::Initialise(HINSTANCE _hWindowInstance, HWND _hWindow, CXInputController* _pXInput)
{
	/*
	bool bIsInitialsed = true; 

	InitialiseXInputTarget(_pXInput);

	// Initialise the DirectInput Class
	bIsInitialsed = m_DInputDevice.Initialise(_hWindowInstance, _hWindow);

	m_pXInput = _pXInput;

	*/
	return(true);
}

/** 
*
* Process for active and inactive controllers 
* 
* @author Jamie.Smith  
* @param _fDeltaTick time elapsed between frames 
* @return void 
*
*/ 
void
CPlayerInput::Process(float _fDeltaTick)
{
	/*
	bool bFocused = CApplication::GetInstance().GetGameWindow().IsFocused();

	if(m_sFrameSkip > 0)
	{
		--m_sFrameSkip;
	}
	else if(!m_bDisable && bFocused == true && m_bController == false)
	{
		// update the device 
		m_DInputDevice.Update(); 

		DispatchKeyboardKeys();
		DispatchMouseKeys();
		ShowCursor(TRUE);
	}

	if(m_bController)
	{		
		ShowCursor(FALSE);
	}
	*/
}

/** 
*
* Set the keyboard movement speed modifier 
*
* @author Jamie.Smith  
* @param _f the new speed modidfier value 
* @return void 
*
*/ 
void 
CPlayerInput::SetKeyboardModifier(float _f) 
{
	m_fKeyboardSpeedModifier = _f; 
}

/**
*
* checks if any keyboard keys were pushed
*
* @author Jamie.Smith   
* @return void 
*
*/ 
void 
CPlayerInput::DispatchKeyboardKeys() 
{	
	/*
	for(int i = 0; i< 255; ++i)
	{
		m_bKeys[i] = m_DInputDevice.IsKeyboardKeyPressed(i);

		if(m_bKeys[i] != m_bOldKeys[i])
		{
			std::multimap< int , CPlayerInputTarget* >::iterator iterTarget;
			std::pair< std::multimap< int , CPlayerInputTarget* >::iterator,
					   std::multimap< int , CPlayerInputTarget* >::iterator > ret;

			ret = m_pDirectTargets.equal_range(i);

			if (ret.first != ret.second)
			{
				for (iterTarget = ret.first; iterTarget != ret.second; ++iterTarget)
				{
					(*iterTarget).second->HandleDirectInput( i , m_bKeys[i] );
				}
			}

			m_bOldKeys[i] = m_bKeys[i];
		}
	}
	*/
}

/**
*
* adds the mouse button and which target wants to receive it, to a map 
*
* @author Jamie.Smith  
* @param _iButton the key value 
* @param _pTarget the target
* @return void 
*
*/
void
CPlayerInput::AddMouseTarget(int _iButton, CPlayerInputTarget* _pTarget)
{
	//m_pMouseTargets.insert( std::pair< int , CPlayerInputTarget* >( _iButton , _pTarget ) );
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
CPlayerInput::DispatchMouseKeys()
{
	/*
	std::multimap< int , CPlayerInputTarget* >::iterator iterTarget;
	std::pair< std::multimap< int , CPlayerInputTarget* >::iterator,
			   std::multimap< int , CPlayerInputTarget* >::iterator > ret;

	m_fScroll = static_cast<float>(m_DInputDevice.GetChangeInZ());	

	for(int i = 0; i < 4; ++i)
	{
		m_bButtons[i] = m_DInputDevice.IsMouseKeyPressed(i);

		if(m_bOldButtons[i] != m_bButtons[i] || m_fScroll != 0)
		{
			ret = m_pMouseTargets.equal_range(i);

			if (ret.first != ret.second)
			{
				for (iterTarget = ret.first; iterTarget != ret.second; ++iterTarget)
				{
					(*iterTarget).second->HandleMouseInput( i , m_bButtons[i], m_fScroll);
				}
			}
		}

		m_bOldButtons[i] = m_bButtons[i];
		m_fOldScroll = m_fScroll;		
	}	
	*/
}

/**
*
* adds the key type and which target wants to receive it, to a map 
*
* @author Jamie.Smith  
* @param _iButton the key value 
* @param _pTarget the target
* @return void 
*
*/ 
void
CPlayerInput::AddDirectTarget(int _iButton, CPlayerInputTarget* _pTarget)
{
	m_pDirectTargets.insert( std::pair< int , CPlayerInputTarget* >( _iButton , _pTarget ) );
} 

/**
*
* Returns the mouse current position
*
* @author Jamie.Smith  
* @return const CVector2&
*
*/
const CVector2&
CPlayerInput::GetMousePos() const
{
	return(m_DInputDevice.GetMousePosition());
}

/**
*
* Sets disable true or false
*
* @author Jamie.Smith  
* @return void
*
*/
void
CPlayerInput::DisableInput(bool _bDisable)
{
	m_bDisable = _bDisable;

	if(_bDisable == false)
	{
		m_sFrameSkip = 5;
	}
}

/** 
*
* Handles the input of the XBox 360 controller
* 
* @author Jamie.Smith  
* @Param1 _eButton the button which has been pushed
* @Param2 _fValue the amount the button has been pushed
* @return void
*
*/
void 
CPlayerInput::HandleControllerInput(EXInputButton _eButton, float _fValue)
{

}

/** 
*
* Checks whether the controller is active then sets a bool
* 
* @author Jamie.Smith
* @Param1 _bActive if the controller is active
* @return void
*
*/
void 
CPlayerInput::SetControllerActive(bool _bActive)
{
	//m_bController = _bActive;
}

/** 
*
* Sets up which Xbox controller buttons it wishes to check the changes of
* 
* @author Jamie.Smith  
* @Param1 _pPlayerInput the pointer to player input
* @return void
*
*/
void 
CPlayerInput::InitialiseXInputTarget(CXInputController* _pXInput)
{
	//_pXInput->AddIsActiveTarget(this);
}