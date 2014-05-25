//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   EffectTarget.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Macros.h"


// This Include
#include "EffectTarget.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* EffectTarget class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CEffectTarget::CEffectTarget()
: m_fPoisonTimer(0)
, m_fPoisonTickDamage(0)
, m_fFrostTimer(0)
{
	//Empty
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* EffectTarget class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CEffectTarget::~CEffectTarget()
{
	Deinitialise();
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will apply the poison effect for the effect target.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEffectTarget::ApplyPoison(float _fPoisonTickDamage, float _fPoisonLength)
{
	//Set member variables
	m_fPoisonTickDamage = _fPoisonTickDamage;
	m_fPoisonTimer      = _fPoisonLength;
}







/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will apply the frost effect for the effect target.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEffectTarget::ApplyFrost(float _fFrostPenaltyRatio, float _fFrostLength)
{
	//Set member variables
	m_fFrostTimer = _fFrostLength;


	//Turn on frost effecy
	TurnOnFrostEffect(_fFrostPenaltyRatio);
}










/********************************
            Protected
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will process the frost effect by checking if the frost effect has worn off.
*
* @author Bryce Booth
* @param  _fDeltaTick	The time elasped since last process.
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEffectTarget::ProcessFrostEffect(float _fDeltaTick)
{
	//Check frost timer not negitive
	if (m_fFrostTimer > 0.0f)
	{
		//Decrement frost effect timer
		m_fFrostTimer -= _fDeltaTick;		

		//Check frost timer lower then zero
		if (m_fFrostTimer <= 0.0f)
		{
			//Turn off frost effect
			TurnOffFrostEffect();
		}
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
CEffectTarget::Deinitialise()
{
	//Empty
}