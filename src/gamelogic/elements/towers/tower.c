#include "gamelogic/elements/towers/tower.h"
#include <stdio.h>
#include <stdlib.h>

void tower_init(Tower *tower, const TowerType *type, float x, float y) {
  tower->towerSymbol = type->towerSymbol;
  tower->life = type->life;
  tower->damages = type->damage;
  tower->level = type->level;
  tower->range = type->range;
  tower->cost = type->cost;
  tower->targeted = 0;
  tower->position.x = x;
  tower->position.y = y;
  tower->enemy_target_id = 0;
  tower->lastFiredTime = 0;
  tower->pastTime = 0;
  tower->type = type;
}

char tower_get_symbol(Tower *tower) {
  return tower->towerSymbol;
}

Position *tower_get_position(Tower *tower) {
  return &tower->position;
}

int tower_get_life(Tower *tower) {
  return tower->life;
}

int tower_get_level(Tower *tower) {
  return tower->level;
}

int tower_get_range(Tower *tower) {
  return tower->range;
}

int tower_get_cost(Tower *tower) {
  return tower->cost;
}

int tower_is_targeted(Tower *tower) {
  return tower->targeted;
}

void tower_set_targeted(Tower *tower, int targeted) {
  tower->targeted = targeted;
}

void set_target(Tower *tower, int enemy_target_id) {
  tower->enemy_target_id = enemy_target_id;
}

int calculate_distance(Tower *tower, Enemy *enemy) {
  float x = tower->position.x - enemy->position.x;
  float y = tower->position.y - enemy->position.y;
  float distance = (x * x + y * y) * (1 / 2);
  return distance;
}

void upgrade_tower(Tower *tower) {
  tower->level++;
  tower->damages += 50;
}
