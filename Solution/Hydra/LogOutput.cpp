//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
// (c) 2010 Media Design School
//
//  File Name   :   LogOutput.cpp
//  Description :   Template for implementation of CLogfile files
//  Author      :   Daniel Langsford
//  Mail        :   daniel.langsford@mediadesign.school.nz
//

#include "LogOutput.h"

/**
*
* This function writes a message to the output window in the IDE
*
* @author Daniel Langsford
* @param const char* _pcMessage: Message to be logged to output.
* @return void:
*
*/
void
CLogOutput::Write (const char* _pcMessage)
{
	int iMsgLen = lstrlenA(_pcMessage);

	int iWMsgLen = MultiByteToWideChar(CP_ACP, 0, _pcMessage, iMsgLen, 0, 0);

	wchar_t* pcMessage = new wchar_t[iWMsgLen]; 

	MultiByteToWideChar(CP_ACP, 0, _pcMessage, iMsgLen, pcMessage, iWMsgLen);

	pcMessage[iWMsgLen] = 0;

	OutputDebugString(pcMessage);
}

