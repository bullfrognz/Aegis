//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   WorldMatrix.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// This Include
#include "WorldMatrix.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* WorldMatrix class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWorldMatrix::CWorldMatrix()
{
	D3DXMatrixIdentity(this);
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* WorldMatrix class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWorldMatrix::~CWorldMatrix()
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

void
CWorldMatrix::SetOrientationX(const CVector3& _kv3rOrientationY, const CVector3& _kv3rOrientationZ)
{
	//Set orientation Y
	SetOrientationY(_kv3rOrientationY);


	//Set orientation Z
	SetOrientationZ(_kv3rOrientationZ);


	//Calculate new orientation x vector
	CVector3 m_v3OrientationX = _kv3rOrientationY.Cross(_kv3rOrientationZ);


	//Set orientation X
	SetOrientationX(m_v3OrientationX);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWorldMatrix::SetOrientationY(const CVector3& _kv3rOrientationZ, const CVector3& _kv3rOrientationX)
{
	//Set orientation Y
	SetOrientationZ(_kv3rOrientationZ);


	//Set orientation Z
	SetOrientationX(_kv3rOrientationX);


	//Calculate new orientation x vector
	CVector3 m_v3OrientationY = _kv3rOrientationZ.Cross(_kv3rOrientationX);


	//Set orientation X
	SetOrientationY(m_v3OrientationY);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWorldMatrix::SetOrientationZ(const CVector3& _kv3rOrientationX, const CVector3& _kv3rOrientationY)
{
	//Set orientation Y
	SetOrientationX(_kv3rOrientationX);


	//Set orientation Y
	SetOrientationY(_kv3rOrientationY);


	//Calculate new orientation x vector
	CVector3 m_v3OrientationZ = _kv3rOrientationX.Cross(_kv3rOrientationY);


	//Set orientation X
	SetOrientationZ(m_v3OrientationZ);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void 
CWorldMatrix::SetOrientation(const CVector3& _kv3rOrientationX, const CVector3& _kv3rOrientationY, const CVector3& _kv3rOrientationZ)
{
	//Set orientation Y
	SetOrientationX(_kv3rOrientationX);


	//Set orientation Y
	SetOrientationY(_kv3rOrientationY);


	//Set orientation X
	SetOrientationZ(_kv3rOrientationZ);
}









/********************************
            Protected
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWorldMatrix::SetOrientationX(const CVector3& _kv3rOrientationX)
{
	_11 = _kv3rOrientationX.x;
	_12 = _kv3rOrientationX.y;
	_13 = _kv3rOrientationX.z;
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWorldMatrix::SetOrientationY(const CVector3& _kv3rOrientationY)
{
	_21 = _kv3rOrientationY.x;
	_22 = _kv3rOrientationY.y;
	_23 = _kv3rOrientationY.z;
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWorldMatrix::SetOrientationZ(const CVector3& _kv3rOrientationZ)
{
	_31 = _kv3rOrientationZ.x;
	_32 = _kv3rOrientationZ.y;
	_33 = _kv3rOrientationZ.z;
}









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
CWorldMatrix::Deinitialise()
{
	//Empty
}