//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	Hud.h
//	Description	:	Declaration of CHud
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

#pragma once
#ifndef __HYDRA_HUD_H__
#define __HYDRA_HUD_H__

// Local includes.
class CD3DRenderer;
class CTower;
class CEnemy;
class CTerrain;
class CPlayer;
class CWaveManager;
struct THudData;

struct THudRect
{
	float m_fTop;
	float m_fLeft;
	float m_fBottom;
	float m_fRight;
};

class CHud
{
	// Member functions.
public:
	CHud();
	~CHud();

	bool Initialise(CD3DRenderer* _pRenderer,
					const CPlayer* _pPlayer,
					const CWaveManager* _pWaveManager,
					unsigned int _uiScreenWidth,
					unsigned int _uiScreenHeight,
					const wchar_t* _pkwMiniMapTextureFile);

	void InitialiseTerrain(const CTerrain& _rTerrain);	// Will pull out scaling information.

	void Draw();
	void DrawTowerMarkers(const CTower* const* const _arrpTowers, unsigned int _uiNumTowers);
	void DrawEnemyMarkers();

	void SetSelectionData(const THudData* _pkData);
	const THudData* GetSelectionData() const;

	void SetExtendedInfo(const CTower* _pTower);

	float GetUsedScreenHeight() const;

	bool OnResolutionChange(unsigned int _uiScreenWidth, unsigned int _uiScreenHeight);

protected:

private:

	// Member data.
public:

protected:
	CD3DRenderer* m_pRenderer;

	const CPlayer* m_pPlayer;
	const CWaveManager* m_pWaveManager;

	const THudData* m_pkSelectionData;
	const CTower* m_pkExtendedInfo;

	float m_fHudWidth;
	float m_fHudHeight;

	// Base HUD image.
	unsigned int m_uiBaseVertexID;	// Vertex buffer mesh ID for the base HUD image.
	int m_iBaseTextureID;
	THudRect m_rectBaseBounds;

	// Mini map image.
	unsigned int m_uiMapVertexID;	// Vertex buffer mesh ID for the mini map image.
	int m_iMapTextureID;
	THudRect m_rectMapBounds;

	// Selected object icon image.
	unsigned int m_uiIconVertexID;
	THudRect m_rectIconBounds;

	// Marker data.
	unsigned int m_uiMarkerVertexID;	// Vertex buffer mesh for rendering dots to indicate where towers and enemies are on the map.
	float m_fMarkerPosScalar;

	// Text data.
	unsigned int m_uiTextTitleID;
	unsigned int m_uiTextBodyID;

	unsigned int m_uiBoxNameID;
	unsigned int m_uiBoxTooltipID;	// Description.
	unsigned int m_uiBoxStatsID;
	unsigned int m_uiBoxPlayerID;

private:
};

#endif	// __HYDRA_HUD_H__