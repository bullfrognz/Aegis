//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   Object.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_OBJECT_H__
#define __IGFEB11_IG500_OBJECT_H__


// Library Includes


// Local Includes
#include "Utility.h"
#include "Entity.h"
#include "Matrix.h"
#include "Planes.h"


// Types
typedef void (*PreDrawCallback)(void*, CD3DRenderer*);
typedef void (*PostDrawCallback)(void*, CD3DRenderer*);


// Constants


// Prototypes
class CD3DRenderer;


class CObject : public CEntity
{

	// Member Functions
public:


			 CObject() {};
	virtual ~CObject() {};


	virtual bool Initialise(char* _cpEntityName, CD3DRenderer* _pRenderer, unsigned int _uiMeshId = Utility::INVALID_ID) = 0;
	virtual bool Initialise(char* _cpEntityName, CD3DRenderer* _pRenderer, const char* _kcpMeshFile) = 0;

	virtual void Process(float _fDeltaTick) = 0;

	virtual void Draw(CD3DRenderer* _pRenderer, void* _pClassInstance = 0) = 0;


	// Inline Functions
	virtual inline void SetPredrawCallback(PreDrawCallback _vpPreDrawCallback) = 0;
	virtual inline void SetPostdrawCallback(PostDrawCallback _vpPostDrawCallback) = 0;


	virtual inline void SetMeshId(unsigned int _uiMeshId) = 0;
	virtual inline unsigned int GetMeshId() const = 0;


	virtual inline void SetVisible(bool _bVisible) = 0;
	virtual inline bool IsVisible() const = 0;

protected:



private:


	// Member Variables
protected:


private:


};


#endif //__IGFEB11_IG500_OBJECT_H__