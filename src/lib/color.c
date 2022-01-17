
#include "../include/color.h"
#include "../include/utils.h"
#include <stdlib.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

color_t rgba(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha) {
	color_t color;
	color.red   = red;
	color.green = green;
	color.blue  = blue;
	color.alpha = alpha;
	return color;
}

color_t rgb(uint8_t red, uint8_t green, uint8_t blue) {
	return rgba(red, green, blue, COLOR_MAX);
}

uint8_t red(color_t * color) {
	return color->red;
}
uint8_t green(color_t * color) {
	return color->green;
}
uint8_t blue(color_t * color) {
	return color->blue;
}
uint8_t alpha(color_t * color) {
	return color->alpha;
}
double _alpha(color_t * color){
	return color->alpha / COLOR_MAX;
}

uint8_t brightness(color_t * color) {
	return (uint8_t)((color->red + color->green + color->blue)/3);
}
char * debug(color_t * color) {
	char * msg = malloc(43*sizeof(char));
	if (color->alpha != COLOR_MAX) {
		snprintf(msg, 43, "red: %d, green: %d, blue: %d, alpha: %d",
				      color->red, color->green, color->blue, color->alpha);
	}
	else {
		snprintf(msg, 43, "red: %d, green: %d, blue: %d",
				      color->red, color->green, color->blue);
	}
	return msg;
}

color_t with_brightness(color_t * color, float b) {
	return (color_t)
	{
		b* color->red,
		b * color->green,
		b * color->blue,
		b * color->alpha
	};
}
