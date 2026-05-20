#include "WindowUI.h"
#include <cstdlib>
#include <cmath>

void WindowUI::appendText(const std::string& text) {
    if (lines.empty()) {
        lines.push_back({"", currentColor});
    }

    size_t start = 0;
    while (start < text.size()) {
        size_t pos = text.find('\n', start);
        if (pos == std::string::npos) {
            lines.back().text += text.substr(start);
            break;
        }

        lines.back().text += text.substr(start, pos - start);
        lines.push_back({"", currentColor});
        start = pos + 1;
    }
}

void WindowUI::appendLine(const std::string& text) {
    appendText(text);
    lines.push_back({"", currentColor});
    scrollIfNeeded();
}

void WindowUI::scrollIfNeeded() {
    while (static_cast<int>(lines.size()) > maxLines) {
        lines.erase(lines.begin());
    }
}

void WindowUI::clearScreen() {
    lines.clear();
    lines.push_back({"", currentColor});
    renderFrame(false);
}

void WindowUI::print(const std::string& text) {
    if (quitRequested) {
        std::exit(0);
    }
    appendText(text);
    renderFrame(false);
}

void WindowUI::printLine(const std::string& text) {
    if (quitRequested) {
        std::exit(0);
    }
    appendLine(text);
    renderFrame(false);
}

void WindowUI::setColor(const std::string& colorCode) {
    if (colorCode.find("[32m") != std::string::npos || colorCode.find("32m") != std::string::npos) {
        currentColor = {0, 192, 0, 255};
    } else if (colorCode.find("[31m") != std::string::npos || colorCode.find("31m") != std::string::npos) {
        currentColor = {220, 20, 60, 255};
    } else if (colorCode.find("[33m") != std::string::npos || colorCode.find("33m") != std::string::npos) {
        currentColor = {255, 204, 0, 255};
    } else if (colorCode.find("[34m") != std::string::npos || colorCode.find("34m") != std::string::npos) {
        currentColor = {80, 150, 255, 255};
    } else if (colorCode.find("[35m") != std::string::npos || colorCode.find("35m") != std::string::npos) {
        currentColor = {220, 120, 255, 255};
    } else if (colorCode.find("[36m") != std::string::npos || colorCode.find("36m") != std::string::npos) {
        currentColor = {0, 220, 220, 255};
    } else if (colorCode.find("[90m") != std::string::npos || colorCode.find("90m") != std::string::npos) {
        currentColor = {150, 150, 150, 255};
    } else {
        currentColor = {255, 255, 255, 255};
    }
}

void WindowUI::resetColor() {
    currentColor = {255, 255, 255, 255};
}

void WindowUI::showImage(const std::string& imageId) {
    const std::string imagePath = resolveAssetPath("images", imageId, ".bmp");
    if (imagePath.empty()) {
        printLine("[image missing: " + imageId + "]");
        return;
    }

    SDL_Surface* surface = SDL_LoadBMP(imagePath.c_str());
    if (!surface) {
        printLine("[image failed to load: " + imageId + "]");
        return;
    }

    SDL_Texture* loadedTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!loadedTexture) {
        SDL_FreeSurface(surface);
        printLine("[image failed to render: " + imageId + "]");
        return;
    }

    if (imageTexture) {
        SDL_DestroyTexture(imageTexture);
    }

    imageTexture = loadedTexture;
    imageWidth = surface->w;
    imageHeight = surface->h;
    SDL_FreeSurface(surface);
    renderFrame(false);
}

void WindowUI::playSound(const std::string& soundId) {
    if (audioDevice == 0) {
        return;
    }

    const std::string soundPath = resolveAssetPath("sounds", soundId, ".wav");
    if (!soundPath.empty()) {
        SDL_AudioSpec wavSpec{};
        Uint8* wavBuffer = nullptr;
        Uint32 wavLength = 0;

        if (SDL_LoadWAV(soundPath.c_str(), &wavSpec, &wavBuffer, &wavLength)) {
            SDL_ClearQueuedAudio(audioDevice);
            SDL_QueueAudio(audioDevice, wavBuffer, wavLength);
            SDL_FreeWAV(wavBuffer);
            return;
        }
    }

    playGeneratedTone(soundId);
}

std::vector<std::int16_t> WindowUI::makeTone(double frequency, int durationMs) const {
    const int sampleRate = audioSpec.freq > 0 ? audioSpec.freq : 44100;
    const int sampleCount = sampleRate * durationMs / 1000;
    std::vector<std::int16_t> samples(sampleCount);

    for (int i = 0; i < sampleCount; ++i) {
        const double t = static_cast<double>(i) / sampleRate;
        const double envelope = 1.0 - (static_cast<double>(i) / sampleCount);
        samples[i] = static_cast<std::int16_t>(std::sin(2.0 * 3.141592653589793 * frequency * t) * 8000 * envelope);
    }

    return samples;
}

void WindowUI::playGeneratedTone(const std::string& soundId) {
    double frequency = 440.0;
    int durationMs = 80;

    if (soundId == "error") {
        frequency = 160.0;
        durationMs = 140;
    } else if (soundId == "item") {
        frequency = 660.0;
    } else if (soundId == "power") {
        frequency = 220.0;
        durationMs = 220;
    } else if (soundId == "unlock" || soundId == "scan") {
        frequency = 880.0;
    } else if (soundId == "terminal") {
        frequency = 520.0;
        durationMs = 120;
    }

    const auto samples = makeTone(frequency, durationMs);
    SDL_ClearQueuedAudio(audioDevice);
    SDL_QueueAudio(audioDevice, samples.data(), static_cast<Uint32>(samples.size() * sizeof(std::int16_t)));
}

bool WindowUI::isQuitRequested() const {
    return quitRequested;
}

void WindowUI::printLines(const std::vector<std::string>& lines) {
    if (quitRequested) {
        std::exit(0);
    }
    for (const auto& line : lines) {
        appendLine(line);
    }
    renderFrame(false);
}
