#include "webserver.h"



WebServer::WebServer() :
	serverLogger(std::make_shared<seasocks::PrintfLogger>(seasocks::Logger::Level::Access)),
	serverInstance(serverLogger) {
	this->StartRunnerThread();
}

WebServer::~WebServer() {
	this->serverInstance.terminate();

	if (this->serverThread.joinable()) {
		this->serverThread.join();
	}
}

void WebServer::StartRunnerThread() {
	this->serverThread = std::thread([this]() {
		this->serverInstance.serve("web", 8080);
	});
}
