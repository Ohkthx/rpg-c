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
			printf(" Primary Skill:\n   %s, %.1f \n", creature->skill->name, creature->skill->val);

			item_init(&creature->bandaid, "bandaids",  10);

			save(creature);
			getchar();
			tools("pause", NULL);
		} else
			load_profile(creature);	
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
				p->stats.dexterity = 13 * lvl;
				p->stats.wisdom = 6 * lvl;
				p->stats.strength = 6 * lvl;
				p->stats.range = 2;
				p->stats.cls = 'a';	// Class = Archer
				p->stats.p = 'd';	// Primary stat (dexterity)
				p->stats.s = 's';	// Secondary stat (strength)
				p->stats.t = 'w';	// Tertiary stat (wisdom)

				//p->attr.pri = &p->attr.dexterity;
				//p->attr.sec = &p->attr.strength;	// Used for stat_gain
				//p->attr.ter = &p->attr.wisdom;
				
				p->skill = &p->bucket.archery;
				strncpy(p->skill->name, "Archery", 7);
				p->skill->val = 50.0;
				lpctr = 1;		// To break out of while.
				break;

			case 'm':	// Mage
				p->stats.dexterity = 5 * lvl;
				p->stats.wisdom = 13 * lvl;
				p->stats.strength = 7 * lvl;
				p->stats.range = 1;
				p->stats.cls = 'm';	// Class = Mage
				p->stats.p = 'w';	// Primary stat (wisdom)
				p->stats.s = 'd';	// Secondary stat (dexterity)
				p->stats.t = 's';	// Tertiary stat (strength)

				//p->attr.pri = &p->attr.wisdom;
				//p->attr.sec = &p->attr.dexterity;	// Used for stat_gain
				//p->attr.ter = &p->attr.strength;

				p->skill = &p->bucket.magery;
				strncpy(p->skill->name, "Magery", 6);
				p->skill->val = 50.0;
				lpctr = 1;		// To break out of while.
				break;

			case 'w':	// Warrior
				p->stats.dexterity = 7 * lvl;
				p->stats.wisdom = 3 * lvl;
				p->stats.strength = 15 * lvl;
				p->stats.range = 0;
				p->stats.cls = 'w';	// Class = Warrior
				p->stats.p = 's';	// Primary stat (strength)
				p->stats.s = 'd';	// Secondary stat (dexterity)
				p->stats.t = 'w';	// Tertiary stat (wisdom)

				//p->attr.pri = &p->attr.strength;
				//p->attr.sec = &p->attr.dexterity;	// Used for stat_gain
				//p->attr.ter = &p->attr.wisdom;

				p->skill = &p->bucket.fencing;
				strncpy(p->skill->name, "Fencing", 7);
				p->skill->val = 50.0;
				lpctr = 1;		// To break out of while.
				break;

			default:
				printf("An error occured: [%c] is not a valid option.\n", opt);
				tools("pause", NULL);
				break;
		}

		p->hp = ((p->stats.strength * 3) + 50);
		p->hp_c = p->hp;
		p->stats.p_lck = 0;	// Set primary skill unlocked (allows stat gain.)
		p->stats.s_lck = 0;	// Set secondary skill unlocked.
		p->stats.t_lck = 0;	// Set tertiary skill unlocked.
	}
	
	tools("clear", NULL);
	return 0;
}
