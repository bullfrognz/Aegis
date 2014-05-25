//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   ------.inl
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the instance handle.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

HINSTANCE
CApplication::GetInstanceHandle()
{
	return (m_hInstance);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the game window instance.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWindow&
CApplication::GetGameWindow()
{
	return (*m_pGameWindow);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the base dimention radio for resolution scaling.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

float
CApplication::GetBaseDimentionRatio()
{
	const float kfWindowWidth  = static_cast<float>(m_pGameWindow->GetClientWidth());
	const float kfWindowHeight = static_cast<float>(m_pGameWindow->GetClientHeight());


	return (min(kfWindowWidth  / static_cast<float>(m_eBaseWidth), kfWindowHeight / static_cast<float>(m_eBaseHeight)));
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the base resolution of the game.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

float
CApplication::GetBaseWidth() const
{
	return (static_cast<float>(m_eBaseWidth));
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Gets base height of the game.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

float
CApplication::GetBaseHeight() const
{
	return (static_cast<float>(m_eBaseHeight));
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Posts quit message to quit the application.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CApplication::Quit()
{
	PostQuitMessage(0);
}