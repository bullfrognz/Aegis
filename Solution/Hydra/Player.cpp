#include "Application.h"
#include "Window.h"
#include "Enemy.h"
#include "Event.h"
#include "eventSender.h"
#include "IniParser.h"
#include "gamescene.h"
#include "wavemanager.h"
#include "wave.h"
#include "SoundSystem.h"
#include "InputManager.h"
#include "XInputController.h"

#include "Player.h"

CPlayer::CPlayer()
: m_iLives(0)
, m_uiGold(0)
{
	
}

CPlayer::~CPlayer()
{
	
}

bool 
CPlayer::Initialise(const char* _kcFileName)
{
	CINIParser* pParser = new CINIParser();
	pParser->LoadINIFile(_kcFileName);
	pParser->GetValue("PlayerStats", "Gold", m_uiGold);
	pParser->GetValue("PlayerStats", "Lives", m_iLives);

	CEventTarget::Register(EVENTSUBJECT_ENEMYDEATH);
	CEventTarget::Register(EVENTSUBJECT_ENEMYLASTWAYPOINT);
	CEventTarget::Register(EVENTSUBJECT_TOWERBUILD);
	CEventTarget::Register(EVENTSUBJECT_TOWERUPGRADE);

	delete pParser;
	pParser = 0;

	return true;
}

/**
*
* Handles the current event
* @Param _kpEventData a pointer to the event handler
* @author Daniel.Langsford
* @return void
*
*/
void 
CPlayer::HandleRecievedEvent(const CEvent* _kpEventData)
{
	int iEventDataSubject = _kpEventData->GetSubject();

	switch (iEventDataSubject)
	{
	case EVENTSUBJECT_ENEMYDEATH:
		{	
			int iBounty = reinterpret_cast<const CEnemy*>(_kpEventData->GetData())->GetBountyValue();	

			int iWaveNumber = (reinterpret_cast<CGameScene&>(CApplication::GetInstance().GetGameWindow().GetCurrentMainScene()).GetWaveManager()->GetCurrentWaveCount());

			int iGold = (iWaveNumber / 4) * 2;

			m_uiGold += static_cast<int>(iBounty + iGold);

			break;
		}
	case EVENTSUBJECT_ENEMYLASTWAYPOINT:
		{
			std::string EnemyType =  reinterpret_cast<const CEnemy*>(_kpEventData->GetData())->GetType();
			if(EnemyType == "Boss Enemy")
			{
				m_iLives = 0;
			}

			if(m_iLives > 1)
			{
				--m_iLives;


				CApplication::GetInstance().GetGameWindow().GetCurrentMainScene().GetInputManager().GetXInputController().SetRumbleLeft(XRUMBLELVL_3, 0.5f);
				CApplication::GetInstance().GetGameWindow().GetCurrentMainScene().GetInputManager().GetXInputController().SetRumbleRight(XRUMBLELVL_3, 0.5f);
				//CSoundSystem::GetInstance()->NewSound2DInstant("Assets\\Sounds\\Game-LifeLoss.wav");
			}
			else
			{
				if(m_iLives != 0)
				{
					--m_iLives;
				}


				static_cast<CGameScene&>(CApplication::GetInstance().GetGameWindow().GetCurrentMainScene()).ExecuteGameOver(false);
			}
			break;
		}

		default:
			break;
	}
}
