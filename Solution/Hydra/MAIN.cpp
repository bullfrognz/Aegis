//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   MAIN.cpp
//
//  Author    :	  Team Blue
//




// Library Includes
#include <windows.h>
//#include <crtdbg.h>
//#include <vld.h>


// Local Includes
#include "Macros.h"
#include "Application.h"
#include "Window.h"
#include "Scene.h"
#include "resource.h"

// Implementation

int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _1pCmdLine, INT _iCmdShow)
{
	//Default varaibles
	MSG msgWindowsMessage;
	ZeroMemory(&msgWindowsMessage, sizeof(MSG));
	bool bApplicationSetup = false;
	
	
	//Initialise application
	bApplicationSetup = CApplication::GetInstance().Initialise(_hInstance);


	//Check if application was initialised
	if (bApplicationSetup == true)
	{
		//Get game window
		CWindow& rGameWindow = CApplication::GetInstance().GetGameWindow();


		//Set window startup scene
		rGameWindow.SetMainScene(SCENE_SPLASH_MEDIA);


		do
		{
			if (PeekMessage(&msgWindowsMessage, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msgWindowsMessage); //Translate any accesserator keys
				DispatchMessage(&msgWindowsMessage);  //Send the message to the window proc
			}
			else
			{
				rGameWindow.ExecuteOneFrame();
			}
		}
		while (msgWindowsMessage.message != WM_QUIT);
	}
	else
	{
		DISPLAYERROR("Application failed to initialise. Application will be closed.", L"Fatal Error", MB_OK | MB_ICONERROR)\
	}


	//Destroy application
	CApplication::GetInstance().DestroyInstance();


	//Return window
	return (static_cast<int>(msgWindowsMessage.wParam));
}