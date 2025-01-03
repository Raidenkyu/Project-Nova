#include "compositorlogger.h"

#include <logger/logger.h>

void CompositorLogger::log(mir::logging::Severity severity, const std::string& message, const std::string& component) {
	switch (severity) {
		case mir::logging::Severity::debug:
			LogDebug(message);
			return;
		case mir::logging::Severity::informational:
			LogInfo(message);
			return;
		case mir::logging::Severity::warning:
			LogWarn(message);
			return;
		case mir::logging::Severity::error:
			LogError(message);
			return;
		case mir::logging::Severity::critical:
			LogCritical(message);
			return;
		default:
			LogInfo("Unknown - {}", message);
	}
}

