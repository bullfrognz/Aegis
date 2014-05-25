//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  File Name   :   SettingsScene.h
//  Description :   The scene for change settings of the application 
//					to the users preferences.			
//	
//  Author      :   Bryce Booth
//  Mail        :   bryce.booth@mediadesign.school.nz
//
//  Editor Log:
//  - 
//


#pragma once


#ifndef __IGFEB11_IG500_SETTINGSSCENE_H__
#define __IGFEB11_IG500_SETTINGSSCENE_H__


// Library Includes
#include <d3dx9.h>
#include <map>
#include <vector>
#include <windows.h>
#include <string>


// Local Includes
#include "Scene.h"
#include "XButtonTarget.h"
#include "XAnalogTarget.h"
#include "DMouseTarget.h"
#include "DKeyboardTarget.h"
#include "Text.h"


// Types
enum ESettingsOption
{
	SETTINGSOPTION_INVALID = -1,

	SETTINGSOPTION_RESOLUTION,
	SETTINGSOPTION_MODE,
	SETTINGSOPTION_MULTISAMPLING,
	SETTINGSOPTION_VOLUME,
	SETTINGSOPTION_SAVE,
	SETTINGSOPTION_BACK,

	SETTINGSOPTION_MAX
};


// Constants


// Prototypes
class CSettingsSceneData;


class CSettingsScene : public CScene, public IDMouseTarget, public IDKeyboardTarget, public IXButtonTarget, public IXAnalogTarget
{

	// Member Functions
public:

   
	         CSettingsScene();
	virtual ~CSettingsScene();


	virtual bool InitialiseScene(CD3DRenderer* _pRenderer, void* _pSceneData = 0);
	virtual void ProcessScene(float _fDeltaTick);
	virtual void DrawScene(CD3DRenderer* _pRenderer);


	// Inline Functions


protected:
	void SpriteSelection();
	void TextSelection();


	virtual bool InitialiseLights(CD3DRenderer* _pRenderer);
	virtual bool InitialiseViewports(CD3DRenderer* _pRenderer);


	virtual void HandleDMouseInput(EDInputMouse _eDMouse, bool _bDown, long _lValue);
	virtual void HandleDKeyboardInput(EDInputKeyboard _eDKebyoard, bool _bDown = false);
	virtual void HandleXAnalogInput(EXInputAnalog _eXAnalog, float _fValue = 0.0f);
	virtual void HandleXButtonInput(EXInputButton _eXButton, bool _bDown = false);


private:

	bool InitialisePlayerInputTarget();
	bool InitialiseXInputTarget();
	bool InitialiseSprites(CD3DRenderer* _pRenderer);
	bool InitialiseSpritePositons(CD3DRenderer* _pRenderer);
	bool InitialiseResolutions(CD3DRenderer* _pRenderer);
	bool InitialiseModeTypes();
	bool InitialiseMultiSamplingTypes(CD3DRenderer* _pRenderer, bool _bFullscreen);
	bool InitialiseVolumeTypes();
	bool InitialiseText(CD3DRenderer* _pRenderer);

	void ResetCursor();

	void IncrementCurrentSection();
	void DecrementCurrentSection();


	void IncrementSectionValue();
	void DecrementSectionValue();


	void UpdateSectionText();
	void UpdateSectionSprites();
	void ShadeAllSections();
	void HighlightCurrentSection();


	void ExecuteSaveSettings();


	void ReturnToBeforeScene(unsigned int _uiScreenWidth = 0, unsigned int _uiScreenHeight = 0);


	void Deinitialise();


	CSettingsScene(const CSettingsScene& _krSettingsScene);
	CSettingsScene& operator = (const CSettingsScene& _krSettingsScene);


// Member Variables
protected:	


private:


	CSettingsSceneData* m_pSettingsSceneData;
	ESettingsOption     m_eCurrentOption;


	static enum
	{
		s_uiLeftArrowMarginX  = 650,
		s_uiRightArrowMartinX = 1050,


		s_iSpriteShadeColour = 0xFF999999,
		s_iSpriteHoverColour = 0xFFFFFFFF,


		s_iTextShadeColour = 0xFFBBBBBB,
		s_iTextHoverColour = 0xFFFFFFFF,
	};


	//Lights
	unsigned int m_uiLightDirectional;


	//Settings
	unsigned int m_uiSettingsBackground;
	unsigned int m_uiSettingsLogo;


	//Resolution
	unsigned int m_uiResolutionTitle;
	unsigned int m_uiResolutionArrowLeft;
	unsigned int m_uiResolutionArrowRight;


	//Mode
	unsigned int m_uiModeTitle;
	unsigned int m_uiModeArrowLeft;
	unsigned int m_uiModeArrowRight;


	//Multisampling
	unsigned int m_uiMultisamplingTitle;
	unsigned int m_uiMultisamplingArrowLeft;
	unsigned int m_uiMultisamplingArrowRight;


	//Volume
	unsigned int m_uiVolumeTitle;
	unsigned int m_uiVolumeArrowLeft;
	unsigned int m_uiVolumeArrowRight;


	//Apply
	unsigned int m_uiSaveTitle;
	unsigned int m_uiBackTitle;


	float m_fChangeSectionDelay;
	float m_fChangeSectionTimer;


	float m_fChangeValueDelay;
	float m_fChangeValueTimer;


	//Text
	CText m_TextResolution;
	CText m_TextMode;
	CText m_TextMultiSample;
	CText m_TextVolume;


	//Containers
	std::map<unsigned int, char*> m_mapResolutionTypes;		//Mode -> Text
	std::map<bool, char*> m_mapModeTypes;					//Windowed -> Text
	std::map<unsigned int, char*> m_mapMultiSampleTypes;	//Multisample type -> Text
	std::map<float, char*> m_mapVolumeTypes;				//Volume -> Text


	unsigned int m_uiResolutionMode;
	bool m_bWindowMode;
	unsigned int m_uiMultiSampleType;
	float m_fVolume;


	bool m_bMouseClick;
	bool m_bSpriteSelected;


	bool m_bIncrementValue;
	bool m_bDecrementValue;
	bool m_bIncrementSection;
	bool m_bDecrementSection;


	std::vector<D3DDISPLAYMODE> m_vecDisplayModes;


};


#endif //__IGFEB11_IG500_SETTINGSSCENE_H__