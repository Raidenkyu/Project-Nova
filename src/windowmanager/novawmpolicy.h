#pragma once

#include <miral/canonical_window_manager.h>

#include <mir_toolkit/events/enums.h>

using namespace mir::geometry;

class NovaWMPolicy : public miral::CanonicalWindowManagerPolicy
{
public:
    NovaWMPolicy(miral::WindowManagerTools const& tools);

    auto place_new_window(miral::ApplicationInfo const& app_info, miral::WindowSpecification const& request)
    -> miral::WindowSpecification override;

    void advise_focus_gained(miral::WindowInfo const& info) override;

    bool handle_keyboard_event(MirKeyboardEvent const* event) override;
    bool handle_touch_event(MirTouchEvent const* event) override;
    bool handle_pointer_event(MirPointerEvent const* event) override;
    void handle_modify_window(miral::WindowInfo& window_info, miral::WindowSpecification const& modifications) override;

    void handle_request_move(miral::WindowInfo& window_info, MirInputEvent const* input_event) override;
    void handle_request_resize(miral::WindowInfo& window_info, MirInputEvent const* input_event,
        MirResizeEdge edge) override;

    Rectangle confirm_placement_on_display(const miral::WindowInfo& window_info, MirWindowState new_state,
        Rectangle const& new_placement) override;

private:
    static const int modifier_mask =
        mir_input_event_modifier_alt |
        mir_input_event_modifier_shift |
        mir_input_event_modifier_sym |
        mir_input_event_modifier_ctrl |
        mir_input_event_modifier_meta;
};
