#include "pch.h"
#include "CJson.h"

#include "nlohmann/json.hpp"
#include <fstream>
#include <iostream>
#include <direct.h>
#include <string>

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
		Names.emplace_back(CA2T(t.c_str()));
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
	o.open(getJSONDir(_T("Ranking List.json")));
	if (!o) {
		std::string temp((std::string)(CStringA)getJSONDir());
		_mkdir(temp.c_str());
		o.open(getJSONDir(_T("Ranking List.json")));
	}

	int total = Scores.size();

	temp["total"] = total;
	for (int i = 0; i < total; i++) {
		Sout[i] = Scores[i];
		std::string t = CT2A(Names[i].GetString());
		Nout[i] = t;
	}
	temp["score"] = Sout;
	temp["name"] = Nout;
	o << temp;
	o.close();
}