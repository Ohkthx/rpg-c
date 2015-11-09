#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "headers/save.h"
#include "headers/soul_create.h"
#include "headers/menus.h"


FILE *fd;
char fd_ext[] = ".txt";

int file_exists(char *ptr)
{
	char filename[(sizeof(ptr) + 4)];
	char filepath[(sizeof(filename) + 5)];
	memset(filepath, 0, sizeof(filepath));

	strncpy(filepath, "save", 5);
	strncpy(filename, ptr, sizeof(filename));
	strncat(filename, fd_ext, 4);

	ntof(filename);

	strncat(filepath, "/", 1);
	strncat(filepath, filename, (sizeof(filepath) - 5));

	fd = fopen(filepath, "r");
	if(fd != NULL)
	{
		fclose(fd);
		return 1;
	}
	return 0;
}

int save(soul_t *ptr)
{
	int n;
	char filename[(sizeof(ptr->name) + 4)];
	char filepath[(sizeof(filename) + 5)];
	memset(filepath, 0, sizeof(filepath));

	strncpy(filepath, "save", 5);
	strncpy(filename, ptr->name, sizeof(filename));
	strncat(filename, fd_ext, 4);

	ntof(filename);

	n = mkdir(filepath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	strncat(filepath, "/", 1);
	strncat(filepath, filename, (sizeof(filepath) - 5));

	fd = fopen(filepath, "w");

	if(fd == NULL)
		printf("Error opening file!\n");
	else
	{
		fprintf(fd, "name:%s;\n", ptr->name);
		if(PASSWD)
			fprintf(fd, "password:%lu;\n", ptr->pass);
		fprintf(fd, "description:%s;\n", ptr->desc);
		fprintf(fd, "class:%c;\n", ptr->attr.cls);
		//fprintf(fd, "\n -   S T A T S   - - - - - - - - - - - - - \n");
		fprintf(fd, "strength:%d;\n", ptr->attr.strength);
		fprintf(fd, "wisdom:%d;\n", ptr->attr.wisdom);
		fprintf(fd, "dexterity:%d;\n", ptr->attr.dexterity);
		fprintf(fd, "gold:%.2f;\n", ptr->gold);
		fprintf(fd, "luck:%d;\n", ptr->luck);
		fprintf(fd, "type:%c;\n", ptr->type);
		fprintf(fd, "range:%d;\n", ptr->attr.range);
		//fprintf(fd, "\n -   L O C K S   - - - - - - - - - - - - - \n");
		fprintf(fd, "primary_lock:%d;\n", ptr->attr.p_lck);
		fprintf(fd, "secondary_lock:%d;\n", ptr->attr.s_lck);
		fprintf(fd, "tertiary_lock:%d;\n", ptr->attr.t_lck);
		//fprintf(fd, "\n -   I T E M S   - - - - - - - - - - - - - \n");
		fprintf(fd, "bandaids:%d;\n", ptr->bandaid.amount);

		fclose(fd);
		printf("\n   Changes written to: %s\n", filename);
	}

	return n;
}

float load_d(int code)
{
	long n;
	float f;
	byte b;
	char *tokk, *ptr;

	tokk = strtok(NULL, ":;");
	if(code == 0) {
		n = strtol(tokk, &ptr, 10);
		return (int) n;
	} else if(code == 1) {
		f = strtof(tokk, &ptr);
		return (float) f;
	} else if(code == 2) {
		b = strtol(tokk, &ptr, 10);
		return (byte) b;
	} else
		n = 0;

	return (int) n;
}

int load_profile(soul_t *ptr)
{
	int n, i, x;
	char ch, string[256], filename[(sizeof(ptr->name) + 4)];
	char filepath[(sizeof(filename) + 5)];
	char *tokk, *tptr;

	i = x = 0;

	strncpy(filepath, "save", 4);
	strncpy(filename, ptr->name, sizeof(filename));
	strncat(filename, fd_ext, 4);
	
	ntof(filename);

	n = mkdir(filepath, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	strncat(filepath, "/", 1);
	strncat(filepath, filename, (sizeof(filepath) - 5));
	strncpy(filepath, "save/", 5);

	if(n != 0)
	{
		fd = fopen(filepath, "r");
		while((ch = fgetc(fd)) != EOF) 
		{
			if(ch == '\n')
			{
				string[i] = '\0';
				i = -1;
				tokk = strtok(string, ":;");
				if(!strncmp(tokk, "name", 4))
				{
					tptr = strtok(NULL, ":;");
					strncpy(ptr->name, tptr, sizeof(ptr->name));

				} else if(!strncmp(tokk, "password", 8)) {
					tokk = strtok(NULL, ":;");
					ptr->pass = strtoul(tokk, &tptr, 10);
					if(PASSWD) {
						unsigned long n;
						char plaintext[64];
						printf(" Account found.\n  Password: ");
						fgets(plaintext, 64, stdin);
						n = hash((unsigned char *) plaintext);
						if(n != ptr->pass)
						{
							printf("\n BAD PASSWORD!\n");
							quit(ptr, NULL);
						}


					}

				} else if(!strncmp(tokk, "description", 11)) {
					tptr = strtok(NULL, ":;");
					strncpy(ptr->desc, tptr, sizeof(ptr->desc));

				} else if(!strncmp(tokk, "class", 5)) {
					tptr = strtok(NULL, ":;");
					ptr->attr.cls = tptr[0];

				} else if(!strncmp(tokk, "strength", 8)) {
					ptr->attr.strength = load_d(0);

				} else if(!strncmp(tokk, "wisdom", 6)) {
					ptr->attr.wisdom = load_d(0);

				} else if(!strncmp(tokk, "dexterity", 9)) {
					ptr->attr.dexterity = load_d(0);

				} else if(!strncmp(tokk, "gold", 4)) {
					ptr->gold = load_d(1);

				} else if(!strncmp(tokk, "luck", 4)) {
					ptr->luck = load_d(0);

				} else if(!strncmp(tokk, "type", 4)) {
					tptr = strtok(NULL, ":;");
					ptr->type = tptr[0];

				} else if(!strncmp(tokk, "range", 5)) {
					ptr->attr.range = load_d(0);

				} else if(!strncmp(tokk, "primary_lock", 12)) {
					ptr->attr.p_lck = load_d(0);

				} else if(!strncmp(tokk, "secondary_lock", 14)) {
					ptr->attr.s_lck = load_d(0);

				} else if(!strncmp(tokk, "tertiary_lock", 13)) {
					ptr->attr.t_lck = load_d(0);

				} else if(!strncmp(tokk, "bandaids", 8)) {
					ptr->bandaid.amount = load_d(0);

				}

				//else
					//printf("Token: %s\n", tokk);
			}
			string[i] = ch;
			i++;
		}
		/* Debugging the loading  */
		printf("\n   Name: %s\n", ptr->name);
		printf("   Description: %s\n", ptr->desc);
		printf("   Class: %c\n", ptr->attr.cls);
		printf("   Strength: %d\tWisdom: %d\tDexterity: %d\n", ptr->attr.strength, ptr->attr.wisdom, ptr->attr.dexterity);
		printf("   Gold: %.f\tLuck: %d\n", ptr->gold, ptr->luck);
		printf("   Type: %c\tRange: %d\n", ptr->type, ptr->attr.range);
		printf("   Primary Lock: %d\tSecondary Lock: %d\n", ptr->attr.p_lck, ptr->attr.s_lck);
		printf("   Tertiary Lock: %d\n", ptr->attr.t_lck);

		tools("pause", NULL);
		/*  */

		ptr->hp = ((ptr->attr.strength * 3) + 50);
		ptr->hp_c = ptr->hp;
		ptr->speed = (rand() % (sizeof(byte) - 10));

		fclose(fd);
	}

	return n;
}

void ntof(char *filename)
{
	int n;

	for(n = 0; n < (int)strlen(filename); n++)
		if(filename[n] == ' ')
			filename[n] = '_';
		else if(filename[n] == '\\')
			filename[n] = '_';
		else
			filename[n] = tolower(filename[n]);
}

unsigned long hash(unsigned char *plaintext)
{
	unsigned long hash = 5381;
	int c;

	while((c = *plaintext++))
		hash = ((hash << 5) + hash) + c;

	return hash;
}
