#pragma once

#include "ProgrammLogic.h"
#include <iostream>



int main()
{
    using namespace Game;

    ProgrammLogic plGame;
    Logs{"qwertyu", "dfhdfh" };
    Logs{"11"};
    plGame.loop();

    return 0;
}