//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   InputManager.inl
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the instance of the xinput controller
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CXInputController&
CInputManager::GetXInputController()
{
	return (*m_pXInputController);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CDirectInput&
CInputManager::GetDirectInput()
{
	return (*m_pDirectInput);
}