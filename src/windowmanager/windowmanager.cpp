#include <windowmanager/windowmanager.h>

#include <miral/keymap.h>
#include <miral/set_window_management_policy.h>
#include <miral/command_line_option.h>

#include "windowmanager/novawmpolicy.h"

WindowManager::WindowManager(int argc, char const* argv[]) : runner(argc, argv), display_config(runner) {
    for (auto const& extension : {"zwp_pointer_constraints_v1", "zwp_relative_pointer_manager_v1"}) {
        wayland_extensions.enable(extension);
    }

    this->RunThreadFunc();
}

void WindowManager::RunThreadFunc() {
    runner.run_with({
        display_config,
        display_config.layout_option(),
        miral::set_window_management_policy<NovaWMPolicy>(),
        miral::Keymap{},
        wayland_extensions,
    });
}