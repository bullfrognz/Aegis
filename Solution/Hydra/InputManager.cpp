//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   InputManager.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Application.h"
#include "Window.h"
#include "Macros.h"
#include "XInputController.h"
#include "DirectInput.h"


// This Include
#include "InputManager.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* InputManager class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CInputManager::CInputManager()
: m_pXInputController(0)
, m_pDirectInput(0)
{
	//Empty
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* InputManager class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CInputManager::~CInputManager()
{
	Deinitialise();
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function initialisings the class instance before use.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CInputManager::Initialise()
{
	m_pXInputController = new CXInputController();
	m_pXInputController->Initialise();


	m_pDirectInput = new CDirectInput();
	m_pDirectInput->Initialise();


	EnableInput();


	return (true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Processes the mouse and keyboard if controller is not plugged in or processes the controller.
*
* @author Bryce Booth
* @param _fDeltaTick	Time since last process.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CInputManager::Process(float _fDeltaTick)
{
	bool bFocused = CApplication::GetInstance().GetGameWindow().IsFocused();


	if (bFocused)
	{
		m_pXInputController->Process(_fDeltaTick);


		if (m_pXInputController->IsPluggedIn() == false || m_pXInputController->IsDisabled() == true)
		{
			m_pDirectInput->Process();
		}
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Stops direct input and xinput controller from sending messages.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CInputManager::DisableInput()
{
	m_pXInputController->SetDisabled(true);
	m_pDirectInput->SetDisabled(true);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Enables direct input and xinput controller to start sending messages again
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CInputManager::EnableInput()
{
	m_pXInputController->SetDisabled(false);
	m_pDirectInput->SetDisabled(false);
}









/********************************
            Protected
*********************************/









/********************************
            Private
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function deinitialises the class instance by freeing memory and calling other necessary functions.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CInputManager::Deinitialise()
{
	FW_DELETE(m_pXInputController);
	FW_DELETE(m_pDirectInput);
}