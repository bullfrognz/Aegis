//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	Terrain.cpp
//	Description	:	Definition of CTerrain
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// This include.
#include "Terrain.h"

// Local includes.
#include "Utility.h"
#include "INIParser.h"
#include "D3DRenderer.h"
#include "MeshManager.h"
#include "DeviceManager.h"
#include "WorldMatrix.h"
#include "Tower.h"
#include "Camera.h"

// Library includes.
#include <d3dx9.h>

CTerrain::CTerrain()
: m_pRenderer(0)
, m_fTileSpacing(0.0f)
, m_2dTileArray(0)
, m_uiWidth(0)
, m_uiHeight(0)
, m_pkcTerrain("Terrain")
, m_pkcWaypoints("Waypoints")
, m_arrpTowers(0)
, m_uiNumTowers(0)
, m_fTowerHeightOffset(0.0f)
{
	for (unsigned int ui = 0; ui < TILETYPE_MAX; ++ui)
	{
		m_arruiTileID[ui] = Utility::INVALID_ID;
	}
}

CTerrain::~CTerrain()
{
	Shutdown();
}

/**
*
* Cleans up the terrain manager.
* Can be initialised afterwards.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CTerrain::Shutdown()
{
	for (unsigned int uiWidth = 0; uiWidth < m_uiWidth; ++uiWidth)
	{
		delete[] m_2dTileArray[uiWidth];
	}
	
	delete[] m_2dTileArray;
	m_2dTileArray = 0;

	m_uiWidth = 0;
	m_uiHeight = 0;

	m_WaypointManager.Shutdown();

	for (unsigned int ui = 0; ui < m_uiNumTowers; ++ui)
	{
		delete m_arrpTowers[ui];
	}
	delete[] m_arrpTowers;
	m_arrpTowers = 0;
	m_uiNumTowers = 0;
}

/**
*
* Sets up CTerrain.
* Loads the meshes for each tile type (water mesh, hill mesh, etc).
*
* @author Jade Abbott
* @param _pRenderer Required for initialising towers, and accessing managers such as the mesh manager.
* @param _fTileSpacing The space (in game units) between each tile.
* @param _fTowerHeightOffset How much each tower will translate along the Y axis (specifically to stop intersecting with the terrain).
* @param _bIsInGame False will draw a mesh for blank tiles (this is for the map editor); True will not draw anything for blank tiles.
* @return True if initialisation was successful.
*
*/
bool
CTerrain::Initialise(CD3DRenderer* _pRenderer, float _fTileSpacing, float _fTowerHeightOffset, bool _bIsInGame)
{
	assert(_pRenderer);
	assert(!m_pRenderer);

	m_pRenderer = _pRenderer;
	m_fTileSpacing = _fTileSpacing;
	m_fTowerHeightOffset = _fTowerHeightOffset;

	// Load meshes.
	CMeshManager& rMeshManager = _pRenderer->GetMeshManager();
	m_arruiTileID[TILETYPE_RAISED] = rMeshManager.CreateNewMesh(L"Assets\\Mesh\\Terrain_TowerTile.x");
	m_arruiTileID[TILETYPE_WATER] = rMeshManager.CreateNewMesh(L"Assets\\Mesh\\MapEditor_WaterTile.x");
	m_arruiTileID[TILETYPE_PATH] = rMeshManager.CreateNewMesh(L"Assets\\Mesh\\MapEditor_GoldTile.x");
	m_arruiTileID[TILETYPE_START] = rMeshManager.CreateNewMesh(L"Assets\\Mesh\\MapEditor_StartTile.x");
	m_arruiTileID[TILETYPE_END] = rMeshManager.CreateNewMesh(L"Assets\\Mesh\\MapEditor_EndTile.x");

	if (!_bIsInGame)
		m_arruiTileID[TILETYPE_BLANK] = rMeshManager.CreateNewMesh(L"Assets\\Mesh\\MapEditor_DefaultTile.x");

	return true;
}

/**
*
* Processes the towers.
*
* @param _fDeltaTick The time since last process
* @return Void.
*
*/
void
CTerrain::Process(float _fDeltaTick)
{
	for (unsigned int ui = 0; ui < m_uiNumTowers; ++ui)
	{
		if (m_arrpTowers[ui])
		{
			m_arrpTowers[ui]->Process(_fDeltaTick);
		}
	}
}

/**
*
* Renders the terrain.
* When a tile will be drawn in a different way (e.g. with a highlight), provide the address of the tile to exclude.
*
* @author Jade Abbott
* @param _pTileToExclude If a tile is not to be drawn, provide the address of the tile.
* @param _bDrawTowers True to draw all towers; If set to false, DrawTowers() must be called to draw towers (do not call this function again).
* @return Void.
*
*/
void
CTerrain::Draw(const CTile* _pkTileToExclude, bool _bDrawTowers) const
{
	assert(m_uiWidth || m_uiHeight ? !!m_2dTileArray : true);	// If the width or height are non-zero, the array must be valid.
	assert(m_pRenderer);

	CDeviceManager& rDeviceManager = m_pRenderer->GetDeviceManager();
	CMeshManager& rMeshManager = m_pRenderer->GetMeshManager();

	for (unsigned int uiWidth = 0; uiWidth < m_uiWidth; ++uiWidth)
	{
		for (unsigned int uiHeight = 0; uiHeight < m_uiHeight; ++uiHeight)
		{
			CTile& rTile = m_2dTileArray[uiWidth][uiHeight];
				
			// Ignore this tile if a tile to exclude has been specified.
			if (&rTile == _pkTileToExclude)
				continue;

			// Get the tile type so the proper mesh can be applied.
			unsigned int uiThisTileID = m_arruiTileID[rTile.GetTileType()];

			// If the mesh ID is valid, set the world matrix on the device, then draw the associated mesh.
			if (uiThisTileID != Utility::INVALID_ID)
			{
				// Cull the object if necessry.
				if (!CCamera::IsInFrustum(rTile.GetWorldMatrix().GetPosition(CVector3()), rMeshManager.GetVertexData(uiThisTileID).m_fBoundingSphereRadius))
					continue;

				rDeviceManager.SetTransform(D3DTS_WORLD, &rTile.GetWorldMatrix());
				rMeshManager.Render(uiThisTileID);
			}
		}
	}

	if (_bDrawTowers)
	{
		for (unsigned int ui = 0; ui < m_uiNumTowers; ++ui)
		{
			if (m_arrpTowers[ui])
			{
				m_arrpTowers[ui]->Draw(m_pRenderer);
			}
		}
	}
}

/**
*
* Draws a single tile.
*
* @author Jade Abbott
* @param _uiX Horizontal position of the tile.
* @param _uiY Vertical position of the tile.
* @return Void.
*
*/
void
CTerrain::DrawTile(unsigned int _uiX, unsigned int _uiY)
{
	assert(_uiX < m_uiWidth);
	assert(_uiY < m_uiHeight);
	assert(m_2dTileArray);
	assert(m_pRenderer);

	CTile& rTile = m_2dTileArray[_uiX][_uiY];

	// Get the tile type so the proper mesh can be applied.
	unsigned int uiThisTileID = m_arruiTileID[rTile.GetTileType()];

	// If the mesh ID is valid, set the world matrix on the device, then draw the associated mesh.
	if (uiThisTileID != Utility::INVALID_ID)
	{
		m_pRenderer->GetDeviceManager().SetTransform(D3DTS_WORLD, &rTile.GetWorldMatrix());
		m_pRenderer->GetMeshManager().Render(uiThisTileID);
	}
}

/**
*
* Only call this function if the terrain was drawn with towers explicitly excluded.
*
* @author Jade Abbott
* @param _uiTowerToExcludeID Providing a valid ID will cause the tower matching the ID to not be drawn.
* @return Void.
*
*/
void
CTerrain::DrawTowers(unsigned int _uiTowerToExcludeID)
{
	for (unsigned int ui = 0; ui < m_uiNumTowers; ++ui)
	{
		if (m_arrpTowers[ui] && ui != _uiTowerToExcludeID)
		{
			m_arrpTowers[ui]->Draw(m_pRenderer);
		}
	}
}

/**
*
* Draws a specific tower.
*
* @author Jade bbott
* @param _uiTowerID The ID matching the tower to draw.
* @return Void.
*
*/
void
CTerrain::DrawTower(unsigned int _uiTowerID)
{
	assert(m_pRenderer);

	if (_uiTowerID == Utility::INVALID_ID)
		return;

	assert(_uiTowerID < m_uiNumTowers);
	assert(m_arrpTowers[_uiTowerID]);

	m_arrpTowers[_uiTowerID]->Draw(m_pRenderer);
}

/**
*
* Loads a map from .ini file.
* Assumes the INI parser passed in has the map file open.
*
* @author Jade Abbott
* @param _rkIniParser The .ini parser that is assumed to have the map file open.
* @return True if map loading was successful (existing map is invalidated either way).
*
*/
bool
CTerrain::LoadMap(const char* _pckMapFile)
{
	CINIParser _rkIniParser;
	_rkIniParser.LoadINIFile(_pckMapFile);

	// Clean up old data.
	Shutdown();

	// Temporary data.
	const unsigned int kuiBufferSize = 50;
	char arrcBuffer[kuiBufferSize];

	///////////////////////////////////////
	// Set up terrain:

	// Get terrain dimensions.
	bool bSuccess = _rkIniParser.GetValue(m_pkcTerrain, "Width", m_uiWidth);
	bSuccess = _rkIniParser.GetValue(m_pkcTerrain, "Height", m_uiHeight) ? bSuccess : false;

	if (!bSuccess || !m_uiWidth || !m_uiHeight)	// Missing data; No width; No height...
		return false;

	// Create first dimension of 2D array.
	m_2dTileArray = new CTile*[m_uiWidth];
	if (!m_2dTileArray)
		return false;

	// Create second dimension of 2D array.
	for (unsigned int uiWidth = 0; uiWidth < m_uiWidth; ++uiWidth)
	{
		m_2dTileArray[uiWidth] = new CTile[m_uiHeight];	// Create second dimensional slice.
		if (!m_2dTileArray[uiWidth])	// If failed...
		{
			for (unsigned int ui = 0; ui < uiWidth; ++ui)	// For every previous slice...
			{
				delete[] m_2dTileArray[ui];	// Delete the slice...
			}
			delete[] m_2dTileArray;	// Delete the first dimension.
			m_2dTileArray = 0;	// Nullify.
			return false;	// Report failure.
		}
	}

	// Get from .ini, and set information regarding each element.
	for (unsigned int uiWidth = 0; uiWidth < m_uiWidth; ++uiWidth)
	{
		for (unsigned int uiHeight = 0; uiHeight < m_uiHeight; ++uiHeight)
		{
			sprintf_s(arrcBuffer, kuiBufferSize, "%i_%i", uiWidth, uiHeight);

			unsigned int uiData = 0;
			_rkIniParser.GetValue(m_pkcTerrain, arrcBuffer, uiData);	// If information obtaining fails, the tile is void of data.

			m_2dTileArray[uiWidth][uiHeight].SetRawData(static_cast<unsigned char>(uiData));	// Information was obtained in unsigned int form to not confuse the ini parser into grabbing a letter (char) or character-based number (e.g. '1')

			// Set position of the tile.
			CWorldMatrix matWorld;
			matWorld.SetPosition((uiWidth - ((m_uiWidth - 1) * 0.5f)) * m_fTileSpacing,
								 0.0f,
								 (uiHeight - ((m_uiHeight - 1) * 0.5f)) * m_fTileSpacing);

			m_2dTileArray[uiWidth][uiHeight].SetPosition(matWorld);
		}
	}

	///////////////////////////////////////
	// Set up waypoints:

	D3DXVECTOR3 vecWaypointPos;
	unsigned int ui = 0;

	// Get all waypoints from file, and add to waypoint manager.
	do
	{
		sprintf_s(arrcBuffer, kuiBufferSize, "WP%i", ui);	// Waypoint ui's position.
		if (!_rkIniParser.GetValue(m_pkcWaypoints, arrcBuffer, vecWaypointPos))
			break;

		m_WaypointManager.WaypointCreation(WAYCRE_END, vecWaypointPos);	// Insert waypoint as the last node (insert at end).
	} while (++ui);	// To stop infinite loops.

	// Let waypoint manager calculate final information.
	m_WaypointManager.PostCreate();

	return true;
}

/**
*
* Saves the map to file, using the provided file name.
*
* @author Jade Abbott
* @param The file name to use.
* @return Void.
*
*/
void
CTerrain::SaveMap(const char* _pkcFileName) const
{
	// Temporary data.
	const unsigned int kuiBufferSize = 100;
	char cBuffer1[kuiBufferSize];
	char cBuffer2[kuiBufferSize];

	CINIParser parser;
	parser.LoadINIFile(_pkcFileName);

	//////////////////////////
	// Save terrain data.

	sprintf_s(cBuffer1, kuiBufferSize, "%i", m_uiWidth);
	parser.AddValue(m_pkcTerrain, "Width", cBuffer1);
	sprintf_s(cBuffer1, kuiBufferSize, "%i", m_uiHeight);
	parser.AddValue(m_pkcTerrain, "Height", cBuffer1);

	for (unsigned int uiWidth = 0; uiWidth < m_uiWidth; ++uiWidth)
	{
		for (unsigned int uiHeight = 0; uiHeight < m_uiHeight; ++uiHeight)
		{
			sprintf_s(cBuffer1, kuiBufferSize, "%i_%i", uiWidth, uiHeight);
			sprintf_s(cBuffer2, kuiBufferSize, "%i", m_2dTileArray[uiWidth][uiHeight].GetTileType());
			parser.AddValue(m_pkcTerrain, cBuffer1, cBuffer2);
		}
	}

	//////////////////////////
	// Save waypoint data.

	for (unsigned int ui = 0; ui < m_WaypointManager.GetNumWaypoints(); ++ui)
	{
		assert(m_WaypointManager.GetWaypoint(ui));
		const D3DXVECTOR3& rkVecPos = m_WaypointManager.GetWaypoint(ui)->GetPosition();

		sprintf_s(cBuffer1, kuiBufferSize, "WP%i", ui);
		sprintf_s(cBuffer2, kuiBufferSize, "%.17f, %.17f, %.17f", rkVecPos.x, rkVecPos.y, rkVecPos.z);
		parser.AddValue(m_pkcWaypoints, cBuffer1, cBuffer2);
	}

	/////////////////////
	// Dump out map file.
	parser.SaveINIFile(_pkcFileName);
}

/**
*
* Returns the tile that is closest to the position provided.
*
* @author Jade Abbott
* @param _rkVecClosestPos The position to check against the terain to see which tile is closest.
* @return The closest tile to the position provided.
*
*/
const CTile&
CTerrain::GetTile(const D3DXVECTOR3& _rkVecClosestPos, unsigned int* _puiX, unsigned int* _puiY) const
{
	assert(m_uiWidth && m_uiHeight);	// Must have at least one tile.

	// Find the closest tile.
	float fShortestDistanceSq = MathUtility::kMaxFloat;
	unsigned int uiRefWidth = 0;
	unsigned int uiRefHeight = 0;

	for (unsigned int uiWidth = 0; uiWidth < m_uiWidth; ++uiWidth)
	{
		for (unsigned int uiHeight = 0; uiHeight < m_uiHeight; ++uiHeight)
		{
			D3DXVECTOR3 vecPos;
			m_2dTileArray[uiWidth][uiHeight].GetPosition(vecPos);

			float fDistanceSq = D3DXVec3LengthSq(&(vecPos - _rkVecClosestPos));

			if (fDistanceSq < fShortestDistanceSq)
			{
				fShortestDistanceSq = fDistanceSq;
				uiRefWidth = uiWidth;
				uiRefHeight = uiHeight;
			}
		}
	}

	if (_puiX)
		*_puiX = uiRefWidth;

	if (_puiY)
		*_puiY = uiRefHeight;

	return m_2dTileArray[uiRefWidth][uiRefHeight];
}

/**
*
* @author Jade Abbott
*
*/
unsigned int
CTerrain::AddTower(unsigned int _uiX, unsigned int _uiY, const char* _pkcTowerType)
{
	assert(m_pRenderer);
	assert(m_2dTileArray);	// Terrain must exist.
	assert(_uiX < m_uiWidth);	// X position must be valid.
	assert(_uiY < m_uiHeight);	// Y position must be valid.
	assert(m_2dTileArray[_uiX][_uiY].GetObjectID() == Utility::INVALID_ID);	// Tile must be unoccupied.

	// Get free element.
	unsigned int uiTowerID = GetFreeElement();
	if (uiTowerID == Utility::INVALID_ID)
		return Utility::INVALID_ID;

	// Create tower in free element.
	m_arrpTowers[uiTowerID] = new CTower();
	if (!m_arrpTowers[uiTowerID])
		return Utility::INVALID_ID;

	// Initialise tower.
	if (!m_arrpTowers[uiTowerID]->Initialise(m_pRenderer, _pkcTowerType))	// If initialisation failed...
	{
		assert(false);	// Creation of tower failed (_pkcTowerType?).
		delete m_arrpTowers[uiTowerID];
		m_arrpTowers[uiTowerID] = 0;

		return Utility::INVALID_ID;
	}

	// TODO: Give tower it's ID.

	// Inform tile of object.
	CTile& rTile = m_2dTileArray[_uiX][_uiY];

	rTile.SetObjectType(TILEOBJ_TOWER);
	rTile.SetObjectID(uiTowerID);

	// Set tower's location.
	CWorldMatrix& rTowerMatrix = m_arrpTowers[uiTowerID]->GetWorldMatrix();	// Get access to world matrix.
	rTowerMatrix = rTile.GetWorldMatrix();	// Set position as the same as the tile.
	rTowerMatrix.TranslatePosition(0.0f, m_fTowerHeightOffset, 0.0f);

	return uiTowerID;
}

/**
*
* Deletes the tower matching the provided ID.
*
* @author Jade Abbott
* @param _uiID The ID of the tower to be destroyed.
* @return Void.
*
*/
void
CTerrain::DestroyTower(unsigned int _uiID)
{
	assert(m_arrpTowers);
	assert(_uiID < m_uiNumTowers);

	if (m_arrpTowers[_uiID])
	{
		delete m_arrpTowers[_uiID];
		m_arrpTowers[_uiID] = 0;

		// Find the tile that this tower resided on.
		for (unsigned int uiWidth = 0; uiWidth < m_uiWidth; ++uiWidth)
		{
			for (unsigned int uiHeight = 0; uiHeight < m_uiHeight; ++uiHeight)
			{
				if (m_2dTileArray[uiWidth][uiHeight].GetObjectType() == TILEOBJ_TOWER && m_2dTileArray[uiWidth][uiHeight].GetObjectID() == _uiID)
				{
					m_2dTileArray[uiWidth][uiHeight].SetObjectID(Utility::INVALID_ID);
					return;
				}
			}
		}
	}
}

/**
*
* Deletes the tower in the provided position.
* This method should be preferred over the previous one.
*
* @author Jade Abbott
* @return Void.
*
*/
void
CTerrain::DestroyTower(unsigned int _uiX, unsigned int _uiY)
{
	assert(m_arrpTowers);
	assert(m_2dTileArray);
	assert(_uiX < m_uiWidth);
	assert(_uiY < m_uiHeight);
	assert(m_2dTileArray[_uiX][_uiY].GetObjectType() == TILEOBJ_TOWER);

	unsigned int uiID = m_2dTileArray[_uiX][_uiY].GetObjectID();	// Get the ID of the tower to destroy.
	assert(uiID != Utility::INVALID_ID);	// Why would this function be called when there is no tower?

	m_2dTileArray[_uiX][_uiY].SetObjectID(Utility::INVALID_ID);	// Deregister tower from terrain.

	delete m_arrpTowers[uiID];	// Destroy tower.
	m_arrpTowers[uiID] = 0;
}

/**
*
* @author Jade Abbott
*
*/
bool
CTerrain::InitialiseBlankTerrain(unsigned int _uiWidth, unsigned int _uiHeight)
{
	Shutdown();

	// Create first dimension of 2D array.
	m_2dTileArray = new CTile*[_uiWidth];
	if (!m_2dTileArray)
		return false;

	// Create second dimension of 2D array.
	for (unsigned int uiWidth = 0; uiWidth < _uiWidth; ++uiWidth)
	{
		m_2dTileArray[uiWidth] = new CTile[_uiHeight];	// Create second dimensional slice.
		if (!m_2dTileArray[uiWidth])	// If failed...
		{
			for (unsigned int ui = 0; ui < uiWidth; ++ui)	// For every previous slice...
			{
				delete[] m_2dTileArray[ui];	// Delete the slice...
			}
			delete[] m_2dTileArray;	// Delete the first dimension.
			m_2dTileArray = 0;	// Nullify.
			return false;	// Report failure.
		}

		for (unsigned int uiHeight = 0; uiHeight < _uiHeight; ++uiHeight)
		{
			// Set position of the tile.
			CWorldMatrix matWorld;
			matWorld.SetPosition((uiWidth - ((_uiWidth - 1) * 0.5f)) * m_fTileSpacing,
								 0.0f,
								 (uiHeight - ((_uiHeight - 1) * 0.5f)) * m_fTileSpacing);

			m_2dTileArray[uiWidth][uiHeight].SetPosition(matWorld);
		}
	}

	m_uiWidth = _uiWidth;
	m_uiHeight = _uiHeight;

	return true;
}

/**
*
* Returns an iteration into the tower array, which is an unused pointer.
* Resizes the array if necessary.
* Returns Utility::INVALID_ID if all has failed.
*
* @athor Jade Abbott
* @return Iteration into m_arrpTowers for an unused pointer; Is Utility::INVALID_ID if failed.
*
*/
unsigned int
CTerrain::GetFreeElement()
{
	// Check if there is a free element in the array.
	for (unsigned int ui = 0; ui < m_uiNumTowers; ++ui)
	{
		if (!m_arrpTowers[ui])
		{
			return ui;
		}
	}

	// Else there are no free elements.
	// Increase the array size.
	CTower** arrpTowers = new CTower*[m_uiNumTowers + 1];
	if (!arrpTowers)
		return Utility::INVALID_ID;

	memcpy(arrpTowers, m_arrpTowers, sizeof(CTower*) * m_uiNumTowers);
	arrpTowers[m_uiNumTowers] = 0;
	delete[] m_arrpTowers;
	m_arrpTowers = arrpTowers;
	++m_uiNumTowers;

	return m_uiNumTowers - 1;
}