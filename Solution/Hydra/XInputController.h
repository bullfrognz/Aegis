//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   XInputController.h
//  Description :   Keeps track of xinput controller states
//					and sends changed states to targets.
//
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_XINPUTCONTROLLER_H__
#define __IGFEB11_IG500_XINPUTCONTROLLER_H__


// Library Includes
#include <XInput.h>
#include <map>
#include <vector>


// Local Includes


// Types
enum EXInputButton
{
	XBUTTON_INVALID = -1,

	XBUTTON_DPADUP,
	XBUTTON_DPADDOWN,
	XBUTTON_DPADLEFT,
	XBUTTON_DPADRIGHT,
	XBUTTON_START,
	XBUTTON_BACK,
	XBUTTON_THUMBLEFT,
	XBUTTON_THUMBRIGHT,
	XBUTTON_BUMPERLEFT,
	XBUTTON_BUMPERRIGHT,
	XBUTTON_A,
	XBUTTON_B,
	XBUTTON_X,
	XBUTTON_Y,

	XBUTTON_MAX,
};


enum EXInputTrigger
{
	XTRIGGER_INVALID = -1,

	XTRIGGER_LEFT,
	XTRIGGER_RIGHT,

	XTRIGGER_MAX
};


enum EXInputAnalog
{
	XANALOG_INVALID = -1,

	XANALOG_LEFTX,
	XANALOG_LEFTY,

	XANALOG_RIGHTX,
	XANALOG_RIGHTY,

	XANALOG_MAX
};


enum EXRumbleLevel
{
	XRUMBLELVL_0 = 0,
	XRUMBLELVL_1 = 12800,
	XRUMBLELVL_2 = 19200,
	XRUMBLELVL_3 = 25600,
	XRUMBLELVL_4 = 32000,
};


// Constants


// Prototypes
class IXButtonTarget;
class IXTriggerTarget;
class IXAnalogTarget;


class CXInputController
{

	// Member Functions
public:


	 CXInputController();
	~CXInputController();


	bool Initialise();
	void Process(float _fDeltaTick);


	void AddTarget(EXInputButton _eXButton, IXButtonTarget* _pTarget);
	void AddTarget(EXInputTrigger _eXTrigger, IXTriggerTarget* _pTarget);
	void AddTarget(EXInputAnalog _eXAnalogue, IXAnalogTarget* _pTarget);


	void RemoveTarget(EXInputButton _eXButton, IXButtonTarget* _pTarget);
	void RemoveTarget(EXInputTrigger _eXTrigger, IXTriggerTarget* _pTarget);
	void RemoveTarget(EXInputAnalog _eXAnalogue, IXAnalogTarget* _pTarget);


	// Inline Functions
	inline void SetRumbleLeft(EXRumbleLevel _eLevel, float _fTime);
	inline void SetRumbleRight(EXRumbleLevel _eLevel, float _fTime);


	inline bool IsPluggedIn();
	inline void SetDisabled(bool _bDisabled);
	inline bool IsDisabled() const;


protected:


	void ProcessRumble(float _fDeltaTick);


	void RefreshRumbleState();
	void RefreshPluggedIn();


	void SaveCurrentState();


	void ReadButtonStates(XINPUT_GAMEPAD& _xrGamePad);
	void ReadAnalogueStates(XINPUT_GAMEPAD& _xrGamePad);
	void ReadTriggerStates(XINPUT_GAMEPAD& _xrGamePad);


	void DispatchButtonStates();
	void DispatchAnalogStates();
	void DispatchTriggerStates();
	

	void StoreCurrentStates();


	void SendInputToTargets(EXInputButton _eXButton);
	void SendInputToTargets(EXInputTrigger _eXTrigger);
	void SendInputToTargets(EXInputAnalog _eXAnalogue);


private:


	void Deinitialise();


	CXInputController(const CXInputController& _krXInputController);
	CXInputController& operator = (const CXInputController& _krXInputController);


	// Member Variables
protected:


private:


	float m_fAnalogueStates[XANALOG_MAX];
	float m_fPreviousAnalogueStates[XANALOG_MAX];


	float m_fTriggerStates[XTRIGGER_MAX];
	float m_fPreviousTriggerStates[XTRIGGER_MAX];


	bool m_bButtonStates[XBUTTON_MAX];
	bool m_bPreviousButtonStates[XBUTTON_MAX];


	EXRumbleLevel m_eRumbleLevelLeft;
	EXRumbleLevel m_eRumbleLevelRight;


	unsigned long m_uiLastPacketId;


	unsigned int m_uiThumbLeftDeadZone;


	float m_fLRumbleTimer;
	float m_fRRumbleTimer;


	bool m_bPluggedIn;
	bool m_bDisabled;


	std::vector<IXButtonTarget*>  m_vecXButtonTargets[XBUTTON_MAX];
	std::vector<IXAnalogTarget*>  m_vecXAnalogueTargets[XANALOG_MAX];
	std::vector<IXTriggerTarget*> m_vecXTriggerTargets[XTRIGGER_MAX];


};


#include "Inline/XInputController.inl"


#endif //__IGFEB11_IG500_XINPUTCONTROLLER_H__