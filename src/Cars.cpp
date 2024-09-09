#include "Cars.h"
#include <vector>
#include <iostream>
#include "utils.h"

Cars::Cars(std::pair<int, int> max_coors, size_t num_cars): num_cars {num_cars}, cars {} {
    for (size_t i {0}; i < num_cars; ++i)
        cars.push_back(Car {max_coors.first, max_coors.second});
}

void Cars::update_all(int speed, SDL_Renderer *renderer, std::pair<int, int> max_coors) {
    int n {SDL_rand(5)};
    if (n == 1)
        cars.push_back(Car {max_coors.first, max_coors.second});

    std::vector<std::vector<Car>::iterator> x {};
    for (auto i {cars.begin()}; i != cars.end(); ++i) {
        i->draw_and_update(speed, renderer);
        if (i->get_x() < -car_width)
            x.push_back(i);
    }

    for (auto &i: x)
        cars.erase(i);
}

void Cars::reset(std::pair<int, int> max_coors) {
    cars.clear();
    for (size_t i {0}; i < num_cars; ++i)
        cars.push_back(Car {max_coors.first, max_coors.second});
}

bool Cars::check_collision(int x, int y, double radius) {
    for (Car &c: cars) {
        if (rect_intersects_circle(x, y, radius, c.get_x(), c.get_y(), car_width, car_height))
            return true;
    }
    return false;
}
