//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   Window.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <windows.h>


// Local Includes
#include "StrUtilities.h"
#include "Macros.h"
#include "Application.h"
#include "Clock.h"
#include "Scene.h"
#include "D3DRenderer.h"
#include "resource.h"
#include "INIParser.h"
#include "WindowData.h"


// This Include
#include "Window.h"


// Static Variables
CWindow* CWindow::s_pActiveWindowsInstances[WINDOWS_MAX];
HWND*	 CWindow::s_pActiveWindowsHandles[WINDOWS_MAX];
UINT     CWindow::s_uiNumActiveWindows = 0;
bool     CWindow::m_bShowingCursor = true;
bool     CWindow::m_bCursorStateLocked = false;


// Function Prototypes
LRESULT CALLBACK WindowProcWrapper(HWND _hWindow, UINT _Message, WPARAM _wParam, LPARAM _lParam);


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Window class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWindow::CWindow()
: m_hWindowHandle(0)
, m_kcpWindowTitle(0)
, m_pRenderer(0)
, m_pClock(0)
, m_uiWindowWidth(0)
, m_uiWindowHeight(0)
, m_uiClientWidth(0)
, m_uiClientHeight(0)
, m_iMarginX(0)
, m_iMarginY(0)
, m_uiUpdateRendererHertz(0)
, m_dwStyles(0)
, m_pMainScene(0)
, m_eMainScene(SCENE_INVALID)
, m_pOverlayScene(0)
, m_eOverlayScene(OVERLAYSCENE_INVALID)
, m_eChangeToMainScene(SCENE_INVALID)
, m_pChangeToMainSceneData(0)
, m_eChangeToOverlayScene(OVERLAYSCENE_INVALID)
, m_pChangeToOverlaySceneData(0)
, m_bFullscreen(false)
, m_bUpdateRendererResolution(false)
, m_bFocused(true)
{
	//Empty
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Window class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWindow::~CWindow()
{
	Deinitialise();
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets member variables and runs initialise functions to setup the window.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CWindow::Initialise(HINSTANCE _hInstance, CWindowData& _rWindowData)
{
	//Check incoming parameters
	LOG_FATALERROR(_rWindowData.GetWindowTitle()  == 0, "Invalid window title.");
	LOG_FATALERROR(_rWindowData.GetWidth()  == 0, "Invalid window width.");
	LOG_FATALERROR(_rWindowData.GetHeight() == 0, "Invalid window height.");
	
	
	//Set member variables
	m_uiWindowWidth  = _rWindowData.GetWidth();
	m_uiWindowHeight = _rWindowData.GetHeight();
	m_bFullscreen = _rWindowData.GetFullscreen();
	StrUtilities::Copy(_rWindowData.GetWindowTitle(), m_kcpWindowTitle);
	m_iMarginX = _rWindowData.GetMarginX();
	m_iMarginY = _rWindowData.GetMarginY();
	m_dwStyles = _rWindowData.GetStyles();


	//Run initialise functions
	FW_VALIDATE(InitialiseWinClass(_hInstance), "Winclass initialise failed.");
	FW_VALIDATE(InitialiseWindowHandle(_hInstance), "Window handle initialise failed.");
	FW_VALIDATE(InitialiseRenderer(_rWindowData.GetDisplayAdapter(), _rWindowData.GetMultisampleType()), "Window renderer initialise failed.");
	FW_VALIDATE(InitialiseClock(), "Window clock initialise failed.");


	TurnOnCursorClip();


	return (true);
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Resizes the window to new dimentions and sets the renderer present parameters for next device reset.
*
* @author Bryce Booth
* @param _uiWindowWidth		New width of the window and renderer.
* @param _uiWindowHeight	New height of the window and renderer.
* @param _uiRefreshRate		New refresh rate of the renderer.
* @param _bFullscreen		If window and renderer is to be fullscreen.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindow::ResizeWindow(unsigned int _uiWindowWidth, unsigned int _uiWindowHeight, unsigned int _uiRefreshRate, bool _bFullscreen)
{
	//Set member variables
	m_uiWindowWidth  = _uiWindowWidth;
	m_uiWindowHeight = _uiWindowHeight;
	m_bFullscreen    = _bFullscreen;
	

	//Resize window
	::SetWindowPos(m_hWindowHandle, 0, m_iMarginX, m_iMarginY, m_uiWindowWidth, m_uiWindowHeight, SWP_NOZORDER | SWP_SHOWWINDOW);


	//Update renderer present parameters
	UpdatePresentParameters(_uiRefreshRate);


	//Save new state to ini
	UpdateResolutionINI(_uiRefreshRate);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Centers the mouse based on window parameters.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindow::CenterCursor()
{
	int iPositionX = m_iMarginX + (m_uiWindowWidth  / 2);
	int iPositionY = m_iMarginY + (m_uiWindowHeight / 2);


	//Center mouse
	SetCursorPos(iPositionX,
				 iPositionY);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Positions the cursor within the game window
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindow::SetCursorPosition(int _iPositionX, int _iPositionY)
{
	int iPositionX = m_iMarginX + _iPositionX;
	int iPositionY = m_iMarginY + _iPositionY;


	//Center mouse
	SetCursorPos(iPositionX,
				 iPositionY);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Hides the windows cursor.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindow::HideCursor()
{
	if (m_bCursorStateLocked == false && m_bShowingCursor)
	{
		::ShowCursor(FALSE);


		m_bShowingCursor = false;
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Displays the windows cursor.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindow::ShowCursor()
{
	if (m_bCursorStateLocked == false && m_bShowingCursor == false)
	{
		::ShowCursor(TRUE);


		m_bShowingCursor = true;
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Locks the mouse cursor so it can not be shown or hidden.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindow::SetCursorStateLocked(bool _bLocked)
{
	m_bCursorStateLocked = _bLocked;
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Saves the changed resolution to ini for next game run.
*
* @author Bryce Booth
* @param _uiRefreshRate		The refresh rate of the renderer.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindow::UpdateResolutionINI(unsigned int _uiRefreshRate)
{
	//Default variables
	char cBuffer[256];
	const char kcINIGroup[] = "Renderer";


	//Instance ini parser
	CINIParser INIEngine;


	//Load engine ini file
	INIEngine.LoadINIFile("Ini Files\\Engine.ini");

	
	//Save window width
	sprintf_s(cBuffer, 256, "%d", m_uiWindowWidth);
	INIEngine.AddValue(kcINIGroup, "Width", cBuffer);


	//Save window height
	sprintf_s(cBuffer, 256, "%d", m_uiWindowHeight);
	INIEngine.AddValue(kcINIGroup, "Height", cBuffer);


	//Save refresh rate
	sprintf_s(cBuffer, 256, "%d", _uiRefreshRate);
	INIEngine.AddValue(kcINIGroup, "Refresh", cBuffer);


	//Save fullscreen
	INIEngine.AddValue(kcINIGroup, "FullScreen", ((m_bFullscreen)? "true" : "false"));


	//Save INI file
	INIEngine.SaveINIFile("Ini Files\\Engine.ini");
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Wrapper for window messages for windows.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

LRESULT CALLBACK
CWindow::DefaultWindowProc(HWND _hWindowHandle, UINT _uiMessage, WPARAM _wParam, LPARAM _lParam)
{
	CWindow* pWindow = 0;


	for (UINT i = 0; i < s_uiNumActiveWindows; ++i)
	{
		if ((*s_pActiveWindowsHandles[i]) == _hWindowHandle)
		{
			pWindow = s_pActiveWindowsInstances[i];
			

			break;
		}
	}


	if (pWindow != 0)
	{
		pWindow->WindowProc(_hWindowHandle, _uiMessage, _wParam, _lParam);


		switch (_uiMessage)
		{
		case WM_CLOSE:
			CApplication::GetInstance().Quit();
			break;


		default:
			break;
		}
	}


	return (DefWindowProc(_hWindowHandle, _uiMessage, _wParam, _lParam));
}









/********************************
            Protected
*********************************/









/********************************
            Private
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates win class.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CWindow::InitialiseWinClass(HINSTANCE _hInstance)
{
	//Check win class has not been created
	if (!GetClassInfo(_hInstance, WINCLASSNAME, NULL))
	{
		WNDCLASSEX WinClass;
		WinClass.cbSize			= sizeof(WNDCLASSEX);
		WinClass.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS; //CS_DBLCLKS | CS_OWNDC | 
		WinClass.lpfnWndProc	= WindowProcWrapper;
		WinClass.cbClsExtra		= 0;
		WinClass.cbWndExtra		= 0;
		WinClass.hInstance		= _hInstance;
		WinClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
		WinClass.hCursor		= LoadCursor(_hInstance, MAKEINTRESOURCE(IDI_ICON1));
		WinClass.hbrBackground	= static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
		WinClass.lpszMenuName	= NULL;
		WinClass.lpszClassName	= WINCLASSNAME;
		WinClass.hIconSm		= LoadIcon(NULL, IDI_APPLICATION);
	 
		//Register win class
		ATOM atomRegistered = RegisterClassEx(&WinClass);


		LOG_FATALERROR(atomRegistered == false, "Could not create winclass.");
	}


	return (true);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates window handle.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CWindow::InitialiseWindowHandle(HINSTANCE _hInstance)
{
	//Convert window title type
	wchar_t* wcpWindowTitle = 0;
	StrUtilities::ConvertToWChar(m_kcpWindowTitle, wcpWindowTitle);


	//Create window
	m_hWindowHandle = CreateWindowEx(NULL,
									 WINCLASSNAME,
									 wcpWindowTitle,
									 m_dwStyles,
									 m_iMarginX, m_iMarginY,
									 m_uiWindowWidth,
									 m_uiWindowHeight,
									 NULL,
									 NULL,
									 _hInstance,
									 NULL);


	//Check window handle is valid
	LOG_FATALERROR(m_hWindowHandle == false, "Window failed to create.");


	//Add active window
	s_pActiveWindowsInstances[s_uiNumActiveWindows] = this;
	s_pActiveWindowsHandles[s_uiNumActiveWindows] = &m_hWindowHandle;


	//Increment number of active windows
	++ s_uiNumActiveWindows;


	FW_DELETE(wcpWindowTitle);


	return (true);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates renderer instance.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CWindow::InitialiseRenderer(unsigned char _ucDisplayAdapter, unsigned int _uiMultisampleType)
{
	//Recalculate client rect
	RecalculateClientRect();


	//Instance renderer class
	m_pRenderer = new CD3DRenderer();


	//Initialise renderer
	FW_VALIDATE(m_pRenderer->Initialise(m_hWindowHandle, _ucDisplayAdapter, _uiMultisampleType, m_uiClientWidth, m_uiClientHeight, m_bFullscreen),
				"Window renderer initialise failed.");
	

	return (true);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* Creates clock instance.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CWindow::InitialiseClock()
{
	//Instance clock class
	m_pClock = new CClock();
	m_pClock->Initialise();
	m_pClock->Process();


	return (true);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* Locks the cursor to the game bounds for mouse scrolling.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindow::TurnOnCursorClip()
{
	RECT rectClipBounds;
	rectClipBounds.top = m_iMarginY;
	rectClipBounds.bottom = m_iMarginY + m_uiWindowHeight;
	rectClipBounds.left = m_iMarginX;
	rectClipBounds.right = m_iMarginX + m_uiWindowWidth;


	::ClipCursor(&rectClipBounds);


	CenterCursor();
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Unlocks the cursor.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindow::TurnOffCursorClip()
{
	::ClipCursor(0);
}










/*---------------------------------------------------------------------------------------------------------------------------
*
* Changes the renderer present parameters to the new window settings.
*
* @author Bryce Booth
* @param _uiRefreshRate		The new refreshrate of the renderer for fullscreen.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindow::UpdatePresentParameters(unsigned int _uiRefreshRate)
{
	//Recalcuate new client rect
	RecalculateClientRect();


	//Set renderer back buffer dimentions
	m_pRenderer->SetBackbufferDimentions(m_uiClientWidth, m_uiClientHeight);


	//Set renderer fullscreen or window
	m_pRenderer->SetFullscreen(m_bFullscreen, _uiRefreshRate);


	TurnOnCursorClip();
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* Graps the client dimentions from window.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindow::RecalculateClientRect()
{
	//Check if window is full screen
	if (m_bFullscreen == false)
	{
		//Set default variables
		RECT rectWindowDimentions;


		//Get real window dimentions
		GetClientRect(m_hWindowHandle, &rectWindowDimentions);

		
		//Calculate new window dimentions
		m_uiClientWidth  = rectWindowDimentions.right;
		m_uiClientHeight = rectWindowDimentions.bottom;
	}
	else
	{
		m_uiClientWidth  = m_uiWindowWidth;
		m_uiClientHeight = m_uiWindowHeight;
	}
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function deinitialises the class instance by freeing memory and calling other necessary functions.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWindow::Deinitialise()
{
	//Decrement number of active windows
	-- s_uiNumActiveWindows;


	//Check if there are other windows active
	if (s_uiNumActiveWindows == 0)
	{
		//Delete the global scene
		FW_DELETE(m_pMainScene);
		FW_DELETE(m_pOverlayScene);
	}


	//Delete member variables
	FW_DELETE(m_pRenderer);
	FW_DELETE(m_pClock);


	FW_DELETE(m_kcpWindowTitle);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

LRESULT CALLBACK
WindowProcWrapper(HWND _hDialog, UINT _Message, WPARAM _wParam, LPARAM _lParam)
{
	return (CWindow::DefaultWindowProc(_hDialog, _Message, _wParam, _lParam));
}