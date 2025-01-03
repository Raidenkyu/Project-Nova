#pragma once

#include <spdlog/spdlog.h>

#include <memory>

class Logger {
public:
	Logger();

	static spdlog::logger* Get();
private:
	std::shared_ptr<spdlog::logger> loggerInstance;
};

#define LogTrace(...) ::Logger::Get()->log(spdlog::level::trace, __VA_ARGS__)
#define LogDebug(...) ::Logger::Get()->log(spdlog::level::debug, __VA_ARGS__)
#define LogInfo(...) ::Logger::Get()->log(spdlog::level::info, __VA_ARGS__)
#define LogWarn(...) ::Logger::Get()->log(spdlog::level::warn, __VA_ARGS__)
#define LogError(...) ::Logger::Get()->log(spdlog::level::err, __VA_ARGS__)
#define LogCritical(...) ::Logger::Get()->log(spdlog::level::critical, __VA_ARGS__)