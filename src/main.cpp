/*
 * Copyright © Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * under the terms of the GNU General Public License version 2 or 3 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <windowmanager/windowmanager.h>
#include <UI/uiwindow.h>
#include <UI/webserver.h>


int main(int argc, char const* argv[]) {
	bool isRunning = true;
	auto webServer = new WebServer();
    auto windowManager = new WindowManager(argc, argv);
	auto uiWindow = new UIWindow();

	windowManager->startupSignal.append([&]() {
		uiWindow->StartRunnerThread();
	});

	windowManager->shutdownSignal.append([&]() {
		isRunning = false;
	});

	webServer->StartRunnerThread();
	windowManager->StartRunnerThread();

	while (isRunning) { std::this_thread::sleep_for(std::chrono::milliseconds(16)); }

	delete uiWindow;
	delete windowManager;
	delete webServer;

    return 0;
}
