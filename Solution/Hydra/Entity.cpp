//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   Entity.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Macros.h"
#include "StrUtilities.h"


// This Include
#include "Entity.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Entity class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CEntity::CEntity()
: m_pTrackingEntity(0)
, m_cpEntityName(0)
, m_fRadius(0)
, m_fTrackUpdateElapsed(0)
, m_fTrackUpdateInterval(0)
, m_bProcessingPaused(false)
, m_fLerpPositionTimer(0)
, m_fLerpPositionDuration(0)
, m_fLerpRotationTimer(0)
, m_fLerpRotationDuration(0)
, m_fLerpRotationRadians(0)
{
	//Empty
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Entity class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CEntity::~CEntity()
{
	Deinitialise();
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function initialisings the class instance before use.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CEntity::Initialise(char* _cpEntityName)
{
	// Set member variables
	StrUtilities::Copy(_cpEntityName, m_cpEntityName);


	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEntity::Process(float _fDeltaTick)
{
	if (m_bProcessingPaused == false)
	{
		ProcessAngularVelocity(_fDeltaTick);


		ProcessMovementVelocity(_fDeltaTick);


		if(m_pTrackingEntity != 0)
		{
			ProcessTrackEntity(_fDeltaTick);
		}


		if (m_fLerpPositionTimer > 0.0f)
		{
			ProcessLerpPosition(_fDeltaTick);
		}


		if (m_fLerpRotationTimer > 0.0f)
		{
			ProcessLerpRotation(_fDeltaTick);
		}
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
CEntity::RotateX(float _fRadianAngle)
{
	//Set default variables
	D3DXQUATERNION quatPitch;
	D3DXQUATERNION quatPitchConjugate;
	D3DXQUATERNION quatPitchResult;
	D3DXQUATERNION quatForward;
	CVector3 v3OrientationX;
	CVector3 v3OrientationZ;


	//Get orientation from world matrix
	m_mtxWorldMatrix.GetOrientationX(v3OrientationX);
	m_mtxWorldMatrix.GetOrientationZ(v3OrientationZ);


	//Calculate quaternion rotation axis
	D3DXQuaternionRotationAxis(&quatPitch, &v3OrientationX, _fRadianAngle);


	//Calculate quaternion pitch conjugate
	D3DXQuaternionConjugate(&quatPitchConjugate, &quatPitch);


	//Copy orientation Z
	quatForward.x = v3OrientationZ.x;
	quatForward.y = v3OrientationZ.y;
	quatForward.z = v3OrientationZ.z;
	quatForward.w = 0.0f;


	//Calculate quaternion pitch result
	D3DXQuaternionMultiply(&quatPitchResult, &quatPitch, &quatForward);
	D3DXQuaternionMultiply(&quatPitchResult, &quatPitchResult, &quatPitchConjugate);
	

	//Set new orientation Z
	v3OrientationZ = quatPitchResult;
	

	//Set world matrix new orientation Y
	m_mtxWorldMatrix.SetOrientationY(v3OrientationZ, v3OrientationX);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEntity::RotateY(float _fRadianAngle)
{
	//Set default variables
	D3DXQUATERNION quatYaw;
	D3DXQUATERNION quatYawConjugate;
	D3DXQUATERNION quatYawResult;
	D3DXQUATERNION quatForward;
	CVector3 v3OrientationY;
	CVector3 v3OrientationZ;


	//Get orientation from world matrix
	m_mtxWorldMatrix.GetOrientationY(v3OrientationY);
	m_mtxWorldMatrix.GetOrientationZ(v3OrientationZ);


	//Calculate quaternion rotation axis
	D3DXQuaternionRotationAxis(&quatYaw, &v3OrientationY, _fRadianAngle);


	//Calculate quaternion yaw conjugate
	D3DXQuaternionConjugate(&quatYawConjugate, &quatYaw);


	//Copy orientation Z
	quatForward.x = v3OrientationZ.x;
	quatForward.y = v3OrientationZ.y;
	quatForward.z = v3OrientationZ.z;
	quatForward.w = 0.0f;


	//Calculate quaternion yaw result
	D3DXQuaternionMultiply(&quatYawResult, &quatYaw, &quatForward);
	D3DXQuaternionMultiply(&quatYawResult, &quatYawResult, &quatYawConjugate);
	

	//Set new orientation Z
	v3OrientationZ = quatYawResult;
	

	//Set world matrix new orientation X
	m_mtxWorldMatrix.SetOrientationX(v3OrientationY, v3OrientationZ);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEntity::RotateZ(float _fRadianAngle)
{
	//Set default variables
	D3DXQUATERNION quatRoll;
	D3DXQUATERNION quatRollConjugate;
	D3DXQUATERNION quatRollResult;
	D3DXQUATERNION quatUp;
	CVector3 v3OrientationZ;
	CVector3 v3OrientationY;


	//Get orientation from world matrix
	m_mtxWorldMatrix.GetOrientationZ(v3OrientationZ);
	m_mtxWorldMatrix.GetOrientationY(v3OrientationY);


	//Calculate quaternion rotation axis
	D3DXQuaternionRotationAxis(&quatRoll, &v3OrientationZ, _fRadianAngle);


	//Calculate quaternion roll conjugate
	D3DXQuaternionConjugate(&quatRollConjugate, &quatRoll);


	//Copy orientation Z
	quatUp.x = v3OrientationY.x;
	quatUp.y = v3OrientationY.y;
	quatUp.z = v3OrientationY.z;
	quatUp.w = 0.0f;


	//Calculate quaternion roll result
	D3DXQuaternionMultiply(&quatRollResult, &quatRoll, &quatUp);
	D3DXQuaternionMultiply(&quatRollResult, &quatRollResult, &quatRollConjugate);
	

	//Set new orientation Z
	v3OrientationY = quatRollResult;
	

	//Set world matrix new orientation X
	m_mtxWorldMatrix.SetOrientationX(v3OrientationY, v3OrientationZ);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void 
CEntity::CopyPosition(CEntity* _pEntity)
{
	//Setup default variables
	CVector3 v3Position;


	//Get entity position
	_pEntity->GetWorldMatrix().GetPosition(v3Position);


	//Set self position
	m_mtxWorldMatrix.SetPosition(v3Position);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void 
CEntity::CopyOrientation(CEntity* _pEntity)
{
	//Setup default variables
	CVector3 v3OrientationX;
	CVector3 v3OrientationY;
	CVector3 v3OrientationZ;


	//Get entity position
	_pEntity->GetWorldMatrix().GetOrientationX(v3OrientationX);
	_pEntity->GetWorldMatrix().GetOrientationY(v3OrientationY);
	_pEntity->GetWorldMatrix().GetOrientationZ(v3OrientationZ);


	//Set self position
	m_mtxWorldMatrix.SetOrientation(v3OrientationX, v3OrientationY, v3OrientationZ);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEntity::LookAt(const CVector3& _kv3rTargetPosition)
{
	//Set default variables
	CVector3 v3SelfPosition;
	CVector3 v3SelfOrientationY;
	CVector3 v3SelfOrientationZ;
	CVector3 v3TargetPosition;
	CWorldMatrix mtxLookAt;


	//Get self position
	m_mtxWorldMatrix.GetPosition(v3SelfPosition);


	//Calculate new direction
	D3DXMatrixLookAtLH(&mtxLookAt, &v3SelfPosition, &_kv3rTargetPosition, &CVector3(0,1,0));


	//Convert from view to world matrix
	mtxLookAt.Inverse();


	//Set new world matrix
	m_mtxWorldMatrix = mtxLookAt;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

float 
CEntity::GetSquaredDistanceTo(CEntity* _pTargetEntity)
{
	//Set default variables
	float fTargetSquaredRadius = _pTargetEntity->GetSquaredRadius();
	CVector3 v3TargetPosition;
	_pTargetEntity->GetWorldMatrix().GetPosition(v3TargetPosition);


	//Calculate squared distance
	float fSquaredDistance = 0.0f;


	fSquaredDistance = GetSquaredDistanceTo(v3TargetPosition);


	//Minus radius from distance
	fSquaredDistance -= fTargetSquaredRadius;


	return (fSquaredDistance);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

float
CEntity::GetSquaredDistanceTo(const CVector3& _kv3pTargetPosition)
{
	//Set default variables
	float fSelfSquaredRadius = CEntity::m_fRadius;
	CVector3 v3SelfPosition;
	CEntity::m_mtxWorldMatrix.GetPosition(v3SelfPosition);


	//Calculate difference in position
	CVector3 v3PositionDifference;

	v3PositionDifference  = _kv3pTargetPosition;
	v3PositionDifference -= v3SelfPosition;


	//Convert to squared space
	v3PositionDifference.x *= v3PositionDifference.x;
	v3PositionDifference.y *= v3PositionDifference.y;
	v3PositionDifference.z *= v3PositionDifference.z;


	//Calculate squared distance
	float fSquaredDistance = 0.0f;

	fSquaredDistance  = v3PositionDifference.x;
	fSquaredDistance += v3PositionDifference.y;
	fSquaredDistance += v3PositionDifference.z;


	//Minus radius from distance
	fSquaredDistance -= fSelfSquaredRadius;


	return (fSquaredDistance);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

float
CEntity::GetSquaredRadius() const
{
	//Calculate squared radius
	float fSquaredRadius = 0.0f;
	fSquaredRadius  = m_fRadius;
	fSquaredRadius *= m_fRadius;


	return (fSquaredRadius);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CEntity::IsCollidingWith(CEntity* _pTargetEntity)
{
	//Set default variables
	float fSquaredDistance = GetSquaredDistanceTo(_pTargetEntity);


	//Check if colliding
	bool bColliding = (fSquaredDistance < 0.0f);


	return (bColliding);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEntity::LerpPosition(CVector3 _v3TargetPosition, float _fDuration)
{
	//Check previous lerp still active
	if (m_fLerpPositionTimer > 0.0f)
	{
		//Process the remaining lerp
		ProcessLerpPosition(m_fLerpPositionTimer);
	}


	//Set lerp start position
	m_mtxWorldMatrix.GetPosition(m_v3LerpStartPosition);


	//Set end position
	m_v3LerpEndPosition = _v3TargetPosition;


	//Set lerp duration
	m_fLerpPositionDuration = _fDuration;
	m_fLerpPositionTimer    = _fDuration;
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEntity::LerpRotation(float _fRadianAmount, float _fDuration, EAxis _eAxis)
{
	//Check previous lerp still active
	if (m_fLerpRotationTimer > 0.0f)
	{
		//Process the remaining lerp
		ProcessLerpRotation(m_fLerpRotationTimer);
	}


	//Set member variables
	m_fLerpRotationRadians  = _fRadianAmount;
	m_fLerpRotationDuration = _fDuration;
	m_fLerpRotationTimer    = m_fLerpRotationDuration;
	m_eLerpRotationAxis     = _eAxis;
}


bool
CEntity::IsLerpingInProgress()
{
	bool bLerpInProcess = false;


	if (m_fLerpRotationTimer > 0.0f)
	{
		bLerpInProcess = true;
	}
	else if (m_fLerpPositionTimer > 0.0f)
	{
		bLerpInProcess = true;
	}
	else
	{
		bLerpInProcess = false;
	}


	return (bLerpInProcess);
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
CEntity::ProcessAngularVelocity(float _fDeltaTick)
{
	if (m_v3AngularVelocity.x != 0.0f)
	{
		RotateX(m_v3AngularVelocity.x * _fDeltaTick);
	}


	if (m_v3AngularVelocity.y != 0.0f)
	{
		RotateY(m_v3AngularVelocity.y * _fDeltaTick);
	}


	if (m_v3AngularVelocity.z != 0.0f)
	{
		RotateZ(m_v3AngularVelocity.z * _fDeltaTick);
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
CEntity::ProcessMovementVelocity(float _fDeltaTick)
{
	//Set default variables
	CVector3 v3TotalTranslation;
	CVector3 v3TranslationX;
	CVector3 v3TranslationY;
	CVector3 v3TranslationZ;


	//Check movement velocity on X axis not zero
	if (m_v3MovementVelocity.x != 0.0f)
	{
		//Retrieve orientation X
		m_mtxWorldMatrix.GetOrientationX(v3TranslationX);


		//Calculate X translation
		v3TranslationX *= m_v3MovementVelocity.x;
		v3TranslationX *= _fDeltaTick;


		//Add X translateion to total translation
		v3TotalTranslation += v3TranslationX;
	}

	
	//Check movement velocity on Y axis not zero
	if (m_v3MovementVelocity.y != 0.0f)
	{
		//Retrieve orientation Y
		m_mtxWorldMatrix.GetOrientationY(v3TranslationY);


		//Calculate Y translation
		v3TranslationY *= m_v3MovementVelocity.y;
		v3TranslationY *= _fDeltaTick;

	
		//Add Y translateion to total translation
		v3TotalTranslation += v3TranslationY;
	}


	//Check movement velocity on Z axis not zero
	if (m_v3MovementVelocity.z != 0.0f)
	{
		//Retrieve orientation Z
		m_mtxWorldMatrix.GetOrientationZ(v3TranslationZ);


		//Calculate Z translation
		v3TranslationZ *= m_v3MovementVelocity.z;
		v3TranslationZ *= _fDeltaTick;


		//Add Z translateion to total translation
		v3TotalTranslation += v3TranslationZ;
	}


	//Check total translation is not zero
	if (v3TotalTranslation.IsZero() == false)
	{
		//Translate world position
		m_mtxWorldMatrix.TranslatePosition(v3TotalTranslation);
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
CEntity::ProcessTrackEntity(float _fDeltaTick)
{
	//Increment tracking interval timer
	m_fTrackUpdateElapsed += _fDeltaTick;


	if (m_fTrackUpdateElapsed >= m_fTrackUpdateInterval)
	{
		//Get target position
		CVector3 v3TargetPosition;
		m_pTrackingEntity->GetWorldMatrix().GetPosition(v3TargetPosition);


		LookAt(v3TargetPosition);


		m_fTrackUpdateElapsed = 0.0f;
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
CEntity::ProcessLerpPosition(float _fDeltaTick)
{
	//Setup default variables
	CVector3 v3NewPosition;


	//Decrement lerp timer
	m_fLerpPositionTimer -= _fDeltaTick;

	
	float fScaler = 0.0f;


	if (m_fLerpPositionTimer < 0.0f)
	{
		m_fLerpPositionTimer = 0.0f;
	}
	else
	{
		//Calculate lerp scaler
		fScaler = m_fLerpPositionTimer / m_fLerpPositionDuration;
	}
	

	//Calculate lerp
	D3DXVec3Lerp(&v3NewPosition, &m_v3LerpEndPosition, &m_v3LerpStartPosition, fScaler);


	//Set new position
	m_mtxWorldMatrix.SetPosition(v3NewPosition);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEntity::ProcessLerpRotation(float _fDeltaTick)
{
	//Decrement lerp timer
	m_fLerpRotationTimer -= _fDeltaTick;


	//Calculate lerp scaler
	float fScaler = m_fLerpRotationTimer / m_fLerpRotationDuration;


	float fRadiansPerSec = m_fLerpRotationRadians / m_fLerpRotationDuration;


	float fMovementAmount = m_fLerpRotationTimer - _fDeltaTick;

	
	float fRadians = 0.0f;


	if (m_fLerpRotationTimer > 0.0f)
	{
		fRadians = fRadiansPerSec * _fDeltaTick;
	}
	else
	{
		fRadians = fRadiansPerSec * (_fDeltaTick + m_fLerpRotationTimer);
	}


	switch (m_eLerpRotationAxis)
	{
	case AXIS_X:
		RotateX(fRadians);
		break;

	case AXIS_Y:
		RotateY(fRadians);
		break;

	case AXIS_Z:
		RotateZ(fRadians);
		break;
	}
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
CEntity::Deinitialise()
{
	delete[] m_cpEntityName;
	m_cpEntityName = 0;
}