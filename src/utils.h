#ifndef UTILS_H
#define UTILS_H

#pragma once

#include <SDL3/SDL.h>
#include <algorithm>
#include <array>
#include <iostream>
#include <math.h>

void DrawCircle(SDL_Renderer *renderer, int32_t centreX, int32_t centreY, int32_t radius);
double distance(int x1, int y1, int x2, int y2);
bool point_in_rect(int x, int y, int width, int height, int px, int py);
bool circle_intersects_line(int cx, int cy, int cr, int lx1, int ly1, int lx2, int ly2);
bool rect_intersects_circle(int cx, int cy, int cr, int rx, int ry, int rw, int rh);

#endif
