#pragma once

#include <thread>

#include <miral/runner.h>
#include <miral/wayland_extensions.h>
#include <miral/display_configuration.h>

class WindowManager {
public:
    WindowManager(int argc, char const* argv[]);
    ~WindowManager();

private:
    void StartRunnerThead();

    miral::MirRunner runner;
    miral::DisplayConfiguration display_config;
    miral::WaylandExtensions wayland_extensions;

    std::thread wmThread;
};
