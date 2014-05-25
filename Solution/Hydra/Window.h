//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Window.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_WINDOW_H__
#define __IGFEB11_IG500_WINDOW_H__


// Library Includes
#include <windows.h>
#include <map>
#include <d3dx9.h>


// Local Includes


// Types


// Constants
#define WINCLASSNAME L"Project Hydra"
#define WINDOWS_MAX 1


// Prototypes
enum EScene;
enum EOverlayScene;

class CWindowData;
class CD3DRenderer;
class CClock;
class CScene;


class CWindow
{

	// Member Functions
public:


	         CWindow();
	virtual ~CWindow();


	bool Initialise(HINSTANCE _hInstance, CWindowData& _rWindowData);


	virtual void ResizeWindow(unsigned int _uiWindowWidth, unsigned int _uiWindowHeight, unsigned int _uiRefreshRate, bool _bFullscreen);


	virtual void ExecuteOneFrame() = 0;


	void CenterCursor();
	void SetCursorPosition(int _iPositionX, int _iPositionY);


	void HideCursor();
	void ShowCursor();
	void SetCursorStateLocked(bool _bLocked);


	virtual LRESULT CALLBACK WindowProc(HWND _hWindow, unsigned int _uiMessage, 
										WPARAM _wParam, LPARAM _lParam) = 0;

	
	static LRESULT CALLBACK DefaultWindowProc(HWND _hWindowHandle, unsigned int _uiMessage,
											  WPARAM _wParam, LPARAM _lParam);



	// Inline Functions
	inline HWND& GetWindowHandle();


	inline unsigned int GetWindowWidth() const;
	inline unsigned int GetWindowHeight() const;


	inline unsigned int GetClientWidth() const;
	inline unsigned int GetClientHeight() const;


	inline void SetMainScene(EScene _eScene, void* _pSceneData = 0);
	inline void SetOverlayScene(EOverlayScene _eOverlayScene, void* _pSceneData = 0);


	inline CScene& GetCurrentMainScene();
	inline EScene  GetCurrentMainSceneType() const;


	inline EOverlayScene GetOverlaySceneType() const;
	inline CScene& GetCurrentOverlayScene();


	inline CD3DRenderer* GetRenderer();
	inline COORD& GetMosueCoords();


	inline bool IsFullscreen() const;
	inline bool IsFocused() const;


protected:


	virtual bool InitialiseWindowHandle(HINSTANCE _hInstance);
	virtual bool InitialiseRenderer(unsigned char _ucDisplayAdapter, unsigned int _uiMultisampleType);
	virtual bool InitialiseClock();


	void TurnOnCursorClip();
	void TurnOffCursorClip();


	virtual void ExecuteMainSceneChange() = 0;
	virtual void ExecuteOverlaySceneChange() = 0;


	virtual void UpdatePresentParameters(unsigned int _uiRefreshRate);


	virtual void RecalculateClientRect();


	virtual void UpdateResolutionINI(unsigned int _uiRefreshRate);


private:


	bool InitialiseWinClass(HINSTANCE _hInstance);
	

	void Deinitialise();


	CWindow(const CWindow& _krWindow);
	CWindow& operator=(const CWindow& _krWindow);


	// Member Variables
protected:


	HWND m_hWindowHandle;


	COORD m_crdMousePosition;


	const char* m_kcpWindowTitle;


	CD3DRenderer* m_pRenderer;
	CClock*		  m_pClock;


	unsigned int m_uiWindowWidth;
	unsigned int m_uiWindowHeight;


	unsigned int m_uiClientWidth;
	unsigned int m_uiClientHeight;


	int m_iMarginX;
	int m_iMarginY;


	unsigned int m_uiUpdateRendererHertz;


	DWORD m_dwStyles;


	CScene* m_pMainScene;
	EScene  m_eMainScene;


	CScene*       m_pOverlayScene;
	EOverlayScene m_eOverlayScene;


	EScene  m_eChangeToMainScene;
	void*   m_pChangeToMainSceneData;


	EOverlayScene m_eChangeToOverlayScene;
	void*         m_pChangeToOverlaySceneData;


	bool m_bUpdateRendererResolution;
	bool m_bFullscreen;
	bool m_bFocused;


	static bool m_bShowingCursor;
	static bool m_bCursorStateLocked;


private:


	static CWindow* s_pActiveWindowsInstances[WINDOWS_MAX];
	static HWND*	s_pActiveWindowsHandles[WINDOWS_MAX];
	static UINT		s_uiNumActiveWindows;


};


#include "Inline/Window.inl"


#endif //__IGFEB11_IG500_WINDOW_H__