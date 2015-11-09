#ifndef _COMBAT_HEADER
#define _COMBAT_HEADER

#include "soul_create.h"
#include "menus.h"

int  combat(soul_t *ptr);
int  round_start(soul_t *player, soul_t *npc);
int  damage_calc(soul_t *ptr);
int  defense_calc(soul_t *ptr);
int  range_count(soul_t *a_, soul_t *d_);

void attack(soul_t *attacker, soul_t *defender);
void round_post(soul_t *player, soul_t *npc, byte result);
int  stat_check(soul_t *ptr, int special);
void stat_gain(soul_t *ptr);

#endif
