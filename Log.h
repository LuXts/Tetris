#pragma once

/*
 * @Author: Jungle
 * @Date: 2020-05-27 00:11:34
 * @LastEditTime: 2020-05-28 02:58:22
 * @LastEditors: LuXts
 * @Description:
 * @FilePath:
 */

#include <string>

#define LOG(level,x, ...)                                                   \
    lena::Log::writeLog(level, __FILE__, __FUNCTION__,						\
                        __LINE__, x, __VA_ARGS__)

#ifdef _DEBUG
#define LOG_DEBUG(x,...)													\
	lena::Log::writeLog(lena::LOG_LEVEL_DEBUG, __FILE__, __FUNCTION__,		\
                        __LINE__, x, __VA_ARGS__)
#else
#define LOG_DEBUG(x,...)		0;
#endif

namespace lena {
	// output level
	enum LOGLEVEL {
		LOG_LEVEL_NONE,
		LOG_LEVEL_ERROR,
		LOG_LEVEL_WARNING,
		LOG_LEVEL_INFO,
		LOG_LEVEL_DEBUG
	};

	// output target
	enum LOGTARGET {
		LOG_TARGET_NONE,
		LOG_TARGET_CONSOLE,
		LOG_TARGET_FILE,
		LOG_TARGET_ALL = LOG_TARGET_CONSOLE | LOG_TARGET_FILE
	};

	class Log {
	private:
		static std::string logBuffer;

		static LOGLEVEL  logLevel;
		static LOGTARGET logTarget;

		static int  createFile();
		static void outputToTarget();

	public:
		static void init(LOGLEVEL inLevel, LOGTARGET inTarget);
		static void uninit();

		static LOGLEVEL getLogLevel();
		static void     setLogLevel(LOGLEVEL inLevel);

		static LOGTARGET getLogTarget();
		static void      setLogTarget(LOGTARGET inTarget);

		static bool writeLog(LOGLEVEL inLevel, const char* fileName,
			const char* function, int lineNumber,
			const char* format, ...);
	};
}  // namespace lena
