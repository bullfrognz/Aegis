//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Matrix.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_MATRIX_H__
#define __IGFEB11_IG500_MATRIX_H__


// Library Includes
#include <windows.h>
#include <d3dx9.h>


// Local Includes


// Types


// Constants


// Prototypes

__declspec(align(16))
class CMatrix : public D3DXMATRIXA16
{

	// Member Functions
public:


	 CMatrix();
	~CMatrix();


    CMatrix& operator += (const CMatrix& _kmtxrMatrix);
    CMatrix& operator -= (const CMatrix& _kmtxrMatrix);
    CMatrix& operator *= (const CMatrix& _kmtxrMatrix);
    CMatrix& operator /= (const CMatrix& _kmtxrMatrix);


	CMatrix operator + (const CMatrix& _kmtxrMatrix) const;
	CMatrix operator - (const CMatrix& _kmtxrMatrix) const;
	CMatrix operator * (const CMatrix& _kmtxrMatrix) const;
	CMatrix operator / (const CMatrix& _kmtxrMatrix) const;


	// Inline Functions
	inline void Inverse();


	inline float GetDeterminant() const;


	// Operator Functions
	inline void operator = (const D3DXMATRIX& _kmtxrMatrix);
	inline void operator = (const CMatrix& _kmtxrMatrix);


    inline bool operator == (const CMatrix& _kmtxrMatrix) const;
    inline bool operator != (const CMatrix& _kmtxrMatrix) const;


protected:


private:


	void Deinitialise();


	// Member Variables
protected:


private:


};


#include "Inline/Matrix.inl"


#endif //__IGFEB11_IG500_MATRIX_H__