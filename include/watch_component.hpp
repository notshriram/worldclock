// SPDX-License-Identifier: BSD-3-Clause

#pragma once

#include <functional> 
#include <ftxui/component/component.hpp>

#include <string>
#include <chrono>
#include <format>

ftxui::Component WatchComponent(const std::string& tz, const std::chrono::time_point<std::chrono::system_clock>& time) {

    using namespace ftxui;
    using namespace std::chrono;
    using namespace std::chrono_literals;

    // std::chrono::zoned_time zt{ tz, time };

    return Renderer([tz, &time] {
        return window(text(tz), text(std::format("{:%Y-%m-%d %X}", time))) | flex;
        });
}