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

std::vector<std::string> zones = {
"Africa/Abidjan",
"Africa/Accra",
"Africa/Addis_Ababa",
"Africa/Algiers",
"Africa/Asmara",
"Africa/Asmera",
"Africa/Bamako",
"Africa/Bangui",
"Africa/Banjul",
"Africa/Bissau",
"Africa/Blantyre",
"Africa/Brazzaville",
"Africa/Bujumbura",
"Africa/Cairo",
"Africa/Casablanca",
"Africa/Ceuta",
"Africa/Conakry",
"Africa/Dakar",
"Africa/Dar_es_Salaam",
"Africa/Djibouti",
"Africa/Douala",
"Africa/El_Aaiun",
"Africa/Freetown",
"Africa/Gaborone",
"Africa/Harare",
"Africa/Johannesburg",
"Africa/Juba",
"Africa/Kampala",
"Africa/Khartoum",
"Africa/Kigali",
"Africa/Kinshasa",
"Africa/Lagos",
"Africa/Libreville",
"Africa/Lome",
"Africa/Luanda",
"Africa/Lubumbashi",
"Africa/Lusaka",
"Africa/Malabo",
"Africa/Maputo",
"Africa/Maseru",
"Africa/Mbabane",
"Africa/Mogadishu",
"Africa/Monrovia",
"Africa/Nairobi",
"Africa/Ndjamena",
"Africa/Niamey",
"Africa/Nouakchott",
"Africa/Ouagadougou",
"Africa/Porto-Novo",
"Africa/Sao_Tome",
"Africa/Timbuktu",
"Africa/Tripoli",
"Africa/Tunis",
"Africa/Windhoek",
"America/Adak",
"America/Anchorage",
"America/Anguilla",
"America/Antigua",
"America/Araguaina",
"America/Argentina/Buenos_Aires",
"America/Argentina/Catamarca",
"America/Argentina/ComodRivadavia",
"America/Argentina/Cordoba",
"America/Argentina/Jujuy",
"America/Argentina/La_Rioja",
"America/Argentina/Mendoza",
"America/Argentina/Rio_Gallegos",
"America/Argentina/Salta",
"America/Argentina/San_Juan",
"America/Argentina/San_Luis",
"America/Argentina/Tucuman",
"America/Argentina/Ushuaia",
"America/Aruba",
"America/Asuncion",
"America/Atikokan",
"America/Atka",
};

// auto zones = std::chrono::tzdb::zones;

ftxui::Component MenuComponent(
    std::function<void()> close_modal,
    std::function<void(std::string)> set_timezone
) {
    using namespace ftxui;

    static int selected = 0;

    MenuOption option;
    option.on_enter = [&set_timezone, &close_modal] {
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