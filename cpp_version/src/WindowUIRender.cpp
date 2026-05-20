#include "WindowUI.h"
#include <cstdlib>

void WindowUI::renderFrame(bool showPrompt) const {
    if (!renderer || !font) {
        return;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quitRequested = true;
            SDL_Quit();
            std::exit(0);
        }
    }

    SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    SDL_RenderClear(renderer);

    const SDL_Rect contentRect = {20, 60, width - 40, height - 140};
    const SDL_Rect promptRect = {20, height - 60, width - 40, 40};
    const SDL_Rect headerRect = {20, 20, width - 40, 30};

    SDL_SetRenderDrawColor(renderer, panelColor.r, panelColor.g, panelColor.b, panelColor.a);
    SDL_RenderFillRect(renderer, &contentRect);
    SDL_SetRenderDrawColor(renderer, promptBgColor.r, promptBgColor.g, promptBgColor.b, promptBgColor.a);
    SDL_RenderFillRect(renderer, &promptRect);
    SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
    SDL_RenderDrawRect(renderer, &contentRect);
    SDL_RenderDrawRect(renderer, &promptRect);
    SDL_RenderDrawRect(renderer, &headerRect);

    int textRightPadding = 20;
    if (imageTexture && imageWidth > 0 && imageHeight > 0) {
        const int imagePanelWidth = 260;
        const int imagePanelHeight = 170;
        const SDL_Rect imagePanel = {
            contentRect.x + contentRect.w - imagePanelWidth - 10,
            contentRect.y + 10,
            imagePanelWidth,
            imagePanelHeight
        };

        SDL_SetRenderDrawColor(renderer, 0, 16, 16, 255);
        SDL_RenderFillRect(renderer, &imagePanel);
        SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
        SDL_RenderDrawRect(renderer, &imagePanel);

        const float imageAspect = static_cast<float>(imageWidth) / static_cast<float>(imageHeight);
        int renderWidth = imagePanel.w - 20;
        int renderHeight = static_cast<int>(renderWidth / imageAspect);
        if (renderHeight > imagePanel.h - 20) {
            renderHeight = imagePanel.h - 20;
            renderWidth = static_cast<int>(renderHeight * imageAspect);
        }

        const SDL_Rect imageDst = {
            imagePanel.x + (imagePanel.w - renderWidth) / 2,
            imagePanel.y + (imagePanel.h - renderHeight) / 2,
            renderWidth,
            renderHeight
        };
        SDL_RenderCopy(renderer, imageTexture, nullptr, &imageDst);
        textRightPadding = imagePanelWidth + 30;
    }

    SDL_Surface* headerSurface = TTF_RenderText_Blended(font, "Project Faulken", borderColor);
    if (headerSurface) {
        SDL_Texture* headerTexture = SDL_CreateTextureFromSurface(renderer, headerSurface);
        SDL_Rect headerDst = {30, 24, headerSurface->w, headerSurface->h};
        SDL_RenderCopy(renderer, headerTexture, nullptr, &headerDst);
        SDL_DestroyTexture(headerTexture);
        SDL_FreeSurface(headerSurface);
    }

    int y = contentRect.y + 10;
    for (size_t i = 0; i < lines.size(); ++i) {
        const TextLine& line = lines[i];
        std::string text = line.text;

        if (showPrompt && i + 1 == lines.size() && !currentInput.empty()) {
            text += currentInput;
        }

        if (text.empty()) {
            y += lineHeight;
            continue;
        }

        std::string displayText = text;
        if (displayText.size() > 120) {
            displayText = displayText.substr(0, 120);
        }

        SDL_Surface* surface = TTF_RenderUTF8_Solid(font, displayText.c_str(), line.color);
        if (!surface) {
            surface = TTF_RenderUTF8_Blended(font, displayText.c_str(), line.color);
        }
        if (!surface) {
            continue;
        }
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture) {
            SDL_FreeSurface(surface);
            continue;
        }

        SDL_Rect src = {0, 0, surface->w, surface->h};
        if (src.w > contentRect.w - textRightPadding) {
            src.w = contentRect.w - textRightPadding;
        }
        SDL_Rect dst = {contentRect.x + 10, y, src.w, surface->h};
        SDL_RenderCopy(renderer, texture, &src, &dst);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
        y += lineHeight;
    }

    std::string promptText = "ACTION:> " + currentInput;
    SDL_Surface* promptSurface = TTF_RenderText_Blended(font, promptText.c_str(), promptTextColor);
    if (promptSurface) {
        SDL_Texture* promptTexture = SDL_CreateTextureFromSurface(renderer, promptSurface);
        SDL_Rect promptDst = {promptRect.x + 10, promptRect.y + 8, promptSurface->w, promptSurface->h};
        SDL_RenderCopy(renderer, promptTexture, nullptr, &promptDst);
        SDL_DestroyTexture(promptTexture);
        SDL_FreeSurface(promptSurface);
    }

    SDL_RenderPresent(renderer);
}
