//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Tower.h
//  Description :   
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_TOWER_H__
#define __IGFEB11_IG500_TOWER_H__


// Library Includes
#include <vector>


// Local Includes
#include "Vector3.h"
#include "EventTarget.h"
#include "Entity.h"
#include "Weapon.h"
#include "Utility.h"


// Types
enum ETowerEmitter
{
	TOWEREMITTER_NONE,
	TOWEREMITTER_FROST  = Utility::B1,
	TOWEREMITTER_POISON = Utility::B2,

	TOWEREMITTER_MAX
};


// Constants


// Prototypes
struct TProjectileData;
struct TWeaponData;

class CEnemy;
class CINIParser;
class CD3DRenderer;
class CStaticObject;
class CObject;


class CTower : public CEntity,  public CEventTarget
{

	// Member Functions
public:


	         CTower();
	virtual ~CTower();


	bool Initialise(CD3DRenderer* _pRenderer, const char* _kcpTowerType);
	void Process(float _fDeltaTick);
	void Draw(CD3DRenderer* _pRenderer);


	virtual void HandleRecievedEvent(const CEvent* _kpEventData);


	// Inline Functions
	inline unsigned int GetBuildCost() const;
	inline std::vector<char*>& GetTowerUpgradeTypes();
	inline const char* GetTowerType() const;


	inline unsigned int GetMaxTargets() const;
	inline unsigned int GetAbilitys() const;


	inline float GetMaxDamage() const;
	inline float GetMinDamage() const;
	inline float GetRange() const;
	inline float GetFireRate() const;


protected:


	bool InitialiseTowerIniData(char*& _cprMeshFile, bool& _brMeshAnimated, char*& _cprTrackerMeshFile);
	bool InitialiseTowerEmitterIni();
	bool IntiailiseObject(CD3DRenderer* _pRenderer, char* _cpMeshFile, bool _bMeshAnimated);
	bool InitialiseTracker(CD3DRenderer* _pRenderer, const char* _kcpTrackerMeshFile);
	bool InitialiseMaxTargets();
	bool InitialiseProjectileIniData(TProjectileData& _trProjectileData);
	bool InitialiseProjectileEffectIniData(TProjectileData& _trProjectileData);
	bool InitialiseWeaponIniData(CD3DRenderer* _pRenderer, TWeaponData& _trWeaponData);
	bool InitialiseWeapon(CD3DRenderer* _pRenderer, TWeaponData& _trWeaponData, TProjectileData& _trProjectileData);


	void ProcessTracker(float _fDeltaTick);
	void ProcessTargetEnemyStatus(unsigned int _uiTargetIndex);
	void ProcessCriticalColour(float _fDeltaTick);


	void FireWeaponAtEnemy(CEnemy* _pEnemy);
	void FindNewTargetEnemy(unsigned int _uiTargetIndex);
	bool IsEnemyWithinTowerRange(CEnemy* _pEnemy);
	void AddNewTargetEnemy(CEnemy* _pEnemy);
	bool IsEnemyTargeted(const CEnemy* _kpEnemy);


	void RemoveTargetEnemy(const CEnemy* _kpEnemy);


private:


	void Deinitialise();


	static void LoadTowerIniParser();


	CTower(const CTower& _krTower);
	CTower& operator = (const CTower& _krTower);


	// Member Variables
protected:


	CVector3 m_v3TrackerOffset;
	CVector3 m_v3WeaponOffset;
	CVector3 m_v3EmitterOffset;

	
	const char* m_kcpTowerType;
	      char* m_cpSndFire;


	CD3DRenderer* m_pRenderer;
	CEnemy** m_ppTargetEnemy;
	CWeapon* m_pWeapon;
	CObject* m_pObjTower;
	CStaticObject* m_pObjTracker;


	unsigned int m_uiMaxTargets;
	unsigned int m_uiMaxActiveTargetId;
	unsigned int m_uiBuildCost;
	unsigned int m_uiTowerEmitterType;


	float m_fRange;
	float m_fFireRate;
	float m_fFireTimer;
	float m_fEmitterTime;


	std::vector<char*> m_vecUpgradeTowerTypes;


private:


	static CINIParser*  s_pTowerIniParser;
	static unsigned int s_uiTowerReffCount;


	static bool s_bShadowsEnabled;


};


#include "Inline/Tower.inl"


#endif //__IGFEB11_IG500_TOWER_H__