#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <pthread.h>

#include "headers/buffer.h"
#include "headers/menus.h"

void binit(void)
{
	buf = malloc(sizeof(buffer_t));
	memset(&buf->cbuf, 0, MAXBUFF*STRINGS);

	buf->start = &buf->cbuf[0];
	buf->end   = &buf->cbuf[MAXBUFF*STRINGS-1];
	buf->c     = buf->start;
	buf->n = 0;
}


void bfree(void)
{
	memset(buf, 0, sizeof(buffer_t));
	free(buf);
}


void bwrite(char *fmt, ...)
{
	char string[MAXBUFF];
	va_list ap;
	va_start(ap, fmt);

	vsnprintf(string, MAXBUFF, fmt, ap);
	if(buf->n < STRINGS)
	{
		sprintf(buf->cbuf + (buf->n * MAXBUFF), "%s", string);
		buf->s[buf->n] = &buf->cbuf[buf->n*MAXBUFF];
		buf->n++;
	} else {
		bshift();
		sprintf(buf->cbuf + ((STRINGS-1) * MAXBUFF), "%s", string);
		buf->s[STRINGS-1] = &buf->cbuf[((STRINGS-1)*MAXBUFF)];
	}

	buf->u = 1;

	va_end(ap);
}


void bprintf(soul_t *ptr)
{
	while(buf->u == 0)
		;
	tools("clear", NULL);
	XY(15, 0);
	// printf(" THIS IS A STOP FOR THE MENU \n");	// Shows where buffer will end.
	XY(0, 0);
	menus(ptr, 1);
	menus(ptr->o, 1);
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	for(int n = 0; n < STRINGS; n++)
	{
		if(buf->s[n] != NULL)
			printf(" %s \n", buf->s[n]);
	}
	printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	buf->u = 0;
	menus(ptr, 2);
	menus(ptr->o, 2);
}


void bshift(void)
{
	int n;

	for(n = 0; n < STRINGS-1; n++)
	{
		if(buf->s[n+1] != NULL)
			strncpy(buf->s[n], buf->s[n+1], MAXBUFF);
	}
}


