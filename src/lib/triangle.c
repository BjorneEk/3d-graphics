
#include "../include/triangle.h"
#include "../include/vector.h"
#include "../include/matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

static void log_error(char* msg) {
	fprintf(stderr, "\033[31;1;4m[Error]\033[0m %s | %s\n",msg, strerror( errno ));
}


triangle3d_t * new_triangle3d(vec3d_t p1, vec3d_t p2, vec3d_t p3) {
	triangle3d_t * tri = malloc(sizeof(triangle3d_t));
	if (tri == NULL) log_error("error allocating triangle");
	tri->p1 = p1;
	tri->p2 = p2;
	tri->p3 = p3;
	return tri;
}

float z_avg(triangle3d_t * tri) {
	return (tri->p1.z + tri->p2.z + tri->p3.z) / 3;
}

uint8_t tri_contains(triangle3d_t * tri, vec3d_t p) {
	return equals_v3d(tri->p1, p) || equals_v3d(tri->p2, p) || equals_v3d(tri->p3, p);
}

uint8_t equals_tri(triangle3d_t * t1, triangle3d_t * t2) {
	return tri_contains(t1, t2->p1) && tri_contains(t1, t2->p2) && tri_contains(t1, t2->p3);
}
triangle2d_t render(triangle3d_t * tri) {
	return (triangle2d_t)
	{
		.p1 = {tri->p1.x, tri->p1.y},
		.p2 = {tri->p2.x, tri->p2.y},
		.p3 = {tri->p3.x, tri->p3.y}
	};
}

triangle3d_t copy_trig(triangle3d_t tri) {
	return (triangle3d_t)
	{
		.p1 = copy_vec(tri.p1),
		.p2 = copy_vec(tri.p2),
		.p3 = copy_vec(tri.p3)
	};
}
void print_trig(triangle3d_t tri) {
	printf("[ (%i, %i, %i) | (%i, %i, %i) | (%i, %i, %i)]",
	(int)tri.p1.x, (int)tri.p1.y, (int)tri.p1.z,
	(int)tri.p2.x, (int)tri.p2.y, (int)tri.p2.z,
	(int)tri.p3.x, (int)tri.p3.y, (int)tri.p3.z);
}
vec3d_t normal(triangle3d_t trig) {
	vec3d_t v1 = sub_3d_2(trig.p1, trig.p2);
	vec3d_t v2 = sub_3d_2(trig.p1, trig.p3);
	vec3d_t cp = cross_prod(v1, v2);
	normalize(&cp);
	return cp;
}
