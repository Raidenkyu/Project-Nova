#include <linux/input-event-codes.h>
#include <windowmanager/windowmanager.h>

#include <miral/append_event_filter.h>
#include <miral/display_configuration_option.h>
#include <miral/keymap.h>
#include <miral/set_window_management_policy.h>
#include <miral/x11_support.h>

#include "windowmanager/novawmpolicy.h"

namespace mirtk = miral::toolkit;

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

		const auto inputBindings = [this](MirEvent const* event) -> bool {
			return this->InputCallback(event);
		};

		this->runner.run_with({
			miral::display_configuration_options,
			miral::X11Support{},
			wayland_extensions,
			miral::set_window_management_policy<NovaWMPolicy>(),
			miral::Keymap{},
			miral::AppendEventFilter{inputBindings}
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

bool WindowManager::InputCallback(MirEvent const* event) {
	if (mirtk::mir_event_get_type(event) != mir_event_type_input)
		return false;

	MirInputEvent const* input_event = mirtk::mir_event_get_input_event(event);
	if (mirtk::mir_input_event_get_type(input_event) != mir_input_event_type_key)
		return false;

	MirKeyboardEvent const* kev = mirtk::mir_input_event_get_keyboard_event(input_event);
	if (mirtk::mir_keyboard_event_action(kev) != mir_keyboard_action_down)
		return false;

	MirInputEventModifiers mods = mirtk::mir_keyboard_event_modifiers(kev);
	if (!(mods & mir_input_event_modifier_alt) || !(mods & mir_input_event_modifier_ctrl))
		return false;

	if (mirtk::mir_keyboard_event_scan_code(kev) == KEY_BACKSPACE) {
		this->ShutdownCallback();
		return true;
	}

	return false;
}