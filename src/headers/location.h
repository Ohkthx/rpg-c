#ifndef _LOCATION_HEADER_H
#define _LOCATION_HEADER_H	1

#include "soul_create.h"

typedef struct node
{
	char name[24];	char d[128];	// description
	int id;
	struct node *next;
	struct node *prev;
	struct node *link0;
	struct node *link1;

} node_t;

void list_print(struct node *head);
void list_push(struct node *head);
void list_destroy(struct node *head);
void world_grab(struct node *head);
void location_create(struct node *location, char *name, char *description);
void stage(struct node *head, struct soul *ptr);

#endif
