//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Window.inl
//  Description :  
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindow::SetMainScene(EScene _eScene, void* _pSceneData)
{
	//Set member variables
	m_eChangeToMainScene = _eScene;
	m_pChangeToMainSceneData = _pSceneData;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindow::SetOverlayScene(EOverlayScene _eOverlayScene, void* _pSceneData)
{
	m_eChangeToOverlayScene     = _eOverlayScene;
	m_pChangeToOverlaySceneData = _pSceneData;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

HWND&
CWindow::GetWindowHandle()
{
	return (m_hWindowHandle);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

unsigned int
CWindow::GetClientWidth() const
{
	return (m_uiClientWidth);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

unsigned int
CWindow::GetClientHeight() const
{
	return (m_uiClientHeight);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

unsigned int
CWindow::GetWindowWidth() const
{
	return (m_uiWindowWidth);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

unsigned int
CWindow::GetWindowHeight() const
{
	return (m_uiWindowHeight);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CScene&
CWindow::GetCurrentMainScene()
{
	return (*m_pMainScene);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

EScene
CWindow::GetCurrentMainSceneType() const
{
	return (m_eMainScene);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CScene&
CWindow::GetCurrentOverlayScene()
{
	return(*m_pOverlayScene);
}

EOverlayScene 
CWindow::GetOverlaySceneType() const
{
	return (m_eOverlayScene);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CD3DRenderer*
CWindow::GetRenderer()
{
	return (m_pRenderer);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

COORD&
CWindow::GetMosueCoords()
{
	return (m_crdMousePosition);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CWindow::IsFullscreen() const
{
	return (m_bFullscreen);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CWindow::IsFocused() const
{
	return (m_bFocused);
}