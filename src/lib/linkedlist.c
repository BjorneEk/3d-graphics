#include "../include/linkedlist.h"
#include "../include/vector.h"
#include "../include/triangle.h"
#include "../include/utils.h"

#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////
///        @author Gustaf Franzén :: https://github.com/BjorneEk;        ///
////////////////////////////////////////////////////////////////////////////

node_t * new_node(triangle3d_t * t) {
	node_t * tmp = malloc(sizeof(node_t));
	tmp->t = t;
	tmp->next = NULL;
	return tmp;
}
void push(node_t ** head, triangle3d_t * y) {
	node_t * tmp = (*head)->next;
	(*head)->next = new_node(y);
	(*head)->next->next = tmp;
}
void clear(node_t * head) {
	node_t * tmp = head;
	while (head != NULL) {
		head = head->next;
		free(tmp);
		tmp = head;
	}
}

uint8_t greater_than(node_t * n1, node_t * n2) {
	return z_avg(n1->t) > z_avg(n2->t);
}

node_t * mid_node(node_t * head) {
	node_t * slow = head;
	node_t * fast = head->next;
	while(fast != NULL && fast->next != NULL) {
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

node_t * merge(node_t * a, node_t * b) {
	return merge_by(a, b, greater_than);
}

node_t * merge_sort(node_t * head) {
	return merge_sort_by(head, greater_than);
}

node_t * merge_by(node_t * a, node_t * b, uint8_t (*compare)(node_t *, node_t *)) {
	if (a == NULL) return b;
	if (b == NULL) return a;

	node_t * c;
	if (compare(a, b)) {
		c = b;
		c->next = merge_by(a, b->next, compare);
	} else {
		c = a;
		c->next = merge_by(a->next, b, compare);
	}
	return c;
}

node_t * merge_sort_by(node_t * head, uint8_t (*compare)(node_t *, node_t *)) {
	if (head == NULL || head->next == NULL) return head;

	node_t * mid = mid_node(head);

	node_t * a = head;
	node_t * b = mid->next;
	mid->next = NULL;

	a = merge_sort_by(a, compare);
	b = merge_sort_by(b, compare);

	return merge_by(a, b, compare);
}
