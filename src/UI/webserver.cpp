#include "webserver.h"

#include <logger/logger.h>
#include "serverlogger.h"

WebServer::WebServer() :
	serverInstance(std::make_shared<ServerLogger>()) {
}

WebServer::~WebServer() {
	this->serverInstance.terminate();

	if (this->serverThread.joinable()) {
		this->serverThread.join();
	}

	LogInfo("WebServer destroyed");
}

void WebServer::StartRunnerThread() {
	this->serverThread = std::thread([this]() {
		pthread_setname_np(pthread_self(), "WebServer");
		this->serverInstance.serve("web", 8080);
	});
}
