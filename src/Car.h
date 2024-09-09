#ifndef CAR_H
#define CAR_H

#pragma once
#include <SDL3/SDL.h>

const int car_width = 20;
const int car_height = 10;

class Car {
private:
    int r;
    int g;
    int b;

    int y;
    int x;
public:
    Car(int max_x, int max_y);
    void draw_and_update(int speed, SDL_Renderer *renderer);
    int get_y() const;
    int get_x() const;
};

#endif