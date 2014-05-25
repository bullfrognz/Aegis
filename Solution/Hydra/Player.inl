//
//	Diploma of Interactive Gaming
//	Media Design School
//	Auckland
//	New Zealand
//
//	(c) 2005 - 2011 Media Design School
//
//	File Name	:	Player.inl
//	Description	:	Definition of inline functions for CPlayer
//	Author		:	Jamie.smith
//	Mail		:	Jamie.Smith@mediadesign.school.nz
//


/**
*
* Returns the amount of lives
*
* @author Jamie Smith
* @return amount of lives.
*
*/
int
CPlayer::GetLives() const
{
	return(m_iLives);
}

/**
*
* Returns the amount of gold
*
* @author Jamie Smith
* @return amount of gold.
*
*/
unsigned int
CPlayer::GetGold() const
{
	return(m_uiGold);
}

/**
*
* Sets the amount of Gold
*
* @author Jamie Smith
* @Param amount of desired gold
* @return void
*
*/
void
CPlayer::SetGold(unsigned int _ui)
{
	m_uiGold = _ui;
}

/**
*
* Sets the amount of lives
*
* @author Jamie Smith
* @Param amount of desired Lives
* @return void
*
*/
void
CPlayer::SetLives(int _i)
{
	if(_i > 0)
	{
		m_iLives = _i;
	}
}


