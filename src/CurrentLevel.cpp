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
    SDL_Color textColor = { 255, 255, 255, 0 };


    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    int text_width = textSurface->w;
    int text_height = textSurface->h;
    SDL_DestroySurface(textSurface);

    SDL_Rect renderQuad = { font_x, font_y, text_width, text_height };
    SDL_FRect frect;
    SDL_RectToFRect(&renderQuad, &frect);
    if (!SDL_RenderTexture(renderer, texture, NULL, &frect))
        std::cerr << "Error rendering font: " << SDL_GetError() << std::endl;
    SDL_DestroyTexture(texture);
}

CurrentLevel &CurrentLevel::operator=(const CurrentLevel &rhs) {
    this->current_level = rhs.current_level;
    this->font = TTF_OpenFont(filename.c_str(), font_size);
    return *this;
}
