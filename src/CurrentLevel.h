#ifndef CURRENTLEVEL_H
#define CURRENTLEVEL_H

#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>

const std::string filename {"game_over.ttf"};
const int font_size {72};
const int font_x {0};
const int font_y {560}; 

class CurrentLevel {
private:
    int current_level;
    TTF_Font *font;
public:
    CurrentLevel();
    ~CurrentLevel();
    void increment_level();
    int get_level() const;
    void draw(SDL_Renderer *renderer);
    CurrentLevel &operator=(const CurrentLevel &rhs);
};

#endif