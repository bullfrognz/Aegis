//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Vector3.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_VECTOR3_H__
#define __IGFEB11_IG500_VECTOR3_H__


// Library Includes
#include <windows.h>
#include <d3dx9.h>


// Local Includes


// Types


// Constants


// Prototypes
class CVector2;


class CVector3 : public D3DXVECTOR3
{

	// Member Functions
public:


	 CVector3();
	 CVector3(float _fX, float _fY, float _fZ);
	 CVector3(int _iX, int _iY, int _iZ);
	 CVector3(UINT _uiX, UINT _uiY, UINT _uiZ);
	 CVector3(const D3DXVECTOR3& _kd3drVector);
	~CVector3();


	CVector3& Cross(const CVector3& _kv3rVector) const;
	float     Dot(const CVector3& _kv3rVector) const;


	// Inline Functions
	inline void Set(float _fX, float _fY, float _fZ);
	inline void Scale(float _fValue);
	inline void Normalise();
	inline void Invert();
	inline void Zero();
	inline bool IsZero() const;


	// Operator Functions
	inline void operator = (const CVector2& _kv2rVector);
	inline void operator = (const CVector3& _kv3rVector);
	inline void operator = (const D3DXVECTOR3& _kd3drVector);
	inline void operator = (const D3DVECTOR& _kd3drVector);
	inline void operator = (const D3DXQUATERNION& _kquatrQuaternion);


    inline CVector3& operator += (const CVector3& _kv3rVector);
    inline CVector3& operator -= (const CVector3& _kv3rVector);
    inline CVector3& operator *= (const CVector3& _kv3rVector);
    inline CVector3& operator /= (const CVector3& _kv3rVector);
    inline CVector3& operator *= (float _fScaler);
    inline CVector3& operator /= (float _fScaler);


	inline CVector3 operator + (const CVector3& _kv3rVector) const;
	inline CVector3 operator - (const CVector3& _kv3rVector) const;
	inline CVector3 operator * (const CVector3& _kv3rVector) const;
	inline CVector3 operator / (const CVector3& _kv3rVector) const;


    inline bool operator == (const CVector3& _kv3rVector) const;
    inline bool operator != (const CVector3& _kv3rVector) const;


protected:


private:


	void Deinitialise();


	// Member Variables
protected:


private:


	static CVector3 s_v3FunctionTemp;


};


#include "Inline/Vector3.inl"


#endif //__IGFEB11_IG500_VECTOR3_H__