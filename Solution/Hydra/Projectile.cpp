//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   Projectile.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes
#include <cmath>


// Local Includes
#include "Macros.h"
#include "INIParser.h"
#include "D3Drenderer.h"
#include "StrUtilities.h"
#include "Enemy.h"
#include "Event.h"
#include "EnemySpawner.h"
#include "StaticObject.h"
#include "AnimatedObject.h"
#include "SoundSystem.h"
#include "ParticleManager.h"
#include "ParticleInterface.h"
#include "vector3.h"
#include "Utility.h"

// This Include
#include "Projectile.h"


// Static Variables
unsigned int CProjectile::s_uiProjectileReffCount = 0;


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Projectile class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CProjectile::CProjectile()
: m_pTargetEnemy(0)
, m_cpSndHit(0)
, m_uiTowerOwnerId(0)
, m_uiEffects(0)
, m_uiEmitterType(0)
, m_fDamage(0)
, m_fLifeTimeElapsed(0)
, m_fTotalDistanceTarget(0)
, m_fPoisonTickDamage(0)
, m_fPoisonLength(0)
, m_fFrostPenaltyRatio(0)
, m_fFrostLength(0)
, m_fAreaOfEffect(0)
, m_bActive(false)
, m_bCopyOrientation(true)
, m_bCritical(false)
{
	//Add reff
	++ s_uiProjectileReffCount;
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Projectile class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CProjectile::~CProjectile()
{
	Deinitialise();


	//Remove reff
	-- s_uiProjectileReffCount;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function initialisings the class instance before use.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CProjectile::Initialise(CD3DRenderer* _pRenderer, TProjectileData& _trProjectileData)
{
	//Set member variables
	m_uiTowerOwnerId = _trProjectileData.m_uiTowerOwnerId;
	CEntity::m_fTrackUpdateInterval = GetTrackingUpdateInverval();
	CEntity::m_v3MovementVelocity.z = _trProjectileData.m_fMovementVelocity;
	m_fAreaOfEffect = _trProjectileData.m_fAreaOfEffect;
	m_uiEmitterType = _trProjectileData.m_uiEmitterType;
	m_eProjType = static_cast<EProjectileEmitterType>(m_uiEmitterType);
	StrUtilities::Copy(_trProjectileData.m_cpSndHit, m_cpSndHit);


	//Run initialsie functions
	InitialiseObject(_pRenderer, _trProjectileData);
	InitialiseEffects(_trProjectileData);

	m_pRenderer = _pRenderer;


	return (true);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function processes the class instance for the current frame.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CProjectile::Process(float _fDeltaTick)
{
	//Process position
	ProcessCheckPosition();


	//Process life elapsed time
	ProcessLifeTimeElapsed(_fDeltaTick);


	//Process trajectory
	ProcessTrajectory();

	
	//Check projectile has a target
	if (m_pTargetEnemy)
	{
		//Process collision with target
		ProcessTargetCollison();
	}	
	else
	{
		//Process collision with all enemy instances
		ProcessStrayCollison();
	}


	//Process derived class CEntity
	CEntity::Process(_fDeltaTick);


	//Process projectile mesh
	m_pObjProjectile->Process(_fDeltaTick);	

	if(m_eProjType == PROJECTILEEMITTER_METEOR)
	{
		CEntity::m_pTrackingEntity = 0;
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will call on the renderer to draw meshes.
*
* @author Bryce Booth
* @param _pRenderer		The renderer for the window
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CProjectile::Draw(CD3DRenderer* _pRenderer)
{	
	m_pObjProjectile->CopyPosition(this);

	if (m_bCopyOrientation == true)
	{
		m_pObjProjectile->CopyOrientation(this);
	}

	//Draw projectile object
	if(m_eProjType == PROJECTILEEMITTER_FROST )
	{
		//dont draw
	}
	else if(m_eProjType == PROJECTILEEMITTER_WATER)
	{
		//dont draw
	}
	else if(m_eProjType == PROJECTILEEMITTER_SUNSWRATH)
	{
		//dont draw
	}
	else
	{
		m_pObjProjectile->Draw(_pRenderer);
	}

	//Draw Particles
	switch(m_eProjType)
	{
	case PROJECTILEEMITTER_FROST:
		{
			for(int i = 0; i < 5; ++i)
			{
				float fXDirection = MathUtility::RandomNumber(-5.5f, 5.5f);
				float fYDirection = MathUtility::RandomNumber(-5.5f, 5.5f);
				float fZDirection = MathUtility::RandomNumber(-5.5f, 5.5f);
				CVector3 Vec(fXDirection, fYDirection, fZDirection);
				CVector3 ThisPos;
				this->GetWorldMatrix().GetPosition(ThisPos);
				_pRenderer->GetParticleManager().GetParticleInterface().CreateFrost(ThisPos, Vec, 0.15f);
			}
		}
		break;

	case PROJECTILEEMITTER_METEOR:
		{
			for(int i = 0; i < 5; ++i)
			{
				float fXDirection = MathUtility::RandomNumber(-1.5f, 1.5f);
				float fYDirection = MathUtility::RandomNumber(-1.5f, 1.5f);
				float fZDirection = MathUtility::RandomNumber(-1.5f, 1.5f);
				CVector3 Vec(fXDirection, fYDirection, fZDirection);
				CVector3 ThisPos;
				this->GetWorldMatrix().GetPosition(ThisPos);
				_pRenderer->GetParticleManager().GetParticleInterface().CreateSmoke(ThisPos, Vec, 0.85f);
			}
		}
		break;

	case PROJECTILEEMITTER_WATER:
		{
			for(int i = 0; i < 2; ++i)
			{
				float fXDirection = MathUtility::RandomNumber(-0.5f, 0.5f);
				float fYDirection = MathUtility::RandomNumber(-0.5f, 0.5f);
				float fZDirection = MathUtility::RandomNumber(-0.5f, 0.5f);
				CVector3 Vec(fXDirection, fYDirection, fZDirection);
				CVector3 ThisPos;
				this->GetWorldMatrix().GetPosition(ThisPos);
				_pRenderer->GetParticleManager().GetParticleInterface().CreateWater(ThisPos, Vec, 0.35f);
			}
		}
		break;

	case PROJECTILEEMITTER_FIRE:
		{
			for(int i = 0; i < 5; ++i)
			{
				float fXDirection = MathUtility::RandomNumber(-5.5f, 5.5f);
				float fYDirection = MathUtility::RandomNumber(-5.5f, 5.5f);
				float fZDirection = MathUtility::RandomNumber(-5.5f, 5.5f);
				CVector3 Vec(fXDirection, fYDirection, fZDirection);
				CVector3 ThisPos;
				this->GetWorldMatrix().GetPosition(ThisPos);
				_pRenderer->GetParticleManager().GetParticleInterface().CreateFireTower(ThisPos, Vec, 0.10f);
			}
		}
		break;

	case PROJECTILEEMITTER_SUNSWRATH:
		{
			CVector3 Vec(0.0f, 0.0f, 0.0f);
			CVector3 ThisPos;
			this->GetWorldMatrix().GetPosition(ThisPos);
			_pRenderer->GetParticleManager().GetParticleInterface().CreateSunsWrath(ThisPos, Vec, 0.8f);			
		}
		break;

	default:
		break;
	}	
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will activate the projectile by resetting member variables and setting memeber variables.
*
* @author Bryce Booth
* @param _kv3rPosition		Start position of the projectile
* @param _pTargetEnemy		Target enemy of the projectile
* @param _fDamage			Damage of the projectile
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CProjectile::Activate(const CVector3& _kv3rPosition, CEnemy* _pTargetEnemy, float _fDamage, bool _bIsCritical)
{
	//Set member variables
	CEntity::m_pTrackingEntity = _pTargetEnemy;
	CEntity::m_mtxWorldMatrix.SetPosition(_kv3rPosition);
	m_pTargetEnemy = _pTargetEnemy;
	m_fDamage = _fDamage;
	m_fLifeTimeElapsed = 0.0f;
	CEntity::m_fTrackUpdateElapsed = GetTrackingUpdateInverval();
	m_fTotalDistanceTarget = CEntity::GetSquaredDistanceTo(_pTargetEnemy);
	m_bCritical = _bIsCritical;


	//Look at target on activate
	CVector3 v3TargePosition;
	_pTargetEnemy->GetWorldMatrix().GetPosition(v3TargePosition);
	m_pObjProjectile->LookAt(v3TargePosition);


	//Tell enemy to tell this projectile when it dies
	CEventTarget::Register(EVENTSUBJECT_ENEMYDEATH);


	//Activate
	m_bActive = true;	
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will deactivate the projectile by setting and clearing member variables.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CProjectile::Deactivate()
{
	//Remove target
	CEntity::m_pTrackingEntity = 0;
	m_pTargetEnemy = 0;
	CEventTarget::Deregister(EVENTSUBJECT_ENEMYDEATH);


	//Deactivate
	m_bActive = false;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will handle incomine events from event senders.
*
* @author Bryce Booth
* @param _kpEventData	Container for received event data
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CProjectile::HandleRecievedEvent(const CEvent* _kpEventData)
{
	int iEventDataSubject = _kpEventData->GetSubject();


	switch (iEventDataSubject)
	{
		case EVENTSUBJECT_ENEMYDEATH:
			{
				const CEnemy* kpEnemy = reinterpret_cast<const CEnemy*>(_kpEventData->GetData());


				if (kpEnemy == m_pTargetEnemy)
				{
					RemoveCurrentTargetEnemy();
				}
			}
			break;


		default:
			break;
	}
}








/********************************
            Protected
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will create a mesh for the projectile object and initialise the projectile object.
*
* @author Bryce Booth
* @param _pRenderer			    The renderer for the window
* @param _trProjectileData		Container for the projectile data
* @return bool					States function execution succeeded or failed
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CProjectile::InitialiseObject(CD3DRenderer* _pRenderer, TProjectileData& _trProjectileData)
{
	//Check if mesh is animated
	if (_trProjectileData.m_bAnimatedMesh == true)
	{
		//Instance animated object
		m_pObjProjectile = new CAnimatedObject();
	}
	else
	{
		//Instance static object
		m_pObjProjectile = new CStaticObject();
	}


	//Create projectile name
	//TODO, ALloc/ Dealloc
	char* cpBuffer = new char[128];
	sprintf_s(cpBuffer, 128, "Projectile %d", s_uiProjectileReffCount);


	//Initialise instance object
	m_pObjProjectile->Initialise(cpBuffer, _pRenderer, _trProjectileData.m_kcpMeshFile);


	//Set rotational velocity if any
	if (_trProjectileData.m_v3AngularVelocity.IsZero() == false)
	{
		m_pObjProjectile->SetAngularVelocity(_trProjectileData.m_v3AngularVelocity);
			

		m_bCopyOrientation = false;
	}


	//Delete variables
	delete[] cpBuffer;
	cpBuffer = 0;


	return (true);
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will check which effects it has and set the required member data.
*
* @author Bryce Booth
* @param _trProjectileData		Container for the projectile data
* @return bool					States function execution succeeded or failed
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CProjectile::InitialiseEffects(TProjectileData& _trProjectileData)
{
	//Set member variables
	m_uiEffects = _trProjectileData.m_uiEffects;


	//Check projectiles has poison effect
	if (_trProjectileData.m_uiEffects & EFFECTTYPE_POISON)
	{
		//Set member variables
		m_fPoisonTickDamage = _trProjectileData.m_fPoisonTickDamage;
		m_fPoisonLength = _trProjectileData.m_fPoisonLength;
	}


	//Check projectiles has frost effect
	if (_trProjectileData.m_uiEffects & EFFECTTYPE_FROST)
	{
		//Set member variables
		m_fFrostPenaltyRatio = _trProjectileData.m_fFrostPenaltyRatio;
		m_fFrostLength = _trProjectileData.m_fFrostLength;
	}

	return (true);
}










/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will check if the projectile has become invalid by going too far under the game ground.
* The projectile will deactivate will it has.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CProjectile::ProcessCheckPosition()
{
	//Check projectile has gone into ground
	if (CEntity::m_mtxWorldMatrix.GetPositionY() <= -0.1f)
	{
		ProcessStrayCollison();

		if (m_bActive == true)
		{
			Deactivate();
		}
	}
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will check if the projectile has collided with its target enemy.
* It will run functionality if it has hit it's target.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CProjectile::ProcessTargetCollison()
{
	//Check colliding with target entity
	bool bCollidingWithTarget = IsCollidingWith(m_pTargetEnemy);


	if (bCollidingWithTarget == true)
	{
		//Execute projectile -> enemy collision result
		HitEnemy(m_pTargetEnemy);


		//Check projectile has area of effect
		if (m_fAreaOfEffect != 0.0f)
		{
			//Trigger explode
			Explode();
		}


		//Deactivate
		Deactivate();
	}
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will be called instead of ProcessTargetCollison() if the projectile's target has become invalid.
* It will instead check collision against all enemies.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CProjectile::ProcessStrayCollison()
{
	//Set default variables
	CEnemy* pEnemy = 0;
	bool bWithinRange = false;


	//Get enemy instances
	std::vector<CEnemy*>& vecEnemyInstances = CEnemySpawner::GetEnemyInstances();
	unsigned int uiNumEnemyInstances = static_cast<unsigned int>(vecEnemyInstances.size());


	//Loop through number active enemy instances
	for (unsigned int i = 0; i < uiNumEnemyInstances; ++ i)
	{
		//Set enemy
		pEnemy = vecEnemyInstances[i];


		//Check enemy is alive
		if (pEnemy->IsAlive() == true)
		{
			//Check enemy is within tower range
			bWithinRange = CEntity::IsCollidingWith(pEnemy);


			if (bWithinRange == true)
			{
				//Check projectile has area of effect
				if (m_fAreaOfEffect != 0.0f)
				{
					//Trigger explode
					Explode();
				}


				//Deactivate
				Deactivate();


				break;
			}
		}
	}
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will run a projectile trajectory algorithm to give the projectile a more smooth change of angle
* when tracking it's target
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CProjectile::ProcessTrajectory()
{
	if (m_pTargetEnemy)
	{
		const float kfGravity = 9.8f;
		const float kfMovementVelocityZ = m_pObjProjectile->GetMovementVelocity().z;


		//y = x * tan(theta) - (kfGravity * x) / (2 * kfMovementVelocityZ * cos(theta))


		/*
		//Get distance to target
		float fDistanceToTarget = CEntity::GetSquaredDistanceTo(m_pTargetEnemy);


		//Get velocity
		float fMovementVelocity = CEntity::m_v3MovementVelocity.z;


		//Square velocity
		fMovementVelocity *= fMovementVelocity;


		//Get get time impact
		float fTimeTillImpact = fDistanceToTarget / fMovementVelocity;

		//fTimeTillImpact = sqrt(fTimeTillImpact);


		//Get Y positions
		float fSelfYPosition   = CEntity::m_mtxWorldMatrix.GetPositionY();
		float fTargetYPosition = m_pTargetEnemy->GetWorldMatrix().GetPositionY();
		

		//Calculate Y difference
		float fYDifference = fSelfYPosition - fTargetYPosition;

		fYDifference *= (fDistanceToTarget / m_fTotalDistanceTarget);


		CEntity::m_mtxWorldMatrix.SetPositionY(fTargetYPosition + fYDifference);











		char cBuffer[128];

		sprintf_s(cBuffer, 128, "Time: %.2f", fTimeTillImpact);


		m_Text.SetText(cBuffer);
		*/
	}
}










/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will process the projectiles current time alive. It will deactivate the projectile if it has been
* alive for too long
*
* @author Bryce Booth
* @param  _fDeltaTick	The time elasped since last process
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CProjectile::ProcessLifeTimeElapsed(float _fDeltaTick)
{
	//Increment life time elapsed
	m_fLifeTimeElapsed += _fDeltaTick;


	//Check time elapsed higher then maxium life span
	if (m_fLifeTimeElapsed > GetMaxiumLifeSpan())
	{
		//Deactivate projectile
		Deactivate();
	}
}










/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will process the effects and damage of the projectile when it hits the givene enemy instance
*
* @author Bryce Booth
* @param _pEnemy	Instance of enemy that the projectile is set to hit
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CProjectile::HitEnemy(CEnemy* _pEnemy)
{
	//play hit sound!
	if (m_cpSndHit)
	{
		CSoundSystem::GetInstance()->NewSound2DInstant(m_cpSndHit);
	}


	//Check projectile has poison effect
	if (m_uiEffects & EFFECTTYPE_POISON)
	{
		_pEnemy->ApplyPoison(m_fPoisonTickDamage, m_fPoisonLength);
	}


	//Check projectile has frost effect
	if (m_uiEffects & EFFECTTYPE_FROST)
	{
		_pEnemy->ApplyFrost(m_fFrostPenaltyRatio, m_fFrostLength);
	}


	//Check projectile is critical
	if (m_bCritical)
	{
		_pEnemy->SetCriticalColourTimer(0.2f);
	}


	//Decrease target enemy life by damage value
	_pEnemy->DecrementHealth(m_fDamage);
}










/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CProjectile::Explode()
{
	//Set default variables
	float fDistanceToEnemy = 0.0f;


	//Get enemy instances
	std::vector<CEnemy*>& vecEnemyInstances = CEnemySpawner::GetEnemyInstances();
	unsigned int uiNumEnemyInstances = static_cast<unsigned int>(vecEnemyInstances.size());

	switch(m_eProjType)
	{
	case PROJECTILEEMITTER_FROST:
		{
			for(int i = 0; i < 25; ++i)
			{
				float fXDirection = MathUtility::RandomNumber(-2.0f, 2.0f);
				float fYDirection = MathUtility::RandomNumber(-2.0f, 2.0f);
				float fZDirection = MathUtility::RandomNumber(-2.0f, 2.0f);
				CVector3 Vec(fXDirection, fYDirection, fZDirection);
				CVector3 ThisPos;
				this->GetWorldMatrix().GetPosition(ThisPos);
				m_pRenderer->GetParticleManager().GetParticleInterface().CreateFrostTower(ThisPos, Vec, 0.5f);
			}
		}
		break;

	case PROJECTILEEMITTER_METEOR:
		{
			for(int i = 0; i < 25; ++i)
			{
				float fXDirection = MathUtility::RandomNumber(-2.0f, 2.0f);
				float fYDirection = MathUtility::RandomNumber(-2.0f, 2.0f);
				float fZDirection = MathUtility::RandomNumber(-2.0f, 2.0f);
				CVector3 Vec(fXDirection, fYDirection, fZDirection);
				CVector3 ThisPos;
				this->GetWorldMatrix().GetPosition(ThisPos);
				m_pRenderer->GetParticleManager().GetParticleInterface().CreateCannon(ThisPos, Vec, 0.5f);
			}
		}

	case PROJECTILEEMITTER_CANNON:
		{
			for(int i = 0; i < 25; ++i)
			{
				float fXDirection = MathUtility::RandomNumber(-2.0f, 2.0f);
				float fYDirection = MathUtility::RandomNumber(-2.0f, 2.0f);
				float fZDirection = MathUtility::RandomNumber(-2.0f, 2.0f);
				CVector3 Vec(fXDirection, fYDirection, fZDirection);
				CVector3 ThisPos;
				this->GetWorldMatrix().GetPosition(ThisPos);
				m_pRenderer->GetParticleManager().GetParticleInterface().CreateCannon(ThisPos, Vec, 0.5f);
			}
		}
	}


	for (unsigned int i = 0; i < uiNumEnemyInstances; ++i)
	{
		fDistanceToEnemy = CEntity::GetSquaredDistanceTo(vecEnemyInstances[i]);


		if (fDistanceToEnemy <= m_fAreaOfEffect)
		{
			if (m_pTargetEnemy != vecEnemyInstances[i])
			{
				HitEnemy(vecEnemyInstances[i]);
			}
		}
	}
}










/*---------------------------------------------------------------------------------------------------------------------------
*
* This function will remove the projectiles current target enemy.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CProjectile::RemoveCurrentTargetEnemy()
{
	m_pTargetEnemy = 0;
	CEntity::m_pTrackingEntity = 0;
}










/********************************
            Private
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function deinitialises the class instance by freeing memory and calling other necessary functions.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CProjectile::Deinitialise()
{
	FW_DELETE(m_pObjProjectile);
	FW_ADELETE(m_cpSndHit);


	CEventTarget::Deregister(EVENTSUBJECT_ENEMYDEATH);
}