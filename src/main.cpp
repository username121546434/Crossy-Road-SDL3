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
const std::string window_title {"Crossy Road"};
constexpr double update_rate = 1.0 / 60.0 * 1000;

struct AppState {
    Player player;
    Cars cars;
    CurrentLevel current_level;
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool player_should_go_up;
    bool pause_game;
    SDL_TimerID step_timer;
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
            break;
        case SDL_SCANCODE_P:
            as->pause_game = !as->pause_game;
            if (as->pause_game) {
                if (!SDL_SetWindowTitle(as->window, (window_title + " (Paused)").c_str()))
                    SDL_LogError(SDL_LOG_CATEGORY_ERROR, SDL_GetError());
            } else {
                if (!SDL_SetWindowTitle(as->window, window_title.c_str()))
                    std::cerr << SDL_GetError() << std::endl;
            }
            break;
        default:
            return SDL_APP_CONTINUE;
    }
    return SDL_APP_CONTINUE;
}

SDL_AppResult handle_key_up(AppState *as, SDL_Scancode key) {
    switch (key) {
        case SDL_SCANCODE_UP:
            as->player_should_go_up = false;
            break;
        default:
            return SDL_APP_CONTINUE;
    }
    return SDL_APP_CONTINUE;
}

// taken from snake game example in sdl github
static Uint32 sdl_timer_callback_(void *payload, SDL_TimerID timer_id, Uint32 interval) {
    SDL_Event event;
    SDL_zero(event);
    event.type = SDL_EVENT_USER;
    SDL_PushEvent(&event);
    return interval;
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
    as->player_should_go_up = false;
    as->pause_game = false;
    
    as->step_timer = SDL_AddTimer(update_rate, sdl_timer_callback_, NULL);
    if (as->step_timer == 0) {
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(window_title.c_str(), window_size, window_size, 0, &as->window, &as->renderer)) {
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

    as->cars.draw_all(as->renderer);
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
            if (as->pause_game)
                break;
            as->cars.update_all(as->current_level.get_level(), size);
            if (as->player_should_go_up)
                move_player_up(*as);
            break;
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
        SDL_RemoveTimer(as->step_timer);
        SDL_free(as);
        TTF_Quit();
    }
}
