//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Application.cpp
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Macros.h"
#include "GameWindow.h"
#include "INIParser.h"
#include "WindowData.h"



// This Include
#include "Application.h"


// Static Variables
CApplication* CApplication::s_pApplication = 0;


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Application class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CApplication::CApplication()
: m_hInstance(0)
, m_pDirect3D9(0)
, m_pGameWindow(0)
{
	//Empty
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Application class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CApplication::~CApplication()
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
CApplication::Initialise(HINSTANCE _hInstance)
{
	// Save member variables
	m_hInstance = _hInstance;


	// Run class initialisers
	FW_VALIDATE(InitialiseGameWindow(), "Applicationg game window initialise failed.");
	CSoundSystem::GetInstance()->StartUp();



	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the instance of application or creates it if it does not exist.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CApplication&
CApplication::GetInstance()
{
	if (s_pApplication == 0)
	{
		s_pApplication = new CApplication();
	}

	return (*s_pApplication);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Destroys the application instance.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CApplication::DestroyInstance()
{
	CSoundSystem::DestroyInstance();
	FW_DELETE(s_pApplication);
}








/********************************
            Protected
*********************************/









/********************************
            Private
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CApplication::InitialiseGameWindow()
{
	CINIParser FileReader;

	FileReader.LoadINIFile("Ini Files\\Engine.ini");

	CWindowData WindowParameters;


	unsigned int m_uiWindowWidth = 0;
	unsigned int m_uiWindowHeight = 0;
	unsigned int m_uiMulisampleType = 0;
	unsigned int m_uiDisplayAdapter = 0;
	int m_iMarginX = 0;
	int m_iMarginY = 0;
	bool bFullscreen = false;


	FileReader.GetValue("Renderer", "Width", m_uiWindowWidth);
	FileReader.GetValue("Renderer", "Height", m_uiWindowHeight);
	FileReader.GetValue("Renderer", "DisplayAdapter", m_uiDisplayAdapter);
	FileReader.GetValue("Renderer", "MultisampleType", m_uiMulisampleType);
	FileReader.GetValue("Renderer", "FullScreen", bFullscreen);


	FileReader.GetValue("Window", "MarginX", m_iMarginX);
	FileReader.GetValue("Window", "MarginY", m_iMarginY);


	WindowParameters.SetWindowTitle("Aegis");
	WindowParameters.SetStyles(WS_VISIBLE | WS_OVERLAPPED | WS_POPUP); //  WS_BORDER | WS_CAPTION | WS_SYSMENU  | 
	WindowParameters.SetMarginX(m_iMarginX);
	WindowParameters.SetMarginY(m_iMarginY);
	WindowParameters.SetDisplayAdapter(m_uiDisplayAdapter);
	WindowParameters.SetMultisamplingType(m_uiMulisampleType);
	WindowParameters.SetWidth(m_uiWindowWidth);
	WindowParameters.SetHeight(m_uiWindowHeight);
	WindowParameters.SetFullscreen(bFullscreen);


	m_pGameWindow = new CGameWindow();
	FW_VALIDATE(m_pGameWindow->Initialise(m_hInstance, WindowParameters), "Game window initialise failed.");


	return (true);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function deinitialises the class instance by freeing memory and calling other necessary functions.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CApplication::Deinitialise()
{
	FW_RELEASE(m_pDirect3D9);
	FW_DELETE(m_pGameWindow);
}


