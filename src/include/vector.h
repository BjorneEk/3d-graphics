#pragma once

#include "utils.h"

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

typedef struct vec4d {
	float i;
	float j;
	float k;
	float l;
} vec4d_t;

typedef struct vec3d {
	float x;
	float y;
	float z;
} vec3d_t;

typedef struct vec2d {
	float x;
	float y;
} vec2d_t;



///
/// create a new vector
///
vec3d_t * new_vec3d(float x, float y, float z);
vec2d_t * new_vec2d(float x, float y);

float length_3d(vec3d_t * vec);
float length_2d(vec2d_t * vec);

///
/// standard vector - vector arithmetic
///
void add_3d(vec3d_t * v1, vec3d_t v2);
void add_2d(vec2d_t * v1, vec2d_t v2);
void sub_3d(vec3d_t * v1, vec3d_t v2);
void sub_2d(vec2d_t * v1, vec2d_t v2);
void mult_3d(vec3d_t * v1, vec3d_t v2);
void mult_2d(vec2d_t * v1, vec2d_t v2);
void div_3d(vec3d_t * v1, vec3d_t v2);
void div_2d(vec2d_t * v1, vec2d_t v2);

///
/// standard vector - scalar arithmetic
///
void add_scalar_3d(vec3d_t * v1, float scalar);
void add_scalar_2d(vec2d_t * v1, float scalar);
void sub_scalar_3d(vec3d_t * v1, float scalar);
void sub_scalar_2d(vec2d_t * v1, float scalar);
void mult_scalar_3d(vec3d_t * v1, float scalar);
void mult_scalar_2d(vec2d_t * v1, float scalar);
void div_scalar_3d(vec3d_t * v1, float scalar);
void div_scalar_2d(vec2d_t * v1, float scalar);

vec2d_t * to_vec2d(vec3d_t * vec);

vec3d_t * to_vec3d(vec2d_t * vec);

char * v3d_to_str(vec3d_t vec);
char * v2d_to_str(vec2d_t vec);

uint8_t equals_v2d(vec2d_t v1, vec2d_t v2);
uint8_t equals_v3d(vec3d_t v1, vec3d_t v2);

float dist(vec3d_t v1, uint32_t x, uint32_t y);

float lerp_dist(vec2d_t v1, vec2d_t v2);

vec3d_t copy_vec(vec3d_t vec);

vec3d_t cross_prod(vec3d_t v1, vec3d_t v2);
float dot_prod(vec3d_t v1, vec3d_t v2);
vec2d_t add_2d_2(vec2d_t v1, vec2d_t v2);
vec2d_t sub_2d_2(vec2d_t v1, vec2d_t v2);
vec2d_t mult_2d_2(vec2d_t v1, float s);
vec2d_t div_2d_2(vec2d_t v1, float s);
vec3d_t add_3d_2(vec3d_t v1, vec3d_t v2);
vec3d_t sub_3d_2(vec3d_t v1, vec3d_t v2);

void normalize(vec3d_t * v);

float cmp_vec(vec3d_t v1, vec3d_t v2);
