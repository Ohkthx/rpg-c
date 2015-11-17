#ifndef ORGA_CREATE_INCLUDED
#define ORGA_CREATE_INCLUDED	1

#include "skills.h"


typedef struct item   
{
	char name[16];
	int id;
        int amount;
	int stock;
        float cost;

} item_t; 

typedef struct objects
{
	struct item null;
	struct item bandaid;
	struct item arrow;
	struct item reagent;

} objects_t;

//  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //  //

typedef struct soul 
{
        char name[24];  char desc[64];
	unsigned long pass;
        int hp;         int hp_c;
        int dmg;        int def;
	int o_mod;	int d_mod;	// Both unused.
        float gold;
        byte luck;      float speed;	// Speed is normally byte_t
        byte type;

 	stats_t     stats;	// Player's stats
	item_t      *item;	// "Current" item.
	item_t 	    *consumable;
	skill_t     *skill;	// Link to primary skill.
	objects_t   objs;	// Holds items.
	container_t bucket;	// Holds the skills.
	struct soul *o;		// Opposition of the soul (combat);

} soul_t; 


int soul_create(struct soul *creature, char *name, char *desc, char p_class, int lvl);
int class_create(struct soul *p, char p_class, int lvl);

#endif
