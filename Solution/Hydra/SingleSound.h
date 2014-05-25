#ifndef __SINGLESOUND_H__
#define __SINGLESOUND_H__

#include <d3dx9.h>
#include "Third Party\\irrKlang\\irrKlang.h"

class CSingleSound
{
public:
	CSingleSound();
	~CSingleSound();

	bool StartUp(LPSTR _pFileName, unsigned int _uiMaxSounds, float _fDelay, irrklang::ISoundEngine* _pEngine);
	void Play2D();
	void Play3D(float _fX, float _fY, float _fZ);
private:
	irrklang::ISound** m_ppInstances;
	float m_fDelay;
	unsigned int m_uiMaxSounds;	
	LPSTR m_pFilename;
	irrklang::ISoundEngine* m_pEngineBackEnd;
};

#endif //__SINGLESOUND_H__