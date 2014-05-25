//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Application.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_APPLICATION_H__
#define __IGFEB11_IG500_APPLICATION_H__


// Library Includes
#include <windows.h>
#include <d3dx9.h>

// Local Includes
#include "GameWindow.h"
#include "vector2.h"
#include "SoundSystem.h"

// Types


// Constants


// Prototypes
class CWindow;


class CApplication
{

	// Member Functions
public:


	~CApplication();


	bool Initialise(HINSTANCE _hInstance);


	static CApplication& GetInstance();
	static void DestroyInstance();


	// Inline Functions
	inline HINSTANCE GetInstanceHandle();
	inline CWindow& GetGameWindow();
	inline float GetBaseDimentionRatio();
	inline float GetBaseWidth() const;
	inline float GetBaseHeight() const;
	inline void Quit();

	CVector2* GetMouseCo();


protected:


private:


	bool InitialiseGameWindow();


	void Deinitialise();


	CApplication();
	CApplication(const CApplication& _krApplication);
	CApplication& operator = (const CApplication& _krApplication);


	// Member Variables
public:

protected:


private:

	CVector2* m_pVecMouseCo;

	HINSTANCE m_hInstance;

	IDirect3D9* m_pDirect3D9;
	CWindow*    m_pGameWindow;


	enum 
	{
		m_eBaseWidth  = 1280,
		m_eBaseHeight = 1024
	};


	static CApplication* s_pApplication;


};


#include "Inline/Application.inl"


#endif //__IGFEB11_IG500_APPLICATION_H__