//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   WindowData.h
//  Description :   Data container required for initialing window instance.
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_WINDOWDATA_H__
#define __IGFEB11_IG500_WINDOWDATA_H__


// Library Includes
#include <windows.h>


// Local Includes


// Types


// Constants


// Prototypes


class CWindowData
{

	// Member Functions
public:


	 CWindowData();
	~CWindowData();


	void SetWindowTitle(const char* _kcpWindowTitle);
	void SetStyles(DWORD _dwStyles);
	void SetMarginX(int _iMarginX);
	void SetMarginY(int _iMarginY);
	void SetWidth(unsigned int _uiWidth);
	void SetHeight(unsigned int _uiHeight);
	void SetDisplayAdapter(unsigned char _ucDisplayAdapter);
	void SetMultisamplingType(unsigned int _uiMultisampleType);
	void SetFullscreen(bool _bFullScreen);


	const char*	  GetWindowTitle();
	DWORD		  GetStyles();
	int  GetMarginX();
	int  GetMarginY();
	unsigned int  GetWidth();
	unsigned int  GetHeight();
	unsigned char GetDisplayAdapter();
	unsigned int  GetMultisampleType();
	bool		  GetFullscreen();


	// Inline Functions


protected:


private:


	// Member Variables
protected:


private:


	const char* m_kcpWindowTitle;


	DWORD m_dwStyles;


	int m_iMarginX;
	int m_iMarginY;


	unsigned int m_uiWidth;
	unsigned int m_uiHeight;


	unsigned int m_uiMultisampleType;


	unsigned char m_ucDisplayAdapter;


	bool m_bFullScreen;


};


#endif //__IGFEB11_IG500_WINDOWDATA_H__