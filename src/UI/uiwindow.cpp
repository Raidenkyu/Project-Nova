#include "uiwindow.h"

#include <iostream>
#include <fstream>

#include <iostream>

UIWindow::UIWindow() : webView(true, nullptr) {
	try {
		gtk_window_set_decorated(static_cast<GtkWindow*>(webView.window().value()), false);
		webView.set_size(1290, 1080, WEBVIEW_HINT_NONE);

		webView.navigate("http://localhost:8080/");
		webView.run();
		std::cout << "[HERE] WebView Stopped Running" << std::endl;
	} catch (const webview::exception &e) {
		std::cerr << "WebKit Window Exception: " << e.what() << '\n';
	}
}
