//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Text.inl
//  Description :  
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "StrUtilities.h"

// Implementation

void CText::SetPositionX(int _iValue)
{
	m_iPositionX = _iValue;

	UpdateRectBounds();
}

void CText::SetPositionY(int _iValue)
{
	m_iPositionY = _iValue;

	UpdateRectBounds();
}

void CText::SetPosition(int _iValueX, int _iValueY)
{
	SetPositionX(_iValueX);
	SetPositionY(_iValueY);
}

void CText::SetFontSize(unsigned int _FontSize)
{
	FontSize = _FontSize;

	UpdateFont();
	UpdateRectBounds();
}

void CText::SetFontFamily(EFontFamily _eFamily)
{
	m_eFontFamily = _eFamily;

	UpdateFont();
}

void CText::SetItalic(bool _bValue)
{
	m_bItalic = _bValue;

	UpdateFont();
}

void CText::SetWeightHeavy(bool _bValue)
{
	m_bWeightHeavy = _bValue;

	UpdateFont();
}

void CText::SetColour(DWORD _dwColour)
{
	m_dwColour = _dwColour;
}


void CText::SetFormat(DWORD _dwFormat)
{
	m_dwFormat = _dwFormat;
}

RECT CText::GetRect()
{
	return(m_rectBounds);
}

char* CText::GetText(char*& _cpCurrentText)
{
	if (m_wcpText != 0)
	{
		StrUtilities::ConvertToChar(m_wcpText, _cpCurrentText);
	}

	return (_cpCurrentText);
}