#pragma once
#include <string_view>
namespace Game {

    struct Settings
    {
        static constexpr int windowWidth{ 800 };
        static constexpr int windowHeight{ 600 };
        static constexpr std::string_view nameWindow{ "GAME BY xACx" };
    };
}
