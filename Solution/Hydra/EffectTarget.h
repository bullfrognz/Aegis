//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   EffectTarget.h
//  Description :   Allows derived classes to be affected by effects.
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_EFFECTTARGET_H__
#define __IGFEB11_IG500_EFFECTTARGET_H__


// Library Includes


// Local Includes
#include "Utility.h"

// Types
enum EEffect
{
	EFFECTTYPE_INVALID,

	EFFECTTYPE_POISON = Utility::B1,
	EFFECTTYPE_FROST  = Utility::B2,

	EFFECTTYPE_MAX = 3
};


// Constants


// Prototypes


class CEffectTarget
{

	// Member Functions
public:


	         CEffectTarget();
	virtual ~CEffectTarget();


	void ApplyPoison(float _fPoisonTickDamage, float _fPoisonLength);
	void ApplyFrost(float _fFrostPenaltyRatio, float _fFrostLength);


	// Inline Functions
	inline float GetPoisonTimer() const;
	inline float GetFrostTimer() const;


protected:


	virtual void ProcessPoisonEffect(float _fDeltaTick) = 0;


	void ProcessFrostEffect(float _fDeltaTick);


	virtual void TurnOnFrostEffect(float _fFrostPenaltyRatio) = 0;
	virtual void TurnOffFrostEffect() = 0;


private:


	void Deinitialise();


	CEffectTarget(const CEffectTarget& _krEffectTarget);
	CEffectTarget& operator = (const CEffectTarget& _krEffectTarget);


	// Member Variables
protected:


	float m_fPoisonTimer;
	float m_fPoisonTickDamage;


	float m_fFrostTimer;


private:


};


#include "Inline/EffectTarget.inl"


#endif //__IGFEB11_IG500_EFFECTTARGET_H__