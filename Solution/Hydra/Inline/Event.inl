//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Event.inl
//  Description :  
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation


/*---------------------------------------------------------------------------------------------------------------------------
*
* Sets the data for the event.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEvent::SetData(void* _pData)
{
	m_pData = _pData;
}









/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the subject for the event.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

unsigned int
CEvent::GetSubject() const
{
	return (m_uiSubject);
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns the data for the event.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

const void*
CEvent::GetData() const
{
	return (m_pData);
}