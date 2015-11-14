#include <stdio.h>

#include "headers/skills.h"
#include "headers/menus.h"
#include "headers/soul_create.h"


int skill_check(skill_t *skill)
{
	if(skill->val == 120.0)
		return 0;	// Skill is too high, return false for not able to gain.

	else if(skill->val > 115.0)
		printf("115.1 -> 119.9\n");

	else if(skill->val > 110.0)
		printf("110.1 -> 115.0\n");

	else if(skill->val > 105.0)
		printf("105.1 -> 110.0\n");

	else if(skill->val > 100.0)
		printf("100.1 -> 105.0\n");

	else if(skill->val > 90.0)
		printf("90.1 -> 100.0\n");

	else if(skill->val > 80.0)
		printf("80.1 -> 90.0\n");

	else if(skill->val > 70.0)
		printf("70.1 -> 80.0\n");

	else if(skill->val > 60.0)
		printf("60.1 -> 70.0\n");

	else if(skill->val > 50.0)
		printf("50.1 -> 60.0\n");

	else if(skill->val > 40.0)
		printf("40.1 -> 50.0\n");

	else if(skill->val > 30.0)
		printf("30.1 -> 40.0\n");
	else
		printf("0.0 -> 30.0\n");

	return 1;		// True as in skill able to be gained.
}
