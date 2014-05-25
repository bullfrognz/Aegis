//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	HudDataManager.inl
//	Description	:	Definition of inline CHudDataManager functions.
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// Library includes.
#include <cassert>

CHudDataManager*
CHudDataManager::GetInstance()
{
	if (!sm_pThis)
		sm_pThis = new CHudDataManager;

	return sm_pThis;
}

void
CHudDataManager::DestroyInstance()
{
	delete sm_pThis;
	sm_pThis = 0;
}

const THudData&
CHudDataManager::GetData(EHudGroup _eGroup, unsigned int _uiChild) const
{
	assert(_eGroup < HUDGRP_MAX);
	assert(_uiChild < m_arrData[_eGroup].m_uiNumChildren);
	return m_arrData[_eGroup].m_arrChildData[_uiChild];
}

unsigned int
CHudDataManager::GetNumChildren(EHudGroup _eGroup)
{
	assert(_eGroup < HUDGRP_MAX);
	return m_arrData[_eGroup].m_uiNumChildren;
}

void
CHudDataManager::SetValue(EHudGroup _eGroup, unsigned int _uiChild, unsigned int _uiNewValue)
{
	assert(_eGroup < HUDGRP_MAX);
	assert(_uiChild < m_arrData[_eGroup].m_uiNumChildren);
	m_arrData[_eGroup].m_arrChildData[_uiChild].m_uiValue = _uiNewValue;
}