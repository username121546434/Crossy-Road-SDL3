#include "Car.h"
#include <SDL3/SDL.h>
#include <iostream>

Car::Car(int max_x, int max_y)
    : r {SDL_rand(206) + 50}, g {SDL_rand(206) + 50}, b {SDL_rand(206) + 50},
      x {max_x}, y {SDL_rand(max_y - 100) + 40} {
    
}

void Car::draw_and_update(int speed, SDL_Renderer *renderer) {
    x -= speed;
    SDL_Rect rect {x, y, car_width, car_height};
    SDL_FRect frect;
    bool success;
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
