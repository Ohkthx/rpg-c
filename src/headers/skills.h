#ifndef _SKILLS_HEADER_H
#define _SKILLS_HEADER_H

typedef unsigned char byte;

//  //  //  //  //  //  //  //  //  //  //  //  //  //

typedef struct stats
{
	int range;	int range_c;
        byte wisdom;    byte dexterity;
        byte strength;  byte cls;
	char p;		char p_lck;
	char s;		char s_lck;
	char t;		char t_lck;
	byte *pri;	byte *sec;
	byte *ter;

} stats_t; 

//  //  //  //  //  //  //  //  //  //  //  //  //  //

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

//  //  //  //  //  //  //  //  //  //  //  //  //  //

int skill_check(skill_t *skill);

#endif
