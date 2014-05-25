//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	LogWindow.cpp
//	Description	:	Definition of CLogWindow
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// Library includes.
#include <cassert>
#include <stdarg.h>
#include <varargs.h>

// Local includes.
#include "Utility.h"
#include "IniParser.h"
#include "Macros.h"

// This include.
#include "LogWindow.h"

CLogWindow::CLogWindow()
: m_pDevice(0)
, m_arrpFonts(0)
, m_uiNumFonts(0)
, m_uiCurrentFont(Utility::INVALID_ID)
, m_pcErrorBuffer(0)
, m_kuiErrorBufferSize(500)
, m_fDisplayTime(10.0f)	// Beats zero.
, m_arrpLogBoxes(0)
, m_uiNumLogBoxes(0)
, m_iCurrLogBox(-1)
, m_uiCurrChar(0)
, m_uiBufferSize(0)
, m_kuiUpperLimit(2000)	// Max characters.
, m_pcBuffer(0)
{
	ZeroMemory(&m_ErrorWindow, sizeof(TLogWindowData));
}

CLogWindow::~CLogWindow()
{
	for (unsigned int ui = 0; ui < m_uiNumFonts; ++ui)
	{
		assert(m_arrpFonts);

		if (m_arrpFonts[ui])
			m_arrpFonts[ui]->Release();
	}
	delete[] m_arrpFonts;

	delete[] m_pcBuffer;

	for (unsigned int ui = 0; ui < m_vecpErrorLogs.size(); ++ui)
	{
		delete[] m_vecpErrorLogs[ui]->m_pcMessage;
		delete m_vecpErrorLogs[ui];
	}
	m_vecpErrorLogs.clear();

	delete[] m_pcErrorBuffer;

	for (unsigned int ui = 0; ui < m_uiNumLogBoxes; ++ui)
	{
		delete m_arrpLogBoxes[ui];
	}
	delete[] m_arrpLogBoxes;

	if (m_pDevice)
		m_pDevice->Release();
}

/**
*
* Sets up writing text to the screen.
*
* @author Jade Abbott
* @return True if initialisation was successful.
*
*/
bool
CLogWindow::Initialise(IDirect3DDevice9* _pDevice)
{
	assert(_pDevice);
	assert(!m_pDevice);

	m_pDevice = _pDevice;
	m_pDevice->AddRef();

	delete[] m_pcBuffer;
	m_uiBufferSize = 100;
	m_pcBuffer = new char[m_uiBufferSize];
	if (!m_pcBuffer)
		return false;

	*m_pcBuffer = 0;	// Set first char as null terminator.

	//_rkIniParser.GetValue("Renderer", "Error Display Time", m_fDisplayTime);
	m_fDisplayTime = 3.0f;
	return true;
}

/**
*
* @author Jade Abbott
*
*/
void
CLogWindow::Process(float _fDeltaTick)
{
	if (!m_vecpErrorLogs.empty())
	{
		for (unsigned int ui = 0; ui < m_vecpErrorLogs.size(); ++ui)
		{
			TLogWindowErrorData* pLog = m_vecpErrorLogs[ui];
			pLog->m_fTime -= _fDeltaTick;
			if (pLog->m_fTime <= 0.0f)
			{
				delete[] m_vecpErrorLogs[ui]->m_pcMessage;
				delete m_vecpErrorLogs[ui];
				m_vecpErrorLogs.erase(m_vecpErrorLogs.begin() + ui);
				--ui;
			}
		}
	}
}

/**
*
* @author Jade Abbott
*
*/
unsigned int
CLogWindow::CreateNewFont(unsigned int _uiCharWidth,
						  unsigned int _uiCharHeight,
						  unsigned int _uiCharWeight,
						  const wchar_t* _pwFontName)
{
	// Create the font.
	assert(m_pDevice);

	D3DXFONT_DESC fontDesc;
	ZeroMemory(&fontDesc, sizeof(D3DXFONT_DESC));

	fontDesc.Width = _uiCharWidth;
	fontDesc.Height = _uiCharHeight;
	fontDesc.Weight = _uiCharWeight;
	fontDesc.MipLevels = D3DX_DEFAULT;
	wcscpy_s(fontDesc.FaceName, 32, _pwFontName);

	ID3DXFont* pFont = 0;
	HRESULT hr = D3DXCreateFontIndirect(m_pDevice, &fontDesc, &pFont);

	if (FAILED(hr) || !pFont)
		return Utility::INVALID_ID;

	// Find free slot in the array.
	for (unsigned int ui = 0; ui < m_uiNumFonts; ++ui)
	{
		assert(m_arrpFonts);

		if (!m_arrpFonts[ui])	// If this slot is free...
		{
			m_arrpFonts[ui] = pFont;
			return ui;
		}
	}
	// Else there was no free slots.

	if (ResizeFontBuffer())	// If resizing was successful...
	{
		m_arrpFonts[m_uiNumFonts - 1] = pFont;
		return m_uiNumFonts - 1;
	}
	else	// Resizing was unsuccessful...
	{
		return Utility::INVALID_ID;
	}
}

/**
*
* @author Jade Abbott
*
*/
void
CLogWindow::DeleteFont(unsigned int _uiFontID)
{
	assert(m_arrpFonts);

	if (_uiFontID == Utility::INVALID_ID)
		return;

	assert(_uiFontID < m_uiNumFonts);

	if (m_arrpFonts[_uiFontID])
	{
		m_arrpFonts[_uiFontID]->Release();
		m_arrpFonts[_uiFontID] = 0;
	}
	
}

/**
*
* @author Jade Abbott
*
*/
void
CLogWindow::SetFont(unsigned int _uiFontID)
{
	assert(m_arrpFonts);

	if (_uiFontID == Utility::INVALID_ID)
		return;

	assert(_uiFontID < m_uiNumFonts);
	assert(m_arrpFonts[_uiFontID]);

	if (_uiFontID != Utility::INVALID_ID)
	{
		m_uiCurrentFont = _uiFontID;
	}
}

/**
*
* @author Jade Abbott
*
*/
unsigned int
CLogWindow::CreateNewLogBox(D3DCOLOR _colour, const RECT& _rkRectBounds, DWORD _dwAlignmentFlags)
{
	TLogWindowData* pData = new TLogWindowData();
	if (!pData)
		return Utility::INVALID_ID;

	pData->m_rectDest = _rkRectBounds;
	pData->m_colour = _colour;
	pData->m_dwAlignment = _dwAlignmentFlags;

	// Find a free element in the array, otherwise resize the array.
	for (unsigned int ui = 0; ui < m_uiNumLogBoxes; ++ui)
	{
		assert(m_arrpLogBoxes);
		
		if (!m_arrpLogBoxes[ui])
		{
			m_arrpLogBoxes[ui] = pData;
			return ui;
		}
	}
	// Else there is no room in the array.

	if (ResizeLogWindowBuffer())	// If successfully resized...
	{
		m_arrpLogBoxes[m_uiNumLogBoxes - 1] = pData;
		return m_uiNumLogBoxes - 1;
	}
	else	// Resizing failed...
	{
		delete pData;
		return Utility::INVALID_ID;
	}
}

/**
*
* @author Jade Abbott
*
*/
void
CLogWindow::DeleteLogBox(unsigned int _uiID)
{
	assert(m_arrpLogBoxes);
	assert(_uiID < m_uiNumLogBoxes);
	delete m_arrpLogBoxes[_uiID];
	m_arrpLogBoxes[_uiID] = 0;
}

/**
*
* @author Jade Abbott
*
*/
void
CLogWindow::SetErrorMessageColour(D3DCOLOR _colour)
{
	m_ErrorWindow.m_colour = _colour;
}

/**
*
* @author Jade Abbott
*
*/
void
CLogWindow::SetErrorMessagePosition(LONG _iTop, LONG _iLeft, LONG _iBottom, LONG _iRight)
{
	m_ErrorWindow.m_rectDest.top = _iTop;
	m_ErrorWindow.m_rectDest.left = _iLeft;
	m_ErrorWindow.m_rectDest.bottom = _iBottom;
	m_ErrorWindow.m_rectDest.right = _iRight;
}

/**
*
* @author Jade Abbott
*
*/
void
CLogWindow::SetErrorMessagePosition(const RECT& _rkRect)
{
	m_ErrorWindow.m_rectDest = _rkRect;
}

/**
*
* @author Jade Abbott
*
*/
void
CLogWindow::SetErrorMessageAlignment(DWORD _dwAlignmentFlags)
{
	m_ErrorWindow.m_dwAlignment = _dwAlignmentFlags;
}

/**
*
* @author Jade Abbott
*
*/
void
CLogWindow::Write(const char *_pcMessage)
{
	TLogWindowErrorData* pLog = new TLogWindowErrorData();
	if (!pLog)
		return;

	unsigned int uiStringLength = 0;
	while(_pcMessage[uiStringLength++]);	// Includes null terminator.

	char* pcMessageCopy = new char[uiStringLength];
	if (!pcMessageCopy)
	{
		delete pLog;
		return;
	}

	memcpy(pcMessageCopy, _pcMessage, uiStringLength);

	pLog->m_fTime = m_fDisplayTime;	// Time (in seconds) until log disappears.
	pLog->m_pcMessage = pcMessageCopy;


	m_vecpErrorLogs.push_back(pLog);
}

/**
*
* @author Jade Abbott
*
*/
void
CLogWindow::PrintErrorMessages()
{
	// Error reports accumulated through the log manager.
	if (!m_vecpErrorLogs.empty())
	{
		if (!m_pcErrorBuffer)
		{
			m_pcErrorBuffer = new char[m_kuiErrorBufferSize];
			if (!m_pcErrorBuffer)
			{
				return;
			}
		}

		unsigned int uiCurrChar = 0;

		for (unsigned int ui = 0; ui < m_vecpErrorLogs.size(); ++ui)
		{
			int iResult = _snprintf_s(m_pcErrorBuffer + uiCurrChar, m_kuiErrorBufferSize - uiCurrChar, (m_kuiErrorBufferSize - uiCurrChar) - 1, "%s", m_vecpErrorLogs[ui]->m_pcMessage);

			if (iResult == -1)
			{
				break;
			}
			else
			{
				uiCurrChar += iResult;
			}
		}

		if (m_arrpFonts && m_uiCurrentFont != Utility::INVALID_ID)
		{
			if (m_arrpFonts[m_uiCurrentFont])
			{
				m_arrpFonts[m_uiCurrentFont]->DrawTextA(NULL, m_pcErrorBuffer, -1, &m_ErrorWindow.m_rectDest, m_ErrorWindow.m_dwAlignment, m_ErrorWindow.m_colour);
			}
		}
	}
	else if (m_pcErrorBuffer)	// if there are no more error logs, but the buffer still exists...
	{
		delete[] m_pcErrorBuffer;	// Delete the buffer.
		m_pcErrorBuffer = 0;
	}
}

/**
*
* @author Jade Abbott
*
*/
void
CLogWindow::WriteToBuffer(const char* _pcFormat, ...)
{
	if (!m_pcBuffer)
	{
		return;
	}

	// Add new line character to buffer, if this is not the first line, or the last character.
	if (m_uiCurrChar != m_uiBufferSize - 1 && m_uiCurrChar != 0)	// If not the last character...
	{
		*(m_pcBuffer + m_uiCurrChar) = '\n';
		++m_uiCurrChar;
		*(m_pcBuffer + m_uiCurrChar) = 0;
	}

	// _vsnprintf_s returns -1 if truncation occured.
	va_list tempContainer = 0;
	va_start(tempContainer, _pcFormat);
	int iResult = _vsnprintf_s(m_pcBuffer + m_uiCurrChar, m_uiBufferSize - m_uiCurrChar, (m_uiBufferSize - m_uiCurrChar) - 1, _pcFormat, tempContainer);

	if (iResult == -1)
	{
		bool bResult = ResizeBuffer(100);

		if (!bResult)
		{
			return;
		}

		// Try one more time.
		iResult = _vsnprintf_s(m_pcBuffer + m_uiCurrChar, m_uiBufferSize - m_uiCurrChar, (m_uiBufferSize - m_uiCurrChar) - 1, _pcFormat, tempContainer);

		if (iResult != -1)
		{
			m_uiCurrChar += iResult;
		}
	}
	else
	{
		m_uiCurrChar += iResult;
	}
}

/**
*
* @author Jade Abbott
*
*/
void
CLogWindow::EmptyBuffer()
{
	if (m_uiBufferSize)
	{
		*m_pcBuffer = 0;	// Set first char as null terminator.
		m_uiCurrChar = 0;
	}
}

/**
*
* @author Jade Abbott
*
*/
bool
CLogWindow::PrintToScreen(unsigned int _uiLogBoxID, D3DCOLOR _dwTempColour, DWORD _dwTempAlignment)
{
	if (_uiLogBoxID == Utility::INVALID_ID || m_uiCurrentFont == Utility::INVALID_ID)
		return false;

	assert(_uiLogBoxID < m_uiNumLogBoxes);
	assert(m_arrpLogBoxes);
	assert(m_arrpLogBoxes[_uiLogBoxID]);
	assert(m_arrpFonts);
	assert(m_arrpFonts[m_uiCurrentFont]);

	TLogWindowData& rData = *m_arrpLogBoxes[_uiLogBoxID];

	m_arrpFonts[m_uiCurrentFont]->DrawTextA(NULL, m_pcBuffer, -1, &rData.m_rectDest, _dwTempAlignment != DT_INTERNAL ? _dwTempAlignment : rData.m_dwAlignment, _dwTempColour ? _dwTempColour : rData.m_colour);

	return true;
}

/**
*
* @author Jade Abbott
*
*/
bool
CLogWindow::ResizeBuffer(unsigned int _uiExtra)
{
	if (m_uiBufferSize == m_kuiUpperLimit)
	{
		return false;
	}

	if (m_uiBufferSize + _uiExtra > m_kuiUpperLimit)
	{
		_uiExtra = m_kuiUpperLimit - m_uiBufferSize;
	}

	char* pTemp = new char[m_uiBufferSize + _uiExtra];
	if (!pTemp)
	{
		return false;
	}

	m_uiBufferSize += _uiExtra;

	memcpy(pTemp, m_pcBuffer, m_uiCurrChar);
	delete[] m_pcBuffer;
	m_pcBuffer = pTemp;

	return true;
}

/**
*
* @author Jade Abbott
*
*/
bool
CLogWindow::ResizeLogWindowBuffer()
{
	TLogWindowData** arrpLogWindows = new TLogWindowData*[m_uiNumLogBoxes + 1];
	if (!arrpLogWindows)
		return false;

	memcpy(arrpLogWindows, m_arrpLogBoxes, sizeof(TLogWindowData*) * m_uiNumLogBoxes);
	arrpLogWindows[m_uiNumLogBoxes] = 0;
	
	delete[] m_arrpLogBoxes;
	m_arrpLogBoxes = arrpLogWindows;
	++m_uiNumLogBoxes;

	return true;
}

/**
*
* @author Jade Abbott
*
*/
bool
CLogWindow::ResizeFontBuffer()
{
	ID3DXFont** arrpFonts = new ID3DXFont*[m_uiNumFonts + 1];
	if (!arrpFonts)
		return false;

	memcpy(arrpFonts, m_arrpFonts, sizeof(ID3DXFont*) * m_uiNumFonts);
	arrpFonts[m_uiNumFonts] = 0;
	
	delete[] m_arrpFonts;
	m_arrpFonts = arrpFonts;
	++m_uiNumFonts;

	return true;
}

/**
*
* @author Jade Abbott
*
*/
void
CLogWindow::OnDeviceLost()
{
	for (unsigned int i = 0; i < m_uiNumFonts; ++i)
	{
		if (m_arrpFonts[i])
		{
			m_arrpFonts[i]->OnLostDevice();
		}
	}
}

/**
*
* @author Jade Abbott
*
*/
void
CLogWindow::OnDeviceReset()
{
	for (unsigned int i = 0; i < m_uiNumFonts; ++i)
	{
		if (m_arrpFonts[i])
		{
			m_arrpFonts[i]->OnResetDevice();
		}
	}
}