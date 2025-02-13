#include "log.h"

void TranslateLogLevel(char* buff, LogLevel level) {
	


	switch (level) {


	case LogLevel_INFO:
		strcpy(buff, "INFO");
		break;

	case LogLevel_DEBUG:
		strcpy(buff, "DEBUG");
		break;

	case LogLevel_WARN:
		strcpy(buff, "WARN");
		break;

	case LogLevel_ERROR:
		strcpy(buff, "ERROR");
		break;

	case LogLevel_FATAL:
		strcpy(buff, "FATAL");
		break;

	default:
		break;
	}


}

void Log(char* info, LogLevel level) {


	if (level > LogLevel_FATAL || level < LogLevel_INFO) return;

	struct tm* local;
	time_t now;
	char timestamp[127];
	char logLevel[32];
	char milliSec[16];
	size_t size;


	memset(logLevel, 0, sizeof(logLevel));
	memset(timestamp, 0, sizeof(timestamp));

	// Format DD-MM-YYYY

	now = time(NULL);

	local = localtime(&now);

	//size_t rsl =  strftime(timestamp, sizeof(timestamp), "%d/%B/%Y %H:%M:%S", local);

	char fullMonth[32];

	strftime(fullMonth, sizeof(fullMonth), "%B", local);

	snprintf(milliSec, sizeof(milliSec), "%03ld", GetMillisec());

	snprintf(timestamp, sizeof(timestamp), "%02d/%s/%d %02d:%02d:%02d.%s",
		local->tm_mday,
		fullMonth,
		1900+local->tm_year, 
		local->tm_hour,
		local->tm_min,
		local->tm_sec,
		milliSec

	);



	TranslateLogLevel(logLevel, level);

	size = strlen(timestamp) + strlen(logLevel) + strlen(info) + 20;

	//char buff[sizeof(size)];

	char* buff = (char*)malloc(size + 1);
	//buff = (char*)calloc(size, sizeof(char*));

	if (buff == NULL) {
		return;
	}

	memset(buff, 0, sizeof(buff));

	snprintf(buff, size, "%s [%s] -> %s\n", timestamp,logLevel, info);




	FILE* file = NULL;
#ifdef WINDOWS
	file = fopen("..\\..\\..\\memory_game.log", "a");

#elif LINUX
	file = fopen("../../memory_game.log", "a");
#endif

	

	if (!file) {
		free(buff);
		return;
	}

	fprintf(file, "%s", buff);

	fclose(file);

	free(buff);
}

long GetMillisec() {

#ifdef WINDOWS
	SYSTEMTIME lt;

	GetLocalTime(&lt);

	return (long)lt.wMilliseconds;

#elif LINUX
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL) + (tv.tv_usec / 1000);

#endif


	return 0;
}


