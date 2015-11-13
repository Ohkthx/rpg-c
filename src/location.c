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

	wd = fopen("data/ecosphere.in", "r");		// Open the world data.
	while((ch = fgetc(wd)) != EOF)
	{
		if(ch == '\n')					// On newline...
		{
			string[n] = '\0';			//  terminate the string.
			n = -1;					//  set n = 0 (-1 will be ++)

			if(strlen(string) > 0)			// If '\n\n' caught, don't strtok.
				tokk = strtok(string, ":;");	// tokk will be the token.
			
			if(!strncmp(tokk, "dungeon", 7))	// If token is dungeon...
			{
				tokk = strtok(NULL, ":;");
				if(!strncmp(tokk, "name", 4)) {		// if second token is name...
					tokk = strtok(NULL, ":;");
					if(i == 0)
					{
						amt = strtol(tokk, &ptr, 10);	// Amount of room names. *See the actual first line of the world data.
						amt = (rand() % amt) + 1;	// Get the random room name number.
						i++;
					} else {
						x++;
						if(x == amt) 	// if x is the equivalent to the rand()...
							strncpy(c->name, tokk, 24);	// Set the room name to this one..
					}
				} else if(!strncmp(tokk, "description", 11))	// If first token is description.
				{
					tokk = strtok(NULL, ":;");
					if(i == 1) {
						amt = strtol(tokk, &ptr, 10);	// Get the amount of descriptions
						amt = (rand() % amt) + 1;	// Get a random description identity.
						x = 0;
						i++;
					} else {
						x++;
						if(x == amt)			// If x is the rand()...
							strncpy(c->d, tokk, 128);	// Set the description to this one.
					}
				}   
			}
		}

		string[n] = ch;
		n++;
	}	
	fclose(wd);	// Close the file.
}


void stage(struct node *head, struct soul *ptr)
{
	struct node *c = head;	// Hold original
	ptr->item = &ptr->objs.bandaid;

	int id_hold = c-> id;

	while(1) 
	{
		if(((rand() % 100) < 30) && (id_hold != c->id) && (c->id != 0))	// 3 in 10 chance
		{	
			char type;			// Will pass the mob type.
			int lvl, tp;			// Passes mobs level, *should implement scaling 
							//  tp is the numeric value of type.
			lvl = (rand() % 2) + 1;		// Between 1 - 2.
			tp = (rand() % 3);
			switch(tp)
			{
				case (0):
					type = 'a';	// Archer
					break;
				case (1):
					type = 'm';	// Mage
					break;
				case (2):
					type = 'w';	// Warrior
					break;
			}

			tools("clear", NULL);
			struct soul *npc = malloc(sizeof(soul_t));		// Allocate storage
			soul_create(npc, "Training Dummy", "WAF", type, lvl);	// Create monster.
			printf("   You have been approached by a \n   > [ %s, %s ]\n    while traveling!\n", npc->name, npc->desc);
			tools("pause", NULL);
			round_start(ptr, npc);					// Start the round.
			free(npc);						// Free up the allocated storage.
		}

		char ch;		// Used by getchar in passed to switch-case.
		char hp_string[10 + 1];		// String that will contain health bar (10 + \0)
		hpbar(ptr, hp_string, 10);	// Create the hp bar.
		
		ptr->hp = ((ptr->stats.strength * 3) + 50);

		if(id_hold != c->id)
			id_hold = c->id;
	
		tools("clear", NULL);	// Sends the ANSI Clear.
		printf(" ---|  %s |---\n ---| %s |---  \n\n", c->name, c->d);	// Location Data.
		printf(" -| %s, %s |- \n", ptr->name, ptr->desc);	// Name & Description
		printf(" -| Health: [" KRED "%s" RESET "]   %d/%d \n\n", hp_string, ptr->hp_c, ptr->hp);
	
		printf("- - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n\n");
	
		printf("  I) Individual\t\tS) Save\n");			// i = profile, s = save
		printf("  C) Combat\t\tH) Bandage [%d] \n", ptr->item->amount);	// c = combat, h = heal
		printf("  Q) Quit\t\t");				// q = quit.

		if(c->id == 0)
			printf("R) Changelog\n");
		else
			printf("\n");

		printf("\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");

		if(c->id == 0)
			printf("  X) Store\t\t");
		else if(c->prev != NULL)
			printf("  L) Last: [%s]\t", c->prev->name);
	
		if(c->next != NULL)					// List next location.
			printf("N) Next: [%s]\n", c->next->name);
	
		//if(c->prev != NULL)					// If away from main menu,
		//	printf("L) Last: [%s]\n", c->prev->name);	//  list the previous place.
		//else
		//	printf("\n");

		printf(" - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
	
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
				}		// Otherwise it will fall-thru to the default.
			case 'x':
				if(c->id == 0) {
					item_store(&ptr->objs, &ptr->gold);
					break;
				}
			default:
				printf(" Bad Option!\n");
				tools("pause", NULL);
		}
	}
}
