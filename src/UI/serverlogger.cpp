#include "serverlogger.h"

#include <logger/logger.h>

void ServerLogger::log(Level level, const char* message) {
	switch (level) {
		case Level::Debug:
			LogDebug(message);
			return;
		case Level::Access:
			LogInfo("Access {}", message);
			return;
		case Level::Info:
			LogInfo(message);
			return;
		case Level::Warning:
			LogWarn(message);
			return;
		case Level::Error:
			LogError(message);
			return;
		case Level::Severe:
			LogCritical(message);
			return;
		default:
			LogInfo("Unknown - {}", message);
	}
}