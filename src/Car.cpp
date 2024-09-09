#include "Car.h"
#include <SDL3/SDL.h>
#include <iostream>

Car::Car(int max_x, int max_y)
    : x {max_x}, y {SDL_rand(max_y - 100) + 40},
      r {SDL_rand(256)}, g {SDL_rand(256)}, b {SDL_rand(256)} {
    
}

void Car::draw_and_update(int speed, SDL_Renderer *renderer) {
    x -= speed;
    SDL_Rect rect {x, y, car_width, car_height};
    SDL_FRect frect;
    SDL_bool success;
    success = SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
    if (!success) std::cerr << "Error: " << SDL_GetError();
    SDL_RectToFRect(&rect, &frect);
    success = SDL_RenderFillRect(renderer,  &frect);
    if (!success) std::cerr << "Error: " << SDL_GetError();
}

int Car::get_y() const {
    return y;
}

int Car::get_x() const {
    return x;
}
