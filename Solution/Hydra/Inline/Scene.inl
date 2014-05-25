//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Scene.inl
//  Description :  
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the log window for this scene.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CLogWindow&
CScene::GetLogWindow()
{
	return (*m_pLogWindow);
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the input manager for this scene.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CInputManager&
CScene::GetInputManager()
{
	return (*m_pInputManager);
}

