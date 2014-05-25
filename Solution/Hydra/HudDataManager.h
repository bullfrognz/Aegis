//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	HudDataManager.h
//	Description	:	Declaration of CHudDataManager
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

#pragma once
#ifndef __HYDRA_HUDDATAMANAGER_H__
#define __HYDRA_HUDDATAMANAGER_H__

// Library includes.

// Local includes.
class CTextureManager;

enum EHudGroup
{
	HUDGRP_TOWER,
	HUDGRP_MISC,	// E.g. Selling towers.
	HUDGRP_MAX
};

struct THudExtraData
{
	float m_fMinDamage;
	float m_fMaxDamage;
	float m_fRange;
	float m_fFireRate;	// In shots per second.
};

struct THudData	// Data belonging to each child of a group.
{
	char* m_pcSectionHeader;

	int m_iIconTextureID;
	unsigned int m_uiValue;	// Value in currency.
	char* m_pcName;	// E.g. "Frost Tower".
	char* m_pcTooltip;

	THudExtraData* m_pExtraData;
};

struct THudGroup
{
	const char* m_pkcFileName;	// .ini to open.
	unsigned int m_uiNumChildren;
	THudData* m_arrChildData;
};

class CHudDataManager
{
	// Member functions.
public:
	~CHudDataManager();

	inline static CHudDataManager* GetInstance();
	inline static void DestroyInstance();

	void Shutdown();

	bool Initialise(CTextureManager& _rTextureManager);

	inline const THudData& GetData(EHudGroup _eGroup, unsigned int _uiChild) const;
	const THudData* GetData(EHudGroup _eGroup, const char* _pkcSectionHeader) const;

	inline unsigned int GetNumChildren(EHudGroup _eGroup);

	inline void SetValue(EHudGroup _eGroup, unsigned int _uiChild, unsigned int _uiNewValue);

protected:
	CHudDataManager();

private:

	// Member data.
public:

protected:
	static CHudDataManager* sm_pThis;

	THudGroup m_arrData[HUDGRP_MAX];

private:
};

#include "HudDataManager.inl"

#endif	// __HYDRA_HUDDATAMANAGER_H__