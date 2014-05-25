//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	Waypoint.h
//	Description	:	Declaration of CWaypoint
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

#pragma once
#ifndef __WAYPOINT_H__
#define __WAYPOINT_H__

// Library includes.
#include <d3dx9.h>

class CWaypoint
{
	// Member functions.
public:
	CWaypoint();
	CWaypoint(const D3DXVECTOR3& _rkVecPosition);
	~CWaypoint();

	inline const D3DXVECTOR3& GetPosition() const;
	inline void SetPosition(const D3DXVECTOR3& _rkVecPosition);

	inline const D3DXVECTOR3& GetDirectionToThis() const;
	inline void SetDirectionToThis(const D3DXVECTOR3& _rhs);

	inline const CWaypoint* GetNextWaypoint() const;
	inline void SetNextWaypoint(const CWaypoint* _pkNextWaypoint);

	inline void operator = (const CWaypoint&);

protected:
	CWaypoint(const CWaypoint&);

private:

	// Member data.
public:

protected:
	D3DXVECTOR3 m_vecPosition;	// Position of this waypoint; Is at start for vertex support.
	D3DXVECTOR3 m_vecNormalisedDirection;	// Normalised direction to this waypoint from the previous waypoint.
	const CWaypoint* m_pkNextWaypoint;

private:
};

#include "Waypoint.inl"

#endif	// __WAYPOINT_H__