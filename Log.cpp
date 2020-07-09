#include "pch.h"
#include "Log.h"

/*
 * @Author: Jungle
 * @Date: 2020-05-27 00:11:40
 * @LastEditTime: 2020-05-28 09:30:49
 * @LastEditors: LuXts
 * @Description:
 * @FilePath:
 */

#include "Log.h"
#include <Windows.h>
#include <ctime>
#include <direct.h>
#include <fstream>
#include <iostream>

#include <atlstr.h>

using namespace lena;
using namespace std;

std::string        Log::logBuffer = "";
LOGLEVEL      Log::logLevel;
LOGTARGET     Log::logTarget;
std::ofstream mFile;

CString GetProgramPath()
{
	CString  strProgramPath;
	GetModuleFileName(NULL, strProgramPath.GetBuffer(MAX_PATH), MAX_PATH);
	strProgramPath.ReleaseBuffer(MAX_PATH);
	int nPathPos = strProgramPath.ReverseFind('\\');
	strProgramPath = strProgramPath.Left(nPathPos + 1);
	return strProgramPath;
}

const CString getLogDir(const CString& subDir = _T("")) {
	static CString strPath;
	const char         PATH_SEP = '\\';
	if (strPath.IsEmpty()) {
		/*
		char exeFullPath[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, CA2W(exeFullPath));
		strPath = (CString)exeFullPath;
		*/
		strPath = GetProgramPath();
		strPath = strPath + _T("Log") + PATH_SEP;
	}
	return subDir.IsEmpty() ? strPath : strPath + subDir;
}

void Log::init(LOGLEVEL  inLevel = LOG_LEVEL_NONE,
	LOGTARGET inTarget = LOG_TARGET_NONE) {
	setLogLevel(inLevel);
	setLogTarget(inTarget);
	createFile();
}

void Log::uninit() {
	logBuffer.clear();
	mFile.close();
	logLevel = LOG_LEVEL_NONE;
	logTarget = LOG_TARGET_NONE;
}

inline LOGLEVEL Log::getLogLevel() {
	return logLevel;
};
inline void Log::setLogLevel(LOGLEVEL inLevel) {
	logLevel = inLevel;
};

inline LOGTARGET Log::getLogTarget() {
	return logTarget;
};
inline void Log::setLogTarget(LOGTARGET inTarget) {
	logTarget = inTarget;
};

int Log::createFile() {
	/* time_t newTime       = time(NULL);
	tm     temp          = *(localtime(&newTime)); */
	CString fileDirectory = getLogDir(_T("Tetris_Log.log"));
	cout << fileDirectory << endl;
	cout << getLogDir() << endl;
	mFile.open(fileDirectory, ios::app);
	if (!mFile) {
		std::string temp((std::string)(CStringA)getLogDir());
		_mkdir(temp.c_str());
		mFile.open(fileDirectory);
	}
	return 0;
}

bool Log::writeLog(LOGLEVEL inLevel, const char* fileName, const char* function,
	int lineNumber, const char* format, ...) {
	//if (!mFile) {
	//	createFile();
	//}

	if (inLevel > logLevel) {
		return false;
	}
	std::string Level;
	time_t t = time(NULL);
	char   timeBuffer[200];
	char   infoBuffer[400];
	char   logInfoBuffer[1024];
	strftime(timeBuffer, sizeof(timeBuffer), "[%Y-%m-%d %H:%M:%S]",
		localtime(&t));
	switch (inLevel) {
	case LOG_LEVEL_DEBUG:
		Level = "DEBUG";
		break;
	case LOG_LEVEL_ERROR:
		Level = "ERROR";
		break;
	case LOG_LEVEL_WARNING:
		Level = "WANING";
		break;
	case LOG_LEVEL_INFO:
		Level = "INFO";
		break;
	case LOG_LEVEL_NONE:
		return false;
		break;
	}

	sprintf_s(infoBuffer, sizeof(infoBuffer), "[%s][-%s][%s:%4d]",
		Level.c_str(), fileName, function, lineNumber);

	va_list ap;
	va_start(ap, format);
	vsnprintf(logInfoBuffer, sizeof(logInfoBuffer), format, ap);
	va_end(ap);
	logBuffer += timeBuffer;
	logBuffer += infoBuffer;
	logBuffer += logInfoBuffer;
	logBuffer += "\n";
	outputToTarget();

	return true;
};

void Log::outputToTarget() {
	if (logTarget & LOG_TARGET_CONSOLE) {
		cout << logBuffer;
	}

	if (logTarget & LOG_TARGET_FILE) {
		mFile << logBuffer;
		mFile.flush();
	}

	logBuffer.clear();
}