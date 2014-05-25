//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Framework/DirectX/Text.h
//  Description :  
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


#pragma once


#ifndef __IGFEB11_IG500_TEXT_H__
#define __IGFEB11_IG500_TEXT_H__


// Library Includes
#include <D3dx9core.h>
#include <vector>


// Local Includes
#include "DeviceResetTarget.h"


// Types
enum EFontFamily
{
	FONTFAMILY_INVALID,
	FONTFAMILY_ARIAL,
	FONTFAMILY_VERDANA,
	FONTFAMILY_TAHOMA,
	FONTFAMILY_MAX
};


// Constants


// Prototypes
class CD3DRenderer;


class CText : public CDeviceResetTarget
{
	// Member Functions
public:
	         CText();
	virtual ~CText();

	bool Initialise(CD3DRenderer* _pRenderer);
	void Draw(CD3DRenderer* _pRenderer);

	void SetText(const char* _kcpText);

	// Inline Functions
	inline void SetPositionX(int _iValue);
	inline void SetPositionY(int _iValue);
	inline void SetPosition(int _iValueX, int _iValueY);
	inline void SetFontSize(unsigned int _FontSize);
	inline void SetFontFamily(EFontFamily _eFamily);
	inline void SetItalic(bool _bValue);
	inline void SetWeightHeavy(bool _bValue);
	inline void SetColour(DWORD _dwColour);
	inline void SetFormat(DWORD _dwFormat);	
	
	inline RECT GetRect();
	inline char* GetText(char*& _cpCurrentText);


protected:


	virtual void OnDeviceLost();
	virtual void OnDeviceReset();


private:



	void UpdateFont();
	void UpdateRectBounds();


	bool Deinitialise();



	// Member Variables
protected:


private:


	RECT m_rectBounds;


	CD3DRenderer* m_pRenderer;
	ID3DXFont*    m_pd3dFont;
	wchar_t*      m_wcpText;


	EFontFamily m_eFontFamily;
	

	DWORD m_dwColour;
	DWORD m_dwFormat;

	int m_iPositionX;
	int m_iPositionY;


	unsigned int FontSize;


	bool m_bItalic;
	bool m_bWeightHeavy;


};


#include "Inline/Text.inl"


#endif // __IGFEB11_IG500_TEXT_H__