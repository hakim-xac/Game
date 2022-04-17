#pragma once
#include <string_view>
#include <map>

#include "Enums.h"

namespace Game {

    struct Settings
    {
        static constexpr size_t maxLengthTextInLog{ 110 };
        static constexpr size_t windowWidth{ 800 };
        static constexpr size_t windowHeight{ 600 };
        static constexpr int menuTextFontSize{ 40 };
        static constexpr std::string_view nameWindow{ "GAME BY xACx" };
        static constexpr std::string_view fontPath{ "fonts/arial.ttf" };


        /* HERO INFO */
        static constexpr int heroWidth{ 150 };
        static constexpr int heroHeight{ 120 };
        static constexpr int heroMaxFrame{ 11 };
        static constexpr std::string_view heroPathTexture{ "sprites/hero.png" };


        /* ENEMY INFO */
        static constexpr int enemyWidth{ 150 };
        static constexpr int enemyHeight{ 120 };
        static constexpr int enemyMaxFrame{ 11 };
        static constexpr std::string_view enemyPathTexture{ "sprites/enemy.png" };


        static const std::string& showCode(CodeBase key);

    };
}