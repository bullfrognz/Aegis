//
//  Diploma of Interactive Gaming
//  Scene Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   playerinput.inl
//  Description :   PlayerInput inline implementation (source) file 
//  Author      :   Jamie.Smith
//  Mail        :   Jamie.Smith@mediadesign.school.nz 
//

// Library Includes

// Local Includes

// This Include

// Static Variables

// Static Function Prototypes

// Implementation 

/** 
*
* Get the keyboard speed modifier value 
*
* @author Jamie.Smith
* @return keyboard speed modifier value 
*
*/
float 
CPlayerInput::GetKeyboardSpeedModifier() const 
{
	return(m_fKeyboardSpeedModifier); 
}

/** 
*
* Get the controller speed modifier value 
*
* @author Jamie.Smith 
* @return controller speed modifier value 
*
*/
float 
CPlayerInput::GetControllerSpeedModifier() const 
{
	return(m_fControllerSpeedModifier); 
}

/** 
*
* Get the DirectInput class 
*
* @author Jamie.Smith 
* @return DirectInput instance 
*
*/
CDirectInput&
CPlayerInput::GetDirectInput() 
{
	return m_DInputDevice; 
}