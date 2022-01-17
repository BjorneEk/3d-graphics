
#include "../include/vector.h"
#include "../include/matrix.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

vec3d_t * new_vec3d(float x, float y, float z) {
	vec3d_t * res = malloc(sizeof(vec3d_t));
	res->x = x;
	res->y = y;
	res->z = z;
	return res;
}

vec2d_t * new_vec2d(float x, float y) {
	vec2d_t * res = malloc(sizeof(vec2d_t));
	res->x = x;
	res->y = y;
	return res;
}

float length_3d(vec3d_t * vec) {
	return sqrt( (vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z) );
}

float length_2d(vec2d_t * vec) {
	return sqrt( (vec->x * vec->x) + (vec->y * vec->y) );
}
/// vector-vector arithmetic
void add_3d(vec3d_t * v1, vec3d_t v2) {
	v1->x += v2.x;
	v1->y += v2.y;
	v1->z += v2.z;
}
void add_2d(vec2d_t * v1, vec2d_t v2) {
	v1->x += v2.x;
	v1->y += v2.y;
}
void sub_3d(vec3d_t * v1, vec3d_t v2) {
	v1->x -= v2.x;
	v1->y -= v2.y;
	v1->z -= v2.z;
}
void sub_2d(vec2d_t * v1, vec2d_t v2) {
	v1->x -= v2.x;
	v1->y -= v2.y;
}
void mult_3d(vec3d_t * v1, vec3d_t v2) {
	v1->x *= v2.x;
	v1->y *= v2.y;
	v1->z *= v2.z;
}
void mult_2d(vec2d_t * v1, vec2d_t v2) {
	v1->x *= v2.x;
	v1->y *= v2.y;
}
void div_3d(vec3d_t * v1, vec3d_t v2) {
	v1->x /= v2.x;
	v1->y /= v2.y;
	v1->z /= v2.z;
}
void div_2d(vec2d_t * v1, vec2d_t v2) {
	v1->x /= v2.x;
	v1->y /= v2.y;
}
/// vector-scalar arithmetic
void add_scalar_3d(vec3d_t * v1, float scalar) {
	v1->x += scalar;
	v1->y += scalar;
	v1->z += scalar;
}
void add_scalar_2d(vec2d_t * v1, float scalar) {
	v1->x += scalar;
	v1->y += scalar;
}
void sub_scalar_3d(vec3d_t * v1, float scalar) {
	v1->x -= scalar;
	v1->y -= scalar;
	v1->z -= scalar;
}
void sub_scalar_2d(vec2d_t * v1, float scalar) {
	v1->x -= scalar;
	v1->y -= scalar;
}
void mult_scalar_3d(vec3d_t * v1, float scalar) {
	v1->x *= scalar;
	v1->y *= scalar;
	v1->z *= scalar;
}
void mult_scalar_2d(vec2d_t * v1, float scalar) {
	v1->x *= scalar;
	v1->y *= scalar;
}
void div_scalar_3d(vec3d_t * v1, float scalar) {
	v1->x /= scalar;
	v1->y /= scalar;
	v1->z /= scalar;
}
void div_scalar_2d(vec2d_t * v1, float scalar) {
	v1->x /= scalar;
	v1->y /= scalar;
}

vec2d_t * to_vec2d(vec3d_t * vec) {
	return realloc(vec, sizeof(vec2d_t));
}
vec3d_t * to_vec3d(vec2d_t * vec) {
	return realloc(vec, sizeof(vec3d_t));
}

char * v3d_to_str(vec3d_t vec) {
	char * res = malloc(33 * sizeof(char));
	sprintf(res, "{%f | %f | %f}", vec.x, vec.y, vec.z);
	return res;
}
char * v2d_to_str(vec2d_t vec)  {
	char * res = malloc(25 * sizeof(char));
	sprintf(res, "{%f | %f}", vec.x, vec.y);
	return res;
}

uint8_t equals_v2d(vec2d_t v1, vec2d_t v2) {
	return (v1.x == v2.x) && (v1.y == v2.y);
}
uint8_t equals_v3d(vec3d_t v1, vec3d_t v2) {
	return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
}

float dist(vec3d_t v1, uint32_t x, uint32_t y) {
	return sqrt( ((x - v1.x)*(x - v1.x)) + ((y - v1.y)*(y - v1.y)));
}
float lerp_dist(vec2d_t v1, vec2d_t v2) {
	return sqrt(fabsf(((v2.x - v1.x)*(v2.x - v1.x)) + ((v2.y - v1.y)*(v2.y - v1.y))));
}

vec3d_t copy_vec(vec3d_t vec) {
	return (vec3d_t){
		.x = vec.x,
		.y = vec.y,
		.z = vec.z
	};
}
vec3d_t cross_prod(vec3d_t v1, vec3d_t v2) {
	return (vec3d_t)
	{
		.x = v1.y*v2.z - v1.z*v2.y,
		.y = v1.z*v2.x - v1.x*v2.z,
		.z = v1.x*v2.y - v1.y*v2.x
	};
}

vec2d_t add_2d_2(vec2d_t v1, vec2d_t v2) {
	return (vec2d_t){.x=v1.x+v2.x, .y=v1.y+v2.y};
}
vec2d_t sub_2d_2(vec2d_t v1, vec2d_t v2) {
	return (vec2d_t){.x=v1.x-v2.x, .y=v1.y-v2.y};
}
vec2d_t mult_2d_2(vec2d_t v1, float s) {
	return (vec2d_t){.x=v1.x*s, .y=v1.y*s};
}
vec2d_t div_2d_2(vec2d_t v1, float s) {
	return (vec2d_t){.x=v1.x/s, .y=v1.y/s};
}


vec3d_t add_3d_2(vec3d_t v1, vec3d_t v2) {
	return (vec3d_t){.x=v1.x+v2.x, .y=v1.y+v2.y,.z=v1.z+v2.z};
}
vec3d_t sub_3d_2(vec3d_t v1, vec3d_t v2) {
	return (vec3d_t){.x=v1.x-v2.x, .y=v1.y-v2.y,.z=v1.z-v2.z};
}

void normalize(vec3d_t * v) {
	float length = sqrt(fabsf(v->x*v->x + v->y*v->y + v->z*v->z));
	v->x = v->x/length;
	v->y = v->y/length;
	v->z = v->z/length;
}

float dot_prod(vec3d_t v1, vec3d_t v2) {
	return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}
