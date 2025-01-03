#include "webserver.h"



WebServer::WebServer() :
	serverLogger(std::make_shared<seasocks::PrintfLogger>(seasocks::Logger::Level::Access)),
	serverInstance(serverLogger) {
}

WebServer::~WebServer() {
	this->serverInstance.terminate();

	if (this->serverThread.joinable()) {
		this->serverThread.join();
	}

	std::cout << "WebServer destroyed\n";
}

void WebServer::StartRunnerThread() {
	this->serverThread = std::thread([this]() {
		pthread_setname_np(pthread_self(), "WebServer");
		this->serverInstance.serve("web", 8080);
	});
}
