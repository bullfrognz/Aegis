#include "LightManager.h"
#include "D3DRenderer.h"
#include "DeviceManager.h"

CLightManager::CLightManager()
:m_iActiveLights(0)
,m_pRenderer(0)
,m_uiMaxLights(0)
,m_uiTotalLights(0)
,m_uiLastID(0)
,m_bActive(false)
{
}

CLightManager::~CLightManager()
{
	ShutDown();
}
/**
*
* Starts the light manager and sets the max active lights.
*
* @author Joshua Print
* @param _CD3DRenderer Pointer to a renderer that owns this manager.
* @param _uiMaxLights Unsigned int stateing the max lights this manager should allow, 
*                     use the caps.MaxActiveLights to sync it with hardware limits.
* @return True if setup was successful.
*
*/
bool CLightManager::Initalise(CD3DRenderer* _pRenderer, unsigned int _uiMaxLights)
{
	if(_pRenderer != 0 && _uiMaxLights != 0)
	{
		m_pRenderer = _pRenderer;

		if(_uiMaxLights > 8)
		{
			m_uiMaxLights = 8;
		}
		else
		{
			m_uiMaxLights = _uiMaxLights;
		}

		m_iActiveLights = new int[m_uiMaxLights];

		for(unsigned int i = 0; i < m_uiMaxLights; i++)
		{
			m_iActiveLights[i] = -1;
		}

		m_bActive = true;
	}

	return m_bActive;
}
/**
*
* Shuts down the manager and destroys all lights, active or otherwise.
*
* @author Joshua Print
* @return Nothing.
*
*/
void CLightManager::ShutDown()
{
	if(m_bActive == true)
	{
		delete[] m_iActiveLights;
		m_iActiveLights = 0;

		m_pRenderer = 0;

		m_uiMaxLights = 0;

		m_uiLastID = 0;

		m_vecLights.clear();

		m_bActive = false;
	}
}

/**
*
* Creates a new default directinal light.
*
* @author Joshua Print
* @return ID of the new light so it can be set or its settings changed.
*
*/
int CLightManager::AddLight()
{
	int iReturn = -1;

	if(m_bActive == true)
	{
		LightSource sTemp;

		sTemp.m_Light.Type = D3DLIGHT_DIRECTIONAL;
		sTemp.m_Light.Diffuse.a = 1.0f;
		sTemp.m_Light.Diffuse.r = 1.0f;
		sTemp.m_Light.Diffuse.g = 1.0f;
		sTemp.m_Light.Diffuse.b = 1.0f;

		sTemp.m_Light.Specular.a = 1.0f;
		sTemp.m_Light.Specular.r = 0.0f;
		sTemp.m_Light.Specular.g = 0.0f;
		sTemp.m_Light.Specular.b = 0.0f;

		sTemp.m_Light.Ambient.a = 1.0f;
		sTemp.m_Light.Ambient.r = 1.0f;
		sTemp.m_Light.Ambient.g = 1.0f;
		sTemp.m_Light.Ambient.b = 1.0f;

		sTemp.m_Light.Position.x = 0.0f;
		sTemp.m_Light.Position.y = 0.0f;
		sTemp.m_Light.Position.z = 0.0f;

		sTemp.m_Light.Direction.x = 0.3f;
		sTemp.m_Light.Direction.y = -1.0f;
		sTemp.m_Light.Direction.z = 0.1f;

		sTemp.m_Light.Range = 0.0f;
		sTemp.m_Light.Falloff = 0.0f;
		sTemp.m_Light.Attenuation0 = 0.0f;
		sTemp.m_Light.Attenuation1 = 0.0f;
		sTemp.m_Light.Attenuation2 = 0.0f;
		sTemp.m_Light.Theta = 0.0f;
		sTemp.m_Light.Phi = 0.0f;

		sTemp.m_uiID = m_uiLastID++;

		m_uiTotalLights++;

		m_vecLights.push_back(sTemp);

		iReturn = sTemp.m_uiID;
	}

	return iReturn;
}
/**
*
* Removes a light from the manager.
*
* @author Joshua Print
* @param _uiLightID ID of the light you want to destroy
* @return True if the light was found and removed.
*
*/
bool CLightManager::RemoveLight(unsigned int _uiLightID)
{
	bool bReturn = false;

	std::vector<LightSource>::iterator itter = m_vecLights.begin();

	for(unsigned int i = 0; i < m_uiTotalLights; i++)
	{
		if(m_vecLights[i].m_uiID == _uiLightID)
		{
			itter += i;
			m_vecLights.erase(itter);
			m_uiTotalLights--;
			bReturn = true;
			break;
		}
	}
	
	return bReturn;
}
/**
*
* Sets a light active in the first unused active lights spot.
*
* @author Joshua Print
* @param _uiLightID ID of the light yu want to activate.
* @return True if light is found and set.
*
*/
bool CLightManager::TurnOnLight(unsigned int _uiLightID)
{
	bool bReturn = false;

	for(unsigned int i = 0;i < m_uiMaxLights;i++)
	{
		if(m_iActiveLights[i] == -1)
		{
			m_iActiveLights[i] = _uiLightID;
			bReturn = true;

			D3DLIGHT9* pTemp = 0;

			for(unsigned int j = 0; j < m_vecLights.size(); j++)
			{
				if(m_vecLights[j].m_uiID == _uiLightID)
				{
					pTemp = &(m_vecLights[j].m_Light);
				}
			}

			if(pTemp != 0)
			{
				m_pRenderer->GetDeviceManager().SetLight(i, pTemp);
				m_pRenderer->GetDeviceManager().SetLightEnabled(i, true);
			}

			break;
		}
	}

	return bReturn;
}
/**
*
* Forces a light into a set spot in the lighting array, 
* turning off any light that was there already.
*
* @author Joshua Print
* @param _uiLightID ID of the light to activate.
* @param _uiLightPos what slot in the array you want to set this light to.
* @return True if the light is found, the array position is valid and the light was set.
*
*/
void CLightManager::ForceLight(unsigned int _uiLightID, unsigned int _uiLightPos)
{
	if(m_bActive == true && _uiLightPos < m_uiMaxLights)
	{
		m_iActiveLights[_uiLightPos] = _uiLightID;

		m_pRenderer->GetDeviceManager().SetLight(_uiLightPos, &(m_vecLights[_uiLightID].m_Light));
		m_pRenderer->GetDeviceManager().SetLightEnabled(_uiLightPos, true);
	}
}
/**
*
* Turns of a light eather by ID or position in the array.
*
* @author Joshua Print
* @param _bTurnOffByID True if you want to turn of a light, false if you want to disable a position in the array.
* @param _uiLight Eather a light ID or an array position depending on the first param.
* @return True if the light was found and turned off or the light position is valid and was disabled.
*
*/
bool CLightManager::TurnOffLight(bool _bTurnOffByID,unsigned int _iLight)
{
	bool bReturn = false;

	if(m_bActive == true)
	{
		if(_bTurnOffByID == true)
		{
			for(unsigned int i = 0;i < m_uiMaxLights;i++)
			{
				if(m_iActiveLights[i] == _iLight)
				{
					m_iActiveLights[i] = -1;
					bReturn = true;
					m_pRenderer->GetDeviceManager().SetLightEnabled(i, false);
					break;
				}
			}
		}
		else
		{
			if(_iLight < m_uiMaxLights)
			{
				m_iActiveLights[_iLight] = -1;
				m_pRenderer->GetDeviceManager().SetLightEnabled(_iLight, false);
				bReturn = true;
			}
		}
	}

	return bReturn;
}
/**
*
* Turns off all Active lights.
*
* @author Joshua Print
* @return Nothing.
*
*/
void CLightManager::CreateDarkness()
{
	for(unsigned int i = 0;i < m_uiMaxLights;i++)
	{
		m_iActiveLights[i] = -1;

		m_pRenderer->GetDeviceManager().SetLightEnabled(i, false);
	}
}
/**
*
* Updates a light on a single light parameter.
*
* @author Joshua Print
* @param _uiLightID ID of the light to update.
* @param _eParameter A member of the E_LIGHTTYPE enum describing what the seting value is
* @param _pData Pointer to the new parameter data
* @return True if the light was found and the parameter was set.
*
*/
bool CLightManager::UpdateParam(unsigned int _uiLightID, E_LIGHTTYPE _eParameter, void* _pData)
{
	bool bReturn = false;

	for(unsigned int i = 0; i < m_uiTotalLights; i++)
	{
		if(m_vecLights[i].m_uiID == _uiLightID)
		{
			switch(_eParameter)
			{
			case TYPE:
				{
					m_vecLights[i].m_Light.Type = *(reinterpret_cast<D3DLIGHTTYPE*>(_pData));
					bReturn = true;
					break;
				}
			case DIFFUSE:
				{
					m_vecLights[i].m_Light.Diffuse = *(reinterpret_cast<D3DCOLORVALUE*>(_pData));
					bReturn = true;
					break;
				}
			case SPECULAR:
				{
					m_vecLights[i].m_Light.Specular = *(reinterpret_cast<D3DCOLORVALUE*>(_pData));
					bReturn = true;
					break;
				}
			case AMBIENT:
				{
					m_vecLights[i].m_Light.Ambient = *(reinterpret_cast<D3DCOLORVALUE*>(_pData));
					bReturn = true;
					break;
				}
			case RANGE:
				{
					m_vecLights[i].m_Light.Range = *(reinterpret_cast<float*>(_pData));
					bReturn = true;
					break;
				}
			case FALLOFF:
				{
					m_vecLights[i].m_Light.Falloff = *(reinterpret_cast<float*>(_pData));
					bReturn = true;
					break;
				}
			case ATTENUATION0:
				{
					m_vecLights[i].m_Light.Attenuation0 = *(reinterpret_cast<float*>(_pData));
					bReturn = true;
					break;
				}
			case ATTENUATION1:
				{
					m_vecLights[i].m_Light.Attenuation1 = *(reinterpret_cast<float*>(_pData));
					bReturn = true;
					break;
				}
			case ATTENUATION2:
				{
					m_vecLights[i].m_Light.Attenuation2 = *(reinterpret_cast<float*>(_pData));
					bReturn = true;
					break;
				}
			case THETA:
				{
					m_vecLights[i].m_Light.Theta = *(reinterpret_cast<float*>(_pData));
					bReturn = true;
					break;
				}
			case PHI:
				{
					m_vecLights[i].m_Light.Phi = *(reinterpret_cast<float*>(_pData));
					bReturn = true;
					break;
				}
			case POSITION:
				{
					m_vecLights[i].m_Light.Position = *(reinterpret_cast<D3DVECTOR*>(_pData));
					bReturn = true;
					break;
				}
			case DIRECTION:
				{
					m_vecLights[i].m_Light.Direction = *(reinterpret_cast<D3DVECTOR*>(_pData));
					bReturn = true;
					break;
				}
			}
			break;
		}
	}

	return bReturn;
}
/**
*
* Replaces an entire light with a defined light.
*
* @author Joshua Print
* @param _uiLightID ID of the light to replace.
* @param _pLight Pointer to the new light.
* @return True if the light is found and replaced.
*
*/
bool CLightManager::UpdateLight(unsigned int _uiLightID, D3DLIGHT9* _pLight)
{
	bool bReturn = false;

	for(unsigned int i = 0; i < m_uiTotalLights; i++)
	{
		if(m_vecLights[i].m_uiID == _uiLightID)
		{
			m_vecLights[i].m_Light = *_pLight;
			bReturn = true;
			break;
		}
	}

	return bReturn;
}
/**
*
* Checks if the light has been created.
*
* @author Joshua Print
* @param _uiID ID you want to check.
* @return True if the light exists.
*
*/
bool CLightManager::DoesLightIDExist(unsigned int _uiID)
{
	bool bReturn = false;

	for(unsigned int i = 0; i < m_uiTotalLights; i++)
	{
		if(m_vecLights[i].m_uiID == _uiID)
		{
			bReturn = true;
			break;
		}
	}

	return bReturn;
}
/**
*
* Returns the max number of lights that can be set at once.
*
* @author Joshua Print
* @return The max number of lights that can be set at once.
*
*/
unsigned int CLightManager::MaxLights()
{
	return m_uiMaxLights;
}
/**
*
* Gets the total number of lights made.
*
* @author Joshua Print
* @return The current number of Lights created through this manager.
*
*/
unsigned int CLightManager::TotalLights()
{
	return m_uiTotalLights;
}
/**
*
* Code that gets run when the device is lost.
*
* @author Joshua Print
* @return Nothing.
*
*/
void CLightManager::OnDeviceLost()
{
	//WOO! COMMENTS!
}
/**
*
* Code thats run when the device is restored, simply resets all active lights back on the device.
*
* @author Joshua Print
* @return Nothing.
*
*/
void CLightManager::OnDeviceReset()
{
	if(m_bActive == true)
	{
		for(unsigned int i = 0; i < m_uiMaxLights;i++)
		{
			if(m_iActiveLights[i] > 0)
			{
				m_pRenderer->GetDeviceManager().SetLight(i, &(m_vecLights[i].m_Light));
				m_pRenderer->GetDeviceManager().SetLightEnabled(i, true);
			}
			else
			{
				m_pRenderer->GetDeviceManager().SetLightEnabled(i, false);
			}
		}
	}
}