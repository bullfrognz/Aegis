//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   EnemyManager.inl
//  Description :  
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the container of the enemy instances
*
* @author Bryce Booth
* @return s_vecEnemies	Container of enemies
*
*---------------------------------------------------------------------------------------------------------------------------*/

std::vector<CEnemy*>&
CEnemySpawner::GetEnemyInstances()
{
	return (s_vecEnemies);
}