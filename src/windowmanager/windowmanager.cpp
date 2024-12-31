#include <windowmanager/windowmanager.h>

#include <miral/display_configuration_option.h>
#include <miral/keymap.h>
#include <miral/set_window_management_policy.h>
#include <miral/x11_support.h>

#include "windowmanager/novawmpolicy.h"

WindowManager::WindowManager(int argc, char const* argv[]) : runner(argc, argv) {
    for (auto const& extension : wayland_extensions.all_supported()) {
        wayland_extensions.enable(extension);
    }

	this->runner.add_stop_callback([this]() { this->ShutdownCallback(); });
	this->runner.add_start_callback([this]() { this->StartUpCallback(); });
}

WindowManager::~WindowManager() {
	this->runner.stop();

	if (this->wmThread.joinable()) {
		this->wmThread.join();
	}
}

void WindowManager::StartRunnerThread() {
	this->wmThread = std::thread([this]() {
		pthread_setname_np(pthread_self(), "WindowManager");

		this->runner.run_with({
			miral::display_configuration_options,
			miral::X11Support{},
			wayland_extensions,
			miral::set_window_management_policy<NovaWMPolicy>(),
			miral::Keymap{},
		});
	});
}

void WindowManager::StartUpCallback() const {
	const auto& wayland_display = this->runner.wayland_display();

	// Prepare Environment before starting any window
	setenv("WAYLAND_DISPLAY", wayland_display.value().c_str(),  true);   // configure Wayland socket
	setenv("GDK_BACKEND", "wayland", true);             // configure GTK to use Wayland
	setenv("QT_QPA_PLATFORM", "wayland", true);         // configure Qt to use Wayland
	unsetenv("QT_QPA_PLATFORMTHEME");                   // Discourage Qt from unsupported theme
	setenv("SDL_VIDEODRIVER", "wayland", true);         // configure SDL to use Wayland

	// Notify all windows that the environment is ready
	this->startupSignal();
}

void WindowManager::ShutdownCallback() {
	this->shutdownSignal();
}
