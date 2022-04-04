#pragma once
#include <string_view>
#include <map>

#include "Enums.h"

namespace Game {

    struct Settings
    {
        static constexpr size_t windowWidth{ 800 };
        static constexpr size_t windowHeight{ 600 };
        static constexpr int heroWidth{ 150 };
        static constexpr int heroHeight{ 120 };
        static constexpr int heroMaxFrame{ 11 };
        static constexpr std::string_view nameWindow{ "GAME BY xACx" };
        static std::string_view showError(CodeErrors key);
    };
}