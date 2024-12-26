#pragma once

#include <miral/runner.h>
#include <miral/wayland_extensions.h>
#include <miral/display_configuration.h>

class WindowManager {
public:
    WindowManager(int argc, char const* argv[]);
    void RunThreadFunc();

private:
    miral::MirRunner runner;
    miral::DisplayConfiguration display_config;
    miral::WaylandExtensions wayland_extensions;
};
