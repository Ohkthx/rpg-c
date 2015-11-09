#include <stdio.h>
#include <stdlib.h>     /*  rand() */
#include <time.h>       /*  srand seeding. */
#include <string.h>	/*  strcspn */
#include <ctype.h>	/*  tolower */

#include "headers/soul_create.h"
#include "headers/items.h"
#include "headers/menus.h"      /*   tools function */
#include "headers/save.h"


int soul_create(soul_t *creature, char *name, char *desc, char p_class, int lvl)
{
	tools("clear", NULL);
	//unsigned long pass;
	char plaintext[64];

	if(name == NULL)
	{
		printf(" Name: ");
		fgets(creature->name, sizeof(creature->name), stdin);	// set p->name to input data.
		creature->name[strcspn(creature->name, "\n")] = 0;	// remove trailing '\n'
		if(!file_exists(creature->name))
		{
			if(PASSWD) {
				printf(" Password: ");
				fgets(plaintext, 64, stdin);
				creature->pass = hash((unsigned char *) plaintext);
			}

			printf(" Description: ");
			fgets(creature->desc, sizeof(creature->desc), stdin);	//set p->desc to input data.
			creature->desc[strcspn(creature->desc, "\n")] = 0;	// removetrailing '\n'

			creature->speed = (rand() % (sizeof(byte) - 10));	// Generate player speed
			creature->luck = 25;		// Set player's initial luck.
			creature->type = 'p';		// Set player's type. ( p = player, m = mob )
			creature->gold = 500.00;	// Set base gold value player owns.

			class_create(creature, 0, 1);	// Call on selectings the player's class.

			printf("\n Player name: %s\n Description: %s\n  Health: %d\n  Damage: %d\n  Speed: %d\n",
					creature->name, creature->desc, creature->hp, creature->dmg, creature->speed);

			item_init(&creature->bandaid, "bandaids",  10);

			save(creature);
			getchar();
			tools("pause", NULL);
		} else
			load(creature);	
	} else
	{
		strncpy(creature->name, name, sizeof(creature->name));	// Changed from strcpy (safer now)
		strncpy(creature->desc, desc, sizeof(creature->desc));	// Same as above.
		creature->speed = (rand() % (sizeof(byte) - 20));	// Set speed.
		creature->type = 'm';				// Set type to mob ( m = mob )
		creature->gold = (250.00 * ((float)lvl / 2));				// Gold being held.

		class_create(creature, p_class, lvl);
	}

	return 0;
}

int class_create(soul_t *p, char p_class, int lvl)
{
	char opt;	// "Option" for switch statement.
	byte lpctr;	// While variable to be changed to break.

	lpctr = 0;	// 1 will break the while loop.
	opt = p_class;

	tools("clear", NULL);

	while(!lpctr)
	{	
		if(opt != 'a' && opt != 'm' && opt != 'w')
		{
			fflush(stdout);
			printf("[%s, %s]\n", p->name, p->desc);
			printf(" Choose a class: \n\n");
			printf("  [A]rcher\n  [M]age\n  [W]arrior\n\n Option [a/m/w]: ");
			opt = getchar();
			opt = tolower(opt);
		}

		switch(opt)
		{
			case 'a':	// Archer
				p->attr.dexterity = 13 * lvl;
				p->attr.wisdom = 6 * lvl;
				p->attr.strength = 6 * lvl;
				p->attr.range = 2;
				p->attr.cls = 'a';	// Class = Archer
				p->attr.p = 'd';	// Primary stat (dexterity)
				p->attr.s = 's';	// Secondary stat (strength)
				p->attr.t = 'w';	// Tertiary stat (wisdom)

				//p->attr.pri = &p->attr.dexterity;
				//p->attr.sec = &p->attr.strength;	// Used for stat_gain
				//p->attr.ter = &p->attr.wisdom;

				lpctr = 1;		// To break out of while.
				break;

			case 'm':	// Mage
				p->attr.dexterity = 5 * lvl;
				p->attr.wisdom = 13 * lvl;
				p->attr.strength = 7 * lvl;
				p->attr.range = 1;
				p->attr.cls = 'm';	// Class = Mage
				p->attr.p = 'w';	// Primary stat (wisdom)
				p->attr.s = 'd';	// Secondary stat (dexterity)
				p->attr.t = 's';	// Tertiary stat (strength)

				//p->attr.pri = &p->attr.wisdom;
				//p->attr.sec = &p->attr.dexterity;	// Used for stat_gain
				//p->attr.ter = &p->attr.strength;

				lpctr = 1;		// To break out of while.
				break;

			case 'w':	// Warrior
				p->attr.dexterity = 7 * lvl;
				p->attr.wisdom = 3 * lvl;
				p->attr.strength = 15 * lvl;
				p->attr.range = 0;
				p->attr.cls = 'w';	// Class = Warrior
				p->attr.p = 's';	// Primary stat (strength)
				p->attr.s = 'd';	// Secondary stat (dexterity)
				p->attr.t = 'w';	// Tertiary stat (wisdom)

				//p->attr.pri = &p->attr.strength;
				//p->attr.sec = &p->attr.dexterity;	// Used for stat_gain
				//p->attr.ter = &p->attr.wisdom;

				lpctr = 1;		// To break out of while.
				break;

			default:
				printf("An error occured: [%c] is not a valid option.\n", opt);
				tools("pause", NULL);
				break;
		}

		p->hp = ((p->attr.strength * 3) + 50);
		p->hp_c = p->hp;
		p->attr.p_lck = 0;	// Set primary skill unlocked (allows stat gain.)
		p->attr.s_lck = 0;	// Set secondary skill unlocked.
		p->attr.t_lck = 0;	// Set tertiary skill unlocked.
	}
	
	tools("clear", NULL);
	return 0;
}
