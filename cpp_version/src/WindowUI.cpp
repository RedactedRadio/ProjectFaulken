#include "WindowUI.h"
#include <filesystem>

namespace fs = std::filesystem;

WindowUI::WindowUI(int width_, int height_)
    : initialized(false)
    , quitRequested(false)
    , window(nullptr)
    , renderer(nullptr)
    , font(nullptr)
    , audioDevice(0)
    , audioSpec{}
    , imageTexture(nullptr)
    , imageWidth(0)
    , imageHeight(0)
    , currentColor({0, 255, 0, 255})
    , backgroundColor({0, 0, 0, 255})
    , panelColor({0, 0, 0, 255})
    , borderColor({0, 255, 0, 255})
    , promptBgColor({0, 24, 0, 255})
    , promptTextColor({0, 255, 0, 255})
    , width(width_)
    , height(height_)
    , lineHeight(18)
    , maxLines((height_ - 140) / lineHeight) {
    if (initializeSDL() && initializeAudio() && initializeFont()) {
        initialized = true;
        lines.push_back({"", currentColor});
    }
}

WindowUI::~WindowUI() {
    if (imageTexture) {
        SDL_DestroyTexture(imageTexture);
        imageTexture = nullptr;
    }
    if (audioDevice != 0) {
        SDL_CloseAudioDevice(audioDevice);
        audioDevice = 0;
    }
    if (font) {
        TTF_CloseFont(font);
        font = nullptr;
    }
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    TTF_Quit();
    SDL_Quit();
}

bool WindowUI::isInitialized() const {
    return initialized;
}

bool WindowUI::initializeSDL() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        return false;
    }

    window = SDL_CreateWindow(
        "Project Faulken",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        return false;
    }

    return true;
}

bool WindowUI::initializeAudio() {
    SDL_AudioSpec desired{};
    desired.freq = 44100;
    desired.format = AUDIO_S16SYS;
    desired.channels = 1;
    desired.samples = 2048;

    audioDevice = SDL_OpenAudioDevice(nullptr, 0, &desired, &audioSpec, 0);
    if (audioDevice == 0) {
        audioSpec = desired;
        return true;
    }

    SDL_PauseAudioDevice(audioDevice, 0);
    return true;
}

bool WindowUI::initializeFont() {
    if (TTF_Init() != 0) {
        return false;
    }

    const std::string fontPath = findFontPath();
    if (fontPath.empty()) {
        return false;
    }

    font = TTF_OpenFont(fontPath.c_str(), 18);
    return font != nullptr;
}

std::string WindowUI::findFontPath() const {
    const std::vector<std::string> candidates = {
        "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationMono-Regular.ttf",
        "/usr/share/fonts/truetype/freefont/FreeMono.ttf",
        "/usr/share/fonts/truetype/freefont/FreeSans.ttf"
    };

    for (const auto& candidate : candidates) {
        if (fs::exists(candidate)) {
            return candidate;
        }
    }
    return "";
}

std::string WindowUI::resolveAssetPath(
    const std::string& directory,
    const std::string& id,
    const std::string& extension
) const {
    const std::vector<std::string> candidates = {
        "cpp_version/assets/" + directory + "/" + id + extension,
        "../assets/" + directory + "/" + id + extension,
        "assets/" + directory + "/" + id + extension,
        id
    };

    for (const auto& candidate : candidates) {
        if (fs::exists(candidate)) {
            return candidate;
        }
    }

    return "";
}
