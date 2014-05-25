//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Entity.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_ENTITY_H__
#define __IGFEB11_IG500_ENTITY_H__


// Library Includes


// Local Includes
#include "WorldMatrix.h"
#include "Vector3.h"


// Types
typedef char* EntityName;


// Constants
enum EAxis
{
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
};


// Prototypes
class CD3DRenderer;


class CEntity
{

	// Member Functions
public:


	         CEntity();
	virtual ~CEntity();


	virtual bool Initialise(char* _cpEntityName);
	virtual void Process(float _fDeltaTick);


	//Rotation
	void RotateX(float _fRadianAngle);
	void RotateY(float _fRadianAngle);
	void RotateZ(float _fRadianAngle);


	//Copy
	void CopyPosition(CEntity* _pEntity);
	void CopyOrientation(CEntity* _pEntity);


	//Math
	void  LookAt(const CVector3& _kv3rTargetPosition);
	float GetSquaredDistanceTo(CEntity* _pTargetEntity);
	float GetSquaredDistanceTo(const CVector3& _kv3pTargetPosition);
	float GetSquaredRadius() const;
	bool  IsCollidingWith(CEntity* _pTargetEntity);
	void  LerpPosition(CVector3 _v3TargetPosition, float _fDuration);
	void  LerpRotation(float _fRadianAmoutn, float _fDuration, EAxis _eAxis);
	bool  IsLerpingInProgress();


	// Inline Functions


	inline void SetTrackingEntity(CEntity* _pEntity);
	inline CWorldMatrix& GetWorldMatrix();
	inline const CWorldMatrix& GetWorldMatrix_s() const;
	inline void  SetRadius(float _fRadius);
	inline float GetRadius() const;
	inline void  SetTrackUpdateInverval(float _fValue);


	//Movement Velocity
	inline void SetMovementVelocityX(float _fX);
	inline void SetMovementVelocityY(float _fY);
	inline void SetMovementVelocityZ(float _fZ);
	inline void SetMovementVelocity(float _fX, float _fY, float _fZ);
	inline void SetMovementVelocity(const CVector3& _kv3rVelocity);


	inline const CVector3& GetMovementVelocity() const;


	//Angular Velocity
	inline void SetAngularVelocityX(float _fX);
	inline void SetAngularVelocityY(float _fY);
	inline void SetAngularVelocityZ(float _fZ);
	inline void SetAngularVelocity(float _fX, float _fY, float _fZ);
	inline void SetAngularVelocity(const CVector3& _kv3rVelocity);


	inline const CVector3& GetAngularVelocity() const;


protected:


	void ProcessAngularVelocity(float _fDeltaTick);
	void ProcessMovementVelocity(float _fDeltaTick);
	void ProcessTrackEntity(float _fDeltaTick);
	void ProcessLerpPosition(float _fDeltaTick);
	void ProcessLerpRotation(float _fDeltaTick);


private:


	void Deinitialise();


	CEntity(const CEntity& _krEntity);
	CEntity& operator = (const CEntity& _krEntity);


	// Member Variables
protected:


	CWorldMatrix m_mtxWorldMatrix;


	CVector3 m_v3MovementVelocity;
	CVector3 m_v3AngularVelocity;


	CEntity* m_pTrackingEntity;


	char* m_cpEntityName;


	float m_fRadius;
	float m_fTrackUpdateInterval;
	float m_fTrackUpdateElapsed;


	bool m_bProcessingPaused;


private:


	CVector3 m_v3LerpStartPosition;
	CVector3 m_v3LerpEndPosition;
	

	float m_fLerpPositionTimer;
	float m_fLerpPositionDuration;


	float m_fLerpRotationTimer;
	float m_fLerpRotationDuration;
	float m_fLerpRotationRadians;


	EAxis m_eLerpRotationAxis;


};


#include "Inline/Entity.inl"


#endif //__IGFEB11_IG500_ENTITY_H__