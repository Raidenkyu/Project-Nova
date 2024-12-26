#include "windowmanager/novawmpolicy.h"

#include <miral/toolkit_event.h>
#include <miral/window_info.h>
#include <miral/window_manager_tools.h>

#include <linux/input.h>

namespace ms = mir::scene;
using namespace miral;
using namespace miral::toolkit;

NovaWMPolicy::NovaWMPolicy(WindowManagerTools const& tools) :
    CanonicalWindowManagerPolicy{tools}
{
}

bool NovaWMPolicy::handle_keyboard_event(MirKeyboardEvent const* event)
{
    auto const action = mir_keyboard_event_action(event);
    auto const scan_code = mir_keyboard_event_scan_code(event);
    auto const modifiers = mir_keyboard_event_modifiers(event) & modifier_mask;

    if (action == mir_keyboard_action_down &&
            modifiers == mir_input_event_modifier_alt &&
            scan_code == KEY_TAB)
    {
        tools.focus_next_application();

        return true;
    }
    else if (action == mir_keyboard_action_down &&
            modifiers == mir_input_event_modifier_alt &&
            scan_code == KEY_GRAVE)
    {
        tools.focus_next_within_application();

        return true;
    }
    else if (action == mir_keyboard_action_down &&
             modifiers == (mir_input_event_modifier_alt | mir_input_event_modifier_shift) &&
             scan_code == KEY_GRAVE)
    {
        tools.focus_prev_within_application();

        return true;
    }
    else if (action == mir_keyboard_action_down && scan_code == KEY_F4)
    {
        switch (modifiers & modifier_mask)
        {
        case mir_input_event_modifier_alt:
            tools.ask_client_to_close(tools.active_window());;
            return true;

        default:
            break;
        }
    }

    return false;
}

bool NovaWMPolicy::handle_touch_event(MirTouchEvent const* event)
{
    auto const count = mir_touch_event_point_count(event);

    long total_x = 0;
    long total_y = 0;

    for (auto i = 0U; i != count; ++i)
    {
        total_x += mir_touch_event_axis_value(event, i, mir_touch_axis_x);
        total_y += mir_touch_event_axis_value(event, i, mir_touch_axis_y);
    }

    Point const cursor{total_x/count, total_y/count};

    tools.select_active_window(tools.window_at(cursor));

    return false;
}

bool NovaWMPolicy::handle_pointer_event(MirPointerEvent const* event)
{
    auto const action = mir_pointer_event_action(event);

    Point const cursor{
        mir_pointer_event_axis_value(event, mir_pointer_axis_x),
        mir_pointer_event_axis_value(event, mir_pointer_axis_y)};

    if (action == mir_pointer_action_button_down)
    {
        tools.select_active_window(tools.window_at(cursor));
    }

    return false;
}

void NovaWMPolicy::advise_focus_gained(WindowInfo const& info)
{
    CanonicalWindowManagerPolicy::advise_focus_gained(info);
}

auto NovaWMPolicy::place_new_window(ApplicationInfo const& app_info, WindowSpecification const& request)
-> WindowSpecification
{
    WindowSpecification specification = CanonicalWindowManagerPolicy::place_new_window(app_info, request);

    if ((specification.type() == mir_window_type_normal || specification.type() == mir_window_type_freestyle) &&
        (!specification.parent().is_set() || !specification.parent().value().lock()))
    {
        specification.state() = mir_window_state_maximized;
        specification.top_left() = mir::optional_value<Point>{}; // Ignore requested position (if any) when we maximize
        specification.size() = mir::optional_value<Size>{}; // Ignore requested size (if any) when we maximize
        tools.place_and_size_for_state(specification, WindowInfo{});

        if (!request.state().is_set() || request.state().value() != mir_window_state_restored)
            specification.state() = request.state();
    }

    return specification;
}

void NovaWMPolicy::handle_modify_window(WindowInfo& window_info, WindowSpecification const& modifications)
{
    WindowSpecification specification = modifications;

    if ((window_info.type() == mir_window_type_normal || window_info.type() == mir_window_type_freestyle) &&
        !window_info.parent())
    {
        specification.state() = mir_window_state_maximized;
        specification.top_left() = mir::optional_value<Point>{}; // Ignore requested position (if any) when we maximize
        specification.size() = mir::optional_value<Size>{}; // Ignore requested size (if any) when we maximize
        tools.place_and_size_for_state(specification, window_info);

        if (!modifications.state().is_set() || modifications.state().value() != mir_window_state_restored)
            specification.state() = modifications.state();
    }

    CanonicalWindowManagerPolicy::handle_modify_window(window_info, specification);
}

void NovaWMPolicy::handle_request_move(WindowInfo& /*window_info*/, MirInputEvent const* /*input_event*/)
{
}

void NovaWMPolicy::handle_request_resize(WindowInfo& /*window_info*/, MirInputEvent const* /*input_event*/, MirResizeEdge /*edge*/)
{
}

Rectangle
NovaWMPolicy::confirm_placement_on_display(WindowInfo const& /*window_info*/, MirWindowState /*new_state*/,
    Rectangle const& new_placement)
{
    return new_placement;
}
