//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	Waypoint.cpp
//	Description	:	Definition of CWaypoint
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// This include.
#include "Waypoint.h"

CWaypoint::CWaypoint()
: m_vecPosition(0.0f, 0.0f, 0.0f)
, m_vecNormalisedDirection(0.0f, 0.0f, 0.0f)
, m_pkNextWaypoint(0)
{

}

CWaypoint::CWaypoint(const D3DXVECTOR3& _rkVecPosition)
: m_vecPosition(_rkVecPosition)
, m_vecNormalisedDirection(0.0f, 0.0f, 0.0f)
, m_pkNextWaypoint(0)
{

}

CWaypoint::~CWaypoint()
{

}