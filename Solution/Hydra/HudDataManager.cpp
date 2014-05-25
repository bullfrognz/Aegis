//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	HudDataManager.cpp
//	Description	:	Definition of CHudDataManager
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

// Library includes.
#include <cassert>

// Local includes.
#include "Utility.h"
#include "TextureManager.h"
#include "INIParser.h"

// This include.
#include "HudDataManager.h"

CHudDataManager* CHudDataManager::sm_pThis = 0;

CHudDataManager::CHudDataManager()
{
	for (unsigned int ui = 0; ui < HUDGRP_MAX; ++ui)
	{
		m_arrData[ui].m_arrChildData = 0;
		m_arrData[ui].m_pkcFileName = 0;
		m_arrData[ui].m_uiNumChildren = 0;
	}
}

CHudDataManager::~CHudDataManager()
{
	Shutdown();
}

/**
*
* Cleans up the Hud Data Manager, so it can be reinitialised
*
* @author Jade Abbott
*
*/
void
CHudDataManager::Shutdown()
{
	for (unsigned int uiGroup = 0; uiGroup < HUDGRP_MAX; ++uiGroup)
	{
		for (unsigned int uiChild = 0; uiChild < m_arrData[uiGroup].m_uiNumChildren; ++uiChild)
		{
			delete[] m_arrData[uiGroup].m_arrChildData[uiChild].m_pcSectionHeader;
			delete[] m_arrData[uiGroup].m_arrChildData[uiChild].m_pcName;
			delete[] m_arrData[uiGroup].m_arrChildData[uiChild].m_pcTooltip;
			delete m_arrData[uiGroup].m_arrChildData[uiChild].m_pExtraData;
		}

		delete[] m_arrData[uiGroup].m_arrChildData;
		m_arrData[uiGroup].m_arrChildData = 0;
		m_arrData[uiGroup].m_uiNumChildren = 0;
	}
}

/**
*
* Initialises the Hud Data Manager
*
* @author Jade Abbott
*
*/
bool
CHudDataManager::Initialise(CTextureManager& _rTextureManager)
{
	Shutdown();

	bool bSuccess = true;

	// Initialise data for each group.
	m_arrData[HUDGRP_TOWER].m_pkcFileName = "Ini Files\\Tower Data.ini";	// The file to open.
	m_arrData[HUDGRP_MISC].m_pkcFileName = "Ini Files\\Misc Data.ini";

	CINIParser parser;
	std::string strTemp;
	std::wstring wstrIconTextureAddress;

	for (unsigned int uiGroup = 0; uiGroup < HUDGRP_MAX; ++uiGroup)
	{
		if (!parser.LoadINIFile(m_arrData[uiGroup].m_pkcFileName))
			return false;

		bool bAnotherFound = false;
		char cBuffer[50];
		std::vector<std::string> vecSectionNames;

		// Count the elements, and store in a vector for future reference.
		do
		{
			sprintf_s(cBuffer, 50, "Item%i", vecSectionNames.size());
			bAnotherFound = parser.GetValue("Index", cBuffer, strTemp);

			if (bAnotherFound)
				vecSectionNames.push_back(strTemp);
		} while (bAnotherFound);

		if (vecSectionNames.size() > 0)
		{
			m_arrData[uiGroup].m_arrChildData = new THudData[vecSectionNames.size()];
			if (!m_arrData[uiGroup].m_arrChildData)
				continue;

			m_arrData[uiGroup].m_uiNumChildren = static_cast<unsigned int>(vecSectionNames.size());

			for (unsigned int ui = 0; ui < m_arrData[uiGroup].m_uiNumChildren; ++ui)
			{
				// Copy the section header.
				m_arrData[uiGroup].m_arrChildData[ui].m_pcSectionHeader = new char[vecSectionNames[ui].length() + 1];
				if (m_arrData[uiGroup].m_arrChildData[ui].m_pcSectionHeader)
					memcpy(m_arrData[uiGroup].m_arrChildData[ui].m_pcSectionHeader, vecSectionNames[ui].c_str(), vecSectionNames[ui].length() + 1);

				// Set all other information to invalid.
				m_arrData[uiGroup].m_arrChildData[ui].m_iIconTextureID = Utility::INVALID_ID;
				m_arrData[uiGroup].m_arrChildData[ui].m_uiValue = 0;
				m_arrData[uiGroup].m_arrChildData[ui].m_pcTooltip = 0;
				m_arrData[uiGroup].m_arrChildData[ui].m_pcName = 0;
				m_arrData[uiGroup].m_arrChildData[ui].m_pExtraData = 0;
			}
		}

		for (unsigned int uiChild = 0; uiChild < m_arrData[uiGroup].m_uiNumChildren; ++uiChild)
		{
			THudData& rChild = m_arrData[uiGroup].m_arrChildData[uiChild];

			//Get cost of upgrade/sell/etc...
			parser.GetValue(vecSectionNames[uiChild].c_str(), "Value", rChild.m_uiValue);

			// Get name.
			if (parser.GetValue(vecSectionNames[uiChild].c_str(), "Name", strTemp))
			{
				assert(!rChild.m_pcName);
				const size_t kuiNameLength = strTemp.length() + 1;	// Length() doesn't inlcude the null terminator.

				rChild.m_pcName = new char[kuiNameLength];
				if (rChild.m_pcName)
				{
					memcpy(rChild.m_pcName, strTemp.c_str(), sizeof(char) * kuiNameLength);
				}
			}

			// Get description.
			if (parser.GetValue(vecSectionNames[uiChild].c_str(), "Tooltip", strTemp))
			{
				assert(!rChild.m_pcTooltip);
				const size_t kuiStringLength = strTemp.length() + 1;	// Length() doesn't inlcude the null terminator.
				rChild.m_pcTooltip = new char[kuiStringLength];
				if (rChild.m_pcTooltip)
				{
					memcpy(rChild.m_pcTooltip, strTemp.c_str(), sizeof(char) * kuiStringLength);
				}
			}

			// Get file address of the icon texture.
			if (parser.GetValue(vecSectionNames[uiChild].c_str(), "IconTexture", wstrIconTextureAddress))
			{
				rChild.m_iIconTextureID = _rTextureManager.LoadTextureFile(wstrIconTextureAddress.c_str());
			}

			// Check if this has extended information.
			bool bHasExtraInfo = false;
			float fMinDamage = 0.0f;
			float fMaxDamage = 0.0f;
			float fRange = 0.0f;
			float fFireDelay = 0.0f;
			bHasExtraInfo = parser.GetValue(vecSectionNames[uiChild].c_str(), "MinDamage", fMinDamage) ? true : bHasExtraInfo;
			bHasExtraInfo = parser.GetValue(vecSectionNames[uiChild].c_str(), "MaxDamage", fMaxDamage) ? true : bHasExtraInfo;
			bHasExtraInfo = parser.GetValue(vecSectionNames[uiChild].c_str(), "Range", fRange) ? true : bHasExtraInfo;
			bHasExtraInfo = parser.GetValue(vecSectionNames[uiChild].c_str(), "FireRate", fFireDelay) ? true : bHasExtraInfo;	// FireRate in the .ini is actually the delay between shots.

			if (bHasExtraInfo)
			{
				rChild.m_pExtraData = new THudExtraData;
				if (rChild.m_pExtraData)
				{
					rChild.m_pExtraData->m_fFireRate = fFireDelay > 0.0f ? 1.0f / fFireDelay : 0.0f;
					rChild.m_pExtraData->m_fMinDamage = fMinDamage;
					rChild.m_pExtraData->m_fMaxDamage = fMaxDamage;
					rChild.m_pExtraData->m_fRange = fRange;
				}
			}
		}
	}

	return true;
}

/**
*
* @author Jade Abbott
*
*/
const THudData*
CHudDataManager::GetData(EHudGroup _eGroup, const char* _pkcSectionHeader) const
{
	assert(_eGroup < HUDGRP_MAX);

	if (!_pkcSectionHeader)
		return 0;

	for (unsigned int ui = 0; ui < m_arrData[_eGroup].m_uiNumChildren; ++ui)
	{
		const char* pkcSectionHeader = m_arrData[_eGroup].m_arrChildData[ui].m_pcSectionHeader;
		assert(pkcSectionHeader);

		if (!*pkcSectionHeader)	// Ignore empty string.
			continue;

		// Compare strings.
		unsigned int uiChar = 0;
		do
		{
			if (!pkcSectionHeader[uiChar])	// If the end of the string has been reached, the strings match.
				return &m_arrData[_eGroup].m_arrChildData[ui];
			else if (pkcSectionHeader[uiChar] != _pkcSectionHeader[uiChar])
				break;	// Stop comparing the string, continue checking others.
		} while (++uiChar);	// Prevents infinite loops.
	}

	return 0;
}