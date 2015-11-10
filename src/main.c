#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>

#include "headers/combat.h"
#include "headers/menus.h"
#include "headers/soul_create.h"
#include "headers/save.h"
#include "headers/items.h"
#include "headers/location.h"


int main(void)
{
	srand(time(NULL));

	struct soul *ptr = malloc(sizeof(soul_t));
	soul_create(ptr, NULL, NULL, 0, 0);	// Create the player

	struct node *head = malloc(sizeof(node_t));
	strncpy(head->name, "Main Menu", 24);
	strncpy(head->d, "Welcome to the game! This is the main menu :D", 128);
	head->id = 0;
	head->prev = NULL;
	head->next = NULL;

	location_create(head, "Dungeon Entrance", "Welcome to the start of the dungeon!");

	item_load(&ptr->objs);

	while(1)
		stage(head, ptr);

	return 0;
}

