#include "logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

Logger::Logger() : loggerInstance(new spdlog::logger("Nova")) {
	// Console Sink
	auto console = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	console->set_pattern("[%Y-%m-%d %H:%M:%S.%e][%^%l%$] %v");

	this->loggerInstance->sinks().emplace_back(std::move(console));

	spdlog::register_logger(this->loggerInstance);
	spdlog::set_default_logger(this->loggerInstance);
}

spdlog::logger* Logger::Get() {
	return spdlog::default_logger_raw();
}
