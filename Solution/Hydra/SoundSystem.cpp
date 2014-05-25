#include "SoundSystem.h"
#include "INIParser.h"
using namespace irrklang;

CSoundSystem* CSoundSystem::m_pSystem = 0;

CSoundSystem::CSoundSystem()
:m_bActive(false)
,m_pEngineBackEnd(0)
,m_pBackgroundMusic(0)
,m_ppcLoadedFiles(0)
,m_uiLoadedSounds(0)
{
}

CSoundSystem::~CSoundSystem()
{
	ShutDown();
}

CSoundSystem* CSoundSystem::GetInstance()
{
	if(m_pSystem == 0)
	{
		m_pSystem = new CSoundSystem;
	}

	return m_pSystem;
}

bool CSoundSystem::DestroyInstance()
{
	bool bReturn = false;

	if(m_pSystem != 0)
	{
		delete m_pSystem;
		m_pSystem = 0;
		bReturn = true;
	}

	return bReturn;
}

bool CSoundSystem::StartUp()
{
	bool bReturn = false;

	if(m_bActive == false)
	{
		CINIParser settings;

		settings.LoadINIFile("Ini Files\\Engine.ini");

		float fVolume = 0.5f;

		settings.GetValue("Sound", "BaseVolume", fVolume);
		settings.GetValue("Sound", "SameSoundDelay", m_fDelay);
		settings.GetValue("Sound", "MaxSameSound", m_uiMaxSounds);

		m_pEngineBackEnd = createIrrKlangDevice(ESOD_AUTO_DETECT,
												ESEO_MUTE_IF_NOT_FOCUSED		 |
												ESEO_MULTI_THREADED				 |
												ESEO_LOAD_PLUGINS				 |
												ESEO_USE_3D_BUFFERS				 |
												ESEO_PRINT_DEBUG_INFO_TO_DEBUGGER);

		if(m_pEngineBackEnd != 0)
		{
			m_ppcLoadedFiles = new LPSTR[1];

			m_ppcLoadedFiles[0] = 0;
			m_uiLoadedSounds = 1;

			bReturn = true;
			m_bActive = true;

			GlobalVolume(fVolume);
		}

	}

	return bReturn;
}

void CSoundSystem::ShutDown()
{
	if(m_bActive == true)
	{
		m_pEngineBackEnd->stopAllSounds();

		m_pSounds.clear();

		m_pEngineBackEnd->removeAllSoundSources();

		if (m_pBackgroundMusic)
		{
			m_pBackgroundMusic->stop();
			m_pBackgroundMusic->drop();
			m_pBackgroundMusic = 0;
		}
		//m_pBackgroundMusic->Roll();

		for(unsigned int i = 0; i < m_uiLoadedSounds; i++)
		{
			if(m_ppcLoadedFiles[i] != 0)
			{
				delete[] m_ppcLoadedFiles[i];
				m_ppcLoadedFiles[i] = 0;
			}
		}

		delete[] m_ppcLoadedFiles;

		m_pEngineBackEnd->drop();
		m_pEngineBackEnd = 0;

		m_bActive = false;
	}
}

void CSoundSystem::NewSound2DInstant(LPSTR _pFileName)
{
	if(m_bActive == true)
	{
		int iStringNum = -1;

		for(unsigned int i = 0; i < m_uiLoadedSounds; i++)
		{
			if(m_ppcLoadedFiles[i] != 0)
			{
				int diffrence = strcmp(_pFileName, m_ppcLoadedFiles[i]);

				if(diffrence == 0)
				{
					iStringNum = i;
					break;
				}
			}
		}

		if(iStringNum == -1)
		{
			bool bAdded = false;

			for(unsigned int i = 0; i < m_uiLoadedSounds; i++)
			{
				if(m_ppcLoadedFiles[i] == 0)
				{
					size_t iCharsNeeded = strlen(_pFileName);

					m_ppcLoadedFiles[i] = new char[iCharsNeeded + 1];

					strcpy_s(m_ppcLoadedFiles[i], iCharsNeeded + 1, _pFileName);

					iStringNum = i;

					bAdded = true;

					break;
				}
			}

			if(bAdded == false)
			{
				LPSTR* ppTemp = new LPSTR[m_uiLoadedSounds + 5];

				if(ppTemp != 0)
				{
					for(unsigned int i = 0; i < m_uiLoadedSounds + 5; i++)
					{
						ppTemp[i] = 0;
					}

					for(unsigned int i = 0; i < m_uiLoadedSounds; i++)
					{
						ppTemp[i] = m_ppcLoadedFiles[i];
					}

					m_uiLoadedSounds += 5;

					delete[] m_ppcLoadedFiles;

					m_ppcLoadedFiles = ppTemp;

					for(unsigned int i = 0; i < m_uiLoadedSounds; i++)
					{
						if(m_ppcLoadedFiles[i] == 0)
						{
							size_t iCharsNeeded = strlen(_pFileName);

							m_ppcLoadedFiles[i] = new char[iCharsNeeded + 1];

							strcpy_s(m_ppcLoadedFiles[i], iCharsNeeded + 1, _pFileName);

							iStringNum = i;

							bAdded = true;

							break;
						}
					}
				}
			}
		}
		bool bFound = false;
		
		if(iStringNum != -1)
		{
			bFound = (m_pSounds.count(m_ppcLoadedFiles[iStringNum]) > 0);
		}

		if(bFound && iStringNum != -1)
		{
			m_pSounds[m_ppcLoadedFiles[iStringNum]].Play2D();
		}
		else if(iStringNum != -1)
		{
			m_pSounds[m_ppcLoadedFiles[iStringNum]].StartUp(m_ppcLoadedFiles[iStringNum], m_uiMaxSounds, m_fDelay, m_pEngineBackEnd);

			m_pSounds[m_ppcLoadedFiles[iStringNum]].Play2D();
		}
	}
}

void CSoundSystem::NewSound3DInstant(LPSTR _pFileName, float _fX, float _fY, float _fZ)
{
	if(m_bActive == true)
	{
		int iStringNum = -1;

		for(unsigned int i = 0; i < m_uiLoadedSounds; i++)
		{
			if(m_ppcLoadedFiles[i] != 0)
			{
				int diffrence = strcmp(_pFileName, m_ppcLoadedFiles[i]);

				if(diffrence == 0)
				{
					iStringNum = i;
					break;
				}
			}
		}

		if(iStringNum == -1)
		{
			bool bAdded = false;

			for(unsigned int i = 0; i < m_uiLoadedSounds; i++)
			{
				if(m_ppcLoadedFiles[i] == 0)
				{
					size_t iCharsNeeded = strlen(_pFileName);

					m_ppcLoadedFiles[i] = new char[iCharsNeeded + 1];

					strcpy_s(m_ppcLoadedFiles[i], iCharsNeeded + 1, _pFileName);

					iStringNum = i;

					bAdded = true;

					break;
				}
			}

			if(bAdded == false)
			{
				LPSTR* ppTemp = new LPSTR[m_uiLoadedSounds + 5];

				if(ppTemp != 0)
				{
					for(unsigned int i = 0; i < m_uiLoadedSounds + 5; i++)
					{
						ppTemp[i] = 0;
					}

					for(unsigned int i = 0; i < m_uiLoadedSounds; i++)
					{
						ppTemp[i] = m_ppcLoadedFiles[i];
					}

					m_uiLoadedSounds += 5;

					delete[] m_ppcLoadedFiles;

					m_ppcLoadedFiles = ppTemp;

					for(unsigned int i = 0; i < m_uiLoadedSounds; i++)
					{
						if(m_ppcLoadedFiles[i] == 0)
						{
							size_t iCharsNeeded = strlen(_pFileName);

							m_ppcLoadedFiles[i] = new char[iCharsNeeded + 1];

							strcpy_s(m_ppcLoadedFiles[i], iCharsNeeded + 1, _pFileName);

							iStringNum = i;

							bAdded = true;

							break;
						}
					}
				}
			}
		}

		bool bFound = (m_pSounds.count(m_ppcLoadedFiles[iStringNum]) > 0);

		if(bFound)
		{
			m_pSounds[m_ppcLoadedFiles[iStringNum]].Play3D(_fX, _fY, _fZ);
		}
		else
		{
			m_pSounds[m_ppcLoadedFiles[iStringNum]].StartUp(m_ppcLoadedFiles[iStringNum], m_uiMaxSounds, m_fDelay, m_pEngineBackEnd);

			m_pSounds[m_ppcLoadedFiles[iStringNum]].Play3D(_fX, _fY, _fZ);
		}
	}
}

bool CSoundSystem::GlobalVolume(float _fVolume)
{
	bool bReturn = false;

	if(m_bActive == true)
	{
		if(_fVolume > 1.0f)
		{
			_fVolume = 1.0f;
		}
		if(_fVolume < 0.0f)
		{
			_fVolume = 0.0f;
		}

		m_pEngineBackEnd->setSoundVolume(_fVolume);

		m_fGloabalVolume = _fVolume;

		bReturn = true;

		CINIParser temp;
		char pTemp[256];

		temp.LoadINIFile("Ini Files\\Engine.ini");

		sprintf_s(pTemp, 256, "%f", _fVolume);
		temp.AddValue("Sound", "BaseVolume", pTemp);

		temp.SaveINIFile("Ini Files\\Engine.ini");
	}

	return bReturn;
}

float CSoundSystem::GetVolume()
{
	return m_fGloabalVolume;
}

bool CSoundSystem::SetLissenPos(float _fPosX, float _fPosY, float _fPosZ, float _fLookX, float _fLookY, float _fLookZ)
{
	bool bReturn = false;

	if(m_bActive == true)
	{
		vec3df pos(_fPosX, _fPosY, _fPosZ);
		vec3df look(_fLookX, _fLookY, _fLookZ);

		m_pEngineBackEnd->setListenerPosition(pos, look);

		bReturn = true;
	}

	return bReturn;
}

bool CSoundSystem::SetBackgroundMusic(LPSTR _pFileName)
{
	bool bReturn = false;

	if(m_bActive == true)
	{
		if(m_pBackgroundMusic != 0)
		{
			m_pBackgroundMusic->drop();
			m_pBackgroundMusic = 0;
		}
		m_pBackgroundMusic = m_pEngineBackEnd->play2D(_pFileName, true, false, true);

		bReturn = true;
	}

	return bReturn;
}