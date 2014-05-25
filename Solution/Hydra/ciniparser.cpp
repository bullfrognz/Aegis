//
//  Diploma of Interactive Gaming
//  Game Development Faculty
//  Media Design School
//  Auckland
//  New Zealand
//
// (c) 2011 Media Design School
//
//  File Name   :   CINIParser.cpp
//  Description :   Template for implementation of CCiniparser files
//  Author      :   Daniel Langsford
//  Mail        :   daniel.langsford@mediadesign.school.nz
//

#include "ciniparser.h"
#include <string>

using namespace std;

CINIParser::CINIParser()
:m_CurrentSection("0")
,m_iComment(0)
{
}

bool 
CINIParser::SaveINIFile(const char *_pcFileName)
{
	bool bSuccess;

	string strTemp;

	ofstream INIFile;
	INIFile.open(_pcFileName);

	if(INIFile.is_open())
	{			
		bSuccess = true;
		map<string, string>::iterator iter = m_mapPairs.begin();	

		int iLineCount = 0;

		while (iter != m_mapPairs.end())
		{	
			string strKey;
			string strSection = iter->first;
			int iLength = static_cast<int>(strSection.length());
			int iPosition = static_cast<int>(strSection.find('-'));

			strKey = strSection.substr(iPosition+1, iLength);
			strSection = strSection.substr(0, iPosition);

			if (strSection != strTemp)
			{
				if(iLineCount > 0)
				{
					INIFile << endl;
				}
				
				if (iter->second[0] != ';')
				{
					INIFile << strSection << endl;
					INIFile << endl;
				}
			}
	
			if (iter->second[0] != ';')
			{
				strTemp = strSection;				
				INIFile << strKey;
				INIFile << " = ";
			}
			
			INIFile << iter->second << endl;			

			iter++;
			iLineCount++;
		}			
	}

	INIFile.close();
	return(bSuccess);	
}

bool
CINIParser::LoadINIFile(const char* _pcFileName)
{
	string strTest;
	string strSection;

	bool bSuccess = false;

	int iPosition = 0;
	int iLength = 0;

	ifstream INIFile;
	INIFile.open(_pcFileName);

	if (INIFile.is_open())
	{
		while (!INIFile.eof())
		{
			string strItem;
			string strValue;
			string strKey;
			string strComment;

			bool bComment = false;

			getline(INIFile, strTest);
			if (strTest[0] == ' ')
			{
				//Empty line
				AddValue(" ", " ", " ");

			}			
			else if (strTest[0] == ';')
			{
				//Comment.
				if(m_CurrentSection != "0")
				{
					strComment = strTest;
					AddComment(strTest.c_str());							
				}
			}
			else if (strTest[0] == '[')
			{
				//Section.
				strSection = strTest;
				m_CurrentSection = strSection;				 
			}			
			else
			{
				//Variable.	
				iPosition = static_cast<int> (strTest.find('='));
				if (iPosition < 0)
				{
					iPosition = 0;
				}

				iLength =static_cast<int> (strTest.length());

				if (iPosition != 0 && iLength != 0)
				{
					strItem = strTest.substr(0, iPosition - 1);
					strValue = strTest.substr(iPosition + 1, iLength);
				}
			}			
			if (strSection != "" && strItem != "" && strValue != "")
			{
				AddValue(strSection.c_str(), strItem.c_str(), strValue.c_str());				
			}	
		}
		INIFile.close();
		bSuccess = true;
	}
	return(bSuccess);
}


bool
CINIParser::AddValue(const char* _pcSection, const char* _pcKey,
					 const char* _pcValue)
{
	bool bEntryAdded = false;

	string strSection = _pcSection;
	string strKey = _pcKey;
	string strValue = _pcValue;

	strKey = strSection + '-' + strKey;

	m_mapPairs[strKey] = strValue;

	map<string, string>::iterator iter;
	iter = m_mapPairs.find(strKey);

	if (iter == m_mapPairs.end())
	{
		bEntryAdded = false;
	}
	else 
	{
		bEntryAdded = true;
	}
	
	return(bEntryAdded);	
}

bool
CINIParser::AddComment (const char* _pcComment)
{
	bool bEntryAdded = false;
	string strCommentName = "              ";
	
	string strSection = m_CurrentSection;
	string strKey = strCommentName.substr(0, m_iComment);
	string strValue = _pcComment;	
	
	strKey = strSection + '-' + strKey;

	m_mapPairs[strKey] = strValue;
	
	map<string, string>::iterator iter;
	iter = m_mapPairs.find(strKey);

	if (iter == m_mapPairs.end())
	{
		bEntryAdded = false;
	}
	else 
	{
		bEntryAdded = true;
	}
	
	m_iComment++;

	return(bEntryAdded);	
}

bool
CINIParser::GetStringValue(const char* _pcSection, const char* _pcKey,
						   string& _rStrValue)
{
	string strSection = _pcSection;
	string strKey = _pcKey;
	strKey = strSection + '-' + strKey;

	map<string, string>::iterator iter;

	iter = m_mapPairs.find(strKey);

	if (iter == m_mapPairs.end())
	{
		return(false);
	}
	else
	{
		_rStrValue = m_mapPairs[strKey];
	}

	return(true);
}


bool
CINIParser::GetIntValue(const char* _pcSection, const char* _pcKey,
						int& _riValue)
{
	string strSection = _pcSection;
	string strKey = _pcKey;
	string strAnswer;

	strKey = strSection + '-' + strKey;

	map<string, string>::iterator iter;

	iter = m_mapPairs.find(strKey);

	if (iter == m_mapPairs.end())
	{
		return(false);
	}
	else
	{
		strAnswer = m_mapPairs[strKey];
		strAnswer.c_str();
		_riValue = atoi(strAnswer.c_str());
	}

	return(true);
}

bool
CINIParser::GetFloatValue(const char* _pcSection, const char* _pcKey,
						  float& _rfValue)
{
	string strSection = _pcSection;
	string strKey = _pcKey;
	string strAnswer;

	strKey = strSection + '-' + strKey;

	map<string, string>::iterator iter;

	iter = m_mapPairs.find(strKey);

	if (iter == m_mapPairs.end())
	{
		return(false);
	}
	else
	{
		strAnswer = m_mapPairs[strKey];
		strAnswer.c_str();
		_rfValue = static_cast<float>(atof(strAnswer.c_str()));
	}
	return(true);
}

bool
CINIParser::GetBoolValue(const char* _pcSection, const char* _pcKey,
						 bool& _rbValue)
{
	string strSection = _pcSection;
	string strKey = _pcKey;
	strKey = strSection + '-' + strKey;
	string Result;
	bool bReturn;

	Result = m_mapPairs[strKey];
	if (Result == "true" || Result == "True" || Result == "On" || Result == "1")
	{
		bReturn = true;
	}
	else 
	{
		bReturn = false;
	}
	return(true);
}

bool
CINIParser::GetVectorValue(const char* _pcSection, const char* _pcKey,
						D3DXVECTOR3& _rvecValue)
{
	string strSection = _pcSection;
	string strKey = _pcKey;
	string strResult;
	float fX;
	float fY;
	float fZ;
	int iLengthToX;
	int iLengthToY;
	int iTotalLength;

	strKey = strSection + '-' + strKey;

	map<string, string>::iterator iter;

	iter = m_mapPairs.find(strKey);

	if (iter == m_mapPairs.end())
	{
		return(false);
	}
	else
	{		 
		strResult = m_mapPairs[strKey];

		iTotalLength = static_cast<int>(strResult.length());
		
		string strModifier;
		iLengthToX = static_cast<int>(strResult.find(','));
		
		strModifier = strResult;
		strModifier = strResult.substr(iLengthToX + 1, iTotalLength);

		iLengthToY = static_cast<int>(strModifier.find(','));
		iLengthToY += iLengthToX + 1;

		string strX = strResult.substr(0, iLengthToX);
		float fX = atof(strX.c_str());

		string strY = strResult.substr(iLengthToX + 1, iLengthToY);
		float fY = atof(strY.c_str());

		string strZ = strResult.substr(iLengthToY + 1, iTotalLength);
		float fZ = atof(strZ.c_str());

		_rvecValue = D3DXVECTOR3(fX,fY,fZ);
	}

}









