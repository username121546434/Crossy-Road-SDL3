#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <iostream>
#include "Cars.h"
#include "CurrentLevel.h"
#include "Player.h"
#include <vector>
#include <SDL3_ttf/SDL_ttf.h>

const int window_size = 600;
const std::pair<int, int> size {window_size, window_size};

struct AppState {
    Player player;
    Cars cars;
    CurrentLevel current_level;
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool player_should_go_up;
};

void move_player_up(AppState &as) {
    bool reset = as.player.move_up(window_size);
    if (reset) {
        as.player.reset();
        as.current_level.increment_level();
        as.cars.reset(size);
    }
}

SDL_AppResult handle_key_down(AppState *as, SDL_Scancode key) {
    switch (key) {
        case SDL_SCANCODE_Q:
            return SDL_APP_SUCCESS;
        case SDL_SCANCODE_UP:
            as->player_should_go_up = true;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult handle_key_up(AppState *as, SDL_Scancode key) {
    switch (key) {
        case SDL_SCANCODE_UP:
            as->player_should_go_up = false;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << SDL_GetError() << std::endl;
        return SDL_APP_FAILURE;
    }
    if (!TTF_Init()) {
        std::cerr << SDL_GetError() << std::endl;
        return SDL_APP_FAILURE;
    }
    AppState *as = static_cast<AppState*>(SDL_calloc(1, sizeof(AppState)));
    as->player = Player {window_size / 2};
    as->current_level = CurrentLevel {};
    as->cars = Cars {size};

    if (!SDL_CreateWindowAndRenderer("Crossy Road", window_size, window_size, 0, &as->window, &as->renderer)) {
        std::cerr << SDL_GetError() << std::endl;
        return SDL_APP_FAILURE;
    }

    *appstate = as;

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    AppState *as {static_cast<AppState*>(appstate)};
    
    SDL_SetRenderDrawColor(as->renderer, 0, 0, 0, 255);
    SDL_RenderClear(as->renderer);

    if (as->player_should_go_up)
        move_player_up(*as);

    as->cars.update_all(as->current_level.get_level(), as->renderer, size);
    as->current_level.draw(as->renderer);
    as->player.draw(as->renderer);

    SDL_RenderPresent(as->renderer);

    if (as->cars.check_collision(as->player.get_x(), as->player.get_y(), player_size)) {
        SDL_Delay(1000);
        return SDL_APP_SUCCESS;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
    AppState *as {static_cast<AppState*>(appstate)};

    switch (event->type) {
        case SDL_EVENT_QUIT:
        case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
            return SDL_APP_SUCCESS;
        case SDL_EVENT_USER:
            as->cars.update_all(as->current_level.get_level(), as->renderer, size);
        case SDL_EVENT_KEY_DOWN:
            return handle_key_down(as, event->key.scancode);
        case SDL_EVENT_KEY_UP:
            return handle_key_up(as, event->key.scancode);
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate) {
    if (appstate != NULL) {
        AppState* as {static_cast<AppState*>(appstate)};
        SDL_DestroyWindow(as->window);
        SDL_DestroyRenderer(as->renderer);
        SDL_free(as);
        TTF_Quit();
    }
}
