#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "headers/soul_create.h"
#include "headers/items.h"
#include "headers/menus.h"
#include "headers/combat.h"

void item_load(objects_t *objs)
{
	struct item *item;
	FILE *fd;
	char ch, string[128], *tokk, *ptr;
	long id;
	int n;

	n = id = 0;

	fd = fopen("data/items.in", "r");
	while((ch = fgetc(fd)) != EOF)
	{
		string[n] = ch;

		if(ch == '\n')
		{
			string[n] = '\0';
			n = -1;

			if(strlen(string) > 0)
				tokk = strtok(string, ":;");

			id = strtol(tokk, &ptr, 10);

			if(id == 1)
				item = &objs->bandaid;
			else if(id == 2)
				item = &objs->arrow;
			else if(id == 3)
				item = &objs->reagent;

			if(id != 0 && id < 4)
			{
				item->id = id;

				tokk = strtok(NULL, ":;");
				strncpy(item->name, tokk, 7);

				tokk = strtok(NULL, ":;");
				item->stock = strtol(tokk, &ptr, 10);

				tokk = strtok(NULL, ":;");
				item->cost = strtof(tokk, &ptr);
			}
		}

		n++;
	}

	fclose(fd);
}

void item_init(item_t *item, char *name, int amount)
{
	strncpy(item->name, name, sizeof(item->name));
	item->amount = amount;
	item->cost   = 15.00;
}


void item_use(soul_t *ptr, char *name)
{
	int amount;
	int oh;

	if(!strncmp(name, "bandaid", 7))
	{
		ptr->item = &ptr->objs.bandaid;
		printf("\n  Amount to use [%d]: ", ptr->item->amount);
		scanf("%d", &amount);
		getchar();

		if(amount != 0 && ptr->item->amount != 0)
		{
			if(amount > ptr->item->amount)
				amount = ptr->item->amount;

			int hp_tmp;
			hp_tmp = ptr->hp;
			oh = ((((hp_tmp / 6) * amount) + ptr->hp_c) - ptr->hp);

			ptr->hp_c = (((hp_tmp / 6) * amount) + ptr->hp_c);
			if(ptr->hp_c > ptr->hp)
				ptr->hp_c = ptr->hp;
			else
				oh = 0;

			if(stat_check(ptr, 1)) {
				printf("   [" BRED "+" RESET "]  Strength increased from %d to ", ptr->stats.strength);
				ptr->stats.strength += 1;
				printf("%d.\n", ptr->stats.strength);
			}

			ptr->item->amount -= amount;
			printf("   Used %d %s(s) to get to %d health (%d overheal) (%d left).\n",
					amount, name, ptr->hp_c, oh, ptr->item->amount);
		} else
			printf("   Not enough bandaids to perform that action.");

	}
}


