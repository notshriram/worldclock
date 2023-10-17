// SPDX-License-Identifier: BSD-3-Clause

#include <functional>
#include <memory>

// ftxui components
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/mouse.hpp>
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp" 
#include "ftxui/dom/elements.hpp"

#include <menu_component.hpp>
#include <main_component.hpp>


#include <fstream>
#include <iterator>
#include <chrono>
#include <ranges>

template<std::ranges::range R>
constexpr auto to_vector(R&& r) {
    using elem_t = std::decay_t<std::ranges::range_value_t<R>>;
    return std::vector<elem_t>{r.begin(), r.end()};
}

int main(int argc, const char* argv[]) {
    using namespace ftxui;
    using namespace std::chrono;
    using namespace std::chrono_literals;

    auto screen = ScreenInteractive::Fullscreen();

    bool modal_open = false;
    auto time = std::chrono::system_clock::now();

    auto show_modal = [&] { modal_open = true; };
    auto close_modal = [&] { modal_open = false; };
    auto exit = screen.ExitLoopClosure();

    std::ifstream ifs;
    ifs.open(".worldclock", std::ios::in);

    std::vector<std::string> user_zones(std::istream_iterator<std::string>{ifs},
        std::istream_iterator<std::string>{});

    auto& tzdb = std::chrono::get_tzdb();
    std::vector<std::string> zones = to_vector(tzdb.zones
        | std::views::transform([](const std::chrono::time_zone& tz) {return std::string(tz.name());}));

    auto watches = Container::Vertical({});

    for (auto z : user_zones) {
        watches->Add(WatchComponent(z, time));
    }

    auto set_timezone = [&](std::string zone) {
        user_zones.push_back(zone);
        };

    auto main_component = MainComponent(show_modal, exit, watches);

    auto menu_component = MenuComponent(close_modal, set_timezone, zones);

    main_component |= Modal(menu_component, &modal_open);

    std::atomic<bool> refresh_ui_continue = true;
    std::thread refresh_ui([&] {
        while (refresh_ui_continue) {
            std::this_thread::sleep_for(1s);
            screen.Post([&] { time = std::chrono::system_clock::now(); });
            screen.Post(Event::Custom);

            if (user_zones.size() > watches->ChildCount()) {
                watches->Add(WatchComponent(user_zones.back(), time));
            }
        }
        });

    screen.Loop(main_component);
    refresh_ui_continue = false;
    refresh_ui.join();
    ifs.close();

    std::ofstream ofs;
    ofs.open(".worldclock", std::ios::out);
    for (const std::string& s : user_zones) {
        ofs << s << '\n';
    }

    return 0;
}