#ifndef ORGA_CREATE_INCLUDED
#define ORGA_CREATE_INCLUDED


#include "skills.h"

typedef unsigned char byte;

typedef struct item   
{
	char name[16];
        int amount;	int stock;
        int heal;
        float cost;

} item_t; 

typedef struct _attr_t
{
	int range;	int range_c;
        byte wisdom;    byte dexterity;
        byte strength;  byte cls;
	char p;		char p_lck;
	char s;		char s_lck;
	char t;		char t_lck;
	byte *pri, *sec, *ter;

} attr_t; 

typedef struct soul 
{
        char name[24];  char desc[64];
	unsigned long pass;
        int hp;         int hp_c;
        int dmg;        int def;
	int o_mod;	int d_mod;
        float gold;
        byte luck;      byte speed;
        byte type;

 	attr_t attr;
	item_t bandaid;
	skill_t *skill;		// Link to primary skill.
	container_t bucket;	// Holds the skills.

} soul_t; 


int soul_create(struct soul *creature, char *name, char *desc, char p_class, int lvl);
int class_create(struct soul *p, char p_class, int lvl);

#endif
