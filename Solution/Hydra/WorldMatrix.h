//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   WorldMatrix.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_WORLDMATRIX_H__
#define __IGFEB11_IG500_WORLDMATRIX_H__


// Library Includes


// Local Includes
#include "Vector3.h"
#include "Matrix.h"


// Types


// Constants


// Prototypes


class CWorldMatrix : public CMatrix
{

	// Member Functions
public:


	 CWorldMatrix();
	~CWorldMatrix();


	// Orientation Settings
	void SetOrientationX(const CVector3& _kv3rOrientationY, const CVector3& _kv3rOrientationZ);
	void SetOrientationY(const CVector3& _kv3rOrientationZ, const CVector3& _kv3rOrientationX);
	void SetOrientationZ(const CVector3& _kv3rOrientationX, const CVector3& _kv3rOrientationY);

	void SetOrientation(const CVector3& _kv3rOrientationX, const CVector3& _kv3rOrientationY, const CVector3& _kv3rOrientationZ);


	// Inline Functions
	inline void SetPositionX(float _fX);
	inline void SetPositionY(float _fY);
	inline void SetPositionZ(float _fZ);
	inline void SetPosition(float _fX, float _fY, float _fZ);
	inline void SetPosition(const CVector3& _kv3rVector);

	inline CVector3& GetPosition(CVector3& _v3rInOutVector) const;
	inline float GetPositionX() const;
	inline float GetPositionY() const;
	inline float GetPositionZ() const;


	// Position Translation
	inline void TranslatePosition(float _fX, float _fY, float _fZ);
	inline void TranslatePosition(const CVector3& _kv3rTranslation);


	inline CVector3& GetOrientationX(CVector3& _v3rOrientationX) const;
	inline CVector3& GetOrientationY(CVector3& _v3rOrientationY) const;
	inline CVector3& GetOrientationZ(CVector3& _v3rOrientationZ) const;


protected:


	void SetOrientationX(const CVector3& _kv3rOrientationX);
	void SetOrientationY(const CVector3& _kv3rOrientationY);
	void SetOrientationZ(const CVector3& _kv3rOrientationZ);


private:


	void Deinitialise();


	// Member Variables
protected:


private:


};


#include "Inline/WorldMatrix.inl"


#endif //__IGFEB11_IG500_WORLDMATRIX_H__