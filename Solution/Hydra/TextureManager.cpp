#include "TextureManager.h"
#include "Macros.h"
#include "Utility.h"
#include "StrUtilities.h"
#include "D3DRenderer.h"
#include "DeviceManager.h"

CTextureManager::CTextureManager()
:m_pDevice(0)
,m_uiTotalTextures(0)
,m_pRenderer(0)
,m_uiNextTextureID(0)
{
}

CTextureManager::~CTextureManager()
{
	ShutDown();
}

/**
*
* Initialises the texture manager.
*
* @author Joshua Print
* @param _pDevice The rendering device (needed to create textures).
* @param _pRenderer The renderer class that holds this manager, needed for state changes.
* @return True if initialisation was successful.
*
*/
bool CTextureManager::Initalise(IDirect3DDevice9* _pDevice, CD3DRenderer* _pRenderer)
{
	bool bCreated = false;

	if(_pDevice != 0)
	{
		m_pDevice = _pDevice;
		m_pDevice->AddRef();

		m_pRenderer = _pRenderer;

		bCreated = true;
	}

	return(bCreated);
}

/**
*
* Shuts down the texture manager and removes all textures
*
* @author Joshua Print
* @return Nothing
*
*/
void CTextureManager::ShutDown()
{
	for(unsigned int i = 0; i < m_uiTotalTextures; i++)
	{
		if(m_pTexture[i] != 0)
		{
			m_pTexture[i]->m_pTexture->Release();
			delete m_pTexture[i];
		}
	}

	m_pTexture.clear();

	FW_RELEASE(m_pDevice);
}

/**
*
* Deletes a texture set and releases all contained textures
*
* @author Joshua Print
* @param _iID ID of the texture set to destroy.
* @return Nothing.
*
*/
void CTextureManager::RemoveTexture(int _iID)
{
	std::vector<TextureItem*>::iterator itter = m_pTexture.begin();

	for(unsigned int i = 0; i < m_uiTotalTextures; i++)
	{
		if(m_pTexture[i]->m_uiID == _iID)
		{
			m_pTexture[i]->m_pTexture->Release();
			delete m_pTexture[i];
			itter += i;
			m_pTexture.erase(itter);
			m_uiTotalTextures--;
			break;
		}
	}
}
/**
*
* Loads a texture from a file, into the given texture set at the given stage.
*
* @author Joshua Print
* @param _iID ID of the texture set to add the texture to
* @param _uiStage The stage to set the texture to.
* @param _pcFileName File name of the texture to be added
* @return True if loading was seccessful
*
*/
int CTextureManager::LoadTextureFile(LPCWSTR _pcFileName)
{
	bool bReturn = false;

	unsigned int uiTextureId = Utility::INVALID_ID;

	bool bTextureLoaded = HasTextureBeenLoaded(_pcFileName, uiTextureId);

	if (bTextureLoaded == true)
	{
		return (uiTextureId);
	}
	else
	{
		TextureItem* pTemp = new TextureItem;

		if(pTemp != 0)
		{
			HRESULT result = D3DXCreateTextureFromFile(m_pDevice, _pcFileName, &(pTemp->m_pTexture));
			
			if(!FAILED(result))
			{
				pTemp->m_uiID = m_uiNextTextureID++;
				uiTextureId = pTemp->m_uiID;

				m_pTexture.push_back(pTemp);

				m_uiTotalTextures++;

				CacheTextureFile(_pcFileName, uiTextureId);
			}
			else
			{
				delete pTemp;
			}
		}

		return uiTextureId;
	}
}

int CTextureManager::LoadTextureMemory(LPDIRECT3DTEXTURE9 _pTexture)
{
	bool bReturn = false;

	int iReturn = -1;

	TextureItem* pTemp = new TextureItem;

	if(pTemp != 0 && _pTexture != 0)
	{
		pTemp->m_pTexture = _pTexture;
		pTemp->m_uiID = m_uiNextTextureID++;
		iReturn = pTemp->m_uiID;

		m_pTexture.push_back(pTemp);

		m_uiTotalTextures++;
	}
	else if(pTemp != 0)
	{
		delete pTemp;
	}

	return iReturn;
}

/**
*
* Sends a texture set to the device, allowing it to be drawn on objects.
*
* @author Joshua Print
* @param _iID ID of the texture set to send to the device
* @return True if setting successful.
*
*/
bool CTextureManager::SetTexture(int _iID)
{
	m_pRenderer->GetDeviceManager().SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
	bool bReturn = false;

	TextureItem* pTemp = 0;

	for(unsigned int i = 0; i < m_uiTotalTextures && _iID >= 0; i++)
	{
		if(m_pTexture[i]->m_uiID == _iID)
		{
			pTemp = m_pTexture[i];
			break;
		}
	}

	if(pTemp != 0)
	{
		m_pRenderer->GetDeviceManager().SetStageTexture(0, pTemp->m_pTexture);
		bReturn = true;
	}
	else
	{
		m_pRenderer->GetDeviceManager().SetStageTexture(0, 0);
	}

	return bReturn;
}

LPDIRECT3DTEXTURE9 CTextureManager::GetTexture(int _iID)
{
	TextureItem* pTemp = 0;

	for(unsigned int i = 0; i < m_uiTotalTextures && _iID >= 0; i++)
	{
		if(m_pTexture[i]->m_uiID == _iID)
		{
			pTemp = m_pTexture[i];
			break;
		}
	}

	if(pTemp != 0)
	{
		return pTemp->m_pTexture;
	}
	else
	{
		return 0;
	}
}










/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will check if the texture has already been loaded and will return the texture id if it has.
*
* @author Bryce Booth
* @param _wcpTextureFile The texture file to check
* @param _uirLoadedTextureId The texture id of the already loaded texture
* @return If the texture has been loaded or not
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CTextureManager::HasTextureBeenLoaded(LPCWSTR _wcpTextureFile, unsigned int& _uirLoadedTextureId)
{
	//Conver to char
	char* cpTextureFile = 0;
	StrUtilities::ConvertToChar(_wcpTextureFile, cpTextureFile);
	

	std::string strTextureFile = cpTextureFile;


	delete[] cpTextureFile;
	cpTextureFile = 0;


	std::map<std::string, unsigned int>::iterator iterTextureId;
	iterTextureId = m_mapLoadedTextures.find(strTextureFile);


	if (iterTextureId != m_mapLoadedTextures.end())
	{
		_uirLoadedTextureId = (*iterTextureId).second;


		return (true);
	}
	else
	{
		_uirLoadedTextureId = Utility::INVALID_ID;


		return (false);
	}
}










/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will cache the loaded texture file so it wont be loaded again.
*
* @author Bryce Booth
* @param _wcpTextureFile The texture file to remember
* @param _uirLoadedTextureId The texture id of the loaded texture
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CTextureManager::CacheTextureFile(LPCWSTR _wcpTextureFile, unsigned int _uiTextureId)
{
	//Conver to char
	char* cpTextureFile = 0;
	StrUtilities::ConvertToChar(_wcpTextureFile, cpTextureFile);
	

	std::string strTextureFile = cpTextureFile;


	delete[] cpTextureFile;
	cpTextureFile = 0;


	m_mapLoadedTextures.insert( std::pair<std::string, unsigned int>(strTextureFile, _uiTextureId) );
}