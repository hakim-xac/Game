#pragma once

#include "includes.h"

enum class Directions { LEFT, RIGHT };


int main()
{
    using namespace Game;

    ProgrammLogic plGame;

    plGame.loop();

    return 0;
}