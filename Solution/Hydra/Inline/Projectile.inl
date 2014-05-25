//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Projectile.inl
//  Description :  
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will return the effects that the projectile has.
*
* @author Bryce Booth
* @return m_uiEffects	Effects the projectile has
*
*---------------------------------------------------------------------------------------------------------------------------*/

unsigned int
CProjectile::GetEffects() const
{
	return (m_uiEffects);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will return the active state of the projectile.
*
* @author Bryce Booth
* @return bool		The projectiles active state.
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CProjectile::IsActive() const
{
	return (m_bActive);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will return the maxium life span of all projectiles.
*
* @author Bryce Booth
* @return float		The maxium life span time
*
*---------------------------------------------------------------------------------------------------------------------------*/

float
CProjectile::GetMaxiumLifeSpan()
{
	return (4.0f);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will return the tracking update time interval of all projectiles.
*
* @author Bryce Booth
* @return float		Time between tracking updates
*
*---------------------------------------------------------------------------------------------------------------------------*/

float
CProjectile::GetTrackingUpdateInverval()
{
	return (0.1f);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will return the minimum movement velocity of all projectiles.
*
* @author Bryce Booth
* @return float		Minimum projectile movement velocity
*
*---------------------------------------------------------------------------------------------------------------------------*/

float
CProjectile::GetMinMovementVelocity()
{
	return (0.1f);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will return the maximum velocity of all projectiles.
*
* @author Bryce Booth
* @return float		Maximum projectile movement velocity
*
*---------------------------------------------------------------------------------------------------------------------------*/

float
CProjectile::GetMaxMovementVelocity()
{
	return (4000.0f);
}