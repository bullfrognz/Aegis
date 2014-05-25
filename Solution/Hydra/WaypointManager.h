//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	WaypointManager.h
//	Description	:	Declaration of CWaypointManager
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

#pragma once
#ifndef __WAYPOINTMANAGER_H__
#define __WAYPOINTMANAGER_H__

// Local includes.
#include "Waypoint.h"
class CDeviceManager;
struct D3DXVECTOR3;

// Enumerations.
enum EWaypointCreation
{
	WAYCRE_BEGIN,	// Insert a waypoint at the front.
	WAYCRE_END,		// Insert a waypoint at the back.
	WAYCRE_INSERT,	// Insert a waypoint into the closest track piece.
	WAYCRE_MOVE,	// Move the closest waypoint.
	WAYCRE_DELETE	// Delete the closest waypoint.
};

class CWaypointManager
{
	// Member functions.
public:
	CWaypointManager();
	~CWaypointManager();

	void Shutdown();

	void Draw(CDeviceManager& _rDeviceManager);

	inline const CWaypoint* GetWaypoint(unsigned int _uiWaypoint) const;
	inline unsigned int GetNumWaypoints() const;

	// Construction functions.
	void WaypointCreation(const EWaypointCreation _keMethod, const D3DXVECTOR3& _rkVecPosition);
	void PostCreate();

protected:
	CWaypointManager(const CWaypointManager&);

	void AddWaypoint(const CWaypoint& _rkWaypoint, unsigned int _uiPosition);
	void RemoveWaypoint(unsigned int _uiWaypoint);

private:

	// Member data.
public:

protected:
	CWaypoint* m_arrWaypoints;
	unsigned int m_uiNumWaypoints;

private:
};

#include "WaypointManager.inl"

#endif	// __WAYPOINTMANAGER_H__