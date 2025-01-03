#pragma once

#include <memory>

#include <logger/logger.h>
#include <UI/uiwindow.h>
#include <UI/webserver.h>
#include <windowmanager/windowmanager.h>

class NovaCore {
public:
	NovaCore(int argc, char const* argv[]);

	int RunProcess();
private:
	bool isRunning;

	std::unique_ptr<Logger> logger;
	std::unique_ptr<WebServer> webServer;
	std::unique_ptr<WindowManager> windowManager;
	std::unique_ptr<UIWindow> uiWindow;
};
