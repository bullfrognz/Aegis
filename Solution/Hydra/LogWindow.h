//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	LogWindow.h
//	Description	:	Declaration of CLogWindow
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

#pragma once
#ifndef __LOGWINDOW_H__
#define __LOGWINDOW_H__

// Library includes.
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>
#include <map>

// Local includes.
#include "LogTarget.h"
#include "DeviceResetTarget.h"
class CINIParser;

struct TLogWindowErrorData	// Error messages being dumped to file.
{
	float m_fTime;
	char* m_pcMessage;
};

struct TLogWindowData	// Window messages.
{
	RECT m_rectDest;
	D3DCOLOR m_colour;
	DWORD m_dwAlignment;
};

class CLogWindow : public ILogTarget , public CDeviceResetTarget
{
	// Member functions:
public:
	         CLogWindow();
	virtual ~CLogWindow();

	bool Initialise(IDirect3DDevice9* _pDevice);
	void Process(float _fDeltaTick);

	unsigned int CreateNewFont(unsigned int _uiCharWidth,
							   unsigned int _uiCharHeight,
							   unsigned int _uiCharWeight,
							   const wchar_t* _pwFontName);

	void DeleteFont(unsigned int _uiFontID);

	void SetFont(unsigned int _uiFontID);	// Set the font that all text will be drawn in until the next change.

	unsigned int CreateNewLogBox(D3DCOLOR _colour, const RECT& _rkRectBounds, DWORD _dwAlignmentFlags);
	void DeleteLogBox(unsigned int _uiID);

	void SetErrorMessageColour(D3DCOLOR _colour);
	void SetErrorMessagePosition(LONG _iTop, LONG _iLeft, LONG _iBottom, LONG _iRight);
	void SetErrorMessagePosition(const RECT& _rkRect);
	void SetErrorMessageAlignment(DWORD _dwAlignmentFlags);

	void Write(const char* _pcMessage);	// Writes into error message buffer.
	void PrintErrorMessages();	// Should be called every draw().

	void WriteToBuffer(const char* _pcFormat, ...);	// Writes into log box buffer.
	void EmptyBuffer();	// Empties the log box buffer.
	bool PrintToScreen(unsigned int _uiLogBoxID, D3DCOLOR _dwTempColour = 0, DWORD _dwTempAlignment = DT_INTERNAL);	// Renders the contents of the log box buffer to the provided log box.

protected:
	bool ResizeBuffer(unsigned int _uiExtra);	// Log box text buffer.
	bool ResizeLogWindowBuffer();	// Log box buffer.
	bool ResizeFontBuffer();	// 


	virtual void OnDeviceLost();
	virtual void OnDeviceReset();


private:

	// Member data.
public:

protected:
	IDirect3DDevice9* m_pDevice;

	// Fonts.
	ID3DXFont** m_arrpFonts;
	unsigned int m_uiNumFonts;
	unsigned int m_uiCurrentFont;

	// Printing error messages to screen.
	TLogWindowData m_ErrorWindow;
	std::vector<TLogWindowErrorData*> m_vecpErrorLogs;	// Individual error messages being collected.
	char* m_pcErrorBuffer;
	const unsigned int m_kuiErrorBufferSize;
	float m_fDisplayTime;	// Time each message is displayed for.

	// Individual logging boxes.
	TLogWindowData** m_arrpLogBoxes;
	unsigned int m_uiNumLogBoxes;

	int m_iCurrLogBox;
	unsigned int m_uiCurrChar;
	unsigned int m_uiBufferSize;
	const unsigned int m_kuiUpperLimit;
	char* m_pcBuffer;

private:
};

#endif	// __LOGWINDOW_H__