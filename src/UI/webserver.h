#pragma once

#include <memory>
#include <thread>

#include "seasocks/PrintfLogger.h"
#include "seasocks/Server.h"

class WebServer {
public:
	WebServer();
	~WebServer();

	void StartRunnerThread();
private:
	std::shared_ptr<seasocks::PrintfLogger> serverLogger;
	seasocks::Server serverInstance;
	std::thread serverThread;
};
