//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	Clock.inl
//	Description	:	Definition of inline functions for CClock
//	Author		:	Jade Abbott
//	Mail		:	20chimps@gmail.com
//

CClock::CClock()
{

}

CClock::~CClock()
{

}

/**
*
* Returns the delta time calculated by Process()
*
* @author Jade Abbott
* @return Delta time.
*
*/
const double&
CClock::GetDeltaTick() const
{
	return m_dDeltaTick;
}