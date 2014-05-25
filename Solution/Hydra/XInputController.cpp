//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   XInputController.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <cmath>


// Local Includes
#include "Application.h"
#include "Window.h"
#include "Scene.h"
#include "LogWindow.h"
#include "XButtonTarget.h"
#include "XAnalogTarget.h"
#include "XTriggerTarget.h"


// This Include
#include "XInputController.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* XInputController class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CXInputController::CXInputController()
: m_eRumbleLevelLeft(XRUMBLELVL_0)
, m_eRumbleLevelRight(XRUMBLELVL_0)
, m_uiLastPacketId(0)
, m_uiThumbLeftDeadZone(0)
, m_fLRumbleTimer(0)
, m_fRRumbleTimer(0)
, m_bPluggedIn(false)
, m_bDisabled(true)
{
	ZeroMemory(&m_fAnalogueStates, sizeof(float) * 4);
	ZeroMemory(&m_fPreviousAnalogueStates, sizeof(float) * 4);


	ZeroMemory(&m_fTriggerStates, sizeof(float) * 2);
	ZeroMemory(&m_fPreviousTriggerStates, sizeof(float) * 2);


	ZeroMemory(&m_bButtonStates, sizeof(bool) * 14);
	ZeroMemory(&m_bPreviousButtonStates, sizeof(bool) * 14);
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* XInputController class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CXInputController::~CXInputController()
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
CXInputController::Initialise()
{
	SaveCurrentState();


	RefreshPluggedIn();


	return (true);
}


void
CXInputController::Process(float _fDeltaTick)
{
	if (m_bDisabled == false)
	{
		RefreshPluggedIn();


		//Check if controller is plugged in
		if (m_bPluggedIn == true)
		{
			//Default varaibles
			XINPUT_STATE xState;
			DWORD dwResult = 0;
				
				
			//Get xinput state
			dwResult = XInputGetState(0, &xState);


			//Check if packets differ
			if (xState.dwPacketNumber != m_uiLastPacketId)
			{
				//Read analouge sticks
				ReadButtonStates(xState.Gamepad);
				ReadAnalogueStates(xState.Gamepad);
				ReadTriggerStates(xState.Gamepad);


				DispatchButtonStates();
				DispatchAnalogStates();
				DispatchTriggerStates();


				StoreCurrentStates();


				//Set last packet
				m_uiLastPacketId = xState.dwPacketNumber;
			}


			ProcessRumble(_fDeltaTick);
		}
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Adds xinput target for chosen button.
*
* @author Bryce Booth
* @param _eXButton	The button that the target wants to know about.
* @param _pTarget	The pointer to the target that wants to know about the button.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::AddTarget(EXInputButton _eXButton, IXButtonTarget* _pTarget)
{
	m_vecXButtonTargets[_eXButton].push_back(_pTarget);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Adds xinput target for chosen trigger.
*
* @author Bryce Booth
* @param _eXTrigger	The trigger that the target wants to know about.
* @param _pTarget	The pointer to the target that wants to know about the button.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::AddTarget(EXInputTrigger _eXTrigger, IXTriggerTarget* _pTarget)
{
	m_vecXTriggerTargets[_eXTrigger].push_back(_pTarget);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Adds xinput target for chosen analogue.
*
* @author Bryce Booth
* @param _eXButton	The analogue that the target wants to know about.
* @param _pTarget	The pointer to the target that wants to know about the button.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::AddTarget(EXInputAnalog _eXAnalogue, IXAnalogTarget* _pTarget)
{
	m_vecXAnalogueTargets[_eXAnalogue].push_back(_pTarget);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Removes the target from recieving selected button messages from this controller.
*
* @author Bryce Booth
* @param _eXButton	Select button to stop receiving messages for.
* @param _pTarget	Instance of the reciever.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::RemoveTarget(EXInputButton _eXButton, IXButtonTarget* _pTarget)
{
	//Get number of targets
	int iNumTargets = static_cast<int>(m_vecXButtonTargets[_eXButton].size());


	//Loop through number of targets
	for (int i = 0; i < iNumTargets; ++i)
	{
		if (m_vecXButtonTargets[_eXButton][i] == _pTarget)
		{
			//Erase target from group
			m_vecXButtonTargets[_eXButton].erase(m_vecXButtonTargets[_eXButton].begin() + i);

			
			break;
		}
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Removes the target from recieving selected trigger messages from this controller.
*
* @author Bryce Booth
* @param _eXButton	Select trigger to stop receiving messages for.
* @param _pTarget	Instance of the reciever.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::RemoveTarget(EXInputTrigger _eXTrigger, IXTriggerTarget* _pTarget)
{
	//Get number of targets
	int iNumTargets = static_cast<int>(m_vecXTriggerTargets[_eXTrigger].size());


	//Loop through number of targets
	for (int i = 0; i < iNumTargets; ++i)
	{
		if (m_vecXTriggerTargets[_eXTrigger][i] == _pTarget)
		{
			//Erase target from group
			m_vecXTriggerTargets[_eXTrigger].erase(m_vecXTriggerTargets[_eXTrigger].begin() + i);

			
			break;
		}
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Removes the target from recieving selected analogue messages from this controller.
*
* @author Bryce Booth
* @param _eXButton	Select analogue to stop receiving messages for.
* @param _pTarget	Instance of the reciever.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::RemoveTarget(EXInputAnalog _eXAnalogue, IXAnalogTarget* _pTarget)
{
	//Get number of targets
	int iNumTargets = static_cast<int>(m_vecXAnalogueTargets[_eXAnalogue].size());


	//Loop through number of targets
	for (int i = 0; i < iNumTargets; ++i)
	{
		if (m_vecXAnalogueTargets[_eXAnalogue][i] == _pTarget)
		{
			//Erase target from group
			m_vecXAnalogueTargets[_eXAnalogue].erase(m_vecXAnalogueTargets[_eXAnalogue].begin() + i);

			
			break;
		}
	}
}









/********************************
            Protected
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Processes the rumble of the controller.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::ProcessRumble(float _fDeltaTick)
{
	//Set default varaibles
	bool bRefreshRumbleState = false;


	if (m_fLRumbleTimer > 0.0f)
	{
		m_fLRumbleTimer -= _fDeltaTick;


		if (m_fLRumbleTimer <= 0.0f)
		{
			m_eRumbleLevelLeft = XRUMBLELVL_0;


			bRefreshRumbleState = true;
		}
	}


	if (m_fRRumbleTimer > 0.0f)
	{
		m_fRRumbleTimer -= _fDeltaTick;


		if (m_fLRumbleTimer <= 0.0f)
		{
			m_eRumbleLevelRight = XRUMBLELVL_0;


			bRefreshRumbleState = true;
		}
	}


	if (bRefreshRumbleState)
	{
		RefreshRumbleState();
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Refreshes the rumble state of the controller.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::RefreshRumbleState()
{
	if (m_bPluggedIn && m_bDisabled == false)
	{
		XINPUT_VIBRATION xVibration;


		xVibration.wLeftMotorSpeed = m_eRumbleLevelLeft;
		xVibration.wRightMotorSpeed = m_eRumbleLevelRight;


		XInputSetState(0, &xVibration);
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Refreshes if the controller is plugged in.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::RefreshPluggedIn()
{
	//Default varaibles
	XINPUT_STATE xState;
	DWORD dwResult = 0;
		
		
	//Get xinput state
	dwResult = XInputGetState(0, &xState);


	//Set plugged in
	m_bPluggedIn = (dwResult == ERROR_SUCCESS) ? true : false;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Saves the current state of the controller.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::SaveCurrentState()
{
	//Default varaibles
	XINPUT_STATE xState;
	DWORD dwResult = 0;


	//Get xinput state
	dwResult = XInputGetState(0, &xState);


	if (dwResult == ERROR_SUCCESS)
	{
		ReadButtonStates(xState.Gamepad);
		ReadAnalogueStates(xState.Gamepad);
		ReadTriggerStates(xState.Gamepad);


		StoreCurrentStates();
	}
}



/*---------------------------------------------------------------------------------------------------------------------------
*
* Reads button state information from the gamepad data container.
*
* @author Bryce Booth
* @param _xrGamePad	 Container holding information about the current state of the controller.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::ReadButtonStates(XINPUT_GAMEPAD& _xrGamePad)
{
	WORD wButtons = _xrGamePad.wButtons;


	//Read Buttons
	m_bButtonStates[XBUTTON_DPADDOWN]  = !!(wButtons & XINPUT_GAMEPAD_DPAD_DOWN);
	m_bButtonStates[XBUTTON_DPADUP]	   = !!(wButtons & XINPUT_GAMEPAD_DPAD_UP);
	m_bButtonStates[XBUTTON_DPADRIGHT] = !!(wButtons & XINPUT_GAMEPAD_DPAD_RIGHT);
	m_bButtonStates[XBUTTON_DPADLEFT]  = !!(wButtons & XINPUT_GAMEPAD_DPAD_LEFT);


	m_bButtonStates[XBUTTON_THUMBLEFT]   = !!(wButtons & XINPUT_GAMEPAD_LEFT_THUMB);
	m_bButtonStates[XBUTTON_THUMBRIGHT]  = !!(wButtons & XINPUT_GAMEPAD_RIGHT_THUMB);


	m_bButtonStates[XBUTTON_BUMPERLEFT]  = !!(wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER);
	m_bButtonStates[XBUTTON_BUMPERRIGHT] = !!(wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER);


	m_bButtonStates[XBUTTON_START] = !!(wButtons & XINPUT_GAMEPAD_START);
	m_bButtonStates[XBUTTON_BACK]  = !!(wButtons & XINPUT_GAMEPAD_BACK);


	m_bButtonStates[XBUTTON_A] = !!(wButtons & XINPUT_GAMEPAD_A);
	m_bButtonStates[XBUTTON_B] = !!(wButtons & XINPUT_GAMEPAD_B);
	m_bButtonStates[XBUTTON_X] = !!(wButtons & XINPUT_GAMEPAD_X);
	m_bButtonStates[XBUTTON_Y] = !!(wButtons & XINPUT_GAMEPAD_Y);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Reads analogue state information from the gamepad data container.
*
* @author Bryce Booth
* @param _xrGamePad	 Container holding information about the current state of the controller.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::ReadAnalogueStates(XINPUT_GAMEPAD& _xrGamePad)
{
	//Get analogue data
	float fThumbLeftX = static_cast<float>(_xrGamePad.sThumbLX);
	float fThumbLeftY = static_cast<float>(_xrGamePad.sThumbLY);
	float fThumbRightX = static_cast<float>(_xrGamePad.sThumbRX);
	float fThumbRightY = static_cast<float>(_xrGamePad.sThumbRY);


	fThumbLeftX = (fThumbLeftX) ? fThumbLeftX / 32767.0f : 0.0f;
	fThumbLeftY = (fThumbLeftY) ? fThumbLeftY / 32767.0f : 0.0f;
	fThumbRightX = (fThumbRightX) ? fThumbRightX / 32767.0f : 0.0f;
	fThumbRightY = (fThumbRightY) ? fThumbRightY / 32767.0f : 0.0f;


	pow(fThumbLeftX, 2.0f);
	pow(fThumbLeftY, 2.0f);
	pow(fThumbRightX, 2.0f);
	pow(fThumbRightY, 2.0f);


	//Square analogue scalar
	m_fAnalogueStates[XANALOG_LEFTX] = fThumbLeftX;
	m_fAnalogueStates[XANALOG_LEFTY] = fThumbLeftY;
	m_fAnalogueStates[XANALOG_RIGHTX] = fThumbRightX;
	m_fAnalogueStates[XANALOG_RIGHTY] = fThumbRightY;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Reads trigger state information from the gamepad data container.
*
* @author Bryce Booth
* @param _xrGamePad	 Container holding information about the current state of the controller.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::ReadTriggerStates(XINPUT_GAMEPAD& _xrGamePad)
{
	//Triggers
	float fTriggerLeft  = static_cast<float>(_xrGamePad.bLeftTrigger);
	float fTriggerRight = static_cast<float>(_xrGamePad.bRightTrigger);


	fTriggerLeft  = (fTriggerLeft)  ? fTriggerLeft  / 255.0f : 0.0f;
	fTriggerRight = (fTriggerRight) ? fTriggerRight / 255.0f : 0.0f;


	m_fTriggerStates[XTRIGGER_LEFT]  = fTriggerLeft;
	m_fTriggerStates[XTRIGGER_RIGHT] = fTriggerRight;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Stores the current states of buttons, triggers and analog for state chaning.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::StoreCurrentStates()
{
	memcpy(&m_fPreviousAnalogueStates, &m_fAnalogueStates, sizeof(float) * 4);
	memcpy(&m_fPreviousTriggerStates, &m_fTriggerStates, sizeof(float) * 2);
	memcpy(&m_bPreviousButtonStates, &m_bButtonStates, sizeof(bool) * 14);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Finds all button states that has change and sends change to targets.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::DispatchButtonStates()
{
	//Process button states
	for (int i = 0; i < XBUTTON_MAX; ++ i)
	{
		if (m_bButtonStates[i] != m_bPreviousButtonStates[i])
		{
			SendInputToTargets(static_cast<EXInputButton>(i));
		}
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Finds all analog states that has change and sends change to targets.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::DispatchAnalogStates()
{
	//Process Analogue states
	for (int i = 0; i < XANALOG_MAX; ++ i)
	{
		if (m_fAnalogueStates[i] != m_fPreviousAnalogueStates[i])
		{
			SendInputToTargets(static_cast<EXInputAnalog>(i));
		}
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Finds all trigger states that has change and sends change to targets.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::DispatchTriggerStates()
{
	//Process trigger states
	for (int i = 0; i < XTRIGGER_MAX; ++ i)
	{
		if (m_fTriggerStates[i] != m_fPreviousTriggerStates[i])
		{
			SendInputToTargets(static_cast<EXInputTrigger>(i));
		}
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sends information about the change in state for button to targets.
*
* @author Bryce Booth
* @param 
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::SendInputToTargets(EXInputButton _eXButton)
{
	int iNumTargets = static_cast<int>(m_vecXButtonTargets[_eXButton].size());


	for (int i = 0; i < iNumTargets; ++i)
	{
		m_vecXButtonTargets[_eXButton][i]->HandleXButtonInput(_eXButton, m_bButtonStates[_eXButton]);
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sends information about the change in state for trigger to targets.
*
* @author Bryce Booth
* @param 
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::SendInputToTargets(EXInputTrigger _eXTrigger)
{
	int iNumTargets = static_cast<int>(m_vecXTriggerTargets[_eXTrigger].size());


	for (int i = 0; i < iNumTargets; ++i)
	{
		m_vecXTriggerTargets[_eXTrigger][i]->HandleXTriggerInput(_eXTrigger, m_fTriggerStates[_eXTrigger]);
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sends information about the change in state for analogue to targets.
*
* @author Bryce Booth
* @param 
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::SendInputToTargets(EXInputAnalog _eXAnalogue)
{
	int iNumTargets = static_cast<int>(m_vecXAnalogueTargets[_eXAnalogue].size());


	for (int i = 0; i < iNumTargets; ++i)
	{
		m_vecXAnalogueTargets[_eXAnalogue][i]->HandleXAnalogInput(_eXAnalogue, m_fAnalogueStates[_eXAnalogue]);
	}
}








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
CXInputController::Deinitialise()
{
	//Empty
}