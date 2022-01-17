
#include "matrix.h"
#include "vector.h"
#include "utils.h"
#include <math.h>
#include <stdio.h>

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////


matrix3x3_t rot_x_matrix(float ang) {
	return (matrix3x3_t)
	{
		.r1 = {1.0,      0.0,       0.0},
		.r2 = {0.0, cos(ang), -sin(ang)},
		.r3 = {0.0, sin(ang),  cos(ang)}
	};
}

matrix3x3_t rot_y_matrix(float ang) {
	return (matrix3x3_t)
	{
		.r1 = { cos(ang), 0.0, sin(ang)},
		.r2 = {      0.0, 1.0,      0.0},
		.r3 = {-sin(ang), 0.0, cos(ang)}
	};
}

matrix3x3_t rot_z_matrix(float ang)  {
	return (matrix3x3_t)
	{
		.r1 = {cos(ang), -sin(ang), 0.0},
		.r2 = {sin(ang),  cos(ang), 0.0},
		.r3 = {0.0,            0.0, 1.0}
	};
}

matrix4x4_t projection_matrix(float near, float far, float fov, float ar){
	float fov_rad = 1.0f / tan(fov * 0.5f / 180.0f * 3.1415926535f);
	return (matrix4x4_t)
	{
		.m[0] = {ar * fov_rad, 0.0f    , 0.0f                        , 0.0f},
		.m[1] = {0.0f         , fov_rad, 0.0f                        , 0.0f},
		.m[2] = {0.0f         , 0.0f    , far / (far - near)         , 1.0f},
		.m[3] = {0.0f         , 0.0f    , (-far * near) / (far- near), 0.0f}
	};
}



void mat4x4_mult(vec3d_t *v, matrix4x4_t m) {
	vec3d_t i = *v;
	v->x    = (i.x * m.m[0][0]) + (i.y * m.m[1][0]) + (i.z * m.m[2][0]) + m.m[3][0];
	v->y    = (i.x * m.m[0][1]) + (i.y * m.m[1][1]) + (i.z * m.m[2][1]) + m.m[3][1];
	v->z    = (i.x * m.m[0][2]) + (i.y * m.m[1][2]) + (i.z * m.m[2][2]) + m.m[3][2];
	float w = (i.x * m.m[0][3]) + (i.y * m.m[1][3]) + (i.z * m.m[2][3]) + m.m[3][3];
	if (w != 0) {
		v->x /= w;
		v->y /= w;
		v->z /= w;
	}
}

void mat3x3_mult(vec3d_t * v1, matrix3x3_t mat) {
	vec3d_t tmp = *v1;
	v1->x = (mat.r1.x * tmp.x) + (mat.r1.y * tmp.y) + (mat.r1.z * tmp.z);
	v1->y = (mat.r2.x * tmp.x) + (mat.r2.y * tmp.y) + (mat.r2.z * tmp.z);
	v1->z = (mat.r3.x * tmp.x) + (mat.r3.y * tmp.y) + (mat.r3.z * tmp.z);
}
void rotate_x(vec3d_t * v1, float angle) {
	mat3x3_mult(v1, rot_x_matrix(angle));
}
void rotate_y(vec3d_t * v1, float angle) {
	mat3x3_mult(v1, rot_y_matrix(angle));
}
void rotate_z(vec3d_t * v1, float angle) {
	mat3x3_mult(v1, rot_z_matrix(angle));
}
