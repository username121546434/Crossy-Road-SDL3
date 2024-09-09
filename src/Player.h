#ifndef PLAYER_H
#define PLAYER_H

#pragma once
#include <SDL3/SDL.h>

const int player_size = 10;

class Player {
private:
    int x;
    int y;

public:
    Player(int x);
    int get_x() const;
    int get_y() const;
    void reset();
    // if returns true, then need to reset
    bool move_up(int window_height);
    void draw(SDL_Renderer *renderer);
};

#endif