#pragma once

#include "vector.h"
#include "utils.h"
#include "matrix.h"
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

typedef struct triangle3d {
	union {
		struct {
			vec3d_t p1;
			vec3d_t p2;
			vec3d_t p3;
		};
		vec3d_t p[3];
	};
} triangle3d_t;

typedef struct triangle2d {
	union {
		struct {
			vec2d_t p1;
			vec2d_t p2;
			vec2d_t p3;
		};
		vec2d_t p[3];
	};
} triangle2d_t;



triangle3d_t * new_triangle3d(vec3d_t p1, vec3d_t p2, vec3d_t p3);

triangle3d_t copy_trig(triangle3d_t tri);
float z_avg(triangle3d_t * tri);

uint8_t tri_contains(triangle3d_t * tri, vec3d_t p);
uint8_t equals_tri(triangle3d_t * t1, triangle3d_t * t2);

triangle2d_t render(triangle3d_t * tri);

void print_trig(triangle3d_t tri);

vec3d_t normal(triangle3d_t trig);
