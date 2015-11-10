#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

#include "headers/menus.h"
#include "headers/soul_create.h"
#include "headers/items.h"
#include "headers/save.h"


void tools(char *code, soul_t *ptr)
{
	char ch;
	const char *CLEAR_SCREE_ANSI = "\n\e[1;1H\e[2J\n";

	if(!strcmp(code, "clear"))
		write(STDOUT_FILENO, CLEAR_SCREE_ANSI, 12);	// Clears the screen.

	else if(!strcmp(code, "pause"))
	{
		//sleep(DELAY);		// Depreciated temporarily.
		printf("\n  Press [enter] to continue... ");
		fflush(stdout);
		while (((ch = getchar()) != '\n') && (ch != EOF));	// Until [enter] is pressed.
		write(STDOUT_FILENO, CLEAR_SCREE_ANSI, 12);		// Clear the screen.

	} else if(!strcmp(code, "menu")) 
	{
		printf("\n Press [enter] to continue, [m] for menu... ");	
		fputs("\0337", stdout);					// Hold spot in buffer/screen.
		fflush(stdout);
		//scanf("%c", &ch);
		ch = getchar();
		if(ch == '\n' || ch == EOF)				// If [enter] is pressed, clear.
			write(STDOUT_FILENO, CLEAR_SCREE_ANSI, 12);	// Clear.
		else if(ch == 'm')					// If [m] is pressed.
		{
			fflush(stdout);
			fputs("\0338", stdout);				// Go to the saved spot.
			printf("\r   |===-----=====:::::|  M  E   N  U  |:::::=====-----===|   \n");

			getchar(); // Required to eat '\n' for next statement.
			//while(((ch = getchar()) != '\n') && (ch != EOF));
			round_menu(ptr);
			write(STDOUT_FILENO, CLEAR_SCREE_ANSI, 12);	// Clear the screen
		} else
			printf("Something went wrong...\n");
	}
}


void menus(soul_t *ptr, byte code)
{
	int hp, hp_c, bar_amount;
	bar_amount = 10;

	char hp_string[bar_amount + 1];

	hp = ptr->hp;		// Easier to read; HP of the struct person being passed.
	hp_c = ptr->hp_c;	// Holds current hp.

	/*  Grab the current HP status bar */
	if(code == 0)
		code = 0;	
	else if(code == 1)
	{
		hpbar(ptr, hp_string, bar_amount);
		printf("   %c :: [" KRED "%s" RESET "]  %d/%d\trange: %d\t(%s, %s)\n", ptr->type, hp_string, hp_c, hp, ptr->stats.range_c, ptr->name, ptr->desc);
		printf(" #-----------------\\__|  P R E     R O U N D  |__/----------------#\n\n\n");
	} else if(code == 11)
	{
		hpbar(ptr, hp_string, bar_amount);
		printf("   %c :: ["KRED"%s"RESET"]  %d/%d\trange: %d\t(%s, %s)\n", ptr->type, hp_string, hp_c, hp, ptr->stats.range_c, ptr->name, ptr->desc);
	} else if(code == 2)
	{
		printf("\n #_________________/--|  P O S T   R O U N D  |--\\________________#\n");
		hpbar(ptr, hp_string, bar_amount);
		printf("   %c :: ["KRED"%s"RESET"]  %d/%d\trange: %d\t(%s, %s)\n", ptr->type, hp_string, hp_c, hp, ptr->stats.range_c, ptr->name, ptr->desc);
	} else if(code == 3)
	{
		printf(" #________________/--|  T H I S   R O U N D  |--\\________________#\n");
		hpbar(ptr, hp_string, bar_amount);
		printf("   %c :: ["KRED"%s"RESET"]  %d/%d\t(%s, %s)\n", ptr->type, hp_string, hp_c, hp, ptr->name, ptr->desc);
	} else if(code == 33)
	{
		hpbar(ptr, hp_string, bar_amount);
		printf("   %c :: ["KRED"%s"RESET"]  %d/%d\t(%s, %s)\n", ptr->type, hp_string, hp_c, hp, ptr->name, ptr->desc);
		printf("\n #----------------\\__|  T H I S   R O U N D  |__/----------------#\n\n\n");
	}
		
}


void hpbar(soul_t *ptr, char *string, int bar_amount)
{	// RESPONSIBLE FOR CREATING THE HEALTH BAR IN menu() FUNCTION
        int bar, i, n;
        bar = ptr->hp / bar_amount;	// The amount of HP per bar (#)
        i = bar; n = 0;

        for(n = 0; n < bar_amount; n++)
        {
                if(bar <= ptr->hp_c)
                {
                        string[n] = '#';	// Create a bar.
                        bar += i;
                } else
                        string[n] = ' ';	// Fill in empty space with blanks.
        }
        string[n] = '\0';	// Terminate the array with a null char.
}


void bprintf(buffer_t *pbuf, char *fmt, ...)
{
	/*  DEPRECIATED TERMPORARILY;
	 *   Will be used to have a 'Queue' for the battle log. Reminder: Circular Buffer */

	/*  vsnprintf, prints assigns the *fmt into the buff, to be printed by printf */
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(pbuf->buff, MAXCHAR, fmt, ap);
	va_end(ap);

	printf("<< %s", pbuf->buff);          // Only prints if DEBUG is set to 2.
	//printf("SIZE: %d\n", (int)strlen(pbuf->buff));
}


void round_menu(soul_t *ptr)
{
	char ch;

	//fputs("\0337", stdout);	
	printf("\n  s) Save Information.\n  h) Bandage [%d]\n  q) Quit (menu)\n\n Option: ", ptr->bandaid.amount);
	//fputs("\0337", stdout);
	ch = getchar(); // Required to eat '\n' for next statement.

	if(ch == 's')		// Save the character.
		save(ptr);
	else if(ch == 'h')	// heal the character/
		item_use(ptr, "bandaid");
	else if(ch == 'q')	// quit this menu.
		printf("Leaving menu...\n");
	getchar();
	tools("pause", NULL);

}


void stat_print(struct soul * ptr)
{
	item_t *item = &ptr->bandaid;
	char string[21], pclass[8];

	hpbar(ptr, string, 20);

	switch(ptr->stats.cls)
	{
		case 'a':
			strncpy(pclass, "Archer", 8);
			break;
		case 'm':
			strncpy(pclass, "Mage", 8);
			break;
		case 'w':
			strncpy(pclass, "Warrior", 8);
			break;
		default:
			printf(" An error occured in stat_print!\n");
			exit(0);
	}

	tools("clear", NULL);
	//printf(" +--------------------------------------+\n");
	printf(" +--[   D E T A I L S   ]\n");
	printf(" |   *  %s,\tthe %s\n", ptr->name, pclass);
	printf(" |\t %s\n", ptr->desc);
	printf(" | \n");
	printf(" +--[   I T E M S   ]\n");
	printf(" |    *  Gold    : " BYEL "%.2f\n" RESET, ptr->gold);
	printf(" |    *  Bandaids: " BRED "%d\n" RESET, item->amount);
	printf(" | \n");
	printf(" +--[   A T T R I B U T E S   ]\n");
	printf(" |    *  Strength : " KRED "%d" RESET "\tWisdom: " BCYN "%d\n" RESET, ptr->stats.strength, ptr->stats.wisdom);
	printf(" |    *  Dexterity: " BYEL "%d" RESET "\n", ptr->stats.dexterity);
        printf(" |    *  Luck     : " BGRN "%d" RESET "\tRange: " KGRN "%d\n" RESET, ptr->luck, ptr->stats.range);
	printf(" | \n");
	printf(" +--[   S T A T U S ]\n");
	printf(" |    [" KRED "%s" RESET "]\n", string);
	printf(" |    *  Maximum Health: " KRED "%d\n" RESET, ptr->hp);
	printf(" |    *  Current Health: " BRED "%d\n" RESET, ptr->hp_c);
	printf(" | \n");
	printf(" +--------------------------------------+\n");


	tools("pause", NULL);

}


void quit(soul_t *ptr, node_t *head)
{
	list_destroy(head);
	free(ptr);
	exit(0);
}


void readme_read(void)
{
	FILE *rd;
	char string[256], ch;
	int n, nl, s_flag;

	n = nl = s_flag = 0;

	tools("clear", NULL);

	rd = fopen("README", "r");
	while((ch = fgetc(rd)) != EOF)
	{
		string[n] = ch;
		if(string[n] == '\n') {
			string[n] = '\0';
			n = -1;

			if(s_flag == 1) {
				printf("%s\r", string);
				nl++;
				if(nl > 7) {
					//fputs("\0337", stdout);
					getchar();
					//fputs("\0338", stdout);
				} else
					printf("\n");
			}
		}
		if((s_flag == 0) && (string[n] == '-') && (string[n - 1] == ';')) {
			if(n == 1)
				s_flag = 1;
		} else if((s_flag == 1) && (string[n] == '-') && (string[n - 1] == ';')) {
			if(n == 1)
				s_flag = 0;
		}

		n++;
	}
	
	fclose(rd);
	while((ch = getchar()) != 'c')
		printf(" Enter ['c' + enter] to continue: ");
}
