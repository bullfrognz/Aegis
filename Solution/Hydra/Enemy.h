//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Enemy.h
//  Description :   Enemy units that can follow paths, take damage
//					and be attacked by towers.
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_ENEMY_H__
#define __IGFEB11_IG500_ENEMY_H__


// Library Includes
#include <string>


// Local Includes
#include "EffectTarget.h"
#include "EventSender.h"
#include "Entity.h"


// Types


// Constants
enum EEnemyEvent
{
};


// Prototypes
class CD3DRenderer;
class CINIParser;
class CWaypoint;
class CPlayer;
class CSoundSystem;
class CObject;


class CEnemy : public CEntity, public CEffectTarget, public CEventSender<EEnemyEvent>
{

	// Member Functions
public:


	         CEnemy();
	virtual ~CEnemy();


	bool Initialise(CD3DRenderer* _pRenderer);
	void Process(float _fDeltaTick);
	void Draw(CD3DRenderer* _pRenderer);


	void Kill(bool _bHitLastWaypoint = false);
	void Revive();


	void SetWaypoint(const CWaypoint* _kpWaypoint);
	void ChangeType(CD3DRenderer* _pRenderer, const char* _kcpEnemyType, unsigned int _uiWaveNumber);


	// Inline Functions
	inline void SetDefaultHealth(float _fDefaultHealth);
	inline void SetDefaultMovementVelocity(float _fMovementVelocity);
	inline bool IsAlive() const;
	inline void DecrementHealth(float _fValue);
	inline unsigned int GetBountyValue() const;
	inline float GetDefaultHealth() const;
	inline float GetDefaultMovementVelocity() const;
	inline float GetLifeTimeElapsed() const;
	inline float GetHealth() const;
	inline void SetCriticalColourTimer(float _fTimer);
	inline float GetCriticalColourTimer() const;
	inline const char* GetType() const;


protected:


	bool InitialiseEnemyIniData(char*& _cprEnemyMeshFile, bool& _brMeshFileAnimated);
	bool InitialiseMesh(CD3DRenderer* _pRenderer, const char* _kcpEnemyMeshFile, bool _bMeshAnimated);
	bool IntiialiseHealthBar();


	void ProcessHealthRegen(float _fDeltaTick);
	virtual void ProcessPoisonEffect(float _fDeltaTick);
	void ProcessAlive();
	void ProcessTargetWaypoint();
	void ProcessHealthBar();
	void ProcessCriticalColour(float _fDeltaTick);


	static void PreDraw(void* _pEnemy, CD3DRenderer* _pRenderer);
	static void PostDraw(void* _pEnemy, CD3DRenderer* _pRenderer);


	virtual void TurnOnFrostEffect(float _fFrostPenaltyRatio);
	virtual void TurnOffFrostEffect();


	void ExecuteDeathEffect();
	void RestoreDefaultVariables();


private:


	void Deinitialise();


	static void LoadEnemyIniParser();


	CEnemy(const CEnemy& _krEnemy);
	CEnemy& operator = (const CEnemy& _krEnemy);


	// Member Variables
protected:


	CD3DRenderer* m_pRenderer;
	CObject*      m_pIObjEnemy;


	unsigned int m_uiSpriteHealthBar;


	const char* m_kcpEnemyType;


	const CWaypoint* m_kpTargetWaypoint;


	unsigned int m_uiBountyValue;


	float m_fHealth;
	float m_fHealthRegen;
	float m_fDefaultHealth;
	float m_fDefaultMovementVelocity;
	float m_fLifeTimeElapsed;
	float m_fCriticalColourTimer;
	float m_fLastDistanceToWaypoint;


	float m_fToBeDefaultHealth;
	float m_fToBeDefaultMovementVelocity;


	bool m_bAlive;

	bool m_bFrostEffect;


private:


	static CINIParser*  s_pEnemyIniParser;
	static unsigned int s_uiEnemyReffCount;


};


#include "Inline/Enemy.inl"


#endif //__IGFEB11_IG500_ENEMY_H__