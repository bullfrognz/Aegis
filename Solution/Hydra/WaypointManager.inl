//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	WaypointManager.inl
//	Description	:	Definition of inline CWaypointManager functions.
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// Local includes.
#include "Waypoint.h"	// The entities calling GetWaypoint() will need this data anyway.

/**
*
* Returns the requested waypoint.
* If the waypoint erquested does not exist, a null pointer is returned.
* This is good when detecting when the last waypoint was reached.
*
* @author Jade Abbott
* @param _uiWaypoint The waypoint to return.
* @return Pointer to the waypoint requested, but null when the waypoint erquested does not exist.
*
*/
const CWaypoint*
CWaypointManager::GetWaypoint(unsigned int _uiWaypoint) const
{
	return _uiWaypoint < m_uiNumWaypoints ? &m_arrWaypoints[_uiWaypoint] : 0;
}

/**
*
* Returns the number of waypoints that exist.
*
* @author Jade Abbott
* @return The number of waypoints that exist.
*
*/
unsigned int
CWaypointManager::GetNumWaypoints() const
{
	return m_uiNumWaypoints;
}