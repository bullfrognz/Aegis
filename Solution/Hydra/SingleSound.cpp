#include "SingleSound.h"
#include "INIParser.h"

using namespace irrklang;

CSingleSound::CSingleSound()
:m_ppInstances(0)
,m_fDelay(0.0f)
,m_uiMaxSounds(0)
,m_pFilename(0)
{
}

CSingleSound::~CSingleSound()
{
	if(m_ppInstances != 0)
	{
		for(unsigned int i = 0; i < m_uiMaxSounds; i++)
		{
			if(m_ppInstances[i] != 0)
			{
				m_ppInstances[i]->drop();
				m_ppInstances[i] = 0;
			}
		}
		delete[] m_ppInstances;
	}
}

bool CSingleSound::StartUp(LPSTR _pFileName, unsigned int _uiMaxSounds, float _fDelay, ISoundEngine* _pEngine)
{
	bool bReturn = false;

	if(m_ppInstances == 0)
	{
		m_pFilename = _pFileName;
		m_uiMaxSounds = _uiMaxSounds;
		m_fDelay = _fDelay;
		m_pEngineBackEnd = _pEngine;

		m_ppInstances = new irrklang::ISound*[m_uiMaxSounds];

		if(m_ppInstances != 0)
		{
			for(unsigned int i = 0; i < m_uiMaxSounds; i++)
			{
				m_ppInstances[i] = 0;
			}
			bReturn = true;
		}
	}

	return bReturn;
}

void CSingleSound::Play2D()
{
	int iFreeSlot = -1;
	bool bDelayPased = true;

	for(unsigned int ui = 0; ui < m_uiMaxSounds; ui++)
	{
		if(m_ppInstances[ui] != 0)
		{
			int iMilliseconds = m_ppInstances[ui]->getPlayPosition();
			float TimeSinceStart = iMilliseconds * 0.001f;

			if(TimeSinceStart < m_fDelay && !m_ppInstances[ui]->isFinished())
			{
				bDelayPased = false;
			}

			if(m_ppInstances[ui]->isFinished())
			{
				m_ppInstances[ui]->drop();
				m_ppInstances[ui] = 0;
			}
		}
		
		if(m_ppInstances[ui] == 0)
		{
			iFreeSlot = ui;
		}
	}

	if(bDelayPased == true && iFreeSlot != -1)
	{
		m_ppInstances[iFreeSlot] = m_pEngineBackEnd->play2D(m_pFilename, false, false, true);
	}
}

void CSingleSound::Play3D(float _fX, float _fY, float _fZ)
{
	int iFreeSlot = -1;
	bool bDelayPased = true;

	for(unsigned int ui = 0; ui < m_uiMaxSounds; ui++)
	{
		if(m_ppInstances[ui] != 0)
		{
			int iMilliseconds = m_ppInstances[ui]->getPlayPosition();
			float TimeSinceStart = iMilliseconds * 0.001f;

			if(TimeSinceStart < m_fDelay && !m_ppInstances[ui]->isFinished())
			{
				bDelayPased = false;
			}

			if(m_ppInstances[ui]->isFinished())
			{
				m_ppInstances[ui]->drop();
				m_ppInstances[ui] = 0;
			}
		}
		
		if(m_ppInstances[ui] == 0)
		{
			iFreeSlot = ui;
		}
	}

	if(bDelayPased == true && iFreeSlot != -1)
	{
		vec3df pos(_fX, _fY, _fZ);

		m_ppInstances[iFreeSlot] = m_pEngineBackEnd->play3D(m_pFilename, pos, false, false, true);
	}
}