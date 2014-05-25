//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name	:	Utility.h
//  Description	:	Utilities used across the whole program.
//  Author		:	Team Blue
//  Mail		:	Jamie.Smith@mediadesign.school.nz
//				:	jade.abbott@mediadesign.school.nz
//				:	bryce.booth@mediadesign.school.nz
//				:	joshua.print@mediadesign.school.nz
//				:	daniel.langsford@mediadesign.school.nz
//

#pragma once
#ifndef __HYDRA_UTILITY_H__
#define __HYDRA_UTILITY_H__

// Library includes.
#include <d3dx9.h>

namespace Utility
{
	static const int INVALID_ID = -1;

	static const unsigned char B1 = unsigned char(1);
	static const unsigned char B2 = unsigned char(1) << 1;
	static const unsigned char B3 = unsigned char(1) << 2;
	static const unsigned char B4 = unsigned char(1) << 3;
	static const unsigned char B5 = unsigned char(1) << 4;
	static const unsigned char B6 = unsigned char(1) << 5;
	static const unsigned char B7 = unsigned char(1) << 6;
	static const unsigned char B8 = unsigned char(1) << 7;
}

namespace MathUtility
{
	const float PI = 3.1415926535897932384626433832795f;

	const float				kMaxFloat = 3.402823466e+38F;
	const unsigned char		kMaxUC = 255;
	const unsigned short	kMaxUS = 65535;
	const unsigned int		kMaxUI = 4294967295;

	// Math functions.
	float AngleFromDeltaPos(float _fX, float _fY);
	float LengthOfVecSq(const D3DXVECTOR3& _rkVec);
	bool IsAABBIntersecting(const D3DXVECTOR3& _rkVecMin1,
							const D3DXVECTOR3& _rkVecMax1,
							const D3DXVECTOR3& _rkVecMin2,
							const D3DXVECTOR3& _rkVecMax2,
							bool _bIgnoreY = false);

	void MinimumRepulsionAABB(const D3DXVECTOR3& _rkVecMin1,
							  const D3DXVECTOR3& _rkVecMax1,
							  const D3DXVECTOR3& _rkVecMin2,
							  const D3DXVECTOR3& _rkVecMax2,
							  D3DXVECTOR3& _rVecOut,
							  bool _bIgnoreY = false);

	bool IsLineSphereIntersecting(const D3DXVECTOR3& _rkVecRelLineStart,
								  const D3DXVECTOR3& _rkVecRelLineEnd,
								  float _fSphereRadius);

	void TimeOfLineSphereIntersect(const D3DXVECTOR3& _rkVecRelLineStart,
									const D3DXVECTOR3& _rkVecRelLineEnd,
									float _fSphereRadius,
									float* _pTimeFirstIntersect,
									float* _pTimeSecondIntersect);

	bool IsLineGroundIntersecting(const D3DXVECTOR3& _rkVecLineStart,
								  const D3DXVECTOR3& _rkVecLineEnd,
								  float _fGroundHeight = 0.0f);

	void GetLineGroundIntersect(const D3DXVECTOR3& _rkVecLineStart,
								const D3DXVECTOR3& _rkVecLineEnd,
								D3DXVECTOR3& _rVecIntersectOut,
								float _fGroundHeight = 0.0f);

	// Rotation.
	void Roll(D3DXQUATERNION& _rQuatRot, float _fAngle);
	void Pitch(D3DXQUATERNION& _rQuatRot, float _fAngle);
	void Yaw(D3DXQUATERNION& _rQuatRot, float _fAngle);

	// Translation.
	void Strafe(const D3DXQUATERNION& _krQuatRot, D3DXVECTOR3& _rVecPos, float _fDistance);
	void Fly(const D3DXQUATERNION& _krQuatRot, D3DXVECTOR3& _rVecPos, float _fDistance);
	void Move(const D3DXQUATERNION& _krQuatRot, D3DXVECTOR3& _rVecPos, float _fDistance);

	// Assumes the first 12 bytes of each vertex is the X, Y, and Z position.
	void CalculateBoundingSphere(float& _rSphereRadius, void* _pVertices, unsigned int _uiVertexStride, unsigned int _uiNumVertices);

	DWORD VectorToRGB(const D3DXVECTOR3& _rkVecNorm);
	D3DCOLOR ColourScaleToRGB(float _fRed, float _fGreen, float _fBlue);

	unsigned int RandomNumber(int _iMin, int _iMax);

	float RandomNumber(float _fMin, float _fMax);


	void
	PointRotation(float _fCenterX, float _fCenterY, float _fPointX, float _fPointY,
				  float _fRotationAmount, float& _frNewPointX, float& _frNewPointY);

	void
	CalculatePointAngle(float _fPointX, float _fPointY, float& _frRadianAngle);

}

#endif //__HYDRA_UTILITY_H__
