#include "uiwindow.h"

#include <iostream>
#include <fstream>

UIWindow::UIWindow() : webView(true, nullptr) {
	try {
		webView.set_size(1290, 1080, WEBVIEW_HINT_NONE);

		webView.navigate("http://localhost:8080/");
		webView.run();
	} catch (const webview::exception &e) {
		std::cerr << e.what() << '\n';
	}
}
