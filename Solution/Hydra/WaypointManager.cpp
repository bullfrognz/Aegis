//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	WaypointManager.cpp
//	Description	:	Definition of CWaypointManager
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// This include.
#include "WaypointManager.h"

// Local includes.
#include "DeviceManager.h"
#include "Utility.h"

#include "VertexDiffuse.h"
#include "WorldMatrix.h"

// Library includes.
#include <d3dx9.h>
#include <cassert>

CWaypointManager::CWaypointManager()
: m_arrWaypoints(0)
, m_uiNumWaypoints(0)
{

}

CWaypointManager::~CWaypointManager()
{
	Shutdown();
}

/**
*
* Cleans up the waypoint manager, allowing it to be reinitialised.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CWaypointManager::Shutdown()
{
	delete[] m_arrWaypoints;
	m_arrWaypoints = 0;
	m_uiNumWaypoints = 0;
}

/**
*
* This draw call is for debug purposes and is not designed for performance AT ALL!
* Draws a line between each waypoint, allowing the path being followed to be viewed.
*
* @author Jade Abbott
* @param _rDeviceManager Required to set render states, and draw the waypoints.
* @return Void.
*
*/
void
CWaypointManager::Draw(CDeviceManager& _rDeviceManager)
{
	if (m_uiNumWaypoints >= 2)
	{
		assert(m_arrWaypoints);

		// Create an array of vertices (this is purely to stop DirectX from throwing a psychospasm).
		CVertex* pVertices = new CVertex[m_uiNumWaypoints];
		if (pVertices)
		{
			for (unsigned int ui = 0; ui < m_uiNumWaypoints; ++ui)
			{
				pVertices[ui].SetPos(m_arrWaypoints[ui].GetPosition());
			}

			DWORD dwOriginalZState = _rDeviceManager.GetRenderStateValue(D3DRS_ZENABLE);

			if (dwOriginalZState != FALSE)
				_rDeviceManager.SetRenderState(D3DRS_ZENABLE, FALSE);

			_rDeviceManager.SetTransform(D3DTS_WORLD, &CWorldMatrix());	// CWorldMatrix is constructed as identity.

			D3DMATERIAL9 material;
			ZeroMemory(&material, sizeof(D3DMATERIAL9));
			material.Emissive.r = 1.0f;

			_rDeviceManager.SetMaterial(&material);

			_rDeviceManager.SetFVF(D3DFVF_XYZ);
			_rDeviceManager.DrawPrimitiveUP(D3DPT_LINESTRIP, m_uiNumWaypoints - 1, pVertices, sizeof(CVertex));

			if (dwOriginalZState != FALSE)
				_rDeviceManager.SetRenderState(D3DRS_ZENABLE, dwOriginalZState);

			delete[] pVertices;
		}
	}

	//if (m_uiNumWaypoints >= 2)
	//{
	//	assert(m_arrWaypoints);

	//	DWORD dwOriginalZState = _rDeviceManager.GetRenderStateValue(D3DRS_ZENABLE);

	//	if (dwOriginalZState != FALSE)
	//		_rDeviceManager.SetRenderState(D3DRS_ZENABLE, FALSE);

	//	CWorldMatrix matIdentity;
	//	_rDeviceManager.SetTransform(D3DTS_WORLD, &matIdentity);

	//	D3DMATERIAL9 material;
	//	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	//	material.Emissive.r = 1.0f;

	//	_rDeviceManager.SetMaterial(&material);

	//	_rDeviceManager.SetFVF(D3DFVF_XYZ);
	//	_rDeviceManager.DrawPrimitiveUP(D3DPT_LINESTRIP, m_uiNumWaypoints - 1, m_arrWaypoints, sizeof(CWaypoint));

	//	if (dwOriginalZState != FALSE)
	//		_rDeviceManager.SetRenderState(D3DRS_ZENABLE, dwOriginalZState);
	//}
}

/**
*
* Handles creation (and destruction of) waypoints.
*
* @author Jade Abbott
* @param _keMethod The method used to create waypoints.
* @param _rkVecPosition The area where the operation will be performed.
* @return Void.
*
*/
void
CWaypointManager::WaypointCreation(const EWaypointCreation _keMethod, const D3DXVECTOR3& _rkVecPosition)
{
	// Handle functions that do not involve creation of waypoints.
	if (_keMethod == WAYCRE_DELETE || _keMethod == WAYCRE_MOVE)
	{
		if (!m_uiNumWaypoints)
				return;

			// Find the nearest waypoint to the position provided.
			unsigned int uiClosest = Utility::INVALID_ID;	// Element in the array that is closest.
			float fShortestDistanceSq = MathUtility::kMaxFloat;	// Reference value.

			for (unsigned int ui = 0; ui < m_uiNumWaypoints; ++ui)
			{
				float fDistanceSq = D3DXVec3LengthSq(&(m_arrWaypoints[ui].GetPosition() - _rkVecPosition));

				if (fDistanceSq < fShortestDistanceSq)
				{
					fShortestDistanceSq = fDistanceSq;
					uiClosest = ui;
				}
			}

			assert(uiClosest < m_uiNumWaypoints);

		switch (_keMethod)
		{
		case WAYCRE_DELETE:
			{
				RemoveWaypoint(uiClosest);
			}
			break;

		case WAYCRE_MOVE:
			{
				m_arrWaypoints[uiClosest].SetPosition(_rkVecPosition);
			}
			break;
		}

		return;
	}

	// Handle remaining functions (ones that involve creation of waypoints).
	CWaypoint* pWaypoint = new CWaypoint(_rkVecPosition);
	if (!pWaypoint)
		return;

	switch (_keMethod)
	{
	case WAYCRE_BEGIN:
		{
			AddWaypoint(*pWaypoint, 0);	// Inserts a waypoint at the start.
		}
		break;

	case WAYCRE_END:
		{
			AddWaypoint(*pWaypoint, m_uiNumWaypoints);	// Inserts a waypoint at the end.
		}
		break;

	case WAYCRE_INSERT:
		{
			// Handle creation method differently if there are not enough waypoints.
			if (m_uiNumWaypoints < 2)
			{
				WaypointCreation(WAYCRE_END, _rkVecPosition);
				break;
			}

			// Find the closest line to join the waypoint to.
			unsigned int uiClosestEnd = Utility::INVALID_ID;	// Must use the end-waypoint as that is where the new waypoint will be inserted.
			float fReference = MathUtility::kMaxFloat;

			for (unsigned int ui = 0; ui < m_uiNumWaypoints - 1; ++ui)
			{
				const D3DXVECTOR3 kVecLine(m_arrWaypoints[ui + 1].GetPosition() - m_arrWaypoints[ui].GetPosition());
				float fDistanceSq = D3DXVec3LengthSq(D3DXVec3Cross(&D3DXVECTOR3(), &kVecLine, &(m_arrWaypoints[ui].GetPosition() - _rkVecPosition))) / D3DXVec3LengthSq(&kVecLine);

				assert(fDistanceSq != MathUtility::kMaxFloat);
				if (fDistanceSq < fReference)
				{
					fReference = fDistanceSq;
					uiClosestEnd = ui + 1;
				}
			}

			assert(uiClosestEnd < m_uiNumWaypoints);	// Covers Utility::INVALID_ID too.

			AddWaypoint(*pWaypoint, uiClosestEnd);
		}
		break;
	}

	delete pWaypoint;
	pWaypoint = 0;
}

/**
*
* Optimises waypoints and calculates measurement data.
* Should be called at the end of waypoint creation.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CWaypointManager::PostCreate()
{
	if (!m_uiNumWaypoints)
		return;

	// Remove waypoints with no distance in between (will create problems in the future anyway).
	// Also link waypoints (pointers to each other).
	for (unsigned int ui = 0; ui < m_uiNumWaypoints - 1; ++ui)
	{
		if (D3DXVec3LengthSq(&(m_arrWaypoints[ui + 1].GetPosition() - m_arrWaypoints[ui].GetPosition())) <= 0.0f)
		{
			RemoveWaypoint(ui + 1);
			--ui;	// So the one after ui is not skipped when the loop continues.
		}
		else	// Next waypoint is guaranteed to stay...
		{
			m_arrWaypoints[ui].SetNextWaypoint(&m_arrWaypoints[ui + 1]);
		}
	}

	// Find direction the entity must move to get from the old waypoint to the new waypoint (does not apply to first waypoint).
	for (unsigned int ui = 1; ui < m_uiNumWaypoints; ++ui)	// Ignoring the first waypoint, as it is the spawnpoint and hence does not have a direction.
	{
		D3DXVECTOR3 vecOut;
		D3DXVec3Normalize(&vecOut, &(m_arrWaypoints[ui].GetPosition() - m_arrWaypoints[ui - 1].GetPosition()));
		m_arrWaypoints[ui].SetDirectionToThis(vecOut);
	}
}

/**
*
* Inserts the provided waypoint into the requested position.
* If the position is occupied, the existing waypoint is shifted further down.
* This function copies the provided waypoint, meaning it is up to the caller to clean up the original waypoint.
*
* @author Jade Abbott
* @param _rkWaypoint The waypoint to insert.
* @param _uiPosition The element in m_arrWaypoints where it will be inserted. Any existing element in that position will be moved +1.
* @return Void.
*/
void
CWaypointManager::AddWaypoint(const CWaypoint& _rkWaypoint, unsigned int _uiPosition)
{
	assert(_uiPosition <= m_uiNumWaypoints);

	CWaypoint* pWaypoints = new CWaypoint[m_uiNumWaypoints + 1];
	if (!pWaypoints)
		return;

	pWaypoints[_uiPosition] = _rkWaypoint;

	// Insert existing waypoints at the start.
	for (unsigned int ui = 0; ui < _uiPosition; ++ui)
	{
		pWaypoints[ui] = m_arrWaypoints[ui];
	}

	// Insert existing waypoints at the end.
	for (unsigned int ui = _uiPosition; ui < m_uiNumWaypoints; ++ui)
	{
		pWaypoints[ui + 1] = m_arrWaypoints[ui];
	}

	delete[] m_arrWaypoints;
	m_arrWaypoints = pWaypoints;
	++m_uiNumWaypoints;
}

/**
*
* Deletes the waypoint requested.
*
* @author Jade Abbott
* @param _uiWaypoint The position of the waypoint to delete (e.g. Zero deletes the first waypoint).
* @return Void.
*
*/
void
CWaypointManager::RemoveWaypoint(unsigned int _uiWaypoint)
{
	assert(_uiWaypoint < m_uiNumWaypoints);

	CWaypoint* pWaypoints = new CWaypoint[m_uiNumWaypoints - 1];

	// Insert existing waypoints at the start.
	for (unsigned int ui = 0; ui < _uiWaypoint; ++ui)
	{
		if (pWaypoints)	// Is only validated during insertion so that when the last element is deleted, it will remove the old array anyway.
		{
			pWaypoints[ui] = m_arrWaypoints[ui];
		}
	}

	// Insert existing waypoints at the end.
	for (unsigned int ui = _uiWaypoint + 1; ui < m_uiNumWaypoints; ++ui)
	{
		if (pWaypoints)	// Is only validated during insertion so that when the last element is deleted, it will remove the old array anyway.
		{
			pWaypoints[ui - 1] = m_arrWaypoints[ui];
		}
	}

	delete[] m_arrWaypoints;
	m_arrWaypoints = pWaypoints;
	--m_uiNumWaypoints;
}