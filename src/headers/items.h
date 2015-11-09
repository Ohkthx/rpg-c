#ifndef _items_header_h
#define _items_header_h


#include "soul_create.h"

void item_init(item_t *item, char *name, int amount);
void item_use(soul_t *ptr, char *name);

#endif
