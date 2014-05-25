//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
//  (c) 2011 Media Design School
//
//  Author		:	Team Blue
//  Mail		:	Jamie.Smith@mediadesign.school.nz
//				:	jade.abbott@mediadesign.school.nz
//				:	bryce.booth@mediadesign.school.nz
//				:	joshua.print@mediadesign.school.nz
//				:	daniel.langsford@mediadesign.school.nz
//


#pragma once


#ifndef __IGFEB11_IG500_MACROS_H__
#define __IGFEB11_IG500_MACROS_H__


// Library Includes
#include <map>
#include <vector>
#include <windows.h>


// Local Includes
#include "Application.h"
#include "Window.h"
#include "StrUtilities.h"


// Implementation


#define FW_VALIDATE(Function, ErrorMessage)\
if (Function == false)\
{\
	DISPLAYERROR(ErrorMessage, L"Fatal Error", MB_OK | MB_ICONERROR)\
	return (false);\
}


#define FW_HVALIDATE(__hResult, ErrorMessage)\
if (FAILED(__hResult))\
{\
	DISPLAYERROR(ErrorMessage, L"Fatal Error", MB_OK | MB_ICONERROR)\
	return (false);\
}


#if _DEBUG

#define FW_BREAK() _CrtDbgBreak();

#else

#define FW_BREAK() ; // goto FatalErrorClose

#endif


#define FW_FILLARRAY(Variable, NumElements, Filler)\
{\
	for (UINT __ui = 0; __ui < NumElements; ++ __ui)\
	{\
		 Variable[__ui] = Filler;\
	}\
}


#define FW_FILLMARRAY(Variable, NumRows, NumElements, Filler)\
{\
	for (UINT __uj = 0; __uj < NumRows; ++ __uj)\
	{\
		 FW_FILLARRAY(Variable[__uj], NumElements, Filler);\
	}\
}


#define FW_RELEASE(Variable)\
{\
	if (Variable != 0)\
	{\
		Variable->Release();\
		Variable = 0;\
	}\
}


#define FW_DELETE(Variable)\
{\
	delete Variable;\
	Variable = 0;\
}


#define FW_ADELETE(ArrayVariable)\
{\
	delete[] ArrayVariable;\
	ArrayVariable = 0;\
}


#define FW_DELETEMAP(KeyType, ValueType, Variable)\
{\
	std::map<KeyType, ValueType>::iterator iterElement;\
	iterElement = Variable.begin();\
	\
	while (iterElement != Variable.end())\
	{\
		FW_DELETE((*iterElement).second);\
		\
		\
		iterElement = Variable.erase(iterElement);\
	}\
}


#define FW_DELETEVECTOR(Type, Variable)\
{\
	std::vector<Type>::iterator iterElement;\
	iterElement = Variable.begin();\
	\
	while (iterElement != Variable.end())\
	{\
		FW_DELETE((*iterElement));\
		\
		\
		iterElement = Variable.erase(iterElement);\
	}\
}


#define FW_DELETEARRAY(Variable, NumElements)\
{\
	for (UINT __ui = 0; __ui < NumElements; ++__ui)\
	{\
		FW_DELETE(Variable[__ui]);\
	}\
}


#define FW_DELETEMARRAY(Variable, NumContainers, NumElements)\
{\
	for (UINT __uiContainer = 0; __uiContainer < NumContainers; ++__uiContainer)\
	{\
		FW_DELETEARRAY(Variable[NumContainers][__ui], NumElements);\
	}\
}


#define LOG_ERROR(Condition, ErrorMessage)\
{\
	if (Condition == true)\
	{\
		DISPLAYERROR(ErrorMessage, L"warning", MB_OK | MB_ICONWARNING);\
	}\
}


#define LOG_FATALERROR(Condition, ErrorMessage)\
{\
	if (Condition == true)\
	{\
		DISPLAYERROR(ErrorMessage, L"Fatal Error", MB_OK | MB_ICONERROR)\
		FW_BREAK();\
	}\
}


#define DISPLAYERROR(ErrorMessage, Title, Parameters)\
{\
	wchar_t* wcpBuffer = 0;\
	StrUtilities::ConvertToWChar(ErrorMessage, wcpBuffer);\
	MessageBox(CApplication::GetInstance().GetGameWindow().GetWindowHandle(), wcpBuffer, Title, Parameters);\
	FW_DELETE(wcpBuffer);\
}


#endif //__IGFEB11_IG500_MACROS_H__