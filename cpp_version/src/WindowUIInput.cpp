#include "WindowUI.h"
#include <cstdlib>

std::string WindowUI::readLine() {
    if (quitRequested) {
        std::exit(0);
    }
    SDL_StartTextInput();
    currentInput.clear();
    bool finished = false;
    bool cancelled = false;
    std::string result;

    while (!finished && !quitRequested) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                finished = true;
                quitRequested = true;
                SDL_Quit();
                std::exit(0);
            }
            if (event.type == SDL_TEXTINPUT) {
                currentInput += event.text.text;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_BACKSPACE && !currentInput.empty()) {
                    currentInput.pop_back();
                } else if (event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP_ENTER) {
                    finished = true;
                    break;
                } else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    finished = true;
                    cancelled = true;
                    break;
                }
            }
        }

        renderFrame(true);
        SDL_Delay(16);
    }

    SDL_StopTextInput();
    result = cancelled ? "" : currentInput;

    currentInput.clear();
    renderFrame(false);
    return result;
}

void WindowUI::sleepMs(int ms) {
    processSleep(ms);
}

void WindowUI::processSleep(int ms) const {
    const int step = 16;
    int remaining = ms;
    SDL_Event event;

    while (remaining > 0 && !quitRequested) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quitRequested = true;
                SDL_Quit();
                std::exit(0);
            }
        }
        SDL_Delay(step);
        remaining -= step;
    }
}
