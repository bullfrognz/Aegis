//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	Particle.inl
//	Description	:	Definition of inline CParticle functions
//	Author		:	Jade Abbott
//	Mail		:	jade.abbott@mediadesign.school.nz
//

void
CParticle::SetPosition(const D3DXVECTOR3& _rkVecPos)
{
	m_vecPos = _rkVecPos;
}

const D3DXVECTOR3&
CParticle::GetPosition() const
{
	return m_vecPos;
}