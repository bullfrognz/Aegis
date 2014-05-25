//
//  Diploma of Interactive Gaming
//  Game Development 
//  Media Design School
//  Auckland
//  New Zealand
//
// (c) 2011 Media Design School
//
//  File Name   :   INI Parser.cpp
//  Description :   Template for implementation of CIniparser files
//  Author      :   Daniel Langsford
//  Mail        :   daniel.langsford@mediadesign.school.nz
//

#include <string>
#include "iniparser.h"
#include "strUtilities.h"

using namespace std;

/**
*
* INIParser constructor.
*
* @author Daniel Langsford
* @param 
* @return 
*
*/
CINIParser::CINIParser()
:m_CurrentSection("0")
,m_iComment(0)
{
}

/**
*
* This function saves information from containers into a file.
*
* @author Daniel Langsford
* @param _pcFileName: Name of the file to save into.
* @returns a bool representing whether or not the function succeeded. 
*
*/
bool 
CINIParser::SaveINIFile(const char *_pcFileName)
{
	string strTemp;

	ofstream INIFile;
	INIFile.open(_pcFileName);

	if(INIFile.is_open())
	{			
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
	return(true);	
}

/**
*
* This function opens a file from which variables will be read.
*
* @author Daniel Langsford
* @param _pcFileName: Name of the file to be opened.
* @returns a bool representing function success.
*
*/
bool
CINIParser::LoadINIFile(const char* _pcFileName)
{
	m_mapPairs.clear();


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
				int iStartPos = 0;
				int iEndPointPos = 0;
				int iLength = 0;
				iStartPos = static_cast<int>(strTest.find("["));
				iStartPos++;
				iEndPointPos = static_cast<int>(strTest.find("]"));
				iLength = (iEndPointPos - iStartPos);

				strSection = strTest.substr(iStartPos,iLength);
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
				char* pcValue = 0;
				char* pcItem = 0;

				::StrUtilities::Copy(strItem.c_str(), pcItem);
				::StrUtilities::Copy( strValue.c_str(), pcValue);

				::StrUtilities::Trim(pcItem);
				::StrUtilities::Trim(pcValue);

				strItem = pcItem;
				strValue = pcValue;

				AddValue(strSection.c_str(), strItem.c_str(), strValue.c_str());

				delete pcValue;
				pcValue = 0;

				delete pcItem;
				pcItem = 0;
			}	
		}
		INIFile.close();
		bSuccess = true;
	}
	return(bSuccess);
}

/**
*
* This function adds a value into the map at a given location. 
*
* @author Daniel Langsford
* @param _pcSection: The section of the file under which the value willl be added.
* @param _pcKey: The name of the value to be modified.
* @param _pcValue: The value of the modified variable.
* @returns a bool representing function success.
*
*/
bool
CINIParser::AddValue(const char* _pcSection, const char* _pcKey,
					 const char* _pcValue)
{
	bool bEntryAdded = false;

	string strSection = _pcSection;
	string strKey = _pcKey;
	string strValue = _pcValue;

	strSection = "[" + strSection + "]";

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

/**
*
* This function adds a comment into the map at a given location. 
*
* @author Daniel Langsford
* @param _pcComment: The comment that will be added to the current section.
* @returns a bool representing function success.
*
*/
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

/**
*
* This function returns a char value from the file.
*
* @author Daniel Langsford
* @param const char* _pcSection: Section in the file
* @param const char* _pcKey: the name of the variable
* @param char& _cValue: This will be populated and returned.
* @returns a bool, representing function success.
*
*/
bool
CINIParser::GetValue(const char* _pcSection, const char* _pcKey,
			  char& _cValue) const
{
	string strKey = _pcKey;

	string strSection = "[";
	strSection.append(_pcSection);
	strSection.append("]");

	strKey = strSection + '-' + strKey;

	map<string, string>::const_iterator iter;

	iter = m_mapPairs.find(strKey);

	if (iter == m_mapPairs.end())
	{
		return(false);
	}
	else
	{
		const string strAnswer = iter->second;
		string strFirstLetter = strAnswer.substr(0,1);
		_cValue = *(strFirstLetter.c_str());
	}

	return(true);

}

/**
*
* This function returns a wide char string value from the file.
*
* @author Daniel Langsford
* @param const char* _pcSection: Section in the file
* @param const char* _pcKey: the name of the variable
* @param wstring& _rwValue: This will be populated and returned.
* @returns a bool, representing function success.
*
*/
bool
CINIParser::GetValue(const char* _pcSection, const char* _pcKey,
std::wstring& _rwValue) const
{
	string strKey = _pcKey;

	string strSection = "[";
	strSection.append(_pcSection);
	strSection.append("]");

	strKey = strSection + '-' + strKey;

	map<string, string>::const_iterator iter;

	iter = m_mapPairs.find(strKey);

	if (iter == m_mapPairs.end())
	{
		return(false);
	}
	else
	{
		std::string rString = iter->second;

		const unsigned int kuiStringLength = static_cast<unsigned int>(rString.size() + 1);

		wchar_t* pTemp = new wchar_t[kuiStringLength];
		if (pTemp)
		{
			MultiByteToWideChar(CP_UTF8, 0, rString.c_str(), kuiStringLength, pTemp, kuiStringLength);
			_rwValue = pTemp;
			delete[] pTemp;
			pTemp = 0;
		}
	}

	return(true);
	
}

/**
*
* This function returns a string value from the file.
*
* @author Daniel Langsford
* @param const char* _pcSection: Section in the file
* @param const char* _pcKey: the name of the variable
* @param wstring& _rStrValue: This will be populated and returned.
* @returns a bool, representing function success.
*
*/
bool
CINIParser::GetValue(const char* _pcSection, const char* _pcKey,
						   string& _rStrValue) const
{
	string strKey = _pcKey;

	string strSection = "[";
	strSection.append(_pcSection);
	strSection.append("]");

	strKey = strSection + '-' + strKey;

	map<string, string>::const_iterator iter;

	iter = m_mapPairs.find(strKey);

	if (iter == m_mapPairs.end())
	{
		return(false);
	}
	else
	{
		_rStrValue = iter->second;
	}

	return(true);
}

/**
*
* This function returns an int value from the file.
*
* @author Daniel Langsford
* @param const char* _pcSection: Section in the file
* @param const char* _pcKey: the name of the variable
* @param wstring& _riValue: This will be populated and returned.
* @returns a bool, representing function success.
*
*/
bool
CINIParser::GetValue(const char* _pcSection, const char* _pcKey,
						int& _riValue) const
{
	string strKey = _pcKey;
	string strAnswer;

	string strSection = "[";
	strSection.append(_pcSection);
	strSection.append("]");
	strKey = strSection + '-' + strKey;

	map<string, string>::const_iterator iter;

	iter = m_mapPairs.find(strKey);

	if (iter == m_mapPairs.end())
	{
		return(false);
	}
	else
	{
		strAnswer = iter->second;
		strAnswer.c_str();
		_riValue = atoi(strAnswer.c_str());
	}

	return(true);
}

/**
*
* This function returns an unsigned int value from the file.
*
* @author Daniel Langsford
* @param const char* _pcSection: Section in the file
* @param const char* _pcKey: the name of the variable
* @param wstring& _ruiValue: This will be populated and returned.
* @returns a bool, representing function success.
*
*/
bool
CINIParser::GetValue(const char* _pcSection, const char* _pcKey,
						unsigned int& _ruiValue) const
{
	string strKey = _pcKey;
	string strAnswer;

	string strSection = "[";
	strSection.append(_pcSection);
	strSection.append("]");

	strKey = strSection + '-' + strKey;

	map<string, string>::const_iterator iter;

	iter = m_mapPairs.find(strKey);

	if (iter == m_mapPairs.end())
	{
		return(false);
	}
	else
	{
		strAnswer = iter->second;
		strAnswer.c_str();
		_ruiValue = atoi(strAnswer.c_str());
	}

	return(true);
}

/**
*
* This function returns a float value from the file.
*
* @author Daniel Langsford
* @param const char* _pcSection: Section in the file
* @param const char* _pcKey: the name of the variable
* @param wstring& _rfValue: This will be populated and returned.
* @returns a bool, representing function success.
*
*/
bool
CINIParser::GetValue(const char* _pcSection, const char* _pcKey,
						  float& _rfValue) const
{
	string strSection = "[";
	string strKey = _pcKey;
	string strAnswer;

	strSection.append(_pcSection);
	strSection.append("]");

	strKey = strSection + '-' + strKey;

	map<string, string>::const_iterator iter;

	iter = m_mapPairs.find(strKey);

	if (iter == m_mapPairs.end())
	{
		return(false);
	}
	else
	{
		strAnswer = iter->second;
		_rfValue = static_cast<float>(atof(strAnswer.c_str()));
	}
	return(true);
}

/**
*
* This function returns a bool value from the file.
*
* @author Daniel Langsford
* @param const char* _pcSection: Section in the file
* @param const char* _pcKey: the name of the variable
* @param wstring& _rbValue: This will be populated and returned.
* @returns a bool, representing function success.
*
*/
bool
CINIParser::GetValue(const char* _pcSection, const char* _pcKey,
						 bool& _rbValue) const
{
	string strKey = _pcKey;

	string strSection = "[";
	strSection.append(_pcSection);
	strSection.append("]");

	strKey = strSection + '-' + strKey;

	map<string, string>::const_iterator iter;

	iter = m_mapPairs.find(strKey);

	if(iter == m_mapPairs.end())
	{
		return(false);
	}

	else
	{
		const string Result = iter->second;
		if (Result == "true" || Result == "True" || Result == "On" || Result == "1" || Result == "on" ||
			Result == "ON" || Result == "TRUE")
		{
			_rbValue = true;
			return(true);
		}
		else 
		{
			_rbValue = false;
			return(true);
		}
	}
}

/**
*
* This function returns a 3D vector from the file.
*
* @author Daniel Langsford
* @param const char* _pcSection: Section in the file
* @param const char* _pcKey: the name of the variable
* @param wstring& _rvecValue: This will be populated and returned.
* @returns a bool, representing function success.
*
*/
bool
CINIParser::GetValue(const char* _pcSection, const char* _pcKey,
						D3DXVECTOR3& _rvecValue) const
{
	string strKey = _pcKey;
	float fX = 0;
	float fY = 0;
	float fZ = 0;
	int iLengthToX;
	int iLengthToY;
	int iTotalLength;

	string strSection = "[";
	strSection.append(_pcSection);
	strSection.append("]");

	strKey = strSection + '-' + strKey;	

	map<string, string>::const_iterator iter;

	iter = m_mapPairs.find(strKey);

	if (iter == m_mapPairs.end())
	{
		return(false);
	}
	else
	{		 
		const string strResult = m_mapPairs.find(strKey)->second;

		iTotalLength = static_cast<int>(strResult.length());
		
		string strModifier;
		iLengthToX = static_cast<int>(strResult.find(','));
		
		strModifier = strResult;
		strModifier = strResult.substr(iLengthToX + 1, iTotalLength);

		iLengthToY = static_cast<int>(strModifier.find(','));
		iLengthToY += iLengthToX + 1;

		string strX = strResult.substr(0, iLengthToX);
		float fX = static_cast<float>(atof(strX.c_str()));

		string strY = strResult.substr(iLengthToX + 1, iLengthToY);
		float fY = static_cast<float>(atof(strY.c_str()));

		string strZ = strResult.substr(iLengthToY + 1, iTotalLength);
		float fZ = static_cast<float>(atof(strZ.c_str()));

		_rvecValue = D3DXVECTOR3(fX,fY,fZ);

		return(true);
	}

}









