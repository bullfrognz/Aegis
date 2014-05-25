#include "GameWinScene.h"
#include "SpriteManager.h"
#include "Application.h"

CGameWinScene::CGameWinScene()
:m_uiSplashID(-1)
,m_uiModulate(0x00FFFFFF)
,m_fFadeTime(2.0f)
,m_fTotalTimeOpen(0.0f)
,m_fSolidTime(2.0f)
,m_fDelay(2.0f)
{
}

CGameWinScene::~CGameWinScene()
{
}

bool CGameWinScene::InitialiseScene(CD3DRenderer* _pRenderer, void* _pSceneData)
{
	bool bReturn = false;

	bool bWon = *(reinterpret_cast<bool*>(_pSceneData));

	delete _pSceneData;

	if(bWon == true)
	{
		m_uiSplashID = _pRenderer->GetSpriteManager().AddSprite(L"Assets\\Game-Win.png");
	}
	else
	{
		m_uiSplashID = _pRenderer->GetSpriteManager().AddSprite(L"Assets\\Game-Loss.png");
	}

	if(m_uiSplashID != -1)
	{
		CVector3 vecTemp(1280.0f / 2.0f, 1024.0f / 2.0f, 0.0f);

		//CWorldMatrix matTemp;

		//D3DXMatrixScaling(&matTemp, 1024.0f / 1280.0f, 1.0f, 1.0f);

		//matTemp.SetPosition(vecTemp);

		//_pRenderer->GetSpriteManager().SetWorldMatrix(matTemp, m_uiSplashID);
		_pRenderer->GetSpriteManager().SetPosition(1280.0f / 2.0f, 1024.0f / 2.0f, 0.0f, m_uiSplashID);
		_pRenderer->GetSpriteManager().SetModulate(m_uiModulate,m_uiSplashID);
		//_pRenderer->GetSpriteManager().SetObjectSpace(false, m_uiSplashID);
		//_pRenderer->GetSpriteManager().SetVisible(true, m_uiSplashID);
		//_pRenderer->GetSpriteManager().SetCenter(&vecTemp, m_uiSplashID);

		bReturn = true;
	}

	return bReturn;
}

void CGameWinScene::ProcessScene(float _fDeltaTick)
{
	m_fTotalTimeOpen += _fDeltaTick;

	if(m_fTotalTimeOpen < m_fDelay)
	{
		m_uiModulate = 0x00FFFFFF;
	}
	else if(m_fTotalTimeOpen < m_fFadeTime + m_fDelay)
	{
		float fDifrence = (m_fTotalTimeOpen - m_fDelay) / m_fFadeTime ;
		unsigned int uiAlphaBlend = static_cast<unsigned int>(0xFF * fDifrence);

		m_uiModulate = (uiAlphaBlend << 24) + 0xFFFFFF;
	}
	else if(m_fTotalTimeOpen > (m_fFadeTime + m_fSolidTime + m_fDelay) && m_fTotalTimeOpen < ((m_fFadeTime * 2.0f) + m_fSolidTime + m_fDelay))
	{
		float fDifrence = (m_fTotalTimeOpen - ((m_fFadeTime + m_fSolidTime) + m_fDelay)) / m_fFadeTime;
		unsigned int uiColourBlend = static_cast<unsigned int>(0xFF * fDifrence) ^ 0xFF;

		m_uiModulate = (0xFF << 24) + (uiColourBlend << 16) + (uiColourBlend << 8) + uiColourBlend;
	}

	m_pRenderer->GetSpriteManager().SetModulate(m_uiModulate, m_uiSplashID);

	if(m_fTotalTimeOpen > ((m_fFadeTime * 2.6f) + m_fSolidTime + m_fDelay))
	{
		m_pRenderer->GetSpriteManager().RemoveSprite(m_uiSplashID);
		CApplication::GetInstance().GetGameWindow().SetMainScene(SCENE_MAINMENU);
		m_uiSplashID = -1;
		CApplication::GetInstance().GetGameWindow().SetOverlayScene(OVERLAYSCENE_DELETE);
	}
}

void CGameWinScene::DrawScene(CD3DRenderer* _pRenderer)
{
}

void CGameWinScene::RecoverFromOverlayScene()
{
}

bool CGameWinScene::InitialiseLights(CD3DRenderer* _pRenderer)
{
	return true;
}

bool CGameWinScene::InitialiseViewports(CD3DRenderer* _pRenderer)
{
	return true;
}

bool CGameWinScene::InitialisePlayerInput()
{
	return true;
}

bool CGameWinScene::InitialiseXInput()
{
	return true;
}

bool CGameWinScene::InitialiseSoundSystem()
{
	return true;
}

bool CGameWinScene::InitialiseLogManager()
{
	return true;
}

void CGameWinScene::ProcessFPSCount(float _fDeltaTick)
{
}