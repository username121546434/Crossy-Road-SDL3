#include "Player.h"
#include "utils.h"

Player::Player(int x): y {x * 2}, x {x} {

}

int Player::get_x() const {
    return x;
}

int Player::get_y() const {
    return y;
}

void Player::reset() {
    y = x * 2;
}

bool Player::move_up(int window_height) {
    y -= 10;
    return y < 0;
}

void Player::draw(SDL_Renderer *renderer) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
    DrawCircle(renderer, x, y, player_size);
}
