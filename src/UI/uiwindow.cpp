#include "uiwindow.h"

#include <logger/logger.h>

#include <fstream>
#include <iostream>

UIWindow::UIWindow() {}

UIWindow::~UIWindow() {
	this->webView->terminate();

	if (this->windowThread.joinable()) {
		this->windowThread.join();
	}

	LogInfo("UIWindow destroyed");
}

void UIWindow::StartRunnerThread() {
	this->windowThread = std::thread([this]() {
		pthread_setname_np(pthread_self(), "UIWindow");

		try {
			// Init Window
			this->webView = new webview::webview(true, nullptr);

			// Configure Window
			gtk_window_set_decorated(static_cast<GtkWindow*>(webView->window().value()), false);
			webView->set_size(1290, 1080, WEBVIEW_HINT_NONE);

			// Bind Window to WebServer and run
			webView->navigate("http://localhost:8080/");
			webView->run();

			// Destroy Window
			delete this->webView;
		} catch (const webview::exception &e) {
			std::cerr << "WebKit Window Exception: " << e.what() << '\n';
		}
	});
}