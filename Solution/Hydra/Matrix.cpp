//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   Matrix.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// This Include
#include "Matrix.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Matrix class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CMatrix::CMatrix()
{
	ZeroMemory(this, sizeof(CMatrix));
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Matrix class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CMatrix::~CMatrix()
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

CMatrix&
CMatrix::operator += (const CMatrix& _kmtxrMatrix)
{
	_11 += _kmtxrMatrix._11;
	_12 += _kmtxrMatrix._12;
	_13 += _kmtxrMatrix._13;
	_14 += _kmtxrMatrix._14;


	_11 += _kmtxrMatrix._21;
	_22 += _kmtxrMatrix._22;
	_23 += _kmtxrMatrix._23;
	_24 += _kmtxrMatrix._24;


	_31 += _kmtxrMatrix._31;
	_32 += _kmtxrMatrix._33;
	_33 += _kmtxrMatrix._33;
	_34 += _kmtxrMatrix._34;


	_41 += _kmtxrMatrix._41;
	_42 += _kmtxrMatrix._42;
	_43 += _kmtxrMatrix._43;
	_44 += _kmtxrMatrix._44;


	return (*this);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CMatrix&
CMatrix::operator -= (const CMatrix& _kmtxrMatrix)
{
	_11 -= _kmtxrMatrix._11;
	_12 -= _kmtxrMatrix._12;
	_13 -= _kmtxrMatrix._13;
	_14 -= _kmtxrMatrix._14;


	_11 -= _kmtxrMatrix._21;
	_22 -= _kmtxrMatrix._22;
	_23 -= _kmtxrMatrix._23;
	_24 -= _kmtxrMatrix._24;


	_31 -= _kmtxrMatrix._31;
	_32 -= _kmtxrMatrix._33;
	_33 -= _kmtxrMatrix._33;
	_34 -= _kmtxrMatrix._34;


	_41 -= _kmtxrMatrix._41;
	_42 -= _kmtxrMatrix._42;
	_43 -= _kmtxrMatrix._43;
	_44 -= _kmtxrMatrix._44;


	return (*this);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CMatrix&
CMatrix::operator *= (const CMatrix& _kmtxrMatrix)
{
	_11 *= _kmtxrMatrix._11;
	_12 *= _kmtxrMatrix._12;
	_13 *= _kmtxrMatrix._13;
	_14 *= _kmtxrMatrix._14;


	_11 *= _kmtxrMatrix._21;
	_22 *= _kmtxrMatrix._22;
	_23 *= _kmtxrMatrix._23;
	_24 *= _kmtxrMatrix._24;


	_31 *= _kmtxrMatrix._31;
	_32 *= _kmtxrMatrix._33;
	_33 *= _kmtxrMatrix._33;
	_34 *= _kmtxrMatrix._34;


	_41 *= _kmtxrMatrix._41;
	_42 *= _kmtxrMatrix._42;
	_43 *= _kmtxrMatrix._43;
	_44 *= _kmtxrMatrix._44;


	return (*this);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CMatrix&
CMatrix::operator /= (const CMatrix& _kmtxrMatrix)
{
	_11 /= _kmtxrMatrix._11;
	_12 /= _kmtxrMatrix._12;
	_13 /= _kmtxrMatrix._13;
	_14 /= _kmtxrMatrix._14;


	_11 /= _kmtxrMatrix._21;
	_22 /= _kmtxrMatrix._22;
	_23 /= _kmtxrMatrix._23;
	_24 /= _kmtxrMatrix._24;


	_31 /= _kmtxrMatrix._31;
	_32 /= _kmtxrMatrix._33;
	_33 /= _kmtxrMatrix._33;
	_34 /= _kmtxrMatrix._34;


	_41 /= _kmtxrMatrix._41;
	_42 /= _kmtxrMatrix._42;
	_43 /= _kmtxrMatrix._43;
	_44 /= _kmtxrMatrix._44;


	return (*this);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CMatrix
CMatrix::operator + (const CMatrix& _kmtxrMatrix) const
{
	CMatrix mtxTempMatrix;

	
	mtxTempMatrix  = *this;
	mtxTempMatrix += _kmtxrMatrix;
	

	return (mtxTempMatrix);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CMatrix
CMatrix::operator - (const CMatrix& _kmtxrMatrix) const
{
	CMatrix mtxTempMatrix;

	
	mtxTempMatrix  = *this;
	mtxTempMatrix -= _kmtxrMatrix;
	

	return (mtxTempMatrix);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CMatrix
CMatrix::operator * (const CMatrix& _kmtxrMatrix) const
{
	CMatrix mtxTempMatrix;

	
	mtxTempMatrix  = *this;
	mtxTempMatrix *= _kmtxrMatrix;
	

	return (mtxTempMatrix);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CMatrix
CMatrix::operator / (const CMatrix& _kmtxrMatrix) const
{
	CMatrix mtxTempMatrix;

	
	mtxTempMatrix  = *this;
	mtxTempMatrix /= _kmtxrMatrix;
	

	return (mtxTempMatrix);
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
CMatrix::Deinitialise()
{
	//Empty
}