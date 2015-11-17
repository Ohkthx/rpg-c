#ifndef G_TOOLS_INCLUDED
#define G_TOOLS_INCLUDED	1

#define KNRM  "\x1b[0m"

#define KRED  "\x1b[31m"	// Regular Red (used for health)
#define BRED  "\x1b[31;1m"

#define KGRN  "\x1b[32m"
#define BGRN  "\x1b[32;1m"

#define KYEL  "\x1b[33m"
#define BYEL  "\x1b[33;1m"	// Bright yellow used for gold.

#define KBLU  "\x1b[34m"
#define BBLU  "\x1b[34;1m"

#define KMAG  "\x1b[35m"

#define KCYN  "\x1b[36m"
#define BCYN  "\x1b[36;1m"

#define KWHT  "\x1b[37m"
#define RESET "\x1b[0m"


#include "soul_create.h"
#include "location.h"


void tools(char *code, soul_t *ptr);
void menus(soul_t *ptr, byte code);
void hpbar(soul_t *ptr, char *string, int bar_amount);
void round_menu(soul_t *ptr);
void stat_print(soul_t *ptr);
void quit(soul_t *ptr, node_t *head);
void readme_read(void);

#endif
