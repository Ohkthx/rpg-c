#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <pthread.h>

#include "buffer.h"

void bshift(void)
{
	int n;

	for(n = 0; n < STRINGS-1; n++)
	{
		if(buf->s[n+1] != NULL)
			strncpy(buf->s[n], buf->s[n+1], 64);
	}

}

void binit(void)
{
	buf = malloc(sizeof(buffer_t));
	memset(&buf->cbuf, 0, MAXCHAR*STRINGS);

	buf->start = &buf->cbuf[0];
	buf->end   = &buf->cbuf[MAXCHAR*STRINGS-1];
	buf->c     = buf->start;
	buf->n = 0;
}

void bwrite(char *fmt, ...)
{
	char string[MAXCHAR];
	va_list ap;
	va_start(ap, fmt);

	vsnprintf(string, MAXCHAR, fmt, ap);
	if(buf->n < STRINGS)
	{
		sprintf(buf->cbuf + (buf->n * MAXCHAR), "%s", string);
		buf->s[buf->n] = &buf->cbuf[buf->n*MAXCHAR];
		buf->n++;
	} else {
		bshift();
		sprintf(buf->cbuf + ((STRINGS-1) * MAXCHAR), "%s", string);
		buf->s[STRINGS-1] = &buf->cbuf[((STRINGS-1)*MAXCHAR)];
	}

	va_end(ap);
}

void bprintf(void)
{
	system("clear");
	printf("- - - - - - - - - - - - - - - - - - - -\n");
	for(int n = 0; n < STRINGS; n++)
	{
		if(buf->s[n] != NULL)
			printf(" %s \n", buf->s[n]);
	}
	printf("- - - - - - - - - - - - - - - - - - - -\n");

}
