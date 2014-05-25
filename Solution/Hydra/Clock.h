//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	Clock.h
//	Description	:	Declaration of CClock
//	Author		:	Jade Abbott
//	Mail		:	20chimps@gmail.com
//

#pragma once
#ifndef __SR_CLOCK_H__
#define __SR_CLOCK_H__

__declspec(align(8)) class CClock
{
	// Member functions.
public:
	inline CClock();
	inline ~CClock();

	bool Initialise();
	void Process();
	inline const double& GetDeltaTick() const;

protected:
	CClock(const CClock&);	// Disallow initialisation by copy.

private:

	// Member data.
public:
	union mTime
	{
		__int64 m_i64HighRes;	// Raw time for high resolution.
		int m_arriLowRes[2];	// Raw time for low resolution.
	};

protected:
	double m_dFreq;	// Frequency of the quartz chip.
	double m_dDeltaTick;	// Delta time in seconds.
	mTime m_RawTime;

private:

};

#include "Clock.inl"

#endif	// __SR_CLOCK_H__