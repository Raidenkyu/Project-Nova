#pragma once

#include "compositorlogger.h"
#include "mir/logging/logger.h"


class CompositorLogger: public mir::logging::Logger {
public:
	void log(mir::logging::Severity severity, const std::string& message, const std::string& component) override;
};
