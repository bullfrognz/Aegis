//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Text.cpp
//  Description :  
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes
#include <windows.h>
#include <iostream>

// Local Includes
#include "Macros.h"
#include "D3DRenderer.h"
#include "DeviceManager.h"


// This Include
#include "Text.h"


// Static Variables


// Static Function Prototypes


// Implementation


CText::CText()
: m_pRenderer(0)
, m_pd3dFont(0)
, m_wcpText(0)
, m_dwColour(0)
, m_iPositionX(0)
, m_iPositionY(0)
, m_eFontFamily(FONTFAMILY_INVALID)
, FontSize(0)
, m_bItalic(false)
, m_bWeightHeavy(false)
, m_dwFormat(DT_TOP | DT_LEFT)
{
	ZeroMemory(&m_rectBounds, sizeof(RECT));
}


CText::~CText()
{
	FW_RELEASE(m_pd3dFont);
	Deinitialise();
}


bool
CText::Initialise(CD3DRenderer* _pRenderer)
{
	m_pRenderer = _pRenderer;

	m_eFontFamily = FONTFAMILY_TAHOMA;
	FontSize = 16;
	m_dwColour = 0xffFFFFFF;

	UpdateFont();
	UpdateRectBounds();
	
	return (true);
}


void
CText::Draw(CD3DRenderer* _pRenderer)
{
	if (_pRenderer == m_pRenderer && m_wcpText)
	{
		m_pd3dFont->DrawText(NULL, m_wcpText,  -1, &m_rectBounds, m_dwFormat, m_dwColour);
	}
}

void
CText::SetText(const char* _kcpText)
{
	if (m_wcpText != 0)
	{
		delete m_wcpText;
		m_wcpText = 0;
	}

	StrUtilities::ConvertToWChar(_kcpText, m_wcpText);


	UpdateRectBounds();
}


void
CText::UpdateFont()
{
	if (m_pd3dFont != 0)
	{
		FW_RELEASE(m_pd3dFont);
	}

	D3DXFONT_DESC d3dFontDesc;
	ZeroMemory(&d3dFontDesc, sizeof(D3DXFONT_DESC));

	d3dFontDesc.Height = FontSize;
	d3dFontDesc.Weight = (m_bWeightHeavy == false) ? FW_THIN : FW_HEAVY;
	d3dFontDesc.MipLevels = D3DX_DEFAULT;
	d3dFontDesc.Italic = m_bItalic;
	d3dFontDesc.CharSet = 0;
	d3dFontDesc.OutputPrecision = 0;
	d3dFontDesc.PitchAndFamily = 0;
	//d3dFontDesc.Quality = 1;

	char cFontFamilyBuffer[32];

	switch (m_eFontFamily)
	{
	case FONTFAMILY_ARIAL:
		sprintf_s(cFontFamilyBuffer, 32, "arial");
		break;

	case FONTFAMILY_VERDANA:
		sprintf_s(cFontFamilyBuffer, 32, "verdana");
		break;

	case FONTFAMILY_TAHOMA:
		sprintf_s(cFontFamilyBuffer, 32, "tahoma");
		break;

	default:
		LOG_FATALERROR(false, "Unable to define font type");
		break;
	}

	short sStrLength = static_cast<int>(strlen(cFontFamilyBuffer)) + 1;

	for (int i = 0; i <= sStrLength; ++i)
	{
		d3dFontDesc.FaceName[i] = cFontFamilyBuffer[i];
	}

	m_pRenderer->GetDeviceManager().CreateFont(d3dFontDesc, m_pd3dFont);
}


void
CText::UpdateRectBounds()
{
	if (m_wcpText != 0)
	{
		m_rectBounds.top = m_iPositionY;
		m_rectBounds.bottom = m_rectBounds.top + FontSize;
		m_rectBounds.left = m_iPositionX;
		m_rectBounds.right = m_rectBounds.left + static_cast<int>(wcslen(m_wcpText)) * FontSize;
	}
}


void
CText::OnDeviceLost()
{
	HRESULT hResult = m_pd3dFont->OnLostDevice();
}


void
CText::OnDeviceReset()
{
	HRESULT hResult = m_pd3dFont->OnResetDevice();
}


bool
CText::Deinitialise()
{
	delete[] m_wcpText;
	m_wcpText = 0;

	return (true);
}