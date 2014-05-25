//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   AnimatedObject.inl
//  Description :  
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CAnimatedObject::SetPredrawCallback(PreDrawCallback _vpPreDrawCallback)
{
	m_vpPreDrawCallback = _vpPreDrawCallback;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CAnimatedObject::SetPostdrawCallback(PostDrawCallback _vpPostDrawCallback)
{
	m_vpPostDrawCallback = _vpPostDrawCallback;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CAnimatedObject::SetMeshId(unsigned int _uiMeshId)
{
	m_uiAnimatedMeshId = _uiMeshId;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

unsigned int
CAnimatedObject::GetMeshId() const
{
	return (m_uiAnimatedMeshId);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void 
CAnimatedObject::SetVisible(bool _bVisible)
{
	m_bVisible = _bVisible;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CAnimatedObject::IsVisible() const
{
	return (m_bVisible);
}