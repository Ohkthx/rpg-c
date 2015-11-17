#ifndef _BUFFER_H
#define _BUFFER_H 1


#include "soul_create.h"

#define STRINGS 5
#define MAXBUFF 128

#define XY(x, y) printf("\x1b[%d;%dH", x, y);

typedef struct buffer
{
	char cbuf[MAXBUFF*STRINGS];
	char *start;	char *end;
	char *c;	char *s[STRINGS];
	int n;		int u;
	char ch;

} buffer_t;

struct buffer *buf;

void binit(void);
void bfree(void);
void bshift(void);
void bwrite(char *fmt, ...);
void bprintf(soul_t *ptr);

#endif
