#ifndef _BUFFER_H
#define _BUFFER_H 1


#define MAXCHAR 64
#define STRINGS 6


typedef struct buffer
{
	char cbuf[MAXCHAR*STRINGS];
	char *start;	char *end;
	char *c;	char *s[6];
	int n;

} buffer_t;

struct buffer *buf;

void bwrite(char *fmt, ...);
void binit(void);
void bprintf(void);
void bshift(void);

#endif
