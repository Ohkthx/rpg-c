#include <stdio.h>
#include <string.h>

#include "headers/soul_create.h"
#include "headers/items.h"
#include "headers/menus.h"
#include "headers/combat.h"

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
	item_t *item = &ptr->bandaid;

	if(!strncmp(name, "bandaid", 7))
	{
		printf("\n  Amount to use [%d]: ", item->amount);
		scanf("%d", &amount);
		getchar();

		if(amount != 0 && item->amount != 0)
		{
			if(amount > item->amount)
				amount = item->amount;

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

			item->amount -= amount;
			printf("   Used %d %s(s) to get to %d health (%d overheal) (%d left).\n",
					amount, name, ptr->hp_c, oh, item->amount);
		} else
			printf("   Not enough bandaids to perform that action.");

	}
}


