#ifndef __LIGHTMANAGER_H__
#define __LIGHTMANAGER_H__

#include <d3dx9.h>
#include <vector>
#include "DeviceResetTarget.h"
#include "D3DRenderer.h"

class CD3DRenderer;

enum E_LIGHTTYPE
{
	TYPE,
	DIFFUSE,
	SPECULAR,
	AMBIENT,
	RANGE,
	FALLOFF,
	ATTENUATION0,
	ATTENUATION1,
	ATTENUATION2,
	THETA,
	PHI,
	POSITION,
	DIRECTION,
};

struct LightSource
{
	D3DLIGHT9 m_Light;
	unsigned int m_uiID;
};

class CLightManager : public CDeviceResetTarget
{
public:
	CLightManager();
	~CLightManager();

	bool Initalise(CD3DRenderer* _pRenderer, unsigned int _uiMaxLights);
	void ShutDown();

	int AddLight();
	bool RemoveLight(unsigned int _uiLightID);

	bool TurnOnLight(unsigned int _uiLightID);
	void ForceLight(unsigned int _uiLightID, unsigned int _uiLightPos);

	bool TurnOffLight(bool _bTurnOffByID,unsigned int _iLight);
	void CreateDarkness();

	bool UpdateParam(unsigned int _uiLightID, E_LIGHTTYPE _eParameter, void* _pData);
	bool UpdateLight(unsigned int _uiLightID, D3DLIGHT9* _pLight);

	bool DoesLightIDExist(unsigned int _uiID);

	virtual void OnDeviceLost();
	virtual void OnDeviceReset();

	unsigned int MaxLights();
	unsigned int TotalLights();
private:
	int* m_iActiveLights;
	std::vector<LightSource> m_vecLights;

	CD3DRenderer* m_pRenderer;

	unsigned int m_uiMaxLights;
	unsigned int m_uiTotalLights;
	unsigned int m_uiLastID;

	bool m_bActive;
};

#endif //__LIGHTMANAGER_H__