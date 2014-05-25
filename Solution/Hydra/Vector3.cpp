//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Vector3.cpp
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// This Include
#include "Vector3.h"


// Static Variables
CVector3 CVector3::s_v3FunctionTemp;


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Vector3 class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector3::CVector3()
{
	x = 0;
	y = 0;
	z = 0;
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Vector3 class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector3::CVector3(float _fX, float _fY, float _fZ)
{
	x = _fX;
	y = _fY;
	z = _fZ;
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Vector3 class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector3::CVector3(int _iX, int _iY, int _iZ)
{
	x = static_cast<float>(_iX);
	y = static_cast<float>(_iY);
	z = static_cast<float>(_iZ);
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Vector3 class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector3::CVector3(UINT _uiX, UINT _uiY, UINT _uiZ)
{
	x = static_cast<float>(_uiX);
	y = static_cast<float>(_uiY);
	z = static_cast<float>(_uiZ);
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Vector3 class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector3::CVector3(const D3DXVECTOR3& _kd3drVector)
{
	x = _kd3drVector.x;
	y = _kd3drVector.y;
	z = _kd3drVector.z;
}



/*---------------------------------------------------------------------------------------------------------------------------
*
* Vector3 class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector3::~CVector3()
{
	Deinitialise();
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector3&
CVector3::Cross(const CVector3& _kv3rVector) const
{
	s_v3FunctionTemp.x = (y * _kv3rVector.z) - (z * _kv3rVector.y);
	s_v3FunctionTemp.y = (z * _kv3rVector.x) - (x * _kv3rVector.z);
	s_v3FunctionTemp.z = (x * _kv3rVector.y) - (y * _kv3rVector.x);

	return (s_v3FunctionTemp);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

float
CVector3::Dot(const CVector3& _kv3rVector) const
{
	float fDotResult = 0.0f;

	fDotResult  = x * _kv3rVector.x;
	fDotResult += y * _kv3rVector.y;
	fDotResult += z * _kv3rVector.z;

	return (fDotResult);
}









/********************************
            Protected
*********************************/









/********************************
            Private
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function deinitialises the class instance by freeing memory and calling other necessary functions.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CVector3::Deinitialise()
{
	//Empty
}