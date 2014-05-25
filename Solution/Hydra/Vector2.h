//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Vector2.h
//  Description :   
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_VECTOR2_H__
#define __IGFEB11_IG500_VECTOR2_H__


// Library Includes
#include <windows.h>
#include <d3dx9.h>


// Local Includes


// Types


// Constants


// Prototypes
class CVector2;


class CVector2 : public D3DXVECTOR2
{

	// Member Functions
public:


	 CVector2();
	 CVector2(float _fX, float _fY);
	 CVector2(int _iX, int _iY);
	 CVector2(UINT _uiX, UINT _uiY);
	~CVector2();


	// Inline Functions
	inline void Set(float _fX, float _fY);
	inline void Scale(float _fValue);
	inline void Normalise();
	inline void Invert();
	inline void Zero();


	// Operator Functions
	inline void operator = (const CVector2& _kv2rVector);
	inline void operator = (const D3DXVECTOR2& _kd3drVector);


    inline CVector2& operator += (const CVector2& _kv2rVector);
    inline CVector2& operator -= (const CVector2& _kv2rVector);
    inline CVector2& operator *= (float _fScaler);
    inline CVector2& operator /= (float _fScaler);


	inline CVector2 operator + (const CVector2& _kv2rVector) const;
	inline CVector2 operator - (const CVector2& _kv2rVector) const;
	inline CVector2 operator * (const CVector2& _kv2rVector) const;
	inline CVector2 operator / (const CVector2& _kv2rVector) const;


	inline bool operator == (const CVector2& _kv2rVector) const;
	inline bool operator != (const CVector2& _kv2rVector) const;


protected:


private:


	void Deinitialise();


	// Member Variables
protected:


private:


	static CVector2 s_v2FunctionTemp;


};


#include "Inline/Vector2.inl"


#endif //__IGFEB11_IG500_VECTOR2_H__