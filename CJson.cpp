#include "pch.h"
#include "CJson.h"

#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <direct.h>
#include <string>
#include "Log.h"

using json = nlohmann::json;

CString JSONGetProgramPath()
{
	CString  strProgramPath;
	GetModuleFileName(NULL, strProgramPath.GetBuffer(MAX_PATH), MAX_PATH);
	strProgramPath.ReleaseBuffer(MAX_PATH);
	int nPathPos = strProgramPath.ReverseFind('\\');
	strProgramPath = strProgramPath.Left(nPathPos + 1);
	return strProgramPath;
}

static std::string ConvertCStringToUTF8(CString strValue)
{
	std::wstring wbuffer;
#ifdef _UNICODE
	wbuffer.assign(strValue.GetString(), strValue.GetLength());
#else
	/*
	 * 转换ANSI到UNICODE
	 * 获取转换后长度
	 */
	int length = ::MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, (LPCTSTR)strValue, -1, NULL, 0);
	wbuffer.resize(length);
	/* 转换 */
	MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strValue, -1, (LPWSTR)(wbuffer.data()), wbuffer.length());
#endif

	/* 获取转换后长度 */
	int length = WideCharToMultiByte(CP_UTF8, 0, wbuffer.data(), wbuffer.size(), NULL, 0, NULL, NULL);
	/* 获取转换后内容 */
	std::string buffer;
	buffer.resize(length);

	WideCharToMultiByte(CP_UTF8, 0, strValue, -1, (LPSTR)(buffer.data()), length, NULL, NULL);
	return(buffer);
}

static CString ConvertUTF8ToCString(std::string utf8str)
{
	/* 预转换，得到所需空间的大小 */
	int nLen = ::MultiByteToWideChar(CP_UTF8, NULL,
		utf8str.data(), utf8str.size(), NULL, 0);
	/* 转换为Unicode */
	std::wstring wbuffer;
	wbuffer.resize(nLen);
	::MultiByteToWideChar(CP_UTF8, NULL, utf8str.data(), utf8str.size(),
		(LPWSTR)(wbuffer.data()), wbuffer.length());

#ifdef UNICODE
	return(CString(wbuffer.data(), wbuffer.length()));
#else
	/*
	 * 转换为ANSI
	 * 得到转换后长度
	 */
	nLen = WideCharToMultiByte(CP_ACP, 0,
		wbuffer.data(), wbuffer.length(), NULL, 0, NULL, NULL);

	std::string ansistr;
	ansistr.resize(nLen);

	/* 把unicode转成ansi */
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)(wbuffer.data()), wbuffer.length(),
		(LPSTR)(ansistr.data()), ansistr.size(), NULL, NULL);
	return(CString(ansistr.data(), ansistr.length()));
#endif
}

const CString getJSONDir(const CString& subDir = _T("")) {
	static CString strPath;
	const char         PATH_SEP = '\\';
	if (strPath.IsEmpty()) {
		/*
		char exeFullPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, CA2W(exeFullPath));
		strPath = (CString)exeFullPath;
		*/
		strPath = JSONGetProgramPath();
		strPath = strPath + _T("Rank") + PATH_SEP;
	}
	return subDir.IsEmpty() ? strPath : strPath + subDir;
}

void CJson::load(std::vector<CString>& Names, std::vector<int>& Scores)
{
	json          temp;
	std::ifstream i;
	i.open(getJSONDir(_T("Ranking List.json")));
	if (!i) {
		return;
	}
	i >> temp;
	json Nin = temp["name"];
	json Sin = temp["score"];
	int total = temp["total"];
	for (int i = 0; i < total; i++) {
		std::string t = Nin[i];
		Names.emplace_back(ConvertUTF8ToCString(t));
		Scores.emplace_back(Sin[i]);
	}
	i.close();
	return;
}

void CJson::save(std::vector<CString>& Names, std::vector<int>& Scores)
{
	json temp;
	json          Sout = json::array();
	json          Nout = json::array();
	std::ofstream o;
	LOG_DEBUG("Open File.");
	o.open(getJSONDir(_T("Ranking List.json")));
	if (!o) {
		std::string temp((std::string)(CStringA)getJSONDir());
		LOG_DEBUG("Create File Path.");
		_mkdir(temp.c_str());
		o.open(getJSONDir(_T("Ranking List.json")));
	}
	int total = Scores.size();
	temp["total"] = total;
	LOG_DEBUG("for(int i)");
	for (int i = 0; i < total; i++) {
		Sout[i] = Scores[i];
		std::string t = ConvertCStringToUTF8(Names[i]);
		LOG_DEBUG("%s", t.c_str());
		Nout[i] = t;
	}
	LOG_DEBUG("Data Combine");
	temp["score"] = Sout;
	temp["name"] = Nout;
	LOG_DEBUG("Out");
	o << temp;
	LOG_DEBUG("Close File.");
	o.close();
	LOG_DEBUG("Function End.");
}