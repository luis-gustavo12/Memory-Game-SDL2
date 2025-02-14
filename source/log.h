#pragma once

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef WINDOWS
#include <Windows.h>
#elif LINUX
#include <sys/time.h>
#endif // WINDOWS



typedef enum LogLevel {

	LogLevel_INFO,
	LogLevel_DEBUG,
	LogLevel_WARN,
	LogLevel_ERROR,
	LogLevel_FATAL,

} LogLevel;

void TranslateLogLevel(char* buff, LogLevel level);

void Log(char* info, LogLevel	level);

long GetMillisec(void);