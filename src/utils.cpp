#include "utils.h"

void DrawCircle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY, int32_t radius) {
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y) {
        //  Each of the following renders an octant of the circle
        std::array<bool, 8> m{
            SDL_RenderPoint(renderer, centreX + x, centreY - y),
            SDL_RenderPoint(renderer, centreX + x, centreY + y),
            SDL_RenderPoint(renderer, centreX - x, centreY - y),
            SDL_RenderPoint(renderer, centreX - x, centreY + y),
            SDL_RenderPoint(renderer, centreX + y, centreY - x),
            SDL_RenderPoint(renderer, centreX + y, centreY + x),
            SDL_RenderPoint(renderer, centreX - y, centreY - x),
            SDL_RenderPoint(renderer, centreX - y, centreY + x),
        };

        if (!std::all_of(m.begin(), m.end(), [](bool x) { return x; })) {
            std::cerr << "Error drawing circle: " << SDL_GetError() << std::endl;
        }

        if (error <= 0) {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0) {
            --x;
            tx += 2;
            error += (tx - diameter);
        }
    }
}

double distance(int x1, int y1, int x2, int y2) {
    int dist_x{x2 - x1};
    int dist_y{y2 - y1};
    return sqrt(static_cast<double>(dist_x * dist_x + dist_y * dist_y));
}

bool point_in_rect(int x, int y, int width, int height, int px, int py) {
    return (x <= px && px <= x + width && y <= py && py <= y + height);
}

bool circle_intersects_line(int cx, int cy, int cr, int lx1, int ly1, int lx2, int ly2) {
    if (distance(lx1, cy, lx1, ly1) < cr && cx > lx1 && cx < lx2)
        return true;
    if (distance(cx, ly1, lx1, ly1) < cr && cy > ly1 && cy < ly2)
        return true;
    return false;
}

bool rect_intersects_circle(int cx, int cy, int cr, int rx, int ry, int rw, int rh) {
    if (point_in_rect(rx, ry, rw, rh, cx, cy))
        return true;
    if (circle_intersects_line(cx, cy, cr, rx, ry, rx + rw, ry))
        return true;
    if (circle_intersects_line(cx, cy, cr, rx, ry, rx, ry + rh))
        return true;
    if (circle_intersects_line(cx, cy, cr, rx + rw, ry, rx + rw, ry + rh))
        return true;
    if (circle_intersects_line(cx, cy, cr, rx, ry + rh, rx + rw, ry + rh))
        return true;
    return false;
}
