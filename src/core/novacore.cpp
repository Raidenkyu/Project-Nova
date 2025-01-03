#include "novacore.h"

NovaCore::NovaCore(int argc, char const* argv[]) :
	isRunning(false),
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
	this->isRunning = true;

	this->webServer->StartRunnerThread();
	this->windowManager->StartRunnerThread();

	while (this->isRunning) {
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	return 0;
}
