#include "gamelogic/elements/enemies/enemy.h"

void enemy_init(Enemy *enemy, const EnemyType *type, int x, int y, int id) {
  enemy->id = id;
  enemy->isDead = 0;
  enemy->actHP = type->totHP;
  enemy->hiddenHP = type->totHP;
  position_init(&enemy->position, x, y);
  position_init(&enemy->deathPosition, x, y);
  enemy->type = type;
}

void enemy_set_position(Enemy *enemy, int x, int y) {
  position_setX(&enemy->position, x);
  position_setY(&enemy->position, y);
}

int enemy_get_id(Enemy *enemy) {
  return enemy->id;
}

Position *enemy_get_position(Enemy *enemy) {
  return &enemy->position;
}

char enemy_get_symbol(Enemy *enemy) {
  return enemy->type->get_symbol();
}

int enemy_get_actHP(Enemy *enemy) {
  return enemy->actHP;
}

int enemy_get_hiddenHealth(Enemy *enemy) {
  return enemy->hiddenHP;
}

void enemy_die(Enemy *enemy) {
  enemy->isDead = 1;
}

void enemy_damage(Enemy *enemy, int amount) {
  enemy->actHP -= amount;
  enemy->hiddenHP -= amount;
  if (enemy->actHP <= 0) {
    enemy_die(enemy);
  }
}

int enemy_isDead(Enemy *enemy) {
  return enemy->isDead;
}

void enemy_move_x(Enemy *enemy) {
  position_setX(&enemy->position, position_getX(&enemy->position) + enemy->type->speed);
}

void enemy_move_y(Enemy *enemy) {
  position_setY(&enemy->position, position_getY(&enemy->position) + enemy->type->speed);
}

void enemy_move_neg_x(Enemy *enemy) {
  position_setX(&enemy->position, position_getX(&enemy->position) - enemy->type->speed);
}

void enemy_move_neg_y(Enemy *enemy) {
  position_setY(&enemy->position, position_getY(&enemy->position) - enemy->type->speed);
}
