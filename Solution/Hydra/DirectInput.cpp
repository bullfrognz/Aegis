//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   DirectInput.cpp
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Macros.h"
#include "DMouseTarget.h"
#include "DKeyboardTarget.h"


// This Include
#include "DirectInput.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* DirectInput class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CDirectInput::CDirectInput()
: m_d3dpDirectInput8(0)
, m_d3dpKeyboard(0)
, m_d3dpMouse(0)
, m_uiWindowWidth(0)
, m_uiWindowHeight(0)
, m_bDisabled(true)
{
	ZeroMemory(&m_bKeyStates, sizeof(bool) * DKEYBOARD_MAX);
	ZeroMemory(&m_bPreviousKeyStates, sizeof(bool) * DKEYBOARD_MAX);


	ZeroMemory(&m_tMouseCaps, sizeof(DIDEVCAPS));


	ZeroMemory(&m_lMouseState, sizeof(long) * sizeof(DMOUSE_MAX));
	ZeroMemory(&m_lPreviousMouseState, sizeof(long) * sizeof(DMOUSE_MAX));
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* DirectInput class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CDirectInput::~CDirectInput()
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
CDirectInput::Initialise()
{
	InitialiseDInputInteface();
	InitialiseMouse();
	InitialiseKeyboard();


	SaveCurrentState();


	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Processes the direct input instance.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDirectInput::Process()
{
	if (m_bDisabled == false)
	{
		UpdateMouse();
		UpdateKeyboard();


		DispatchMouseState();
		DispatchKeyboardState();


		StoreCurrentStates();
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Adds target to recieve messages for chosen mouse input.
*
* @author Bryce Booth
* @param _eDMouse	Mouse message that the target wants to know about.
* @param _pTarget	Target instance.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDirectInput::AddTarget(EDInputMouse _eDMouse, IDMouseTarget* _pTarget)
{
	m_vecDMouseTargets[_eDMouse].push_back(_pTarget);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Adds target to recieve messages for chosen keyboard input.
*
* @author Bryce Booth
* @param _eDKeyboard	Keyboard message that the target wants to know about.
* @param _pTarget		Target instance.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDirectInput::AddTarget(EDInputKeyboard _eDKeyboard, IDKeyboardTarget* _pTarget)
{
	m_vecDKeyboardTargets[_eDKeyboard].push_back(_pTarget);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Removes target for that mouse input.
*
* @author Bryce Booth
* @param _eDMouse	Mouse message to remove mouse from.
* @param _pTarget	Target instance.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDirectInput::RemoveTarget(EDInputMouse _eDMouse, IDMouseTarget* _pTarget)
{
	//Get number of targets
	int iNumTargets = static_cast<int>(m_vecDMouseTargets[_eDMouse].size());


	//Loop through number of targets
	for (int i = 0; i < iNumTargets; ++i)
	{
		if (m_vecDMouseTargets[_eDMouse][i] == _pTarget)
		{
			//Erase target from group
			m_vecDMouseTargets[_eDMouse].erase(m_vecDMouseTargets[_eDMouse].begin() + i);

			
			break;
		}
	}
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Removes target for that mouse input.
*
* @author Bryce Booth
* @param _eDKeyboard	keyboard message to remove mouse from.
* @param _pTarget		Target instance.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDirectInput::RemoveTarget(EDInputKeyboard _eDKeyboard, IDKeyboardTarget* _pTarget)
{
	//Get number of targets
	int iNumTargets = static_cast<int>(m_vecDKeyboardTargets[_eDKeyboard].size());


	//Loop through number of targets
	for (int i = 0; i < iNumTargets; ++i)
	{
		if (m_vecDKeyboardTargets[_eDKeyboard][i] == _pTarget)
		{
			//Erase target from group
			m_vecDKeyboardTargets[_eDKeyboard].erase(m_vecDKeyboardTargets[_eDKeyboard].begin() + i);

			
			break;
		}
	}
}








/********************************
            Protected
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Gets the mouse current state from direct input and calcualtes the new mouse position.
* 
* @author Bryce Booth
* @param bActive	States if the mouse is active.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CDirectInput::UpdateMouse()
{
	//Default variables
	DIMOUSESTATE tMouseState;
	HRESULT hResult = S_OK;
	bool bActive = false;


	hResult = m_d3dpMouse->GetDeviceState(sizeof(DIMOUSESTATE), reinterpret_cast<void*>(&tMouseState));	// Automatically obtains the delta position.


	if (FAILED(hResult)) 
	{
		if (hResult == DIERR_INPUTLOST) 
		{
			// re-acquire the mouse device if device lost 
			m_d3dpMouse->Acquire(); 
		}
		else 
		{
			bActive = false; 
		}
	}


	//Calculate new mouse positions
	m_v2MousePosition.x += tMouseState.lX; 
	m_v2MousePosition.y += tMouseState.lY; 


	//Check if mmouse is within width bounds
	if (m_v2MousePosition.x < 0) 
	{
		m_v2MousePosition.x = 0.0f; 
	}
	else if (m_v2MousePosition.x >= m_uiWindowWidth) 
	{
		m_v2MousePosition.x = static_cast<float>(m_uiWindowWidth - 1); 
	}


	//Check if mmouse is within height bounds
	if (m_v2MousePosition.y < 0) 
	{
		m_v2MousePosition.y = 0.0f; 
	}
	else if (m_v2MousePosition.y >= m_uiWindowHeight) 
	{
		m_v2MousePosition.y = static_cast<float>(m_uiWindowHeight - 1); 
	}


	//Set button states
	m_lMouseState[DMOUSE_LEFTCLICK] = tMouseState.rgbButtons[DMOUSE_LEFTCLICK];
	m_lMouseState[DMOUSE_RIGHTCLICK] = tMouseState.rgbButtons[DMOUSE_RIGHTCLICK];
	m_lMouseState[DMOUSE_MIDDLECLICK] = tMouseState.rgbButtons[DMOUSE_MIDDLECLICK];
	m_lMouseState[DMOUSE_WHEEL] = tMouseState.lZ;


	return(bActive); 
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Gets keyboard current state.
* 
* @author Bryce Booth
* @param bActive	States if the keyboard is active.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CDirectInput::UpdateKeyboard()
{
	//Default variables
	HRESULT hResult = S_OK;
	bool bActive = false;


	hResult = m_d3dpKeyboard->GetDeviceState(sizeof(bool) * DKEYBOARD_MAX, reinterpret_cast<void*>(&m_bKeyStates)); 


	if (FAILED(hResult)) 
	{
		if (hResult == DIERR_INPUTLOST) 
		{
			//Re-acquire the keyboard
			m_d3dpKeyboard->Acquire(); 
		}
		else 
		{
			bActive = false; 
		}
	}


	return (bActive);
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Saves the current state of the mouse and keyboard.
* 
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDirectInput::SaveCurrentState()
{
	UpdateMouse();
	UpdateKeyboard();


	StoreCurrentStates();
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Stores the current keyboard and mouse states in previous containers.
* 
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDirectInput::StoreCurrentStates()
{
	memcpy(&m_lPreviousMouseState, &m_lMouseState, sizeof(long) * DMOUSE_MAX);
	memcpy(&m_bPreviousKeyStates, &m_bKeyStates, sizeof(bool) * DKEYBOARD_MAX);
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Sends all changed mouse states to targets.
* 
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDirectInput::DispatchMouseState()
{
	for (unsigned int i = 0; i < DMOUSE_MAX; ++i)
	{
		if (m_lMouseState[i] != m_lPreviousMouseState[i])
		{
			SendInputToTargets(static_cast<EDInputMouse>(i));
		}
	}
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Sends all changed key states to targets.
* 
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDirectInput::DispatchKeyboardState()
{
	for (unsigned int i = 0; i < DKEYBOARD_MAX; ++i)
	{
		if (m_bKeyStates[i] != m_bPreviousKeyStates[i])
		{
			SendInputToTargets(static_cast<EDInputKeyboard>(i));
		}
	}
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Sends current mouse state to all targets.
* 
* @author Bryce Booth
* @param _eDMouse	Mouse state.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDirectInput::SendInputToTargets(EDInputMouse _eDMouse)
{
	int iNumTargets = static_cast<int>(m_vecDMouseTargets[_eDMouse].size());


	for (int i = 0; i < iNumTargets; ++i)
	{
		m_vecDMouseTargets[_eDMouse][i]->HandleDMouseInput(_eDMouse, !!m_lMouseState[_eDMouse], m_lMouseState[_eDMouse]);
	}
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Sends current keyboard state to all targets.
* 
* @author Bryce Booth
* @param _eDMouse	Mouse state.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDirectInput::SendInputToTargets(EDInputKeyboard _eDKeyboard)
{
	int iNumTargets = static_cast<int>(m_vecDKeyboardTargets[_eDKeyboard].size());


	for (int i = 0; i < iNumTargets; ++i)
	{
		m_vecDKeyboardTargets[_eDKeyboard][i]->HandleDKeyboardInput(_eDKeyboard, m_bKeyStates[_eDKeyboard]);
	}
}





/********************************
            Private
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates a direct input 8 interface.
*
* @author Jamie Smith
* @param bInitialised	States if the interface was successfully created.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CDirectInput::InitialiseDInputInteface()
{
	//Default variables
	HRESULT hResult = S_OK;
	bool bInitialised = true; 


	//Retrieve window dimentions
	unsigned int m_uiWindowWidth  = CApplication::GetInstance().GetGameWindow().GetClientWidth();
	unsigned int m_uiWindowHeight = CApplication::GetInstance().GetGameWindow().GetClientHeight();
	

	//Default cursor to center of window
	m_v2MousePosition.x = m_uiWindowWidth  / 2.0f; 
	m_v2MousePosition.y = m_uiWindowHeight / 2.0f; 


	//Create interface
	hResult = DirectInput8Create(CApplication::GetInstance().GetInstanceHandle(), 
							     DIRECTINPUT_VERSION, 
								 IID_IDirectInput8, 
								 reinterpret_cast<void**>(&m_d3dpDirectInput8), 
								 NULL);  


	//Check if interface was created
	if (SUCCEEDED(hResult)) 
	{
		//Initialise keyboard
		InitialiseKeyboard(); 


		//Initialise mouse
		InitialiseMouse();
	}
	else 
	{
		bInitialised = false; 
	}


	//Return if initialised
	return(bInitialised); 
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates direct input mouse interface.
*
* @author Jamie Smith
* @param bInitialised	States if the interface was successfully created.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CDirectInput::InitialiseMouse()
{
	//Default variables
	HRESULT hResult = S_OK;
	bool bInitialised = true; 


	//Create mouse interface
	m_d3dpDirectInput8->CreateDevice(GUID_SysMouse, &m_d3dpMouse, NULL); 


	// set the data format based on the internal, prebuilt information 
	m_d3dpMouse->SetDataFormat(&c_dfDIMouse); 


	// set the coop' level 
	m_d3dpMouse->SetCooperativeLevel(CApplication::GetInstance().GetGameWindow().GetWindowHandle(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE); 


	// set the dw size of the struct 
	m_tMouseCaps.dwSize = sizeof(DIDEVCAPS); 


	// get the mouse caps 
	m_d3dpMouse->GetCapabilities(&m_tMouseCaps); 


	//Set Initial Mouse Coords
	POINT mouse; 
	GetCursorPos(&mouse);
	m_v2MousePosition.x = static_cast<float>(mouse.x - 100);
	m_v2MousePosition.y = static_cast<float>(mouse.y - 100);


	// get the device from the system for state checking 
	hResult = m_d3dpMouse->Acquire(); 


	if (FAILED(hResult)) 
	{	
		bInitialised = false; 
	}


	return(bInitialised); 
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates direct input keyboard interface.
*
* @author Jamie Smith
* @param bInitialised	States if the interface was successfully created.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CDirectInput::InitialiseKeyboard()
{
	bool bIsInitialised = true; 


	// create the keyboard device 
	m_d3dpDirectInput8->CreateDevice(GUID_SysKeyboard, &m_d3dpKeyboard, NULL); 


	// set the data format based on the internal, prebuilt information 
	m_d3dpKeyboard->SetDataFormat(&c_dfDIKeyboard); 


	// set the coop' level 
	m_d3dpKeyboard->SetCooperativeLevel(CApplication::GetInstance().GetGameWindow().GetWindowHandle(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE); 


	// get the device from the system for state checking 
	HRESULT hr = m_d3dpKeyboard->Acquire(); 
	

	if (FAILED(hr)) 
	{
		bIsInitialised = false; 
	}


	return(bIsInitialised);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* This function deinitialises the class instance by freeing memory and calling other necessary functions.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CDirectInput::Deinitialise()
{
	//Empty
}