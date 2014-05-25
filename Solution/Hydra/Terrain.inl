//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	Terrain.inl
//	Description	:	Definition of inline CTerrain functions.
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// Local includes.
#include "Utility.h"
#include "Tower.h"

// Library includes.
#include <cassert>

/**
*
* Returns an uneditable version of the tile requested.
* This function is intended for use during runtime.
*
* @author Jade Abbott
* @param _uiX The row that the tile exists in (beginning from zero).
* @param _uiY The column that the tile exists in (beginning from zero).
* @return Reference to the constant tile.
*
*/
const CTile&
CTerrain::GetTile(unsigned int _uiX, unsigned int _uiY) const
{
	assert(_uiX < m_uiWidth && _uiY < m_uiHeight);
	assert(m_2dTileArray);
	return m_2dTileArray[_uiX][_uiY];
}

/**
*
* Returns an editable version of the tile requested.
* This function is intended for use during initialisation or map creation.
*
* @author Jade Abbott
* @param _uiX The row that the tile exists in (beginning from zero).
* @param _uiY The column that the tile exists in (beginning from zero).
* @return Reference to the tile.
*
*/
CTile&
CTerrain::GetTile(unsigned int _uiX, unsigned int _uiY, bool _bUnused)
{
	assert(_uiX < m_uiWidth && _uiY < m_uiHeight);
	assert(m_2dTileArray);
	return m_2dTileArray[_uiX][_uiY];
}

/**
*
* Returns the number of rows in the grid.
*
* @author Jade Abbott
* @return The number of rows in the grid.
*
*/
unsigned int
CTerrain::GetGridWidth() const
{
	return m_uiWidth;
}

/**
*
* Returns the number of columns in the grid.
*
* @author Jade Abbott
* @return The number of columns in the grid.
*
*/
unsigned int
CTerrain::GetGridHeight() const
{
	return m_uiHeight;
}

/**
*
* Returns the distance between each tile (in world space distance).
*
* @author Jade Abbott
* @return The distance between each tile (in world space distance).
*
*/
float
CTerrain::GetTileSpacing() const
{
	return m_fTileSpacing;
}

/**
*
* Returns a reference to the uneditable waypoint manager.
* This is because the waypoint manager is not edited outside of the terrain manager.
*
* @author Jade Abbott
* @return Reference to the uneditable waypoint manager.
*
*/
const CWaypointManager&
CTerrain::GetWaypointManager() const
{
	return m_WaypointManager;
}

/**
*
* Returns the tower matching the ID provided.
*
* @author Jade Abbott
* @param _uiID The ID of the tower to obtain (note nonexistent towers will trigger a break).
* @return Reference to the tower (because the tower requested should always be valid).
*
*/
CTower&
CTerrain::GetTower(unsigned int _uiID)
{
	assert(_uiID < m_uiNumTowers);
	assert(m_arrpTowers);
	assert(m_arrpTowers[_uiID]);	// While it is possible to return a pointer, invalid towers should never be requested.

	return *m_arrpTowers[_uiID];
}

float
CTerrain::GetTowerHeightOffset() const
{
	return m_fTowerHeightOffset;
}

unsigned int
CTerrain::GetNumTowers() const
{
	return m_uiNumTowers;
}

const CTower* const* const
CTerrain::GetTowers() const
{
	return m_arrpTowers;
}

/**
*
* Returns a reference to the editable waypoint manager.
* This is for map creation.
*
* @author Jade Abbott
* @return Reference to the editable waypoint manager.
*
*/
CWaypointManager&
CTerrain::GetWaypointManager()
{
	return m_WaypointManager;
}