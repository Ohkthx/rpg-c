#ifndef _items_header_h
#define _items_header_h

#include "soul_create.h"


int  item_consume(soul_t *ptr);
void item_init(item_t *item, char *name, int amount);
void item_use(soul_t *ptr, char *name);
void item_load(objects_t *objs);

#endif
