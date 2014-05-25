//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Weapon.inl
//  Description :  
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Projectile.h"


// Implementation


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CWeapon::SetDamageMultiplier(float _fMultiplier)
{
	m_fCriticalMultiplier = _fMultiplier;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the min damage of the weapon.
*
* @author Bryce Booth
* @return m_fMinDamage	Min damage of the weapon.
*
*---------------------------------------------------------------------------------------------------------------------------*/

float 
CWeapon::GetMinDamage() const
{
	return (m_fMinDamage);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the max damage of the weapon.
*
* @author Bryce Booth
* @return m_fMaxDamage	Max damage of the weapon.
*
*---------------------------------------------------------------------------------------------------------------------------*/

float 
CWeapon::GetMaxDamage() const
{
	return (m_fMaxDamage);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the effects of the weapon's projectiles.
*
* @author Bryce Booth
* @return m_fMaxDamage	Max damage of the weapon.
*
*---------------------------------------------------------------------------------------------------------------------------*/

unsigned int
CWeapon::GetProjectileEffects() const
{
	if (m_pProjectiles)
	{
		return (m_pProjectiles[0].GetEffects());
	}
	else
	{
		return (0);
	}
}