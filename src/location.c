#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "headers/location.h"
#include "headers/menus.h"
#include "headers/save.h"
#include "headers/combat.h"
#include "headers/items.h"


void list_print(struct node *head)
{
	struct node *current = head;

	while(current != NULL)
	{
		printf("Name: %s; ID: %d\n", current->name, current->id);
		current = current->next;
	}

}

void list_push(struct node *head)
{
	struct node *current = head;

	while(current->next != NULL)
	{
		current = current->next;
	}

	current->next       = malloc(sizeof(node_t));
	current->next->id   = current->id + 1;
	current->next->next = NULL;
}

void list_destroy( struct node *head)
{
	struct node *f;
	while(head)
	{
		f = head;		// Hold the address of previous
		head = head->next;	// Move on!
		free(f);		// DESTRUCTION!
	}

}

void location_create(struct node *head, char *name, char *description)
{
	struct node *c = head;		// (c)urrent spot is the head of the linked list.

	while(c->next != NULL) {	// Go to the end of the nodes.
		c = c->next;
	}

	c->next       = malloc(sizeof(node_t));	// Allocate memory.
	c->next->id   = c->id + 1;		// Give a unique ID (simple.)
	c->next->next = NULL;			// Null next location.
	c->next->prev = c;			// Assign previous location ptr.

	if(name == NULL)
		world_grab(c->next);
	else {
		strncpy(c->next->name, name, 24);
		strncpy(c->next->d, description, 128);	// Assign description.
	}

}

void world_grab(struct node *head)
{
	struct node *c = head;
	FILE *wd;
	char string[256];
	char ch, *tokk, *ptr;
	int n, i;
	long amt, x;
	amt = n = i = x = 0;

	// echophere.ru:  dungeon:name:NAME;
	// 		  dungeon:description:DESCRIPTION;

	wd = fopen("ecosphere.ru", "r");
	while((ch = fgetc(wd)) != EOF)
	{
		if(ch == '\n')
		{
			string[n] = '\0';
			n = -1;

			if(strlen(string) > 0)
				tokk = strtok(string, ":;");
			
			if(!strncmp(tokk, "dungeon", 7))
			{
				tokk = strtok(NULL, ":;");
				if(!strncmp(tokk, "name", 4)) {
					tokk = strtok(NULL, ":;");
					if(i == 0)
					{
						amt = strtol(tokk, &ptr, 10);
						amt = (rand() % amt) + 1;
						i++;
					} else {
						x++;
						if(x == amt) 
							strncpy(c->name, tokk, 24);
					}
				} else if(!strncmp(tokk, "description", 11))
				{
					tokk = strtok(NULL, ":;");
					if(i == 1) {
						amt = strtol(tokk, &ptr, 10);
						amt = (rand() % amt) + 1;
						x = 0;
						i++;
					} else {
						x++;
						if(x == amt)
							strncpy(c->d, tokk, 128);
					}
				}   
			}
		}

		string[n] = ch;
		n++;
	}
	fclose(wd);
}


void stage(struct node *head, struct soul *ptr)
{
	struct node *c = head;	// Hold original
	//struct item *i = &ptr->bandaid;

	while(1) 
	{
		char ch;		// Used by getchar in passed to switch-case.
		char hp_string[10 + 1];		// String that will contain health bar (10 + \0)
		hpbar(ptr, hp_string, 10);	// Create the hp bar.
		
		ptr->hp = ((ptr->attr.strength * 3) + 50);
	
		tools("clear", NULL);	// Sends the ANSI Clear.
		printf(" [  %s ]\n [ %d ] %s  \n\n", c->name, c->id, c->d);	// Location Data.
		printf("  [ %s, %s ] \n", ptr->name, ptr->desc);	// Name & Description
		printf("    Health: [" KRED "%s" RESET "]   %d/%d \n\n", hp_string, ptr->hp_c, ptr->hp);
	
		printf(" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n");
	
		printf("  I) Individual\t\tS) Save\n");			// i = profile, s = save
		printf("  C) Combat\t\tH) Bandage [%d] \n", ptr->bandaid.amount);	// c = combat, h = heal
		printf("  Q) Quit\t\t");				// q = quit.

		if(c->id == 0)
			printf("R) Changelog\n");
		else
			printf("\n");
	
		if(c->next != NULL)					// List next location.
			printf("  N) Next: [%s]\t", c->next->name);
	
		if(c->prev != NULL)					// If away from main menu,
			printf("L) Last: [%s]", c->prev->name);	//  list the previous place.
	
		printf("\n\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
	
		printf("\n Option: ");
	
		ch = getchar();
		getchar();		// Catch '\n' for a future "pause"
		ch = tolower(ch);	// Catch in case of caps lock.
	
		switch(ch)
		{
			case 'i':			// Inventory
				stat_print(ptr);	// Print player stats.
				break;
			case 's':
				save(ptr);		// Save player data.
				tools("pause", NULL);
				break;
			case 'h':
				item_use(ptr, "bandaid");	// Use bandages to heal.
				tools("pause", NULL);
				break;
			case 'c':
				combat(ptr);	// Go to combat then select monster's difficulty.
				break;
			case 'q':			// Quit the game.
				tools("clear", NULL);	// Clear the screen and then save (print text)
				save(ptr);		// ** ADD THIS TO quit() IN FUTURE.
				printf("\n   Thanks for playing!\n\n");
				quit(ptr, head);	// Repsonsible for freeing memory of structs.
			case 'r':
				readme_read();
				break;
			case 'n':
				c = c->next;		// Go to next link in list.
				location_create(c, NULL, NULL);	// Append a new location.
				break;
			case 'l':
				if(c->prev != NULL) {	// Block 'p' (causes seg_fault) due to going to
					c = c->prev;	//  a null location.
					break;
				}			// Otherwise it will fall-thru to the default.
			default:
				printf(" Bad Option!\n");
				tools("pause", NULL);
		}
	}
}