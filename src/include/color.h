#pragma once
#include "utils.h"

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

typedef struct color {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
} color_t;

#define COLOR_MAX 255

#define RED   (color_t){COLOR_MAX, 0, 0}
#define GREEN (color_t){0, COLOR_MAX, 0}
#define BLUE  (color_t){0, 0, COLOR_MAX}
#define BLACK  (color_t){0, 0, 0}
#define WHITE  (color_t){COLOR_MAX, COLOR_MAX, COLOR_MAX}

color_t rgba(
	uint8_t red,
	uint8_t green,
	uint8_t blue,
	uint8_t alpha
);

color_t rgb(
	uint8_t red,
	uint8_t green,
	uint8_t blue
);

uint8_t red(   color_t * color );
uint8_t green( color_t * color );
uint8_t blue(  color_t * color );
uint8_t alpha( color_t * color );
double _alpha( color_t * color );

uint8_t brightness( color_t * color );
char * debug( color_t * color );

color_t with_brightness(color_t * color, float brightness);
