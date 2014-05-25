//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Vector2.inl
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <cmath>


// Local Includes


// Implementation









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CVector2::Set(float _fX, float _fY)
{
	x *= _fX;
	y *= _fY;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CVector2::Scale(float _fValue)
{
	x *= _fValue;
	y *= _fValue;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CVector2::Normalise()
{
	float fMagnitude = 0.0f;

	fMagnitude  = x * x;
	fMagnitude += y * y;
	fMagnitude = sqrt(fMagnitude);


	if (fMagnitude != 0.0f)
	{
		x /= fMagnitude;
		y /= fMagnitude;
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
CVector2::Invert()
{
	x *= -1.0f;
	y *= -1.0f;
}

void
CVector2::Zero()
{
	ZeroMemory(this, sizeof(CVector2));
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CVector2::operator = (const CVector2& _kv2rVector)
{
	x = _kv2rVector.x;
	y = _kv2rVector.y;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CVector2::operator = (const D3DXVECTOR2& _kd3drVector)
{
	x = _kd3drVector.x;
	y = _kd3drVector.y;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector2&
CVector2::operator += (const CVector2& _kv2rVector)
{
	x += _kv2rVector.x;
	y += _kv2rVector.y;

	return (*this);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector2&
CVector2::operator -= (const CVector2& _kv2rVector)
{
	x -= _kv2rVector.x;
	y -= _kv2rVector.y;

	return (*this);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector2&
CVector2::operator *= (float _fScaler)
{
	x *= _fScaler;
	y *= _fScaler;

	return (*this);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector2&
CVector2::operator /= (float _fScaler)
{
	x /= _fScaler;
	y /= _fScaler;

	return (*this);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector2
CVector2::operator + (const CVector2& _kv2rVector) const
{
	s_v2FunctionTemp.x = x + _kv2rVector.x;
	s_v2FunctionTemp.y = y + _kv2rVector.y;

	return (s_v2FunctionTemp);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector2
CVector2::operator - (const CVector2& _kv2rVector) const
{
	s_v2FunctionTemp.x = x - _kv2rVector.x;
	s_v2FunctionTemp.y = y - _kv2rVector.y;

	return (s_v2FunctionTemp);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector2
CVector2::operator * (const CVector2& _kv2rVector) const
{
	s_v2FunctionTemp.x = x * _kv2rVector.x;
	s_v2FunctionTemp.y = y * _kv2rVector.y;

	return (s_v2FunctionTemp);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector2
CVector2::operator / (const CVector2& _kv2rVector) const
{
	s_v2FunctionTemp.x = x / _kv2rVector.x;
	s_v2FunctionTemp.y = y / _kv2rVector.y;

	return (s_v2FunctionTemp);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CVector2::operator == (const CVector2& _kv2rVector) const
{
	if (x == _kv2rVector.x &&
		y == _kv2rVector.y)
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
CVector2::operator != (const CVector2& _kv2rVector) const
{
	if (x != _kv2rVector.x &&
		y != _kv2rVector.y)
	{
		return (true);
	}
	else
	{
		return (false);
	}
}