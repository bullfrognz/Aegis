//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	Waypoint.inl
//	Description	:	Definition of inline CWaypoint functions.
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

/**
*
* Returns the position of this waypoint in world space.
*
* @author Jade Abbott
* @return The position of this waypoint in world space.
*
*/
const D3DXVECTOR3&
CWaypoint::GetPosition() const
{
	return m_vecPosition;
}

/**
*
* Sets the position of this waypoint in world space.
*
* @author Jade Abbott
* @param _rkVecPosition The position this waypoint will be.
*
*/
void
CWaypoint::SetPosition(const D3DXVECTOR3& _rkVecPosition)
{
	m_vecPosition = _rkVecPosition;
}

/**
*
* Returns the (normalised) direction from the last waypoint to this waypoint.
* This saves entities on a fixed path from having to calculate direction using square-root.
*
* @author Jade Abbott
* @return Normalised vector pointing from the last waypoint to this waypoint.
*
*/
const D3DXVECTOR3&
CWaypoint::GetDirectionToThis() const
{
	return m_vecNormalisedDirection;
}

/**
*
* Sets the direction from the last waypoint to this waypoint.
* Should be normailsed.
*
* @author Jade Abbott
* @return Normalised vector pointing from the last waypoint to this waypoint.
*
*/
void
CWaypoint::SetDirectionToThis(const D3DXVECTOR3& _rhs)
{
	m_vecNormalisedDirection = _rhs;
}

/**
*
* Returns pointer to the waypoint after this one.
* Returns null if there are no more waypoints (this is the last).
*
* @author Jade Abbott
* @return Pointer to the waypoint after this one. But null if there are no more waypoints (when this is the last).
*
*/
const CWaypoint*
CWaypoint::GetNextWaypoint() const
{
	return m_pkNextWaypoint;
}

/**
*
* Sets the pointer to the waypoint after this one.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CWaypoint::SetNextWaypoint(const CWaypoint* _pkNextWaypoint)
{
	m_pkNextWaypoint = _pkNextWaypoint;
}

void
CWaypoint::operator = (const CWaypoint& _rhs)
{
	m_vecPosition = _rhs.m_vecPosition;
	m_vecNormalisedDirection = _rhs.m_vecNormalisedDirection;
	m_pkNextWaypoint = _rhs.m_pkNextWaypoint;
}