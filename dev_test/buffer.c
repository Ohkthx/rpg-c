#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>

#define MAXCHAR 64
#define STRINGS 6


typedef struct buffer
{
	char cbuf[MAXCHAR*STRINGS];
	char *start;	char *end;
	char *c;	char *s[7];
	int n;

} buffer_t;

struct buffer *buf;

void bwrite(char *fmt, ...);
void binit(void);
void bprintf(void);
void bshift(void);

int main(void)
{
	time_t t;
	srand((unsigned) time(&t));

	binit();
	
	for(int n = 0; n < 100; n++)
		bwrite("Number: %d", n);

	bprintf();

	printf("\n");
	bshift();

	free(buf);
	return 0;
}


void bshift(void)
{
	printf("In bshift.\n");
	for(int n = STRINGS; n > 1; n--)
	{
		buf->s[n-2] = buf->s[n-1];
		buf->s[n-1] = buf->s[n];
		printf("%s -> %s \n", buf->s[n-1], buf->s[n]);
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
	//if(buf->n > (STRINGS - 1))
	//	buf->n = 0;
	sprintf(buf->cbuf + (buf->n * MAXCHAR), "%s", string);
	buf->s[buf->n] = &buf->cbuf[buf->n*MAXCHAR];
	buf->n++;

	va_end(ap);
}

void bprintf(void)
{
	for(int n = 0; n < STRINGS; n++)
	{
		if(buf->s[n] != NULL)
			printf("%s \n", buf->s[n]);
	}
}
