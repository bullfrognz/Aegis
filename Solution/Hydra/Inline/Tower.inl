//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Tower.inl
//  Description :  
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation



/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will return the next upgrade tower type
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

unsigned int
CTower::GetBuildCost() const
{
	return (m_uiBuildCost);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will return the next upgrade tower type.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

std::vector<char*>&
CTower::GetTowerUpgradeTypes()
{
	return (m_vecUpgradeTowerTypes);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will return the next upgrade tower type.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

const char*
CTower::GetTowerType() const
{
	return (m_kcpTowerType);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the number of max targets the tower can have.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

unsigned int
CTower::GetMaxTargets() const
{
	return (m_uiMaxTargets);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the abilitys that the tower has.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

unsigned int 
CTower::GetAbilitys() const
{
	return (m_pWeapon->GetProjectileEffects());
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the max damage of the tower.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

float
CTower::GetMaxDamage() const
{
	return (m_pWeapon->GetMaxDamage());
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the min damage of the tower.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

float
CTower::GetMinDamage() const
{
	return (m_pWeapon->GetMinDamage());
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the range of the tower.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

float
CTower::GetRange() const
{
	return (m_fRange);
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the fire rate of the tower.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

float
CTower::GetFireRate() const
{
	return (m_fFireRate);
}
