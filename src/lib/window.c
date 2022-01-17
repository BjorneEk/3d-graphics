#include "../include/window.h"
#include "/Library/Frameworks/SDL2.framework/Headers/SDL.h"
#include "../include/utils.h"
#include "../include/color.h"
//#include "../include/linkedlist.h"
#include "../include/vector.h"
#include "../include/triangle.h"

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

void set_title(char* msg, SDL_Window* screen) {
	SDL_SetWindowTitle(screen, msg);
}

SDL_Rect rectangle(int _x, int _y, int _w, int _h) {
	SDL_Rect rect;
	rect.h = _h;
	rect.w = _w;
	rect.y = _y;
	rect.x = _x;
	return rect;
}
void set_color(SDL_Renderer * renderer, color_t color) {
	SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, color.alpha);
}

void set_pixel( SDL_Renderer* renderer, vec2d_t * p) {
	SDL_RenderDrawPoint(renderer, (int)p->x, (int)p->y);
}

void fill_rect(SDL_Renderer* rndr, int x, int y, int w, int h, color_t clr) {
	set_color(rndr, clr);
	SDL_Rect rect;
	rect = rectangle( x, y, w, h );
	SDL_RenderFillRect(rndr, &rect);
}
void draw_line(SDL_Renderer* rndr, vec2d_t * v1, vec2d_t * v2) {
		SDL_RenderDrawLine(rndr, (int)(v1->x), (int)(v1->y), (int)(v2->x), (int)(v2->y));
}

void draw_triangle(SDL_Renderer * rndr, triangle2d_t triangle) {
	draw_line(rndr, &triangle.p1, &triangle.p2);
	draw_line(rndr, &triangle.p2, &triangle.p3);
	draw_line(rndr, &triangle.p3, &triangle.p1);
}



/////////////////////////////////////////////////////////////////////////////
///                                                                       ///
///       for each corner draw a line from that corner                    ///
///       to each point on the line between the two other                 ///
///       corners. this fills the triangle however it is                  ///
///       not verry efficent.                                             ///
///                                                                       ///
/////////////////////////////////////////////////////////////////////////////
void fill_triangle(SDL_Renderer * rndr, triangle2d_t triangle, color_t color) {
	set_color(rndr, color);
	uint32_t dist = (uint32_t)lerp_dist(triangle.p2, triangle.p3);
	vec2d_t lv = sub_2d_2(triangle.p2, triangle.p3);
	for (float i = 0; i < dist; i+=1) {
		vec2d_t next = add_2d_2(triangle.p3, mult_2d_2(lv, i/dist));
		draw_line(rndr, &triangle.p1, &next);
	}
	dist = (uint32_t)lerp_dist(triangle.p2, triangle.p1);
	lv = sub_2d_2(triangle.p2, triangle.p1);
	for (float i = 0; i < dist; i+=1) {
		vec2d_t next = add_2d_2(triangle.p1, mult_2d_2(lv, i/dist));
		draw_line(rndr, &triangle.p3, &next);
	}
	dist = (uint32_t)lerp_dist(triangle.p3, triangle.p1);
	lv = sub_2d_2(triangle.p3, triangle.p1);
	for (float i = 0; i < dist; i+=1) {
		vec2d_t next = add_2d_2(triangle.p1, mult_2d_2(lv, i/dist));
		draw_line(rndr, &triangle.p2, &next);
	}
}
