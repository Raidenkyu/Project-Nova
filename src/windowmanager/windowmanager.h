#pragma once

#include <thread>

#include <miral/runner.h>
#include <miral/wayland_extensions.h>
#include <miral/toolkit_event.h>

#include "eventpp/callbacklist.h"


class WindowManager {
public:
    WindowManager(int argc, char const* argv[]);
    ~WindowManager();

    void StartRunnerThread();

    // Callback signal objects
    eventpp::CallbackList<void ()> startupSignal;
    eventpp::CallbackList<void ()> shutdownSignal;
private:
    void StartUpCallback() const;
    void ShutdownCallback();
    bool InputCallback(MirEvent const* event);

    // Window Management objects
    miral::MirRunner runner;
    miral::WaylandExtensions wayland_extensions;

    // Threading object
    std::thread wmThread;
};
