#include "CurrentLevel.h"
#include <iostream>

CurrentLevel::CurrentLevel()
    : current_level {1}, font {TTF_OpenFont(filename.c_str(), font_size)} {
    if (!font)
        std::cerr << "Error loading font: " << SDL_GetError() << std::endl;
}

CurrentLevel::~CurrentLevel() {
    TTF_CloseFont(font);
}

void CurrentLevel::increment_level() {
    ++current_level;
}

int CurrentLevel::get_level() const {
    return current_level;
}

void CurrentLevel::draw(SDL_Renderer *renderer) {
    std::string text {"Current level: "};
    text += std::to_string(current_level);
    SDL_Color textColor = { 255, 255, 255, 255 };

    SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), 0, textColor);
    if (!surface) SDL_LogError(SDL_LogCategory::SDL_LOG_CATEGORY_ERROR, "Failed to create surface: %s", SDL_GetError());
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) SDL_LogError(SDL_LogCategory::SDL_LOG_CATEGORY_ERROR, "Failed to create texture: %s", SDL_GetError());
    if (!surface || !texture)
        return;

    SDL_Rect dstRect {font_x, font_y, surface->w, surface->h};
    SDL_FRect d;
    SDL_RectToFRect(&dstRect, &d);
    SDL_RenderTexture(renderer, texture, NULL, &d);

    SDL_DestroyTexture(texture);
    SDL_DestroySurface(surface);
}

CurrentLevel &CurrentLevel::operator=(const CurrentLevel &rhs) {
    this->current_level = rhs.current_level;
    this->font = TTF_OpenFont(filename.c_str(), font_size);
    return *this;
}
