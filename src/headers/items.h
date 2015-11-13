#ifndef _items_header_h
#define _items_header_h	1

#include "soul_create.h"


int  item_consume(soul_t *ptr);
void item_init(item_t *item, char *name, int amount);
void item_use(soul_t *ptr, char *name);
void item_load(objects_t *objs);
void item_store(objects_t *items, float *gold);
void item_buy(item_t *item, float *gold);

#endif
