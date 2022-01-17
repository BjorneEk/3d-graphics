#pragma once

#include "linkedlist.h"
#include "vector.h"
#include "utils.h"
#include "triangle.h"

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

typedef struct node{
	triangle3d_t * t;
	struct node * next;
} node_t;

node_t * new_node(triangle3d_t * t);
void push(node_t ** head, triangle3d_t * t);
void clear(node_t * head);
uint8_t greater_than(node_t * n1, node_t * n2);
node_t * mid_node(node_t * head);
node_t * merge(node_t * a, node_t * b);
node_t * merge_sort(node_t * head);
node_t * merge_by(node_t * a, node_t * b, uint8_t (*compare)(node_t *, node_t *));
node_t * merge_sort_by(node_t * head, uint8_t (*compare)(node_t *, node_t *));
