#pragma once

#include"/Library/Frameworks/SDL2.framework/Headers/SDL.h"
#include "color.h"
#include "vector.h"
#include "triangle.h"
#include "utils.h"

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

void set_title(char* msg, SDL_Window* screen);
SDL_Rect rectangle( int _x, int _y, int _w, int _h );
void set_color( SDL_Renderer* renderer, color_t color );

void fill_rect(
	SDL_Renderer* renderer,
	int x,
	int y,
	int w,
	int h,
	color_t clr
);
void draw_line(SDL_Renderer* rndr, vec2d_t * v1, vec2d_t * v2);

void draw_triangle(SDL_Renderer * rndr, triangle2d_t triangle);

void fill_triangle(SDL_Renderer * rndr, triangle2d_t triangle, color_t color);
