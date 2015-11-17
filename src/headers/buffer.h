#ifndef _BUFFER_H
#define _BUFFER_H 1


#define MAXBUFF 128
#define STRINGS 5

#include "soul_create.h"


typedef struct buffer
{
	char cbuf[MAXBUFF*STRINGS];
	char *start;	char *end;
	char *c;	char *s[STRINGS];
	int n;		int u;

} buffer_t;

struct buffer *buf;

void bwrite(char *fmt, ...);
void binit(void);
void bprintf(soul_t *ptr);
void bshift(void);

#endif
