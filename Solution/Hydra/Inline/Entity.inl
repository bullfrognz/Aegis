//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Entity.inl
//  Description :  
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


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
CEntity::SetTrackingEntity(CEntity* _pEntity)
{
	m_pTrackingEntity = _pEntity;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CWorldMatrix&
CEntity::GetWorldMatrix()
{
	return (m_mtxWorldMatrix);
}





/**
*
* Returns this entity's world matrix.
* Is a const variation of the one above.
*
*/
const CWorldMatrix&
CEntity::GetWorldMatrix_s() const
{
	return m_mtxWorldMatrix;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEntity::SetRadius(float _fRadius)
{
	m_fRadius = _fRadius;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

float
CEntity::GetRadius() const
{
	return (m_fRadius);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void 
CEntity::SetTrackUpdateInverval(float _fValue)
{
	m_fTrackUpdateInterval = _fValue;
}










/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEntity::SetMovementVelocityX(float _fX)
{
	m_v3MovementVelocity.x = _fX;
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEntity::SetMovementVelocityY(float _fY)
{
	m_v3MovementVelocity.y = _fY;
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEntity::SetMovementVelocityZ(float _fZ)
{
	m_v3MovementVelocity.z = _fZ;
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEntity::SetMovementVelocity(float _fX, float _fY, float _fZ)
{
	m_v3MovementVelocity.x = _fX;
	m_v3MovementVelocity.y = _fY;
	m_v3MovementVelocity.z = _fZ;
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEntity::SetMovementVelocity(const CVector3& _kv3rVelocity)
{
	m_v3MovementVelocity = _kv3rVelocity;
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

const CVector3&
CEntity::GetMovementVelocity() const
{
	return (m_v3MovementVelocity);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEntity::SetAngularVelocityX(float _fX)
{
	m_v3AngularVelocity.x = _fX;
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEntity::SetAngularVelocityY(float _fY)
{
	m_v3AngularVelocity.y = _fY;
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEntity::SetAngularVelocityZ(float _fZ)
{
	m_v3AngularVelocity.z = _fZ;
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEntity::SetAngularVelocity(float _fX, float _fY, float _fZ)
{
	m_v3AngularVelocity.x = _fX;
	m_v3AngularVelocity.y = _fY;
	m_v3AngularVelocity.z = _fZ;
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEntity::SetAngularVelocity(const CVector3& _kv3rVelocity)
{
	m_v3AngularVelocity = _kv3rVelocity;
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

const CVector3&
CEntity::GetAngularVelocity() const
{
	return (m_v3AngularVelocity);
}