// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <functional> 
#include "ftxui/component/component.hpp"
#include <watch_component.hpp>
#include <chrono>

ftxui::Component MainComponent(std::function<void()> show_modal,
    std::function<void()> exit,
    const ftxui::Component& watches
) {

    using namespace ftxui;

    auto add_watch_btn = Button("+ Add Watch", show_modal, ButtonOption::Ascii());

    auto add_watch = Renderer(add_watch_btn,
        [add_watch_btn] {
            return add_watch_btn->Render()
                | align_right;
        });

    auto component = Container::Vertical({
        add_watch,
        watches
        });

    component |= Renderer([&](Element inner) {
        return vbox({
                   text("worldclock"),
                   separator(),
                   inner
            }) | border;
        });

    return component;
}