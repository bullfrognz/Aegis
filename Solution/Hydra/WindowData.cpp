//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   WindowData.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "StrUtilities.h"


// This Include
#include "WindowData.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* WindowData class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWindowData::CWindowData()
: m_kcpWindowTitle(0)
, m_dwStyles(0)
, m_iMarginX(0)
, m_iMarginY(0)
, m_uiWidth(0)
, m_uiHeight(0)
, m_uiMultisampleType(0)
, m_ucDisplayAdapter(0)
, m_bFullScreen(false)
{
	//Empty
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* WindowData class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWindowData::~CWindowData()
{
	delete m_kcpWindowTitle;
	m_kcpWindowTitle = 0;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets window title member variable.
*
* @author Bryce Booth
* @param _kcpWindowTitle	The title of the window to be set.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindowData::SetWindowTitle(const char* _kcpWindowTitle)
{
	StrUtilities::Copy(_kcpWindowTitle, m_kcpWindowTitle);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets styles member variable.
*
* @author Bryce Booth
* @param _dwStyles		The styles of the window to be set
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindowData::SetStyles(DWORD _dwStyles)
{
	m_dwStyles = _dwStyles;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets margin x member variable.
*
* @author Bryce Booth
* @param _uiMarginX		Window x offset.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindowData::SetMarginX(int _iMarginX)
{
	m_iMarginX = _iMarginX;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets margin y member variable.
*
* @author Bryce Booth
* @param _uiMarginX		Window y offset.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindowData::SetMarginY(int _iMarginY)
{
	m_iMarginY = _iMarginY;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets window with member variable.
*
* @author Bryce Booth
* @param _uiWidth	Width of the window
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindowData::SetWidth(unsigned int _uiWidth)
{
	m_uiWidth = _uiWidth;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets window height member variable.
*
* @author Bryce Booth
* @param _uiHeight	Height of the window
*
*---------------------------------------------------------------------------------------------------------------------------*/

void 
CWindowData::SetHeight(unsigned int _uiHeight)
{
	m_uiHeight = _uiHeight;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets window renderer' display adapter member variable.
*
* @author Bryce Booth
* @param _ucDisplayAdapter	The display adapter that the window will run on.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindowData::SetDisplayAdapter(unsigned char _ucDisplayAdapter)
{
	m_ucDisplayAdapter = _ucDisplayAdapter;
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets window renderer' multisample type member variable.
*
* @author Bryce Booth
* @param m_uiMultisampleType	The quality of multisampling for renderer.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindowData::SetMultisamplingType(unsigned int _uiMultisampleType)
{
	m_uiMultisampleType = _uiMultisampleType;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets window renderer' fullscreen member variable.
*
* @author Bryce Booth
* @param _bFullScreen	If the window will be fullscreen.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindowData::SetFullscreen(bool _bFullScreen)
{
	m_bFullScreen = _bFullScreen;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns window title member variable.
*
* @author Bryce Booth
* @return m_kcpWindowTitle	Window title member variable.
*
*---------------------------------------------------------------------------------------------------------------------------*/

const char*
CWindowData::GetWindowTitle()
{
	return (m_kcpWindowTitle);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns window styles member variable.
*
* @author Bryce Booth
* @return m_dwStyles	Styles member variable
*
*---------------------------------------------------------------------------------------------------------------------------*/

DWORD
CWindowData::GetStyles()
{
	return (m_dwStyles);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns window margin x member variable.
*
* @author Bryce Booth
* @return m_iMarginX	Window margin x.
*
*---------------------------------------------------------------------------------------------------------------------------*/

int
CWindowData::GetMarginX()
{
	return (m_iMarginX);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns window margin y member variable.
*
* @author Bryce Booth
* @return m_iMarginX	Window margin y.
*
*---------------------------------------------------------------------------------------------------------------------------*/

int
CWindowData::GetMarginY()
{
	return (m_iMarginY);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns window width member variable.
*
* @author Bryce Booth
* @return m_uiWidth		Window width.
*
*---------------------------------------------------------------------------------------------------------------------------*/

unsigned int
CWindowData::GetWidth()
{
	return (m_uiWidth);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns window height member variable.
*
* @author Bryce Booth
* @return m_uiHeight	Window height.
*
*---------------------------------------------------------------------------------------------------------------------------*/

unsigned int
CWindowData::GetHeight()
{
	return (m_uiHeight);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns window renderer' multisample type member variable.
*
* @author Bryce Booth
* @return m_uiMultisampleType	Window renderer' multisampling type.
*
*---------------------------------------------------------------------------------------------------------------------------*/

unsigned int
CWindowData::GetMultisampleType()
{
	return (m_uiMultisampleType);
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns window renderer display adapter member variable.
*
* @author Bryce Booth
* @return m_ucDisplayAdapter	Display adapter to be used.
*
*---------------------------------------------------------------------------------------------------------------------------*/

unsigned char
CWindowData::GetDisplayAdapter()
{
	return (m_ucDisplayAdapter);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns window fullscreen member variable.
*
* @author Bryce Booth
* @return m_bFullScreen		Window fullscreen member variable.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CWindowData::GetFullscreen()
{
	return (m_bFullScreen);
}









/********************************
            Protected
*********************************/









/********************************
            Private
*********************************/