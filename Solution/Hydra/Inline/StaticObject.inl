//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   StatiCStaticObject.inl
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
CStaticObject::SetPredrawCallback(PreDrawCallback _vpPreDrawCallback)
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
CStaticObject::SetPostdrawCallback(PostDrawCallback _vpPostDrawCallback)
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
CStaticObject::SetMeshId(unsigned int _uiMeshId)
{
	m_uiStaticMeshId = _uiMeshId;
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

unsigned int
CStaticObject::GetMeshId() const
{
	return (m_uiStaticMeshId);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function 
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void 
CStaticObject::SetVisible(bool _bVisible)
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
CStaticObject::IsVisible() const
{
	return (m_bVisible);
}