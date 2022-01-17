#include "../include/obj.h"
#include "../include/utils.h"
#include "../include/vector.h"
#include "../include/triangle.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>

#define LINE_LENGTH 40

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
///                                                                      ///
///             functions used to read and parse a .obj file             ///
////////////////////////////////////////////////////////////////////////////

static void log_error(char * msg) {
	fprintf(stderr, "\033[31;1;4m[Error]\033[0m %s | %s\n",msg, strerror( errno ));
}
static void log_file_error(char * msg, char * filename) {
	fprintf(stderr, "\033[31;1;4m[Error]\033[0m %s: %s | %s\n",msg, filename, strerror( errno ));
}

void swap(triangle3d_t *xp, triangle3d_t *yp) {
	triangle3d_t temp = *xp;
	*xp = *yp;
	*yp = temp;
}
void sort(OBJ_t o) {
	int i, j, min_idx;
	// One by one move boundary of unsorted subarray
	for (i = 0; i < o.length-1; i++) {
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i+1; j < o.length; j++) {
			if (z_avg(&o.tris[j]) > z_avg(&o.tris[min_idx]))
				min_idx = j;
				// Swap the found minimum element with the first element
			swap(&o.tris[min_idx], &o.tris[i]);
		}
	}
}

int32_t indexOf(char * str, char c) {
	const char *ptr = strchr(str, c);
	if(ptr) {
		return ptr - str;
	} else {
		return -1;
	}
}

uint8_t contains(char * str, char c) {
	if (indexOf(str, c) != -1) return 1;
	return 0;
}

char * trim(char * str) {
	const char *ptr = strchr(str, '\n');
	if(ptr) {
		uint16_t index = ptr - str;
		char * res = malloc(index+2);
		strncpy(res, str, index);
		return res;
	}
	return str;
}

void get_descriptor(char ** res, char * str) {
	const char *ptr = strchr(str, '\n');
	if(ptr) {
		uint16_t index = ptr - str;
		strncpy(*res, str, index);
	} else {
		strncpy(*res, str, OBJ_MAX_DESCRIPTOR-1);
	}
}

vec3d_t get_vec3d(char * str) {
	char    * vec_str = trim(str);
	uint32_t idx_1    = indexOf(vec_str, ' ');
	uint32_t idx_2    = idx_1 + indexOf(&vec_str[idx_1 + 1], ' ');

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

face_t get_face(char * str) {
	char   * face_str = trim(str);

	uint32_t idx_1    = indexOf(face_str, ' ');
	uint32_t idx_2    = idx_1 + indexOf(&face_str[idx_1 + 1], ' ');

	uint16_t p1_len = idx_1;
	uint16_t p2_len = idx_2 - idx_1;
	uint16_t p3_len = strlen(str) - (idx_2+1);

	char p1_str[p1_len + 1];
	char p2_str[p2_len + 1];
	char p3_str[p3_len + 1];

	strncpy(p1_str, face_str, p1_len);
	strncpy(p2_str, &face_str[idx_1+1], p2_len);
	strncpy(p3_str, &face_str[idx_2+2], p3_len);
	return (face_t){
		.p1=atoi(p1_str),
		.p2=atoi(p2_str),
		.p3=atoi(p3_str),
		.p4=0
	};
}

int read_OBJ(OBJ_t * obj, char * filename) {
	FILE * obj_file;
	char * buffer;
	size_t buffer_len;
	uint32_t vertex_count   = 0;
	uint32_t face_count     = 0;
	uint32_t read_vertecies = 0;
	uint32_t read_faces     = 0;

		/* open the file */
	obj_file = fopen(filename, "rb");
	if (obj_file == NULL) {
		log_file_error("could not open file", filename);
		return -1;
	}

		/* 1. get size of file */
	fseek(obj_file, 0, SEEK_END);
	buffer_len = ftell(obj_file);
	fseek(obj_file, 0, SEEK_SET);

		/* 2. read file into a buffer and close it*/
	buffer = malloc(buffer_len + 1 * sizeof(char));
	fread(buffer, buffer_len, 1, obj_file);
	fclose(obj_file);

		/* count nuber of faces and vertecies and set the name*/
	char name[OBJ_MAX_DESCRIPTOR];
	for (size_t i = 0; i < buffer_len; i++) {
		switch ( buffer[i] ) {
			case OBJ_FACE_START:      face_count++;   break;
			case OBJ_VERTEX_START:    vertex_count++; break;
			case OBJ_DESCRIPTOR_START:
				strncpy(name, &buffer[i+2], OBJ_MAX_DESCRIPTOR-1); // from space after o
				char * res = malloc(OBJ_MAX_DESCRIPTOR);
				get_descriptor(&res, name);
				strncpy(obj->descriptor, res, strlen(res));
				if (contains(obj->descriptor, OBJ_FACE_START)) face_count--;
				if (contains(obj->descriptor, OBJ_VERTEX_START)) vertex_count--;
				break;
		}
	}
		/* set the length member sorrectly and allocate tris. 2 triangles per square face*/
	obj->length = face_count;
	obj->tris   = malloc(sizeof(triangle3d_t) * obj->length);

	vec3d_t vector_set[vertex_count];
	face_t  faces[face_count];

		/* 4. loop trough buffer and serch for vectors and faces */
	for (size_t i = 0; i < buffer_len; i++) {
		switch ( buffer[i] ) {
			case OBJ_VERTEX_START:
				vector_set[read_vertecies] = get_vec3d(&buffer[i+2]);
				i+=5;
				//printf("%s\n", v3d_to_str(vector_set[read_vertecies]));
				read_vertecies++;
				continue;
			case OBJ_FACE_START:
				faces[read_faces] = get_face(&buffer[i+2]);
				read_faces++;
				break;
		}
	}

		/* loop through and set the triangles to their correct values */
	for (size_t i = 0; i < obj->length; i += 1) {
		obj->tris[i] = (triangle3d_t){
			.p1=vector_set[faces[i].p1-1],
			.p2=vector_set[faces[i].p2-1],
			.p3=vector_set[faces[i].p3-1]
		};
	}
	return 0;
}
