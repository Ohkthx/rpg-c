#include <stdio.h>

#include "headers/skills.h"
#include "headers/menus.h"
#include "headers/soul_create.h"


int skill_check(skill_t *skill)
{
	if(skill->val == 120.0)
		return 0;

	else if(skill->val > 115.0)
		printf("115.1 -> 119.9\n");

	else if(skill->val > 110.0)
		printf("115.1 -> 119.9\n");

	else if(skill->val > 105.0)
		printf("115.1 -> 119.9\n");

	else if(skill->val > 100.0)
		printf("115.1 -> 119.9\n");

	else if(skill->val > 90.0)
		printf("115.1 -> 119.9\n");

	else if(skill->val > 80.0)
		printf("115.1 -> 119.9\n");

	else if(skill->val > 70.0)
		printf("115.1 -> 119.9\n");

	else if(skill->val > 60.0)
		printf("115.1 -> 119.9\n");

	else if(skill->val > 50.0)
		printf("115.1 -> 119.9\n");

	else if(skill->val > 40.0)
		printf("115.1 -> 119.9\n");

	else if(skill->val > 30.0)
		printf("115.1 -> 119.9\n");

	return 1;
}
