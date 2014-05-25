//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name :   Frame.cpp
//
//  Author    :   Bryce Booth
//  Mail      :   bryce.booth@mediadesign.school.nz
//


// Library Includes


// Local Includes
#include "Macros.h"
#include "StrUtilities.h"


// This Include
#include "Frame.h"


// Static Variables


// Implementation


/********************************
            Public
*********************************/


/*---------------------------------------------------------------------------------------------------------------------------
*
* Frame class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CFrame::CFrame()
{
	ZeroMemory(this, sizeof(CFrame));
	D3DXMatrixIdentity(&m_mtxCombined);
	D3DXMatrixIdentity(&(D3DXFRAME::TransformationMatrix));
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Frame class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CFrame::CFrame(D3DXFRAME& _d3drFrame)
{
	ZeroMemory(this, sizeof(CFrame));
	D3DXMatrixIdentity(&m_mtxCombined);
	D3DXMatrixIdentity(&(D3DXFRAME::TransformationMatrix));

	Name				 = _d3drFrame.Name;
	TransformationMatrix = _d3drFrame.TransformationMatrix;
	pMeshContainer		 = _d3drFrame.pMeshContainer;
	pFrameSibling		 = _d3drFrame.pFrameSibling;
	pFrameFirstChild	 = _d3drFrame.pFrameFirstChild;
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Frame class constructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CFrame::CFrame(D3DXFRAME* _d3dpFrame)
{
	ZeroMemory(this, sizeof(CFrame));
	D3DXMatrixIdentity(&m_mtxCombined);
	D3DXMatrixIdentity(&(D3DXFRAME::TransformationMatrix));

	Name				 = _d3dpFrame->Name;
	TransformationMatrix = _d3dpFrame->TransformationMatrix;
	pMeshContainer		 = _d3dpFrame->pMeshContainer;
	pFrameSibling		 = _d3dpFrame->pFrameSibling;
	pFrameFirstChild	 = _d3dpFrame->pFrameFirstChild;
}


/*---------------------------------------------------------------------------------------------------------------------------
*
* Frame class deconstructor
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

CFrame::~CFrame()
{
	Deinitialise();
}








/*---------------------------------------------------------------------------------------------------------------------------
*
* This function initialisings the class instance before use.
*
* @author Bryce Booth
*
*---------------------------------------------------------------------------------------------------------------------------*/

bool
CFrame::Initialise(const char* _kcpFrameName)
{
	//Check name valid
	if (strlen(_kcpFrameName) == 0)
	{
		//Set default name
		StrUtilities::Copy("<Unnamed Frame>", D3DXFRAME::Name);
	}
	else
	{
		///Copy frame name
		StrUtilities::Copy(_kcpFrameName, D3DXFRAME::Name);
	}


	return (true);
}








/********************************
            Protected
*********************************/









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
CFrame::Deinitialise()
{
	delete[] D3DXFRAME::Name;
	D3DXFRAME::Name = 0;
}