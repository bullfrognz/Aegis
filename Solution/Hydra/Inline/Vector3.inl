//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Vector3.inl
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <cmath>


// Local Includes
#include "Vector2.h"


// Implementation









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CVector3::Set(float _fX, float _fY, float _fZ)
{
	x = _fX;
	y = _fY;
	z = _fZ;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CVector3::Scale(float _fValue)
{
	x *= _fValue;
	y *= _fValue;
	z *= _fValue;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CVector3::Normalise()
{
	float fMagnitude = 0.0f;


	fMagnitude  = x * x;
	fMagnitude += y * y;
	fMagnitude += z * z;
	fMagnitude = sqrt(fMagnitude);


	if (fMagnitude != 0.0f)
	{
		x /= fMagnitude;
		y /= fMagnitude;
		z /= fMagnitude;
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CVector3::Invert()
{
	x *= -1.0f;
	y *= -1.0f;
	z *= -1.0f;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CVector3::Zero()
{
	ZeroMemory(this, sizeof(CVector3));
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CVector3::IsZero() const
{
	if (x != 0.0f || y != 0.0f || z != 0.0f)
	{
		return (false);
	}
	else
	{
		return (true);
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CVector3::operator = (const CVector2& _kv2rVector)
{
	x = _kv2rVector.x;
	y = _kv2rVector.y;
	z = 0.0f;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CVector3::operator = (const CVector3& _kv3rVector)
{
	x = _kv3rVector.x;
	y = _kv3rVector.y;
	z = _kv3rVector.z;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CVector3::operator = (const D3DXVECTOR3& _kd3drVector)
{
	x = _kd3drVector.x;
	y = _kd3drVector.y;
	z = _kd3drVector.z;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CVector3::operator = (const D3DVECTOR& _kd3drVector)
{
	x = _kd3drVector.x;
	y = _kd3drVector.y;
	z = _kd3drVector.z;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CVector3::operator = (const D3DXQUATERNION& _kquatrQuaternion)
{
	x = _kquatrQuaternion.x;
	y = _kquatrQuaternion.y;
	z = _kquatrQuaternion.z;
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector3&
CVector3::operator += (const CVector3& _kv3rVector)
{
	x += _kv3rVector.x;
	y += _kv3rVector.y;
	z += _kv3rVector.z;

	return (*this);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector3&
CVector3::operator -= (const CVector3& _kv3rVector)
{
	x -= _kv3rVector.x;
	y -= _kv3rVector.y;
	z -= _kv3rVector.z;

	return (*this);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector3&
CVector3::operator *= (const CVector3& _kv3rVector)
{
	x *= _kv3rVector.x;
	y *= _kv3rVector.y;
	z *= _kv3rVector.z;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector3&
CVector3::operator /= (const CVector3& _kv3rVector)
{
	x /= _kv3rVector.x;
	y /= _kv3rVector.y;
	z /= _kv3rVector.z;
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector3&
CVector3::operator *= (float _fScaler)
{
	x *= _fScaler;
	y *= _fScaler;
	z *= _fScaler;

	return (*this);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector3&
CVector3::operator /= (float _fScaler)
{
	x /= _fScaler;
	y /= _fScaler;
	z /= _fScaler;

	return (*this);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector3
CVector3::operator + (const CVector3& _kv3rVector) const
{
	s_v3FunctionTemp.x = x + _kv3rVector.x;
	s_v3FunctionTemp.y = y + _kv3rVector.y;
	s_v3FunctionTemp.z = z + _kv3rVector.z;

	return (s_v3FunctionTemp);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector3
CVector3::operator - (const CVector3& _kv3rVector) const
{
	s_v3FunctionTemp.x = x - _kv3rVector.x;
	s_v3FunctionTemp.y = y - _kv3rVector.y;
	s_v3FunctionTemp.z = z - _kv3rVector.z;

	return (s_v3FunctionTemp);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector3
CVector3::operator * (const CVector3& _kv3rVector) const
{
	s_v3FunctionTemp.x = x * _kv3rVector.x;
	s_v3FunctionTemp.y = y * _kv3rVector.y;
	s_v3FunctionTemp.z = z * _kv3rVector.z;

	return (s_v3FunctionTemp);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector3
CVector3::operator / (const CVector3& _kv3rVector) const
{
	s_v3FunctionTemp.x = x / _kv3rVector.x;
	s_v3FunctionTemp.y = y / _kv3rVector.y;
	s_v3FunctionTemp.z = z / _kv3rVector.z;

	return (s_v3FunctionTemp);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CVector3::operator == (const CVector3& _kv3rVector) const
{
	if (x == _kv3rVector.x &&
		y == _kv3rVector.y &&
		z == _kv3rVector.z)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CVector3::operator != (const CVector3& _kv3rVector) const
{
	if (x != _kv3rVector.x &&
		y != _kv3rVector.y &&
		z != _kv3rVector.z)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}