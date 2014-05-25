//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   CStaticObject.h
//  Description :  
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_STATICOBJECT_H__
#define __IGFEB11_IG500_STATICOBJECT_H__


// Library Includes


// Local Includes
#include "Object.h"


// Types


// Constants


// Prototypes
class CD3DRenerer;


class CStaticObject : public CObject
{

	// Member Functions
public:


	         CStaticObject();
	virtual ~CStaticObject();


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


private:


	void Deinitialise();


	CStaticObject(const CStaticObject& _krStatiCStaticObject);
	CStaticObject& operator = (const CStaticObject& _krStatiCStaticObject);


	// Member Variables
protected:


private:


	CD3DRenderer* m_pRenderer;


	PreDrawCallback  m_vpPreDrawCallback;
	PostDrawCallback m_vpPostDrawCallback;


	unsigned int m_uiStaticMeshId;

	
	bool m_bVisible;


};


#include "Inline/StaticObject.inl"


#endif //__IGFEB11_IG500_STATICOBJECT_H__