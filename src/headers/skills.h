#ifndef _SKILLS_HEADER_H
#define _SKILLS_HEADER_H

typedef struct skill
{
	float val;
	char name[16];

} skill_t;

typedef struct container
{
	struct skill archery;
	struct skill fencing;
	struct skill magery;
	struct skill swordsmanship;
	struct skill macefighting;
} container_t;


int skill_check(skill_t *skill);

#endif
