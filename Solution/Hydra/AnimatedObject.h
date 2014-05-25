//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   AnimatedObject.h
//  Description :   
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_ANIMATEDOBJECT_H__
#define __IGFEB11_IG500_ANIMATEDOBJECT_H__


// Library Includes


// Local Includes
#include "Object.h"


// Types


// Constants


// Prototypes


class CAnimatedObject : public CObject
{

	// Member Functions
public:


	         CAnimatedObject();
	virtual ~CAnimatedObject();


	virtual bool Initialise(char* _cpEntityName, CD3DRenderer* _pRenderer, unsigned int _uiMeshId = Utility::INVALID_ID);
	virtual bool Initialise(char* _cpEntityName, CD3DRenderer* _pRenderer, const char* _kcpMeshFile);

	virtual void Process(float _fDeltaTick);

	virtual void Draw(CD3DRenderer* _pRenderer, void* _pClassInstance = 0);


	// Inline Functions
	virtual inline void SetPredrawCallback(PreDrawCallback _vpPreDrawCallback);
	virtual inline void SetPostdrawCallback(PostDrawCallback _vpPostDrawCallback);


	virtual inline void SetMeshId(unsigned int _uiMeshId);
	virtual inline unsigned int GetMeshId() const;


	virtual inline void SetVisible(bool _bVisible);
	virtual inline bool IsVisible() const;


protected:

	virtual void PreDraw(CD3DRenderer* _pRenderer);
	virtual void PostDraw(CD3DRenderer* _pRenderer);


private:


	void Deinitialise();


	CAnimatedObject(const CAnimatedObject& _krAnimatedObject);
	CAnimatedObject& operator = (const CAnimatedObject& _krAnimatedObject);


	// Member Variables
protected:


	unsigned int m_uiAnimatedMeshId;


private:


	CD3DRenderer* m_pRenderer;


	PreDrawCallback  m_vpPreDrawCallback;
	PostDrawCallback m_vpPostDrawCallback;


	bool m_bVisible;


};


#include "Inline/AnimatedObject.inl"


#endif //__IGFEB11_IG500_ANIMATEDOBJECT_H__