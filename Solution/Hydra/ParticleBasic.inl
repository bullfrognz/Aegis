//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	ParticleBasic.inl
//	Description	:	Definition of inline CParticleBasic functions, inheriting from pure virtual CParticle
//	Author		:	Jamie Smith
//	Mail		:	jamie.smith@mediadesign.school.nz
//

/**
*
* Constructs a basic particle without having to initialise.
*
* @author Jamie Smith
* @param _rkVecPos The initial position of this bullet.
* @param _rkVecMovement The direction and speed of this bullet.
*
*/
CParticleBasic::CParticleBasic(const D3DXVECTOR3& _rkVecPos, const D3DXVECTOR3& _rkVecMovement, float _fLifetime)
: m_vecMovement(_rkVecMovement)
, m_fLifetime(_fLifetime)
{
	m_vecPos = _rkVecPos;
}