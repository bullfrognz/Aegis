//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   EffectTargets.inl
//  Description :  
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the poison timer.
*
* @author Bryce Booth
* @return m_fPoisonTimer  Time remaining for the poison effect.
*
*---------------------------------------------------------------------------------------------------------------------------*/

float
CEffectTarget::GetPoisonTimer() const
{
	return (m_fPoisonTimer);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the frost timer.
*
* @author Bryce Booth
* @return m_fPoisonTimer  Time remaining for the frost effect.
*
*---------------------------------------------------------------------------------------------------------------------------*/

float
CEffectTarget::GetFrostTimer() const
{
	return (m_fFrostTimer);
}