//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	Terrain.h
//	Description	:	Declaration of CTerrain
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

#pragma once
#ifndef	__HYDRA_TERRAIN_H__
#define __HYDRA_TERRAIN_H__

// Local includes.
#include "WaypointManager.h"
#include "Tile.h"
#include "Utility.h"
class CMeshManager;
class CINIParser;
class CD3DRenderer;
class CTower;

class CTerrain
{
	// Member functions.
public:
	CTerrain();
	~CTerrain();

	void Shutdown();

	bool Initialise(CD3DRenderer* _pRenderer, float _fTileSpacing, float _fTowerHeightOffset, bool _bIsInGame);
	void Process(float _fDeltaTick);
	void Draw(const CTile* _pkTileToExclude = 0, bool _bDrawTowers = true) const;
	void DrawTile(unsigned int _uiX, unsigned int _uiY);
	void DrawTowers(unsigned int _uiTowerToExcludeID = Utility::INVALID_ID);
	void DrawTower(unsigned int _uiTowerID);

	bool LoadMap(const char* _pckMapFile);
	void SaveMap(const char* _pkcFileName) const;

	inline const CTile& GetTile(unsigned int _uiX, unsigned int _uiY) const;	// For checks.
	inline CTile& GetTile(unsigned int _uiX, unsigned int _uiY, bool _bUnused);	// For creation, such as placing a tower on the tile.
	const CTile& GetTile(const D3DXVECTOR3& _rkVecClosestPos, unsigned int* _puiX = 0, unsigned int* _puiY = 0) const;	// For grabbing the tile closest to where the user has clicked.
	//CTile& GetTile(const D3DXVECTOR3& _rkVecClosestPos, unsigned int* _puiX = 0, unsigned int* _puiY = 0);	// For grabbing the tile closest to where the user has clicked.
	
	inline unsigned int GetGridWidth() const;
	inline unsigned int GetGridHeight() const;
	inline float GetTileSpacing() const;

	inline const CWaypointManager& GetWaypointManager() const;

	// Tower stuff.
	unsigned int AddTower(unsigned int _uiX, unsigned int _uiY, const char* _pkcTowerType);
	void DestroyTower(unsigned int _uiID);
	void DestroyTower(unsigned int _uiX, unsigned int _uiY);	// Prefer this method over the previous one.
	inline CTower& GetTower(unsigned int _uiID);
	inline float GetTowerHeightOffset() const;

	inline unsigned int GetNumTowers() const;
	inline const CTower* const* const GetTowers() const;

	// Map editor stuff.
	bool InitialiseBlankTerrain(unsigned int _uiWidth, unsigned int _uiHeight);
	inline CWaypointManager& GetWaypointManager();

protected:
	CTerrain(const CTerrain&);

	unsigned int GetFreeElement();

private:

	// Member data.
public:	
  
protected:
	CD3DRenderer* m_pRenderer;

	unsigned int m_arruiTileID[TILETYPE_MAX];	// Mesh ID for each tile

	float m_fTileSpacing;
	
	const char* m_pkcTerrain;	// "Terrain" section name when loading (when using .ini).
	const char* m_pkcWaypoints;	// "Waypoints" section name (when using .ini).

	CTile** m_2dTileArray;
	unsigned int m_uiWidth;
	unsigned int m_uiHeight;

	CWaypointManager m_WaypointManager;

	// Tower stuff.
	unsigned int m_uiNumTowers;
	CTower** m_arrpTowers;
	float m_fTowerHeightOffset;	// Offset from terrain (e.g. +6 units above terrain).

private:
};

#include "Terrain.inl"

#endif	// __HYDRA_TERRAIN_H__