
#include"/Library/Frameworks/SDL2.framework/Headers/SDL.h"   /* All SDL App's need this */

#define __timespec_defined 1
#define __timeval_defined 1
#define __itimerspec_defined 1

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "include/linkedlist.h"
#include "include/window.h"
#include "include/color.h"
#include "include/utils.h"
#include "obj.h"

#define QUITKEY SDLK_ESCAPE

#define WIDTH  2000
#define HEIGHT 1200

	/* keybindigs */
#define W     0x1A
#define A     0x04
#define S     0x16
#define D     0x07
#define UP    0x52
#define LEFT  0x50
#define DOWN  0x51
#define RIGHT 0x4F
#define H     0x0B /// DRAW WIREFRAME
#define J     0x0D /// RENDER WITH COLOR
#define K     0x0E /// SORT TRIANGLES
#define L     0x0F /// RENDER PROPER LIGHTING
#define SHIFT 0xE1

	/* projection constants */

float NEAR = 0.1f;
float FAR  = 1000.0f;
float FOV  = 90.0f;
float ASPECT_RATIO = 1200.0f / 2000.0f;

	/* initial values */
float cube_size = 100.0f;
float cube_x    = 0.0f;
float cube_y    = 0.0f;
float cube_z    = 400.0f;

vec3d_t camera = (vec3d_t){
	.x = 0,
	.y = 0.0,
	.z = 0.0
};
vec3d_t light_dir = (vec3d_t){
	.x = 0,
	.y = 0.0,
	.z = -1.0
};

SDL_Window   * screen = NULL;
SDL_Renderer * renderer;
SDL_Event      event;
SDL_Rect       source;
SDL_Rect       destination;
SDL_Rect       dst;

color_t bg_color = (color_t){
	.red   = 254,
	.green = 228,
	.blue  = 194,
};
color_t fg_color = (color_t){
	.red   = 38,
	.green = 192,
	.blue  = 183,
};

int errorCount = 0;

uint8_t MOUSE_1_DOWN = 0;
uint8_t MOUSE_2_DOWN = 0;
uint8_t SHIFT_DOWN   = 0;

uint8_t WIREFRAME    = 0;
uint8_t RENDER       = 1;
uint8_t LIGHTING     = 1;
uint8_t SORT         = 1;
int mx = 0;
int my = 0;

OBJ_t teapot;
OBJ_t org_teapot;

matrix4x4_t proj_mat;

void log_error(char* msg) {
	fprintf(stderr, "\033[31;1;4m[Error]\033[0m %s | %s\n",msg, strerror( errno ));
	errorCount++;
}

void show() {
	SDL_RenderPresent(renderer);
}

void finnish() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(screen);
	//Quit SDL
	free(org_teapot.tris);
	free(teapot.tris);
	SDL_Quit();
	exit(0);
}

OBJ_t copy_obj(OBJ_t obj) {
	OBJ_t res;
	res.length = obj.length;
	res.tris = malloc(obj.length * sizeof(triangle3d_t));
	for (size_t i = 0; i < obj.length; i++) {
		res.tris[i] = copy_trig(obj.tris[i]);
	}
	return res;
}

void resize(float amount) {
	for (size_t i = 0; i < teapot.length; i++) {
		mult_scalar_3d(&teapot.tris[i].p1, amount);
		mult_scalar_3d(&teapot.tris[i].p2, amount);
		mult_scalar_3d(&teapot.tris[i].p3, amount);
	}
}

void rotate_mesh_y(float amount){
	for (size_t i = 0; i < org_teapot.length; i++) {
		sub_scalar_3d(&org_teapot.tris[i].p1, 0.5);
		sub_scalar_3d(&org_teapot.tris[i].p2, 0.5);
		sub_scalar_3d(&org_teapot.tris[i].p3, 0.5);
		rotate_x(&org_teapot.tris[i].p1, amount);
		rotate_x(&org_teapot.tris[i].p2, amount);
		rotate_x(&org_teapot.tris[i].p3, amount);
		add_scalar_3d(&org_teapot.tris[i].p1, 0.5);
		add_scalar_3d(&org_teapot.tris[i].p2, 0.5);
		add_scalar_3d(&org_teapot.tris[i].p3, 0.5);
	}
}

void rotate_mesh_x(float amount){
	for (size_t i = 0; i < org_teapot.length; i++) {
		sub_scalar_3d(&org_teapot.tris[i].p1, 0.5);
		sub_scalar_3d(&org_teapot.tris[i].p2, 0.5);
		sub_scalar_3d(&org_teapot.tris[i].p3, 0.5);
		rotate_y(&org_teapot.tris[i].p1, -amount);
		rotate_y(&org_teapot.tris[i].p2, -amount);
		rotate_y(&org_teapot.tris[i].p3, -amount);
		add_scalar_3d(&org_teapot.tris[i].p1, 0.5);
		add_scalar_3d(&org_teapot.tris[i].p2, 0.5);
		add_scalar_3d(&org_teapot.tris[i].p3, 0.5);
	}
}

void repaint() {
	fill_rect(renderer, 0, 0, WIDTH, HEIGHT, bg_color);
	if (teapot.tris != NULL) free(teapot.tris);
	teapot = copy_obj(org_teapot);
	resize(cube_size);
	if (SORT)
		sort(teapot);
	for (size_t i = 0; i < teapot.length; i++) {
		triangle3d_t new = teapot.tris[i];
		vec3d_t norm = normal(new);
		new.p1.x += cube_x;
		new.p2.x += cube_x;
		new.p3.x += cube_x;

		new.p1.y += cube_y;
		new.p2.y += cube_y;
		new.p3.y += cube_y;

		new.p1.z += cube_z;
		new.p2.z += cube_z;
		new.p3.z += cube_z;

		if (norm.x * (new.p1.x - camera.x) +
			 norm.y * (new.p1.y - camera.y) +
		    norm.z * (new.p1.z - camera.z) < 0.0) {

			mat4x4_mult(&new.p1, proj_mat);
			mat4x4_mult(&new.p2, proj_mat);
			mat4x4_mult(&new.p3, proj_mat);


			new.p1.y += 1; new.p1.x += 1;
			new.p2.y += 1; new.p2.x += 1;
			new.p3.y += 1; new.p3.x += 1;

			new.p1.x *= 0.5*WIDTH;
			new.p2.x *= 0.5*WIDTH;
			new.p3.x *= 0.5*WIDTH;

			new.p1.y *= 0.5*HEIGHT;
			new.p2.y *= 0.5*HEIGHT;
			new.p3.y *= 0.5*HEIGHT;

			normalize(&light_dir);
			float light = dot_prod(norm, light_dir);
			if (RENDER && LIGHTING)
				fill_triangle(renderer, render(&new), with_brightness(&fg_color, light));
			else if (RENDER)
				fill_triangle(renderer, render(&new), fg_color);
			set_color(renderer, BLACK);
			if (WIREFRAME)
				draw_triangle(renderer, render(&new));
		}
	}
	show();
}

int init_setup() {
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &screen, &renderer);
	if (!screen) {
		log_error("init_setup failed to create window");
		return -1;
	}
	repaint();
	return 0;
}

void event_loop() {
	int running = 1;
	while (running) {
		repaint();
		while ( SDL_PollEvent( &event ) ) {
			switch ( event.type ) {
				case SDL_MOUSEBUTTONDOWN:

					switch (event.button.button) {
						case SDL_BUTTON_LEFT:
							MOUSE_1_DOWN = 1;
							break;
						case SDL_BUTTON_RIGHT:
							MOUSE_2_DOWN = 1;
							break;
						default: break;
					}
					break;

				case SDL_MOUSEBUTTONUP:
					switch (event.button.button) {
						case SDL_BUTTON_LEFT:
							MOUSE_1_DOWN = 0;
							break;
						case SDL_BUTTON_RIGHT:
							MOUSE_2_DOWN = 0;
							break;
						default: break;
					}
					break;

				case SDL_MOUSEMOTION:
					if (SHIFT_DOWN && MOUSE_2_DOWN) {
						cube_x += (event.motion.x - mx);
						cube_y += (event.motion.y - my);
					} else if (MOUSE_2_DOWN) {
						rotate_mesh_x((event.motion.x - mx)/300.0);
						rotate_mesh_y((event.motion.y - my)/300.0);
					} else if (MOUSE_1_DOWN) {

					}
					mx = event.motion.x;
					my = event.motion.y;
					break;
				case SDL_MOUSEWHEEL:
					if(event.wheel.y > 0) {
						cube_z+=2;
					} else if(event.wheel.y < 0) {
						cube_z-=2;
					}
					break;
				case SDL_QUIT: { /* if mouse click to close window */
					running = 0;
					break;
				}
				case SDL_KEYDOWN:
					switch (event.key.keysym.scancode) {
						case UP:
						case W :
							add_3d(&light_dir, (vec3d_t){0.0,-0.05,0.0});
							break;
						case LEFT:
						case A   :
							add_3d(&light_dir, (vec3d_t){-0.05,0.0,0.0});
							break;
						case DOWN:
						case S   :
							add_3d(&light_dir, (vec3d_t){0.0,0.05,0.0});
							break;
						case RIGHT:
						case D    :
							add_3d(&light_dir, (vec3d_t){0.05,0.0,0.0});
							break;
						case SHIFT:
							SHIFT_DOWN = 1;
							break;
						case H:
							WIREFRAME = !WIREFRAME;
							break;
						case J:
							RENDER = !RENDER;
							break;
						case L:
							LIGHTING = !LIGHTING;
							break;
						case K:
							SORT = !SORT;
							break;
						default:
							printf("%x\n", event.key.keysym.scancode);
							break;
					}
					break;
				case SDL_KEYUP:
					switch (event.key.keysym.scancode) {
						case SHIFT:
							SHIFT_DOWN = 0;
							break;
						default:
							printf("%i\n", event.key.keysym.scancode);
							break;
					}
					break;
			}
		}
	}
}

int start_window() {
	if (init_setup() == -1) {
		return -1;
	}
	event_loop();
	finnish();
	return 0;
}

vec3d_t get_color(char * str) {
	char    * vec_str = trim(str);
	printf("%s\n", vec_str);
	uint32_t idx_1    = indexOf(vec_str, ',');
	uint32_t idx_2    = idx_1 + indexOf(&vec_str[idx_1 + 1], ',');

	uint16_t x_len = idx_1;
	uint16_t y_len = idx_2 - idx_1;
	uint16_t z_len = strlen(str) - (idx_2+1);

	char x_str[x_len + 1];
	char y_str[y_len + 1];
	char z_str[z_len + 1];

	strncpy(x_str, vec_str, x_len);
	strncpy(y_str, &vec_str[idx_1+1], y_len);
	strncpy(z_str, &vec_str[idx_2+2], z_len);
	return (vec3d_t){
		.x=atof(x_str),
		.y=atof(y_str),
		.z=atof(z_str)
	};
}

int main(int argc, char * args[]) {
	if (argc < 2){
		log_error("invalid argument count, enter a file to render");
		return -1;
	} if (!strcmp(args[1], "--help") || argc >= 6) {
		printf("%s <filename.obj>\n", args[0]);
		printf("%s <filename.obj> rand (for random colors)\n", args[0]);
		printf("%s <filename.obj> <FOREGROUND_COLOR> (RED, GREEN, BLUE)\n", args[0]);
		printf("%s <filename.obj> <FOREGROUND_COLOR> <BACKGROUND_COLOR>\n", args[0]);
		printf("%s <filename.obj> <FOREGROUND_RGB> (1,0.7,0.3) values between 1 and 0\n", args[0]);
		printf("%s <filename.obj> <FOREGROUND_RGB> <BACKGROUND_RGB>\n", args[0]);
		return 0;
	} else if (argc >= 3) {
		if (!strcmp(args[2], "RED")) {
			fg_color = RED;
		} else if (!strcmp(args[2], "GREEN")) {
			fg_color = GREEN;
		} else if (!strcmp(args[2], "BLUE")) {
			fg_color = BLUE;
		} else if (!strcmp(args[2], "rand")) {
			srand(time(0));
			fg_color = (color_t){
				.red   = rand()*COLOR_MAX,
				.green = rand()*COLOR_MAX,
				.blue  = rand()*COLOR_MAX,
			};
			bg_color = (color_t){
				.red   = rand()*COLOR_MAX,
				.green = rand()*COLOR_MAX,
				.blue  = rand()*COLOR_MAX,
			};
		} else {
			vec3d_t color = get_color(args[2]);
			fg_color = (color_t) {
				.red   = color.x * COLOR_MAX,
				.green = color.y * COLOR_MAX,
				.blue  = color.z * COLOR_MAX
			};
			printf("%s\n", v3d_to_str(color));
		}
		if (argc > 3) {
			if (!strcmp(args[3], "RED")) {
				bg_color = RED;
			} else if (!strcmp(args[3], "GREEN")) {
				bg_color = GREEN;
			} else if (!strcmp(args[3], "BLUE")) {
				bg_color = BLUE;
			} else {
				vec3d_t color = get_color(args[3]);
				bg_color = (color_t) {
					.red   = color.x * COLOR_MAX,
					.green = color.y * COLOR_MAX,
					.blue  = color.z * COLOR_MAX
				};
				printf("%s\n", v3d_to_str(color));
			}
		}
	}

	if (read_OBJ(&org_teapot, args[1]) == -1) return -1;
	proj_mat = projection_matrix(NEAR, FAR, FOV, ASPECT_RATIO);
	if (start_window() == -1) return -1;
	return 0;
}
