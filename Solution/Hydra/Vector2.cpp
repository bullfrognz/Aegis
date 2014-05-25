//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Vector2.cpp
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// This Include
#include "Vector2.h"


// Static Variables
CVector2 CVector2::s_v2FunctionTemp;


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

CVector2::CVector2()
{
	x = 0;
	y = 0;
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Vector3 class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector2::CVector2(float _fX, float _fY)
{
	x = _fX;
	y = _fY;
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Vector3 class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector2::CVector2(int _iX, int _iY)
{
	x = static_cast<float>(_iX);
	y = static_cast<float>(_iY);
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Vector3 class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector2::CVector2(UINT _uiX, UINT _uiY)
{
	x = static_cast<float>(_uiX);
	y = static_cast<float>(_uiY);
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Vector3 class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CVector2::~CVector2()
{
	Deinitialise();
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
CVector2::Deinitialise()
{
	//Empty
}