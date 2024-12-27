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

#include <iostream>

int main(int argc, char const* argv[]) {
	auto webServer = new WebServer();
    auto windowManager = new WindowManager(argc, argv);

	using namespace std::chrono_literals;

	std::this_thread::sleep_for(500ms);

	auto uiWindow = new UIWindow();

	delete uiWindow;
	delete windowManager;
	delete webServer;
    return 0;
}
