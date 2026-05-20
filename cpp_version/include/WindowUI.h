#ifndef WINDOW_UI_H
#define WINDOW_UI_H

#include "IGameUI.h"
#include <cstdint>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>

class WindowUI : public IGameUI {
public:
    WindowUI(int width = 1024, int height = 720);
    ~WindowUI() override;

    bool isInitialized() const;

    void clearScreen() override;
    void print(const std::string& text) override;
    void printLine(const std::string& text) override;
    std::string readLine() override;
    void sleepMs(int ms) override;
    void setColor(const std::string& colorCode) override;
    void resetColor() override;
    void showImage(const std::string& imageId) override;
    void playSound(const std::string& soundId) override;
    void printLines(const std::vector<std::string>& lines) override;
    bool isQuitRequested() const override;

private:
    struct TextLine {
        std::string text;
        SDL_Color color;
    };

    bool initialized;
    mutable bool quitRequested;
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_AudioDeviceID audioDevice;
    SDL_AudioSpec audioSpec;
    SDL_Texture* imageTexture;
    int imageWidth;
    int imageHeight;
    std::vector<TextLine> lines;
    SDL_Color currentColor;
    SDL_Color backgroundColor;
    SDL_Color panelColor;
    SDL_Color borderColor;
    SDL_Color promptBgColor;
    SDL_Color promptTextColor;
    std::string currentInput;
    int width;
    int height;
    int lineHeight;
    int maxLines;

    bool initializeSDL();
    bool initializeAudio();
    bool initializeFont();
    std::string findFontPath() const;
    std::string resolveAssetPath(const std::string& directory, const std::string& id, const std::string& extension) const;
    void appendText(const std::string& text);
    void appendLine(const std::string& text = "");
    void scrollIfNeeded();
    void renderFrame(bool showPrompt) const;
    void processSleep(int ms) const;
    void playGeneratedTone(const std::string& soundId);
    std::vector<std::int16_t> makeTone(double frequency, int durationMs) const;
};

#endif // WINDOW_UI_H
