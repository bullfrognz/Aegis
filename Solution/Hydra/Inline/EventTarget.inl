//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   EventTarget.inl
//  Description :  
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes


// Implementation

/*---------------------------------------------------------------------------------------------------------------------------
*
* Clears all events from the event system.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

void
CEventTarget::ClearAllEvents()
{
	m_mmapEventTargets.clear();
}






/*---------------------------------------------------------------------------------------------------------------------------
*
* Returns all event targets.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

std::multimap<EEventSubject, CEventTarget*>&
CEventTarget::GetEventTargets()
{
	return (m_mmapEventTargets);
}