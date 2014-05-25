//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Frame.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_FRAME_H__
#define __IGFEB11_IG500_FRAME_H__


// Library Includes
#include <d3dx9.h>


// Local Includes
#include "Matrix.h"


// Types


// Constants


// Prototypes


class CFrame : public D3DXFRAME
{

	// Member Functions
public:


	 CFrame();
	 CFrame(D3DXFRAME& _d3drFrame);
	 CFrame(D3DXFRAME* _d3dpFrame);
	~CFrame();


	bool Initialise(const char* _kcpFrameName);


	// Inline Functions


protected:


private:


	void Deinitialise();


	CFrame(const CFrame& _krFrame);
	CFrame& operator = (const CFrame& _krFrame);


	// Member Variables
protected:


public:


	CMatrix m_mtxCombined;


};


#endif //__IGFEB11_IG500_FRAME_H__