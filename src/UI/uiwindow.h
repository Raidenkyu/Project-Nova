#pragma once

#include <thread>

#include "webview/webview.h"

class UIWindow {
public:
	UIWindow();
	~UIWindow();

	void StartRunnerThread();
private:
	webview::webview* webView;

	std::thread windowThread;
};
