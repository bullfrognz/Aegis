#ifndef __SOUNDSYSTEM_H__
#define __SOUNDSYSTEM_H__

#include <map>
#include <d3dx9.h>
#include "Third Party\\irrKlang\\irrKlang.h"
#include "SingleSound.h"

class CSoundSystem
{
public:
	~CSoundSystem();

	static CSoundSystem* GetInstance();
	static bool DestroyInstance();

	bool StartUp();
	void ShutDown();

	void NewSound2DInstant(LPSTR _pFileName);
	void NewSound3DInstant(LPSTR _pFileName, float _fX, float _fY, float _fZ);
	
	bool GlobalVolume(float _fVolume);
	float GetVolume();
	bool SetLissenPos(float _fPosX, float _fPosY, float _fPosZ, float _fLookX, float _fLookY, float _fLookZ);

	bool SetBackgroundMusic(LPSTR _pFileName);

private:
	CSoundSystem();
	CSoundSystem(CSoundSystem& _rCopy);

	static CSoundSystem* m_pSystem;
	bool m_bActive;
	irrklang::ISoundEngine* m_pEngineBackEnd;
	irrklang::ISound* m_pBackgroundMusic;
	std::map<LPSTR,CSingleSound> m_pSounds;

	LPSTR* m_ppcLoadedFiles;
	unsigned int m_uiLoadedSounds;

	float m_fGloabalVolume;
	float m_fDelay;
	unsigned int m_uiMaxSounds;
};

#endif