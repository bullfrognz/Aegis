//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	Clock.cpp
//	Description	:	Definition of CClock
//	Author		:	Jade Abbott
//	Mail		:	20chimps@gmail.com
//

// This include.
#include "Clock.h"	// Included first so header remains unaware of includes.

// Library includes.
#include <ctime>
#include <Windows.h>
#define WIN32_LEAN_AND_MEAN
#include <cassert>

/**
*
* Picks the best method for measuring time.
*
* @author Jade Abbott
* @return False if the high resolution timer is unavailable (Initialisation will always succeed).
*
*/
bool
CClock::Initialise()
{
	assert(sizeof(m_RawTime.m_i64HighRes) >= sizeof(LARGE_INTEGER));	// ms8Time is currently unused, it's capacity is needed here. 
	bool bSuccess = !!QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&m_RawTime.m_i64HighRes));	// Zero cost to reinterpret.
	bSuccess = bSuccess && m_RawTime.m_i64HighRes;
	if (bSuccess)
		m_dFreq = 1.0 / m_RawTime.m_i64HighRes;	// Calculating the time frequency fraction should be done now to replace divions with multiplications.
	else
		m_dFreq = 0.0;

	return bSuccess;
}

/**
*
* Calculates the delta time since last Process().
*
* @author Jade Abbott.
* @return Void.
*
*/
void
CClock::Process()
{
	if (m_dFreq)	// High resolution timer available.
	{
		__int64 i64TimeOld = m_RawTime.m_i64HighRes;	// Stack allocated memory (8).
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&m_RawTime.m_i64HighRes));
		m_dDeltaTick = (m_RawTime.m_i64HighRes - i64TimeOld) * m_dFreq;
	}
	else	// Low resolution only.
	{
		m_RawTime.m_arriLowRes[1] = *m_RawTime.m_arriLowRes;
		*m_RawTime.m_arriLowRes = clock();	// The new and old time must be held on to (old for this tick, new for the next).
		m_dDeltaTick = (*m_RawTime.m_arriLowRes - m_RawTime.m_arriLowRes[1]) * 0.001;	// Low resolution ticks are in milliseconds, so multiply by 1/1000 to get delta.
	}
}