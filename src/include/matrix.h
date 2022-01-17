#pragma once

#include "vector.h"
#include "utils.h"
#include <math.h>

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

typedef struct matrix3x3 {
	union {
		struct {
			vec3d_t r1;
			vec3d_t r2;
			vec3d_t r3;
		};
		float matrix[3][3];
	};
} matrix3x3_t;

typedef struct matrix4x4 {
	float m[4][4];
} matrix4x4_t;


inline matrix3x3_t rot_x_matrix(float ang);
inline matrix3x3_t rot_y_matrix(float ang);
inline matrix3x3_t rot_z_matrix(float ang);

matrix4x4_t projection_matrix(float near, float far, float fov, float ar);

void mat4x4_mult(vec3d_t *v, matrix4x4_t m);
void mat3x3_mult(vec3d_t * v1, matrix3x3_t mat);

///
/// transformations:
///
void rotate_x(vec3d_t * v1, float angle);
void rotate_y(vec3d_t * v1, float angle);
void rotate_z(vec3d_t * v1, float angle);
