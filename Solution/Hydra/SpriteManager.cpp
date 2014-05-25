#include "SpriteManager.h"
#include "DeviceManager.h"
#include "D3DRenderer.h"
#include "WorldMatrix.h"
#include "Macros.h"
#include "texturemanager.h"
#include "Application.h"
#include "DeviceManager.h"

unsigned int CSpriteManager::m_uiNextID;

CSpriteManager::CSpriteManager()
:m_pTextureSource(0)
,m_pRenderer(0)
,m_pSpriteInterface(0)
,m_uiTotalSprites(0)
{
}

CSpriteManager::~CSpriteManager()
{
	ShutDown();
}

bool CSpriteManager::Initalise(CTextureManager* _pTextureSource, CD3DRenderer* _pRenderer, LPD3DXSPRITE _pSprite)
{
	bool bReturn = false;

	if(_pTextureSource != 0 && _pRenderer != 0 && _pSprite != 0)
	{
		m_pTextureSource = _pTextureSource;
		m_pRenderer = _pRenderer;

		m_pSpriteInterface = _pSprite;

		bReturn = true;
	}

	return bReturn;
}

void CSpriteManager::ShutDown()
{
	EraseAll();

	if(m_pSpriteInterface != 0)
	{
		m_pSpriteInterface->Release();
		m_pSpriteInterface = 0;
	}
}

void CSpriteManager::EraseAll()
{
	for(unsigned int i = 0; i < m_SpriteData.size(); i++)
	{
		delete m_SpriteData[i];
		m_SpriteData[i] = 0;
	}

	m_SpriteData.clear();

	m_uiTotalSprites = 0;
}

CVector3 CSpriteManager::GetPositionScaled(unsigned int _iID)
{
	CVector3 Centre;

	Centre.x = 0.0f;
	Centre.y = 0.0f;
	Centre.z = 0.0f;

	for(unsigned int i = 0; i < m_uiTotalSprites; i++)
	{
		if(m_SpriteData[i]->GetID() == _iID)
		{
			m_SpriteData[i]->GetWorldMatrix().GetPosition(Centre);
		}
	}

	int iWidth = CApplication::GetInstance().GetGameWindow().GetClientWidth();
	int iHeight = CApplication::GetInstance().GetGameWindow().GetClientHeight();

	Centre.x *= (iWidth / 1280.0f);
	Centre.y *= (iHeight / 1024.0f);

	return Centre;
}

void CSpriteManager::Draw()
{
	DrawWorld();
	DrawScreen();
}
void CSpriteManager::DrawScreen()
{
	//Setup default variables
	HRESULT hResult = S_OK;
	IDirect3DTexture9* d3dpTexture9 = 0;
	unsigned int uiTextureId  = 0;
	unsigned int uiNumSprites = static_cast<unsigned int>(m_SpriteData.size()); 
	CVector3 v3SpritePosition;

	hResult = m_pSpriteInterface->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK |
										D3DXSPRITE_ALPHABLEND |
										D3DXSPRITE_DO_NOT_ADDREF_TEXTURE);


	LOG_FATALERROR(FAILED(hResult), "Could not begin sprite drawing.");


	for(unsigned int i = 0; i < uiNumSprites; ++i)
	{
		m_SpriteData[i]->GetWorldMatrix().GetPosition(v3SpritePosition);


		if(m_SpriteData[i]->IsVisible() == true && m_SpriteData[i]->IsWorldCords() == false)
		{
			CWorldMatrix temp = m_SpriteData[i]->GetWorldMatrix();

			int iWidth = CApplication::GetInstance().GetGameWindow().GetClientWidth();
			int iHeight = CApplication::GetInstance().GetGameWindow().GetClientHeight();

			D3DXMatrixScaling(&temp,(iWidth / 1280.0f),(iHeight / 1024.0f),1.0f);

			m_pSpriteInterface->SetTransform(&temp);

			hResult = m_pSpriteInterface->Draw(m_pTextureSource->GetTexture(m_SpriteData[i]->GetTextureID()),
											   m_SpriteData[i]->GetRect(), 
											   m_SpriteData[i]->GetCenter(), 
											   &v3SpritePosition, 
											   m_SpriteData[i]->GetModulate());


			LOG_FATALERROR(FAILED(hResult), "Could not draw sprite.");
		}
	}

	m_pSpriteInterface->End();
}

void CSpriteManager::DrawWorld()
{
	//Setup default variables
	HRESULT hResult = S_OK;
	IDirect3DTexture9* d3dpTexture9 = 0;
	unsigned int uiTextureId  = 0;
	unsigned int uiNumSprites = static_cast<unsigned int>(m_SpriteData.size()); 
	CVector3 v3SpritePosition;


	m_pSpriteInterface->SetWorldViewLH(0, m_pRenderer->GetDeviceManager().GetViewMatrix());
	
	hResult = m_pSpriteInterface->Begin(D3DXSPRITE_OBJECTSPACE |
										D3DXSPRITE_BILLBOARD |
										D3DXSPRITE_ALPHABLEND |
										D3DXSPRITE_DO_NOT_ADDREF_TEXTURE);

	LOG_FATALERROR(FAILED(hResult), "Could not begin sprite drawing.");

	for(unsigned int i = 0; i < uiNumSprites; ++i)
	{
		if(m_SpriteData[i]->IsVisible() == true && m_SpriteData[i]->IsWorldCords() == true)
		{
			uiTextureId  = m_SpriteData[i]->GetTextureID();
			d3dpTexture9 = m_pTextureSource->GetTexture(uiTextureId);

			m_pSpriteInterface->SetTransform(&m_SpriteData[i]->GetWorldMatrix());

			m_pSpriteInterface->Draw(d3dpTexture9,
									 m_SpriteData[i]->GetRect(), 
									 m_SpriteData[i]->GetCenter(), 
									 0, 
									 m_SpriteData[i]->GetModulate());
		}
	}

	m_pSpriteInterface->End();
}

int CSpriteManager::AddSprite(LPWSTR _pFileName)
{
	int iReturn = -1;
	RECT Dimentions;
	D3DXIMAGE_INFO FileInfo;
	bool bFound = (m_LoadedSprites.count(_pFileName) > 0);

	Dimentions.top = 0;
	Dimentions.left = 0;
	Dimentions.right = 0;
	Dimentions.bottom = 0;

	CSpriteData* pTemp = new CSpriteData;

	if(bFound && pTemp != 0)
	{
		pTemp->SetID(m_uiNextID++);

		pTemp->SetTextureID(m_LoadedSprites[_pFileName]);

		D3DXGetImageInfoFromFile(_pFileName, &FileInfo);

		Dimentions.right = FileInfo.Width;
		Dimentions.bottom = FileInfo.Height;

		pTemp->SetMaxRect(&Dimentions);
		pTemp->SetRECT(&Dimentions);

		iReturn = pTemp->GetID();

		m_SpriteData.push_back(pTemp);

		m_uiTotalSprites++;
	}
	else if(!bFound && pTemp != 0)
	{
		int iTextureMade = m_pTextureSource->LoadTextureFile(_pFileName);

		if(iTextureMade >= 0)
		{
			pTemp->SetID(m_uiNextID++);

			m_LoadedSprites[_pFileName] = iTextureMade;

			pTemp->SetTextureID(iTextureMade);

			D3DXGetImageInfoFromFile(_pFileName, &FileInfo);

			Dimentions.right = FileInfo.Width;
			Dimentions.bottom = FileInfo.Height;

			pTemp->SetMaxRect(&Dimentions);
			pTemp->SetRECT(&Dimentions);

			iReturn = pTemp->GetID();

			m_SpriteData.push_back(pTemp);

			m_uiTotalSprites++;
		}
		else
		{
			delete pTemp;
		}
	}

	return iReturn;
}

bool CSpriteManager::SetRect(RECT* _pRect, unsigned int _iID)
{
	unsigned int uiNumSprites = static_cast<unsigned int>(m_SpriteData.size()); 
	bool bReturn = false;

	for(unsigned int i = 0; i < uiNumSprites; i++)
	{
		if(m_SpriteData[i]->GetID() == _iID)
		{
			m_SpriteData[i]->SetRECT(_pRect);
			D3DXVECTOR3 Centre((static_cast<float>(_pRect->right - _pRect->left) / 2.0f), (static_cast<float>(_pRect->bottom - _pRect->top) / 2.0f), 0.0f);
			
			SetCenter(&Centre, _iID);

			bReturn = true;
			break;
		}
	}

	return bReturn;
}

bool CSpriteManager::SetCenter(D3DXVECTOR3* _pCenter, unsigned int _iID)
{
	unsigned int uiNumSprites = static_cast<unsigned int>(m_SpriteData.size()); 
	bool bReturn = false;

	for(unsigned int i = 0; i < uiNumSprites; i++)
	{
		if(m_SpriteData[i]->GetID() == _iID)
		{
			m_SpriteData[i]->SetCenter(_pCenter);
			bReturn = true;
			break;
		}
	}

	return bReturn;
}

bool CSpriteManager::SetPosition(CVector3& _rv3Position, unsigned int _iID)
{
	unsigned int uiNumSprites = static_cast<unsigned int>(m_SpriteData.size()); 
	bool bReturn = false;

	for(unsigned int i = 0; i < uiNumSprites; i++)
	{
		if(m_SpriteData[i]->GetID() == _iID)
		{
			m_SpriteData[i]->GetWorldMatrix().SetPosition(_rv3Position);
			bReturn = true;
			break;
		}
	}

	return bReturn;
}


bool CSpriteManager::SetWorldMatrix(CWorldMatrix& _rWorldMatrix, unsigned int _iID)
{
	unsigned int uiNumSprites = static_cast<unsigned int>(m_SpriteData.size()); 
	bool bReturn = false;

	for(unsigned int i = 0; i < uiNumSprites; i++)
	{
		if(m_SpriteData[i]->GetID() == _iID)
		{
			m_SpriteData[i]->SetWorldMatrix(_rWorldMatrix);
			bReturn = true;
			break;
		}
	}

	return bReturn;
}

bool CSpriteManager::SetPosition(float _fX, float _fY, float _fZ, unsigned int _iID)
{
	unsigned int uiNumSprites = static_cast<unsigned int>(m_SpriteData.size()); 
	bool bReturn = false;

	CVector3 Pos(_fX, _fY, _fZ);

	for(unsigned int i = 0; i < uiNumSprites; i++)
	{
		if(m_SpriteData[i]->GetID() == _iID)
		{
			m_SpriteData[i]->GetWorldMatrix().SetPosition(Pos);
			bReturn = true;
			break;
		}
	}

	return bReturn;
}

bool CSpriteManager::SetVisible(bool _bVisible, unsigned int _iID)
{
	unsigned int uiNumSprites = static_cast<unsigned int>(m_SpriteData.size()); 
	bool bReturn = false;

	for(unsigned int i = 0; i < uiNumSprites; i++)
	{
		if(m_SpriteData[i]->GetID() == _iID)
		{
			m_SpriteData[i]->SetVisible(_bVisible);
			bReturn = true;
			break;
		}
	}

	return bReturn;
}

bool CSpriteManager::SetObjectSpace(bool _bIsObjectSpace, unsigned int _iID)
{
	unsigned int uiNumSprites = static_cast<unsigned int>(m_SpriteData.size()); 
	bool bReturn = false;

	for(unsigned int i = 0; i < uiNumSprites; i++)
	{
		if(m_SpriteData[i]->GetID() == _iID)
		{
			m_SpriteData[i]->SetCordSpace(_bIsObjectSpace);
			bReturn = true;
			break;
		}
	}

	return bReturn;
}

RECT CSpriteManager::GetRect(unsigned int _iID)
{
	unsigned int uiNumSprites = static_cast<unsigned int>(m_SpriteData.size()); 
	RECT Return;

	Return.bottom = 0;
	Return.right = 0;
	Return.left = 0;
	Return.top = 0;

	for(unsigned int i = 0; i < uiNumSprites; i++)
	{
		if(m_SpriteData[i]->GetID() == _iID)
		{
			Return = *(m_SpriteData[i]->GetMaxRect());
			break;
		}
	}

	return Return;
}

void CSpriteManager::OnDeviceLost()
{
	if(m_pSpriteInterface != 0)
	{
		m_pSpriteInterface->OnLostDevice();
	}
}

void CSpriteManager::OnDeviceReset()
{
	if(m_pSpriteInterface != 0)
	{
		m_pSpriteInterface->OnResetDevice();
	}
}

bool CSpriteManager::RemoveSprite(unsigned int _iID)
{
	bool bReturn = false;

	std::vector<CSpriteData*>::iterator itter = m_SpriteData.begin();

	for(unsigned int i = 0; i < m_uiTotalSprites; i++)
	{
		if(m_SpriteData[i]->GetID() == _iID)
		{
			delete m_SpriteData[i];
			itter += i;
			m_SpriteData.erase(itter);
			bReturn = true;
			m_uiTotalSprites--;
			break;
		}
	}

	return bReturn;
}

CVector3 CSpriteManager::GetPosition(unsigned int _iID)
{
	CVector3 Return;

	Return.x = 0.0f;
	Return.y = 0.0f;
	Return.z = 0.0f;

	for(unsigned int i = 0; i < m_uiTotalSprites; i++)
	{
		if(m_SpriteData[i]->GetID() == _iID)
		{
			m_SpriteData[i]->GetWorldMatrix().GetPosition(Return);
		}
	}

	return Return;
}

bool CSpriteManager::SetModulate(UINT _uiModulate, unsigned int _iID)
{
	unsigned int uiNumSprites = static_cast<unsigned int>(m_SpriteData.size()); 
	bool bReturn = false;

	for(unsigned int i = 0; i < uiNumSprites; i++)
	{
		if(m_SpriteData[i]->GetID() == _iID)
		{
			m_SpriteData[i]->SetModulate(_uiModulate);
			bReturn = true;
			break;
		}
	}

	return bReturn;
}

int CSpriteManager::Duplicate(unsigned int _iID)
{
	unsigned int uiNumSprites = static_cast<unsigned int>(m_SpriteData.size()); 
	int iReturn = -1;

	for(unsigned int i = 0; i < uiNumSprites; i++)
	{
		if(m_SpriteData[i]->GetID() == _iID)
		{
			CSpriteData* pTemp = new CSpriteData;

			if(pTemp != 0)
			{
				pTemp->SetID(m_uiNextID++);
				m_uiTotalSprites++;

				pTemp->SetTextureID(m_SpriteData[i]->GetTextureID());

				pTemp->SetCenter(m_SpriteData[i]->GetCenter());

				pTemp->SetMaxRect(m_SpriteData[i]->GetMaxRect());

				pTemp->SetModulate(m_SpriteData[i]->GetModulate());

				pTemp->SetRECT(m_SpriteData[i]->GetRect());

				CVector3 vecTemp;
				m_SpriteData[i]->GetWorldMatrix().GetPosition(vecTemp);

				pTemp->GetWorldMatrix().SetPosition(vecTemp);

				pTemp->SetVisible(m_SpriteData[i]->IsVisible());

				pTemp->SetCordSpace(m_SpriteData[i]->IsWorldCords());

				iReturn = pTemp->GetID();

				m_SpriteData.push_back(pTemp);

				break;
			}
		}
	}

	return iReturn;
}