//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name	:	Utility.cpp
//  Description	:	Utilities used across the whole program.
//  Author		:	Team Blue
//  Mail		:	Jamie.Smith@mediadesign.school.nz
//				:	jade.abbott@mediadesign.school.nz
//				:	bryce.booth@mediadesign.school.nz
//				:	joshua.print@mediadesign.school.nz
//				:	daniel.langsford@mediadesign.school.nz
//

// This include.
#include "Utility.h"

// Library includes.
#include <d3dx9.h>
#include <cassert>

#include "Macros.h"

namespace MathUtility
{
	/**
	*
	* Takes an X and Y float and returns the angle, counter-clockwise from right.
	* 75% of scenarios will perform one square root.
	*
	* @author Jade Abbott
	* @param _fX X position of the point.
	* @param _fY Y position of the point.
	* @return Angle in radians of the vector defined by _fX and _fY, counter-clockwise from right.
	*
	*/
	float
	AngleFromDeltaPos(float _fX, float _fY)
	{
		float fLengthSq = (_fX * _fX) + (_fY * _fY);

		// If the length is zero, just return.
		if (!fLengthSq)
			return 0.0f;

		// Use of CAST is necessary.
		return (_fX >= 0.0f) ? ((_fY < 0.0f) ? (-acosf(_fX / sqrtf(fLengthSq)))
											 : (asinf(_fY / sqrtf(fLengthSq))))
							 : ((_fY < 0.0f) ? (MathUtility::PI + atanf(_fY / _fX))
											 : (MathUtility::PI - asinf(_fY / sqrtf(fLengthSq))));
	}

	/**
	*
	* Returns the squared length of two vectors.
	* Manual calculation is preferred.
	*
	* @author Jade Abbott
	* @param _rkVec The 3D vector to measure.
	* @return The squared length of the provided vector.
	*
	*/
	float
	LengthOfVecSq(const D3DXVECTOR3& _rkVec)
	{
		return (_rkVec.x * _rkVec.x) + (_rkVec.y * _rkVec.y) + (_rkVec.z * _rkVec.z);
	}

	/**
	*
	* Returns true if the two AABB's (defined by minimum and maximum values) are intersecting.
	*
	* @author Jade Abbott
	* @param _rkVecMin1 Minimum X, Y, and Z values for AABB #1.
	* @param _rkVecMax1 Maximum X, Y, and Z values for AABB #1.
	* @param _rkVecMin2 Minimum X, Y, and Z values for AABB #2.
	* @param _rkVecMax2 Maximum X, Y, and Z values for AABB #2.
	* @param _bIgnoreY If true, this function will ignore the height of each AABB when checking for collision.
	* @return True if a collision occured.
	*
	*/
	bool IsAABBIntersecting(const D3DXVECTOR3& _rkVecMin1,
							const D3DXVECTOR3& _rkVecMax1,
							const D3DXVECTOR3& _rkVecMin2,
							const D3DXVECTOR3& _rkVecMax2,
							bool _bIgnoreY)
	{
		return (	_rkVecMin1.x < _rkVecMax2.x
				&&	_rkVecMax1.x > _rkVecMin2.x
				&&	(_bIgnoreY ? true : (_rkVecMin1.y < _rkVecMax2.y && _rkVecMax1.y > _rkVecMin2.y))
				&&	_rkVecMin1.z < _rkVecMax2.z
				&&	_rkVecMax1.z > _rkVecMin2.z);
	}

	/**
	*
	* Returns the minimum distance along the X, Y, or Z axis that AABB #1 must move to stop intersection with AABB #2.
	* This function assumes the AABB's are already intersecting (use IsAABBIntersecting() if unsure).
	*
	* @author Jade Abbott
	* @param _rkVecMin1 Minimum X, Y, and Z values for AABB #1.
	* @param _rkVecMax1 Maximum X, Y, and Z values for AABB #1.
	* @param _rkVecMin2 Minimum X, Y, and Z values for AABB #2.
	* @param _rkVecMax2 Maximum X, Y, and Z values for AABB #2.
	* @param _rVecOut The vector that will contain the resulting minimum translation required.
	* @param _bIgnoreY When true, the minimum adjustment returned will not be a Y adjustment.
	* @return Void.
	*/
	void
	MinimumRepulsionAABB(const D3DXVECTOR3& _rkVecMin1,
						 const D3DXVECTOR3& _rkVecMax1,
						 const D3DXVECTOR3& _rkVecMin2,
						 const D3DXVECTOR3& _rkVecMax2,
						 D3DXVECTOR3& _rVecOut,
						 bool _bIgnoreY)
	{
		// Get translation amount required for all sides (positive and negative translation).
		D3DXVECTOR3 vecPosTra(_rkVecMax2.x - _rkVecMin1.x, _rkVecMax2.y - _rkVecMin1.y, _rkVecMax2.z - _rkVecMin1.z);	// Moving right, up, or forward.
		D3DXVECTOR3 vecNegTra(_rkVecMin2.x - _rkVecMax1.x, _rkVecMin2.y - _rkVecMax1.y, _rkVecMin2.z - _rkVecMax1.z);	// Moving left, down, or backward.

		// Get the significance of the second AABB.
//		D3DXVECTOR3 vecHalfSize1((_rkVecMax1 - _rkVecMin1) * 0.5);
		D3DXVECTOR3 vecHalfSize2((_rkVecMax2 - _rkVecMin2) * 0.5);
		D3DXVECTOR3 vecSignificance(1.0f / vecHalfSize2.x, 1.0f / vecHalfSize2.y, 1.0f / vecHalfSize2.z);

		// Get the significance of the translation for all sides.
		D3DXVECTOR3 vecSigPos(vecPosTra.x * vecSignificance.x, vecPosTra.y * vecSignificance.y, vecPosTra.z * vecSignificance.z);
		D3DXVECTOR3 vecSigNeg(vecNegTra.x * -vecSignificance.x, vecNegTra.y * -vecSignificance.y, vecNegTra.z * -vecSignificance.z);

		// The side with the least significance (the lowest number) is the side that requires the least amount of translation.
		// This is important because if significance was not calculated, two sticks would never collide on their end points,
		// as they would be repelled to the side.

		float fMinSignificance = vecSigPos.x;
		_rVecOut.x = vecPosTra.x;
		_rVecOut.y = 0.0f;
		_rVecOut.z = 0.0f;

		if (vecSigNeg.x < fMinSignificance)
		{
			fMinSignificance = vecSigNeg.x;
			_rVecOut.x = vecNegTra.x;
			_rVecOut.y = 0.0f;
			_rVecOut.z = 0.0f;
		}

		if (!_bIgnoreY)
		{
			if (vecSigPos.y < fMinSignificance)
			{
				fMinSignificance = vecSigPos.y;
				_rVecOut.x = 0.0f;
				_rVecOut.y = vecPosTra.y;
				_rVecOut.z = 0.0f;
			}

			if (vecSigNeg.y < fMinSignificance)
			{
				fMinSignificance = vecSigNeg.y;
				_rVecOut.x = 0.0f;
				_rVecOut.y = vecNegTra.y;
				_rVecOut.z = 0.0f;
			}
		}

		if (vecSigPos.z < fMinSignificance)
		{
			fMinSignificance = vecSigPos.z;
			_rVecOut.x = 0.0f;
			_rVecOut.y = 0.0f;
			_rVecOut.z = vecPosTra.z;
		}

		if (vecSigNeg.z < fMinSignificance)
		{
			fMinSignificance = vecSigNeg.z;
			_rVecOut.x = 0.0f;
			_rVecOut.y = 0.0f;
			_rVecOut.z = vecNegTra.z;
		}
	}

	/**
	*
	* Returns true if the line is intersecting the sphere.
	* Assumes the sphere is at the origin, and the line is relative to the sphere.
	*
	* @author Jade Abbott
	* @param _rkVecRelLineStart Start of the line, relative to the sphere.
	* @param _rkVecRelLineEnd End of the line, relative to the sphere.
	* @param _fSphereRadius Radius of the sphere.
	* @return true if the line and sphere are intersecting.
	*
	*/
	bool IsLineSphereIntersecting(const D3DXVECTOR3& _rkVecRelLineStart,
								  const D3DXVECTOR3& _rkVecRelLineEnd,
								  float _fSphereRadius)
	{
		const float kfSphereRadiusSq = _fSphereRadius * _fSphereRadius;

		// Escape test 1: End-point is inside sphere:
		const float kfDeltaEndSq = (_rkVecRelLineEnd.x * _rkVecRelLineEnd.x) + (_rkVecRelLineEnd.y * _rkVecRelLineEnd.y) + (_rkVecRelLineEnd.z * _rkVecRelLineEnd.z);

		if (kfDeltaEndSq <= kfSphereRadiusSq)
		{
			return true;
		}

		// Escape test 2: Start-point is inside sphere:
		const float kfDeltaStartSq = (_rkVecRelLineStart.x * _rkVecRelLineStart.x) + (_rkVecRelLineStart.y * _rkVecRelLineStart.y) + (_rkVecRelLineStart.z * _rkVecRelLineStart.z);

		if (kfDeltaStartSq <= kfSphereRadiusSq)
		{
			return true;
		}

		D3DXVECTOR3 vecLine = _rkVecRelLineEnd - _rkVecRelLineStart;

		float fA = (vecLine.x * vecLine.x) + (vecLine.y * vecLine.y) + (vecLine.z * vecLine.z);
		vecLine *= 2.0f;
		float fB = (vecLine.x * _rkVecRelLineStart.x) + (vecLine.y * _rkVecRelLineStart.y) + (vecLine.z * _rkVecRelLineStart.z);
		float fC = ((_rkVecRelLineStart.x * _rkVecRelLineStart.x) + (_rkVecRelLineStart.y * _rkVecRelLineStart.y) + (_rkVecRelLineStart.z * _rkVecRelLineStart.z)) - kfSphereRadiusSq;

		float fRootVal = (fB*fB) - (4.0f*(fA*fC));	// Not squared.

		if (fRootVal < 0.0f)	// Less than zero if no intersect.
		{
			return false;
		}

		fRootVal = sqrtf(fRootVal);
		fA = 1.0f / (fA + fA);	// Multiply this against (-b +- sqrt(b2 - 4(ac))).

		const float kfFirstIntersect = (-fB - fRootVal) * fA;
		const float kfLastIntersect = (-fB + fRootVal) * fA;

		return (kfFirstIntersect <= 1.0f && kfFirstIntersect >= 0.0f) || (kfLastIntersect <= 1.0f && kfLastIntersect >= 0.0f);
	}

	/**
	*
	* Returns the time of intersections for the line and sphere provided.
	* This function assumes there is an intersection (use IsLineSphereIntersecting() if not sure).
	*
	* @author Jade Abbott
	* @param _rkVecRelLineStart Start of the line, relative to the sphere.
	* @param _rkVecRelLineEnd End of the line, relative to the sphere.
	* @param _fSphereRadius Radius of the sphere.
	* @param _pTimeFirstIntersect float pointer to store the time of first intersect, if needed.
	* @param _pTimeSecondIntersect float pointer to store the time of second intersect, if needed.
	* @return 
	*
	*/
	void TimeOfLineSphereIntersect(const D3DXVECTOR3& _rkVecRelLineStart,
									const D3DXVECTOR3& _rkVecRelLineEnd,
									float _fSphereRadius,
									float* _pTimeFirstIntersect,
									float* _pTimeSecondIntersect)
	{
		D3DXVECTOR3 vecLine = _rkVecRelLineEnd - _rkVecRelLineStart;

		float fA = (vecLine.x * vecLine.x) + (vecLine.y * vecLine.y) + (vecLine.z * vecLine.z);
		vecLine *= 2.0f;
		float fB = (vecLine.x * _rkVecRelLineStart.x) + (vecLine.y * _rkVecRelLineStart.y) + (vecLine.z * _rkVecRelLineStart.z);
		float fC = ((_rkVecRelLineStart.x * _rkVecRelLineStart.x) + (_rkVecRelLineStart.y * _rkVecRelLineStart.y) + (_rkVecRelLineStart.z * _rkVecRelLineStart.z)) - (_fSphereRadius * _fSphereRadius);

		assert((fB*fB) - (4.0f*(fA*fC)) >= 0.0f);

		const float kfRootValue = sqrtf((fB*fB) - (4.0f*(fA*fC)));
		const float kfDivisionValue = 1.0f / (fA + fA);

		if (_pTimeFirstIntersect)	// If caller wants the time of first intersect...
		{
			*_pTimeFirstIntersect = (-fB - kfRootValue) * kfDivisionValue;
		}

		if (_pTimeSecondIntersect)	// If caller wants the time of second intersect...
		{
			*_pTimeSecondIntersect = (-fB + kfRootValue) * kfDivisionValue;
		}
	}

	/**
	*
	* Determines whether a line is intersecting an XZ plane.
	*
	* @author Jade Abbott
	* @param _rkVecLineStart The start of the line.
	* @param _rkVecLineEnd The end of the line.
	* @param _fGroundHeight XZ plane distance from the Y axis (height).
	* @return True if the line intersects the XZ plane.
	*
	*/
	bool IsLineGroundIntersecting(const D3DXVECTOR3& _rkVecLineStart,
								  const D3DXVECTOR3& _rkVecLineEnd,
								  float _fGroundHeight)
	{
		return _rkVecLineStart.y < _fGroundHeight ? _rkVecLineEnd.y >= _fGroundHeight : _rkVecLineEnd.y < _fGroundHeight;
	}

	/**
	*
	* Returns the point where the line intersects the XZ plane.
	* Assumes there is an intersection.
	*
	* @author Jade Abbott
	* @param _rkVecLineStart The start of the line.
	* @param _rkVecLineEnd The end of the line.
	* @param _rVecIntersectionOut The point of intersect is placed here.
	* @param _fGroundHeight XZ plane distance from the Y axis (height).
	*
	*/
	void GetLineGroundIntersect(const D3DXVECTOR3& _rkVecLineStart,
								const D3DXVECTOR3& _rkVecLineEnd,
								D3DXVECTOR3& _rVecIntersectOut,
								float _fGroundHeight)
	{
		assert(_rkVecLineEnd.y - _rkVecLineStart.y);	// Using IsLineGroundIntersecting() should prevent all horizontal lines from getting through.

		_rVecIntersectOut = _rkVecLineEnd - _rkVecLineStart;	// = vecDeltaLine.

		// Produce a scalar amount from the start of the line to the end of the line, to find what time Y = _fGroundHeight.
		float fScalar = (_fGroundHeight - _rkVecLineStart.y) / (_rkVecLineEnd.y - _rkVecLineStart.y);

		// Scale _rVecIntersectOut by fScalar, then add to _rkVecLineStart to get the point of intersect.
		_rVecIntersectOut = _rkVecLineStart + (_rVecIntersectOut * fScalar);
	}

	/**
	*
	* Rotates a quaternion along the "look" vector (Z).
	*
	* @author Jade Abbott
	* @param _rQuatRot The quaternion to rotate.
	* @param _fAngle The angle to roll the quaternion by.
	* @return Void.
	*
	*/
	void
	Roll(D3DXQUATERNION& _rQuatRot, float _fAngle)
	{
		_fAngle *= 0.5f;
		_rQuatRot *= D3DXQUATERNION(((2.0f * _rQuatRot.x * _rQuatRot.z) + (2.0f * _rQuatRot.y * _rQuatRot.w)) * _fAngle,
									((2.0f * _rQuatRot.y * _rQuatRot.z) - (2.0f * _rQuatRot.x * _rQuatRot.w)) * _fAngle,
									((1.0f - (2.0f * _rQuatRot.x * _rQuatRot.x)) - (2.0f * _rQuatRot.y * _rQuatRot.y)) * _fAngle,
									1.0f);
	}

	/**
	*
	* Rotates a quaternion along the "right" vector (X).
	*
	* @author Jade Abbott
	* @param _rQuatRot The quaternion to rotate.
	* @param _fAngle The angle to pitch the quaternion by.
	* @return Void.
	*
	*/
	void
	Pitch(D3DXQUATERNION& _rQuatRot, float _fAngle)
	{
		_fAngle *= 0.5f;
		_rQuatRot *= D3DXQUATERNION(((1.0f - (2.0f * _rQuatRot.y * _rQuatRot.y)) - (2.0f * _rQuatRot.z * _rQuatRot.z)) * _fAngle,
									((2.0f * _rQuatRot.x * _rQuatRot.y) + (2.0f * _rQuatRot.z * _rQuatRot.w)) * _fAngle,
									((2.0f * _rQuatRot.x * _rQuatRot.z) - (2.0f * _rQuatRot.y * _rQuatRot.w)) * _fAngle,
									1.0f);
	}

	/**
	*
	* Rotates a quaternion along the "up" vector (Y).
	*
	* @author Jade Abbott
	* @param _rQuatRot The quaternion to rotate.
	* @param _fAngle The angle to yaw the quaternion by.
	* @return Void.
	*
	*/
	void
	Yaw(D3DXQUATERNION& _rQuatRot, float _fAngle)
	{
		_fAngle *= 0.5f;
		_rQuatRot *= D3DXQUATERNION(((2.0f * _rQuatRot.x * _rQuatRot.y) - (2.0f * _rQuatRot.z * _rQuatRot.w)) * _fAngle,
									((1.0f - (2.0f * _rQuatRot.x * _rQuatRot.x)) - (2.0f * _rQuatRot.z * _rQuatRot.z)) * _fAngle,
									((2.0f * _rQuatRot.y * _rQuatRot.z) + (2.0f * _rQuatRot.x * _rQuatRot.w)) * _fAngle,
									1.0f);
	}

	/**
	*
	* Moves a point along the "right" vector (X) defined by a quaternion, by a provided amount.
	*
	* @author Jade Abbott
	* @param _krQuatRot The quaternion that defines the direction of movement.
	* @param _rVecPos The point that will be moved.
	* @param _fDistance The amount the point will be moved by.
	* @return Void.
	*
	*/
	void
	Strafe(const D3DXQUATERNION& _krQuatRot, D3DXVECTOR3& _rVecPos, float _fDistance)
	{
		_rVecPos.x += ((1.0f - (2.0f * _krQuatRot.y * _krQuatRot.y)) - (2.0f * _krQuatRot.z * _krQuatRot.z)) * _fDistance;
		_rVecPos.y += ((2.0f * _krQuatRot.x * _krQuatRot.y) + (2.0f * _krQuatRot.z * _krQuatRot.w)) * _fDistance;
		_rVecPos.z += ((2.0f * _krQuatRot.x * _krQuatRot.z) - (2.0f * _krQuatRot.y * _krQuatRot.w)) * _fDistance;
	}

	/**
	*
	* Moves a point along the "up" vector (Y) defined by a quaternion, by a provided amount.
	*
	* @author Jade Abbott
	* @param _krQuatRot The quaternion that defines the direction of movement.
	* @param _rVecPos The point that will be moved.
	* @param _fDistance The amount the point will be moved by.
	* @return Void.
	*
	*/
	void
	Fly(const D3DXQUATERNION& _krQuatRot, D3DXVECTOR3& _rVecPos, float _fDistance)
	{
		_rVecPos.x += ((2.0f * _krQuatRot.x * _krQuatRot.y) - (2.0f * _krQuatRot.z * _krQuatRot.w)) * _fDistance;
		_rVecPos.y += ((1.0f - (2.0f * _krQuatRot.x * _krQuatRot.x)) - (2.0f * _krQuatRot.z * _krQuatRot.z)) * _fDistance;
		_rVecPos.z += ((2.0f * _krQuatRot.y * _krQuatRot.z) + (2.0f * _krQuatRot.x * _krQuatRot.w)) * _fDistance;
	}

	/**
	*
	* Moves a point along the "look" vector (Z) defined by a quaternion, by a provided amount.
	*
	* @author Jade Abbott
	* @param _krQuatRot The quaternion that defines the direction of movement.
	* @param _rVecPos The point that will be moved.
	* @param _fDistance The amount the point will be moved by.
	* @return Void.
	*
	*/
	void
	Move(const D3DXQUATERNION& _krQuatRot, D3DXVECTOR3& _rVecPos, float _fDistance)
	{
		_rVecPos.x += ((2.0f * _krQuatRot.x * _krQuatRot.z) + (2.0f * _krQuatRot.y * _krQuatRot.w)) * _fDistance;
		_rVecPos.y += ((2.0f * _krQuatRot.y * _krQuatRot.z) - (2.0f * _krQuatRot.x * _krQuatRot.w)) * _fDistance;
		_rVecPos.z += ((1.0f - (2.0f * _krQuatRot.x * _krQuatRot.x)) - (2.0f * _krQuatRot.y * _krQuatRot.y)) * _fDistance;
	}

	/**
	*
	* Calculates the radius of a bounding sphere for a given mesh.
	* This function assumes the first 12 bytes of each vertex defines the position.
	*
	* @author Jade Abbott
	* @param _rSphereRadius The radius of the sphere, once the function completes.
	* @param _pVertices Pointer to the first vertex in an array of vertices to be checked.
	* @param _uiVertexStride Size of each vertex, for iterating through the array.
	* @param _uiNumVertices The number of vertices in the array.
	* @return Void.
	*
	*/
	void
	CalculateBoundingSphere(float& _rSphereRadius, void* _pVertices, unsigned int _uiVertexStride, unsigned int _uiNumVertices)
	{
		_rSphereRadius = -MathUtility::kMaxFloat;

		for (unsigned int ui = 0; ui < _uiNumVertices; ++ui)
		{
			D3DXVECTOR3* pVertex = reinterpret_cast<D3DXVECTOR3*>(reinterpret_cast<BYTE*>(_pVertices) + (ui * _uiVertexStride));

			float fLengthSq = (pVertex->x * pVertex->x) + (pVertex->y * pVertex->y) + (pVertex->z * pVertex->z);

			_rSphereRadius = _rSphereRadius > fLengthSq ? _rSphereRadius : fLengthSq;
		}

		_rSphereRadius = sqrtf(_rSphereRadius);
	}

	/**
	*
	* Specifically for bump-mapping, this returns a colour value based on the angle of the normalised vector provided.
	*
	* @author Jade Abbott
	* @param _rkVecNorm The normalised vector that will be converted into a colour.
	* @return DWORD defining the 256 colour value of the vector. Is in the form 0xAARRGGBB where alpha = 0xFF.
	*
	*/
	DWORD
	VectorToRGB(const D3DXVECTOR3& _rkVecNorm)
	{
		DWORD dwRed		= static_cast<DWORD>(127 * _rkVecNorm.x + 128);
		DWORD dwGreen	= static_cast<DWORD>(127 * _rkVecNorm.y + 128);
		DWORD dwBlue	= static_cast<DWORD>(127 * _rkVecNorm.z + 128);
		return static_cast<DWORD>(0xff000000 + (dwRed << 16) + (dwGreen << 8) + dwBlue);
	}

	/**
	*
	* Converts scalar float values into a 256 colour DWORD.
	*
	* @author Jade Abbott
	* @param _fRed Red intensity scale from zero to one.
	* @param _fGreen Greenintensity scale from zero to one.
	* @param _fBlue Blue intensity scale from zero to one.
	* @return D3DCOLOR (DWORD) defining the 8-bit XRGB colour value. Is in the form 0xAARRGGBB where alpha = 0xFF.
	*
	*/
	D3DCOLOR
	ColourScaleToRGB(float _fRed, float _fGreen, float _fBlue)
	{
		return D3DCOLOR_XRGB(static_cast<DWORD>(255 * _fRed),
							 static_cast<DWORD>(255 * _fGreen),
							 static_cast<DWORD>(255 * _fBlue));

	}








	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function generates a random number between the min and max number
	*
	* @author Bryce Booth
	* @param  _iMin	The lowest the random number can be
	* @param  _iMax	The highest the random can be
	* @return int	The randomly generated number
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	unsigned int RandomNumber(int _iMin , int _iMax)
	{
		assert(_iMax >= _iMin); // Invalid (besides, can't modulus a negative number).
		return (rand() % ((_iMax + 1) - _iMin)) + _iMin;
	}








	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function generates a random number between the min and max number
	*
	* @author Bryce Booth
	* @param  _fMin	The lowest the random number can be
	* @param  _fMax	The highest the random can be
	* @return float	The randomly generated number
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	float
	RandomNumber(float _fMin, float _fMax)
	{
		assert(_fMax >= _fMin); // Invalid (besides, can't modulus a negative number).
		return _fMin + (((rand() % 20000) * 0.00005f) * (_fMax - _fMin));
	}








	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	void
	PointRotation(float _fCenterX, float _fCenterY, float _fPointX, float _fPointY,
				  float _fRotationAmount, float& _frNewPointX, float& _frNewPointY)
	{
		// Get the difference between the two points
		float fDifferenceX = _fPointX - _fCenterX;
		float fDifferenceY = _fPointY - _fCenterY;
		
		// Get the distance between the two points
		float fHypotenuse = sqrt( pow(fDifferenceX, 2.0f) + pow(fDifferenceY, 2.0f) );

		// Calculate angle
		float fAngle = atan(fDifferenceY / fDifferenceX);

		// Get quadrant
		// Quadrant 1 X Greater, Z Greater | SKIP
		if (fDifferenceX < 0 && fDifferenceY > 0) // X Smaller, Z Greater
		{
			// Quadrant 2
			fAngle = 3.1415f + fAngle;
		}
		else if (fDifferenceX < 0 && fDifferenceY < 0) // X Smaller, Z Smaller
		{
			// Quadrant 3
			fAngle = 3.1415f + fAngle;

		}
		else if (fDifferenceX > 0 && fDifferenceY < 0) // X Greater, Z Smaller
		{
			// Quadrant 4
			fAngle = 6.2831f + fAngle;
		}
		else
		{
			//LOG_FATALERROR(false, "Unknown quadrant.");
		}

		// Add rotation amount to angle
		fAngle += _fRotationAmount;

		if (fAngle > 6.2831f)
		{
			// Gone over 360 degrees
			fAngle -= 6.2831f;
		}

		// Calculate final new point position
		_frNewPointX = cos(fAngle) * fHypotenuse;
		_frNewPointY = sin(fAngle) * fHypotenuse;

		_frNewPointX += _fCenterX;
		_frNewPointY += _fCenterY;
	}








	/*---------------------------------------------------------------------------------------------------------------------------
	*
	* This function
	*
	* @author Bryce Booth
	*
	*---------------------------------------------------------------------------------------------------------------------------*/

	void
	CalculatePointAngle(float _fPointX, float _fPointY, float& _frRadianAngle)
	{
		// Calculate angle
		float fAngle = atan(_fPointY / _fPointX);

		// Get quadrant
		// Quadrant 1 X Greater, Z Greater | SKIP
		if (_fPointX < 0 && _fPointY > 0) // X Smaller, Z Greater
		{
			// Quadrant 1
			fAngle = 1.57079633f + fAngle;
		}
		else if (_fPointX < 0 && _fPointY < 0) // X Smaller, Z Smaller
		{
			// Quadrant 2
			fAngle = 1.57079633f + fAngle;

		}
		else if (_fPointX > 0 && _fPointY < 0) // X Greater, Z Smaller
		{
			// Quadrant 3
			fAngle = 4.71238898f + fAngle;
		}
		else if (_fPointX > 0 && _fPointY > 0)  // X Greater, Z Greater
		{
			// Quadrant 4
			fAngle = 4.71238898f + fAngle;
		}
		else
		{
			LOG_FATALERROR(false, "Unknown quadrant.");
		}

		if (fAngle > 6.2831f)
		{
			// Gone over 360 degrees
			fAngle -= 6.2831f;
		}

		_frRadianAngle = fAngle;
	}
}