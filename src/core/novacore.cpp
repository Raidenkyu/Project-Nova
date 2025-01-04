#include "novacore.h"

#include <logger/logger.h>

NovaCore::NovaCore(int argc, char const* argv[]) :
	isRunning(true),
	logger(new Logger()),
	service(new NovaService()),
	webServer(new WebServer()),
	windowManager(new WindowManager(argc, argv)),
	uiWindow(new UIWindow()) {

	windowManager->startupSignal.append([&]() {
		this->uiWindow->StartRunnerThread();
	});

	windowManager->shutdownSignal.append([&]() {
		this->isRunning = false;
	});

}

int NovaCore::RunProcess() {
	this->webServer->StartRunnerThread();
	this->windowManager->StartRunnerThread();

	while (this->isRunning) {
		this->service->Process();
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	return 0;
}
