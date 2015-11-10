#ifndef G_TOOLS_INCLUDED
#define G_TOOLS_INCLUDED

#define MAXCHAR 1024

#define KNRM  "\x1B[0m"

#define KRED  "\x1B[31m"	// Regular Red (used for health)
#define BRED  "\x1B[31;1m"

#define KGRN  "\x1B[32m"
#define BGRN  "\x1B[32;1m"

#define KYEL  "\x1B[33m"
#define BYEL  "\x1B[33;1m"	// Bright yellow used for gold.

#define KBLU  "\x1B[34m"
#define BBLU  "\x1B[34;1m"

#define KMAG  "\x1B[35m"

#define KCYN  "\x1B[36m"
#define BCYN  "\x1B[36;1m"

#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

#define MAXCHAR 1024


#include "soul_create.h"
#include "location.h"


typedef struct buffer
{
	char buff[MAXCHAR];
	char *start;
	char *end;
	int *pos;
	int l_cnt;

} buffer_t;

//int getint(int *num);

void tools(char *code, soul_t *ptr);
void menus(soul_t *ptr, byte code);
void hpbar(soul_t *ptr, char *string, int bar_amount);
void round_menu(soul_t *ptr);
void stat_print(soul_t *ptr);
void quit(soul_t *ptr, node_t *head);
void readme_read(void);
//void bprintf(buffer_t *pbuf, char *fmt, ...);

#endif
