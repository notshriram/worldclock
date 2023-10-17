// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include "ftxui/component/component.hpp"

#include "ftxui/dom/elements.hpp"  
#include <functional> 
#include <ftxui/component/component.hpp>

#include <vector>
#include <string>
#include <chrono>
#include <format>

// auto zones = std::chrono::tzdb::zones;

ftxui::Component MenuComponent(
    std::function<void()> close_modal,
    std::function<void(std::string)> set_timezone,
    const std::vector<std::string>& zones
) {
    using namespace ftxui;

    static int selected = 0;

    MenuOption option;
    option.on_enter = [&] {
        set_timezone(zones[selected]);
        close_modal();
        };

    auto menu = Menu(&zones, &selected, option);

    // Display together the menu with a border
    auto renderer = Renderer(menu, [menu] {
        return
            window(text("tzdb"), menu->Render() | vscroll_indicator | frame | size(HEIGHT, LESS_THAN, 10));
        });
    return renderer;
}