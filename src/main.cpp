#include <SDL3/SDL_main.h>
#include "core/game.h"

int main(int, char**) {
    Game::getInstance().init("GhostEscape", 1280, 720);
    Game::getInstance().run();
    return 0;
}