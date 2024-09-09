#ifndef CARS_H
#define CARS_H

#pragma once
#include "Car.h"
#include <vector>
#include <map>
#include <SDL3/SDL.h>

class Cars {
private:
    size_t num_cars;
    std::vector<Car> cars;
public:
    Cars(std::pair<int, int> max_coors, size_t num_cars = 5);
    void update_all(int speed, SDL_Renderer *renderer, std::pair<int, int> max_coors);
    void reset(std::pair<int, int> max_coors);
    bool check_collision(int x, int y, double radius);
};

#endif