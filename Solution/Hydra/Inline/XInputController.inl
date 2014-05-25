//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   XInputController.inl
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the runble level for the left controller motor.
*
* @author Bryce Booth
* @param _eLevel	The intensity of the rumble.
* @param _fTime		Duration of the rumble.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::SetRumbleLeft(EXRumbleLevel _eLevel, float _fTime)
{
	m_eRumbleLevelLeft = _eLevel;
	m_fLRumbleTimer = _fTime;


	RefreshRumbleState();
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the runble level for the right controller motor.
*
* @author Bryce Booth
* @param _eLevel	The intensity of the rumble.
* @param _fTime		Duration of the rumble.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::SetRumbleRight(EXRumbleLevel _eLevel, float _fTime)
{
	m_eRumbleLevelRight = _eLevel;
	m_fRRumbleTimer = _fTime;


	RefreshRumbleState();
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns if the controller is plugged in or not.
*
* @author Bryce Booth
* @param m_bPluggedIn		States if the controller is plugged in or not.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CXInputController::IsPluggedIn()
{
	RefreshPluggedIn();


	return (m_bPluggedIn);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets direct input to be disabled or enabled.
*
* @author Bryce Booth
* @param _bDisabled		States if to disable.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CXInputController::SetDisabled(bool _bDisabled)
{
	m_bDisabled = _bDisabled;


	if (m_bDisabled == false)
	{
		SaveCurrentState();
	}
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns if the controller is disabled.
*
* @author Bryce Booth
* @param _bDisabled		States if is disabled.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CXInputController::IsDisabled() const
{
	return (m_bDisabled);
}