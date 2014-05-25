//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Projectile.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_PROJECTILE_H__
#define __IGFEB11_IG500_PROJECTILE_H__


// Library Includes


// Local Includes
#include "Macros.h"
#include "EffectTarget.h"
#include "EventTarget.h"
#include "Entity.h"
#include "Vector3.h"


// Types
enum EProjectileEmitterType
{
	PROJECTILEEMITTER_NONE,

	PROJECTILEEMITTER_FROST,
	PROJECTILEEMITTER_POISON,
	PROJECTILEEMITTER_METEOR,
	PROJECTILEEMITTER_WATER,
	PROJECTILEEMITTER_FIRE,
	PROJECTILEEMITTER_CANNON,
	PROJECTILEEMITTER_SUNSWRATH
};


struct TProjectileData
{
	TProjectileData()
	{
		ZeroMemory(this, sizeof(TProjectileData));
	}

	~TProjectileData()
	{
		FW_ADELETE(m_kcpMeshFile);
		FW_ADELETE(m_cpSndHit);
	}


	CVector3 m_v3AngularVelocity;


	const char* m_kcpMeshFile;
	      char* m_cpSndHit;


	unsigned int m_uiTowerOwnerId;
	unsigned int m_uiEffects;
	unsigned int m_uiEmitterType;


	float m_fMovementVelocity;
	float m_fRadius;
	float m_fPoisonTickDamage;
	float m_fPoisonLength;
	float m_fFrostPenaltyRatio;
	float m_fFrostLength;
	float m_fAreaOfEffect;


	bool m_bAnimatedMesh;
};


// Constants


// Prototypes
class CD3DRenderer;
class CEnemy;
class CVector3;
class CObject;


class CProjectile : public CEntity,  public CEventTarget
{

	// Member Functions
public:


	 CProjectile();
	~CProjectile();


	bool Initialise(CD3DRenderer* _pRenderer, TProjectileData& _trProjectileData);
	void Process(float _fDeltaTick);
	void Draw(CD3DRenderer* _pRenderer);


	void Activate(const CVector3& _kv3rPosition, CEnemy* _pTargetEnemy, float _fDamage, bool _bIsCritical);
	void Deactivate();


	virtual void HandleRecievedEvent(const CEvent* _kpEventData);


	// Inline Functions
	inline unsigned int GetEffects() const;
	inline bool IsActive() const;


	static inline float GetMaxiumLifeSpan();
	static inline float GetTrackingUpdateInverval();
	static inline float GetMinMovementVelocity();
	static inline float GetMaxMovementVelocity();


protected:


	bool InitialiseObject(CD3DRenderer* _pRenderer, TProjectileData& _trProjectileData);
	bool InitialiseEffects(TProjectileData& _trProjectileData);


	void ProcessCheckPosition();
	void ProcessTargetCollison();
	void ProcessLifeTimeElapsed(float _fDeltaTick);
	void ProcessStrayCollison();
	void ProcessTrajectory();


	void HitEnemy(CEnemy* _pEnemy);
	void Explode();
	void RemoveCurrentTargetEnemy();


private:


	void Deinitialise();


	CProjectile(const CProjectile& _krProjectile);
	CProjectile& operator = (const CProjectile& _krProjectile);


	// Member Variables
protected:


	CEnemy*  m_pTargetEnemy;
	CObject* m_pObjProjectile;
	CD3DRenderer* m_pRenderer;


	char* m_cpSndHit;


	unsigned int m_uiTowerOwnerId;
	unsigned int m_uiEffects;
	unsigned int m_uiEmitterType;


	float m_fDamage;
	float m_fLifeTimeElapsed;
	float m_fTotalDistanceTarget;


	float m_fPoisonTickDamage;
	float m_fPoisonLength;
	float m_fFrostPenaltyRatio;
	float m_fFrostLength;
	float m_fAreaOfEffect;


	bool m_bActive;
	bool m_bCopyOrientation;
	bool m_bCritical;


	EProjectileEmitterType m_eProjType;


private:


	static unsigned int s_uiProjectileReffCount;


};


#include "Inline/Projectile.inl"


#endif //__IGFEB11_IG500_PROJECTILE_H__